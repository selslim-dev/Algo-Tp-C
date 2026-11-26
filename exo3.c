
#include <stdio.h>
#include <stdlib.h>

// ==================================================
// Declaration des types
// ==================================================

typedef struct cellule *Liste;

typedef struct cellule
{
    int val;
    Liste svt;
} nod;

// ==================================================
// Creer un noeud
// ==================================================

Liste creer_noeud(void)
{
    Liste L = malloc(sizeof(nod));

    if (L == NULL)
    {
        printf("Erreur d'allocation.\n");
        exit(EXIT_FAILURE);
    }

    return L;
}

// ==================================================
// Affichage d'une liste
// ==================================================

void afficher_liste(Liste T)
{
    while (T != NULL)
    {
        printf("%d -> ", T->val);
        T = T->svt;
    }

    printf("NULL\n");
}

// ==================================================
// Ajout a la fin
// ==================================================

void ajout_fin(Liste *T, Liste *Q, int x)
{
    Liste nouv;

    nouv = creer_noeud();

    nouv->val = x;
    nouv->svt = NULL;

    if (*T == NULL)
    {
        *T = nouv;
        *Q = nouv;
    }
    else
    {
        (*Q)->svt = nouv;
        *Q = nouv;
    }
}

// ==================================================
// Separaration des nombres pairs et impairs
// ==================================================

void separer_Listes(Liste *L1, Liste *L2, Liste T)
{
    Liste p1;
    Liste q1, q2;

    *L1 = NULL;
    *L2 = NULL;

    q1 = NULL;
    q2 = NULL;

    p1 = T;

    while (p1 != NULL)
    {
        if (p1->val % 2 == 0)
        {
            ajout_fin(L1, &q1, p1->val);
        }
        else
        {
            ajout_fin(L2, &q2, p1->val);
        }

        p1 = p1->svt;
    }
}

// ==================================================
// Creer une liste a partir de N valeurs
// ==================================================

void creation_liste(Liste *T, Liste *Q)
{
    int n, i, x;

    *T = NULL;
    *Q = NULL;

    printf("Donner le nombre d'elements : ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++)
    {
        printf("Donner l'element %d : ", i);
        scanf("%d", &x);

        ajout_fin(T, Q, x);
    }
}

// ==================================================
// Liberer une liste
// ==================================================

void liberer_liste(Liste *T)
{
    Liste p;

    while (*T != NULL)
    {
        p = *T;
        *T = (*T)->svt;
        free(p);
    }
}

// ==================================================
// Algorithme principal
// ==================================================

int main(void)
{
    Liste T;
    Liste L1, L2;
    Liste Q;

    T = NULL;
    L1 = NULL;
    L2 = NULL;
    Q = NULL;

    // Creation de la liste initiale
    printf("\n--- Creation de la liste T ---\n");
    creation_liste(&T, &Q);

    // Affichage de la liste initiale
    printf("\nListe initiale : ");
    afficher_liste(T);

    // Separation des nombres pairs et impairs
    separer_Listes(&L1, &L2, T);

    // Affichage des deux listes obtenues
    printf("\nListe des nombres pairs : ");
    afficher_liste(L1);

    printf("Liste des nombres impairs : ");
    afficher_liste(L2);

    // Liberation de la memoire
    liberer_liste(&T);
    liberer_liste(&L1);
    liberer_liste(&L2);

    return 0;
}
