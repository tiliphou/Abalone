#include "deroulement.h"


char joueur = NOIR;
int nb_tour=0;







void deroulement(char* argv[]){
	Pion *plateau[8][8];
	init(plateau);
	if (!(strcmp(argv[1],"-l"))){
        if(!(strcmp(argv[2],"blanc")|| strcmp(argv[2],"noir"))) {
			printf("illegal side choice\n");
			exit(1);
		}
		game_local(argv[2],plateau);
	}
	else if(!(strcmp(argv[1],"-s"))){
        char* port = argv[2];
		game_server_IA(port,plateau);
    }
	else if(!(strcmp(argv[1],"-c"))){
        int buffer = 0;
        char IP[10];
        char port[4];
        while (argv[2][buffer]!=':'){
            IP[buffer]=argv[2][buffer];
            buffer+=1;
        }
        for (int i = 0; i<4;i++){
            port[i]=argv[2][buffer+1];
            buffer+=1;
        }
        game_client_IA(IP,port,plateau);
    }
	else if(!(strcmp(argv[1],"-t"))){
		printf("stop");
	}
	else{
		printf("invalid argument");
	}
}



void game_local(char* argv,Pion* plateau[8][8]){
	if (!(strcmp(argv,"noir"))){
		joueur=NOIR;
	}
	while (1){

		char input[6];
		int valid=0;
		display(plateau);

		if (joueur==NOIR) {
			printf("BLACK player : select and move your coins : ");
			scanf("%s",input);
			//fgets(input,6,stdin);
			while(valid==0){
				valid++;
				if (valid_entry(input,1)==0){
					printf("select and move your coins : ");
					scanf("%s",input);
					valid--;
				}
				else{
					Deplacement entree_1 = convert_command(input);
					if (check(entree_1,plateau,joueur,true)==false){
						printf("wrong move, select and move your coins : ");
						scanf("%s",input);
						valid--;
					}
				}
			}
			nb_tour+=1;
			if (check_win(plateau)==1) {
				printf("BLACK player wins in %i rounds\n",nb_tour);
				break;
			}
			else
				joueur = BLANC;
		}
		else {
			Deplacement entree_2 = randomIA(plateau,joueur);
			check(entree_2,plateau,joueur,true);
	   		nb_tour+=1;
       		if(check_win(plateau)==1) {
				printf("WHITE player wins in %i rounds",nb_tour);
				break;
			}
			else
				joueur = NOIR;
		}
	}
}

void game_server(char* port,Pion* plateau[8][8]){
    printf("The selected port is %s\n",port);
    int p = atoi(port);
    SOCKET master = TCP_Create_Server(p);
    if (master==INVALID_SOCKET) exit(1);
	printf("[+]Server socket initialized waiting for client connection...\n");
	SOCKET slave = accept(master,NULL,0);
	printf("[+]Client connection received... \n");
	char* input = malloc(sizeof(char)*6);
	while(1){
			int valid=0;
			display(plateau);
			if (joueur==BLANC){
				printf("Select and move your coins : ");
				scanf("%s",input);
				while(valid==0){
					valid++;
					if (valid_entry(input,1)==0){
						printf("Select and move your coins : ");
						scanf("%s",input);
						valid--;
					}
					else{
						Deplacement entree_1 = convert_command(input);
						if (check(entree_1,plateau,joueur,true)==false){
							printf("wrong move... \nSelect and move your coins : ");
							scanf("%s",input);
							valid--;
						}
					}
				}
				write(slave,input,sizeof(input));
				nb_tour+=1;
				if (check_win(plateau)==1) {
					printf("BLACK player wins in %i rounds",nb_tour);
					break;
				}
				else {
					joueur=NOIR;
				}
			 }
			else {
				printf("Waiting for client's move...\n");
				recv(slave,input,sizeof(input),0);
				Deplacement deplacement_utilisateur2 = convert_command(input);
				//deplacement(deplacement_utilisateur);
				if (check(deplacement_utilisateur2,plateau,joueur,true)==false){
					printf("Client sent a wrong move\n");
					exit(1);
				}
	       		nb_tour+=1;
	       		if(check_win(plateau)==1) {
					printf("Player 2 wins in %i rounds",nb_tour);
					break;
				}
	       		else{
					joueur=BLANC;
				}
	       	}
		bzero(input,6);
	    }
	shutdown(slave,2);
    shutdown(master,2);
}


