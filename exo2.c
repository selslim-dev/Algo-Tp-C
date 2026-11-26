
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
// Ajouter un element a la fin d'une liste
// ==================================================

void Ajout_fin(Liste *T, Liste *Q, int x)
{
    Liste nouv;

    nouv = malloc(sizeof(nod));

    if (nouv == NULL)
    {
        printf("Erreur : memoire insuffisante.\n");
        return;
    }

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
// Creer une liste
// ==================================================

void Creation_Liste(Liste *T, Liste *Q)
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

        Ajout_fin(T, Q, x);
    }
}

// ==================================================
// Interclasser deux listes triees
// ==================================================

Liste interclasse_deux_liste(Liste L1, Liste L2)
{
    Liste p1, p2, T3, Q3;

    T3 = NULL;
    Q3 = NULL;

    p1 = L1;
    p2 = L2;

    while (p1 != NULL && p2 != NULL)
    {
        if (p1->val <= p2->val)
        {
            Ajout_fin(&T3, &Q3, p1->val);
            p1 = p1->svt;
        }
        else
        {
            Ajout_fin(&T3, &Q3, p2->val);
            p2 = p2->svt;
        }
    }

    while (p1 != NULL)
    {
        Ajout_fin(&T3, &Q3, p1->val);
        p1 = p1->svt;
    }

    while (p2 != NULL)
    {
        Ajout_fin(&T3, &Q3, p2->val);
        p2 = p2->svt;
    }

    return T3;
}

// ==================================================
// Afficher une liste
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
// Programme principal
// ==================================================

int main(void)
{
    Liste L1, L2, L3;
    Liste Q1, Q2;

    L1 = NULL;
    L2 = NULL;
    L3 = NULL;

    Q1 = NULL;
    Q2 = NULL;

    // Creation des deux listes
    printf("\n--- Creation de L1 ---\n");
    Creation_Liste(&L1, &Q1);

    printf("\n--- Creation de L2 ---\n");
    Creation_Liste(&L2, &Q2);

    // Affichage des listes initiales
    printf("\nListe L1 : ");
    afficher_liste(L1);

    printf("Liste L2 : ");
    afficher_liste(L2);

    // Interclassement
    L3 = interclasse_deux_liste(L1, L2);

    // Affichage du resultat
    printf("\nListe apres interclassement : ");
    afficher_liste(L3);

    // Liberation de la memoire
    liberer_liste(&L1);
    liberer_liste(&L2);
    liberer_liste(&L3);

    return 0;
}
