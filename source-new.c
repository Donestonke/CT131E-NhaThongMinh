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

void printColorAtPosition(int position[][2], int count, const char* text, int color){
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hconsole, color);
    for(int i = 0; i < count; i++){
        gotoxy(position[i][0], position[i][1]);
        printf("%s", text);
    }
    SetConsoleTextAttribute(hconsole, 7);
}

// Trạng thái  thiết bị phòng khách
typedef struct {
    // Hallway
    int hallwayLightsOn, hallwayMiddleLightsOn, hallwayLeftLightsOn, hallwayRightLightsOn;
    
    // Living Room
    int livingRoomLightsOn, livingRoomAcOn, livingRoomTVOn, livingRoomDevicesOn;
    
    // Kitchen
    int kitchenLightOn, kitchenVentOn, kitchenDevicesOn;
    
    // Bedroom
    int bedroomLightOn, bedroomAcOn, bedroomDevicesOn;
    
    // Garage
    int garageLightOn, garageVentOn, garageDevicesOn;
    
    // Bathroom
    int bathroomLightOn, bathroomVentOn, bathroomWaterOn, bathroomDevicesOn;
    
    // Storage
    int storageLightOn, storageVentOn, storageDevicesOn;
    
    // System
    int systemPowerOn, powerCutOffActive, totalDevices;
} SmartHomeState;

SmartHomeState home = {0}; // Khởi tạo tất cả = 0
SmartHomeState savedHome;

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

typedef struct{
    int* state;
    int (*position)[2];
    int count;
    const char* name;
    int colorON;
    int colorOFF;
} Device;

void updateDeviceStatus(Device* device){
    int color = *(device->state) ? device->colorON : device->colorOFF;
    printColorAtPosition(device->position, device->count, device->name, color);
}

// Khai báo các thiết bị
Device livingRoomLight = {&home.livingRoomLightsOn, livingRoomLightPos, 1, "Light", 14, 7};
Device livingRoomTV = {&home.livingRoomTVOn, LivingroomTVPos, 1, "TV", 10, 7};
Device livingRoomAC = {&home.livingRoomAcOn, LivingRoomacPos, 1, "AC", 11, 7};

Device kitchenLight = {&home.kitchenLightOn, kitchenLightPos, 1, "Light", 14, 7};
Device kitchenVent = {&home.kitchenVentOn, kitchenVentPos, 1, "CH", 5, 7};

Device bedroomLight = {&home.bedroomLightOn, BedroomLightPos, 1, "Light", 14, 7};
Device bedroomAC = {&home.bedroomAcOn, BedRoomACPos, 1, "AC", 11, 7};

Device garageLight = {&home.garageLightOn, GarageLightPos, 1, "Light", 14, 7};
Device garageVent = {&home.garageVentOn, garageVentPos, 1, "CH", 5, 7};

Device bathroomLight = {&home.bathroomLightOn, bathroomLightPos, 1, "Light", 14, 7};
Device bathroomVent = {&home.bathroomVentOn, bathroomVentPos, 1, "CH", 5, 7};
Device bathroomWater = {&home.bathroomWaterOn, bathroomWaterPos, 1, "Water", 9, 7};

Device storageLight = {&home.storageLightOn, storageLightPos, 1, "Light", 14, 7};
Device storageVent = {&home.storageVentOn, storageVentPos, 1, "CH", 5, 7};

