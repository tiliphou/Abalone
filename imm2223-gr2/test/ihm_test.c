#include<stdio.h>
#include<stdlib.h>
#include"../plateau.h" 
#include"../ihm.h"
#include"ihm_test.h"
#include"test_main.h"

int test_new_position(){
    Position P=new_position(1,4);
    if (P->x==1 && P->y==4){
        printf("test_new_position reussi\n\n");
        return 0;
    }
    else {
        printf("erreur sur new_position_test\n\n");
        return 1;
    }
    
}

int test_char_to_int(){
    if(char_to_int('a')==32){
        printf("test_char_to_int reussi\n\n");
        return 0;
   }
    else {
        printf("erreur sur char_to_int_test\n\n");
        return 1;
    }
}

int test_int_to_int(){
    if (int_to_int('1')==0){
        printf("test_int_to_int reussi\n\n");
        return 0;
    }
    else{
        printf("erreur sur int_to_int_test\n\n");
        return 1;
    }
}

int test_convert(){
    Position P1;
    P1=new_position('A','1');
    if (convert(P1)->x==NULL && convert(P1)->y==NULL){
        printf("test_convert reussi\n\n");
        return 0;
    }
        
    else{
        printf("erreur sur convert_test\n\n");
        return 1;
    } 

    
}



int test_new_tab(){
    Position P1;
    P1=new_position('A','1');
    Position P2;
    P2=new_position('A','1');
    if (new_tab(P1,P2)->start[0]==NULL && new_tab(P1,P2)->start[1]==NULL && new_tab(P1,P2)->end[0]==NULL && new_tab(P1,P2)->end[1]==NULL){
        printf("test_new_tab reussi\n\n");
        return 0;
    }
    else{
        printf("erreur sur new_tab_test\n\n");
        return 1;
    }

    
}

int test_deplt_to_string(){
    char input[5];
    Position P1;
    P1=new_position('A','1');
    Position P2;
    P2=new_position('B','2');
    deplt_to_string(new_tab(P1,P2),input);
    if (input[0]=='A' && input[1]=='1' && input[2]==':' && input[3]=='B' && input[4]=='2'){
        printf("test_deplt_to_string reussi\n\n");
        return 0;
    }
    else{
        printf("erreur sur deplt_to_string_test\n\n");
        return 1;
    }

    
}



int test_verification(){
    if (verification(5)==1 && verification(8)==0){
        printf("test_verification reussi\n\n");
        return 0;
    }
    
    else{
        return 1;
    }
}

int test_syntax(){
    char test1[3]={0,1,':'};
    if (syntax(test1)==1){
        printf("test_syntax reussi\n\n");
        return 0;
    }
    else{
        return 1;
    }
}

int test_valid_entry(){

    char test1[10]={'E','5',':','E','7','8'};
    char test2[10]={'E','5',':','E'};
    char test3[10]={'F','4',':','F','4'};
    char test4[10]={'X','7',':','A','2'};
    char test5[10]={'D','3',':','A','9'};
    char test6[10]={'E','5',':','E','7'};
    if (valid_entry(test1)==0 && valid_entry(test2)==0 && valid_entry(test3)==0 && valid_entry(test4)==0 && valid_entry(test5)==0 && valid_entry(test6)==1){
        printf("test_valid_entry reussi\n\n");
        return 0;
    }
    else{
        printf("erreur sur valid_entry_test\n\n");
        return 1;
    }
    
}



int test_convert_command(){
    char test[10]={'A','1',':','A','1'};
    Deplacement deplt= convert_command(test);
    if (deplt->start[0]==NULL && deplt->start[1]==NULL && deplt->end[0]==NULL && deplt->end[1]==NULL){
        printf("test_convert_command reussi\n\n");
        return 0;
    }
    else{
        printf("erreur sur test_convert_command\n\n");
        return 1;
    }
}

void test_all_ihm_function(int* run, int* failures){
    run_test(test_new_position(),run,failures);
	run_test(test_char_to_int(),run,failures);
	run_test(test_int_to_int(),run,failures);
	run_test(test_convert(),run,failures);
	run_test(test_new_tab(),run,failures);
	run_test(test_deplt_to_string(),run,failures);
	run_test(test_verification(),run,failures);
	run_test(test_syntax(),run,failures);
	run_test(test_valid_entry(),run,failures);
	run_test(test_convert_command(),run,failures);
}

