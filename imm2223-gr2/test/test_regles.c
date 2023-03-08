#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../regles.h"
#include "../plateau.h"
#include "../ihm.h"
#include "test_regles.h"
#include"test_main.h"

int test_abs(){
	if (abs(1)==1 && abs(-1)==1){//abs renvoie la valeur absolue. On regarde donc si elle renvoie bien 1 pour 1 et -1 en paramètre.
		printf("test_abs reussi\n\n");
		return 0;
	}
	else{
		printf("erreur sur test_abs\n\n"); 
		return 1;
	}
}
	
int test_min(){
	if (min(2,1)==1 && min(1,2)==1){//min renvoie le plus petit entier entre les 2 paramètres. On regarde donc si elle renvoie bien 1 pour min(1,2) et min(2,1).
		printf("test_min reussi\n\n");
		return 0;
	}
	else{
		printf("erreur sur test_min\n\n");
		return 1;
	}
}

	
int test_max(){
	if (max(2,1)==2 && max(1,2)==2){//max renvoie le plus grand entier entre les 2 paramètres. On regarde si elle renvoie bien 2 pour max(1,2) et max(2,1).
		printf("test_max reussi\n\n");
		return 0;
	}
	else{
		printf("erreur sur test_max\n\n");
		return 1;
	}
}

 
int test_echange_couleur(){//echange_couleur permet d'échanger la couleur de 2 pions. On regarde si elle fonctionne pour tout les échanges de couleurs possibles.
	int test_reussi=0;
	for (int j=0 ; j<3 ; j++) {
        	for (int i=0 ; i<3 ; i++) {
            		Pion* p1 = init_Pion(j,2,3);
            		Pion* p2 = init_Pion(i,5,4);
            		char temp_couleur_p1 = p1->couleur;
            		char temp_couleur_p2 = p2->couleur;
            		echange_couleur(p1,p2);
            		if ((p1->couleur) == (temp_couleur_p2) && (p2->couleur) == (temp_couleur_p1))
                		test_reussi+=1;
            		else{
            			printf("erreur sur test_echange_couleur\n\n");    
                		return 1;
        		}
    		}
    	}
    	if (test_reussi==9){
    		printf("test_echange_couleur reussi\n\n");
			return 0;
    	}
}

int test_nb_ennemi(){
	int test_reussi=0;
	short i,j;
	Pion* plateau_test[8][8];
	for (i=0;i<8;i++){
		for (j=0;j<8;j++){
			if (i==0 && j<2){
				plateau_test[i][j]=init_Pion(BLANC,i,j);
			}
			else if (i==0 && j>=5){
				plateau_test[i][j]=init_Pion(BLANC,i,j);
			}
			else if(i==0 && j==3){
				plateau_test[i][j]=init_Pion(BLANC,i,j);
			}
			else if(i==1 && j==4){
				plateau_test[i][j]=init_Pion(BLANC,i,j);
			}
			else if(i==2 && j==4){
				plateau_test[i][j]=init_Pion(BLANC,i,j);
			}
			else if(i==7 && j==4){
				plateau_test[i][j]=init_Pion(BLANC,i,j);
			}
			else{
				plateau_test[i][j]=init_Pion(VIDE,i,j);
			}
		}
	}	

	char cas1[2]= {0,0};
	char cas2[2]= {0,6};
	char cas3[2]= {1,4};
	char cas4[2]= {2,4};
	char cas5[2]= {0,1};
	char cas6[2]= {0,6};
	char cas7[2]= {0,0}; 
	char cas8[2]= {7,4};
	if (nb_ennemi(cas1,plateau_test,DROITE,1,3)==2){// push possible de 2 billes vers la droite
		test_reussi+=1;
	}
	if (nb_ennemi(cas2,plateau_test,GAUCHE,1,3)==2){//push possible de 2 billes vers la gauche
		test_reussi+=1;
	}
	if (nb_ennemi(cas3,plateau_test,BAS,1,3)==2){//push possible de 2 billes vers la bas
		test_reussi+=1;
	}
	if (nb_ennemi(cas4,plateau_test,HAUT,1,2)==2){//push possible de 2 billes vers la haut
		test_reussi+=1;
	}
	if (nb_ennemi(cas5,plateau_test,GAUCHE,1,3)==-2){//push en dehors du plateau vers la gauche
		test_reussi+=1;
	}
	if (nb_ennemi(cas6,plateau_test,DROITE,1,3)==-2){//push en dehors du plateau vers la droite
		test_reussi+=1;
	}
	if (nb_ennemi(cas7,plateau_test,HAUT,1,2)==-2){//push en dehors du plateau vers le haut
		test_reussi+=1;
	}
	if (nb_ennemi(cas8,plateau_test,BAS,1,2)==-2){//push en dehors du plateau vers le bas
		test_reussi+=1;
	}	
	if (test_reussi==8){
		printf("test_nb_ennemi reussi\n\n");
		return 0;
	}

	else {
		printf("erreur sur test_nb_ennemi\n\n");
		return 1;
	}
}



