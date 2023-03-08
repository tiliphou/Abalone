
#include "regles.h"




int abs(int x){
    if(x>=0) return x;
    else return -x;
}

int min(int x,int y){
    if(x<=y) return x;
    else return y;
}

int max(int x,int y){
    if(x>=y) return x;
    else return y;
}

void echange_couleur(Pion *p1,Pion *p2){

    char tempcolor = p1->couleur;
    p1->couleur = p2->couleur;
    p2->couleur = tempcolor;

}

int check_win(Pion* plateau[8][8]){//we check if a white or black pawn is missing
	int nb_pion_blanc=0;
	int nb_pion_noir=0;
	for (int j=0;j<8;j++){
		for (int i=0;i<8;i++){
			if (plateau[i][j]->couleur==BLANC){
			nb_pion_blanc+=1;
			}
			if (plateau[i][j]->couleur==NOIR){
			nb_pion_noir+=1;
			}
		}
	}
	if (nb_pion_blanc!=14||nb_pion_noir!=14)
		return 1;
	else
		return 0;
}

bool check(Deplacement entree,Pion *plateau[8][8],int TOUR, bool deplacer){

    // entree->start = case_depart = (x_d,y_d) entree->end = case_arrivee = (x_a,y_a)

    int delta_x = abs(entree->start[0]-entree->end[0]);
    int delta_y = abs(entree->start[1]-entree->end[1]);
    int min_x = min(entree->start[0],entree->end[0]);
    int max_x = max(entree->start[0],entree->end[0]);
    int min_y = min(entree->start[1],entree->end[1]);
    int max_y = max(entree->start[1],entree->end[1]);

    char direction;

    // Generation de la matrice des cases concernee par les deplacements
    Pion *deplacements[delta_x+1][delta_y+1];

    if(plateau[entree->start[0]][entree->start[1]]->couleur != TOUR)
        return false;

    int couleurs[3] = {0,0,0};
    int nb_pions = 0;
    for(int i=min_x;i<=max_x;i++){
        for(int j=min_y;j<=max_y;j++){
            deplacements[i - min_x][j - min_y] = plateau[i][j];
            couleurs[plateau[i][j]->couleur]++;
            nb_pions++;
        }
    }

    // L'arrivee = le depart => pas de mouvement ! (ou on prend trop de pions)
    if((delta_x == 0 && delta_y == 0) || delta_x>=4 || delta_y>=4)
        return false;
        
    // Cas alignes
    if(delta_y == 0){
        /* Deplacement vertical aligne */
        if(couleurs[TOUR] <= couleurs[(TOUR+1)%2])
            return false;
        if((entree->start[0]-entree->end[0] + entree->start[1]-entree->end[1]) < 0) // signe correct ??
            direction = BAS;
        else direction = HAUT;
        int nb_a = couleurs[TOUR];
        int nb_e = nb_ennemi(entree->end,plateau,direction,1,nb_a);
        // On check la couleur d'arrivee
        if(plateau[entree->end[0]][entree->end[1]]->couleur == (TOUR+1)%2){
            /* Pousse : car la case d'arrivee est un ennemi */
            if(nb_e == -1) return false;
            if(nb_e >= nb_a) return false;
            if(nb_e == -2) {
                echange_couleur(plateau[entree->start[0]][entree->start[1]],plateau[entree->end[0]][entree->end[1]]);
                plateau[entree->start[0]][entree->start[1]]->couleur = VIDE;
                return true; // Ejection d'une bille !
            }
            else{
                if(deplacer==true){
                    if(direction == BAS)
                        echange_couleur(plateau[entree->end[0]][entree->end[1]],plateau[entree->end[0]+nb_e][entree->end[1]]);
                    else if(direction == HAUT)
                        echange_couleur(plateau[entree->end[0]][entree->end[1]],plateau[entree->end[0]-nb_e][entree->end[1]]);
                    echange_couleur(plateau[entree->start[0]][entree->start[1]],plateau[entree->end[0]][entree->end[1]]);
                }
                return true;
            } 
            
        }
        else if (plateau[entree->end[0]][entree->end[1]]->couleur == TOUR){
            /* Un allie : bloque */
            return false;
        }
        else{
            /* La case est vide */
            if(nb_a == nb_pions-1 && nb_a <=3){
                if(deplacer==true)
                    echange_couleur(plateau[entree->start[0]][entree->start[1]],plateau[entree->end[0]][entree->end[1]]);
                return true;
                }
            return false;
        }
    }
    else if(delta_x == 0){
        /* Deplacement horizontal aligne */
        if(couleurs[TOUR] <= couleurs[(TOUR+1)%2])
            return false;
        if((entree->start[0]-entree->end[0] + entree->start[1]-entree->end[1]) < 0) // signe correct ??
            direction = DROITE;
        else direction = GAUCHE;

        int nb_a = couleurs[TOUR];
        int nb_e = nb_ennemi(entree->end,plateau,direction,1,nb_a);
        if(plateau[entree->end[0]][entree->end[1]]->couleur == (TOUR+1)%2){
            /* Pousse */
            if(nb_e == -1) return false;
            if(nb_e >= nb_a) return false;
            if(nb_e == -2) {
                echange_couleur(plateau[entree->start[0]][entree->start[1]],plateau[entree->end[0]][entree->end[1]]);
                plateau[entree->start[0]][entree->start[1]]->couleur = VIDE;
                return true; // Ejection d'une bille !
            } 
            else{
                if(deplacer==true){
                    if(direction == DROITE)
                        echange_couleur(plateau[entree->end[0]][entree->end[1]],plateau[entree->end[0]][entree->end[1]+nb_e]);
                    else if(direction == GAUCHE)
                        echange_couleur(plateau[entree->end[0]][entree->end[1]],plateau[entree->end[0]][entree->end[1]-nb_e]);
                    echange_couleur(plateau[entree->start[0]][entree->start[1]],plateau[entree->end[0]][entree->end[1]]);
                }
                return true;
            }
        }
        else if (plateau[entree->end[0]][entree->end[1]]->couleur == TOUR){
            /* Un allie : bloque */
            return false;
        }
        else{
            /* La case est vide */
            if(nb_a == nb_pions-1 && nb_a <=3){
                if(deplacer==true)
                    echange_couleur(plateau[entree->start[0]][entree->start[1]],plateau[entree->end[0]][entree->end[1]]);
                return true;
            }
                
            return false;
        }
    }

    // Cas block
    else{
        if(delta_x == 1 && delta_y == 1){
            /* Bloc 2x2 */
            if(!(couleurs[TOUR] == 2 && couleurs[2] == 2))
                return false;

            // Horizontal vers le bas
            if(deplacements[0][0]->couleur == deplacements[0][1]->couleur) {
                direction = BAS;
                if(deplacer==true){
                    echange_couleur(deplacements[0][0],deplacements[1][0]);
                    echange_couleur(deplacements[0][1],deplacements[1][1]);
                }
                return true;
            }
            // Horizontal vers le haut
            else if (deplacements[1][0]->couleur == deplacements[1][1]->couleur){
                direction = HAUT;
                if(deplacer==true){
                    echange_couleur(deplacements[1][0],deplacements[0][0]);
                    echange_couleur(deplacements[1][1],deplacements[0][1]);
                }
                return true;
            }
            // Vertical vers la gauche
            else if(deplacements[1][0]->couleur == deplacements[1][1]->couleur){
                direction = GAUCHE;
                if(deplacer==true){
                    echange_couleur(deplacements[1][0],deplacements[0][0]);
                    echange_couleur(deplacements[1][1],deplacements[0][1]);
                }
                return true;
            }

            // Vertical vers la droite
            else if (deplacements[0][0]->couleur == deplacements[1][0]->couleur){
                direction = DROITE;
                if(deplacer==true){
                    echange_couleur(deplacements[0][0],deplacements[0][1]);
                    echange_couleur(deplacements[1][0],deplacements[1][1]);
                }
                return true;
            }


        }
        else if(max(delta_x,delta_y) == 2){
            int lg_bloc_alliee = 0;
            int lg_bloc_ennemi = 0;
            /* Bloc 3x2 */
            if(delta_x < delta_y) {
                // Bloc horizontal
                if((entree->start[0]-entree->end[0]) < 0){ // signe correct ??
                    direction = BAS;
                    for (int j = 0; j < 3; j++){
                        if(deplacements[0][j]->couleur == TOUR)
                            lg_bloc_alliee++;
                        if(deplacements[1][j]->couleur == VIDE)
                            lg_bloc_ennemi++;
                    }
                    if (lg_bloc_alliee==3 && lg_bloc_ennemi==3){
                        if(deplacer==true){
                            echange_couleur(deplacements[0][0],deplacements[1][0]);
                            echange_couleur(deplacements[0][1],deplacements[1][1]);
                            echange_couleur(deplacements[0][2],deplacements[1][2]);
                        }
                        return true;
                    }
                    return false;
                }
                else {
                    direction = HAUT;
                    for (int j = 0; j < 3; j++){
                        if(deplacements[1][j]->couleur == TOUR)
                            lg_bloc_alliee++;
                        if(deplacements[0][j]->couleur == VIDE)
                            lg_bloc_ennemi++;
                    }
                    if (lg_bloc_alliee==3 && lg_bloc_ennemi==3){
                        if(deplacer==true){
                            echange_couleur(deplacements[1][0],deplacements[0][0]);
                            echange_couleur(deplacements[1][1],deplacements[0][1]);
                            echange_couleur(deplacements[1][2],deplacements[0][2]);
                        }
                        return true;
                    }
                    return false;
                }
            }
            else {
                // Bloc vertical
                if((entree->start[1]-entree->end[1]) < 0){ // signe correct ??
                    direction = DROITE;
                    for (int i = 0; i < 3; i++){
                        if(deplacements[i][0]->couleur == TOUR)
                            lg_bloc_alliee++;
                        if(deplacements[i][1]->couleur == VIDE)
                            lg_bloc_ennemi++;
                    }
                    if (lg_bloc_alliee==3 && lg_bloc_ennemi==3){
                        if(deplacer==true){
                            echange_couleur(deplacements[0][0],deplacements[0][1]);
                            echange_couleur(deplacements[1][0],deplacements[1][1]);
                            echange_couleur(deplacements[2][0],deplacements[2][1]);
                        }
                        return true;
                    }
                    return false;
                }
                else {
                    direction = GAUCHE;
                    for (int i = 0; i < 3; i++){
                        if(deplacements[i][1]->couleur == TOUR)
                            lg_bloc_alliee++;
                        if(deplacements[i][0]->couleur == VIDE)
                            lg_bloc_ennemi++;
                    }
                    if (lg_bloc_alliee==3 && lg_bloc_ennemi==3){
                        if(deplacer==true){
                            echange_couleur(deplacements[0][1],deplacements[0][0]);
                            echange_couleur(deplacements[1][1],deplacements[1][0]);
                            echange_couleur(deplacements[2][1],deplacements[2][0]);
                        }
                        return true;
                    }
                    return false;
                }

                }

            }
        else return false;
    }
    return false;
}

