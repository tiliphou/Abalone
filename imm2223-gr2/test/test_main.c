
#include "test_plateau.h"
#include "test_regles.h"
#include "ihm_test.h"




void run_test(int* fonction_de_test(), int* nb_run,int* nb_failures){
	if (fonction_de_test==1){
		*nb_failures+=1;
	}
	*nb_run+=1;
}

void main(){
	Pion* plateau[8][8];
	int failures=0;
	int run=0;
	test_all_plateau_function(plateau,&run,&failures);
	test_all_regles_function(&run,&failures);
	test_all_ihm_function(&run,&failures);
	
	printf("\nnb_test :%i, erreur:%i\n\n",run,failures);
}
