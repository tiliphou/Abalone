#include "ia.h"


int dir[4][4] = {{0, -1, 1, 0}, {-1, 0, 0, 1}, {0, 1, 1, 0}, {1, 0, 0, 1}};
int moveValue[10] = {10000000, //coup victorieux
                    70000,    //attaque possible
                    -700,    //attaque possible par eni
                    400,      //position bille
                    -100,      //position bille eni
                    700,      //groupement allie
                    -200,      //groupement eni
                    -400,     //pos dangeureuse
                    2000,      //pos dangereuse eni 
                    -10000000, //coup victorieux de eni
                    };

int valPos[8][8] = {{-80,-80,-20,-20,-20,-20,-80,-80},
                    {-80, 4,  4,  4,  4,  4,  4, -80},
                    {-20, 4, 24, 24, 24, 24,  4, -20},
                    {-20, 4, 24, 64, 64, 24,  4, -20},
                    {-20, 4, 24, 64, 64, 24,  4, -20},
                    {-20, 4, 24, 24, 24, 24,  4, -20},
                    {-80, 4,  4,  4,  4,  4,  4, -80},
                    {-80,-80,-20,-20,-20,-20,-20,-20},
                    };

int valTest[3] = {38, 23, 37};

void copyPlateau(Pion *tableau[8][8],Pion *tempTab[8][8]){

    for (int i = 0; i<8; i++){
        for (int j = 0; j<8; j++){
            tempTab[i][j] = init_Pion(tableau[i][j]->couleur, i, j);
        }
    }
}

int value(Pion *tableau[8][8], int x, int y){
    int val;
    if (0 <= x && x < 8 && 0<=y && y<8){
        val = tableau[x][y]->couleur;
        return val;
    }
    else {
        val = HORS;
        return val;
    }
}

void mvtLateral(int dl[2], int nbr, int billes[3][2], Pion *plateau[8][8], int *nbrMvt, Deplacement listMvt[nbrDep]){
    
    int state=0;
    Position start = new_position((char)(billes[0][0]+65), (char)(billes[0][1]+49));

    for (int i=0; i<nbr; i++){
        int next = value(plateau, billes[i][0]+dl[0], billes[i][1]+dl[1]); 
        if (next==VIDE){
            state++;
        }
        if (state == nbr){
            Position endm = new_position((char)(billes[i][0]+dl[0]+65), (char)(billes[i][1]+dl[1]+49));
            Deplacement deplt = new_tab(start, endm);
            listMvt[*nbrMvt] = deplt;
            *nbrMvt = *nbrMvt + 1;
        }
    }
    
    state = 0;
    for (int i=0; i<nbr; i++){
        int next = value(plateau, billes[i][0]-dl[0], billes[i][1]-dl[1]);
        if (next==VIDE){
            state++;
        }

        if (state == nbr){
            Position endm = new_position((char)(billes[i][0]-dl[0]+65), (char)(billes[i][1]-dl[1]+49));
            Deplacement deplt = new_tab(start, endm);
            listMvt[*nbrMvt] = deplt;
            *nbrMvt = *nbrMvt + 1;
        }
    }
}

