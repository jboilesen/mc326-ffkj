#include "configs.h"

int toUpper( char *string ) {

    int cont=0;

    while( *string != '\0' ){
        if( *string >= 'a' && *string <= 'z' ){
            *string -= 32;
            cont++;
        }
        string++;
    }
    return cont;
}



char *getConfig(char *inf){
    char *auxStr;
    int numChars,flag;
    FILE *p;
    p = fopen("ini.conf","r");
    if (!p){
        return NULL;
    }
    numChars = fileStringSize(p,' ');
    auxStr = (char*)malloc(sizeof(char)*(numChars+1));
    toUpper(inf);
    flag = 0;
    while (fscanf(p,"%s",auxStr)!=EOF){
        toUpper(auxStr);
        if (strcmp(auxStr,inf)==0) flag = 1;
        numChars = fileStringSize(p,'\n');
        free(auxStr);
        auxStr = (char*)malloc(sizeof(char)*(numChars+1));
        fscanf(p,"%s",auxStr);
        if (flag == 1) return auxStr;
        free(auxStr);
    }
    return NULL;
}

char ***loadMessages(char *lang){
    char ***allMessages,*filePath,auxChar;
    int sizeLangStr,numMessages,numErrors,i,j;
    FILE *p;//*p_aux;
    /*verifica se o parametro passado eh valido*/
    sizeLangStr = strlen(lang);
    if (sizeLangStr!=4){
        return NULL;
    }
    /*monta o caminho do arquivo*/
    filePath = (char*)malloc(sizeof(char)*LANGFILEPATHSIZE);
    filePath[0]='\0';
    strcat(filePath,"../lang/");
    strcat(filePath,lang);
    strcat(filePath,".lan");
    printf("filePath->%s\n",filePath);
    p = fopen(filePath,"r");
    if (!p){
        return NULL;
    }

    /*verifica o numero de mensagens contido no texto segundo o cabecalho*/
    fscanf(p,"%d",&numMessages);
    if (numMessages<=0){
        return NULL;
    }
    /*caminha at� o final da linha*/
    do{
        auxChar = getc(p);
    }while(auxChar != '\n');
    /*verifica o numero de mensagens de erro segundo o cabecalho*/
    fscanf(p,"%d",&numErrors);
    if (numErrors<=0){
        return NULL;
    }
    /*caminha at� o final da linha*/
    do{
        auxChar = getc(p);
    }while(auxChar != '\n');
    /*agora comeca a leitura, entao ja reserva o espaco para os dois vetores de vetores de caracteres*/
    allMessages = (char***)malloc(sizeof(char**)*2);
    /*reserva o espa�o para cada vetor de vetores de caracteres*/
    allMessages[MSG] = (char**)malloc(sizeof(char*)*(numMessages+2));
    allMessages[ERR] = (char**)malloc(sizeof(char*)*(numErrors+2));
    allMessages[MSG][numMessages+1] = NULL;
    allMessages[ERR][numErrors+1] = NULL;
    allMessages[ERR][0] = (char*)malloc(sizeof(char));
    allMessages[MSG][0] = (char*)malloc(sizeof(char));     
    allMessages[MSG][0][0] = (char)numMessages;
    allMessages[ERR][0][0] = (char)numErrors;
    for (i=1; i < (numMessages+1); i++ ){
        allMessages[MSG][i] = (char*)malloc(sizeof(char)*(fileStringSize(p,'\n')+2));
        j = 0;
        do{
            auxChar = getc(p);
            allMessages[MSG][i][j] = auxChar;
            j++;
        }while (auxChar!='\n');
        allMessages[MSG][i][j]='\0';
    }
    for (i=1; i < (numErrors+1); i++ ){
        allMessages[ERR][i] = (char*)malloc(sizeof(char)*(fileStringSize(p,'\n')+2));
        j = 0;
        do{
            auxChar = getc(p);
            allMessages[ERR][i][j] = auxChar;
            j++;
        }while (auxChar!='\n');
        allMessages[ERR][i][j]='\0';
    }
    return allMessages;
}

void printMsg(char ***allMessages, int typeId, int msgId){
    int auxSize;
    if ((typeId==MSG)||(typeId==ERR)){
        auxSize = (int)allMessages[typeId][0][0];
        printf("auxSize -> %d\n",auxSize);
        if ((msgId>0)&&(msgId<=auxSize)){
            printf("%s",allMessages[typeId][msgId]);
        }
    }
}

int fileStringSize(FILE *p,char sep){
    int count = 0;
    char aux;
    while (((aux = getc(p))!='\n')&&(aux!=EOF)&&(aux!=sep)&&(aux!='\r')){
        count++;
    }
    switch (aux){
        case EOF: 
            fseek(p,-(count),SEEK_CUR);
            break;
        case '\n':
            fseek(p,-(count+2),SEEK_CUR);
            break;
        default:
            fseek(p,-(count+1),SEEK_CUR);
            break;
    }
    return count;
}
