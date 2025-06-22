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
    for(int i = 23; i < 32; i++){
    gotoxy(0,i);
    printf("                                     ");
    }
}

void printColorAtPosition(int position[0][2], int count, const char* text, int color){
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hconsole, color);
    for(int i = 0; i < count; i++){
        gotoxy(position[i][0], position[i][1]);
        printf("%s", text);
    }
    SetConsoleTextAttribute(hconsole, 7);
}

// Trạng thái đèn hành lang
int lightsOn, middleLightsOn, leftLightsOn, rightLightsOn = 0;

// Trạng thái các thiết bị
int livingRoomTVOn = 0;
int livingRoomLightOn = 0, kitchenLightOn = 0, garageLightOn = 0, bedroom2LightOn = 0, bedroom1LightOn = 0, storageLightOn = 0;
int livingRoomACOn = 0;
int livingRoomDevicesOn = 0;

//Middle Hallway
int MiddleHallway [][2] = { {10,11}, {19,11}, {29,11}, {39,11}, {49,11}, {59,11}, {69,11} };

//Left Hallway
int LeftHallway [][2] = { {0,3}, {0,7}, {0,11}, {0,15}, {0,19} };

//Right Hallway
int RightHallway [][2] = { {79,3}, {79,7}, {79,11}, {79,15}, {79,19} };

// Vị trí các đồ đạc
int LivingroomTVPos[][2]    = { {11,17} };
int Bedroom1tTVPos[][2]     = { {70,5} };
int Bedroom2TVPos[][2]      = { {48,17} };
int LivingRoomacPos[][2]    = { {26,17} };
int BedRoom1acPos[][2]      = { {53,5} };
int BedRoom2acPos[][2]      = { {31,17} };
int livingRoomLightPos[][2] = { {17,14} }; 
int kitchenLightPos[][2]    = { {38,14} };    
int garageLightPos[][2]     = { {60,14} }; 
int bedroom2LightPos[][2]   = { {17,2} }; 
int bedroom1LightPos[][2]   = { {38,2} }; 
int storageLightPos[][2]    = { {60,2} }; 

void TripleONOFF(){
    lightsOn = (middleLightsOn && rightLightsOn && leftLightsOn) ? 1 : 0;
    livingRoomDevicesOn = (livingRoomACOn && livingRoomLightOn && livingRoomTVOn) ? 1 : 0;
}

void MiddleONOFF(){
    middleLightsOn = !middleLightsOn;
     if(middleLightsOn){
        clearAtPositions(MiddleHallway, 7, "🟡");
    }else{
        printAtPositions(MiddleHallway, 7, "⚪");
    } TripleONOFF();
}

void LeftONOFF(){
    leftLightsOn = !leftLightsOn;
     if(leftLightsOn){
        clearAtPositions(LeftHallway, 5, "🟡");
    }else{
        printAtPositions(LeftHallway, 5, "⚪");
    } TripleONOFF();
}

void RightONOFF(){
    rightLightsOn = !rightLightsOn;
     if(rightLightsOn){
        clearAtPositions(RightHallway, 5, "🟡");
    }else{
        printAtPositions(RightHallway, 5, "⚪");
    } TripleONOFF();
}

void toggleAllLights() {
    if(lightsOn) {
        clearAtPositions(MiddleHallway, 7, "🟡");
        clearAtPositions(LeftHallway, 5, "🟡");
        clearAtPositions(RightHallway, 5, "🟡");
    } else {
        printAtPositions(MiddleHallway, 7, "⚪");
        printAtPositions(LeftHallway, 5, "⚪");
        printAtPositions(RightHallway, 5, "⚪");
    }
}

