/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "client.h"
#include "bmp.h"

#define MAX_COULEURS 30

void construire_json_couleurs(char *pathname, char *data, int nb_couleurs)
{
  couleur_compteur *cc = analyse_bmp_image(pathname);

  if (cc == NULL)
  {
    perror("Erreur analyse image");
    exit(EXIT_FAILURE);
  }

  int nb = nb_couleurs;
  if (nb > MAX_COULEURS)
  {
    nb = MAX_COULEURS;
  }

  if (cc->size < nb)
  {
    nb = cc->size;
  }

  strcpy(data, "{\"code\":\"couleurs\",\"valeurs\":[");

  char temp_string[64];

  for (int count = 1; count <= nb && cc->size - count >= 0; count++)
  {
    if (cc->compte_bit == BITS32)
    {
      sprintf(temp_string, "\"#%02x%02x%02x\"",
              cc->cc.cc32[cc->size - count].c.rouge,
              cc->cc.cc32[cc->size - count].c.vert,
              cc->cc.cc32[cc->size - count].c.bleu);
    }
    else
    {
      sprintf(temp_string, "\"#%02x%02x%02x\"",
              cc->cc.cc24[cc->size - count].c.rouge,
              cc->cc.cc24[cc->size - count].c.vert,
              cc->cc.cc24[cc->size - count].c.bleu);
    }

    strcat(data, temp_string);

    if (count < nb)
    {
      strcat(data, ",");
    }
  }

  strcat(data, "]}");
}

int envoie_couleurs_json(int socketfd, char *pathname, int nb_couleurs)
{
  char data[2048];
  memset(data, 0, sizeof(data));

  construire_json_couleurs(pathname, data, nb_couleurs);

  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("erreur ecriture");
    exit(EXIT_FAILURE);
  }

  printf("JSON envoye : %s\n", data);
  return 0;
}

int envoie_message_json(int socketfd)
{
  char saisie[512];
  char data[1024];

  memset(saisie, 0, sizeof(saisie));
  memset(data, 0, sizeof(data));

  printf("Votre message : ");
  fgets(saisie, sizeof(saisie), stdin);

  saisie[strcspn(saisie, "\n")] = '\0';

  sprintf(data, "{\"code\":\"message\",\"valeurs\":[\"%s\"]}", saisie);

  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("erreur ecriture");
    exit(EXIT_FAILURE);
  }

  memset(data, 0, sizeof(data));

  int read_status = read(socketfd, data, sizeof(data));
  if (read_status < 0)
  {
    perror("erreur lecture");
    return -1;
  }

  printf("Message recu : %s\n", data);
  return 0;
}

int main(int argc, char **argv)
{
  int socketfd;
  struct sockaddr_in server_addr;

  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  int connect_status = connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (connect_status < 0)
  {
    perror("connection serveur");
    exit(EXIT_FAILURE);
  }

  if (argc == 1)
  {
    envoie_message_json(socketfd);
  }
  else if (argc == 3)
  {
    int nb_couleurs = atoi(argv[2]);

    if (nb_couleurs <= 0 || nb_couleurs > MAX_COULEURS)
    {
      printf("Erreur: nb_couleurs doit etre entre 1 et %d\n", MAX_COULEURS);
      close(socketfd);
      return EXIT_FAILURE;
    }

    envoie_couleurs_json(socketfd, argv[1], nb_couleurs);
  }
  else
  {
    printf("usage:\n");
    printf("  ./client\n");
    printf("  ./client chemin_bmp_image nb_couleurs\n");
    close(socketfd);
    return EXIT_FAILURE;
  }

  close(socketfd);
  return 0;
}
