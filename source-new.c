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
    printf("                                                                                                     ");
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

// Trạng thái  thiết bị phòng khách
typedef struct{
    int lightsOn, AcOn, TVOn, devicesOn;
} LivingRoomState;
LivingRoomState livingroom = {0, 0, 0, 0};
LivingRoomState savedlivingroom;

// Trạng thái thiết bị hành lang
typedef struct{
    int lightsOn, middleLightsOn, leftLightsOn, rightLightsOn;
} HallwayState;
HallwayState hallway = {0, 0, 0, 0};
HallwayState savedhallway;

// Trạng thái thiết bị trong nhà bếp
typedef struct{
    int LightOn, VentOn, DevicesOn;
} KitchenState;
KitchenState kitchen = {0, 0};
KitchenState savedkitchen;

// Trạng thái thiết bị trong phòng ngủ
typedef struct{
    int ACOn, LightOn, DevicesOn;
} BedroomState;
BedroomState bedroom = {0, 0, 0};
BedroomState savedbedroom;

//Trạng thái thiết bị trong nhà để xe
typedef struct{
    int LightOn, VentOn, DevicesOn;
} GarageState;
GarageState garage = {0, 0, 0};
GarageState savedgarage;

//trạng thái thiết bị trong nhà tắm
typedef struct{
    int LightOn, VentOn, WaterOn, DevicesOn;
} BathroomState;
BathroomState bathroom = {0, 0, 0, 0};
BathroomState savedbathroom;

//trạng thái các thiết bị trong kho
typedef struct{
    int LightOn, VentOn, DevicesOn;
} StorageState;
StorageState storage = {0, 0, 0};
StorageState savedstorage;

//Biến toàn cục
int systemPowerOn = 1;
int powerCutOffActive = 0;
int totalDevices = 0;
 
//Hallway
int MiddleHallway [][2] = { {10,11}, {20,11}, {30,11}, {40,11}, {50,11}, {60,11}, {70,11} };
int LeftHallway [][2] = { {0,3}, {0,7}, {0,11}, {0,15}, {0,19} };
int RightHallway [][2] = { {79,3}, {79,7}, {79,11}, {79,15}, {79,19} };

// Vị trí các đồ đạc
int LivingroomTVPos[][2]    = { {11,17} };
int livingRoomLightPos[][2] = { {17,14} };
int LivingRoomacPos[][2]    = { {26,17} };

int bathroomWaterPos[][2]     = { {67,5} };
int bathroomLightPos[][2]    = { {60,2} };  
int bathroomVentPos[][2]      = { {70,2} };

int BedRoomACPos[][2]      = { {48,17} };
int BedroomLightPos[][2]    = { {38,14} };  

int kitchenLightPos[][2]   = { {38,2} }; 
int kitchenVentPos[][2]     = { {48,2} };

int garageVentPos[][2]      = { {26,2} };
int GarageLightPos[][2]   = { {17,2} };  

int storageVentPos[][2]     = { {70,14} };
int storageLightPos[][2]     = { {60,14} };  

void TripleONOFF(){
    hallway.lightsOn = (hallway.middleLightsOn && hallway.rightLightsOn && hallway.leftLightsOn) ? 1 : 0;
    livingroom.devicesOn = (livingroom.AcOn && livingroom.lightsOn && livingroom.TVOn) ? 1 : 0;
    kitchen.DevicesOn = (kitchen.LightOn && kitchen.VentOn) ? 1 : 0;
    bedroom.DevicesOn = (bedroom.ACOn && bedroom.LightOn) ? 1 : 0;
    storage.DevicesOn = (storage.LightOn && storage.VentOn) ? 1 : 0;
    bathroom.DevicesOn = (bathroom.LightOn && bathroom.VentOn && bathroom.WaterOn) ? 1 : 0;
    garage.DevicesOn = (garage.LightOn && garage.VentOn) ? 1 : 0;
    totalDevices = (hallway.middleLightsOn && hallway.rightLightsOn && hallway.leftLightsOn && livingroom.AcOn && livingroom.lightsOn && livingroom.TVOn && kitchen.LightOn && kitchen.VentOn && bedroom.ACOn && bedroom.LightOn && storage.LightOn && storage.VentOn && bathroom.LightOn && bathroom.VentOn && bathroom.WaterOn && garage.LightOn && garage.VentOn)? 1 : 0;
}