//Toggle function for LivingRoom
void toggleLivingRoomLight(){
    livingRoomLightOn = !livingRoomLightOn;
    if(livingRoomLightOn){
        printColorAtPosition(livingRoomLightPos, 1, "Light", 14); // Bật - màu vàng
    } else {
        printColorAtPosition(livingRoomLightPos, 1, "Light", 7); // Tắt - màu trắng
    } TripleONOFF();
}
void toggleLivingRoomTV(){
    livingRoomTVOn = !livingRoomTVOn;
    if(livingRoomTVOn){
        printColorAtPosition(LivingroomTVPos, 1, "TV", 10);
    }else{
        printColorAtPosition(LivingroomTVPos, 1, "TV", 7);
    } TripleONOFF();
}
void toggleLivingRoomAC(){
    livingRoomACOn = !livingRoomACOn;
    if(livingRoomACOn){
        printColorAtPosition(LivingRoomacPos, 1, "AC", 11);
    }else{
        printColorAtPosition(LivingRoomacPos, 1, "AC", 7);
    } TripleONOFF();
}
void toggleLivingRoomDevices(){
    if(livingRoomDevicesOn){
        printColorAtPosition(LivingRoomacPos, 1, "AC", 11);
        printColorAtPosition(livingRoomLightPos, 1, "Light", 14);
        printColorAtPosition(LivingroomTVPos, 1, "TV", 10);
    }else{
        printColorAtPosition(LivingRoomacPos, 1, "AC", 7);
        printColorAtPosition(livingRoomLightPos, 1, "Light", 7);
        printColorAtPosition(LivingroomTVPos, 1, "TV", 7);      
    }
}

