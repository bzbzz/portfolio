/*

Ce programme permet de résoudre une grille de sudoku de taille N

Optimisations faites :
-   Ajout de techniques de résolutions en plus du backtracking
-   On vérifie d'abord les lignes et les colonnes dans possible plutot que le bloc,
    car dans les deux cas on doit réaliser TAILLE itération, mais dans le premier cas on teste
    le double de valeurs en combinant lignes et colonnes.
-   On utilise estCandidat dans backtracking pour n'utiliser possible que si la valeur est autorisée
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define N 4
#define TAILLE (N * N)

typedef struct
{
    int valeur;
    bool candidats[TAILLE];
    int nbCandidats;
} tCase2;

typedef struct
{
    int val1;
    int val2;
    int l;
    int c;
} tPaire;

typedef tCase2 tGrille[TAILLE][TAILLE];
// FONCTIONS DE BASE
void chargerGrille(tGrille);
void afficherGrille(tGrille);
bool possible(tGrille, int, int, int);
// CANDIDATS
bool estCandidat(tCase2, int);
void ajouterCandidat(tCase2 *, int);
void retirerCandidat(tCase2 *, int);
void candidatIntoValeur(tCase2 *);
int candidatParIndex(tCase2, int);
void initialiserCandidats(tGrille);
void eliminerCandidats(tGrille, int, int, int);

bool paires_egales(tPaire, tPaire);
void afficherCandidats(tCase2);
// TECHNIQUES
bool backtracking(tGrille, int);
void singleton_nu(tGrille, bool *);
void singleton_cache(tGrille, bool *);
void paires_nues(tGrille, bool *);

int main()
{
    tGrille grille;
    clock_t deb;
    clock_t fin;
    double duree;
    bool progression = true;

    chargerGrille(grille);
    printf("Grille initiale\n");
    afficherGrille(grille);

    deb = clock();
    initialiserCandidats(grille);
    while (progression)
    {
        progression = false;
        singleton_nu(grille, &progression);
        singleton_cache(grille, &progression);
        paires_nues(grille, &progression);
    }
    backtracking(grille, 0);
    fin = clock();

    printf("Grille finale\n");
    afficherGrille(grille);

    duree = (fin - deb) * 1.0 / CLOCKS_PER_SEC;
    printf("Temps CPU = %.6f secondes\n", duree);

    return EXIT_SUCCESS;
}

void paires_nues(tGrille grille, bool *progression)
{
    tPaire tabPaires[TAILLE];
    tPaire paireAnalysee;
    int nbPaires = 0;
    int i; // Indice d'itération
    // Lignes
    for (int l = 0; l < TAILLE; l++)
    {
        nbPaires = 0;
        // Rempli le tableau tabPaires de toutes les paires presentes dans la ligne
        for (i = 0; i < TAILLE; i++)
        {
            if (grille[l][i].valeur == 0 && grille[l][i].nbCandidats == 2)
            {
                tabPaires[nbPaires].val1 = candidatParIndex(grille[l][i], 0);
                tabPaires[nbPaires].val2 = candidatParIndex(grille[l][i], 1);
                tabPaires[nbPaires].c = i;
                nbPaires++;
            }
        }
        // Tant qu'il reste des paires dans le tableau
        while (nbPaires > 0)
        {
            paireAnalysee = tabPaires[nbPaires - 1];
            i = 0;
            // On parcourt le tableau pour chercher une deuxieme occurrence de la
            // paire analyse, on s'arrete à l'avant derniere ou quand on a trouve
            while (i < nbPaires - 1)
            {
                if (paires_egales(paireAnalysee, tabPaires[i]))
                {
                    for (int j = 0; j < TAILLE; j++)
                    {
                        if (grille[l][j].valeur == 0 && j != paireAnalysee.c && j != tabPaires[i].c)
                        {
                            if (estCandidat(grille[l][j], paireAnalysee.val1))
                            {
                                retirerCandidat(&grille[l][j], paireAnalysee.val1);
                                *progression = true;
                            }
                            if (estCandidat(grille[l][j], paireAnalysee.val2))
                            {
                                retirerCandidat(&grille[l][j], paireAnalysee.val2);
                                *progression = true;
                            }
                        }
                    }
                }
                i++;
            }
            nbPaires--;
        }
    }
    // colonne
    for (int c = 0; c < TAILLE; c++)
    {
        nbPaires = 0;
        // Rempli le tableau tabPaires de toutes les paires presentes dans la ligne
        for (i = 0; i < TAILLE; i++)
        {
            if (grille[i][c].valeur == 0 && grille[i][c].nbCandidats == 2)
            {
                tabPaires[nbPaires].val1 = candidatParIndex(grille[i][c], 0);
                tabPaires[nbPaires].val2 = candidatParIndex(grille[i][c], 1);
                tabPaires[nbPaires].l = i;
                nbPaires++;
            }
        }
        // Tant qu'il reste des paires dans le tableau
        while (nbPaires > 0)
        {
            paireAnalysee = tabPaires[nbPaires - 1];
            i = 0;
            // On parcourt le tableau pour chercher une deuxieme occurrence de la
            // paire analyse, on s'arrete à l'avant derniere ou quand on a trouve
            while (i < nbPaires - 1)
            {
                if (paires_egales(paireAnalysee, tabPaires[i]))
                {
                    // Si on trouve une paire egales, on l'enleve de toutes les AUTRES cases
                    for (int j = 0; j < TAILLE; j++)
                    {
                        if (grille[j][c].valeur == 0 && j != paireAnalysee.l && j != tabPaires[i].l)
                        {
                            if (estCandidat(grille[j][c], paireAnalysee.val1))
                            {
                                retirerCandidat(&grille[j][c], paireAnalysee.val1);
                                *progression = true;
                            }
                            if (estCandidat(grille[j][c], paireAnalysee.val2))
                            {
                                retirerCandidat(&grille[j][c], paireAnalysee.val2);
                                *progression = true;
                            }
                        }
                    }
                }
                i++;
            }
            nbPaires--;
        }
    }
    // bloc
    // Deux boucles for pour se balader de blocs en blocs
    for (int l = 0; l < TAILLE; l += N)
    {
        for (int c = 0; c < TAILLE; c += N)
        {
            nbPaires = 0;
            // Rempli le tableau tabPaires de toutes les paires presentes dans le bloc
            for (i = l; i < l + N; i++)
            {
                for (int j = c; j < c + N; j++)
                {
                    if (grille[i][j].valeur == 0 && grille[i][j].nbCandidats == 2)
                    {
                        tabPaires[nbPaires].val1 = candidatParIndex(grille[i][j], 0);
                        tabPaires[nbPaires].val2 = candidatParIndex(grille[i][j], 1);
                        tabPaires[nbPaires].l = i;
                        tabPaires[nbPaires].c = j;
                        nbPaires++;
                    }
                }
            }
            // Tant qu'il reste des paires dans le tableau
            while (nbPaires > 0)
            {
                paireAnalysee = tabPaires[nbPaires - 1];
                i = 0;
                // On parcourt le tableau pour chercher une deuxieme occurrence de la
                // paire analyse, on s'arrete à l'avant derniere ou quand on a trouve
                while (i < nbPaires - 1)
                {
                    if (paires_egales(paireAnalysee, tabPaires[i]))
                    {
                        // Deux boucles pour se balader dans le bloc actuel
                        for (int v = l; v < l + N; v++)
                        {
                            for (int j = c; j < c + N; j++)
                            {
                                // Petite subtilite differente des lignes et colonnes
                                // On utilise un OU pour verifier les deux coordonnees en meme temps
                                if (grille[v][j].valeur == 0 && (v != paireAnalysee.l || j != paireAnalysee.c) && (v != tabPaires[i].l || j != tabPaires[i].c))
                                {
                                    if (estCandidat(grille[v][j], paireAnalysee.val1))
                                    {
                                        retirerCandidat(&grille[v][j], paireAnalysee.val1);
                                        *progression = true;
                                    }
                                    if (estCandidat(grille[v][j], paireAnalysee.val2))
                                    {
                                        retirerCandidat(&grille[v][j], paireAnalysee.val2);
                                        *progression = true;
                                    }
                                }
                            }
                        }
                    }
                    i++;
                }
                nbPaires--;
            }
        }
    }
}

void singleton_cache(tGrille grille, bool *progression)
{
    int i = 0;           // iteration
    int j = 0;           // deuxieme iteration pour le bloc
    int v = 1;           // valeur testee
    int occurrence = 0;  // nombre d'occurrence de la valeur
    int index = 0;       // index de la premiere occurrence
    int index2 = 0;      // deuxieme index quand on analyse dans le bloc
    bool trouve = false; // booleen permettant d'arreter quand on a trouve la valeur
    // ligne
    for (int l = 0; l < TAILLE; l++)
    {
        i = 0;
        v = 1;
        occurrence = 0;
        trouve = false;
        while (v <= TAILLE && !trouve)
        {
            if (grille[l][i].valeur == 0 && estCandidat(grille[l][i], v))
            {
                occurrence++;
                index = i;
            }
            i++;
            if (i == TAILLE)
            {
                if (occurrence == 1)
                {
                    grille[l][index].valeur = v;
                    trouve = true;
                    eliminerCandidats(grille, l, index, grille[l][index].valeur);
                    *progression = true;
                }
                i = 0;
                occurrence = 0;
                v++;
            }
        }
    }
    // colonne
    for (int c = 0; c < TAILLE; c++)
    {
        i = 0;
        v = 1;
        occurrence = 0;
        trouve = false;
        while (v <= TAILLE && !trouve)
        {
            if (grille[i][c].valeur == 0 && estCandidat(grille[i][c], v))
            {
                occurrence++;
                index = i;
            }
            i++;
            if (i == TAILLE)
            {
                if (occurrence == 1)
                {
                    grille[index][c].valeur = v;
                    trouve = true;
                    eliminerCandidats(grille, index, c, grille[index][c].valeur);
                    *progression = true;
                }
                i = 0;
                occurrence = 0;
                v++;
            }
        }
    }
    // Bloc
    for (int l = 0; l < TAILLE; l += N)
    {
        for (int c = 0; c < TAILLE; c += N)
        {
            i = l;
            j = c;
            v = 1;
            occurrence = 0;
            trouve = false;
            while (v <= TAILLE && !trouve)
            {
                if (grille[i][j].valeur == 0 && estCandidat(grille[i][j], v))
                {
                    occurrence++;
                    index = i;
                    index2 = j;
                }
                j++;
                // Fin du bloc on passe a la valeur suivante (IMPORTANT : la difference entre (l + N - 1) et (c + N) vient du fait
                // que j est incremente avant le if donc sa valeur sortira du bloc mais i sera toujours la derniere valeur du bloc)
                if (i == (l + N - 1) && j == (c + N))
                {
                    if (occurrence == 1)
                    {
                        grille[index][index2].valeur = v;
                        trouve = true;
                        eliminerCandidats(grille, index, index2, grille[index][index2].valeur);
                        *progression = true;
                    }
                    j = c;
                    i = l;
                    occurrence = 0;
                    v++;
                }
                else if (j == (c + N)) // Fin du ligne de N cases au sein du bloc, on passe à la ligne suivante de N cases
                {
                    j = c;
                    i++;
                }
            }
        }
    }
}

void singleton_nu(tGrille grille, bool *progression)
{
    for (int l = 0; l < TAILLE; l++)
    {
        for (int c = 0; c < TAILLE; c++)
        {
            if (grille[l][c].valeur == 0 && grille[l][c].nbCandidats == 1)
            {
                candidatIntoValeur(&grille[l][c]);
                eliminerCandidats(grille, l, c, grille[l][c].valeur);
                *progression = true;
            }
        }
    }
}

bool backtracking(tGrille grille, int numeroCase)
{
    int ligne;
    int colonne;
    bool resultat = false;
    if (numeroCase == TAILLE * TAILLE)
    {
        // On a traité toutes les cases, la grille est résolue
        resultat = true;
    }
    else
    {
        // On récupére les coordonnées de la case
        ligne = numeroCase / TAILLE;
        colonne = numeroCase % TAILLE;

        if (grille[ligne][colonne].valeur != 0)
        {
            // Si la case n'est pas vide, on passe à la suivante
            // (appel récursif)
            resultat = backtracking(grille, numeroCase + 1);
        }
        else
        {
            for (int valeur = 1; valeur <= TAILLE; valeur++)
            {
                if (estCandidat(grille[ligne][colonne], valeur) && possible(grille, ligne, colonne, valeur))
                {
                    // Si la valeur est autorisée on l'inscrit dans la case
                    grille[ligne][colonne].valeur = valeur;
                    // On passe à la suivante : appel récursif
                    // Pour voir si ce choix est bon par la suite
                    if (backtracking(grille, numeroCase + 1))
                    {
                        resultat = true;
                    }
                    else
                    {
                        grille[ligne][colonne].valeur = 0;
                    }
                }
            }
        }
    }
    return resultat;
}

void chargerGrille(tGrille g)
{
    char nomFichier[30];
    FILE *f;

    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");

    if (f == NULL)
    {
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    }
    else
    {
        for (int i = 0; i < TAILLE; i++)
        {
            for (int j = 0; j < TAILLE; j++)
            {
                fread(&g[i][j].valeur, sizeof(int), 1, f);
            }
        }
    }
    fclose(f);
}

bool possible(tGrille grille, int numLigne, int numColonne, int valeur)
{
    bool possible;
    possible = true;
    int l, c, i, j;
    i = 0;
    // Vérifie pour la ligne et la colonne en même temps
    while (i < TAILLE && possible)
    {
        if (grille[i][numColonne].valeur == valeur || grille[numLigne][i].valeur == valeur)
        {
            possible = false;
        }
        i++;
    }
    // Vérifie pour un bloc
    // Divisions entieres pour obtenir les coordonnées du bloc
    l = (numLigne / N) * N;
    c = (numColonne / N) * N;
    i = l;
    while (i < l + N && possible)
    {
        j = c;
        while (j < c + N && possible)
        {
            if (grille[i][j].valeur == valeur)
            {
                possible = false;
            }
            j++;
        }
        i++;
    }

    return possible;
}

void afficherGrille(tGrille grille)
{
    for (int i = 0; i < TAILLE; i++)
    {
        if (i % N == 0)
        {
            printf("+----------------+----------------+----------------+----------------+\n");
        }

        for (int j = 0; j < TAILLE; j++)
        {
            if (j % N == 0)
            {
                printf("|");
            }

            if (grille[i][j].valeur == 0)
            {
                printf("  . ");
            }
            else
            {
                printf(" %2d ", grille[i][j].valeur);
            }
        }
        printf("|");
        printf("\n");
    }
    printf("+----------------+----------------+----------------+----------------+\n");
}

// FONCTIONS CANDIDATS

void eliminerCandidats(tGrille grille, int numLigne, int numColonne, int valeur)
{
    int l, c;
    // ligne et colonne
    for (int i = 0; i < TAILLE; i++)
    {
        if (grille[numLigne][i].valeur == 0 && estCandidat(grille[numLigne][i], valeur))
        {
            retirerCandidat(&grille[numLigne][i], valeur);
        }
        if (grille[i][numColonne].valeur == 0 && estCandidat(grille[i][numColonne], valeur))
        {
            retirerCandidat(&grille[i][numColonne], valeur);
        }
    }
    // bloc
    l = (numLigne / N) * N;
    c = (numColonne / N) * N;
    // Vérifie pour un bloc
    for (int i = l; i < l + N; i++)
    {
        for (int j = c; j < c + N; j++)
        {
            if (grille[i][j].valeur == 0 && estCandidat(grille[i][j], valeur))
            {
                retirerCandidat(&grille[i][j], valeur);
            }
        }
    }
}

void candidatIntoValeur(tCase2 *laCase)
{
    int iter = 0;
    bool trouve;
    trouve = false;
    while (iter < TAILLE && !trouve)
    {
        if (laCase->candidats[iter] == true)
        {
            laCase->valeur = iter + 1;
            trouve = true;
        }
        iter++;
    }
}

void initialiserCandidats(tGrille grille)
{
    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = 0; j < TAILLE; j++)
        {
            for (int init = 0; init < TAILLE; init++)
            {
                grille[i][j].candidats[init] = false;
                grille[i][j].nbCandidats = 0;
            }
            for (int v = 1; v <= TAILLE; v++)
            {

                if (grille[i][j].valeur == 0 && possible(grille, i, j, v))
                {
                    ajouterCandidat(&grille[i][j], v);
                }
            }
        }
    }
}

void ajouterCandidat(tCase2 *laCase, int valeur)
{
    laCase->candidats[valeur - 1] = true;
    laCase->nbCandidats++;
}

void retirerCandidat(tCase2 *laCase, int valeur)
{
    if (laCase->candidats[valeur - 1] == true)
    {
        laCase->candidats[valeur - 1] = false;
        laCase->nbCandidats--;
    }
}

bool estCandidat(tCase2 laCase, int valeur)
{
    return laCase.candidats[valeur - 1];
}

void afficherCandidats(tCase2 laCase)
{
    printf("Candidat : ");
    for (int i = 0; i < TAILLE; i++)
    {
        if (laCase.candidats[i] == true)
        {
            printf("%d ", i + 1);
        }
    }
    printf("\n");
}

int candidatParIndex(tCase2 laCase, int index)
{
    int iter = 0;
    int occurrence = 0;
    int val = -1;
    bool trouve = false;
    while (iter < TAILLE && !trouve)
    {
        if (laCase.candidats[iter] == true && occurrence == index)
        {
            val = iter + 1;
            trouve = true;
        }
        else if (laCase.candidats[iter] == true)
        {
            occurrence++;
        }
        iter++;
    }

    return val;
}

bool paires_egales(tPaire p1, tPaire p2)
{
    // On teste si deux paires sont egales
    bool egaux = false;
    if (p1.val1 == p2.val1 && p1.val2 == p2.val2)
    {
        egaux = true;
    }
    else if (p1.val1 == p2.val2 && p1.val2 == p2.val1)
    {
        egaux = true;
    }
    return egaux;
}