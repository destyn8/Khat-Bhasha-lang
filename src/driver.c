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
