#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdint.h>
#include<ctype.h>
#include"lex.h"
#include "../header/lang-struct.h"
struct lexeme tok;
struct lexeme lexemes[24];
struct lexeme *tokenize(char script[128], uint8_t lflag, uint8_t cflag){
    int count = 0;
    int index = 0;
    int newline = 0;
    int linechar = 0;
    char ch='a';
    char buffer[128];
    char *type = "UNDEF";
    uint8_t indc  = 0;//KEEP TRACK OF INDENTS
    uint8_t iflag = 0;//NUMBER
    uint8_t sflag = 0;//STRING
    uint8_t pflag = 0;//PAREN
    uint8_t dvflag= 0;//DEFINE VARIABLE
    uint8_t vflag = 0;//VARIABLE
    uint8_t tcount = 0;//LEXEME COUNT
    while(1){
        ch = script[count];
        if(strcmp(buffer,"agar ") == 0){
            tok.token = AGAR_IF;
            strcpy(tok.desc,"kw");
            tok.cflag = 1;
            tok.lflag = 0;
            memset(buffer, 0, sizeof buffer);
            index = 0;
            tcount++;
            lexemes[tcount]  = tok ;
        }
        if(strcmp(buffer," hai") == 0){
            tok.token = HAI_ASSGN;
            strcpy(tok.desc,"equ");
            tok.cflag = cflag;
            tok.lflag = lflag;
            tcount++;
            lexemes[tcount]  = tok ;
            
        }
        else if(cflag == 1){
            if(strcmp(" phir",buffer) == 0){
                memset(buffer, 0, sizeof buffer);
                index = 0;
            }
            if(linechar == 0 && isalpha(ch) && cflag == 1){
                indc--;
                tok.token = AGAR_ENDIF;
                strcpy(tok.desc,"eif");
                tok.cflag = 0;
                tok.lflag = 0;
                tcount++;
                lexemes[tcount]  = tok ;
            }
            else if(strcmp(buffer,"    ") == 0 ||strcmp(buffer,"\t") == 0 || ch == '\t'){
                indc++;
                memset(buffer, 0, sizeof buffer);
                index = 0;
            }
        }
        if(strcmp(buffer, "dauhrao") == 0){
            lflag = 1;
            tok.token = DAUHRAO_FOR;
            strcpy(tok.desc,"for");
            tok.cflag = 0;
            tok.lflag = 1;
            memset(buffer, 0, sizeof buffer);
            tcount++;
            index = 0;
            lexemes[tcount]  = tok ;
        }
        if(strcmp(buffer,"    ") == 0 ||strcmp(buffer,"\t") == 0 || ch == '\t'){
            indc++;
            memset(buffer, 0, sizeof buffer);
            index = 0;
        }
        else if(linechar == 0 && isalpha(ch) && lflag == 1){
            indc--;
            tok.token = DAUH_ENDFOR;
            strcpy(tok.desc,"efor");
            tok.lflag = 0;
            tok.cflag = 0;
            tcount++;            
            lexemes[tcount]  = tok ;
        }
        else if(lflag == 1){
            if(strcmp(buffer," se ") == 0){
                tok.token = SE_RANGE;
                strcpy(tok.desc,"to");
                tok.lflag = 1;
                tok.cflag = 0;
                tcount++;
                lexemes[tcount]  = tok ;
            }
            else if(strcmp(buffer,"baar") == 0){
                memset(buffer, 0, sizeof buffer);
                index = 0;
            }
        }
        if(strcmp(buffer,"ank ") == 0){
            dvflag = 1;
            strcpy(tok.desc,"ank");
            tok.token = ANK_INT;
            tok.cflag = cflag;
            tok.lflag = lflag;
            memset(buffer, 0, sizeof buffer);
            index = 0;
            tcount++;
            lexemes[tcount]  = tok ;
        }
        else if(strcmp(buffer,"shabd ") == 0){
            dvflag = 1;
            strcpy(tok.desc,"shbd");
            tok.token = SHABD_STR;
            memset(buffer, 0, sizeof buffer);
            index = 0;
            tok.cflag = cflag;
            tok.lflag = lflag;
            tcount++;
            lexemes[tcount]  = tok ;
        }
        else if(strcmp(buffer,"sachai ") == 0){
            dvflag = 1;
            strcpy(tok.desc,"sach");
            tok.token = SACHAI_BOOL;
            memset(buffer, 0, sizeof buffer);
            index = 0;
        }
        else if(dvflag == 1 && strcmp(type,"sachai") == 0){
            //CODE REMAINING TO DETERMINE BOOLEAN VALUE
        }
        else if(dvflag == 1){
            if(ch == ' '){//WHY NOT JUST USE ONE CONDITION WITH AND THO-
                strcpy(tok.desc,buffer);
                dvflag = 0;
                memset(buffer, 0, sizeof buffer);
                index = 0;
                tok.lflag = lflag;
                tok.cflag = cflag;
                tcount++;
                lexemes[tcount]  = tok ;
            }
        }
        if(ch == '$' && dvflag == 0){
            memset(buffer, 0, sizeof buffer);
            index = 0;
            vflag = 1;  
        }
        else if(!isalnum(ch) && vflag == 1){
            strcpy(tok.desc,buffer);
            //printf("VARIABLE: %s\n",buffer);
            memset(buffer, 0, sizeof buffer);
            index = 0;
            vflag = 0;
            tok.lflag = lflag;
            tok.cflag = cflag;
            tcount++;
            lexemes[tcount]  = tok ;
        }
        else if(isdigit(ch)){//NUMBER
            if(sflag == 0){
                if(iflag == 0){//AGAIN, USE THE SAME PARENT IF PLEASE
                    iflag = 1;
                    memset(buffer, 0, sizeof buffer);
                    index = 0;
                }
            }
        }
        else if(!isdigit(ch) && iflag == 1){
            iflag = 0;
            tok.token = INT_CONST;
            strcpy(tok.desc,buffer);
            tok.lflag = lflag;
            tok.cflag = cflag;
            memset(buffer, 0, sizeof buffer);
            index = 0;
            tcount++;
            lexemes[tcount]  = tok ;
        }
        if(ch == '+' || ch == '-'||ch == '*'||ch == '/'||ch == '%'){
            tok.token = ARITH_OPERAT;
            strcpy("OP",tok.desc);//CHANGE THIS
            tok.cflag = cflag;
            tok.lflag = lflag;
            tcount++;
            lexemes[tcount]  = tok ;            
        }
        else if(ch=='('){
            if(isalpha(script[count-1])){
                tok.token = LPAREN;
                strcpy(tok.desc,"lp");
                tok.cflag = cflag;
                tok.lflag = lflag;
                tcount++;
                lexemes[tcount]  = tok ;                
            }
            else{
                pflag=1;
                tok.token = PUNCT;
                strcpy(tok.desc,"pnc");
                tok.cflag = cflag;
                tok.lflag = lflag;
                memset(buffer, 0, sizeof buffer);
                index = 0;             
                tcount++;   
                lexemes[tcount]  = tok ;
            }
        }
        else if(ch =='"'){
            if(sflag == 0){//start string
                memset(buffer, 0, sizeof buffer);
                index = 0;
                sflag = 1;
                count+=1;
                continue;
            }
            else if(sflag == 1){//end string
                tok.token = STR_CONST;
                strcpy(tok.desc,"str");
                tok.cflag = cflag;
                tok.lflag = lflag;
                memset(buffer, 0, sizeof buffer);
                index=0;
                sflag = 0;
                tcount++;
                lexemes[tcount]  = tok ;
            }
        }
        else if(ch == '\n'){
            newline++;
            printf("[%d]\n",newline);
            memset(buffer, 0, sizeof buffer);
            index = 0;
            linechar = 0;
            count+=1;
            break;
        }
        else if(ch == '\0'){
            break;
        }
        buffer[index] = ch;
        index+=1;
        count+=1;
        linechar+=1;
        //printf("%c\n",ch);
        //printf("buffer: %s\n",buffer);
    }
    return lexemes;
}
