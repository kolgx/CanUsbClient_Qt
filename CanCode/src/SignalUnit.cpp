#include "../inc/SignalUnit.hpp"
#include <string.h>

void SignalUnit::setSignalValue(u32 value) {
    // Assuming canMsgRecord->data is an array of u32
    // Reset the bits in the range [lowDataIndex, highDataIndex]
    if (signalValue != value) {
        signalValue = value;
        needUpdate = true;
    }
}

u32 SignalUnit::getSignalValue() {
    // Assuming canMsgRecord->data is an array of u32
    return signalValue;
}

u32 SignalUnit::getSignalValueByCanMsgRecord(P_Can_Msg_Record canMsgRecord, bool syncData) {
    // Assuming canMsgRecord->data is an array of u32
    u8 tmp_index = getSignalIndex(canMsgRecord);
    u32 ret = (canMsgRecord->canMsg[tmp_index].Data[msgIndex] & ~resetMask) >> lowDataIndex;
    if (syncData) {
        signalValue = ret;
    }
    return ret;
}

void SignalUnit::updateCanMsgRecord(P_Can_Msg_Record canMsgRecord) {
    // Assuming canMsgRecord->data is an array of u32
    if (needUpdate) {
        u8 tmp_index = getSignalIndex(canMsgRecord);
        canMsgRecord->canMsg[tmp_index].Data[msgIndex] &= ~resetMask;
        canMsgRecord->canMsg[tmp_index].Data[msgIndex] |= (signalValue << lowDataIndex);
        needUpdate = false;
        printf("updateCanMsgRecord[%d:%d]: id = %x , len = %d, data: ",msgIndex, lowDataIndex, canMsgRecord->canMsg[tmp_index].ID, canMsgRecord->canMsg[tmp_index].DataLen);
        for(int i = 0 ; i < canMsgRecord->canMsg[tmp_index].DataLen; i++)
        {
            printf("%02x ",(unsigned char)canMsgRecord->canMsg[tmp_index].Data[i]);
        }
        printf("\r\n");
    }
}

u8 SignalUnit::getSignalIndex(P_Can_Msg_Record canMsgRecord) {
    // Assuming canMsgRecord->data is an array of u32
    for (u8 i = 0; i < canMsgRecord->count; i++) {
        if (canMsgRecord->canMsg[i].ID == msgId) {
            return i;
        }
    }
    u8 index = canMsgRecord->count;
    if (index < canMsgRecord->maxCount) {
        canMsgRecord->count++;
    } else {
        index = canMsgRecord->maxCount - 1;
    }
    memset(&canMsgRecord->canMsg[index], 0, sizeof(canMsgRecord->canMsg[index]));
    canMsgRecord->canMsg[index].ID = msgId;
    canMsgRecord->canMsg[index].DataLen = 8;
    canMsgRecord->canMsg[index].ExternFlag = 1;
    return index;
}

void SignalUnit::setUpdataFlag(bool flag) {
    needUpdate = flag;
}