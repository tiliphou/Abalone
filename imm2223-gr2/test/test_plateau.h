/**
* \file test_plateau.h
* \brief test des fonctions du fichier plateau.c
* \author Bocca Adrien et Durukan Ayhan
* \version 0.1
*/


#ifndef TEST_PLATEAU_H
#define TEST_PLATEAU_H 

#include "../plateau.h"
/**
* \fn test_init_(Pion* palteau[8][8]) 
* \brief test de la fonction init
* \param un tableau de Pion
* \return 0 si le test est bon
*/
int test_init_(Pion* plateau[8][8]);

/**
* \fn test_display(Pion* palteau[8][8]) 
* \brief test de la fonction display
* \param un tableau de Pion
* \return 0 si le test est bon
*/
int test_display (Pion* plateau[8][8]);


/**
* \fn test_init_pion(Pion* palteau[8][8]) 
* \brief test de la fonction init_Pion
* \param un tableau de Pion
* \return 0 si le test est bon, 1 sinon
*/
int test_init_pion(Pion* plateau[8][8]);


/**
* \fn test_all_plateau_function(Pion* palteau[8][8],int* run, int* failures) 
* \brief applique la fonction run_test sur les fonctions test définies précédemment
* \param un tableau de Pion
* \param un pointeur, run, sur un entier 
* \param un pointeur, failures, sur un entier
*/
void test_all_plateau_function(Pion* plateau[8][8],int *run,int *failures);

#endif