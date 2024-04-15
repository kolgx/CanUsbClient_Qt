#include "../inc/CanDrive.hpp"

CanDrive::~CanDrive() {
    // Clean up your data members here
    CAN_CloseDevice(devNum,chNum);            //关闭CAN
    debugLog("CanDrive destructor");
}

int CanDrive::initialize(P_Can_Config pInitConfig) {
    // Implement your initialization logic here
    // Return 0 for success, non-zero for failure
    u8 ret = CAN_OpenDevice(devNum,chNum);        //打开通道0(CAN)
    if(ret != 0) {
        debugLog("CAN_OpenDevice failed");
        return -1;
    }

    ret = CAN_Init(devNum,chNum,pInitConfig);         //初始化CAN
    if(ret != 0) {
        debugLog("CAN_Init failed");
        return -1;
    }

    ret = CAN_SetFilter(devNum,chNum,0,0,0,0,1);    //设置接收所有数据
    if(ret != 0) {
        debugLog("CAN_SetFilter failed");
        return -1;
    }

    debugLog("CanDrive initialized");

    return 0;
}

int CanDrive::sendData(P_Can_Msg canmsg, u32 items, u32 timeou) {
    // Implement your data sending logic here
    // Return 0 for success, non-zero for failur
    if (items == 0) {
        debugLog("No data to send");
        return -1;
    }
    u8 ret = CAN_Transmit(devNum,chNum,canmsg,items,timeou);
    if(ret <= 0) {
        debugLog("CAN_Transmit failed");
    }
    return ret;
}

int CanDrive::receiveData(P_Can_Msg canmsg, u32 Len, u32 timeou) {
    // Implement your data receiving logic here
    // Return 0 for success, non-zero for failure
    u8 ret = CAN_Receive(devNum,chNum,canmsg,Len,timeou);
    if(ret == 0) {
        debugLog("CAN_Receive timeout!!");
    } else if(ret < 0) {
        debugLog("CAN_Receive failed");
    }
    return ret;
}

void CanDrive::debugLog(const char* message) {
    // Implement your debug logging logic here
    // return;
    printf("CanDrive[%d:%d]: %s\n", devNum, chNum, message);
}