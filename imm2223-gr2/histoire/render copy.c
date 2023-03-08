#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include "plateau.h"
#include "ihm.h"
#include "regles.h"
#include "ia.h"
#include "network.h"





typedef struct {
	Pion* plateau[8][8];
	int *TOUR;
	GtkWidget *label;
	GtkWidget *tourlabel;
	GtkWidget *plateauUI[8][8];

}EntryStruct;

typedef struct {
	Pion* plateau[8][8];
	int *TOUR;
	SOCKET s;
	char mode;
	GtkWidget *tourlabel;
	GtkWidget *plateauUI[8][8];

}ThreadParam;


char *images[3]={"blanc.png","noir.png","gris.png"};

int COULEUR = 1;
int button_clicked;
const int start = 10;
int pos_x = start;
int pos_y = start;
int width = 40;
int length = 40;
int radius = 20;
const int pace = 50;

const int totalwidth=pace*10;
const int totallength=pace*18;

void listening(SOCKET s,GtkWidget *plateauUI[8][8],Pion *plateau[8][8],int *joueur);
void ecriture(SOCKET s,GtkWidget *plateauUI[8][8],Pion *plateau[8][8],int *joueur);



EntryStruct* init_EntryStruct(Pion* plateau[8][8],int* TOUR,GtkWidget *label,GtkWidget *tourlabel,GtkWidget *plateauUI[8][8]){
	EntryStruct* ets = malloc(sizeof(EntryStruct));

	for(int i =0;i<8;i++){
		for(int j =0;j<8;j++){
			ets->plateau[i][j]=init_Pion(plateau[i][j]->couleur,i,j);
		}
	}
	ets->TOUR=TOUR;
	ets->label=label;
	ets->tourlabel = tourlabel;
	for(int i =0;i<8;i++){
		for(int j =0;j<8;j++){
			ets->plateauUI[i][j] = plateauUI[i][j];
		}
	}
	return ets;
}

ThreadParam* init_ThreadParam(Pion* plateau[8][8],int* TOUR,SOCKET s,char mode,GtkWidget *tourlabel,GtkWidget *plateauUI[8][8]){
	ThreadParam* Thp = malloc(sizeof(ThreadParam));
	for(int i =0;i<8;i++){
		for(int j =0;j<8;j++){
			Thp->plateau[i][j]=init_Pion(plateau[i][j]->couleur,i,j);
		}
	}
	Thp->TOUR=TOUR;
	Thp->s = s;
	Thp->mode =mode;
	Thp->tourlabel = tourlabel;
	for(int i =0;i<8;i++){
		for(int j =0;j<8;j++){
			Thp->plateauUI[i][j] = plateauUI[i][j];
		}
	}
	return Thp;
}

