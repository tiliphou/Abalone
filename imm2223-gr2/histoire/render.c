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


#define WIDTH  1200
#define HEIGHT 850

#define MAX_X 2
#define MAX_Y 10

#define NB_FLOCONS 200


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

typedef struct{
    GtkWidget *layout;
    GtkWidget *tab_flocons[NB_FLOCONS];
}AnimThreadParam;


int FLOCONS[NB_FLOCONS][2];

char *images[3] = {"Images/pion_blanc.png","Images/pion_noir.png","Images/pion_gris.png"};
char *images_select[3] = {"Images/pion_blanc_select.png","Images/pion_noir_select.png","Images/pion_valid.png"};
//char *c[8] = {"1","2","3","4","5","6","7","8"};
//char *l[8] = {"A","B","C","D","E","F","G","H"};

char *c[8] = {"Images/Lettres/1.png","Images/Lettres/2.png","Images/Lettres/3.png",
              "Images/Lettres/4.png","Images/Lettres/5.png","Images/Lettres/6.png",
              "Images/Lettres/7.png","Images/Lettres/8.png"};
char *l[8] = {"Images/Lettres/A.png","Images/Lettres/B.png","Images/Lettres/C.png",
              "Images/Lettres/D.png","Images/Lettres/E.png","Images/Lettres/F.png",
              "Images/Lettres/G.png","Images/Lettres/H.png"};

int COULEUR = NOIR;

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
	
	image_pion = gtk_image_new_from_file(images[pion->couleur]);

	return image_pion;
	
}



void refresh_table(Pion *plateau[8][8],GtkWidget *plateauUI[8][8]){

	for (int i = 0; i<8; i++){		
		for(int j=0; j<8; j++){
			gtk_image_set_from_file(plateauUI[i][j],images[plateau[i][j]->couleur]);	
		}
	}

}