int test_check () {

    Pion *plateau[8][8];
    for (int i=0 ; i<8 ; i++) {
        for (int j=0 ; j<8 ; j++) {
            plateau[i][j]=init_Pion(VIDE,i,j);
        }   
    } 

    int test_reussi=0;

    // ------------------------------- Test déplcement vertical vers le haut --------------------------------- //
   
    Deplacement entree1_1 = malloc(sizeof(Tdeplacement));
    entree1_1->start[1]=0;
    entree1_1->end[1]=0;
    int j = 11;

    // ----- Avec 0 ennemi -----
    for (int i=7 ; i>=5 ; i--) {
        j = j-2;
        plateau[(j-2)][0] = init_Pion(BLANC,(j-2),0);
        entree1_1->start[0]=i;
        entree1_1->end[0]=(j-3);

        char temp_couleur_depart1 = plateau[entree1_1->start[0]][entree1_1->start[1]]->couleur;
        char temp_couleur_arrive1 = plateau[entree1_1->end[0]][entree1_1->end[1]]->couleur;

        bool a = check(entree1_1,plateau,0,true);
        
        if (a == true && plateau[entree1_1->start[0]][entree1_1->start[1]]->couleur == temp_couleur_arrive1 && plateau[entree1_1->end[0]][entree1_1->end[1]]->couleur == temp_couleur_depart1)
            test_reussi++;
        else {
            printf ("Erreur : Déplacement vertical vers le haut avec la case d'arrivé vide");
            return 1;
        }
    }
   
    
    // ----- Avec 1 aliée qui bloque -----
    Deplacement entree1_2 = malloc(sizeof(Tdeplacement));
    entree1_2->start[0]=4;
    entree1_2->start[1]=0;
    entree1_2->end[0]=2;
    entree1_2->end[1]=0;
    
    if (check(entree1_2,plateau,0,true) == false)
        test_reussi+=1;
    else {
        printf ("Erreur : Déplacement vertical vers le haut avec 1 alliée dans la case d'arrivée");
        return 1;
    }   
 

    // ----- Avec nb_mate = nb_ennemie -----
    Deplacement entree1_3 = malloc(sizeof(Tdeplacement));
    entree1_3->start[0]=5;
    entree1_3->start[1]=1;
    entree1_3->end[0]=4;
    entree1_3->end[1]=1;

    plateau[5][1] = init_Pion(BLANC,5,1);
    plateau[4][1] = init_Pion(NOIR,4,1);

    if (check(entree1_3,plateau,0,true) == false) 
        test_reussi+=1;
    else {
        printf ("Erreur : Deplacement verticale vers le haut avec nb_mate = nb_ennemie");
        return 1;
    }
   

    // ----- Avec nb_mate > nb_ennemie && ejection -----
    Deplacement entree1_4 = malloc(sizeof(Tdeplacement));
    entree1_4->start[0]=2;
    entree1_4->start[1]=1;
    entree1_4->end[0]=0;
    entree1_4->end[1]=1;

    plateau[2][1] = init_Pion(BLANC,2,1);
    plateau[1][1] = init_Pion(BLANC,1,1);
    plateau[0][1] = init_Pion(NOIR,0,1);

    char temp_couleur_depart2 = plateau[entree1_4->start[0]][entree1_4->start[1]]->couleur;
    char temp_couleur_arrive2 = plateau[entree1_4->end[0]][entree1_4->end[1]]->couleur;

    bool b = check(entree1_4,plateau,0,true);

    if (b == true && plateau[entree1_4->end[0]][entree1_4->end[1]]->couleur == temp_couleur_depart2  && plateau[entree1_4->start[0]][entree1_4->start[1]]->couleur == VIDE) 
        test_reussi+=1;
    else {
        printf ("Erreur : Deplacement verticale vers le haut avec une ejection\n");
        return 1;
    }
   

    // ----- Deplacement impossible -----
    Deplacement entree1_5 = malloc(sizeof(Tdeplacement));
    entree1_5->start[0]=1;
    entree1_5->start[1]=1;
    entree1_5->end[0]=2;
    entree1_5->end[1]=4;
    
    if (check(entree1_5,plateau,0,true) == false) 
        test_reussi+=1;
    else {
        printf ("Erreur : Deplacement verticale vers le haut avec un d'éplacement impossible");
        return 1;
    }
    

    // ----- Pas de mouvement -----
    Deplacement entree1_6 = malloc(sizeof(Tdeplacement));
    entree1_6->start[0]=1;
    entree1_6->start[1]=1;
    entree1_6->end[0]=1;
    entree1_6->end[1]=1;
    
    if (check(entree1_6,plateau,0,true) == false) 
        test_reussi+=1;
    else {
        printf ("Erreur : L'arrivee = le depart => pas de mouvement");
        return 1;
    }
   

    // ----- Couleur de la case de départ different de la couleur du TOUR -----
    Deplacement entree1_8 = malloc(sizeof(Tdeplacement));
    entree1_8->start[0]=4;
    entree1_8->start[1]=1;
    entree1_8->end[0]=3;
    entree1_8->end[1]=1;
    
    if (check(entree1_8,plateau,0,true) == false) 
        test_reussi+=1;
    else {
        printf ("Erreur : Couleur de la case de départ different de la couleur du TOUR");
        return 1;
    }
   

    // ----- Limite du nombre de pion excédé -----
    Deplacement entree1_7 = malloc(sizeof(Tdeplacement));
    entree1_7->start[0]=7;
    entree1_7->start[1]=2;
    entree1_7->end[0]=3;
    entree1_7->end[1]=2;

    plateau[7][2] = init_Pion(BLANC,7,1);
    plateau[6][2] = init_Pion(BLANC,6,1);
    plateau[5][2] = init_Pion(BLANC,5,1);
    plateau[4][2] = init_Pion(BLANC,4,1);
    
    if (check(entree1_7,plateau,0,true) == false) 
        test_reussi+=1;
    else {
        printf ("Erreur : On prend trop de pions");
        return 1;
    }
   

    // ----- Avec au moin 1 et au plus 3 ennemi -----
    Deplacement entree1_9 = malloc(sizeof(Tdeplacement));
    entree1_9->start[0]=6;
    entree1_9->start[1]=2;
    entree1_9->end[0]=3;
    entree1_9->end[1]=2;

    plateau[3][2] = init_Pion(NOIR,3,2);
    plateau[2][2] = init_Pion(NOIR,2,2);

    char temp_couleur_depart3 = plateau[entree1_9->start[0]][entree1_9->start[1]]->couleur;
    char temp_couleur_arrive3 = plateau[entree1_9->end[0]][entree1_9->end[1]]->couleur;
    int nb_e1 = nb_ennemi(entree1_9->end,plateau,HAUT,1,3); 

    if (check(entree1_9,plateau,0,true) == true && plateau[entree1_9->end[0]-nb_e1][entree1_9->end[1]]->couleur == temp_couleur_arrive3 && plateau[entree1_9->end[0]][entree1_9->end[1]]->couleur == temp_couleur_depart3 && plateau[entree1_9->start[0]][entree1_9->start[1]]->couleur == VIDE)
        test_reussi+=1;
    else {
        printf ("Erreur : Poussé vertical vers le haut avec au moin 1 et au plus 3 ennemi");
        return 1;
    }   
   
    // ------------------------------- Test déplcement vertical vers le bas --------------------------------- //
    Deplacement entree2_0 = malloc(sizeof(Tdeplacement));
    entree2_0->start[0]=2;
    entree2_0->start[1]=0;
    entree2_0->end[0]=5;
    entree2_0->end[1]=0;

    plateau[5][0] = init_Pion(NOIR,5,0);
    plateau[6][0] = init_Pion(NOIR,6,0);

    char temp_couleur_depart4 = plateau[entree2_0->start[0]][entree2_0->start[1]]->couleur;
    char temp_couleur_arrive4 = plateau[entree2_0->end[0]][entree2_0->end[1]]->couleur;
    int nb_e2 = nb_ennemi(entree2_0->end,plateau,BAS,1,3); 

    if (check(entree2_0,plateau,0,true) == true && plateau[entree2_0->end[0]+nb_e2][entree2_0->end[1]]->couleur == temp_couleur_arrive4 && plateau[entree2_0->end[0]][entree2_0->end[1]]->couleur == temp_couleur_depart4 && plateau[entree2_0->start[0]][entree2_0->start[1]]->couleur == VIDE)
        test_reussi+=1;
    else {
        printf ("Erreur : Poussé vertical vers le bas avec au moin 1 et au plus 3 ennemi");
        return 1;
    }   
  
    //display(plateau);
    
    // ----------------------------- Test déplcement horizontal vers la gauche --------------------------------- //
   

    Deplacement entree3_0 = malloc(sizeof(Tdeplacement));
    entree3_0->start[0]=6;
    entree3_0->end[0]=6;
    int k = 11;

    // ----- Avec 0 ennemi -----
    for (int i=7 ; i>=5 ; i--) {
        k = k-2;
        plateau[6][(k-2)] = init_Pion(BLANC,(k-2),0);
        entree3_0->start[1]=i;
        entree3_0->end[1]=(k-3);

        char temp_couleur_depart5 = plateau[entree3_0->start[0]][entree3_0->start[1]]->couleur;
        char temp_couleur_arrive5 = plateau[entree3_0->end[0]][entree3_0->end[1]]->couleur;

        bool a = check(entree3_0,plateau,0,true);
        
        if (a == true && plateau[entree3_0->start[0]][entree3_0->start[1]]->couleur == temp_couleur_arrive5 && plateau[entree3_0->end[0]][entree3_0->end[1]]->couleur == temp_couleur_depart5)
            test_reussi++;
        else {
            printf ("Erreur : Déplacement horizontal vers la gauche avec la case d'arrivé vide");
            return 1;
        }
    }
   
    // ----- Avec 1 aliée qui bloque -----
    Deplacement entree3_1 = malloc(sizeof(Tdeplacement));
    entree3_1->start[0]=6;
    entree3_1->start[1]=4;
    entree3_1->end[0]=6;
    entree3_1->end[1]=2;
    
    if (check(entree3_1,plateau,0,true) == false)
        test_reussi+=1;
    else {
        printf ("Erreur : Déplacement horizontal vers la gauche avec 1 alliée dans la case d'arrivée");
        return 1;
    }   
   

    // ----- Avec nb_mate = nb_ennemie -----
    Deplacement entree3_2 = malloc(sizeof(Tdeplacement));
    entree3_2->start[0]=6;
    entree3_2->start[1]=3;
    entree3_2->end[0]=6;
    entree3_2->end[1]=1;

    plateau[6][1] = init_Pion(NOIR,6,1);

    if (check(entree3_2,plateau,0,true) == false) 
        test_reussi+=1;
    else {
        printf ("Erreur : Deplacement horizontal vers la gauche avec nb_mate = nb_ennemie");
        return 1;
    }
   

    // ----- Avec nb_mate > nb_ennemie && ejection -----
    Deplacement entree3_3 = malloc(sizeof(Tdeplacement));
    entree3_3->start[0]=6;
    entree3_3->start[1]=4;
    entree3_3->end[0]=6;
    entree3_3->end[1]=1;

    char temp_couleur_depart6 = plateau[entree3_3->start[0]][entree3_3->start[1]]->couleur;
    char temp_couleur_arrive6 = plateau[entree3_3->end[0]][entree3_3->end[1]]->couleur;

    bool l = check(entree3_3,plateau,0,true);

    if (l == true && plateau[entree3_3->end[0]][entree1_4->end[1]]->couleur == temp_couleur_depart6 && plateau[entree3_3->start[0]][entree3_3->start[1]]->couleur == VIDE) 
        test_reussi+=1;
    else {
        printf ("Erreur : Deplacement horizontal vers la gauche avec une ejection\n");
        return 1;
    }
   

    // ----- Deplacement impossible -----
    Deplacement entree3_4 = malloc(sizeof(Tdeplacement));
    entree3_4->start[0]=6;
    entree3_4->start[1]=3;
    entree3_4->end[0]=5;
    entree3_4->end[1]=4;
    
    if (check(entree3_4,plateau,0,true) == false) 
        test_reussi+=1;
    else {
        printf ("Erreur : Deplacement horizontal vers la gauche avec un d'éplacement impossible");
        return 1;
    }
   
    // ----- Pas de mouvement -----
    Deplacement entree3_5 = malloc(sizeof(Tdeplacement));
    entree3_5->start[0]=6;
    entree3_5->start[1]=3;
    entree3_5->end[0]=6;
    entree3_5->end[1]=3;
    
    if (check(entree3_5,plateau,0,true) == false) 
        test_reussi+=1;
    else {
        printf ("Erreur : L'arrivee = le depart => pas de mouvement");
        return 1;
    }
   

    // ----- Couleur de la case de départ different de la couleur du TOUR -----
    Deplacement entree3_6 = malloc(sizeof(Tdeplacement));
    entree3_6->start[0]=2;
    entree3_6->start[1]=2;
    entree3_6->end[0]=2;
    entree3_6->end[1]=1;
    
    if (check(entree3_6,plateau,0,true) == false) 
        test_reussi+=1;
    else {
        printf ("Erreur : Couleur de la case de départ different de la couleur du TOUR");
        return 1;
    }
   

    // ----- Limite du nombre de pion excédé -----
    Deplacement entree3_7 = malloc(sizeof(Tdeplacement));
    entree3_7->start[0]=6;
    entree3_7->start[1]=4;
    entree3_7->end[0]=6;
    entree3_7->end[1]=0;

    plateau[6][4] = init_Pion(BLANC,6,4);
    
    if (check(entree3_7,plateau,0,true) == false) 
        test_reussi+=1;
    else {
        printf ("Erreur : On prend trop de pions");
        return 1;
    }
   

    // ----- Avec au moin 1 et au plus 3 ennemi -----
    Deplacement entree3_8 = malloc(sizeof(Tdeplacement));
    entree3_8->start[0]=2;
    entree3_8->start[1]=4;
    entree3_8->end[0]=2;
    entree3_8->end[1]=2;

    plateau[2][4] = init_Pion(BLANC,2,4);
    plateau[2][3] = init_Pion(BLANC,2,3);

    char temp_couleur_depart7 = plateau[entree3_8->start[0]][entree3_8->start[1]]->couleur;
    char temp_couleur_arrive7 = plateau[entree3_8->end[0]][entree3_8->end[1]]->couleur;
    int nb_e3 = nb_ennemi(entree3_8->end,plateau,GAUCHE,1,2); 

    if (check(entree3_8,plateau,0,true) == true && plateau[entree3_8->end[0]][entree3_8->end[1]-nb_e3]->couleur == temp_couleur_arrive7 && plateau[entree3_8->end[0]][entree3_8->end[1]]->couleur == temp_couleur_depart7 && plateau[entree3_8->start[0]][entree3_8->start[1]]->couleur == VIDE)
        test_reussi+=1;
    else {
        printf ("Erreur : Poussé horizontal vers la gauche avec au moin 1 et au plus 3 ennemi");
        return 1;
    }   
  

    // ------------------------------- Test déplcement horizontal vers la droite --------------------------------- //
    Deplacement entree3_9 = malloc(sizeof(Tdeplacement));
    entree3_9->start[0]=6;
    entree3_9->start[1]=2;
    entree3_9->end[0]=6;
    entree3_9->end[1]=5;

    plateau[6][5] = init_Pion(NOIR,6,5);
    plateau[6][6] = init_Pion(NOIR,6,6);

    char temp_couleur_depart8 = plateau[entree3_9->start[0]][entree3_9->start[1]]->couleur;
    char temp_couleur_arrive8 = plateau[entree3_9->end[0]][entree3_9->end[1]]->couleur;
    int nb_e4 = nb_ennemi(entree3_9->end,plateau,DROITE,1,3); 

    if (check(entree3_9,plateau,0,true) == true && plateau[entree3_9->end[0]][entree3_9->end[1]+nb_e4]->couleur == temp_couleur_arrive8 && plateau[entree3_9->end[0]][entree3_9->end[1]]->couleur == temp_couleur_depart8 && plateau[entree3_9->start[0]][entree3_9->start[1]]->couleur == VIDE)
        test_reussi+=1;
    else {
        printf ("Erreur : Poussé horizontal vers la droite avec au moin 1 et au plus 3 ennemi");
        return 1;
    }   
    

    // --------------------------- Test déplcement horizontal en bloc ------------------------------ //
  

    // ----- Vers le bas -----
    Deplacement entree4_0 = malloc(sizeof(Tdeplacement));
    entree4_0->start[0]=6;
    entree4_0->start[1]=4;
    entree4_0->end[0]=7;
    entree4_0->end[1]=5;

    Pion *deplacements1[2][2];

    int couleurs1[3] = {0,0,0};
    int nb_pions1 = 0;
    for(int i=6;i<=7;i++){
        for(int j=4;j<=5;j++){
            deplacements1[i-6][j-4] = plateau[i][j];
            couleurs1[plateau[i][j]->couleur]++;
            nb_pions1++;
        }
    }

    char temp_couleur_depart9_1 = deplacements1[0][0]->couleur;
    char temp_couleur_arrive9_1 = deplacements1[1][0]->couleur;   
    char temp_couleur_depart9_2 = deplacements1[0][1]->couleur;
    char temp_couleur_arrive9_2 = deplacements1[1][1]->couleur;   
    
    if (check(entree4_0,plateau,0,true) == true && deplacements1[0][0]->couleur == deplacements1[0][1]->couleur && deplacements1[0][0]->couleur == temp_couleur_arrive9_1 && deplacements1[0][1]->couleur == temp_couleur_arrive9_2 && deplacements1[1][1]->couleur == temp_couleur_depart9_2 && deplacements1[1][0]->couleur == temp_couleur_depart9_1)
        test_reussi+=1;
    else {
        printf ("Erreur : Poussé horizontal en bloc de 2 vers le bas");
        return 1;
    }   
 
    // ----- Vers le haut -----

    Deplacement entree4_1 = malloc(sizeof(Tdeplacement));
    entree4_1->start[0]=7;
    entree4_1->start[1]=4;
    entree4_1->end[0]=6;
    entree4_1->end[1]=5;

    Pion *deplacements2[2][2];

    int couleurs2[3] = {0,0,0};
    int nb_pions2 = 0;
    for(int i=6;i<=7;i++){
        for(int j=4;j<=5;j++){
            deplacements2[i-6][j-4] = plateau[i][j];
            couleurs2[plateau[i][j]->couleur]++;
            nb_pions2++;
        }
    }

    char temp_couleur_depart10_1 = deplacements2[0][0]->couleur;
    char temp_couleur_arrive10_1 = deplacements2[1][0]->couleur;   
    char temp_couleur_depart10_2 = deplacements2[0][1]->couleur;
    char temp_couleur_arrive10_2 = deplacements2[1][1]->couleur;   
    
    if (check(entree4_1,plateau,0,true) == true && deplacements2[1][0]->couleur == deplacements2[1][1]->couleur && deplacements2[0][0]->couleur == temp_couleur_arrive10_1 && deplacements2[0][1]->couleur == temp_couleur_arrive10_2 && deplacements2[1][1]->couleur == temp_couleur_depart10_2 && deplacements2[1][0]->couleur == temp_couleur_depart10_1)
        test_reussi+=1;
    else {
        printf ("Erreur : Poussé horizontal en bloc de 2 vers le haut");
        return 1;
    }   
   
    // --------------------------- Test déplcement vertical en bloc ------------------------------ //
    // ----- Vers la droite -----

    Deplacement entree4_2 = malloc(sizeof(Tdeplacement));
    entree4_2->start[0]=4;
    entree4_2->start[1]=2;
    entree4_2->end[0]=3;
    entree4_2->end[1]=3;

    Pion *deplacements3[2][2];

    int couleurs3[3] = {0,0,0};
    int nb_pions3 = 0;
    for(int i=3;i<=4;i++){
        for(int j=2;j<=3;j++){
            deplacements3[i-3][j-2] = plateau[i][j];
            couleurs3[plateau[i][j]->couleur]++;
            nb_pions3++;
        }
    }

    char temp_couleur_depart11_1 = deplacements3[0][0]->couleur;
    char temp_couleur_arrive11_1 = deplacements3[1][0]->couleur;  
    char temp_couleur_depart11_2 = deplacements3[0][1]->couleur;
    char temp_couleur_arrive11_2 = deplacements3[1][1]->couleur; 
    
    if (check(entree4_2,plateau,0,true) == true && deplacements3[0][0]->couleur == deplacements3[1][0]->couleur && deplacements3[0][0]->couleur == temp_couleur_depart11_2 && deplacements3[1][0]->couleur == temp_couleur_arrive11_2 && deplacements3[1][1]->couleur == temp_couleur_arrive11_1 && deplacements3[0][1]->couleur == temp_couleur_depart11_1)
        test_reussi+=1;
    else {
        printf ("Erreur : Poussé horizontal en bloc de 2 vers la droite");
        return 1;
    }   
   

    // ----- Vers la gauche -----

    Deplacement entree4_3 = malloc(sizeof(Tdeplacement));
    entree4_3->start[0]=3;
    entree4_3->start[1]=3;
    entree4_3->end[0]=4;
    entree4_3->end[1]=2;

    Pion *deplacements4[2][2];

    int couleurs4[3] = {0,0,0};
    int nb_pions4 = 0;
    for(int i=3;i<=4;i++){
        for(int j=2;j<=3;j++){
            deplacements4[i-3][j-2] = plateau[i][j];
            couleurs4[plateau[i][j]->couleur]++;
            nb_pions4++;
        }
    }

    char temp_couleur_depart12_1 = deplacements4[0][0]->couleur;
    char temp_couleur_arrive12_1 = deplacements4[1][0]->couleur;  
    char temp_couleur_depart12_2 = deplacements4[0][1]->couleur;
    char temp_couleur_arrive12_2 = deplacements4[1][1]->couleur; 
    
    if (check(entree4_3,plateau,0,true) == true && deplacements4[0][1]->couleur == deplacements4[1][1]->couleur && deplacements4[1][1]->couleur == temp_couleur_arrive12_1 && deplacements4[0][0]->couleur == temp_couleur_depart12_2 && deplacements4[0][1]->couleur == temp_couleur_depart12_1 && deplacements4[1][0]->couleur == temp_couleur_arrive12_2)
        test_reussi+=1;
    else {
        printf ("Erreur : Poussé horizontal en bloc de 2 vers la gauche");
        return 1;
    }   
  
    
    // ------------------------------- Test déplcement vertical vers le haut --------------------------------- //

  
    // ----- Vers la droite -----

    Deplacement entree5_0 = malloc(sizeof(Tdeplacement));
    entree5_0->start[0]=3;
    entree5_0->start[1]=2;
    entree5_0->end[0]=5;
    entree5_0->end[1]=3;

    Pion *deplacements5[3][2];

    int couleurs5[3] = {0,0,0};
    int nb_pions5 = 0;
    for(int i=3;i<=5;i++){
        for(int j=2;j<=3;j++){
            deplacements5[i-3][j-2] = plateau[i][j];
            couleurs5[plateau[i][j]->couleur]++;
            nb_pions5++;
        }
    }

    char temp_couleur_depart13_1 = deplacements5[0][0]->couleur;
    char temp_couleur_arrive13_1 = deplacements5[0][1]->couleur;  
    char temp_couleur_depart13_2 = deplacements5[1][0]->couleur;
    char temp_couleur_arrive13_2 = deplacements5[1][1]->couleur; 
    char temp_couleur_depart13_3 = deplacements5[2][0]->couleur;
    char temp_couleur_arrive13_3 = deplacements5[2][1]->couleur; 

    if (check(entree5_0,plateau,0,true) == true && deplacements5[0][0]->couleur == deplacements5[1][0]->couleur && deplacements5[2][0]->couleur == deplacements5[0][0]->couleur && deplacements5[0][0]->couleur == temp_couleur_arrive13_1 && deplacements5[0][1]->couleur == temp_couleur_depart13_1 && deplacements5[1][0]->couleur == temp_couleur_arrive13_2 && deplacements5[1][1]->couleur == temp_couleur_depart13_2 && deplacements5[2][0]->couleur == temp_couleur_arrive13_3 && deplacements5[2][1]->couleur == temp_couleur_depart13_3)
        test_reussi+=1;
    else {
        printf ("Erreur : Poussé horizontal en bloc de 3 vers la droite");
        return 1;
    }   
    
    
    // ----- Vers la gauche -----

    Deplacement entree5_1 = malloc(sizeof(Tdeplacement));
    entree5_1->start[0]=3;
    entree5_1->start[1]=3;
    entree5_1->end[0]=5;
    entree5_1->end[1]=2;

    Pion *deplacements6[3][2];

    int couleurs6[3] = {0,0,0};
    int nb_pions6 = 0;
    for(int i=3;i<=5;i++){
        for(int j=2;j<=3;j++){
            deplacements6[i-3][j-2] = plateau[i][j];
            couleurs6[plateau[i][j]->couleur]++;
            nb_pions6++;
        }
    }

    char temp_couleur_depart14_1 = deplacements6[0][0]->couleur;
    char temp_couleur_arrive14_1 = deplacements6[0][1]->couleur;  
    char temp_couleur_depart14_2 = deplacements6[1][0]->couleur;
    char temp_couleur_arrive14_2 = deplacements6[1][1]->couleur; 
    char temp_couleur_depart14_3 = deplacements6[2][0]->couleur;
    char temp_couleur_arrive14_3 = deplacements6[2][1]->couleur; 

    if (check(entree5_1,plateau,0,true) == true && deplacements6[0][1]->couleur == deplacements6[1][1]->couleur && deplacements6[2][1]->couleur == deplacements6[0][1]->couleur && deplacements6[0][0]->couleur == temp_couleur_arrive14_1 && deplacements6[0][1]->couleur == temp_couleur_depart14_1 && deplacements6[1][0]->couleur == temp_couleur_arrive14_2 && deplacements6[1][1]->couleur == temp_couleur_depart14_2 && deplacements6[2][0]->couleur == temp_couleur_arrive14_3 && deplacements6[2][1]->couleur == temp_couleur_depart14_3)
        test_reussi+=1;
    else {
        printf ("Erreur : Poussé horizontal en bloc de 3 vers la gauche");
        return 1;
    }   
  

    // ----- Vers le haut -----

    Deplacement entree5_2 = malloc(sizeof(Tdeplacement));
    entree5_2->start[0]=6;
    entree5_2->start[1]=3;
    entree5_2->end[0]=5;
    entree5_2->end[1]=5;

    Pion *deplacements7[2][3];

    int couleurs7[3] = {0,0,0};
    int nb_pions7 = 0;
    for(int i=5;i<=6;i++){
        for(int j=3;j<=5;j++){
            deplacements7[i-5][j-3] = plateau[i][j];
            couleurs7[plateau[i][j]->couleur]++;
            nb_pions7++;
        }
    }

    char temp_couleur_depart15_1 = deplacements7[1][0]->couleur;
    char temp_couleur_depart15_2 = deplacements7[1][1]->couleur;
    char temp_couleur_depart15_3 = deplacements7[1][2]->couleur;
    char temp_couleur_arrive15_1 = deplacements7[0][0]->couleur;  
    char temp_couleur_arrive15_2 = deplacements7[0][1]->couleur; 
    char temp_couleur_arrive15_3 = deplacements7[0][2]->couleur; 

    if (check(entree5_2,plateau,0,true) == true && deplacements7[1][0]->couleur == deplacements7[1][1]->couleur && deplacements7[1][0]->couleur == deplacements7[1][2]->couleur && deplacements7[0][0]->couleur == temp_couleur_depart15_1 && deplacements7[1][0]->couleur == temp_couleur_arrive15_1 && deplacements7[0][1]->couleur == temp_couleur_depart15_2 && deplacements7[1][1]->couleur == temp_couleur_arrive15_2 && deplacements7[0][2]->couleur == temp_couleur_depart15_3 && deplacements7[1][2]->couleur == temp_couleur_arrive15_3)
        test_reussi+=1;
    else {
        printf ("Erreur : Poussé horizontal en bloc de 3 vers le haut");
        return 1;
    }   
  
    // ----- Vers le bas -----

    Deplacement entree5_3 = malloc(sizeof(Tdeplacement));
    entree5_3->start[0]=5;
    entree5_3->start[1]=3;
    entree5_3->end[0]=6;
    entree5_3->end[1]=5;

    Pion *deplacements8[2][3];

    int couleurs8[3] = {0,0,0};
    int nb_pions8 = 0;
    for(int i=5;i<=6;i++){
        for(int j=3;j<=5;j++){
            deplacements8[i-5][j-3] = plateau[i][j];
            couleurs8[plateau[i][j]->couleur]++;
            nb_pions8++;
        }
    }

    char temp_couleur_depart16_1 = deplacements8[1][0]->couleur;
    char temp_couleur_depart16_2 = deplacements8[1][1]->couleur;
    char temp_couleur_depart16_3 = deplacements8[1][2]->couleur;
    char temp_couleur_arrive16_1 = deplacements8[0][0]->couleur;  
    char temp_couleur_arrive16_2 = deplacements8[0][1]->couleur; 
    char temp_couleur_arrive16_3 = deplacements8[0][2]->couleur; 

    if (check(entree5_3,plateau,0,true) == true && deplacements8[0][0]->couleur == deplacements8[0][1]->couleur && deplacements8[0][0]->couleur == deplacements8[0][2]->couleur && deplacements8[0][0]->couleur == temp_couleur_depart16_1 && deplacements8[1][0]->couleur == temp_couleur_arrive16_1 && deplacements8[0][1]->couleur == temp_couleur_depart16_2 && deplacements8[1][1]->couleur == temp_couleur_arrive16_2 && deplacements8[0][2]->couleur == temp_couleur_depart16_3 && deplacements8[1][2]->couleur == temp_couleur_arrive16_3)
        test_reussi+=1;
    else {
        printf ("Erreur : Poussé horizontal en bloc de 3 vers le bas");
        return 1;
    }   
   
    
    // ----------------------- ANNEXE -----------------------
    // ----- Vers le bas avec un enemie dans la matrice de déplacement -----
    Deplacement entree4_4 = malloc(sizeof(Tdeplacement));
    entree4_4->start[0]=6;
    entree4_4->start[1]=4;
    entree4_4->end[0]=7;
    entree4_4->end[1]=5;

    plateau[7][4]=init_Pion(NOIR,7,4);

    Pion *deplacements10[2][2];

    int couleurs10[3] = {0,0,0};
    int nb_pions10 = 0;
    for(int i=6;i<=7;i++){
        for(int j=4;j<=5;j++){
            deplacements10[i-6][j-4] = plateau[i][j];
            couleurs10[plateau[i][j]->couleur]++;
            nb_pions10++;
        }
    }  
    
    if (check(entree4_4,plateau,0,true) == false && couleurs10[0] == 2 && couleurs10[1] == 1 && couleurs10[2] == 1)
        test_reussi+=1;
    else {
        printf ("Erreur : Poussé horizontal en bloc de 2 vers le bas avec un enemie dans la matrice de déplacement");
        return 1;
    }   
  
    
    // ----- Vers la droite -----

    Deplacement entree5_5 = malloc(sizeof(Tdeplacement));
    entree5_5->start[0]=2;
    entree5_5->start[1]=2;
    entree5_5->end[0]=4;
    entree5_5->end[1]=3;

    Pion *deplacements11[3][2];

    int couleurs11[3] = {0,0,0};
    int nb_pions11 = 0;
    for(int i=2;i<=4;i++){
        for(int j=2;j<=3;j++){
            deplacements11[i-2][j-2] = plateau[i][j];
            couleurs11[plateau[i][j]->couleur]++;
            nb_pions11++;
        }
    }

    if (check(entree5_5,plateau,0,true) == false && couleurs11[0] == 4 && couleurs11[2] == 2)
        test_reussi+=1;
    else {
        printf ("Erreur : Poussé horizontal en bloc de 3 vers la droite");
        return 1;
    }   
  

    // ----- Vers la gauche -----

    Deplacement entree5_6 = malloc(sizeof(Tdeplacement));
    entree5_6->start[0]=2;
    entree5_6->start[1]=2;
    entree5_6->end[0]=4;
    entree5_6->end[1]=3;

    Pion *deplacements12[3][2];

    int couleurs12[3] = {0,0,0};
    int nb_pions12 = 0;
    for(int i=2;i<=4;i++){
        for(int j=1;j<=2;j++){
            deplacements12[i-2][j-1] = plateau[i][j];
            couleurs12[plateau[i][j]->couleur]++;
            nb_pions12++;
        }
    }

    if (check(entree5_6,plateau,0,true) == false && couleurs12[0] == 3 && couleurs12[1] == 2 && couleurs12[2] == 1)
        test_reussi+=1;
    else {
        printf ("Erreur : Poussé horizontal en bloc de 3 vers la gauche");
        return 1;
    }   
   

    // ----- Vers le bas -----

    Deplacement entree5_7 = malloc(sizeof(Tdeplacement));
    entree5_7->start[0]=5;
    entree5_7->start[1]=0;
    entree5_7->end[0]=6;
    entree5_7->end[1]=2;

    Pion *deplacements13[2][3];

    int couleurs13[3] = {0,0,0};
    int nb_pions13 = 0;
    for(int i=5;i<=6;i++){
        for(int j=0;j<=2;j++){
            deplacements13[i-5][j-0] = plateau[i][j];
            couleurs13[plateau[i][j]->couleur]++;
            nb_pions13++;
        }
    }

    if (check(entree5_7,plateau,0,true) == false && couleurs13[0] == 4 && couleurs13[1] == 1 && couleurs13[2] == 1 )
        test_reussi+=1;
    else {
        printf ("Erreur : Poussé horizontal en bloc de 3 vers le bas");
        return 1;
    }   
   
    // ----- Vers le haut -----

    Deplacement entree5_8 = malloc(sizeof(Tdeplacement));
    entree5_8->start[0]=5;
    entree5_8->start[1]=0;
    entree5_8->end[0]=4;
    entree5_8->end[1]=2;

    Pion *deplacements14[2][3];

    int couleurs14[3] = {0,0,0};
    int nb_pions14 = 0;
    for(int i=4;i<=5;i++){
        for(int j=0;j<=2;j++){
            deplacements14[i-4][j-0] = plateau[i][j];
            couleurs14[plateau[i][j]->couleur]++;
            nb_pions14++;
        }
    }

    if (check(entree5_8,plateau,0,true) == false && couleurs14[0] == 5 && couleurs14[1] == 1 && couleurs14[2] == 0 )
        test_reussi+=1;
    else {
        printf ("Erreur : Poussé horizontal en bloc de 3 vers le haut");
        return 1;
    }   
   

    // ----- delta y == 3 -----

    Deplacement entree5_9 = malloc(sizeof(Tdeplacement));
    entree5_9->start[0]=5;
    entree5_9->start[1]=2;
    entree5_9->end[0]=4;
    entree5_9->end[1]=5;

    if (check(entree5_9,plateau,0,true) == false)
        test_reussi+=1;
    else {
        printf ("Erreur : Poussé horizontal en bloc de 3 avec delta y diferent de 1 et 2");
        return 1;
    }   
  
    // ----- Avec nb_mate < nb_ennemie -----
    Deplacement entree6_0 = malloc(sizeof(Tdeplacement));
    entree6_0->start[0]=7;
    entree6_0->start[1]=0;
    entree6_0->end[0]=4;
    entree6_0->end[1]=0;

    Pion *deplacements15[4][1];

    int couleurs15[3] = {0,0,0};
    int nb_pions15 = 0;
    for(int i=4;i<=7;i++){
        for(int j=0;j<=0;j++){
            deplacements15[i - 4][j - 0] = plateau[i][j];
            couleurs15[plateau[i][j]->couleur]++;
            nb_pions15++;
        }
    }

    if (check(entree6_0,plateau,1,true) == false && couleurs15[1] <= couleurs15[2%2])
        test_reussi+=1;
    else {
        printf ("Erreur : Deplacement horizontal vers le haut avec nb_mate < nb_ennemie");
        return 1;
    }
  

    // ----- Avec nb_mate < nb_ennemie -----
    Deplacement entree6_1 = malloc(sizeof(Tdeplacement));
    entree6_1->start[0]=2;
    entree6_1->start[1]=1;
    entree6_1->end[0]=2;
    entree6_1->end[1]=3;

    Pion *deplacements16[1][3];

    int couleurs16[3] = {0,0,0};
    int nb_pions16 = 0;
    for(int i=2;i<=2;i++){
        for(int j=1;j<=3;j++){
            deplacements16[i - 2][j - 1] = plateau[i][j];
            couleurs16[plateau[i][j]->couleur]++;
            nb_pions16++;
        }
    }

    if (check(entree6_1,plateau,1,true) == false && couleurs16[1] <= couleurs16[2%2])
        test_reussi+=1;
    else {
        printf ("Erreur : Deplacement horizontal vers la droite haut avec nb_mate < nb_ennemie");
        return 1;
    }
    if (test_reussi == 40){
        printf ("test_check reussi\n\n");
        return 0;
    }
    
    else{ 
        printf ("Test déplacement horizontal vers la droite avec nb_mate < nb_ennemie : Déféctueux\n");
        return 1;
    }
 
}



void test_all_regles_function(int* run,int* failures){
       run_test(test_abs(),run,failures);
       run_test(test_min(),run,failures);
       run_test(test_max(),run,failures);
       run_test(test_echange_couleur(),run,failures);
       run_test(test_nb_ennemi(),run,failures);
	   run_test(test_check(),run,failures);
}
				

			


 	
 	