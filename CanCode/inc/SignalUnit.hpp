#ifndef SIGNALUNIT_HPP
#define SIGNALUNIT_HPP

#include "../../canbus.h"

typedef  struct _Can_Msg_Record {
    P_Can_Msg canMsg;
    u8 maxCount;
    u8 count;
} Can_Msg_Record, *P_Can_Msg_Record;

class SignalUnit {
public:
    SignalUnit(u32 msgId, u8 msgIndex, u8 lowDataIndex, u8 highDataIndex): msgId(msgId), msgIndex(msgIndex), lowDataIndex(lowDataIndex), highDataIndex(highDataIndex) {
        resetMask = 0;
        for (u8 i = lowDataIndex; i <= highDataIndex; i++) {
            resetMask |= (1 << i);
        }
        signalValue = -1;
        needUpdate = false;
    }; // constructor
    ~SignalUnit() {}; // destructor

    // a method for the SignalUnit class
    void setSignalValue(u32 value);
    u32 getSignalValue();
    u32 getSignalValueByCanMsgRecord(P_Can_Msg_Record canMsgRecord, bool syncData = false);
    void updateCanMsgRecord(P_Can_Msg_Record canMsgRecord);    
    void setUpdataFlag(bool flag);

private:
    // private data members
    u32 msgId;
    u8 msgIndex;
    u8 lowDataIndex;
    u8 highDataIndex;
    u32 resetMask;
    u32 signalValue;
    bool needUpdate;

    u8 getSignalIndex(P_Can_Msg_Record canMsgRecord);
};

#endif // SIGNALUNIT_HPP