int IfPowerOff(){
    if(!systemPowerOn) {
        clearMenu();
        gotoxy(0, 24);
        printf("⚠️  SYSTEM POWER IS OFF!");
        printf("\nRestore power first to use devices.");
        Sleep(1500);
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        clearMenu();
        return 1;
    } return 0;
}
//Toggle function for Hallway
void MiddleONOFF(){
    if(IfPowerOff()) return;
    hallway.middleLightsOn = !hallway.middleLightsOn;
     if(hallway.middleLightsOn){
        clearAtPositions(MiddleHallway, 7, "🟡");
    }else{
        printAtPositions(MiddleHallway, 7, "⚪");
    } TripleONOFF();
}
void LeftONOFF(){
    if(IfPowerOff()) return;
    hallway.leftLightsOn = !hallway.leftLightsOn;
     if(hallway.leftLightsOn){
        clearAtPositions(LeftHallway, 5, "🟡");
    }else{
        printAtPositions(LeftHallway, 5, "⚪");
    } TripleONOFF();
}
void RightONOFF(){
    if(IfPowerOff()) return;
    hallway.rightLightsOn = !hallway.rightLightsOn;
     if(hallway.rightLightsOn){
        clearAtPositions(RightHallway, 5, "🟡");
    }else{
        printAtPositions(RightHallway, 5, "⚪");
    } TripleONOFF();
}
void toggleAllLights() {
    if(IfPowerOff()) return;
    if(hallway.lightsOn) {
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
    if(IfPowerOff()) return;
    livingroom.lightsOn = !livingroom.lightsOn;
    if(livingroom.lightsOn){
        printColorAtPosition(livingRoomLightPos, 1, "Light", 14); // Bật - màu vàng
    } else {
        printColorAtPosition(livingRoomLightPos, 1, "Light", 7); // Tắt - màu trắng
    } TripleONOFF();
}
void toggleLivingRoomTV(){
    if(IfPowerOff()) return;
    livingroom.TVOn = !livingroom.TVOn;
    if(livingroom.TVOn){
        printColorAtPosition(LivingroomTVPos, 1, "TV", 10);
    }else{
        printColorAtPosition(LivingroomTVPos, 1, "TV", 7);
    } TripleONOFF();
}
void toggleLivingRoomAC(){
    if(IfPowerOff()) return;
    livingroom.AcOn = !livingroom.AcOn;
    if(livingroom.AcOn){
        printColorAtPosition(LivingRoomacPos, 1, "AC", 11);
    }else{
        printColorAtPosition(LivingRoomacPos, 1, "AC", 7);
    } TripleONOFF();
}
void toggleLivingRoomDevices(){
    if(IfPowerOff()) return;
    if(livingroom.devicesOn){
        printColorAtPosition(LivingRoomacPos, 1, "AC", 11);
        printColorAtPosition(livingRoomLightPos, 1, "Light", 14);
        printColorAtPosition(LivingroomTVPos, 1, "TV", 10);
    }else{
        printColorAtPosition(LivingRoomacPos, 1, "AC", 7);
        printColorAtPosition(livingRoomLightPos, 1, "Light", 7);
        printColorAtPosition(LivingroomTVPos, 1, "TV", 7);      
    }
}

//Toggle function for kitchen
void toggleKitchenLight(){
    if(IfPowerOff()) return;
    kitchen.LightOn = !kitchen.LightOn;
    if(kitchen.LightOn){
        printColorAtPosition(kitchenLightPos, 1, "Light", 14);
    }else{
        printColorAtPosition(kitchenLightPos, 1, "Light", 7);
    } TripleONOFF();
}
void toggleKitchenVent(){
    if(IfPowerOff()) return;
    kitchen.VentOn = !kitchen.VentOn;
    if(kitchen.VentOn){
        printColorAtPosition(kitchenVentPos, 1, "CH", 5);
    }else{
        printColorAtPosition(kitchenVentPos, 1, "CH", 7);
    } TripleONOFF();
}
void toggleKitchenDevices(){
    if(IfPowerOff()) return;
    if(kitchen.DevicesOn){
        printColorAtPosition(kitchenLightPos, 1, "Light", 14);
        printColorAtPosition(kitchenVentPos, 1, "CH", 5);
    }else{
        printColorAtPosition(kitchenLightPos, 1, "Light", 7);
        printColorAtPosition(kitchenVentPos, 1, "CH", 7);      
    }
}

//Toggle function for bedroom
void toggleBedroomLight(){
    if(IfPowerOff()) return;
    bedroom.LightOn = !bedroom.LightOn;
    if(bedroom.LightOn){
        printColorAtPosition(BedroomLightPos, 1, "Light", 14);
    }else{
        printColorAtPosition(BedroomLightPos, 1, "Light", 7);
    } TripleONOFF();
}
void toggleBedroomAC(){
    if(IfPowerOff()) return;
    bedroom.ACOn = !bedroom.ACOn;
    if(bedroom.ACOn){
        printColorAtPosition(BedRoomACPos, 1, "AC", 11);
    }else{
        printColorAtPosition(BedRoomACPos, 1, "AC", 7);
    } TripleONOFF();
}
void toggleBedroomDevices(){
    if(IfPowerOff()) return;
    if(bedroom.DevicesOn){
        printColorAtPosition(BedroomLightPos, 1, "Light", 14);
        printColorAtPosition(BedRoomACPos, 1, "AC", 11);
    }else{
        printColorAtPosition(BedroomLightPos, 1, "Light", 7);
        printColorAtPosition(BedRoomACPos, 1, "AC", 7);      
    }
}

//Toggle function for Garage
void toggleGarageLight(){
    if(IfPowerOff()) return;
    garage.LightOn = !garage.LightOn;
    if(garage.LightOn){
        printColorAtPosition(GarageLightPos, 1, "Light", 14);
    }else{
        printColorAtPosition(GarageLightPos, 1, "Light", 7);
    } TripleONOFF();
}
void toggleGarageVent(){
    if(IfPowerOff()) return;
    garage.VentOn = !garage.VentOn;
    if(garage.VentOn){
        printColorAtPosition(garageVentPos, 1, "CH", 5);
    }else{
        printColorAtPosition(garageVentPos, 1, "CH", 7);
    } TripleONOFF();
}
void toggleGarageDevices(){
    if(IfPowerOff()) return;
    if(garage.DevicesOn){
        printColorAtPosition(GarageLightPos, 1, "Light", 14);
        printColorAtPosition(garageVentPos, 1, "CH", 5);
    }else{
        printColorAtPosition(GarageLightPos, 1, "Light", 7);
        printColorAtPosition(garageVentPos, 1, "CH", 7);      
    }
}

//Toggle function for Bathroom
void toggleBathroomLight(){
    if(IfPowerOff()) return;
    bathroom.LightOn = !bathroom.LightOn;
    if(bathroom.LightOn){
        printColorAtPosition(bathroomLightPos, 1, "Light", 14); 
    } else {
        printColorAtPosition(bathroomLightPos, 1, "Light", 7); 
    } TripleONOFF();
}
void toggleBathroomCH(){
    if(IfPowerOff()) return;
    bathroom.VentOn = !bathroom.VentOn;
    if(bathroom.VentOn){
        printColorAtPosition(bathroomVentPos, 1, "CH", 5);
    }else{
        printColorAtPosition(bathroomVentPos, 1, "CH", 7);
    } TripleONOFF();
}
void toggleBathroomWater(){
    if(IfPowerOff()) return;
    bathroom.WaterOn = !bathroom.WaterOn;
    if(bathroom.WaterOn){
        printColorAtPosition(bathroomWaterPos, 1, "Water", 9);
    }else{
        printColorAtPosition(bathroomWaterPos, 1, "Water", 7);
    } TripleONOFF();
}
void toggleBathroomDevices(){
    if(IfPowerOff()) return;
    if(bathroom.DevicesOn){
        printColorAtPosition(bathroomWaterPos, 1, "Water", 9);
        printColorAtPosition(bathroomLightPos, 1, "Light", 14);
        printColorAtPosition(bathroomVentPos, 1, "CH", 5);
    }else{
        printColorAtPosition(bathroomWaterPos, 1, "Water", 7);
        printColorAtPosition(bathroomLightPos, 1, "Light", 7);
        printColorAtPosition(bathroomVentPos, 1, "CH", 7);      
    }
}

//Toggle function for Storage
void toggleStorageLight(){
    if(IfPowerOff()) return;
    storage.LightOn = !storage.LightOn;
    if(storage.LightOn){
        printColorAtPosition(storageLightPos, 1, "Light", 14);
    }else{
        printColorAtPosition(storageLightPos, 1, "Light", 7);
    } TripleONOFF();
}
void toggleStorageVent(){
    if(IfPowerOff()) return;
    storage.VentOn = !storage.VentOn;
    if(storage.VentOn){
        printColorAtPosition(storageVentPos, 1, "CH", 5);
    }else{
        printColorAtPosition(storageVentPos, 1, "CH", 7);
    } TripleONOFF();
}
void toggleStorageDevices(){
    if(IfPowerOff()) return;
    if(storage.DevicesOn){
        printColorAtPosition(storageLightPos, 1, "Light", 14);
        printColorAtPosition(storageVentPos, 1, "CH", 5);
    }else{
        printColorAtPosition(storageLightPos, 1, "Light", 7);
        printColorAtPosition(storageVentPos, 1, "CH", 7);      
    }
}

void restorePreviousState(){
    // Khôi phục trạng thái trước khi cúp điện
    hallway = savedhallway;
    livingroom = savedlivingroom;
    kitchen = savedkitchen;
    bedroom = savedbedroom;
    garage = savedgarage;
    bathroom = savedbathroom;
    storage = savedstorage;
    
    // Cập nhật các biến tổng hợp
    TripleONOFF();
    
    // Hiển thị trạng thái đã lưu
    if(hallway.lightsOn){
        clearAtPositions(MiddleHallway, 7, "🟡");
        clearAtPositions(LeftHallway, 5, "🟡");
        clearAtPositions(RightHallway, 5, "🟡");
    }else{
        printAtPositions(MiddleHallway, 7, "⚪");
        printAtPositions(LeftHallway, 5, "⚪");
        printAtPositions(RightHallway, 5, "⚪");
    }
    
    // Hiển thị từng thiết bị theo trạng thái đã lưu
    printColorAtPosition(LivingRoomacPos, 1, "AC", savedlivingroom.AcOn ? 11 : 7);
    printColorAtPosition(livingRoomLightPos, 1, "Light", savedlivingroom.lightsOn ? 14 : 7);
    printColorAtPosition(LivingroomTVPos, 1, "TV", savedlivingroom.TVOn ? 10 : 7);
    printColorAtPosition(kitchenLightPos, 1, "Light", savedkitchen.LightOn ? 14 : 7);
    printColorAtPosition(kitchenVentPos, 1, "CH", savedkitchen.VentOn ? 5 : 7);
    printColorAtPosition(BedroomLightPos, 1, "Light", savedbedroom.LightOn ? 14 : 7);
    printColorAtPosition(BedRoomACPos, 1, "AC", savedbedroom.ACOn ? 11 : 7);
    printColorAtPosition(GarageLightPos, 1, "Light", savedgarage.LightOn ? 14 : 7);
    printColorAtPosition(garageVentPos, 1, "CH", savedgarage.VentOn ? 5 : 7);
    printColorAtPosition(bathroomWaterPos, 1, "Water", savedbathroom.WaterOn ? 9 : 7);
    printColorAtPosition(bathroomLightPos, 1, "Light", savedbathroom.LightOn ? 14 : 7);
    printColorAtPosition(bathroomVentPos, 1, "CH", savedbathroom.VentOn ? 5 : 7);
    printColorAtPosition(storageLightPos, 1, "Light", savedstorage.LightOn ? 14 : 7);
    printColorAtPosition(storageVentPos, 1, "CH", savedstorage.VentOn ? 5 : 7);

    systemPowerOn = 1;
    powerCutOffActive = 0;
    
    clearMenu();
}

//Toggle function for all Devices
void cutOffAllPower(){
if(powerCutOffActive) {
        clearMenu();
        gotoxy(0, 24);
        printf("Bro really try to cut off power again 🙏💔");
        printf("\nYou are insane dude");
        Sleep(3000);
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        printf("\n\n[1]: Restore Previous State");
        printf("\n[ESC]: Continue with power off");
        // Chờ người dùng chọn
        char choice;
        while(1){
            if(kbhit()){
                choice = getch();
                if(choice == '1'){
                    clearMenu();
                    restorePreviousState();
                    break;
                }else if(choice == 27){ // ESC
                    clearMenu();
                    break;
                }
            }
            Sleep(10);
        }
        return;
    }

    powerCutOffActive = 1;
    // Lưu trạng thái hiện tại trước khi tắt
    savedhallway = hallway;
    savedlivingroom = livingroom;
    savedkitchen = kitchen;
    savedbedroom = bedroom;
    savedgarage = garage;
    savedbathroom = bathroom;
    savedstorage = storage;
    
    // Tắt tất cả thiết bị
    hallway.lightsOn = hallway.middleLightsOn = hallway.leftLightsOn = hallway.rightLightsOn = 0;
    livingroom.lightsOn, livingroom.AcOn, livingroom.TVOn, livingroom.devicesOn = 0;
    kitchen.LightOn = kitchen.VentOn = 0;
    bedroom.LightOn = bedroom.ACOn = 0;
    garage.LightOn = garage.VentOn = 0;
    bathroom.LightOn = bathroom.VentOn = bathroom.WaterOn = 0;
    storage.LightOn = storage.VentOn = 0;
    
    // Cập nhật các biến tổng hợp
    TripleONOFF();
    
    // Hiển thị tất cả thiết bị ở trạng thái TẮT
    printAtPositions(MiddleHallway, 7, "⚪");
    printAtPositions(LeftHallway, 5, "⚪");
    printAtPositions(RightHallway, 5, "⚪");
    
    printColorAtPosition(LivingRoomacPos, 1, "AC", 7);
    printColorAtPosition(livingRoomLightPos, 1, "Light", 7);
    printColorAtPosition(LivingroomTVPos, 1, "TV", 7);
    printColorAtPosition(kitchenLightPos, 1, "Light", 7);
    printColorAtPosition(kitchenVentPos, 1, "CH", 7);
    printColorAtPosition(BedroomLightPos, 1, "Light", 7);
    printColorAtPosition(BedRoomACPos, 1, "AC", 7);
    printColorAtPosition(GarageLightPos, 1, "Light", 7);
    printColorAtPosition(garageVentPos, 1, "CH", 7);
    printColorAtPosition(bathroomWaterPos, 1, "Water", 7);
    printColorAtPosition(bathroomLightPos, 1, "Light", 7);
    printColorAtPosition(bathroomVentPos, 1, "CH", 7);
    printColorAtPosition(storageLightPos, 1, "Light", 7);
    printColorAtPosition(storageVentPos, 1, "CH", 7);

    systemPowerOn = 0;
    // Hiển thị thông báo và menu khôi phục
    clearMenu();
    gotoxy(0, 24);
    printf("⚠️  ALL POWER CUT OFF! ⚠️");
    printf("\nAll devices have been turned off.");
    printf("\n\n[1]: Restore Power");
    printf("\n[ESC]: Continue with power off");
    
    // Chờ người dùng chọn
    char choice;
    while(1){
        if(kbhit()){
            choice = getch();
            if(choice == '1'){
                restorePreviousState();
                break;
            }else if(choice == 27){ // ESC
                powerCutOffActive = 1;
                clearMenu();
                break;
            }
        }
        Sleep(110);
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
        printColorAtPosition(GarageLightPos, 1, "Light", 7);
        printColorAtPosition(bathroomLightPos, 1, "Light", 7);
        printColorAtPosition(BedroomLightPos, 1, "Light", 7);
        printColorAtPosition(storageLightPos, 1, "Light", 7);

        //Nội thất
        printColorAtPosition(LivingroomTVPos, 1, "TV", 7);
        printColorAtPosition(LivingRoomacPos, 1, "AC", 7);
        printColorAtPosition(bathroomVentPos, 1, "CH", 7);
        printColorAtPosition(bathroomWaterPos, 1, "Water", 7);
        printColorAtPosition(BedRoomACPos, 1, "AC", 7);
        printColorAtPosition(kitchenVentPos, 1, "CH", 7);
        printColorAtPosition(garageVentPos, 1, "CH", 7);
        printColorAtPosition(storageVentPos, 1, "CH", 7);

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
                printf("\n\n[4]: HETCUU");
                if(powerCutOffActive){
                    gotoxy(0,29);
                    printf("[5]: Restore power");
                }
            }
            
            else if(mode == 1){
                gotoxy(0,24);
                printf("[1]: Hallway");
                printf("\n[2]: Rooms");
                printf("\n[0]: Back to main menu");
            }else if(mode == 11){
                gotoxy(0,24);
                printf("[1]: Turn %s all lights  ", hallway.lightsOn ? "off" : "on");
                printf("\n[2]: Turn %s middle lights  ", hallway.leftLightsOn ? "off" : "on");
                printf("\n[3]: Turn %s left lights  ", hallway.middleLightsOn ? "off" : "on");
                printf("\n[4]: Turn %s right lights  ", hallway.rightLightsOn ? "off" : "on");
                printf("\n\n[0]: Go back");
            }else if(mode == 12){
                gotoxy(0,24);
                printf("[1]: Living room\n");
                printf("[2]: Kitchen\n");
                printf("[3]: Garage\n");
                printf("[4]: Bedroom\n");
                printf("[5]: Bathroom\n");
                printf("[6]: Storage\n");
                printf("\n[0]: Go back");
            }else if(mode == 121){
                gotoxy(0,24);
                printf("[1]: Turn %s light  ", livingroom.lightsOn ? "off" : "on");
                printf("\n[2]: Turn %s TV ", livingroom.TVOn ? "off" : "on");
                printf("\n[3]: Turn %s AC ", livingroom.AcOn ? "off" : "on");
                printf("\n[4]: Turn %s all device ", livingroom.devicesOn ? "off" : "on");
                printf("\n[0]: Go back");
            }else if(mode == 122){
                gotoxy(0,24);
                printf("[1]: Turn %s light  ", kitchen.LightOn ? "off" : "on");
                printf("\n[2]: Turn %s vent ", kitchen.VentOn ? "off" : "on");
                printf("\n[3]: Turn %s all devices", kitchen.DevicesOn ? "off" : "on");
                printf("\n[0]: Go back");
            }else if(mode == 123){
                gotoxy(0,24);
                printf("[1]: Turn %s light ", garage.LightOn ? "off" : "on");
                printf("\n[2]: Turn %s Vent ", garage.VentOn ? "off" : "on");
                printf("\n[3]: Turn %s all device ", garage.DevicesOn ? "off" : "on");
                printf("\n[0]: Go back");
            }
            else if(mode == 124){
                gotoxy(0,24);
                printf("[1]: Turn %s light  ", bedroom.LightOn ? "off" : "on");
                printf("\n[2]: Turn %s AC ", bedroom.ACOn ? "off" : "on");
                printf("\n[3]: Turn %s all device ", bedroom.DevicesOn ? "off" : "on");
                printf("\n[0]: Go back");
            }
            else if(mode == 125){
                gotoxy(0,24);
                printf("[1]: Turn %s light  ", bathroom.LightOn ? "off" : "on");
                printf("\n[2]: Turn %s vent  ", bathroom.VentOn ? "off" : "on");
                printf("\n[3]: Turn %s water  ", bathroom.WaterOn ? "off" : "on");
                printf("\n[4]: Turn %s all device  ", bathroom.DevicesOn ? "off" : "on");
                printf("\n[0]: Go back");
            }else if(mode == 126){
                gotoxy(0,24);
                printf("[1]: Turn %s light  ", storage.LightOn ? "off" : "on");
                printf("\n[2]: Turn %s vent  ", storage.VentOn ? "off" : "on");
                printf("\n[3]: Turn %s all device  ", storage.DevicesOn ? "off" : "on");
                printf("\n[0]: Go back");
            }
            else if(mode == 2){
                if(powerCutOffActive) {
                    clearMenu();
                    gotoxy(0, 24);
                    printf("⚠️  SYSTEM POWER IS OFF!");
                    printf("\nRestore power first to use.");
                    printf("\n\n[0]: Back to main menu");
                    // Đợi người dùng bấm phím 0 để quay lại menu chính
                    char ch;
                    while(1){
                        if(kbhit()){
                            ch = getch();
                            if(ch == '0' || ch == 27) { // 0 hoặc ESC đều quay lại menu chính
                                mode = 0;
                                break;
                            }
                        }
                        Sleep(10);
                    }
                    clearMenu();
                    continue;
                }
                // Lấy thời gian hiện tại
                time_t now = time(NULL);
                struct tm *local = localtime(&now);
                int hour = local->tm_hour;
                int minute = local->tm_min;
                int currentTime = hour * 100 + minute; 

                gotoxy(0,24);
                printf("Automatic Mode - Device Schedules:");printf("\nHallway Left/Right: 18:30-05:30");
                printf("\nHallway Middle: 17:30-23:30");
                printf("\nAC: 21:30-06:00");
                printf("\nRoom Lights: 18:00-06:00");
                printf("\nCurrent time: %02d:%02d", hour, minute);
                printf("\n\n[0]: Back to main menu");
    
                // Hallway Left/Right Lights: 18:30 - 05:30
                if((currentTime >= 1830) || (currentTime < 530)){
                    if(!hallway.leftLightsOn){
                        hallway.leftLightsOn = 1;
                         clearAtPositions(LeftHallway, 5, "🟡");
                        }
                        if(!hallway.rightLightsOn){
                            hallway.rightLightsOn = 1;
                            clearAtPositions(RightHallway, 5, "🟡");
                        }
                    } else {
                        if(hallway.leftLightsOn){
                            hallway.leftLightsOn = 0;
                            printAtPositions(LeftHallway, 5, "⚪");
                        }
                        if(hallway.rightLightsOn){
                            hallway.rightLightsOn = 0;
                            printAtPositions(RightHallway, 5, "⚪");
                        }
                    }
    
                    // Hallway Middle Lights: 17:30 - 23:30
                    if((currentTime >= 1730) && (currentTime < 2330)){
                        if(!hallway.middleLightsOn){
                            hallway.middleLightsOn = 1;
                            clearAtPositions(MiddleHallway, 7, "🟡");
                        }
                    } else {
                        if(hallway.middleLightsOn){
                            hallway.middleLightsOn = 0;
                            printAtPositions(MiddleHallway, 7, "⚪");
                        }
                    }
    
                    // AC (Living Room & Bedroom): 21:30 - 06:00
                    if((currentTime >= 2130) || (currentTime < 600)){
                        if(!livingroom.AcOn){
                            livingroom.AcOn = 1;
                            printColorAtPosition(LivingRoomacPos, 1, "AC", 11);
                        }
                        if(!bedroom.ACOn){
                            bedroom.ACOn = 1;
                            printColorAtPosition(BedRoomACPos, 1, "AC", 11);
                        }
                    } else {
                        if(livingroom.AcOn){
                            livingroom.AcOn = 0;
                            printColorAtPosition(LivingRoomacPos, 1, "AC", 7);
                        }
                        if(bedroom.ACOn){
                            bedroom.ACOn = 0;
                            printColorAtPosition(BedRoomACPos, 1, "AC", 7);
                        }
                    }
                    
                    // Room Lights: 18:00 - 06:00 (Living Room, Kitchen, Garage, Bedroom, Bathroom, Storage)
                     if((currentTime >= 1800) || (currentTime < 600)){
                        if(!livingroom.lightsOn){
                            livingroom.lightsOn = 1;
                            printColorAtPosition(livingRoomLightPos, 1, "Light", 14);
                        }
                        if(!kitchen.LightOn){
                            kitchen.LightOn = 1;
                            printColorAtPosition(kitchenLightPos, 1, "Light", 14);
                        }
                        if(!garage.LightOn){
                            garage.LightOn = 1;
                            printColorAtPosition(GarageLightPos, 1, "Light", 14);
                        }
                        if(!bedroom.LightOn){
                            bedroom.LightOn = 1;
                            printColorAtPosition(BedroomLightPos, 1, "Light", 14);
                        }
                        if(!bathroom.LightOn){
                            bathroom.LightOn = 1;
                            printColorAtPosition(bathroomLightPos, 1, "Light", 14);
                        }
                        if(!storage.LightOn){
                            storage.LightOn = 1;
                            printColorAtPosition(storageLightPos, 1, "Light", 14);
                        }
                    } else {
                        if(livingroom.lightsOn){
                            livingroom.lightsOn = 0;
                            printColorAtPosition(livingRoomLightPos, 1, "Light", 7);
                        }
                        if(kitchen.LightOn){
                            kitchen.LightOn = 0;
                            printColorAtPosition(kitchenLightPos, 1, "Light", 7);
                        }
                        if(garage.LightOn){
                            garage.LightOn = 0;
                            printColorAtPosition(GarageLightPos, 1, "Light", 7);
                        }
                        if(bedroom.LightOn){
                            bedroom.LightOn = 0;
                            printColorAtPosition(BedroomLightPos, 1, "Light", 7);
                        }
                        if(bathroom.LightOn){
                            bathroom.LightOn = 0;
                            printColorAtPosition(bathroomLightPos, 1, "Light", 7);
                        }
                        if(storage.LightOn){
                            storage.LightOn = 0;
                            printColorAtPosition(storageLightPos, 1, "Light", 7);
                        }
                    } TripleONOFF();
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
                    if(input == '4'){
                        cutOffAllPower();
                    }
                    if(powerCutOffActive){
                    if(input == '5') restorePreviousState();
                    }
                }
                else if(mode == 1){
                    if(input == '0') mode = 0;   //Ấn 0
                    else if(input == '1') mode = 11;  //Ấn 1 - vào Hallway
                    else if(input == '2') mode = 12;  //Ấn 2 - vào Rooms
                }
                else if(mode == 11){ // Manual Hallway mode
                    if(input == '0') mode = 1;   //Ấn 0 - quay lại manual menu
                    else if(input == '1'){       //Ấn 1
                        hallway.lightsOn = !hallway.lightsOn;
                        hallway.middleLightsOn = hallway.lightsOn;
                        hallway.leftLightsOn = hallway.lightsOn;
                        hallway.rightLightsOn = hallway.lightsOn;
                        toggleAllLights();
                    }
                    if(input == '2') LeftONOFF();
                    if(input == '3') MiddleONOFF();
                    if(input == '4') RightONOFF();
                }
                else if(mode == 12){ // Manual Rooms mode
                    if(input == '0') mode = 1;   //Ấn 0 - quay lại manual menu
                    if(input == '1') mode = 121;
                    if(input == '2') mode = 122;
                    if(input == '3') mode = 123;
                    if(input == '4') mode = 124;
                    if(input == '5') mode = 125;
                    if(input == '6') mode = 126;
                }else if(mode == 121){
                    if(input == '4'){
                        livingroom.devicesOn = !livingroom.devicesOn;
                        livingroom.TVOn = livingroom.devicesOn;
                        livingroom.AcOn = livingroom.devicesOn;
                        livingroom.lightsOn = livingroom.devicesOn;
                        toggleLivingRoomDevices();
                    }
                    if(input == '0') mode = 12;
                    if(input == '1') toggleLivingRoomLight();
                    if(input == '2') toggleLivingRoomTV();
                    if(input == '3') toggleLivingRoomAC();
                }else if(mode == 122){
                    if(input == '3'){
                        kitchen.DevicesOn = !kitchen.DevicesOn;
                        kitchen.LightOn = kitchen.DevicesOn;
                        kitchen.VentOn = kitchen.DevicesOn;
                        toggleKitchenDevices();
                    }
                    if(input == '0') mode = 12;
                    if(input == '1') toggleKitchenLight();
                    if(input == '2') toggleKitchenVent();
                    }
                else if(mode == 123){
                    if(input == '1') toggleGarageLight();
                    if(input == '2') toggleGarageVent();
                    if(input == '3'){
                        garage.DevicesOn = !garage.DevicesOn;
                        garage.LightOn = garage.DevicesOn;
                        garage.VentOn = garage.DevicesOn;
                        toggleGarageDevices();
                    }
                    if(input == '0') mode = 12;
                }
                else if(mode == 124){
                    if(input == '3'){
                        bedroom.DevicesOn = !bedroom.DevicesOn;
                        bedroom.LightOn = bedroom.DevicesOn;
                        bedroom.ACOn = bedroom.DevicesOn;
                        toggleBedroomDevices();
                    }
                    if(input == '1') toggleBedroomLight();
                    if(input == '2') toggleBedroomAC();
                    if(input == '0') mode = 12;
                }
                else if(mode == 125){
                    if(input == '4'){
                        bathroom.DevicesOn = !bathroom.DevicesOn;
                        bathroom.LightOn = bathroom.DevicesOn;
                        bathroom.VentOn = bathroom.DevicesOn;
                        bathroom.WaterOn = bathroom.DevicesOn;
                        toggleBathroomDevices();
                    }
                    if(input == '0') mode = 12;
                    if(input == '1') toggleBathroomLight();
                    if(input == '2') toggleBathroomCH();
                    if(input == '3') toggleBathroomWater();
                }
                else if(mode == 126){
                    if(input == '3'){
                        storage.DevicesOn = !storage.DevicesOn;
                        storage.LightOn = storage.DevicesOn;
                        storage.VentOn = storage.DevicesOn;
                        toggleStorageDevices();
                    }
                    if(input == '0') mode = 12;
                    if(input == '1') toggleStorageLight();
                    if(input == '2') toggleStorageVent();
                }

                   //Timer mode
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
