/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
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

/* ================= SOCKET ================= */

int envoie_operateur_numeros(int socketfd, char operateur, int num1, int num2)
{
  char data[1024];

  sprintf(data, "calcule : %c %d %d", operateur, num1, num2);

  if (write(socketfd, data, strlen(data)) < 0)
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
    return -1;

  memset(data, 0, sizeof(data));

  if (read(socketfd, data, sizeof(data)) < 0)
  {
    perror("Erreur de lecture");
    return -1;
  }

  if (sscanf(data, "calcule : %d", &resultat) == 1)
    return resultat;

  if (sscanf(data, "%d", &resultat) == 1)
    return resultat;

  printf("Reponse invalide: %s\n", data);
  return -1;
}

/* ================= FICHIERS ================= */

int lire_note_fichier(const char *chemin)
{
  FILE *f = fopen(chemin, "r");
  int note;

  if (!f)
  {
    perror("Erreur fichier");
    return -1;
  }

  fscanf(f, "%d", &note);
  fclose(f);
  return note;
}

int lire_note_etudiant(int etu, int note)
{
  char chemin[256];
  sprintf(chemin, "../etudiant/%d/note%d.txt", etu, note);
  return lire_note_fichier(chemin);
}

/* ================= AFFICHAGE ================= */

void afficher_notes()
{
  printf("Etudiant %d\n", etudiant_courant);

  for (int i = 1; i <= 5; i++)
  {
    printf("note%d = %d\n", i, lire_note_etudiant(etudiant_courant, i));
  }

  printf("somme = %d\n", somme_courante);
}

/* ================= CALCULS ================= */

int somme_d_un_etudiant(int socketfd, int etu)
{
  int n1 = lire_note_etudiant(etu, 1);
  int n2 = lire_note_etudiant(etu, 2);
  int n3 = lire_note_etudiant(etu, 3);
  int n4 = lire_note_etudiant(etu, 4);
  int n5 = lire_note_etudiant(etu, 5);

  int s1 = envoie_operateur_numeros_et_recois_resultat(socketfd, '+', n1, n2);
  int s2 = envoie_operateur_numeros_et_recois_resultat(socketfd, '+', n3, n4);
  int s3 = envoie_operateur_numeros_et_recois_resultat(socketfd, '+', s1, s2);
  int total = envoie_operateur_numeros_et_recois_resultat(socketfd, '+', s3, n5);

  return total;
}

/* ⭐ MODIFICATION PRINCIPALE */
int moyenne_des_5_etudiants(int socketfd)
{
  printf("Moyennes des 5 etudiants :\n");

  for (int i = 1; i <= 5; i++)
  {
    int somme = somme_d_un_etudiant(socketfd, i);
    int moyenne = envoie_operateur_numeros_et_recois_resultat(socketfd, '/', somme, 5);

    printf("Moyenne etudiant %d = %d/20\n", i, moyenne);
  }

  return 0;
}

/* ================= TOKENS ================= */

int convertir_token(char *token, int *valeur)
{
  int n;

  if (strcmp(token, "somme") == 0)
  {
    *valeur = somme_courante;
    return 0;
  }

  if (sscanf(token, "note%d", &n) == 1)
  {
    *valeur = lire_note_etudiant(etudiant_courant, n);
    return 0;
  }

  if (sscanf(token, "%d", valeur) == 1)
    return 0;

  return -1;
}

int commande_notes(int socketfd, char *msg)
{
  char op, t1[50], t2[50], extra[50];
  int v1, v2;

  if (sscanf(msg, " %c %s %s %s", &op, t1, t2, extra) != 3)
    return -1;

  if (convertir_token(t1, &v1) < 0 || convertir_token(t2, &v2) < 0)
    return -1;

  int res = envoie_operateur_numeros_et_recois_resultat(socketfd, op, v1, v2);

  somme_courante = res;
  printf("%d\n", res);

  return 0;
}

/* ================= MAIN LOOP ================= */

int envoie_recois_message(int socketfd)
{
  char msg[1024];
  char data[1024];
  int etu;

  printf("> ");
  fgets(msg, sizeof(msg), stdin);
  msg[strcspn(msg, "\n")] = 0;

  /* choisir étudiant */
  if (sscanf(msg, "etudiant %d", &etu) == 1)
  {
    etudiant_courant = etu;
    somme_courante = 0;
    printf("Etudiant %d selectionne\n", etudiant_courant);
    return 0;
  }

  /* voir notes */
  if (strcmp(msg, "voir_notes") == 0)
  {
    afficher_notes();
    return 0;
  }

  /* reset */
  if (strcmp(msg, "reset") == 0)
  {
    somme_courante = 0;
    return 0;
  }

  /* ⭐ NOUVELLE COMMANDE */
  if (strcmp(msg, "/ somme 5") == 0)
  {
    return moyenne_des_5_etudiants(socketfd);
  }

  /* ancien format */
  char op;
  int a, b;
  if (sscanf(msg, "calcule : %c %d %d", &op, &a, &b) == 3)
  {
    envoie_operateur_numeros(socketfd, op, a, b);
    read(socketfd, data, sizeof(data));
    printf("%s\n", data);
    return 0;
  }

  /* commandes notes */
  if (commande_notes(socketfd, msg) == 0)
    return 0;

  /* message texte */
  sprintf(data, "message: %s", msg);
  write(socketfd, data, strlen(data));
  read(socketfd, data, sizeof(data));
  printf("%s\n", data);

  return 0;
}

/* ================= MAIN ================= */

int main()
{
  int socketfd;
  struct sockaddr_in server_addr;

  socketfd = socket(AF_INET, SOCK_STREAM, 0);

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

  printf("Client connecte au serveur.\n");

  while (1)
  {
    if (envoie_recois_message(socketfd) < 0)
      break;
  }

  close(socketfd);
  return 0;
}