int main(){
    //Ẩn con trỏ
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    //Xóa màn hình
    system("cls");
    char input;

    //Đọc file txt
    FILE *fh;
    fh = fopen("spine.txt", "r");

    if(fh != NULL){
        char c;
        while( (c = fgetc(fh)) != EOF) {putchar(c);}
        fclose(fh);

        //Đèn (tắt)
        printAtPositions(MiddleHallway, 7, "⚪");
        printAtPositions(LeftHallway, 5, "⚪");
        printAtPositions(RightHallway, 5, "⚪");

        //Đèn các phòng (tắt)
        printColorAtPosition(livingRoomLightPos, 1, "Light", 7);
        printColorAtPosition(kitchenLightPos, 1, "Light", 7);
        printColorAtPosition(garageLightPos, 1, "Light", 7);
        printColorAtPosition(bedroom1LightPos, 1, "Light", 7);
        printColorAtPosition(bedroom2LightPos, 1, "Light", 7);
        printColorAtPosition(storageLightPos, 1, "Light", 7);

        //Nội thất
        printColorAtPosition(LivingroomTVPos, 1, "TV", 7);
        printColorAtPosition(LivingRoomacPos, 1, "AC", 7);
        printColorAtPosition(BedRoom1acPos, 1, "AC", 7);
        printColorAtPosition(BedRoom2acPos, 1, "AC", 7);

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
                gotoxy(0, 24);
                printf("[1]: Manual Mode");
                printf("\n[2]: Automatic Mode");
                printf("\n[ESC]: Exit");
            }
            
            else if(mode == 1){
                gotoxy(0,24);
                printf("[1]: Hallway");
                printf("\n[2]: Rooms");
                printf("\n[0]: Back to main menu");
            }else if(mode == 11){
                gotoxy(0,24);
                printf("[1]: Turn %s all lights  ", lightsOn ? "off" : "on");
                printf("\n[2]: Turn %s middle lights  ", middleLightsOn ? "off" : "on");
                printf("\n[3]: Turn %s left lights  ", leftLightsOn ? "off" : "on");
                printf("\n[4]: Turn %s right lights  ", rightLightsOn ? "off" : "on");
                printf("\n\n[0]: Go back");
            }else if(mode == 12){
                gotoxy(0,24);
                printf("[1]: Living room\n");
                printf("[2]: Kitchen\n");
                printf("[3]: Garage\n");
                printf("[4]: Bedroom 2\n");
                printf("[5]: Bedroom 1\n");
                printf("[6]: Storage\n");
                printf("\n[0]: Go back");
            }else if(mode == 121){
                gotoxy(0,24);
                printf("[1]: Turn %s light  ", livingRoomLightOn ? "off" : "on");
                printf("\n[2]: Turn %s TV ", livingRoomTVOn ? "off" : "on");
                printf("\n[3]: Turn %s AC ", livingRoomACOn ? "off" : "on");
                printf("\n[F]: Turn %s all device ", livingRoomDevicesOn ? "off" : "on");
                printf("\n[0]: Go back");
            }else if(mode == 2){
                // Lấy thời gian hiện tại
                time_t now = time(NULL);
                struct tm *local = localtime(&now);
                int hour = local->tm_hour;

                gotoxy(0,24);
                printf("Lights turn on at 18:00, off at 6:00\n");
                printf("Current hour: %02dh\n", hour);
                printf("\n[0]: Back to main menu");

                if(hour >= 18 || hour < 6){
                    if(!lightsOn){
                        lightsOn = 1;
                        clearAtPositions(MiddleHallway, 7, "🟡");
                        clearAtPositions(LeftHallway, 5, "🟡");
                        clearAtPositions(RightHallway, 5, "🟡");
                    }else if(!middleLightsOn){
                        middleLightsOn = 1;
                        clearAtPositions(MiddleHallway, 7, "🟡");
                    }else if(leftLightsOn){
                        clearAtPositions(LeftHallway, 5, "🟡");
                    }else if(rightLightsOn){
                        clearAtPositions(RightHallway, 5, "🟡");
                    }
                }else if(lightsOn){
                        lightsOn = 0;
                        printAtPositions(MiddleHallway, 7, "⚪");
                        printAtPositions(LeftHallway, 5, "⚪");
                        printAtPositions(RightHallway, 5, "⚪");
                }else if(middleLightsOn){
                    middleLightsOn = 0;
                    printAtPositions(MiddleHallway, 7, "⚪");
                }else if(leftLightsOn){
                    leftLightsOn = 0;
                    printAtPositions(LeftHallway, 5, "⚪");
                }else if(rightLightsOn){
                    rightLightsOn = 0;
                    printAtPositions(RightHallway, 5, "⚪");
                }
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
                    else if(input == '1') mode = 11;  //Ấn 1 - vào Hallway
                    else if(input == '2') mode = 12;  //Ấn 2 - vào Rooms
                }
                else if(mode == 11){ // Manual Hallway mode
                    if(input == '0') mode = 1;   //Ấn 0 - quay lại manual menu
                    else if(input == '1'){       //Ấn 1
                        lightsOn = !lightsOn;
                        middleLightsOn = lightsOn;
                        leftLightsOn = lightsOn;
                        rightLightsOn = lightsOn;
                        toggleAllLights();
                    }
                    if(input == '2') LeftONOFF();
                    if(input == '3') MiddleONOFF();
                    if(input == '4') RightONOFF();
                }
                else if(mode == 12){ // Manual Rooms mode
                    if(input == '0') mode = 1;   //Ấn 0 - quay lại manual menu
                    if(input == '1') mode = 121;
                }else if(mode == 121){
                    if(input == '4'){
                        livingRoomDevicesOn = !livingRoomDevicesOn;
                        livingRoomTVOn = livingRoomDevicesOn;
                        livingRoomACOn = livingRoomDevicesOn;
                        livingRoomLightOn = livingRoomDevicesOn;
                        toggleLivingRoomDevices();
                    }
                    if(input == '0') mode = 12;
                    if(input == '1') toggleLivingRoomLight();
                    if(input == '2') toggleLivingRoomTV();
                    if(input == '3') toggleLivingRoomAC();
                }
                else if(mode == 2){
                    if(input == '0') mode = 0;
                }
            }
            Sleep(11); //Chống lag hoặc nhấp nháy
        }
    } else {
        printf("Can't find file");
    }
    return 0;
}
