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

/* ================= VISUALISATION ================= */

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

/* ================= UTILS ================= */

double degreesToRadians(double degrees)
{
  return degrees * M_PI / 180.0;
}

/* ================= JSON PARSING ================= */

int extraire_code_json(const char *data, char *code, size_t taille_code)
{
  char *pos = strstr(data, "\"code\"");
  if (pos == NULL)
    return -1;

  pos = strchr(pos, ':');
  if (pos == NULL)
    return -1;

  pos = strchr(pos, '"');
  if (pos == NULL)
    return -1;
  pos++;

  char *fin = strchr(pos, '"');
  if (fin == NULL)
    return -1;

  size_t len = fin - pos;
  if (len >= taille_code)
    len = taille_code - 1;

  strncpy(code, pos, len);
  code[len] = '\0';

  return 0;
}

int extraire_valeurs_json(const char *data, char valeurs[MAX_COULEURS][256], int *nb_valeurs)
{
  char *pos = strstr(data, "\"valeurs\"");
  if (pos == NULL)
    return -1;

  pos = strchr(pos, '[');
  if (pos == NULL)
    return -1;
  pos++;

  int count = 0;

  while (*pos != '\0' && *pos != ']' && count < MAX_COULEURS)
  {
    while (*pos == ' ' || *pos == ',')
      pos++;

    if (*pos != '"')
      break;

    pos++;
    char *fin = strchr(pos, '"');
    if (fin == NULL)
      return -1;

    size_t len = fin - pos;
    if (len > 255)
      len = 255;

    strncpy(valeurs[count], pos, len);
    valeurs[count][len] = '\0';

    count++;
    pos = fin + 1;
  }

  *nb_valeurs = count;
  return 0;
}

/* ================= PLOT ================= */

int plot_json(char valeurs[MAX_COULEURS][256], int num_colors)
{
  if (num_colors <= 0)
  {
    fprintf(stderr, "Aucune couleur a afficher\n");
    return 1;
  }

  FILE *svg_file = fopen(svg_file_path, "w");
  if (svg_file == NULL)
  {
    perror("Error opening file");
    return 1;
  }

  fprintf(svg_file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
  fprintf(svg_file, "<svg width=\"400\" height=\"400\" xmlns=\"http://www.w3.org/2000/svg\">\n");
  fprintf(svg_file, "<rect width=\"100%%\" height=\"100%%\" fill=\"#ffffff\" />\n");

  double cx = 200.0;
  double cy = 200.0;
  double r = 150.0;
  double start_angle = -90.0;
  double angle = 360.0 / num_colors;

  for (int i = 0; i < num_colors; i++)
  {
    double end_angle = start_angle + angle;

    double a1 = degreesToRadians(start_angle);
    double a2 = degreesToRadians(end_angle);

    double x1 = cx + r * cos(a1);
    double y1 = cy + r * sin(a1);
    double x2 = cx + r * cos(a2);
    double y2 = cy + r * sin(a2);

    fprintf(svg_file,
            "<path d=\"M%.2f,%.2f A%.2f,%.2f 0 0,1 %.2f,%.2f L%.2f,%.2f Z\" fill=\"%s\" />\n",
            x1, y1, r, r, x2, y2, cx, cy, valeurs[i]);

    start_angle = end_angle;
  }

  fprintf(svg_file, "</svg>\n");
  fclose(svg_file);

  visualize_plot();
  return 0;
}

/* ================= MESSAGE ================= */

int renvoie_message_json(int client_socket_fd, char *message)
{
  char reponse[1024];

  snprintf(reponse, sizeof(reponse),
           "{\"code\":\"reponse\",\"valeurs\":[\"%s\"]}", message);

  write(client_socket_fd, reponse, strlen(reponse));

  return 0;
}

/* ================= TRAITEMENT ================= */

int traiter_message_json(int client_socket_fd, char data[2048])
{
  char code[64];
  char valeurs[MAX_COULEURS][256];  // ✅ FIX ICI
  int nb_valeurs = 0;

  printf("JSON recu: %s\n", data);

  if (extraire_code_json(data, code, sizeof(code)) != 0)
  {
    printf("Erreur extraction code JSON\n");
    return -1;
  }

  if (extraire_valeurs_json(data, valeurs, &nb_valeurs) != 0)
  {
    printf("Erreur extraction valeurs JSON\n");
    return -1;
  }

  if (strcmp(code, "message") == 0)
  {
    if (nb_valeurs > 0)
    {
      renvoie_message_json(client_socket_fd, valeurs[0]);
    }
  }
  else if (strcmp(code, "couleurs") == 0)
  {
    plot_json(valeurs, nb_valeurs);
  }
  else
  {
    printf("Code inconnu: %s\n", code);
  }

  return 0;
}

/* ================= SIGNAL ================= */

void gestionnaire_ctrl_c(int sig)
{
  (void)sig;
  printf("\nArret serveur\n");
  close(socketfd);
  exit(0);
}

/* ================= MAIN ================= */

int main()
{
  struct sockaddr_in server_addr;

  socketfd = socket(AF_INET, SOCK_STREAM, 0);

  int opt = 1;
  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

  signal(SIGINT, gestionnaire_ctrl_c);

  while (1)
  {
    listen(socketfd, 10);

    struct sockaddr_in client_addr;
    char data[2048];
    unsigned int len = sizeof(client_addr);

    int client_socket_fd = accept(socketfd, (struct sockaddr *)&client_addr, &len);

    memset(data, 0, sizeof(data));

    int size = read(client_socket_fd, data, sizeof(data) - 1);
    data[size] = '\0';

    traiter_message_json(client_socket_fd, data);

    close(client_socket_fd);
  }

  return 0;
}
