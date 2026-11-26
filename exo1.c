
#include <stdio.h>
#include <stdlib.h>

// Declaration des types
typedef struct cellule *Liste;

typedef struct cellule
{
    int val;
    Liste svt;
} nod;

// Afficher la liste
void afficher_liste(Liste tete)
{
    while (tete != NULL)
    {
        printf("%d ", tete->val);
        tete = tete->svt;
    }

    printf("\n");
}

// Initialiser la liste avec les entiers de 2 a 1000
void initialiser_liste(Liste *tete, Liste *queue)
{
    Liste p;
    int i;

    *tete = NULL;
    *queue = NULL;

    for (i = 2; i <= 1000; i++)
    {
        p = malloc(sizeof(nod));

        if (p != NULL)
        {
            p->val = i;
            p->svt = NULL;

            if (*tete == NULL)
            {
                *tete = p;
                *queue = p;
            }
            else
            {
                (*queue)->svt = p;
                *queue = p;
            }
        }
        else
        {
            printf("Erreur : memoire insuffisante.\n");
            return;
        }
    }
}

// Crible d'Eratosthene
void crible_erastostene(Liste tete)
{
    Liste p;
    Liste courant;
    Liste prc;

    p = tete;

    while (p != NULL && p->val * p->val <= 1000)
    {
        prc = p;
        courant = p->svt;

        while (courant != NULL)
        {
            if (courant->val % p->val == 0)
            {
                prc->svt = courant->svt;
                free(courant);
                courant = prc->svt;
            }
            else
            {
                prc = courant;
                courant = courant->svt;
            }
        }

        p = p->svt;
    }
}

// Liberer toute la liste
void liberer_liste(Liste *tete)
{
    Liste p;

    while (*tete != NULL)
    {
        p = *tete;
        *tete = (*tete)->svt;
        free(p);
    }
}

// Algorithme principal
int main(void)
{
    Liste Tete, Queue;

    Tete = NULL;
    Queue = NULL;

    // Initialisation
    initialiser_liste(&Tete, &Queue);

    // Application du crible
    crible_erastostene(Tete);

    // Affichage des nombres premiers
    printf("Nombres premiers entre 2 et 1000 :\n");
    afficher_liste(Tete);

    // Liberation de la memoire
    liberer_liste(&Tete);

    return 0;
}
