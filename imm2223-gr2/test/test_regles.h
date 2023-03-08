/**
* \file test_regles.h
* \brief test des fonctions du fichier regles.c
* \author Bocca Adrien et Durukan Ayhan
* \version 0.1
*/


#ifndef TEST_REGLES_H 
#define TEST_REGLES_H

/**
* \fn test_abs() 
* \brief test de la fonction abs
* \return 0 si le test est bon, 1 sinon
*/
int test_abs();

/**
* \fn test_min() 
* \brief test de la fonction min
* \return 0 si le test est bon, 1 sinon
*/
int test_min();

/**
* \fn test_max() 
* \brief test de la fonction max
* \return 0 si le test est bon, 1 sinon
*/
int test_max();

/**
* \fn test_echange_couleur() 
* \brief test de la fonction echange_couleur
* \return 0 si le test est bon, 1 sinon
*/
int test_echange_couleur();

/**
* \fn test_check() 
* \brief test de la fonction check
* \return 0 si le test est bon, 1 sinon
*/
int test_check ();

/**
* \fn test_all_regles_function(int* run,int* failures) 
* \brief applique la fonction run_test sur les fonctions test définies précédemment
* \param un pointeur, run, sur un entier 
* \param un pointeur, failures, sur un entier
*/
void test_all_regles_function(int* run,int* failures);

#endif