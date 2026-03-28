#include <stdio.h>
#include <string.h>

#define MAX_LIGNE 1024

int main(int argc, char *argv[])
{
    FILE *fichier;
    char ligne[MAX_LIGNE];
    char phrase[100];
    int num_ligne = 0;

    // Vérifier argument
    if (argc != 2)
    {
        printf("Usage : %s fichier.txt\n", argv[0]);
        return 1;
    }

    // Ouvrir fichier
    fichier = fopen(argv[1], "r");
    if (fichier == NULL)
    {
        printf("Erreur ouverture fichier\n");
        return 1;
    }

    // Demander la phrase
    printf("Entrez la phrase que vous souhaitez rechercher : ");
    fgets(phrase, sizeof(phrase), stdin);

    // Supprimer le \n de fgets
    phrase[strcspn(phrase, "\n")] = '\0';

    printf("\nRésultats de la recherche :\n");

    // Lire ligne par ligne
    while (fgets(ligne, sizeof(ligne), fichier) != NULL)
    {
        num_ligne++;
        int count = 0;
        char *pos = ligne;

        // Chercher toutes les occurrences dans la ligne
        while ((pos = strstr(pos, phrase)) != NULL)
        {
            count++;
            pos++; // avancer pour continuer la recherche
        }

        // Afficher si trouvé
        if (count > 0)
        {
            printf("Ligne %d, %d fois\n", num_ligne, count);
        }
    }

    fclose(fichier);
    return 0;
}