void mvtLigne(Pion *plateau[8][8], int *nbrMvt, int player, Deplacement listMvt[nbrDep]){
    Position start;
    Position endm;
    for (int i=0;i<8;i++){
        for (int j = 0; j<8; j++){
            if (plateau[i][j]->couleur == player){
                start = new_position((char)(i+65), (char)(j+49));
                for (int k=0; k<4; k++){
                    int next = value(plateau, i+dir[k][0], j+dir[k][1]);
                    if (next == VIDE){
                        endm = new_position((char)(i+dir[k][0]+65), (char)(j+dir[k][1]+49));
                        Deplacement deplt = new_tab(start, endm);
                        listMvt[*nbrMvt] = deplt;
                        *nbrMvt = *nbrMvt + 1;
                    }
                    else if (next == player)
                    {
                        int dl[2]={dir[k][2], dir[k][3]};
                        int billes[3][2]={{i, j},{i+dir[k][0], j+dir[k][1]}, {0, 0}} ;
                        mvtLateral(dl, 2, billes, plateau, nbrMvt, listMvt);
                        
                        int next2 = value(plateau, i+2*dir[k][0], j+2*dir[k][1]);
                        if (next2 == VIDE){
                            endm = new_position((char)(i+2*dir[k][0]+65), (char)(j+2*dir[k][1]+49));
                            Deplacement deplt = new_tab(start, endm);
                            listMvt[*nbrMvt] = deplt;
                            *nbrMvt = *nbrMvt + 1;
                        }

                        else if (next2 == HORS){
                        }

                        else if (next2 != player){
                            int next3 = value(plateau, i+3*dir[k][0], j+3*dir[k][1]);
                            if (next3 == VIDE || next3 == HORS){
                                endm = new_position((char)(i+2*dir[k][0]+65), (char)(j+2*dir[k][1]+49));
                                Deplacement deplt = new_tab(start, endm);
                                listMvt[*nbrMvt] = deplt;
                                *nbrMvt = *nbrMvt + 1;
                            }
                        }

                        else if (next2 == player){
                            int dl[2]={dir[k][2], dir[k][3]};
                            int billes[3][2]={{i, j},{i+dir[k][0], j+dir[k][1]}, {i+2*dir[k][0], j+2*dir[k][1]}} ;
                            mvtLateral(dl, 3, billes, plateau, nbrMvt, listMvt);

                            int next3 = value(plateau, i+3*dir[k][0], j+3*dir[k][1]);
                            if (next3 == VIDE){
                                endm = new_position((char)(i+3*dir[k][0]+65), (char)(j+3*dir[k][1]+49));
                                Deplacement deplt = new_tab(start, endm);
                                listMvt[*nbrMvt] = deplt;
                                *nbrMvt = *nbrMvt + 1;
                            }

                            else if (next3==HORS){

                            }

                            else if (next3 != player){
                                int next4 = value(plateau, i+4*dir[k][0], j+4*dir[k][1]);
                                int next5 = value(plateau, i+5*dir[k][0], j+5*dir[k][1]);
                                if (next4 == VIDE || next4 == HORS){
                                    endm = new_position((char)(i+3*dir[k][0]+65), (char)(j+3*dir[k][1]+49));
                                    Deplacement deplt = new_tab(start, endm);
                                    listMvt[*nbrMvt] = deplt;
                                    *nbrMvt = *nbrMvt +1;
                                }
                                else if (next4 != player && (next5==PION_VIDE || next5==HORS)){
                                    endm = new_position((char)(i+3*dir[k][0]+65), (char)(j+3*dir[k][1]+49));
                                    Deplacement deplt = new_tab(start, endm);
                                    listMvt[*nbrMvt] = deplt;
                                    *nbrMvt = *nbrMvt + 1;
                                }
                            }
                        }
                    }
                }
            }
            
        }
    }
}

Deplacement randomIA(Pion *plateau[8][8], int player){
    int nbrMvt=0;
    Deplacement listMvt[nbrDep]; 
    mvtLigne(plateau, &nbrMvt, player, listMvt);
    int random = rand()%nbrMvt;
    return listMvt[random];
}


int attackPoss(Pion *plateau[8][8], int joueur){
    int atk = 0;
    int eni;
    if (joueur == BLANC){
        eni = NOIR;
    }
    else{
        eni = BLANC;
    }
    for (int i = 0; i<8; i++){
        for (int j = 0; j<8; j++){
            if (plateau[i][j]->couleur == joueur){
                for (int k=0; k<4; k++){
                    char next = value(plateau, i+dir[k][0], j+dir[k][1]);
                    if (next == joueur)
                    {
                        char next2 = value(plateau, i+2*dir[k][0], j+2*dir[k][1]);
                        if (next2 == eni){
                            char next3 = value(plateau, i+3*dir[k][0], j+3*dir[k][1]);
                            if (next3 == VIDE || next3 == HORS){
                                atk++;
                            }
                        }

                        else if (next2 == joueur){
                            char next3 = value(plateau, i+3*dir[k][0], j+3*dir[k][1]);
                            if (next3 == eni){
                                char next4 = value(plateau, i+3*dir[k][0], j+3*dir[k][1]);
                                char next5 = value(plateau, i+3*dir[k][0], j+3*dir[k][1]);
                                if (next4 == VIDE || next4 == HORS || (next4 == eni && (next5==PION_VIDE || next5==HORS))){
                                    atk++;
                                }
                                }
                            }
                        }
                    }
                }
            }
        }
    return atk;

}

