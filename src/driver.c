#include "lexer/lex.h"
#include"header/lang-struct.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
int main(){
    uint8_t lflag = 0;
    uint8_t cflag = 0;
    struct lexeme* tok;
    char* script = "ank $b 5 hai";
    tok = tokenize(script,lflag,cflag);
}

//YOU COMMITTED A MISTAKE
//WE HAVE TO RETURN A LIST OF TOKENS, NOT JUST ONE,
//UPON RETURNING A TOKEN, PROGRAM TERMINATES
//SO KINDLY DEFINE AN ARRAY, AND STORE IT IN THE ARRAY
//THEN AFTER THE LOOP, RETURN THE ARRAY