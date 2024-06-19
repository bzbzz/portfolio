/**
* \brief Programme de sudoku
* \author THUAULT Nathan
* \date 25 novembre 2023
*
* Ce programme permet de jouer une partie de sudoku directement
* dans le terminal à partir de grilles prédéfinies.
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 3
#define TAILLE N*N

typedef int tGrille[TAILLE][TAILLE];

void chargerGrille(tGrille);
void afficherGrille(tGrille);
void saisir(int*);
bool possible(tGrille,int,int,int);
bool grillePleine(tGrille);
/**
* \fn int main()
* \brief Programme principal.
*
* Le programme principal initialise tout d'abord une grille de type tGrille,
* un entier pour la valeur à insérer puis deux entiers pour représenter
* les coordonnées de cette valeur. La grille est chargée grâce à la fonction
* chargerGrille(). Une boucle while représente une partie de jeu en cours, elle
* recommence tant que grillePleine() renvoie faux. Au sein de cette boucle, on
* affiche la grille, appelle la fonction saisie() pour la valeur et ses coordonnées,
* puis on ajoute la valeur si la fonction possible() renvoie vrai avec ces paramètres.
*
*/
int main()
{
    tGrille grille1;
    int numLigne, numColonne, valeur;

    chargerGrille(grille1);

    while(!grillePleine(grille1))
    {
        afficherGrille(grille1);
        printf("Indices de la case ?\n");
        saisir(&numLigne);
        saisir(&numColonne);
        numLigne--;
        numColonne--;

        if(grille1[numLigne][numColonne] != 0)
        {
            printf("Impossible, la case n'est pas libre.\n");
        }
        else
        {
            printf("Valeur à insérer ? \n");
            saisir(&valeur);
            if(possible(grille1, numLigne, numColonne, valeur))
            {
                grille1[numLigne][numColonne] = valeur;
            }
        }
    }
    printf("Grille pleine, fin de partie\n");
    return EXIT_SUCCESS;
}
/**
* \fn void chargerGrille(tGrille g)
*
* Cette procédure permet de charger en mémoire une grille de sudoku existante à
* partir d’un fichier dont le nom est lu au clavier.
*
*/
void chargerGrille(tGrille g)
{
    char nomFichier[30];
    FILE * f;

    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);

    f = fopen(nomFichier, "rb");

    if (f==NULL)
    {
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    }
    else
    {
        fread(g, sizeof(int), TAILLE*TAILLE, f);
    }
    fclose(f);
}
/**
* \fn bool possible(tGrille grille, int numLigne, int numColonne, int valeur)
* \brief Vérifie s'il est possible d'entrer un entier aux coordonnées saisies
* Cette fonction vérifie si une valeur peut être ajoutée dans une case particulière de la grille.
* - La valeur n’est pas déjà présente sur la même ligne que la case.
* - La valeur n’est pas déjà présente sur la même colonne que la case.
* - La valeur n’est pas déjà présente dans le même bloc que la case.
* Pour vérifier à l'intérieur d'un bloc, on doit d'abord obtenir les coordonnées
* du bloc grâce à la division entière des coordonnées numLigne et numColonne par N puis
* on les multiplie par N.
*/
bool possible(tGrille grille, int numLigne, int numColonne, int valeur)
{
    bool possible;
    possible = true;
    int l, c;
    // Divisions entieres pour obtenir les coordonnées du bloc
    l = (numLigne/3)*3; 
    c = (numColonne/3)*3;
    // Vérifie pour un bloc
    for (int i = l; i < l+3; i++)
    {
        for (int j = c; j < c+3; j++)
        {
            if (grille[i][j] == valeur)
            {
                possible = false;
                printf("La valeur est déjà présente dans son bloc.\n");
            }
        }
    }
    // Vérifie pour les colonnes seulement si possible n'est pas deja false
    if (possible)
    {
        for (int i = 0; i < TAILLE; i++)
        {
            if (grille[i][numColonne] == valeur)
            {
                possible = false;
                printf("La valeur est déjà présente sur sa colonne.\n");
            }
        }
    }
    // Vérifie pour les lignes seulement si possible n'est pas deja false 
    if (possible)
    {
        for (int i = 0; i < TAILLE; i++)
        {
            if (grille[numLigne][i] == valeur)
            {
                possible = false;
                printf("La valeur est déjà présente sur sa ligne.\n");
            }
        }
    }

    return possible;
}
/**
* \fn void afficherGrille(tGrille grille)
* \brief Affiche la grille
*/
void afficherGrille(tGrille grille)
{
    printf("     1  2  3   4  5  6   7  8  9\n");
    for (int i = 0; i < TAILLE; i++)
    {
        if (i%3 == 0)
        {
            printf("   +---------+---------+---------+\n");
        }

        for (int j = 0; j < TAILLE; j++)
        {
            if(j == 0)
            {
                printf("%d  ",i+1);
            }

            if (j%3 == 0)
            {
                printf("|");
            }

            if (grille[i][j] == 0)
            {
                printf(" . ");
            }
            else
            {
                printf(" %d ",grille[i][j]);
            }
        }
        printf("|");
        printf("\n");
    }
    printf("   +---------+---------+---------+\n");
}
/**
* \fn void saisir(int* valeur)
* \brief Effectue la saisie
* Cette fonction réalise la saisie en vérifiant qu'elle soit conforme.
* Elle permet de vérifier que la valeur est compris entre 1 et 9 inclus.
* Elle permet aussi de vérifier que la saisie est bien un entier grâce
* à la fonction sscanf().
* 
*/
void saisir(int* valeur)
{
    char ch [2];
    bool nonValide;
    do
    {
        printf("Saisie : ");
        scanf("%s",ch);
        // le sscanf est en premier dans la condition car la fonction doit etre executée pour que ch aille
        // dans valeur avant de faire les comparaisons avec un int
        nonValide = (sscanf(ch, "%d", valeur) == 0 || *valeur < 1 || *valeur > TAILLE);
        if (nonValide)
        {
            printf("Erreur dans la saisie!\n");
        }
    } while (nonValide);
}
/**
* \fn bool grillePleine(tGrille grille1)
* \brief Vérifie si la grille est pleine.
*/
bool grillePleine(tGrille grille1)
{
    int i,j;
    bool pleine;

    i = 0;
    j = 0;
    pleine = true;

    while (i < TAILLE && pleine)
    {
        while (j < TAILLE && pleine)
        {
            if (grille1[i][j]==0)
            {
                pleine = false;
            }
            j++;
        }
        i++;
        j = 0;
    }
    return pleine;
}