int nbrBille(Pion *plateau[8][8], int joueur){
    int bille = 0;
    for (int i = 0; i<8; i++){
        for (int j = 0; j<8; j++){
            if (plateau[i][j]->couleur == joueur){
                bille++;
            }
        }
    }
    return bille;
}

int win(Pion *plateau[8][8], int joueur){
    if (nbrBille(plateau, joueur)<14){
        return 1;
    }
    else{
        return 0;
    }
}

int position(Pion *plateau[8][8], int joueur){
    int pos = 0;
    for (int i = 0; i<8; i++){
        for (int j = 0; j<8; j++){
            if (plateau[i][j]->couleur == joueur){
                pos += valPos[i][j];
            }
        }
    }
    return pos;
}

int posDang(Pion *plateau[8][8], int joueur){
    int posDan = 0;
    for (int i = 0; i<8; i++){
        for (int j = 0; j<8; j++){
            if (plateau[i][j]->couleur == joueur && valPos[i][j] == 0){
                posDan ++;
            }
        }
    }
    return posDan;
}

int groupement(Pion *plateau[8][8], int joueur){
    int group = 0;
    for (int i = 0; i<8; i++){
        for (int j = 0; j<8; j++){
            if (plateau[i][j]->couleur == joueur){
                for (int k = 0; k<4; k++){
                    if (value(plateau, i+dir[k][0], j+dir[k][1])==joueur){
                        group++;
                    }
                    if (value(plateau, i+2*dir[k][0], j+2*dir[k][1])==joueur){
                        group = group + 15;
                    }
                }
            }
        }
    }
    return group;
}

int eval(Pion *plateau[8][8], int joueur){
    int eni;
    if (joueur == BLANC){
        eni = NOIR;
    }
    else {
        eni = BLANC;
    }
    int val = 0;
    val += attackPoss(plateau, joueur)*moveValue[1];
    val += attackPoss(plateau, eni) * moveValue[2];
    val += position(plateau, joueur) * moveValue[3];
    val += position(plateau, eni) * moveValue[4];
    val += groupement(plateau, joueur) * moveValue[5];
    val += groupement(plateau, eni) * moveValue[6];
    val += posDang(plateau, joueur) * moveValue[7];
    val += posDang(plateau, eni) * moveValue[8];
    
    if (win(plateau, eni == 1)){
        val += moveValue[0];
    }
    if (win(plateau, joueur) == 1){
        val +=moveValue[9];
    }
    return val;
}


int minimax_max(Pion *plateau[8][8], int hauteur, int joueur){
    if(hauteur < 1 || check_win(plateau)==1){
        return eval(plateau, joueur);
    }
    int nbrMvt = 0;
    Deplacement listMvt2[nbrDep];
    mvtLigne(plateau,&nbrMvt,joueur, listMvt2);

    if(nbrMvt==0){
        return eval(plateau, joueur);
    } 
    int valmax = INT_MIN;
    hauteur = hauteur-1;
    for (int i=0; i<nbrMvt ;i++){
        Deplacement coup = listMvt2[i];
        Pion *newPlateau[8][8];
        copyPlateau(plateau, newPlateau);
        check(coup,newPlateau,joueur, true);
        int valcoup = minimax_min(newPlateau, hauteur, joueur);
        if (valmax < valcoup){
            valmax = valcoup;
        }

    }
    return valmax;
}


int minimax_min(Pion *plateau[8][8], int hauteur, int joueur){
    if(hauteur < 1 || check_win(plateau)==1){
        return eval(plateau, joueur);
    }
    int eni;
    if (joueur == BLANC){
        eni = NOIR;
    }
    else{
        eni = BLANC;
    }
    int nbrMvt = 0;
    Deplacement listMvt1[nbrDep];
    mvtLigne(plateau,&nbrMvt,eni, listMvt1);

    if(nbrMvt==0){
        return eval(plateau, joueur);
    } 
    int valmin = INT_MAX;
    hauteur = hauteur-1;
    for (int i=0; i<nbrMvt ;i++){
        Deplacement coup = listMvt1[i];
        Pion *newPlateau[8][8];
        copyPlateau(plateau, newPlateau);
        check(coup, newPlateau, eni, true);
        int valcoup = minimax_max(newPlateau, hauteur, joueur);
        if (valmin > valcoup){
            valmin = valcoup;
        }

    }
    return valmin;
}

