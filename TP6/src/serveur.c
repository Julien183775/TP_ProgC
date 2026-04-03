/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <math.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "serveur.h"

#define MAX_COULEURS 30

int socketfd;

int visualize_plot()
{
  const char *browser = "firefox";

  char command[256];
  snprintf(command, sizeof(command), "%s %s", browser, svg_file_path);

  int result = system(command);

  if (result == 0)
  {
    printf("SVG file opened in %s.\n", browser);
  }
  else
  {
    printf("Failed to open the SVG file.\n");
    printf("Graphique genere : %s\n", svg_file_path);
  }

  return 0;
}

double degreesToRadians(double degrees)
{
  return degrees * M_PI / 180.0;
}

int plot(char *data)
{
  int i;
  char *saveptr = NULL;
  char *str = data;
  char *token = strtok_r(str, ",", &saveptr);

  int num_colors = 0;
  char code[20];

  if (token == NULL)
  {
    fprintf(stderr, "Erreur: message vide\n");
    return 1;
  }

  sscanf(token, "%19s %d", code, &num_colors);

  if (strcmp(code, "couleurs:") != 0)
  {
    fprintf(stderr, "Erreur: code inattendu: %s\n", code);
    return 1;
  }

  if (num_colors <= 0 || num_colors > MAX_COULEURS)
  {
    fprintf(stderr, "Erreur: nombre de couleurs invalide: %d\n", num_colors);
    return 1;
  }

  double angles[MAX_COULEURS];
  memset(angles, 0, sizeof(angles));

  FILE *svg_file = fopen(svg_file_path, "w");
  if (svg_file == NULL)
  {
    perror("Error opening file");
    return 1;
  }

  fprintf(svg_file, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
  fprintf(svg_file, "<svg width=\"400\" height=\"400\" xmlns=\"http://www.w3.org/2000/svg\">\n");
  fprintf(svg_file, "  <rect width=\"100%%\" height=\"100%%\" fill=\"#ffffff\" />\n");

  double center_x = 200.0;
  double center_y = 200.0;
  double radius = 150.0;
  double start_angle = -90.0;

  token = strtok_r(NULL, ",", &saveptr);

  i = 0;
  while (i < num_colors && token != NULL)
  {
    angles[i] = 360.0 / num_colors;

    double end_angle = start_angle + angles[i];

    double start_angle_rad = degreesToRadians(start_angle);
    double end_angle_rad = degreesToRadians(end_angle);

    double x1 = center_x + radius * cos(start_angle_rad);
    double y1 = center_y + radius * sin(start_angle_rad);
    double x2 = center_x + radius * cos(end_angle_rad);
    double y2 = center_y + radius * sin(end_angle_rad);

    fprintf(svg_file,
            "  <path d=\"M%.2f,%.2f A%.2f,%.2f 0 0,1 %.2f,%.2f L%.2f,%.2f Z\" fill=\"%s\" />\n",
            x1, y1, radius, radius, x2, y2, center_x, center_y, token);

    start_angle = end_angle;
    i++;

    token = strtok_r(NULL, ",", &saveptr);
  }

  fprintf(svg_file, "</svg>\n");
  fclose(svg_file);

  visualize_plot();
  return 0;
}

int renvoie_message(int client_socket_fd, char *data)
{
  int data_size = write(client_socket_fd, (void *)data, strlen(data));

  if (data_size < 0)
  {
    perror("erreur ecriture");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int recois_envoie_message(int client_socket_fd, char data[1024])
{
  printf("Message recu: %s\n", data);

  char code[20];
  sscanf(data, "%19s", code);

  if (strcmp(code, "message:") == 0)
  {
    renvoie_message(client_socket_fd, data);
  }
  else if (strcmp(code, "couleurs:") == 0)
  {
    plot(data);
  }
  else
  {
    printf("Code inconnu recu: %s\n", code);
  }

  return EXIT_SUCCESS;
}

void gestionnaire_ctrl_c(int signal)
{
  (void)signal;
  printf("\nSignal Ctrl+C capture. Sortie du programme.\n");
  close(socketfd);
  exit(0);
}

int main()
{
  int bind_status;
  struct sockaddr_in server_addr;

  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
    perror("Unable to open a socket");
    return -1;
  }

  int option = 1;
  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  bind_status = bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (bind_status < 0)
  {
    perror("bind");
    return EXIT_FAILURE;
  }

  signal(SIGINT, gestionnaire_ctrl_c);

  while (1)
  {
    listen(socketfd, 10);

    struct sockaddr_in client_addr;
    char data[1024];
    unsigned int client_addr_len = sizeof(client_addr);

    int client_socket_fd = accept(socketfd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket_fd < 0)
    {
      perror("accept");
      return EXIT_FAILURE;
    }

    memset(data, 0, sizeof(data));

    int data_size = read(client_socket_fd, (void *)data, sizeof(data));
    if (data_size < 0)
    {
      perror("erreur lecture");
      close(client_socket_fd);
      continue;
    }

    recois_envoie_message(client_socket_fd, data);
    close(client_socket_fd);
  }

  return 0;
}
