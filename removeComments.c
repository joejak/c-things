#include <stdio.h>

#define OUT 0
#define INLINE 1
#define INBLOCK 2

int next(int, int);

int main()
{
    return next(OUT, getchar());
}

int next(int state, int last){
    if(last == EOF){
        return 0; 
    }
    int current = getchar();
    switch(state){
        case OUT:
            if(last == '/'){
                switch(current){
                    case '/':
                        if(last==current)
                            return next(INLINE, current);
                    break; 
                    case '*':
                        if(last=='/'){
                            return next(INBLOCK, current); 
                        }
                    break;
                    default:
                        putchar(last);
                        return next(OUT, current); 
                }
            }
            else{
                putchar(last); 
                return next(OUT, current); 
            }
        case INLINE:
            if(last == '\n')
                return next(OUT, current); 
        case INBLOCK:
            if(last == '*' && current == '/'){
                return next(OUT, getchar());
            }
        default:
            return next(state, current); 
    }
}