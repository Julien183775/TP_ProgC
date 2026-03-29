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

int etudiant_courant = 1;
int somme_courante = 0;

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

int envoie_operateur_numeros_et_recois_resultat(int socketfd, char operateur, int num1, int num2)
{
  char data[1024];
  int resultat = 0;

  if (envoie_operateur_numeros(socketfd, operateur, num1, num2) < 0)
  {
    return -1;
  }

  memset(data, 0, sizeof(data));

  int read_status = read(socketfd, data, sizeof(data));
  if (read_status < 0)
  {
    perror("Erreur de lecture");
    return -1;
  }

  if (sscanf(data, "calcule : %d", &resultat) == 1)
  {
    return resultat;
  }

  if (sscanf(data, "%d", &resultat) == 1)
  {
    return resultat;
  }

  printf("Reponse invalide du serveur : %s\n", data);
  return -1;
}

int lire_note_fichier(const char *chemin)
{
  FILE *fichier = fopen(chemin, "r");
  int note = -1;

  if (fichier == NULL)
  {
    perror("Erreur ouverture fichier");
    return -1;
  }

  if (fscanf(fichier, "%d", &note) != 1)
  {
    printf("Erreur lecture du fichier: %s\n", chemin);
    fclose(fichier);
    return -1;
  }

  fclose(fichier);
  return note;
}

int lire_note_etudiant(int numero_etudiant, int numero_note)
{
  char chemin[256];

  sprintf(chemin, "../etudiant/%d/note%d.txt", numero_etudiant, numero_note);
  return lire_note_fichier(chemin);
}

void afficher_notes_etudiant_courant()
{
  int i;
  int note;

  printf("Etudiant %d\n", etudiant_courant);

  for (i = 1; i <= 5; i++)
  {
    note = lire_note_etudiant(etudiant_courant, i);
    if (note < 0)
    {
      printf("note%d = erreur\n", i);
    }
    else
    {
      printf("note%d = %d\n", i, note);
    }
  }

  printf("somme = %d\n", somme_courante);
}

int convertir_token_en_valeur(char *token, int *valeur)
{
  int numero_note;

  if (strcmp(token, "somme") == 0)
  {
    *valeur = somme_courante;
    return 0;
  }

  if (sscanf(token, "note%d", &numero_note) == 1)
  {
    if (numero_note < 1 || numero_note > 5)
    {
      printf("Numero de note invalide: %s\n", token);
      return -1;
    }

    *valeur = lire_note_etudiant(etudiant_courant, numero_note);
    return 0;
  }

  if (sscanf(token, "%d", valeur) == 1)
  {
    return 0;
  }

  printf("Token invalide: %s\n", token);
  return -1;
}

int traite_commande_notes(int socketfd, char *message)
{
  char operateur;
  char token1[100];
  char token2[100];
  int valeur1, valeur2;
  int resultat;

  if (sscanf(message, " %c %99s %99s", &operateur, token1, token2) != 3)
  {
    return -1;
  }

  if (operateur != '+' && operateur != '-' && operateur != '*' && operateur != '/')
  {
    return -1;
  }

  if (convertir_token_en_valeur(token1, &valeur1) < 0)
  {
    return -1;
  }

  if (convertir_token_en_valeur(token2, &valeur2) < 0)
  {
    return -1;
  }

  resultat = envoie_operateur_numeros_et_recois_resultat(socketfd, operateur, valeur1, valeur2);
  if (resultat < 0)
  {
    return -1;
  }

  somme_courante = resultat;
  printf("%d\n", somme_courante);

  return 0;
}

int envoie_recois_message(int socketfd)
{
  char data[1024];
  char message[1024];
  char operateur;
  int num1, num2;
  int nouvel_etudiant;

  memset(data, 0, sizeof(data));

  printf("> ");

  if (fgets(message, sizeof(message), stdin) == NULL)
  {
    return -1;
  }

  message[strcspn(message, "\n")] = '\0';

  if (sscanf(message, "etudiant %d", &nouvel_etudiant) == 1)
  {
    if (nouvel_etudiant < 1 || nouvel_etudiant > 5)
    {
      printf("Etudiant invalide\n");
      return 0;
    }

    etudiant_courant = nouvel_etudiant;
    somme_courante = 0;
    printf("Etudiant %d selectionne\n", etudiant_courant);
    return 0;
  }

  if (strcmp(message, "voir_notes") == 0)
  {
    afficher_notes_etudiant_courant();
    return 0;
  }

  if (strcmp(message, "reset") == 0)
  {
    somme_courante = 0;
    printf("Somme remise a 0\n");
    return 0;
  }

  if (sscanf(message, "calcule : %c %d %d", &operateur, &num1, &num2) == 3)
  {
    int write_ok = envoie_operateur_numeros(socketfd, operateur, num1, num2);
    if (write_ok < 0)
    {
      return -1;
    }

    memset(data, 0, sizeof(data));

    int read_status = read(socketfd, data, sizeof(data));
    if (read_status < 0)
    {
      perror("Erreur de lecture");
      return -1;
    }

    printf("%s\n", data);
    return 0;
  }

  if (traite_commande_notes(socketfd, message) == 0)
  {
    return 0;
  }

  strcpy(data, "message: ");
  strcat(data, message);

  int write_status = write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("Erreur d'écriture");
    return -1;
  }

  memset(data, 0, sizeof(data));

  int read_status = read(socketfd, data, sizeof(data));
  if (read_status < 0)
  {
    perror("Erreur de lecture");
    return -1;
  }

  printf("%s\n", data);

  return 0;
}

int main()
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

  printf("Client connecte au serveur.\n");

  while (1)
  {
    if (envoie_recois_message(socketfd) < 0)
    {
      break;
    }
  }

  close(socketfd);
  return 0;
}
