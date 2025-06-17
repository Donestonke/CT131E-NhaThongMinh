#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//Handle for position
void gotoxy(int x, int y){
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void printAtPositions( int positions[][2], int count, const char* text){
    for(int i = 0; i < count; i++){
        gotoxy( positions[i][0], positions[i][1]);
        printf("%s", text);
    }
}

int main(){
system("cls");

    //Read file command
    FILE *fh;
    fh = fopen("spine.txt", "r");

    if(fh != NULL){
        char c;
        while( (c = fgetc(fh)) != EOF){
            putchar(c);
        }
        fclose(fh);
        
        //Middle Hallway
        int MiddleHallway [][2] = {
            {10,10}, {19,10}, {29,10}, {39,10}, {49,10}, {59,10}, {69,10}
        };

        //Left Hallway
         int LeftHallway [][2] = {
            {0,2}, {0,6}, {0,10}, {0,14}, {0,18}
        };

        //Right Hallway
        int RightHallway [][2] = {
            {79,2}, {79,6}, {79,10}, {79,14}, {79,18}
        };

        //PrintLight
        printAtPositions(MiddleHallway, 7, "Light");
        printAtPositions(LeftHallway, 5, "Light");
        printAtPositions(RightHallway, 5, "Light");

        //Prevent stacked content
        gotoxy(24, 24);
        printf("\n");

    } else {
        printf("Can't find file");
    }
    
    return 0;
}