#include <stdio.h>
#include <stdlib.h>
#include "../plateau.h"
#include "test_plateau.h"
#include"test_main.h"



int test_init_ (Pion *plateau[8][8]) {
    init(plateau);
    printf("\ntest_init_ reussi\n\n");
	return 0;
}

int test_display (Pion *plateau[8][8]) {
    display (plateau);
    printf("test_display reussi\n\n");
	return 0;
}

int test_init_Pion(Pion *plateau[8][8]){
	int nb_pion=0;
	for (int pos_x=0;pos_x<8;pos_x++){
		for (int pos_y=0;pos_y<8;pos_y++){
			for (int couleur=BLANC;couleur<=NOIR;couleur++){
				Pion *p = init_Pion(couleur,pos_x,pos_y);
				if (p->couleur==couleur && p->pos_x==pos_x && p->pos_y==pos_y){
					nb_pion+=1;
				}
			}
		}
	}
	if (nb_pion==128){
		printf("test_init_Pion reussi\n\n");
		return 0;
	}
	else{
		printf("erreur sur test_init_Pion\n\n");
		return 1;
	}
}
		
					
			 

void test_all_plateau_function(Pion* plateau[8][8],int *run,int *failures) {
    run_test(test_init_(plateau),run,failures);
    run_test(test_display(plateau),run,failures);
    run_test(test_init_Pion(plateau),run,failures);

} 