Deplacement minmax(Pion *plateau[8][8], int hauteur, int joueur){
    int nbrMvt = 0;
    Deplacement listMvt[nbrDep];
    mvtLigne(plateau,&nbrMvt,joueur, listMvt);
    Deplacement bestMove = listMvt[0];

    int valMax = INT_MIN;
    hauteur = hauteur - 1;

    for (int i = 0; i<nbrMvt; i++){
        Deplacement coup = listMvt[i];
        Pion *newPlateau[8][8];
        copyPlateau(plateau, newPlateau);
        check(coup, newPlateau, joueur, true);
        int valcoup = minimax_min(newPlateau, hauteur, joueur);
        if (valMax < valcoup){
            valMax = valcoup;
            bestMove = coup;
        }
    }
    return bestMove;
}

int alphaBeta_max(Pion *plateau[8][8], int hauteur, int joueur, int alpha, int beta){
    if(hauteur < 1 || check_win(plateau)==1){
        return eval(plateau, joueur);
    }
    int nbrMvt = 0;
    Deplacement listMvt2[nbrDep];
    mvtLigne(plateau,&nbrMvt,joueur, listMvt2);

    if(nbrMvt==0){
        return eval(plateau, joueur);
    } 
    int val = INT_MIN;
    hauteur = hauteur-1;
    for (int i=0; i<nbrMvt ;i++){
        Deplacement coup = listMvt2[i];
        Pion *newPlateau[8][8];
        copyPlateau(plateau, newPlateau);
        check(coup,newPlateau,joueur, true);
        int val_min = alphaBeta_min(newPlateau, hauteur, joueur, alpha, beta);
        val = max(val, val_min);
        if (val >= beta){
            return val;
        }
        alpha = max(alpha, val);
    }
    return val;
}


int alphaBeta_min(Pion *plateau[8][8], int hauteur, int joueur, int alpha, int beta){
    if(hauteur < 1 || check_win(plateau)==1){
        return eval(plateau, joueur);
    }
    int eni;
    if (joueur == BLANC){
        eni = NOIR;
    }
    else{
        eni = BLANC;
    }
    int nbrMvt = 0;
    Deplacement listMvt1[nbrDep];
    mvtLigne(plateau,&nbrMvt,eni, listMvt1);

    if(nbrMvt==0){
        return eval(plateau, joueur);
    } 
    int val = INT_MAX;
    hauteur = hauteur-1;
    for (int i=0; i<nbrMvt ;i++){
        Deplacement coup = listMvt1[i];
        Pion *newPlateau[8][8];
        copyPlateau(plateau, newPlateau);
        check(coup, newPlateau, eni, true);
        int val_max = alphaBeta_max(newPlateau, hauteur, joueur, alpha, beta);
        val = min(val, val_max);
        if (val <= alpha){
            return val;
        }
        beta = min(beta, val);
    }
    return val;
}

Deplacement alphaBeta(Pion *plateau[8][8], int hauteur, int joueur){
    int nbrMvt = 0;
    Deplacement listMvt[nbrDep];
    mvtLigne(plateau,&nbrMvt,joueur, listMvt);
    Deplacement bestMove = listMvt[0];

    int valMax = INT_MIN;
    int alpha = INT_MIN;
    int beta = INT_MAX;
    hauteur = hauteur - 1;

    for (int i = 0; i<nbrMvt; i++){
        Deplacement coup = listMvt[i];
        Pion *newPlateau[8][8];
        copyPlateau(plateau, newPlateau);
        check(coup, newPlateau, joueur, true);
        int valcoup = alphaBeta_min(newPlateau, hauteur, joueur, alpha, beta);
        if (valMax < valcoup){
            valMax = valcoup;
            bestMove = coup;
        }
        alpha = max(alpha, valMax);
    }
    return bestMove;
}

Deplacement ia(Pion *plateau[8][8], int joueur){
    int hauteur = 4;
    return alphaBeta(plateau, hauteur, joueur);
}

/*
int main(){
    test7();
    return 0;
}*/