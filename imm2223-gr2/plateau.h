/**
* \file plateau.h
* \brief Gestion du plateau
* \author Ait Bouserhane Maria and Atir Ikram
* \version 0.1
*/

#ifndef ABALONE_PLATEAU_H
#define ABALONE_PLATEAU_H

#include <stdio.h>
#include <stdlib.h>

#define PION_BLANC 'O'
#define PION_NOIR 'X'
#define PION_VIDE '.'

#define BLANC 0
#define NOIR 1
#define VIDE 2
#define HORS -1



/**
* \struct PION
* \brief Un pion avec une couleur et des coordonnées
*/
typedef struct{
	/*! couleur : noir="X"; blanc="O"; case_vide="."*/
	char couleur;
	/*! ordonnée */
	char pos_x;	
	/*! abscisse */
	char pos_y;	
}Pion;


/** 
 * \fn *init_Pion(char couleur,int posx,int posy)
 * \brief fonction d'initialisation d'un PION
 * \param couleur du pion sous forme de caractère
 * \param position en x sous forme d'entier
 * \param position en y sous forme d'entier 
 * \return un pointeur sur un Pion
 */
Pion *init_Pion(char couleur,int posx,int posy);

/** 
 * \fn init(Pion *plateau[8][8]);
 * \brief Fonction initialisation du plateau 
 * \param Tableau de pointeur sur les Pions 
 */
void init(Pion *plateau[8][8]);

/** 
 * \fn display(Pion *plateau[8][8]);
 * \brief Affichage terminal du tableau de Pion
 * \param Tableau de pointeur sur les Pions
 */
void display(Pion *plateau[8][8]);


#endif //ABALONE_PLATEAU_H