GtkWidget *new_pion(Pion *pion){

	GtkWidget* image_pion;
	
		if(pion->couleur == NOIR){
			image_pion = gtk_image_new_from_file("noir.png");
		}
		if(pion->couleur == BLANC){
			image_pion = gtk_image_new_from_file("blanc.png");
		}
		if(pion->couleur == VIDE){
			image_pion = gtk_image_new_from_file("gris.png");
		}
	
	return image_pion;
	
	
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



void refresh_table(Pion *plateau[8][8],GtkWidget *plateauUI[8][8]){

	for (int i = 0; i<8; i++){		
		for(int j=0; j<8; j++){
			gtk_image_set_from_file(plateauUI[i][j],images[plateau[i][j]->couleur]);	
		}
	}

}

void display_table(GtkWidget *grid, Pion *plateau[8][8],GtkWidget *plateauUI[8][8]){

	GtkWidget* image_pion;
	
	init(plateau);
	
	GtkWidget *label;
	char number ='1';
	char letter = 'A';
	char ind[3] = "   ";
	
	
	for (int i = 0; i<8; i++){
		ind[1]= number;
		label = gtk_label_new(ind);
		
		/*gchar *str = g_locale_to_utf8("Enter your <span foreground=\"#000000\"><b>%s</b></span>", -1, NULL, NULL, NULL);
		gtk_label_set_markup(GTK_LABEL(label), str);
		g_free(str);*/
		
		
		/*gchar* str = g_locale_to_utf8("<span foreground=\"25\"><b> %s </b></span>", -1, NULL,NULL, NULL);
		gchar *markup = g_markup_printf_escaped(str, ind[i]);
		gtk_label_set_markup(GTK_LABEL(label), markup);
		g_free(markup);*/
		
		gtk_grid_attach(GTK_GRID(grid), label, i+1,0,1,1);
		
		
		number++;
	}
	
	for (int i = 0; i<8; i++){
	
		ind[1]= letter;
		label = gtk_label_new(ind);
		gtk_grid_attach(GTK_GRID(grid), label, 0,i+1,1,1);
		letter++;
		
		for(int j=0; j<8; j++){
			image_pion = new_pion(plateau[i][j]);
			gtk_grid_attach(GTK_GRID(grid), image_pion, j+1,i+1,1,1);
			plateauUI[i][j] = image_pion;
			gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
			gtk_grid_set_row_spacing(GTK_GRID(grid), 5);				
		}
	
	}
}




void onDestroy(GtkWidget *widget, gpointer data){

	gtk_main_quit();	
	
}


void onActivateEntry(GtkEntry *entry, gpointer data){

	const gchar *text;
	
	EntryStruct *entrystruct = (EntryStruct *)data;
		
	if(*entrystruct->TOUR == COULEUR){

		text = gtk_entry_get_text(GTK_ENTRY(entry));
	
		
		

		if(valid_entry(text,1)==0){
			const gchar *strWarning = g_locale_to_utf8("Syntaxe non correcte !\n <span foreground=\"#C0C0C0\"><b>(ex: A1:A2)</b></span>", -1, NULL, NULL, NULL);
			//gtk_label_set_text(GTK_LABEL(entrystruct->label),"(ex: A1:A2)");
			gtk_label_set_markup(GTK_LABEL(entrystruct->label), strWarning);
			g_free(strWarning);
			//gtk_misc_set_alignment(GTK_LABEL(entrystruct->label), 0.0, 0.5);
			}
			
			
		else{
			Deplacement entree_1 = convert_command(text);
			
			if (check(entree_1,entrystruct->plateau,*entrystruct->TOUR,true)==false)
				gtk_label_set_text(GTK_LABEL(entrystruct->label),"Mouvement non valide !");
			else{
				*entrystruct->TOUR = (*entrystruct->TOUR+1)%2;

				gtk_label_set_text(GTK_LABEL(entrystruct->label),"Enter your move : ");
				refresh_table(entrystruct->plateau,entrystruct->plateauUI);
				const gchar *strPlayer;
				if(*entrystruct->TOUR == 0)
					strPlayer = g_locale_to_utf8("Player <span foreground=\"#000000\"><b>White</b></span>, it's your turn", -1, NULL, NULL, NULL);
				else
					strPlayer = g_locale_to_utf8("Player <span foreground=\"#000000\"><b>Black</b></span>, it's your turn", -1, NULL, NULL, NULL);
				gtk_label_set_markup(GTK_LABEL(entrystruct->tourlabel), strPlayer);
				

				while (g_main_context_pending(NULL)){
					g_main_context_iteration(NULL, FALSE);
				}
				sleep(1);
				
				
				Deplacement entree_2 = randomIA(entrystruct->plateau,*(entrystruct->TOUR));
				check(entree_2,entrystruct->plateau,*entrystruct->TOUR,true);
				*entrystruct->TOUR = (*entrystruct->TOUR+1)%2;
				refresh_table(entrystruct->plateau,entrystruct->plateauUI);
				
				if(*entrystruct->TOUR == 0)
					strPlayer = g_locale_to_utf8("Player <span foreground=\"#000000\"><b>White</b></span>, it's your turn", -1, NULL, NULL, NULL);
				else
					strPlayer = g_locale_to_utf8("Player <span foreground=\"#000000\"><b>Black</b></span>, it's your turn", -1, NULL, NULL, NULL);
				gtk_label_set_markup(GTK_LABEL(entrystruct->tourlabel), strPlayer);

				g_free(strPlayer);
				
				if (check_win(entrystruct->plateau)==1) {
					printf("%i player wins \n",*entrystruct->TOUR);
					gtk_main_quit();
				}
			}
		}
	}
	else{
		gtk_label_set_text(GTK_LABEL(entrystruct->label),"Ce n'est pas votre tour !");
	}
	gtk_entry_set_text(GTK_ENTRY(entry),"");
}

void *thread_callback(void* arg){
	ThreadParam* Thp = (ThreadParam*)arg;
	if(Thp->mode=='s'){
		listening(Thp->s,Thp->plateauUI,Thp->plateau,Thp->TOUR);
	}
	else if(Thp->mode=='c'){
		ecriture(Thp->s,Thp->plateauUI,Thp->plateau,Thp->TOUR);
	}
	else{
		gtk_main_quit();
	}
}


void ecriture(SOCKET s,GtkWidget *plateauUI[8][8],Pion *plateau[8][8],int *joueur){
	char input[6];
	Deplacement coup = randomIA(plateau,*joueur);
	deplt_to_string(coup,input);
	printf("%s\n",input);
	if (valid_entry(input,1)==1){
		printf("entréee valid");
	}
	if (check(coup,plateau,*joueur,true)==false){
		printf("I sent a wrong move, my bad\n");
	}
	refresh_table(plateau,plateauUI);
	
	//g_main_context_iteration(NULL, FALSE);
	
	printf("%s\n",input);
	sleep(1);
	write(s,input,sizeof(input));
	*joueur = (*joueur+1)%2;
	if (check_win(plateau)==1) {
		printf("%i player wins \n",*joueur);
		gtk_main_quit();
	}
	listening(s,plateauUI,plateau,joueur);
}

void listening(SOCKET s,GtkWidget *plateauUI[8][8],Pion *plateau[8][8],int *joueur){
	char input[6];
	recv(s,input,sizeof(input),0);	
	printf("input : %s\n",input);
	Deplacement coup = convert_command(input);
	if (check(coup,plateau,*joueur,true)==false){
		printf("I sent a wrong move, my bad\n");
	}
	refresh_table(plateau,plateauUI);

	//g_main_context_iteration(NULL, FALSE);

	sleep(1);
	*joueur = (*joueur+1)%2;
	if (check_win(plateau)==1) {
		printf("%i player wins \n",*joueur);
		gtk_main_quit();
	}
	ecriture(s,plateauUI,plateau,joueur);
}

	

void render(char mode,char *IP,int port){
	pthread_t pthid;
	int joueur=NOIR;
	SOCKET slave,master;
	if (mode=='s'){
		master = TCP_Create_Server(port);
		if (master==INVALID_SOCKET) exit(1);
		slave = accept(master,NULL,0);
	}
	else if (mode =='c'){
		slave = TCP_Create_Client(IP,port);
    	if (slave==INVALID_SOCKET) {
			printf("invalid socket");
			exit(1);
		}
	}

	static Pion *plateau[8][8];
	init(plateau);
	
	
	gtk_init(0, NULL);

	static GtkWidget *plateauUI[8][8];

	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget *grid = gtk_grid_new();
	GtkWidget *vBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
	
	
	GtkWidget *textGrid = gtk_grid_new();
	
	GtkWidget *presentationText;
	GtkWidget *playerText;
	GtkWidget *signatureText;

	
	//window initialized
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), totalwidth, totallength);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_title(GTK_WINDOW(window), "Abalone");
	
	
	//vertical box added to the window
	gtk_box_set_spacing(GTK_BOX(vBox), 40);
	gtk_container_add(GTK_CONTAINER(window), vBox);
	
	
	
	
	//Grid containing the display added to the vertical box	
	//gtk_window_set_role(GTK_WINDOW(window), grid);
	gtk_container_add(GTK_CONTAINER(window), grid);
	display_table(grid, plateau,plateauUI);
	
	gtk_box_pack_start(GTK_BOX(vBox), grid, FALSE, FALSE,0);
	
	
	//Player text added to the vertical box
	//char* couleurs[2] = {"NOIR","BLANC"}; 
	playerText=gtk_label_new(NULL);
	const gchar *strPlayer;
	if(COULEUR==0)
		strPlayer = g_locale_to_utf8("Player <span foreground=\"#000000\"><b>White</b></span>, it's your turn", -1, NULL, NULL, NULL);
	else
		strPlayer = g_locale_to_utf8("Player <span foreground=\"#000000\"><b>Black</b></span>, it's your turn", -1, NULL, NULL, NULL);
		gtk_label_set_markup(GTK_LABEL(playerText), strPlayer);
	g_free(strPlayer);
	
	//gtk_grid_attach(GTK_GRID(textGrid), playerText, 1,1,1,1);
	
	gtk_box_pack_start(GTK_BOX(vBox), playerText, FALSE, FALSE, 0);
	
	
	
	
	gtk_window_set_role(GTK_WINDOW(window), textGrid);
	gtk_container_add(GTK_CONTAINER(window), textGrid);
	//gtk_grid_set_column_homogeneous(GTK_GRID(textGrid), FALSE);
	gtk_grid_set_column_spacing(GTK_GRID(textGrid), 90);
	
	gtk_box_pack_start(GTK_BOX(vBox), textGrid, FALSE, FALSE,0);
	
	//Presentation text added to the vertical box
	
	presentationText=gtk_label_new(NULL);
	gchar *strPresentation = g_locale_to_utf8("Enter your <span foreground=\"#000000\"><b>move</b></span>", -1, NULL, NULL, NULL);
	gtk_label_set_markup(GTK_LABEL(presentationText), strPresentation);
	g_free(strPresentation);
	
	gtk_grid_attach(GTK_GRID(textGrid), presentationText, 0,1,3,1);
	
	
	//gtk_box_pack_start(GTK_BOX(vBox), presentationText, FALSE, FALSE, 0);
	
	
	
	
	//Entry zone added to the vertical box
	
	printf("%i\n",joueur);
	//gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "enter your move");
	//gtk_entry_set_frame_size(G_OBJECT(entry), 100);
	if (mode=='l'){
		if (COULEUR==BLANC){
			if(check(randomIA(plateau,NOIR),plateau,NOIR,true)==false){
				printf("coup non fait\n");
			}
			joueur=BLANC;
			refresh_table(plateau,plateauUI);
		}
		GtkWidget* entry = gtk_entry_new();
		EntryStruct *ets = init_EntryStruct(plateau,&joueur,presentationText,playerText,plateauUI);
		g_signal_connect(G_OBJECT(entry), "activate", G_CALLBACK(onActivateEntry), (void *)ets);
		gtk_widget_set_hexpand(GTK_WIDGET(textGrid), TRUE);
		gtk_grid_attach(GTK_GRID(textGrid), entry, 2,1,6,1);
	}
	else if(mode=='s'){
		ThreadParam* Thp = init_ThreadParam(plateau,&joueur,slave,mode,playerText,plateauUI);
		pthread_create(&pthid,NULL,thread_callback,(void*)Thp);
		//pthread_join(pthid,NULL);
	}
	else if(mode=='c'){
		ThreadParam* Thp = init_ThreadParam(plateau,&joueur,slave,mode,playerText,plateauUI);
		pthread_create(&pthid,NULL,thread_callback,(void*)Thp);
		//pthread_join(pthid,NULL);
	}
	//gtk_box_pack_start(GTK_BOX(vBox), entry, FALSE, FALSE,0);
	
	
	//Signature text added to the vertical box
	
	signatureText=gtk_label_new(NULL);
	gchar *strSignature = g_locale_to_utf8(" <span foreground=\"#C0C0C0\"><b>Programmed by 'groupe 2', powered by GTK 3.0</b></span>", -1, NULL, NULL, NULL);
	gtk_label_set_markup(GTK_LABEL(signatureText), strSignature);
	g_free(strSignature);
	
	
	gtk_box_pack_start(GTK_BOX(vBox), signatureText, FALSE, FALSE, 0);




	//destroy mechanism set  
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(onDestroy), NULL);
	
	
	
	gtk_widget_show_all(window);
	gtk_widget_show(window);
	gtk_main();
	
}


int main(int argc, char** argv){
	if (argc!=3){
		printf("nombre d'aguments incorrect\n");
		exit(1);
	}
	if (!(strcmp(argv[1],"-l"))){
        if(!(strcmp(argv[2],"blanc"))){
			COULEUR = BLANC;
			render('l',"127.0.0.1",1234);
		}
		else if(!(strcmp(argv[2],"noir"))){
			COULEUR = NOIR;
			render('l',"127.0.0.1",1234);
		}
		else{
			printf("illegal side choice\n");
			exit(1);
		}
	}
	else if(!(strcmp(argv[1],"-s"))){
        char* port = argv[2];
		int p = atoi(port);
		render('s',"127.0.0.1",p);
    }
	else if(!(strcmp(argv[1],"-c"))){
        int buffer = 0;
        char IP[16];
        char port[4];
        while (argv[2][buffer]!=':'){
            IP[buffer]=argv[2][buffer];
            buffer+=1;
        }
		IP[buffer]='\0';
        for (int i = 0; i<4;i++){
            port[i]=argv[2][buffer+1];
            buffer+=1;
        }
		int p = atoi(port);
        render('c',IP,p);
    }
	else{
		printf("error\n");
	}
	return EXIT_SUCCESS;
	
}
