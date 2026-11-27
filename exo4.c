#include <stdio.h>
#include <stdlib.h>

typedef struct cellule *Liste;
typedef struct cellule
{
    int val;
    Liste svt;
} node;

//////////////////////////////////////
// Fonction pour creer une liste :
void create_list(Liste *tete1)
{
    Liste q = NULL, nouv;
    int N, i, x;
    *tete1 = NULL;

    printf("donner le nombre d'elements : ");
    scanf("%d", &N);

    for (i = 1; i <= N; i++)
    {
        scanf("%d", &x);
        nouv = malloc(sizeof(node));
        if (nouv != NULL)
        {
            nouv->val = x;
            nouv->svt = NULL;

            if (*tete1 == NULL)
            {
                *tete1 = nouv;
                q = nouv;
            }
            else
            {
                q->svt = nouv;
                q = nouv;
            }
        }
    }
}

//////////////////////////////////////
// Fonction chercher_max :
int chercher_max(Liste tete1)
{
    Liste p;
    int max;
    max = tete1->val;
    p = tete1->svt;
    while (p != NULL)
    {
        if (p->val > max)
        {
            max = p->val;
        }
        p = p->svt;
    }
    return max;
}

//////////////////////////////////////
// Fonction liberer_max :
Liste liberer_max_element(Liste tete1, int max)
{
    Liste p, prec;
    p = tete1;
    prec = NULL;
    while (p != NULL && p->val != max)
    {
        prec = p;
        p = p->svt;
    }
    if (p != NULL)
    {
        if (prec == NULL) // l'element a supprimer est la tete
        {
            tete1 = tete1->svt;
        }
        else
        {
            prec->svt = p->svt;
        }
        free(p);
    }
    return tete1;
}

//////////////////////////////////////
// Fonction Creation_Element_Liste (insertion en tete) :
Liste Creation_Element_Liste(Liste Tete2, int max)
{
    Liste nouv = malloc(sizeof(node));
    if (nouv != NULL)
    {
        nouv->val = max;
        nouv->svt = Tete2;
        Tete2 = nouv;
    }
    return Tete2;
}

//////////////////////////////////////
// Fonction afficher_liste :
void affiche_list(Liste tete2)
{
    while (tete2 != NULL)
    {
        printf("%d -> ", tete2->val);
        tete2 = tete2->svt;
    }
    printf("NULL\n");
}

//////////////////////////////////////
// Fonction affiche_max :
void affiche_max(Liste tete2)
{
    if (tete2 == NULL)
    {
        printf("liste vide\n");
        return;
    }
    printf("%d : ", chercher_max(tete2));
}

int main()
{
    Liste tete1, tete2, tmp;
    int max;

    create_list(&tete1);
    tete2 = NULL;

    if (tete1 != NULL)
    {
        max = chercher_max(tete1);
        printf("The max is : %d\n", max);
    }

    while (tete1 != NULL)
    {
        max = chercher_max(tete1);
        tete1 = liberer_max_element(tete1, max);
        tete2 = Creation_Element_Liste(tete2, max);
    }
    affiche_list(tete2);

    // liberation de la memoire
    while (tete2 != NULL)
    {
        tmp = tete2;
        tete2 = tete2->svt;
        free(tmp);
    }
    return 0;
}