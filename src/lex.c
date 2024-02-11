#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdint.h>
#include<ctype.h>
char *read(FILE *fp){
    size_t fsize;
    char *script;
    //READ FILE SIZE
    fseek(fp,0,SEEK_END);
    fsize = ftell(fp);
    fseek(fp,0,SEEK_SET);
    //ALLOCATE SPACE FOR BUFFER    
    script = malloc(fsize);
    fread(script,fsize,1,fp);
    return script;
}
int main(int argc,char *argv[]){
    FILE *fp;
    int count = 0;
    int index = 0;
    int newline = 0;
    char *script;
    char ch='a';
    char buffer[128];
    char *type = "UNDEF";
    uint8_t indc = 0;//KEEP TRACK OF INDENTS
    
    uint8_t iflag = 0;//NUMBER
    uint8_t sflag = 0;//STRING
    uint8_t pflag = 0;//PAREN
    uint8_t dvflag = 0;//DEFINE VARIABLE
    uint8_t vflag = 0;//VARIABLE
    uint8_t cflag = 0;//CONDITIONAL
    uint8_t lflag = 0;//LOOP
    fp = fopen(argv[1],"r");
    script = read(fp);
    while(ch!='\0'){
        ch = script[count];
        if(strcmp(buffer,"agar ") == 0){
            printf("IF STATE: AGAR\n");
            memset(buffer, 0, sizeof buffer);
            index = 0;
            cflag = 1;
        }
        if(strcmp(buffer," hai") == 0){
            printf("ASSIGN: hai\n");
        }
        else if(cflag == 1){
            if(strcmp(" phir",buffer) == 0){
                memset(buffer, 0, sizeof buffer);
                index = 0;
            }
            if(strcmp(buffer,"    ") == 0 ||strcmp(buffer,"\t") == 0 || ch == '\t'){
                indc++;
                memset(buffer, 0, sizeof buffer);
                index = 0;
            }
            else if(script[count-1] == '\n' && isalpha(ch) && cflag == 1){
                indc--;
                printf("ENDIF: AGAR\n");
                cflag = 0;
            }
        }
        if(strcmp(buffer, "dauhrao") == 0){
            lflag = 1;
            printf("LOOP:DAUHRAO\n");
            memset(buffer, 0, sizeof buffer);
            index = 0;
        }
        if(strcmp(buffer,"    ") == 0 ||strcmp(buffer,"\t") == 0 || ch == '\t'){
            indc++;
            memset(buffer, 0, sizeof buffer);
            index = 0;
        }
        else if(script[count-1] == '\n' && isalpha(ch) && lflag == 1){
            indc--;
            printf("ENDLOOP: DAUHRAO\n");
            lflag = 0;
        }
        else if(lflag == 1){
            if(strcmp(buffer," se ") == 0){
                printf("TO\n");
            }
            else if(strcmp(buffer,"baar") == 0){
                memset(buffer, 0, sizeof buffer);
                index = 0;
            }
        }
        if(strcmp(buffer,"ank ") == 0){
            dvflag = 1;
            type = "ank";
            memset(buffer, 0, sizeof buffer);
            index = 0;
        }
        else if(strcmp(buffer,"shabd ") == 0){
            dvflag = 1;
            type = "shabd";
            memset(buffer, 0, sizeof buffer);
            index = 0;
        }
        else if(strcmp(buffer,"sachai ") == 0){
            dvflag = 1;
            type = "sachai";
            memset(buffer, 0, sizeof buffer);
            index = 0;
        }
        else if(dvflag == 1 && strcmp(type,"sachai") == 0){
            //CODE REMAINING TO DETERMINE BOOLEAN VALUE
        }
        else if(dvflag == 1){
            if(ch == ' '){
                printf("VARIABLE: %s TYPE: %s\n",buffer,type);
                dvflag = 0;
                type = "UNDEF";
                memset(buffer, 0, sizeof buffer);
                index = 0;
            }
        }
        if(ch == '$' && dvflag == 0){
            memset(buffer, 0, sizeof buffer);
            index = 0;
            vflag = 1;  
        }
        else if(!isalnum(ch) && vflag == 1){
            printf("VARIABLE: %s\n",buffer);
            memset(buffer, 0, sizeof buffer);
            index = 0;
            vflag = 0;
        }
        else if(isdigit(ch)){//NUMBER
            if(sflag == 0){
                if(iflag == 0){
                    iflag = 1;
                    memset(buffer, 0, sizeof buffer);
                    index = 0;
                }
            }
        }
        else if(!isdigit(ch) && iflag == 1){
            iflag = 0;
            printf("NUMBER:%s\n",buffer);
            memset(buffer, 0, sizeof buffer);
            index = 0;
        }
        if(ch == '+' || ch == '-'||ch == '*'||ch == '/'||ch == '%'){
            printf("OPERAT: %c\n",ch);
        }
        else if(ch=='('){
            if(isalpha(script[count-1])){
                printf("KEYWORD: %s\n",buffer);                
            }
            pflag=1;
            printf("PUNCTUA: %c\n",ch);
            memset(buffer, 0, sizeof buffer);
            index = 0;
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
                printf("STRING: %s\n",buffer);
                memset(buffer, 0, sizeof buffer);
                index=0;
                sflag = 0;
            }
        }
        else if(ch == '\n'){
            newline++;
            printf("[%d]\n",newline);
            memset(buffer, 0, sizeof buffer);
            index = 0;
            count+=1;
            continue;
        }
        buffer[index] = ch;
        index+=1;
        count+=1;
        //printf("%c\n",ch);
        //printf("buffer: %s\n",buffer);
    }
}