void display_table(GtkWidget *grid, Pion *plateau[8][8],GtkWidget *plateauUI[8][8]){

	init(plateau);

	GtkWidget* image_pion;

    gtk_grid_set_column_spacing (GTK_GRID(grid),10);
    gtk_grid_set_row_spacing (GTK_GRID(grid),10);

    for (short i=0;i<9;i++){
        for (short j=0;j<9;j++){
            if (j == 0 && i>0){
                GtkWidget *label = gtk_image_new_from_file (l[i-1]);
                gtk_grid_attach(GTK_GRID(grid),label,j,i,1,1);
            }
            if (i == 0 && j>0){
                GtkWidget *label = gtk_image_new_from_file (c[j-1]);
                gtk_grid_attach(GTK_GRID(grid),label,j,i,1,1);
            }
            if (i>0 && j>0){
				image_pion = new_pion(plateau[i-1][j-1]);
                gtk_grid_attach(GTK_GRID(grid),image_pion,j,i,1,1);
				plateauUI[i-1][j-1] = image_pion;
			}
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
	
		
		

		if(valid_entry(text)==0){
			const gchar *strWarning = g_locale_to_utf8("<span font=\"15\" foreground=\"#C0C0C0\">Syntaxe non correcte !\n <b>(ex: A1:A2)</b></span>", -1, NULL, NULL, NULL);
			//gtk_label_set_text(GTK_LABEL(entrystruct->label),"(ex: A1:A2)");
			gtk_label_set_markup(GTK_LABEL(entrystruct->label), strWarning);
			g_free(strWarning);
			}
			
		else{
			Deplacement entree_1 = convert_command(text);
			
			if (check(entree_1,entrystruct->plateau,*entrystruct->TOUR,true)==false)
				gtk_label_set_markup(GTK_LABEL(entrystruct->tourlabel),g_locale_to_utf8("<span font=\"15\" foreground=\"#000000\">Mouvement non valide !<span>", -1, NULL, NULL, NULL));
				//gtk_label_set_text(GTK_LABEL(entrystruct->label),"Mouvement non valide !");
			else{
				*entrystruct->TOUR = (*entrystruct->TOUR+1)%2;
				gtk_label_set_markup(GTK_LABEL(entrystruct->tourlabel),g_locale_to_utf8("<span font=\"15\" foreground=\"#000000\">Enter your move : <span>", -1, NULL, NULL, NULL));
				//gtk_label_set_text(GTK_LABEL(entrystruct->label),"Enter your move : ");
				refresh_table(entrystruct->plateau,entrystruct->plateauUI);
				const gchar *strPlayer;
				if(*entrystruct->TOUR == 0)
					strPlayer = g_locale_to_utf8("<span font=\"15\" foreground=\"#000000\">Player <b>White</b>, it's your turn</span>", -1, NULL, NULL, NULL);
				else
					strPlayer = g_locale_to_utf8("<span font=\"15\" foreground=\"#000000\">Player <b>Black</b>, it's your turn</span>", -1, NULL, NULL, NULL);
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
					strPlayer = g_locale_to_utf8("<span font=\"15\" foreground=\"#000000\">Player <b>White</b>, it's your turn</span>", -1, NULL, NULL, NULL);
				else
					strPlayer = g_locale_to_utf8("<span font=\"15\" foreground=\"#000000\">Player <b>Black</b>, it's your turn</span>", -1, NULL, NULL, NULL);
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
		gtk_label_set_markup(GTK_LABEL(entrystruct->tourlabel),g_locale_to_utf8("<span font=\"15\" foreground=\"#000000\">Ce n'est pas votre tour !<span>", -1, NULL, NULL, NULL));
		//gtk_label_set_text(GTK_LABEL(entrystruct->label),"Ce n'est pas votre tour !");
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
	if (valid_entry(input)==1){
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

void *animationFlocons(void* args){

    AnimThreadParam *tp = (AnimThreadParam *)args;
    
    for(int i=0;i<NB_FLOCONS;i++){
        if(rand()%2 == 0)
            FLOCONS[i][0]+= rand()%MAX_X;
        else
            FLOCONS[i][0]-= rand()%MAX_X;
        FLOCONS[i][0]+= rand()%MAX_Y;

        if(FLOCONS[i][0] <= 0 || FLOCONS[i][0]>WIDTH)
            FLOCONS[i][0] = rand()%WIDTH;
        if(FLOCONS[i][1] <= 0 || FLOCONS[i][1]>HEIGHT)
            FLOCONS[i][1] = rand()%(HEIGHT/3);
        
        gtk_layout_move (GTK_LAYOUT(tp->layout), tp->tab_flocons[i], rand()%WIDTH, rand()%HEIGHT);
        }
    
    return FALSE;
    //while (g_main_context_pending(NULL))
	//    g_main_context_iteration(NULL, FALSE);

}

AnimThreadParam *initAnimThreadParam(GtkWidget *layout,GtkWidget *tab_flocons[NB_FLOCONS]){

    AnimThreadParam *tp = malloc(sizeof(AnimThreadParam));
    tp->layout = layout;
    for(int i=0;i<NB_FLOCONS;i++)
        tp->tab_flocons[i] = tab_flocons[i];
    
    return tp;
}

void *animation_thread(void *args){

    while(1){
        g_idle_add((GSourceFunc) animationFlocons, args);
    	usleep(15000);
    }
    //animationFlocons(tp->layout,tp->tab_flocons);
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
	GtkWidget *labeled_entry = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
	GtkWidget *hBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
	GtkWidget *vBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
	
	GtkWidget *presentationText;
	GtkWidget *playerText;
	GtkWidget *signatureText;

	
	//window initialized
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), WIDTH, HEIGHT);
	//gtk_window_set_default_size(GTK_WINDOW(window), totalwidth, totallength);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_title(GTK_WINDOW(window), "Abalone");
	
	GtkWidget *layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER (window), layout);

	GtkWidget *background = gtk_image_new_from_file ("Images/background.jpg");
	gtk_layout_put(GTK_LAYOUT(layout), background, 0, 0);
	
	//horizontal box added to the window
	//gtk_box_set_spacing(GTK_BOX(hBox), 20);
	gtk_container_add(GTK_CONTAINER(layout), hBox);
	
	//Grid containing the display added to the vertical box	
	//gtk_window_set_role(GTK_WINDOW(window), grid);
	
	gtk_container_add(GTK_CONTAINER(hBox), grid);
	display_table(grid, plateau,plateauUI);
	gtk_box_pack_start(GTK_BOX(hBox), grid, FALSE, FALSE,0);

	//Player text added to the vertical box
	//char* couleurs[2] = {"NOIR","BLANC"}; 
	playerText=gtk_label_new(NULL);
	const gchar *strPlayer;
	if(COULEUR==0)
		strPlayer = g_locale_to_utf8("<span font=\"15\" foreground=\"#000000\">Player <b>White</b>, it's your turn</span>", -1, NULL, NULL, NULL);
	else
		strPlayer = g_locale_to_utf8("<span font=\"15\" foreground=\"#000000\">Player <b>Black</b>, it's your turn</span>", -1, NULL, NULL, NULL);
		gtk_label_set_markup(GTK_LABEL(playerText), strPlayer);
	g_free(strPlayer);

	gtk_box_pack_start(GTK_BOX(vBox), playerText, FALSE, FALSE, 0);

	//Presentation text added to the vertical box
	
	presentationText=gtk_label_new(NULL);
	gchar *strPresentation = g_locale_to_utf8("<span font=\"15\" foreground=\"#000000\">Enter your <b>move</b></span>", -1, NULL, NULL, NULL);
	gtk_label_set_markup(GTK_LABEL(presentationText), strPresentation);
	g_free(strPresentation);
	
	//Entry zone added to the vertical box

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
		gtk_box_pack_start(GTK_BOX(labeled_entry), presentationText, FALSE, FALSE, 0);
		GtkWidget* entry = gtk_entry_new();
		EntryStruct *ets = init_EntryStruct(plateau,&joueur,presentationText,playerText,plateauUI);
		g_signal_connect(G_OBJECT(entry), "activate", G_CALLBACK(onActivateEntry), (void *)ets);
		gtk_entry_set_max_length(GTK_ENTRY(entry), 10);
		gtk_box_pack_start(GTK_BOX(labeled_entry), entry, FALSE, FALSE, 5);

		gtk_box_pack_start(GTK_BOX(vBox), labeled_entry, FALSE, FALSE, 0);
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
	
	/* signatureText=gtk_label_new(NULL);
	gchar *strSignature = g_locale_to_utf8(" <span font=\"20\" foreground=\"#C0C0C0\"><b>Programmed by 'groupe 2', powered by GTK 3.0</b></span>", -1, NULL, NULL, NULL);
	gtk_label_set_markup(GTK_LABEL(signatureText), strSignature);
	g_free(strSignature);
	gtk_box_pack_start(GTK_BOX(vBox), signatureText, FALSE, FALSE, 0); */

	//gtk_box_set_spacing(GTK_BOX(vBox), 50);
	//gtk_widget_set_margin_right(vBox,10);
	gtk_widget_set_margin_left(vBox,50);
	gtk_container_add(GTK_CONTAINER(hBox), vBox);
	gtk_widget_set_valign(vBox, GTK_ALIGN_CENTER);
	gtk_box_pack_start(GTK_BOX(hBox), vBox, FALSE, FALSE,0);

	GtkWidget *tab_flocon[NB_FLOCONS];

    for(int i=0;i<NB_FLOCONS;i++){
        tab_flocon[i] = gtk_image_new_from_file("Images/flocon.png");
        FLOCONS[i][0] = rand()%WIDTH;
        FLOCONS[i][1] = rand()%HEIGHT;
        gtk_layout_put(GTK_LAYOUT(layout), tab_flocon[i], FLOCONS[i][0], FLOCONS[i][1]);
    }

    AnimThreadParam *tp = initAnimThreadParam(layout,tab_flocon);

    GThread *myThread; 
	myThread = g_thread_new(NULL,(GThreadFunc)animation_thread,(void*)tp);

	//destroy mechanism set  
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(onDestroy), NULL);
	
	gtk_widget_show_all(window);
	//gtk_widget_show(window);
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
