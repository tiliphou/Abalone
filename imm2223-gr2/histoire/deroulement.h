#ifndef ABALONE_DEROULEMENT_H
#define ABALONE_DEROULEMENT_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "plateau.h"
#include "ihm.h"
#include "regles.h"
#include "network.h"
#include "ia.h"



void deroulement(char* argv[]);
void game_local(char* argv,Pion* plateau[8][8]);
void game_server(char* port,Pion* plateau[8][8]);
void game_server_IA(char* port,Pion *plateau[8][8]);
void game_client(char* IP,char* port,Pion* plateau[8][8]);
void game_client_IA(char* IP,char* port,Pion* plateau[8][8]);
void test(Pion* plateau[8][8]);

#endif 	//ABALONE_DEROULEMENT_H