int nb_ennemi(char entree[2], Pion* plateau[8][8], int direction, int nb_pion_ennemi, int nb_pion_allie){
    //cette fonction sert à compter le nombre de pions ennemis que l'on veut pousser.
    //nb correspond au nombre de pion ennemi. Quand la fonction sera appelée il faudra toujours que nb=1, nb est dans les paramètres seulement pour permettre à la fonction d'être recursive

	if (direction==HAUT){
		if (entree[0]-1<0 || entree[0]-1>=8){  //On regarde si la prochaine case en haut n'est pas dans le plateau
			if (nb_pion_allie<=nb_pion_ennemi) return -1; //si la case n'est pas dans le plateau on regarde si la pousse est possible ou non
			else return -2;
		}
        
		else {
			if (plateau[entree[0]][entree[1]]->couleur==plateau[entree[0]-1][entree[1]]->couleur){
				nb_pion_ennemi+=1;
				char new_entry[2];
				new_entry[0]=entree[0]-1;
				new_entry[1]=entree[1];
                return nb_ennemi(new_entry, plateau, HAUT, nb_pion_ennemi,nb_pion_allie);
			}
            if ((plateau[entree[0]][entree[1]]->couleur == PION_NOIR &&
                 plateau[entree[0] - 1][entree[1]]->couleur == PION_BLANC) ||
                (plateau[entree[0]][entree[1]]->couleur == PION_BLANC &&
                 plateau[entree[0] - 1][entree[1]]->couleur == PION_NOIR))
                return -1;
            else return nb_pion_ennemi;
		}
	}
	if(direction==GAUCHE){
		if (entree[1]-1<0 || entree[1]-1>=8){
			if(nb_pion_allie<=nb_pion_ennemi) return -1;
			else return -2;
         	}
		else{	
			if (plateau[entree[0]][entree[1]]->couleur==plateau[entree[0]][entree[1]-1]->couleur){
				nb_pion_ennemi+=1;
				char new_entry[2];
				new_entry[0]=entree[0];
				new_entry[1]=entree[1]-1;
                return nb_ennemi(new_entry, plateau, GAUCHE, nb_pion_ennemi,nb_pion_allie);
            }
            if ((plateau[entree[0]][entree[1]]->couleur == PION_NOIR &&
                 plateau[entree[0]][entree[1] - 1]->couleur == PION_BLANC) ||
                (plateau[entree[0]][entree[1]]->couleur == PION_BLANC &&
                 plateau[entree[0]][entree[1] - 1]->couleur == PION_NOIR))
                return -1;
            else return nb_pion_ennemi;
		}
	}
	if(direction==DROITE){
		if (entree[1]+1<0 || entree[1]+1>=8){
			if(nb_pion_allie<=nb_pion_ennemi) return -1 ;
			else return -2;
		}
		else{	
			if (plateau[entree[0]][entree[1]]->couleur==plateau[entree[0]][entree[1]+1]->couleur){
				nb_pion_ennemi+=1;
				char new_entry[2];
				new_entry[0]=entree[0];
				new_entry[1]=entree[1]+1;
                return nb_ennemi(new_entry, plateau, DROITE, nb_pion_ennemi,nb_pion_allie);
			}
            if ((plateau[entree[0]][entree[1]]->couleur == PION_NOIR &&
                 plateau[entree[0]][entree[1] + 1]->couleur == PION_BLANC) ||
                (plateau[entree[0]][entree[1]]->couleur == PION_BLANC &&
                 plateau[entree[0]][entree[1] + 1]->couleur == PION_NOIR))
                return -1;
            else return nb_pion_ennemi;
		}
	}
	if(direction==BAS){
		if (entree[0]+1<0 || entree[0]+1>=8){
			if(nb_pion_allie<=nb_pion_ennemi) return -1;
			else return -2;
		}
		else{
			if (plateau[entree[0]][entree[1]]->couleur==plateau[entree[0]+1][entree[1]]->couleur){
				nb_pion_ennemi+=1;
				char new_entry[2];
				new_entry[0]=entree[0]+1;
				new_entry[1]=entree[1];
				return nb_ennemi(new_entry, plateau, BAS, nb_pion_ennemi,nb_pion_allie);
			}
            if ((plateau[entree[0]][entree[1]]->couleur == PION_NOIR &&
                 plateau[entree[0] + 1][entree[1]]->couleur == PION_BLANC) ||
                (plateau[entree[0]][entree[1]]->couleur == PION_BLANC &&
                 plateau[entree[0] + 1][entree[1]]->couleur == PION_NOIR)){
                return -1;
            }

            else return nb_pion_ennemi;
		}
	}
    return 0;
}

/*
int main(int argc,char** argv){
    return 0
}*/