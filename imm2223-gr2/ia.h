/**
* \file ia.h
* \brief IA du jeu
* \author BENCHAHBOUN Rim PROUX Marc
* \version 0.1
*/

#ifndef ABALONE_IA
#define ABALONE_IA

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<limits.h>
#include "ihm.h"
#include "plateau.h"
#include "regles.h"

#define nbrDep 200

/**
 * \fn copyPlateau(Pion *tableau[8][8], Pion *tempTab[8][8])
 * \brief fait une copie du premier tableau dans le deuxieme
 * \param tableau de pointeur vers Pion
 * \param tableau de pointeur vers Pion
 */
void copyPlateau(Pion *tableau[8][8],Pion *tempTab[8][8]);

/**
 * \fn value(Pion *tableau[8][8], int x, int y)
 * \brief renvoie si la case du plateau est vide, occupé par un joueur ou hors plateau
 * \param tableau de pointeur vers Pion
 * \param int valeur de x
 * \param int valeur de y
 * \return la valeur de la case sous forme de int
*/
int value(Pion *tableau[8][8], int x, int y);

/**
 * \fn mvtLateral(int dl[2], int nbr, int billes[3][2], Pion *plateau[8][8], int *nbrMvt, Deplacement listMvt[nbrDep])
 * \brief determine tout les mouvements lateraux possible pour un joueur à un plateau donné et une liste de bille donnée
 * \param int tableau de direction a etudier
 * \param int nbr de bille a étudier (2 ou 3)
 * \param int liste des coordonées des billes a étudier
 * \param tableau de pointeur vers Pion
 * \param pointeur vers la variable contenant le nombre de mouvement possible
 * \param tableau de pointeur vers Deplacement
*/
void mvtLateral(int dl[2], int nbr, int billes[3][2], Pion *plateau[8][8], int *nbrMvt, Deplacement listMvt[nbrDep]);

/**
 * \fn mvtLigne(Pion *plateau[8][8], int *nbrMvt, int player, Deplacement listMvt[nbrDep])
 * \brief détermine tout les mouvements possibls pour un joueur à un tableau donnée
 * \param tableau de pointeur vers Pion
 * \param pointeur vers la variable contenant le nombre de mouvement possible
 * \param int couleur du joueur
 * \param tableau de pointeur vers Deplacement
*/
void mvtLigne(Pion *plateau[8][8], int *nbrMvt, int player, Deplacement listMvt[nbrDep]);

/**
 * \fn randomIA(Pion *plateau[8][8], int player)
 * \brief IA aléatoire, renvoie un mouvement aléatoire dans la liste des mouvements possibles
 * \param tableau de pointeur vers Pion
 * \param int couleur du joueur
 * \return un pointeur sur un déplacement
*/
Deplacement randomIA(Pion *plateau[8][8], int player);

/**
 * \fn attackPoss(Pion *plateau[8][8], int joueur)
 * \brief détermine le nombre d'attaque possible par un joueur à un plateau donnée
 * \param tableau de pointeur vers Pion
 * \param int couleur du joueur
 * \return nombre d'attaque possible
*/
int attackPoss(Pion *plateau[8][8], int joueur);

/**
 * \fn nbrBille(Pion *plateau[8][8], int joueur)
 * \brief détermine le nombre de bille d'un joueur à un plateau donnée
 * \param tableau de pointeur vers Pion
 * \param int couleur du joueur
 * \return nombre de bille du joueur
*/
int nbrBille(Pion *plateau[8][8], int joueur);

/**
 * \fn win(Pion *plateau[8][8], int joueur)
 * \brief détermine si le plateau est victorieux pour le joueur adverse
 * \param tableau de pointeur vers Pion
 * \param int couleur du joueur
 * \return 1 si victoire, 0 sinon
*/
int win(Pion *plateau[8][8], int joueur);

/**
 * \fn position(Pion *plateau[8][8], int joueur)
 * \brief détermine si, a un plateau donnée, la position des billes d'un joueur donnée est avantageuse ou non
 * \param tableau de pointeur vers Pion
 * \param int couleur du joueur
 * \return poids de la position des billes
*/
int position(Pion *plateau[8][8], int joueur);

