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

/**
 * Envoie une opération de calcul au serveur.
 *
 * Format :
 * calcule : <operateur> <num1> <num2>
 */
int envoie_operateur_numeros(int socketfd, char operateur, int num1, int num2)
{
  char data[1024];

  memset(data, 0, sizeof(data));
  sprintf(data, "calcule : %c %d %d", operateur, num1, num2);

  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("Erreur d'écriture");
    return -1;
  }

  return 0;
}

/**
 * Fonction pour envoyer et recevoir un message depuis un client connecté à la socket.
 *
 * @param socketfd Le descripteur de la socket utilisée pour la communication.
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int envoie_recois_message(int socketfd)
{
  char data[1024];
  char message[1024];
  char operateur;
  int num1, num2;

  // Réinitialisation
  memset(data, 0, sizeof(data));

  // Saisie utilisateur
  printf("Votre message (ex: texte ou calcule : + 23 45): ");
  fgets(message, sizeof(message), stdin);

  // Supprime le retour à la ligne
  message[strcspn(message, "\n")] = '\0';

  /*
   * Si le message correspond à une opération :
   * calcule : + 23 45
   */
  if (sscanf(message, "calcule : %c %d %d", &operateur, &num1, &num2) == 3)
  {
    if (envoie_operateur_numeros(socketfd, operateur, num1, num2) < 0)
    {
      return -1;
    }
  }
  else
  {
    // Message classique
    strcpy(data, "message: ");
    strcat(data, message);

    int write_status = write(socketfd, data, strlen(data));
    if (write_status < 0)
    {
      perror("Erreur d'écriture");
      return -1;
    }
  }

  // Réinitialisation
  memset(data, 0, sizeof(data));

  // Réception réponse serveur
  int read_status = read(socketfd, data, sizeof(data));
  if (read_status < 0)
  {
    perror("Erreur de lecture");
    return -1;
  }

  // Affichage
  printf("Message reçu: %s\n", data);

  return 0;
}

int main()
{
  int socketfd;
  struct sockaddr_in server_addr;

  /*
   * Création de la socket
   */
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  // Configuration serveur
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // Connexion au serveur
  int connect_status = connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (connect_status < 0)
  {
    perror("connection serveur");
    exit(EXIT_FAILURE);
  }

  // Boucle principale
  while (1)
  {
    envoie_recois_message(socketfd);
  }

  close(socketfd);
  return 0;
}

