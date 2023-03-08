
#include"plateau.h"

Pion *init_Pion(char couleur,int posx,int posy){
    Pion *p=malloc(sizeof(Pion));
    p->couleur = couleur;
    p->pos_x = posx;
    p->pos_y = posy;

    return p;
}

void init(Pion *plateau[8][8]){
	short i,j;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if (i==0 || (i==1 && 0<j && j<7))
                plateau[i][j] = init_Pion(BLANC,i,j);

            else if(i==7 || (i==6 && 0<j && j<7))
                plateau[i][j] = init_Pion(NOIR,i,j);

            else
                plateau[i][j] = init_Pion(VIDE,i,j);

        }
    }
}

void display(Pion *plateau[8][8]){
	char COULEURS[3] = {PION_BLANC,PION_NOIR,PION_VIDE};
	int i,j;
	int character= 65;
	printf("  ");
	for(i=1;i<=8;i++){
		printf("  %d ", i);
	}
	printf("\n");
	for(i=0;i<8;i++){
		printf("%c |", (char)character);
		for(j=0;j<8;j++){
			printf(" %c ",COULEURS[plateau[i][j]->couleur]);
			printf("|");
		}
		printf("\n");
		character++;
	}
}