#include <stdio.h>
#include <stdlib.h>  //để dùng system("cls")
#include <windows.h>  //để dùng gotoxy
#include <conio.h> //Để sử dụng kbhit và getch
#include <time.h> //Để sử dụng các hàm giờ

//Handle for position
void gotoxy(int x, int y){
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//Dùng để in cùng 1 nội dung tại nhiều vị trí
void printAtPositions( int positions[][2], int count, const char* text){
    for(int i = 0; i < count; i++){
        gotoxy( positions[i][0], positions[i][1]);
        printf("%s", text);
    }
}

//Dùng để ghi đè 1 nội dung lên nhiều vị trí
void clearAtPositions(int positions[][2], int count, const char* bruh) {
    for(int i = 0; i < count; i++){
        gotoxy( positions[i][0], positions[i][1]);
        printf("%s", bruh); 
    }
}

void clearMenu(){
    for(int i = 21; i < 25; i++){
    gotoxy(0,i);
    printf("                                     ");
    }
}

int main(){
    //Aane con trỏ
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    //Xóa màn hình
    system("cls");
    int lightsOn = 0;
    char input;

    //Đọc file txt
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

        //Đèn (tắt)
        printAtPositions(MiddleHallway, 7, "⚪");
        printAtPositions(LeftHallway, 5, "⚪");
        printAtPositions(RightHallway, 5, "⚪");

        //Chống nội dung bị chồng lên nhau
        gotoxy(24, 20);
        printf("\n");

        //Main input loop
        int mode = 0;
        while(1){
            static int lastMode = -1;
            if(mode != lastMode){
                clearMenu();
                lastMode = mode;
            }
            if(mode == 0){
                gotoxy(0, 21);
                printf("[1]: Manual Mode");
                printf("\n[2]: Automatic Mode");
                printf("\n[ESC]: Exit");
            }else if(mode == 1){
                gotoxy(0, 21);
                printf("[1]: Turn %s the light", lightsOn ? "off" : "on");
                printf("\n[0]: Back to main menu");
            }else if(mode == 2){
                gotoxy(0, 21);
                printf("Light turns on at 18:00, off at 6:00\n");
                printf("\n[0]: Back to main menu");
            }
            if(kbhit()) {
                input = getch();
                if(input == 27) { // ESC key
                    system("cls");
                    return 0;    
                }
                if (mode == 0){
                    if(input == '1') mode = 1;
                    if(input == '2') mode = 2;
                }
                else if(mode == 1){
                    if(input == '0') mode = 0;   //Ấn 0
                    else if(input == '1'){       //Ấn 1
                        lightsOn = !lightsOn;
                        if(lightsOn){
                            clearAtPositions(MiddleHallway, 7, "🟡");
                            clearAtPositions(LeftHallway, 5, "🟡");
                            clearAtPositions(RightHallway, 5, "🟡");
                        }else{
                            printAtPositions(MiddleHallway, 7, "⚪");
                            printAtPositions(LeftHallway, 5, "⚪");
                            printAtPositions(RightHallway, 5, "⚪");
                        }
                    }
                }
                else if(mode == 2){
                    if(input == '0') mode = 0;
                    // Lấy thời gian hiện tại
                time_t now = time(NULL);
                struct tm *local = localtime(&now);
                int hour = local->tm_hour;

                gotoxy(0,22);
                printf("Current hour: %02d\n", hour);
                if(hour >= 18 || hour < 6){
                    if(!lightsOn){
                        lightsOn = 1;
                        clearAtPositions(MiddleHallway, 7, "🟡");
                        clearAtPositions(LeftHallway, 5, "🟡");
                        clearAtPositions(RightHallway, 5, "🟡");
                    }
                }else if(lightsOn){
                        lightsOn = 0;
                        printAtPositions(MiddleHallway, 7, "⚪");
                        printAtPositions(LeftHallway, 5, "⚪");
                        printAtPositions(RightHallway, 5, "⚪");
                    }
                }
            }
            Sleep(110); //Chống lag hoặc nhấp nháy
        }
    } else {
        printf("Can't find file");
    }
    return 0;
}


