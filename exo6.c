#include <stdio.h>
#include <stdlib.h>

// Declaration des types
typedef struct cellule *Liste;
typedef struct cellule
{
    int val;
    Liste svt;
} node;

// 1. Ecrire une procédure Ajout_Début_Fin (T : liste, Q : liste, x : entier) qui
// insert la valeur x en tête et en queue d’une liste simplement chaînée.Exemple pour
// x = 5, on obtient:
void Ajout_Debut_Fin(Liste T, Liste Q, int x)
{
}
