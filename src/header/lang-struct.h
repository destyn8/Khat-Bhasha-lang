#include<stdio.h>
#include<ctype.h>
enum tokenType{
    AGAR_IF,DAUHRAO_FOR,ANK_INT,SHABD_STR,SACHAI_BOOL,
    VAR,ARITH_OPERAT,COMP_OPERAT,SE_RANGE,PUNCT,LPAREN,RPAREN,HAI_ASSGN,
    AGAR_ENDIF,DAUH_ENDFOR,INT_CONST,STR_CONST
};
struct lexeme{
    enum tokenType token;
    char desc[8];
    uint8_t lflag;
    uint8_t cflag;
};


