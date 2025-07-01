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

// Trạng thái đèn hành lang
int lightsOn, middleLightsOn, leftLightsOn, rightLightsOn = 0;

// Trạng thái các thiết bị
int systemPowerOn = 1;
int powerCutOffActive = 0;
int totalDevices = 0;
int bathroomWaterOn = 0;
int livingRoomTVOn = 0;
int livingRoomLightOn, kitchenLightOn, bathroomLightOn, garageLightOn, bedroomLightOn, storageLightOn = 0;
int livingRoomACOn, bedroomACon = 0;
int kitchenVentOn, bathroomVentOn, garageVentOn, storageVentOn = 0;
int livingRoomDevicesOn, kitchenDevicesOn, BedroomDevicesOn, GarageDevicesOn, StorageDevicesOn, BathroomDevicesOn = 0;

int savedLightsOn, savedMiddleLightsOn, savedLeftLightsOn, savedRightLightsOn;
int savedLivingRoomTVOn, savedLivingRoomLightOn, savedLivingRoomACOn;
int savedKitchenLightOn, savedKitchenVentOn;
int savedBedroomLightOn, savedBedroomACon;
int savedGarageLightOn, savedGarageVentOn;
int savedBathroomLightOn, savedBathroomVentOn, savedBathroomWaterOn;
int savedStorageLightOn, savedStorageVentOn;
 
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
    lightsOn = (middleLightsOn && rightLightsOn && leftLightsOn) ? 1 : 0;
    livingRoomDevicesOn = (livingRoomACOn && livingRoomLightOn && livingRoomTVOn) ? 1 : 0;
    kitchenDevicesOn = (kitchenLightOn && kitchenVentOn) ? 1 : 0;
    BedroomDevicesOn = (bedroomACon && bedroomLightOn) ? 1 : 0;
    StorageDevicesOn = (storageLightOn && storageVentOn) ? 1 : 0;
    BathroomDevicesOn = (bathroomLightOn && bathroomVentOn && bathroomWaterOn) ? 1 : 0;
    GarageDevicesOn = (garageLightOn && garageVentOn) ? 1 : 0;
    totalDevices = (middleLightsOn && rightLightsOn && leftLightsOn && livingRoomACOn && livingRoomLightOn && livingRoomTVOn && kitchenLightOn && kitchenVentOn && bedroomACon && bedroomLightOn && storageLightOn && storageVentOn && bathroomLightOn && bathroomVentOn && bathroomWaterOn && garageLightOn && garageVentOn)? 1 : 0;
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
    middleLightsOn = !middleLightsOn;
     if(middleLightsOn){
        clearAtPositions(MiddleHallway, 7, "🟡");
    }else{
        printAtPositions(MiddleHallway, 7, "⚪");
    } TripleONOFF();
}
void LeftONOFF(){
    if(IfPowerOff()) return;
    leftLightsOn = !leftLightsOn;
     if(leftLightsOn){
        clearAtPositions(LeftHallway, 5, "🟡");
    }else{
        printAtPositions(LeftHallway, 5, "⚪");
    } TripleONOFF();
}
void RightONOFF(){
    if(IfPowerOff()) return;
    rightLightsOn = !rightLightsOn;
     if(rightLightsOn){
        clearAtPositions(RightHallway, 5, "🟡");
    }else{
        printAtPositions(RightHallway, 5, "⚪");
    } TripleONOFF();
}
void toggleAllLights() {
    if(IfPowerOff()) return;
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
    if(IfPowerOff()) return;
    livingRoomLightOn = !livingRoomLightOn;
    if(livingRoomLightOn){
        printColorAtPosition(livingRoomLightPos, 1, "Light", 14); // Bật - màu vàng
    } else {
        printColorAtPosition(livingRoomLightPos, 1, "Light", 7); // Tắt - màu trắng
    } TripleONOFF();
}
void toggleLivingRoomTV(){
    if(IfPowerOff()) return;
    livingRoomTVOn = !livingRoomTVOn;
    if(livingRoomTVOn){
        printColorAtPosition(LivingroomTVPos, 1, "TV", 10);
    }else{
        printColorAtPosition(LivingroomTVPos, 1, "TV", 7);
    } TripleONOFF();
}
void toggleLivingRoomAC(){
    if(IfPowerOff()) return;
    livingRoomACOn = !livingRoomACOn;
    if(livingRoomACOn){
        printColorAtPosition(LivingRoomacPos, 1, "AC", 11);
    }else{
        printColorAtPosition(LivingRoomacPos, 1, "AC", 7);
    } TripleONOFF();
}
void toggleLivingRoomDevices(){
    if(IfPowerOff()) return;
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

//Toggle function for kitchen
void toggleKitchenLight(){
    if(IfPowerOff()) return;
    kitchenLightOn = !kitchenLightOn;
    if(kitchenLightOn){
        printColorAtPosition(kitchenLightPos, 1, "Light", 14);
    }else{
        printColorAtPosition(kitchenLightPos, 1, "Light", 7);
    } TripleONOFF();
}
void toggleKitchenVent(){
    if(IfPowerOff()) return;
    kitchenVentOn = !kitchenVentOn;
    if(kitchenVentOn){
        printColorAtPosition(kitchenVentPos, 1, "CH", 5);
    }else{
        printColorAtPosition(kitchenVentPos, 1, "CH", 7);
    } TripleONOFF();
}
void toggleKitchenDevices(){
    if(IfPowerOff()) return;
    if(kitchenDevicesOn){
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
    bedroomLightOn = !bedroomLightOn;
    if(bedroomLightOn){
        printColorAtPosition(BedroomLightPos, 1, "Light", 14);
    }else{
        printColorAtPosition(BedroomLightPos, 1, "Light", 7);
    } TripleONOFF();
}
void toggleBedroomAC(){
    if(IfPowerOff()) return;
    bedroomACon = !bedroomACon;
    if(bedroomACon){
        printColorAtPosition(BedRoomACPos, 1, "AC", 11);
    }else{
        printColorAtPosition(BedRoomACPos, 1, "AC", 7);
    } TripleONOFF();
}
void toggleBedroomDevices(){
    if(IfPowerOff()) return;
    if(BedroomDevicesOn){
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
    garageLightOn = !garageLightOn;
    if(garageLightOn){
        printColorAtPosition(GarageLightPos, 1, "Light", 14);
    }else{
        printColorAtPosition(GarageLightPos, 1, "Light", 7);
    } TripleONOFF();
}
void toggleGarageVent(){
    if(IfPowerOff()) return;
    garageVentOn = !garageVentOn;
    if(garageVentOn){
        printColorAtPosition(garageVentPos, 1, "CH", 5);
    }else{
        printColorAtPosition(garageVentPos, 1, "CH", 7);
    } TripleONOFF();
}
void toggleGarageDevices(){
    if(IfPowerOff()) return;
    if(GarageDevicesOn){
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
    bathroomLightOn = !bathroomLightOn;
    if(bathroomLightOn){
        printColorAtPosition(bathroomLightPos, 1, "Light", 14); 
    } else {
        printColorAtPosition(bathroomLightPos, 1, "Light", 7); 
    } TripleONOFF();
}
void toggleBathroomCH(){
    if(IfPowerOff()) return;
    bathroomVentOn = !bathroomVentOn;
    if(bathroomVentOn){
        printColorAtPosition(bathroomVentPos, 1, "CH", 5);
    }else{
        printColorAtPosition(bathroomVentPos, 1, "CH", 7);
    } TripleONOFF();
}
void toggleBathroomWater(){
    if(IfPowerOff()) return;
    bathroomWaterOn = !bathroomWaterOn;
    if(bathroomWaterOn){
        printColorAtPosition(bathroomWaterPos, 1, "Water", 9);
    }else{
        printColorAtPosition(bathroomWaterPos, 1, "Water", 7);
    } TripleONOFF();
}
void toggleBathroomDevices(){
    if(IfPowerOff()) return;
    if(BathroomDevicesOn){
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
    storageLightOn = !storageLightOn;
    if(storageLightOn){
        printColorAtPosition(storageLightPos, 1, "Light", 14);
    }else{
        printColorAtPosition(storageLightPos, 1, "Light", 7);
    } TripleONOFF();
}
void toggleStorageVent(){
    if(IfPowerOff()) return;
    storageVentOn = !storageVentOn;
    if(storageVentOn){
        printColorAtPosition(storageVentPos, 1, "CH", 5);
    }else{
        printColorAtPosition(storageVentPos, 1, "CH", 7);
    } TripleONOFF();
}
void toggleStorageDevices(){
    if(IfPowerOff()) return;
    if(StorageDevicesOn){
        printColorAtPosition(storageLightPos, 1, "Light", 14);
        printColorAtPosition(storageVentPos, 1, "CH", 5);
    }else{
        printColorAtPosition(storageLightPos, 1, "Light", 7);
        printColorAtPosition(storageVentPos, 1, "CH", 7);      
    }
}

void restorePreviousState(){
    // Khôi phục trạng thái trước khi cúp điện
    lightsOn = savedLightsOn;
    middleLightsOn = savedMiddleLightsOn;
    leftLightsOn = savedLeftLightsOn;
    rightLightsOn = savedRightLightsOn;
    livingRoomTVOn = savedLivingRoomTVOn;
    livingRoomLightOn = savedLivingRoomLightOn;
    livingRoomACOn = savedLivingRoomACOn;
    kitchenLightOn = savedKitchenLightOn;
    kitchenVentOn = savedKitchenVentOn;
    bedroomLightOn = savedBedroomLightOn;
    bedroomACon = savedBedroomACon;
    garageLightOn = savedGarageLightOn;
    garageVentOn = savedGarageVentOn;
    bathroomLightOn = savedBathroomLightOn;
    bathroomVentOn = savedBathroomVentOn;
    bathroomWaterOn = savedBathroomWaterOn;
    storageLightOn = savedStorageLightOn;
    storageVentOn = savedStorageVentOn;
    
    // Cập nhật các biến tổng hợp
    TripleONOFF();
    
    // Hiển thị trạng thái đã lưu
    if(lightsOn){
        clearAtPositions(MiddleHallway, 7, "🟡");
        clearAtPositions(LeftHallway, 5, "🟡");
        clearAtPositions(RightHallway, 5, "🟡");
    }else{
        printAtPositions(MiddleHallway, 7, "⚪");
        printAtPositions(LeftHallway, 5, "⚪");
        printAtPositions(RightHallway, 5, "⚪");
    }
    
    // Hiển thị từng thiết bị theo trạng thái đã lưu
    printColorAtPosition(LivingRoomacPos, 1, "AC", savedLivingRoomACOn ? 11 : 7);
    printColorAtPosition(livingRoomLightPos, 1, "Light", savedLivingRoomLightOn ? 14 : 7);
    printColorAtPosition(LivingroomTVPos, 1, "TV", savedLivingRoomTVOn ? 10 : 7);
    printColorAtPosition(kitchenLightPos, 1, "Light", savedKitchenLightOn ? 14 : 7);
    printColorAtPosition(kitchenVentPos, 1, "CH", savedKitchenVentOn ? 5 : 7);
    printColorAtPosition(BedroomLightPos, 1, "Light", savedBedroomLightOn ? 14 : 7);
    printColorAtPosition(BedRoomACPos, 1, "AC", savedBedroomACon ? 11 : 7);
    printColorAtPosition(GarageLightPos, 1, "Light", savedGarageLightOn ? 14 : 7);
    printColorAtPosition(garageVentPos, 1, "CH", savedGarageVentOn ? 5 : 7);
    printColorAtPosition(bathroomWaterPos, 1, "Water", savedBathroomWaterOn ? 9 : 7);
    printColorAtPosition(bathroomLightPos, 1, "Light", savedBathroomLightOn ? 14 : 7);
    printColorAtPosition(bathroomVentPos, 1, "CH", savedBathroomVentOn ? 5 : 7);
    printColorAtPosition(storageLightPos, 1, "Light", savedStorageLightOn ? 14 : 7);
    printColorAtPosition(storageVentPos, 1, "CH", savedStorageVentOn ? 5 : 7);

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
        Sleep(4000);
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
    savedLightsOn = lightsOn;
    savedMiddleLightsOn = middleLightsOn;
    savedLeftLightsOn = leftLightsOn;
    savedRightLightsOn = rightLightsOn;
    savedLivingRoomTVOn = livingRoomTVOn;
    savedLivingRoomLightOn = livingRoomLightOn;
    savedLivingRoomACOn = livingRoomACOn;
    savedKitchenLightOn = kitchenLightOn;
    savedKitchenVentOn = kitchenVentOn;
    savedBedroomLightOn = bedroomLightOn;
    savedBedroomACon = bedroomACon;
    savedGarageLightOn = garageLightOn;
    savedGarageVentOn = garageVentOn;
    savedBathroomLightOn = bathroomLightOn;
    savedBathroomVentOn = bathroomVentOn;
    savedBathroomWaterOn = bathroomWaterOn;
    savedStorageLightOn = storageLightOn;
    savedStorageVentOn = storageVentOn;
    
    // Tắt tất cả thiết bị
    lightsOn = middleLightsOn = leftLightsOn = rightLightsOn = 0;
    livingRoomTVOn = livingRoomLightOn = livingRoomACOn = 0;
    kitchenLightOn = kitchenVentOn = 0;
    bedroomLightOn = bedroomACon = 0;
    garageLightOn = garageVentOn = 0;
    bathroomLightOn = bathroomVentOn = bathroomWaterOn = 0;
    storageLightOn = storageVentOn = 0;
    
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
            }
            
            else if(mode == 1){
                gotoxy(0,24);
                printf("[1]: Hallway");
                printf("\n[2]: Rooms");
                printf("\n[0]: Back to main menu");
            }else if(mode == 11){
                gotoxy(0,24);
                printf("[1]: Turn %s all lights  ", lightsOn ? "off" : "on");
                printf("\n[2]: Turn %s middle lights  ", leftLightsOn ? "off" : "on");
                printf("\n[3]: Turn %s left lights  ", middleLightsOn ? "off" : "on");
                printf("\n[4]: Turn %s right lights  ", rightLightsOn ? "off" : "on");
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
                printf("[1]: Turn %s light  ", livingRoomLightOn ? "off" : "on");
                printf("\n[2]: Turn %s TV ", livingRoomTVOn ? "off" : "on");
                printf("\n[3]: Turn %s AC ", livingRoomACOn ? "off" : "on");
                printf("\n[4]: Turn %s all device ", livingRoomDevicesOn ? "off" : "on");
                printf("\n[0]: Go back");
            }else if(mode == 122){
                gotoxy(0,24);
                printf("[1]: Turn %s light  ", kitchenLightOn ? "off" : "on");
                printf("\n[2]: Turn %s vent ", kitchenVentOn ? "off" : "on");
                printf("\n[3]: Turn %s all devices", kitchenDevicesOn ? "off" : "on");
                printf("\n[0]: Go back");
            }else if(mode == 123){
                gotoxy(0,24);
                printf("[1]: Turn %s light ", garageLightOn ? "off" : "on");
                printf("\n[2]: Turn %s Vent ", garageVentOn ? "off" : "on");
                printf("\n[3]: Turn %s all device ", GarageDevicesOn ? "off" : "on");
                printf("\n[0]: Go back");
            }
            else if(mode == 124){
                gotoxy(0,24);
                printf("[1]: Turn %s light  ", bedroomLightOn ? "off" : "on");
                printf("\n[2]: Turn %s AC ", bedroomACon ? "off" : "on");
                printf("\n[3]: Turn %s all device ", BedroomDevicesOn ? "off" : "on");
                printf("\n[0]: Go back");
            }
            else if(mode == 125){
                gotoxy(0,24);
                printf("[1]: Turn %s light  ", bathroomLightOn ? "off" : "on");
                printf("\n[2]: Turn %s vent  ", bathroomVentOn ? "off" : "on");
                printf("\n[3]: Turn %s water  ", bathroomWaterOn ? "off" : "on");
                printf("\n[4]: Turn %s all device  ", BathroomDevicesOn ? "off" : "on");
                printf("\n[0]: Go back");
            }else if(mode == 126){
                gotoxy(0,24);
                printf("[1]: Turn %s light  ", storageLightOn ? "off" : "on");
                printf("\n[2]: Turn %s vent  ", storageVentOn ? "off" : "on");
                printf("\n[3]: Turn %s all device  ", StorageDevicesOn ? "off" : "on");
                printf("\n[0]: Go back");
            }

            else if(mode == 2){
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
                    if(!leftLightsOn){
                        leftLightsOn = 1;
                         clearAtPositions(LeftHallway, 5, "🟡");
                        }
                        if(!rightLightsOn){
                            rightLightsOn = 1;
                            clearAtPositions(RightHallway, 5, "��");
                        }
                    } else {
                        if(leftLightsOn){
                            leftLightsOn = 0;
                            printAtPositions(LeftHallway, 5, "⚪");
                        }
                        if(rightLightsOn){
                            rightLightsOn = 0;
                            printAtPositions(RightHallway, 5, "⚪");
                        }
                    }
    
                    // Hallway Middle Lights: 17:30 - 23:30
                    if((currentTime >= 1730) && (currentTime < 2330)){
                        if(!middleLightsOn){
                            middleLightsOn = 1;
                            clearAtPositions(MiddleHallway, 7, "🟡");
                        }
                    } else {
                        if(middleLightsOn){
                            middleLightsOn = 0;
                            printAtPositions(MiddleHallway, 7, "⚪");
                        }
                    }
    
                    // AC (Living Room & Bedroom): 21:30 - 06:00
                    if((currentTime >= 2130) || (currentTime < 600)){
                        if(!livingRoomACOn){
                            livingRoomACOn = 1;
                            printColorAtPosition(LivingRoomacPos, 1, "AC", 11);
                        }
                        if(!bedroomACon){
                            bedroomACon = 1;
                            printColorAtPosition(BedRoomACPos, 1, "AC", 11);
                        }
                    } else {
                        if(livingRoomACOn){
                            livingRoomACOn = 0;
                            printColorAtPosition(LivingRoomacPos, 1, "AC", 7);
                        }
                        if(bedroomACon){
                            bedroomACon = 0;
                            printColorAtPosition(BedRoomACPos, 1, "AC", 7);
                        }
                    }
                    
                    // Room Lights: 18:00 - 06:00 (Living Room, Kitchen, Garage, Bedroom, Bathroom, Storage)
                     if((currentTime >= 1800) || (currentTime < 600)){
                        if(!livingRoomLightOn){
                            livingRoomLightOn = 1;
                            printColorAtPosition(livingRoomLightPos, 1, "Light", 14);
                        }
                        if(!kitchenLightOn){
                            kitchenLightOn = 1;
                            printColorAtPosition(kitchenLightPos, 1, "Light", 14);
                        }
                        if(!garageLightOn){
                            garageLightOn = 1;
                            printColorAtPosition(GarageLightPos, 1, "Light", 14);
                        }
                        if(!bedroomLightOn){
                            bedroomLightOn = 1;
                            printColorAtPosition(BedroomLightPos, 1, "Light", 14);
                        }
                        if(!bathroomLightOn){
                            bathroomLightOn = 1;
                            printColorAtPosition(bathroomLightPos, 1, "Light", 14);
                        }
                        if(!storageLightOn){
                            storageLightOn = 1;
                            printColorAtPosition(storageLightPos, 1, "Light", 14);
                        }
                    } else {
                        if(livingRoomLightOn){
                            livingRoomLightOn = 0;
                            printColorAtPosition(livingRoomLightPos, 1, "Light", 7);
                        }
                        if(kitchenLightOn){
                            kitchenLightOn = 0;
                            printColorAtPosition(kitchenLightPos, 1, "Light", 7);
                        }
                        if(garageLightOn){
                            garageLightOn = 0;
                            printColorAtPosition(GarageLightPos, 1, "Light", 7);
                        }
                        if(bedroomLightOn){
                            bedroomLightOn = 0;
                            printColorAtPosition(BedroomLightPos, 1, "Light", 7);
                        }
                        if(bathroomLightOn){
                            bathroomLightOn = 0;
                            printColorAtPosition(bathroomLightPos, 1, "Light", 7);
                        }
                        if(storageLightOn){
                            storageLightOn = 0;
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
                    if(input == '2') mode = 122;
                    if(input == '3') mode = 123;
                    if(input == '4') mode = 124;
                    if(input == '5') mode = 125;
                    if(input == '6') mode = 126;
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
                }else if(mode == 122){
                    if(input == '3'){
                        kitchenDevicesOn = !kitchenDevicesOn;
                        kitchenLightOn = kitchenDevicesOn;
                        kitchenVentOn = kitchenDevicesOn;
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
                        GarageDevicesOn = !GarageDevicesOn;
                        garageLightOn = GarageDevicesOn;
                        garageVentOn = GarageDevicesOn;
                        toggleGarageDevices();
                    }
                    if(input == '0') mode = 12;
                }
                else if(mode == 124){
                    if(input == '3'){
                        BedroomDevicesOn = !BedroomDevicesOn;
                        bedroomLightOn = BedroomDevicesOn;
                        bedroomACon = BedroomDevicesOn;
                        toggleBedroomDevices();
                    }
                    if(input == '1') toggleBedroomLight();
                    if(input == '2') toggleBedroomAC();
                    if(input == '0') mode = 12;
                }
                else if(mode == 125){
                    if(input == '4'){
                        BathroomDevicesOn = !BathroomDevicesOn;
                        bathroomLightOn = BathroomDevicesOn;
                        bathroomVentOn = BathroomDevicesOn;
                        bathroomWaterOn = BathroomDevicesOn;
                        toggleBathroomDevices();
                    }
                    if(input == '0') mode = 12;
                    if(input == '1') toggleBathroomLight();
                    if(input == '2') toggleBathroomCH();
                    if(input == '3') toggleBathroomWater();
                }
                else if(mode == 126){
                    if(input == '3'){
                        StorageDevicesOn = !StorageDevicesOn;
                        storageLightOn = StorageDevicesOn;
                        storageVentOn = StorageDevicesOn;
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