void TripleONOFF(){
    home.hallwayLightsOn = (home.hallwayMiddleLightsOn && home.hallwayRightLightsOn && home.hallwayLeftLightsOn) ? 1 : 0;
    home.livingRoomDevicesOn = (home.livingRoomAcOn && home.livingRoomLightsOn && home.livingRoomTVOn) ? 1 : 0;
    home.kitchenDevicesOn = (home.kitchenLightOn && home.kitchenVentOn) ? 1 : 0;
    home.bedroomDevicesOn = (home.bedroomAcOn && home.bedroomLightOn) ? 1 : 0;
    home.storageDevicesOn = (home.storageLightOn && home.storageVentOn) ? 1 : 0;
    home.bathroomDevicesOn = (home.bathroomLightOn && home.bathroomVentOn && home.bathroomWaterOn) ? 1 : 0;
    home.garageDevicesOn = (home.garageLightOn && home.garageVentOn) ? 1 : 0;
    home.totalDevices = (home.hallwayMiddleLightsOn && home.hallwayRightLightsOn && home.hallwayLeftLightsOn && home.livingRoomAcOn && home.livingRoomLightsOn && home.livingRoomTVOn && home.kitchenLightOn && home.kitchenVentOn && home.bedroomAcOn && home.bedroomLightOn && home.storageLightOn && home.storageVentOn && home.bathroomLightOn && home.bathroomVentOn && home.bathroomWaterOn && home.garageLightOn && home.garageVentOn)? 1 : 0;
}

