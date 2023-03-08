/**
* \file ihm.h
* \brief Jonction humain machine
* \author Luca Diaconnu 
* \version 0.1
*/


#ifndef ABALONE_IHM_H
#define ABALONE_IHM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "plateau.h"

#define SIZE_ARG 5


/**
* \struct TPosition 
* \brief Position avec 2 char, x et y
*/
typedef struct {
    /*! Ordonnée */
    char x; 
    /*! Abscisse */
    char y;
}TPosition;
/**
* \typedef Créé un pointeur sur TPosition
*/
typedef TPosition* Position;

/**
* \typedef struct { char start[2]; char end[2];}Tdeplacement & typedef Tdeplacement* Deplacement
* \structure de deplacement avec deux tableaux de char en donées
* \création du pointeur de deplacement
*/
typedef struct { char start[2]; char end[2];}Tdeplacement;
typedef Tdeplacement* Deplacement;



/**
* \fn new_position(char x, char y)
* \brief Creation d'une structure de position avec les coordonnées données en entrée
* \param char coordonnée en x
* \param char coordonnée en y
* \return un doublet de char sous forme de tableau de char de taille 2
*/
Position new_position(char x, char y);


/**
* \fn convert(Position P1)
* \brief Normalisation des indices de position ASCII à 0 pour '1' et 0 pour 'A'
* \param pointeur sur une Position  
* \return une position avec des indices normalisés
*/
Position convert(Position P1);

/**
* \fn Deplacement new_tab(Position P1, Position P2)
* \brief Creation d'une structure de deplacement avec les coordonnées de depart et celles d'arrivée dans 
* \param pointeur sur la Position de depart
* \param pointeur sur la Position d'arrivée
* \return un doublet de positions sous forme de tableau de tableaux de char de taille 2
*/
Deplacement new_tab(Position P1, Position P2);

/**
 * \fn deplt_to_string(Deplacement d,char *input)
 * \brief Convertie un deplacement en string
 * \param pointeur sur un Deplacement
 * \param chaine de caractère char* qui contiendra le Deplacement 
 */
void deplt_to_string(Deplacement d,char *input);

/**
* \fn count(char *argv)
* \brief Compte le nombre de caractères donnés en entrée qui doit être de 5 (cf : SIZE_ARG) : 2 char position de départ, ':', 2 char position d'arrivée
* \param chaine de caractères char*
* \return longueur de la chaine de caractères sur forme d'entier
*/
int count(char *argv);

/**
* \fn char_to_int(char character)
* \brief Normalise un char correspondant à une lettre en minuscule à un indice ASCII entre 0 et 7  (ex : 'a' -> NULL car 97->0)
* \param un chaine de caractères char*
* \return l'indice ASCII int
*/
int lchar_to_int(char character);

/**
* \fn char_to_int(char character)
* \brief Normalise un char correspondant à une lettre en majuscule à un indice ASCII entre 0 et 7  (ex : 'A' -> NULL car 65->0)
* \param un chaine de caractères char*
* \return l'indice ASCII int
*/
int char_to_int(char character);

/**
* \fn int_to_int(char character)
* \brief Normalise un char correspondant à un entier à un indice ASCII entre 0 et 7 (ex : '1' -> NULL car 49->0)
* \param un chaine de caractères char*
* \return l'indice ASCII int
*/
int int_to_int(char character);

/**
* \fn verification(int number)
* \brief Verifie si cet entier se situe entre 0 et 7, les coordonnées du plateau
* \param un entier a verifier
* \return 1 si oui, 0 sinon
*/
int verification(int number);


/**
* \fn syntax(char* argv)
* \brief Verifie si la syntaxe est correcte, c'est-à-dire qu'il y ait bien le ':' entre les deux positions
* \param une chaine de caractères char *
* \return 1 si oui, 0 sinon
*/
int syntax(char* argv);


/**
* \fn valid_entry(char argv[10], int argument)
* \brief applique toutes les fontcions précedentes pour verifier la validité de l'argument donné
* \param la chaine de caractère d'entrée 
* \return 1 si oui, 0 sinon
*/
int valid_entry(char input[]);

/**
* \fn convert_command(char argv[10])
* \brief Créé deux structure de position et une structure de deplacement dans la foulée avec l'argument en chaine de caractères en entrée
* \param une chaine de caractères de taille 10 char*
* \return un pointeur sur un Deplacement 
*/
Deplacement convert_command(char argv[10]);

#endif //ABALONE_IHM_H
