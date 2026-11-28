#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct cellule *Liste;
typedef struct cellule
{
    int val;
    Liste svt;
} node;
typedef Liste Tab[101]; // indices 1..100 utilisables

// 2. Créez la première colonne du triangle avec la valeur 1. Mettez l’adresse de cet
// élément dans le tableau :
// initialiser la tete :
void intialiser_tete(Liste *tete1, int N)
{
    int i;
    Liste p;

    for (i = 1; i <= N; i++)
    {
        p = malloc(sizeof(node)); // un nouveau noeud pour chaque ligne
        if (p != NULL)
        {
            p->val = 1;
            p->svt = NULL;
            tete1[i] = p;
        }
        else
        {
            printf("memory full\n");
            tete1[i] = NULL;
        }
    }
}

// ajouter_fin
void ajout_fin(Liste *tete, Liste *queue, int n)
{
    Liste nouv = malloc(sizeof(node));
    if (nouv != NULL)
    {
        nouv->val = n;
        nouv->svt = NULL;

        if (*tete == NULL)
        {
            *tete = nouv;
            *queue = nouv;
        }
        else
        {
            (*queue)->svt = nouv;
            *queue = nouv;
        }
    }
    else
    {
        printf("memory full\n");
    }
}

// 3. Écrire une action qui, à partir de la ligne n du triangle, calcule les valeurs
// de la ligne n+1
// construction new line
void calc_line(Liste E, Liste *S)
{
    // variables
    Liste p, q, queue;
    int x;

    if (E == NULL)
        return;

    // affectation
    p = E;
    q = E->svt;

    // queue = derniere cellule de S (NULL si S est vide)
    queue = *S;
    while (queue != NULL && queue->svt != NULL)
        queue = queue->svt;

    while (q != NULL)
    {
        x = p->val + q->val;
        ajout_fin(S, &queue, x);
        p = q;
        q = q->svt;
    }
    ajout_fin(S, &queue, 1);
}

// 4. Écrire une fonction qui affiche les éléments d’une ligne du triangle.
// Afficher ligne
void afficher_ligne(Liste tete)
{
    while (tete != NULL)
    {
        printf("%d -> ", tete->val);
        tete = tete->svt;
    }
    printf("NULL");
}

// 5. fonction qui vérifie si une ligne contient une valeur supérieure ou égale à nb
bool depasse(Liste tete, int nb)
{
    while (tete != NULL)
    {
        if (tete->val >= nb)
        {
            return true;
        }
        tete = tete->svt;
    }
    return false;
}

void libere_triangle(Liste *tete, int N);

void F(Tab tete, int N, int nb)
{
    int i;
    intialiser_tete(tete, N);
    i = 1;
    while (i <= N && !depasse(tete[i], nb))
    {
        afficher_ligne(tete[i]);
        printf("\n");
        if (i < N)
        {
            calc_line(tete[i], &tete[i + 1]);
        }
        i += 1;
    }
    libere_triangle(tete, N);
}

// 6. Ecrire une action qui libère l’espace mémoire alloué au triangle dans le but de
// retrouver la configuration donnée par l’étape 1.
void libere_triangle(Liste *tete, int N)
{
    int i;
    Liste p, tmp;

    for (i = 1; i <= N; i++)
    {
        p = tete[i];
        while (p != NULL)
        {
            tmp = p;
            p = p->svt;
            free(tmp);
        }
        tete[i] = NULL;
    }
}

int main()
{
    Tab t;
    int nb_ligne, i;

    // saisie avec controle : 1 <= nb_ligne <= 100
    do
    {
        printf("Donne le nombre de lignes (1..100) : ");
        if (scanf("%d", &nb_ligne) != 1)
        {
            printf("saisie invalide\n");
            return 1;
        }
    } while (nb_ligne < 1 || nb_ligne > 100);

    intialiser_tete(t, nb_ligne);

    for (i = 1; i <= nb_ligne - 1; i++)
    {
        calc_line(t[i], &t[i + 1]);
    }

    for (i = 1; i <= nb_ligne; i++)
    {
        afficher_ligne(t[i]);
        printf("\n");
    }

    libere_triangle(t, nb_ligne);

    printf("\n--- F(t, 10, 20) ---\n");
    F(t, 10, 20);

    return 0;
}