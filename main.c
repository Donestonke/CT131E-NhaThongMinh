#include <stdio.h>
int main(){

//Read file command
    FILE *fh;
    fh = fopen("spine.txt", "r");

    if(fh != NULL){
        char c;
        while( (c = fgetc(fh)) != EOF){
            putchar(c);
        }
    } else( printf(" Can't find file") );
    
    return 0;
}