void game_server_IA(char* port,Pion* plateau[8][8]){
    printf("The selected port is %s\n",port);
    int p = atoi(port);
    SOCKET master = TCP_Create_Server(p);
    if (master==INVALID_SOCKET) exit(1);
	printf("[+]Server socket initialized waiting for client connection...\n");
	SOCKET slave = accept(master,NULL,0);
	printf("[+]Client connection received... \n");
	char* input = malloc(sizeof(char)*6);
	while(1){
			int valid=0;
			display(plateau);
			if (joueur==BLANC){
				Deplacement entree_2 = randomIA(plateau,joueur);
				if (check(entree_2,plateau,joueur,true)==false){
					printf("I sent a wrong move, my bad\n");
					exit(1);
				}
				deplt_to_string(entree_2,input);
				printf("%s\n",input);
				sleep(1);
				write(slave,input,sizeof(input));
				nb_tour+=1;
				if (check_win(plateau)==1) {
					printf("BLACK player wins in %i rounds",nb_tour);
					break;
				}
				else {
					joueur=NOIR;
				}
			}
			else {
				printf("Waiting for client's move...\n");
				recv(slave,input,sizeof(input),0);
				printf("%s\n",input);
				Deplacement deplacement_utilisateur2 = convert_command(input);
				if (check(deplacement_utilisateur2,plateau,joueur,true)==false){
					printf("Client sent a wrong move\n");
					exit(1);
				}
	       		nb_tour+=1;
	       		if(check_win(plateau)==1) {
					printf("Player 2 wins in %i rounds",nb_tour);
					break;
				}
	       		else{
					joueur=BLANC;
				}
	       	}
		bzero(input,6);
	    }
	shutdown(slave,2);
    shutdown(master,2);
}

void game_client(char* IP,char* port,Pion* plateau[8][8]){
	int p = atoi(port);
    SOCKET slave = TCP_Create_Client(IP,p);
    if (slave==INVALID_SOCKET) exit(1);
	printf("[+]Client socket initialized...\n");
	char* input = malloc(sizeof(char)*6);
	while(1){
		int valid=0;
		display(plateau);
		if (joueur==BLANC){
			printf("Waiting for server move...\n");
			recv(slave,input,sizeof(input),0);	
			printf("%s\n",input);		
			Deplacement deplacement_utilisateur1 = convert_command(input);
			//deplacement(deplacement_utilisateur);
			if (check(deplacement_utilisateur1,plateau,joueur,true)==false){
				printf("Server sent a wrong move\n");
				exit(1);
			}
	       	nb_tour+=1;
			if (check_win(plateau)==1) {
				printf("player 1 wins in %i rounds\n",nb_tour);
				break;
			}
			else {
				joueur=NOIR;
			}
		}
		else {
			printf("Select and move your coins : ");
			scanf("%s", input);
			while(valid==0){
				valid++;
				if (valid_entry(input,1)==0){
					printf("Select and move your coins : ");
					scanf("%s", input);
					valid--;
				}
				else{
					Deplacement deplacement_utilisateur2 = convert_command(input);
					if (check(deplacement_utilisateur2,plateau,joueur,true)==false){
						printf("wrong move, select and move your coins : ");
						scanf("%s",input);
						valid--;
					}
				}
			}
			printf("%s\n",input);
			//deplacement(entréeL);
            write(slave,input,sizeof(input));
			nb_tour+=1;
	       	if(check_win(plateau)==1) {
				printf("Player 2 wins in %i rounds",nb_tour);
				break;
			}
	       	else{
				joueur=BLANC;
			}
			bzero(input,6);
       	}
	}
	shutdown(slave,2);
}

void game_client_IA(char* IP,char* port,Pion* plateau[8][8]){
	int p = atoi(port);
    SOCKET slave = TCP_Create_Client(IP,p);
    if (slave==INVALID_SOCKET) exit(1);
	printf("[+]Client socket initialized...\n");
	char* input = malloc(sizeof(char)*6);
	while(1){
		int valid=0;
		display(plateau);
		if (joueur==BLANC){
			printf("Waiting for server move...\n");
			recv(slave,input,sizeof(input),0);	
			printf("%s\n",input);		
			Deplacement deplacement_utilisateur1 = convert_command(input);
			//deplacement(deplacement_utilisateur);
			if (check(deplacement_utilisateur1,plateau,joueur,true)==false){
				printf("Server sent a wrong move\n");
				exit(1);
			}
	       	nb_tour+=1;
			if (check_win(plateau)==1) {
				printf("player 1 wins in %i rounds\n",nb_tour);
				break;
			}
			else {
				joueur=NOIR;
			}
		}
		else {
			Deplacement entree_2 = randomIA(plateau,joueur);
			if (check(entree_2,plateau,joueur,true)==false){
				printf("I sent a wrong move, my bad\n");
				exit(1);
			}
			deplt_to_string(entree_2,input);
			printf("%s\n",input);
			sleep(1);
            write(slave,input,sizeof(input));
			nb_tour+=1;
	       	if(check_win(plateau)==1) {
				printf("Player 2 wins in %i rounds",nb_tour);
				break;
			}
	       	else{
				joueur=BLANC;
			}
			bzero(input,6);
       	}
	}
	shutdown(slave,2);
}



/*
int main(int argc,char** argv){
	return 0;
}
*/