int IfPowerOff(){
    if(!home.systemPowerOn) {
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
    home.hallwayMiddleLightsOn = !home.hallwayMiddleLightsOn;
     if(home.hallwayMiddleLightsOn){
        clearAtPositions(MiddleHallway, 7, "🟡");
    }else{
        printAtPositions(MiddleHallway, 7, "⚪");
    } TripleONOFF();
}
void LeftONOFF(){
    if(IfPowerOff()) return;
    home.hallwayLeftLightsOn = !home.hallwayLeftLightsOn;
     if(home.hallwayLeftLightsOn){
        clearAtPositions(LeftHallway, 5, "🟡");
    }else{
        printAtPositions(LeftHallway, 5, "⚪");
    } TripleONOFF();
}
void RightONOFF(){
    if(IfPowerOff()) return;
    home.hallwayRightLightsOn = !home.hallwayRightLightsOn;
     if(home.hallwayRightLightsOn){
        clearAtPositions(RightHallway, 5, "🟡");
    }else{
        printAtPositions(RightHallway, 5, "⚪");
    } TripleONOFF();
}
void toggleAllLights() {
    if(IfPowerOff()) return;
    if(home.hallwayLightsOn) {
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
    home.livingRoomLightsOn = !home.livingRoomLightsOn;
    updateDeviceStatus(&livingRoomLight);
    TripleONOFF();
}
void toggleLivingRoomTV(){
    if(IfPowerOff()) return;
    home.livingRoomTVOn = !home.livingRoomTVOn;
    updateDeviceStatus(&livingRoomTV);
    TripleONOFF();
}
void toggleLivingRoomAC(){
    if(IfPowerOff()) return;
    home.livingRoomAcOn = !home.livingRoomAcOn;
    updateDeviceStatus(&livingRoomAC);
    TripleONOFF();
}
void toggleLivingRoomDevices(){
    if(IfPowerOff()) return;
    updateDeviceStatus(&livingRoomLight);
    updateDeviceStatus(&livingRoomTV);
    updateDeviceStatus(&livingRoomAC);
}

//Toggle function for kitchen
void toggleKitchenLight(){
    if(IfPowerOff()) return;
    home.kitchenLightOn = !home.kitchenLightOn;
    updateDeviceStatus(&kitchenLight);
    TripleONOFF();
}
void toggleKitchenVent(){
    if(IfPowerOff()) return;
    home.kitchenVentOn = !home.kitchenVentOn;
    updateDeviceStatus(&kitchenVent);
    TripleONOFF();
}
void toggleKitchenDevices(){
    if(IfPowerOff()) return;
    updateDeviceStatus(&kitchenLight);
    updateDeviceStatus(&kitchenVent);
}

//Toggle function for bedroom
void toggleBedroomLight(){
    if(IfPowerOff()) return;
    home.bedroomLightOn = !home.bedroomLightOn;
    updateDeviceStatus(&bedroomLight);
    TripleONOFF();
}
void toggleBedroomAC(){
    if(IfPowerOff()) return;
    home.bedroomAcOn = !home.bedroomAcOn;
    updateDeviceStatus(&bedroomAC);
    TripleONOFF();
}
void toggleBedroomDevices(){
    if(IfPowerOff()) return;
    updateDeviceStatus(&bedroomLight);
    updateDeviceStatus(&bedroomAC);
}

//Toggle function for Garage
void toggleGarageLight(){
    if(IfPowerOff()) return;
    home.garageLightOn = !home.garageLightOn;
    updateDeviceStatus(&garageLight);
    TripleONOFF();
}
void toggleGarageVent(){
    if(IfPowerOff()) return;
    home.garageVentOn = !home.garageVentOn;
    updateDeviceStatus(&garageVent);
    TripleONOFF();
}
void toggleGarageDevices(){
    if(IfPowerOff()) return;
    updateDeviceStatus(&garageLight);
    updateDeviceStatus(&garageVent);
}

//Toggle function for Bathroom
void toggleBathroomLight(){
    if(IfPowerOff()) return;
    home.bathroomLightOn = !home.bathroomLightOn;
    updateDeviceStatus(&bathroomLight);
    TripleONOFF();
}
void toggleBathroomCH(){
    if(IfPowerOff()) return;
    home.bathroomVentOn = !home.bathroomVentOn;
    updateDeviceStatus(&bathroomVent);
    TripleONOFF();
}
void toggleBathroomWater(){
    if(IfPowerOff()) return;
    home.bathroomWaterOn = !home.bathroomWaterOn;
    updateDeviceStatus(&bathroomWater);
    TripleONOFF();
}
void toggleBathroomDevices(){
    if(IfPowerOff()) return;
    updateDeviceStatus(&bathroomLight);
    updateDeviceStatus(&bathroomVent);
    updateDeviceStatus(&bathroomWater);
}

//Toggle function for Storage
void toggleStorageLight(){
    if(IfPowerOff()) return;
    home.storageLightOn = !home.storageLightOn;
    updateDeviceStatus(&storageLight);
    TripleONOFF();
}
void toggleStorageVent(){
    if(IfPowerOff()) return;
    home.storageVentOn = !home.storageVentOn;
    updateDeviceStatus(&storageVent);
    TripleONOFF();
}
void toggleStorageDevices(){
    if(IfPowerOff()) return;
    updateDeviceStatus(&storageLight);
    updateDeviceStatus(&storageVent);
}

void restorePreviousState(){
    // Khôi phục trạng thái trước khi cúp điện
    home = savedHome;
    
    // Cập nhật các biến tổng hợp
    TripleONOFF();
    
    // Hiển thị trạng thái đã lưu
    if(home.hallwayLightsOn){
        clearAtPositions(MiddleHallway, 7, "🟡");
        clearAtPositions(LeftHallway, 5, "🟡");
        clearAtPositions(RightHallway, 5, "🟡");
    }else{
        printAtPositions(MiddleHallway, 7, "⚪");
        printAtPositions(LeftHallway, 5, "⚪");
        printAtPositions(RightHallway, 5, "⚪");
    }
    
    // Hiển thị từng thiết bị theo trạng thái đã lưu
    updateDeviceStatus(&livingRoomLight);
    updateDeviceStatus(&livingRoomTV);
    updateDeviceStatus(&livingRoomAC);
    updateDeviceStatus(&kitchenLight);
    updateDeviceStatus(&kitchenVent);
    updateDeviceStatus(&bedroomLight);
    updateDeviceStatus(&bedroomAC);
    updateDeviceStatus(&garageLight);
    updateDeviceStatus(&garageVent);
    updateDeviceStatus(&bathroomLight);
    updateDeviceStatus(&bathroomVent);
    updateDeviceStatus(&bathroomWater);
    updateDeviceStatus(&storageLight);
    updateDeviceStatus(&storageVent);
    

    home.systemPowerOn = 1;
    home.powerCutOffActive = 0;
    
    clearMenu();
}

//Toggle function for all Devices
void cutOffAllPower(){
if(home.powerCutOffActive) {
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

    home.powerCutOffActive = 1;
    // Lưu trạng thái hiện tại trước khi tắt
    savedHome = home;
    
    // Tắt tất cả thiết bị
    home.hallwayLightsOn = home.hallwayMiddleLightsOn = home.hallwayLeftLightsOn = home.hallwayRightLightsOn = 0;
    home.livingRoomLightsOn = home.livingRoomAcOn = home.livingRoomTVOn = home.livingRoomDevicesOn = 0;
    home.kitchenLightOn = home.kitchenVentOn = home.kitchenDevicesOn = 0;
    home.bedroomLightOn = home.bedroomAcOn = home.bedroomDevicesOn = 0;
    home.garageLightOn = home.garageVentOn = home.garageDevicesOn = 0;
    home.bathroomLightOn = home.bathroomVentOn = home.bathroomWaterOn = home.bathroomDevicesOn = 0;
    home.storageLightOn = home.storageVentOn = home.storageDevicesOn = 0;
    
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

    home.systemPowerOn = 0;
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
                home.powerCutOffActive = 1;
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

    // ✅ Khởi tạo trạng thái hệ thống ban đầu
    home.systemPowerOn = 1; // Bật nguồn hệ thống
    home.powerCutOffActive = 0; // Chưa cúp điện

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
                if(home.powerCutOffActive){
                    gotoxy(0,29);
                    printf("[5]: Restore power");
                }
            }
            
            else if(mode == 1){
                gotoxy(0,24);
                printf("[1]: Hallway");
                printf("\n[2]: Rooms");
                printf("\n\n[0]: Back to main menu");
            }else if(mode == 11){
                gotoxy(0,24);
                printf("[1]: Turn %s all lights  ", home.hallwayLightsOn ? "off" : "on");
                printf("\n[2]: Turn %s middle lights  ", home.hallwayLeftLightsOn ? "off" : "on");
                printf("\n[3]: Turn %s left lights  ", home.hallwayMiddleLightsOn ? "off" : "on");
                printf("\n[4]: Turn %s right lights  ", home.hallwayRightLightsOn ? "off" : "on");
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
                printf("[1]: Turn %s light  ", home.livingRoomLightsOn ? "off" : "on");
                printf("\n[2]: Turn %s TV ", home.livingRoomTVOn ? "off" : "on");
                printf("\n[3]: Turn %s AC ", home.livingRoomAcOn ? "off" : "on");
                printf("\n[4]: Turn %s all device ", home.livingRoomDevicesOn ? "off" : "on");
                printf("\n[0]: Go back");
            }else if(mode == 122){
                gotoxy(0,24);
                printf("[1]: Turn %s light  ", home.kitchenLightOn ? "off" : "on");
                printf("\n[2]: Turn %s vent ", home.kitchenVentOn ? "off" : "on");
                printf("\n[3]: Turn %s all devices", home.kitchenDevicesOn ? "off" : "on");
                printf("\n[0]: Go back");
            }else if(mode == 123){
                gotoxy(0,24);
                printf("[1]: Turn %s light ", home.garageLightOn ? "off" : "on");
                printf("\n[2]: Turn %s Vent ", home.garageVentOn ? "off" : "on");
                printf("\n[3]: Turn %s all device ", home.garageDevicesOn ? "off" : "on");
                printf("\n[0]: Go back");
            }
            else if(mode == 124){
                gotoxy(0,24);
                printf("[1]: Turn %s light  ", home.bedroomLightOn ? "off" : "on");
                printf("\n[2]: Turn %s AC ", home.bedroomAcOn ? "off" : "on");
                printf("\n[3]: Turn %s all device ", home.bedroomDevicesOn ? "off" : "on");
                printf("\n[0]: Go back");
            }
            else if(mode == 125){
                gotoxy(0,24);
                printf("[1]: Turn %s light  ", home.bathroomLightOn ? "off" : "on");
                printf("\n[2]: Turn %s vent  ", home.bathroomVentOn ? "off" : "on");
                printf("\n[3]: Turn %s water  ", home.bathroomWaterOn ? "off" : "on");
                printf("\n[4]: Turn %s all device  ", home.bathroomDevicesOn ? "off" : "on");
                printf("\n[0]: Go back");
            }else if(mode == 126){
                gotoxy(0,24);
                printf("[1]: Turn %s light  ", home.storageLightOn ? "off" : "on");
                printf("\n[2]: Turn %s vent  ", home.storageVentOn ? "off" : "on");
                printf("\n[3]: Turn %s all device  ", home.storageDevicesOn ? "off" : "on");
                printf("\n[0]: Go back");
            }
            else if(mode == 2){
                if(home.powerCutOffActive) {
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
                    if(!home.hallwayLeftLightsOn){
                        home.hallwayLeftLightsOn = 1;
                         clearAtPositions(LeftHallway, 5, "🟡");
                        }
                        if(!home.hallwayRightLightsOn){
                            home.hallwayRightLightsOn = 1;
                            clearAtPositions(RightHallway, 5, "🟡");
                        }
                    } else {
                        if(home.hallwayLeftLightsOn){
                            home.hallwayLeftLightsOn = 0;
                            printAtPositions(LeftHallway, 5, "⚪");
                        }
                        if(home.hallwayRightLightsOn){
                            home.hallwayRightLightsOn = 0;
                            printAtPositions(RightHallway, 5, "⚪");
                        }
                    }
    
                    // Hallway Middle Lights: 17:30 - 23:30
                    if((currentTime >= 1730) && (currentTime < 2330)){
                        if(!home.hallwayMiddleLightsOn){
                            home.hallwayMiddleLightsOn = 1;
                            clearAtPositions(MiddleHallway, 7, "🟡");
                        }
                    } else {
                        if(home.hallwayMiddleLightsOn){
                            home.hallwayMiddleLightsOn = 0;
                            printAtPositions(MiddleHallway, 7, "⚪");
                        }
                    }
    
                    // AC (Living Room & Bedroom): 21:30 - 06:00
                    if((currentTime >= 2130) || (currentTime < 600)){
                        if(!home.livingRoomAcOn){
                            home.livingRoomAcOn = 1;
                            printColorAtPosition(LivingRoomacPos, 1, "AC", 11);
                        }
                        if(!home.bedroomAcOn){
                            home.bedroomAcOn = 1;
                            printColorAtPosition(BedRoomACPos, 1, "AC", 11);
                        }
                    } else {
                        if(home.livingRoomAcOn){
                            home.livingRoomAcOn = 0;
                            printColorAtPosition(LivingRoomacPos, 1, "AC", 7);
                        }
                        if(home.bedroomAcOn){
                            home.bedroomAcOn = 0;
                            printColorAtPosition(BedRoomACPos, 1, "AC", 7);
                        }
                    }
                    
                    // Room Lights: 18:00 - 06:00 (Living Room, Kitchen, Garage, Bedroom, Bathroom, Storage)
                     if((currentTime >= 1800) || (currentTime < 600)){
                        if(!home.livingRoomLightsOn){
                            home.livingRoomLightsOn = 1;
                            printColorAtPosition(livingRoomLightPos, 1, "Light", 14);
                        }
                        if(!home.kitchenLightOn){
                            home.kitchenLightOn = 1;
                            printColorAtPosition(kitchenLightPos, 1, "Light", 14);
                        }
                        if(!home.garageLightOn){
                            home.garageLightOn = 1;
                            printColorAtPosition(GarageLightPos, 1, "Light", 14);
                        }
                        if(!home.bedroomLightOn){
                            home.bedroomLightOn = 1;
                            printColorAtPosition(BedroomLightPos, 1, "Light", 14);
                        }
                        if(!home.bathroomLightOn){
                            home.bathroomLightOn = 1;
                            printColorAtPosition(bathroomLightPos, 1, "Light", 14);
                        }
                        if(!home.storageLightOn){
                            home.storageLightOn = 1;
                            printColorAtPosition(storageLightPos, 1, "Light", 14);
                        }
                    } else {
                        if(home.livingRoomLightsOn){
                            home.livingRoomLightsOn = 0;
                            printColorAtPosition(livingRoomLightPos, 1, "Light", 7);
                        }
                        if(home.kitchenLightOn){
                            home.kitchenLightOn = 0;
                            printColorAtPosition(kitchenLightPos, 1, "Light", 7);
                        }
                        if(home.garageLightOn){
                            home.garageLightOn = 0;
                            printColorAtPosition(GarageLightPos, 1, "Light", 7);
                        }
                        if(home.bedroomLightOn){
                            home.bedroomLightOn = 0;
                            printColorAtPosition(BedroomLightPos, 1, "Light", 7);
                        }
                        if(home.bathroomLightOn){
                            home.bathroomLightOn = 0;
                            printColorAtPosition(bathroomLightPos, 1, "Light", 7);
                        }
                        if(home.storageLightOn){
                            home.storageLightOn = 0;
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
                    if(home.powerCutOffActive){
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
                        home.hallwayLightsOn = !home.hallwayLightsOn;
                        home.hallwayMiddleLightsOn = home.hallwayLightsOn;
                        home.hallwayLeftLightsOn = home.hallwayLightsOn;
                        home.hallwayRightLightsOn = home.hallwayLightsOn;
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
                        home.livingRoomDevicesOn = !home.livingRoomDevicesOn;
                        home.livingRoomTVOn = home.livingRoomDevicesOn;
                        home.livingRoomAcOn = home.livingRoomDevicesOn;
                        home.livingRoomLightsOn = home.livingRoomDevicesOn;
                        toggleLivingRoomDevices();
                    }
                    if(input == '0') mode = 12;
                    if(input == '1') toggleLivingRoomLight();
                    if(input == '2') toggleLivingRoomTV();
                    if(input == '3') toggleLivingRoomAC();
                }else if(mode == 122){
                    if(input == '3'){
                        home.kitchenDevicesOn = !home.kitchenDevicesOn;
                        home.kitchenLightOn = home.kitchenDevicesOn;
                        home.kitchenVentOn = home.kitchenDevicesOn;
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
                        home.garageDevicesOn = !home.garageDevicesOn;
                        home.garageLightOn = home.garageDevicesOn;
                        home.garageVentOn = home.garageDevicesOn;
                        toggleGarageDevices();
                    }
                    if(input == '0') mode = 12;
                }
                else if(mode == 124){
                    if(input == '3'){
                        home.bedroomDevicesOn = !home.bedroomDevicesOn;
                        home.bedroomLightOn = home.bedroomDevicesOn;
                        home.bedroomAcOn = home.bedroomDevicesOn;
                        toggleBedroomDevices();
                    }
                    if(input == '1') toggleBedroomLight();
                    if(input == '2') toggleBedroomAC();
                    if(input == '0') mode = 12;
                }
                else if(mode == 125){
                    if(input == '4'){
                        home.bathroomDevicesOn = !home.bathroomDevicesOn;
                        home.bathroomLightOn = home.bathroomDevicesOn;
                        home.bathroomVentOn = home.bathroomDevicesOn;
                        home.bathroomWaterOn = home.bathroomDevicesOn;
                        toggleBathroomDevices();
                    }
                    if(input == '0') mode = 12;
                    if(input == '1') toggleBathroomLight();
                    if(input == '2') toggleBathroomCH();
                    if(input == '3') toggleBathroomWater();
                }
                else if(mode == 126){
                    if(input == '3'){
                        home.storageDevicesOn = !home.storageDevicesOn;
                        home.storageLightOn = home.storageDevicesOn;
                        home.storageVentOn = home.storageDevicesOn;
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
