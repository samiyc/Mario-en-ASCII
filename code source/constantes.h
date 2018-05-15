/*!==================================================================
Nom      : affichage.cpp
Projet   : mario
Editeur  : Samuel Yanez-Carbonell
===================================================================*/
#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED


//INCLUDE ===========================================================
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <math.h>
#include <windows.h>
using namespace std;


//DEFINE ============================================================
#define NB_LONGEUR_NIV_MAX 1000

#define BLOC_SIZE 4//3
#define NB_BLOC_HAUTEUR 15//20
#define NB_BLOC_LARGEUR 30//40

#define LARGEUR_FENETRE (BLOC_SIZE * NB_BLOC_LARGEUR)
#define HAUTEUR_FENETRE (BLOC_SIZE * NB_BLOC_HAUTEUR)

#define IMAGE_XMAX 400
#define IMAGE_YMAX 400
#define IMAGE_MAX_SIZE (IMAGE_XMAX * IMAGE_YMAX)

#define MAX_CHAINE 200
#define MAX_EVENEMENT 100


//ENUMERATION =======================================================
enum {D_LEFT, D_RIGHT, D_UP, D_DOWN};
enum {E_NULL, E_CAISSE, E_OR, E_CHECK, E_MONSTRE1, E_MONSTRE2, E_MONSTRE3};//evenement
enum {D_NULL, D_END, D_EXPLODE, D_APPLATI, D_CHUTE};//etape mort


//STRUCTURE =========================================================
typedef struct {
    int type;
    int pos_x;
    int pos_y;
    int ct1;
    int ct2;
    int ct3;
} struct_evenement;




//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#endif // CONSTANTES_H_INCLUDED
