/**
* \file regles.h
* \brief Regles du jeu Abalone et fonction pour vérifier la validité d'un déplacement
* \author Chappé Olivier et Durukan Ayhan
* \version 1.0
*/

#ifndef ABALONE_REGLES_H
#define ABALONE_REGLES_H
#include <stdbool.h>

#include "plateau.h"
#include "ihm.h"


#define HAUT 0
#define GAUCHE 1
#define DROITE 2
#define BAS 3

/**
* \fn abs(int x)
* \brief calcule la valeur absolue de x
* \param x entier quelconque
* \return un entier
*/
int abs(int x);

/**
* \fn min(int x, int y)
* \brief calcule le minimum entre x et y
* \param x entier quelconque
* \param y entier quelconque
* \return un entier
*/
int min(int x,int y);

/**
* \fn max(int x, int y)
* \brief calcule le maximum entre x et y
* \param x entier quelconque
* \param y entier quelconque
* \return un entier
*/
int max(int x,int y);

/**
* \fn echange_couleur(Pion *p1,Pion *p2)
* \brief échange les couleurs des pions
* \param p1 pointeur sur un Pion
* \param p2 pointeur sur un Pion
* \return rien (en place)
*/
void echange_couleur(Pion *p1,Pion *p2);

/**
* \fn check(Deplacement entree,Pion *plateau[8][8],int TOUR, bool deplacer)
* \brief Regarde si le déplacement est valide et le joue (si deplacer = true)
* \param entree le déplacement à valider
* \param plateau pointeur sur le plateau courant
* \param TOUR couleur du joueur courant
* \param deplacer booléen pour savoir si on joue le déplacement ou non
* \return rien (en place)
*/
bool check(Deplacement entree,Pion *plateau[8][8],int TOUR, bool deplacer);

/**
* \fn nb_ennemi(char entree[2], Pion* plateau[8][8], int direction, int nb_pion_ennemi, int nb_pion_allie)
* \brief Calcule le nombre d'ennemis dans un alignement (pour calculer le rapport de force)
* \param entree la case d'arrivée
* \param plateau pointeur sur le plateau courant
* \param direction la direction dans laquelle le déplacement a lieu
* \param nb_pion_ennemi nombre d'ennemis
* \param nb_pion_allie nombre d'alliés
* \return le nombre d'ennemis
*/
int nb_ennemi(char entree[2], Pion* plateau[8][8], int direction, int nb_pion_ennemi, int nb_pion_allie);

/**
* \fn check_win(Pion* plateau[8][8])
* \brief Regarde si la partie est finie
* \param plateau pointeur sur le plateau courant
* \return 0 si la partie et fini, 1 sinon
*/
int check_win(Pion* plateau[8][8]);


#endif //ABALONE_REGLES_H
