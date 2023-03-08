/*
***********************************
Written by Luca DIACONU on Monday 5 December 2022
C file wich allows an entrance of commands if those are valid
***********************************
*/


#include "ihm.h"








Position new_position(char x, char y){
	Position P = malloc(sizeof(Position));
	P->x=x;
	P->y=y;
	return P;
}

Position convert(Position P1){
	char x = P1->x;
	char y = P1->y;

	int x_int = char_to_int(x);
	int y_int = int_to_int(y);

	Position convertedP = new_position((char)x_int, (char)y_int);
	return convertedP;
}


Deplacement new_tab(Position P1, Position P2){
    Deplacement deplt = malloc(sizeof(Deplacement));

	Position convertedP1 = convert(P1);
	Position convertedP2 = convert(P2);

	deplt->start[0]=(convertedP1->x);
    deplt->start[1]=(convertedP1->y);
    deplt->end[0]=(convertedP2->x);
    deplt->end[1]=(convertedP2->y);
	return deplt;
}

void deplt_to_string(Deplacement d,char *input){
    input[0]=(char)(((int)d->start[0])+65);
    input[1]=(char)(((int)d->start[1])+49);
    input[2]=':';
    input[3]=(char)(((int)d->end[0])+65);
    input[4]=(char)(((int)d->end[1])+49);
	input[5]='\0';
}


//counts the number of characters given in argument, with colons included. The correct number of characters is 5
int count(char *argv){
	int size = 0;
	while(argv[size] != '\0'){
		size++;
	}
	return size;
}



//converts a char letter in int

int char_to_int(char character){
	return (int)character - 65;
}

//converts a little char letter in int

int lchar_to_int(char character){
	return (int)character - 97;
}

//converts a char number in int

int int_to_int(char character){
	return (int)character - 49;
}

//checks on the validity of the conversion. It should be between 1 and 8

int verification(int number){
	if(0<=number && 7>=number){
		return 1;
	}
	else return 0;
}


int syntax(char* argv){
	if (argv[2] != ':'){
		printf("\n\n! wrong syntax ! \n	you need to write : 'starting position:ending position'\n	example : A2:A3\n\n");
		return 0;
	}
	else return 1;
}

//this part puts together all the functions explicited previously


int valid_entry(char input[]){

	int number=0;
	int number1=0;
	int size = count(input);


	if (size > SIZE_ARG){
		printf("invalid argument, too much characters : over 5 characters entered\n");
		syntax(input);
		return 0;
	}

	if (size < SIZE_ARG){
		printf("invalid argument, too few characters : below 5 characters entered\n");
		syntax(input);
		return 0;
	}

	if (char_to_int(input[0]) == char_to_int(input[3]) && int_to_int(input[1]) == int_to_int(input[4])){
		printf("impossible to move to this position\n");
		syntax(input);
		return 0;
	}

	for(int i=0; i<SIZE_ARG; i++){

		if(i==0 || i==3){
			number = char_to_int(input[i]);
			number1 = lchar_to_int(input[i]);
			if(verification(number) == 0 && verification(number1) == 0){
				printf("invalid argument, %c as the first argument does not belong on the table\n", input[i]);
				return 0;
			}
			if (verification(number)==0){
				input[i]-=32;
			}
		}
		if(i==1 || i==4){
			number = int_to_int(input[i]);
			if(verification(number) == 0){
				printf("invalid argument, %c as the second does not belong on the table\n", input[i]);
				return 0;
			}
		}
	}


	return 1;

}

Deplacement convert_command(char argv[10]){

	Position P1 = new_position(argv[0], argv[1]);
	Position P2 = new_position(argv[3], argv[4]);

	Deplacement deplt = new_tab(P1, P2);
    return deplt;
	//printlist(deplt);

}






