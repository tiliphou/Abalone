/**
* \file test_regles.h
* \brief test des fonctions du fichier ihm.c
* \author AIT BOUSERHANE MARIA
* \version 0.1
*/

#ifndef IHM_TEST_H
#define IHM_TEST_H

#include<stdio.h>
#include<stdlib.h>
#include"../ihm.h"

/**
* \fn test_new_position() 
* \brief test de la fonction new_position
* \return 0 si le test est bon, 1 sinon
*/
int test_new_position();

/**
* \fn test_convert() 
* \brief test de la fonction convert
* \return 0 si le test est bon, 1 sinon
*/
int test_convert();

/**
* \fn test_new_tab() 
* \brief test de la fonction new_tab
* \return 0 si le test est bon, 1 sinon
*/
int test_new_tab();

/**
* \fn test_deplt_to_string() 
* \brief test de la fonction deplt_to_string
* \return 0 si le test est bon, 1 sinon
*/
int test_deplt_to_string();

/**
* \fn test_count() 
* \brief test de la fonction count
* \return 0 si le test est bon, 1 sinon
*/
int test_count();

/**
* \fn test_char_to_int() 
* \brief test de la fonction char_to_int
* \return 0 si le test est bon, 1 sinon
*/
int test_char_to_int();

/**
* \fn test_int_to_int() 
* \brief test de la fonction int_to_int
* \return 0 si le test est bon, 1 sinon
*/
int test_int_to_int();

/**
* \fn test_verification() 
* \brief test de la fonction verification
* \return 0 si le test est bon, 1 sinon
*/
int test_verification();

/**
* \fn test_syntax() 
* \brief test de la fonction syntax
* \return 0 si le test est bon, 1 sinon
*/
int test_syntax();

/**
* \fn test_valid_entry() 
* \brief test de la fonction valid_entry
* \return 0 si le test est bon, 1 sinon
*/
int test_valid_entry();

/**
* \fn test_convert_command() 
* \brief test de la fonction convert_command
* \return 0 si le test est bon, 1 sinon
*/
int test_convert_command();

/**
* \fn test_all_regles_function(int* run, int* failures) 
* \brief applique la fonction run_test sur les fonctions test définies précédemment
* \param un pointeur, run, sur un entier 
* \param un pointeur, failures, sur un entier
*/
void test_all_ihm_function(int* run, int* failures);

#endif