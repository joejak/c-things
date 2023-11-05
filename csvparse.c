#include <stdio.h>

#define MAXCOLS 100
#define MAXLINE 1000
#define DELIMITER ','

int processHeader(); 
void openObj(); 
void closeObj();
void openVal();
void closeVal(); 
int writeKey(int); 

char headers[MAXCOLS][MAXLINE]; 

int ESC = 0; 

int main()
{
    int headerCount = processHeader();
    int currentHeader = 0; 
    printf("%s", "HEADERS {\n");
    for(currentHeader; currentHeader<headerCount; ++currentHeader){
        putchar('\t');
        writeKey(currentHeader);
        putchar(',');
        putchar('\n');
    }
    printf("%s", "}\n---------------------------------\n");
    currentHeader = 0; 
    int c = getchar();
    if(c!=EOF){
        ungetc(c, stdin); 
    }
    openObj();
    writeKey(0);
    putchar(':');
    putchar(' '); 
    openVal();
    while((c=getchar()) != EOF){ 
        switch(c){
            case '\r':
                c = getchar(); 
            case '\n':
                 currentHeader = 0; 
                 ESC = 0; 
                 closeObj();
                 c=getchar(); 
                 if(c==EOF){
                    putchar('\n');
                    return 0; 
                 }
                 ungetc(c, stdin);
                 putchar(','); 
                 putchar('\n');
                 openObj();
                 writeKey(0);
                 putchar(':');
                 putchar(' '); 
                 openVal(); 
                 break; 
            case '\"':
                ESC = (ESC == 0) ? 1 : 0;
                break; 
            case DELIMITER:
                if(ESC==0){
                    closeVal();
                    writeKey(++currentHeader);
                    putchar(':');
                    putchar(' '); 
                    openVal();
                    continue; 
                    break; 
                }      
            default:
                putchar(c);
        }
    }
}

int writeKey(int h){
    int i = 0; 
    while(headers[h][i]!='\0'){
        putchar(headers[h][i++]); 
    }
}

int processHeader(){
    int c;
    int currentHeader = 0; 
    int currentChar = 0; 

    while(currentChar < MAXLINE && currentHeader < MAXCOLS){
        c = getchar(); 
        switch(c){
            case '\r':
                c = getchar(); 
            case '\n':
                headers[currentHeader][currentChar] = '\0';
                return ++currentHeader; 
            case DELIMITER:
                if(ESC==0){
                    headers[currentHeader][currentChar] = '\0';
                    currentChar = 0; 
                    ++currentHeader; 
                    continue; 
                    break; 
                }      
            case '\"':
                ESC = (ESC == 0) ? 1 : 0; 
            default:
                headers[currentHeader][currentChar] = c;
                ++currentChar; 
        }
    }
    return -1; 
}


void closeVal(){
    putchar('\"');
    putchar(',');
    putchar('\n');
    putchar('\t'); 
}

void closeObj(){
    putchar('\"'); 
    putchar('\n'); 
    putchar('}');
}

void openVal(){
    putchar('\"');
}

void openObj(){
    putchar('{'); 
    putchar('\n');
    putchar('\t');  
}