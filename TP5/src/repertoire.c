#include "repertoire.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>

void lire_dossier(const char *nom_repertoire) {
    DIR *dir;
    struct dirent *entry;

    // Ouvrir le répertoire
    dir = opendir(nom_repertoire);
    if (dir == NULL) {
        perror("Erreur lors de l'ouverture du répertoire");
        return;
    }

    printf("Contenu du répertoire '%s' :\n", nom_repertoire);

    // Lire les entrées
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Fermer le répertoire
    closedir(dir);
}

void lire_dossier_recursif(const char *nom_repertoire) {
    DIR *dir;
    struct dirent *entry;
    char chemin[1024];

    dir = opendir(nom_repertoire);
    if (dir == NULL) {
        perror("Erreur lors de l'ouverture du répertoire");
        return;
    }

    printf("Répertoire : %s\n", nom_repertoire);

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            printf("%s\n", entry->d_name);

            if (entry->d_type == DT_DIR) {
                snprintf(chemin, sizeof(chemin), "%s/%s", nom_repertoire, entry->d_name);
                lire_dossier_recursif(chemin);
            }
        }
    }

    closedir(dir);
}

void lire_dossier_iteratif(const char *nom_repertoire) {
    DIR *dir;
    struct dirent *entry;

    // petite "pile" de dossiers
    char dossiers[100][1024];
    int top = 0;

    // on ajoute le dossier initial
    strcpy(dossiers[top++], nom_repertoire);

    while (top > 0) {
        // on récupère un dossier
        char *current = dossiers[--top];

        dir = opendir(current);
        if (dir == NULL) {
            perror("Erreur");
            continue;
        }

        printf("\nRépertoire : %s\n", current);

        while ((entry = readdir(dir)) != NULL) {

            if (strcmp(entry->d_name, ".") != 0 &&
                strcmp(entry->d_name, "..") != 0) {

                printf("%s\n", entry->d_name);

                if (entry->d_type == DT_DIR) {
                    char chemin[1024];
                    snprintf(chemin, sizeof(chemin), "%s/%s", current, entry->d_name);

                    // on empile le sous-dossier
                    strcpy(dossiers[top++], chemin);
                }
            }
        }

        closedir(dir);
    }
}