/**
 * \fn posDang(Pion *plateau[8][8], int joueur)
 * \brief détermine le nombre de bille en position dangereuse du joueur à un plateau donnée
 * \param tableau de pointeur vers Pion
 * \param int couleur du joueur
 * \return nombre de billes en position dangereuse
*/
int posDang(Pion *plateau[8][8], int joueur);

/**
 * \fn groupement(Pion *plateau[8][8], int joueur)
 * \brief détermine le nombre de groupement de bille du joueur à un plateau donnée
 * \param tableau de pointeur vers Pion
 * \param int couleur du joueur
 * \return nombre de groupement
*/
int groupement(Pion *plateau[8][8], int joueur);

/**
 * \fn attackPoss(Pion *plateau[8][8], int joueur)
 * \brief evalue la qualité d'un plateau donnée pour un joueur
 * \param tableau de pointeur vers Pion
 * \param int couleur du joueur
 * \return qualité du plateau
*/
int eval(Pion *plateau[8][8], int joueur);

/**
 * \fn minimax_max(Pion *plateau[8][8], int joueur)
 * \brief fonction max de l'algorithme MinMax
 * \param tableau de pointeur vers Pion
 * \param int profondeur étudié
 * \param int couleur du joueur
 * \return score en max
*/
int minimax_max(Pion *plateau[8][8], int hauteur, int joueur);

/**
 * \fn minimax_min(Pion *plateau[8][8], int joueur)
 * \brief fonction min de l'algorithme MinMax
 * \param tableau de pointeur vers Pion
 * \param int profondeur étudié
 * \param int couleur du joueur
 * \return score en min
*/
int minimax_min(Pion *plateau[8][8], int hauteur, int joueur);

/**
 * \fn minimax(Pion *plateau[8][8], int hauteur, int joueur)
 * \brief IA MinMax, détermine le meilleur coup à joueur
 * \param tableau de pointeur vers Pion
 * \param int profondeur étudié
 * \param int couleur du joueur
 * \return un pointeur sur un déplacement
*/
Deplacement minmax(Pion *plateau[8][8], int hauteur, int joueur);

/**
 * \fn ia(Pion *plateau[8][8], int hauteur, int joueur)
 * \brief appel la fonction IA définie
 * \param tableau de pointeur vers Pion
 * \param int couleur du joueur
 * \return un pointeur sur deplacement
*/
Deplacement ia(Pion *plateau[8][8], int joueur);

/**
 * \fn alphaBeta_max(Pion *plateau[8][8], int hauteur, int joueur, int alpha, int beta)
 * \brief fonction max de l'algorithme AlphaBeta
 * \param tableau de pointeur vers Pion
 * \param int profondeur étudié
 * \param int couleur du joueur
 * \param int alpha
 * \param int beta
 * \return score en max
*/
int alphaBeta_max(Pion *plateau[8][8], int hauteur, int joueur, int alpha, int beta);

/**
 * \fn int alphaBeta_min(Pion *plateau[8][8], int hauteur, int joueur, int alpha, int beta)
 * \brief fonction min de l'algorithme AlphaBeta
 * \param tableau de pointeur vers Pion
 * \param int profondeur étudié
 * \param int couleur du joueur
 * \param int alpha
 * \param int beta
 * \return score en min
*/
int alphaBeta_min(Pion *plateau[8][8], int hauteur, int joueur, int alpha, int beta);

/**
 * \fn Deplacement alphaBeta(Pion *plateau[8][8], int hauteur, int joueur)
 * \brief IA AlphaBeta, détermine le meilleur coup à joueur
 * \param tableau de pointeur vers Pion
 * \param int profondeur étudié
 * \param int couleur du joueur
 * \return un pointeur sur un déplacement
*/
Deplacement alphaBeta(Pion *plateau[8][8], int hauteur, int joueur);

#endif