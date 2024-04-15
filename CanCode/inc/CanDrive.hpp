#ifndef CANDRIVE_HPP
#define CANDRIVE_HPP

#include "../../canbus.h"

/**
 * 单独线程，负责通过Can设备 接收 发送数据
 * 
 * 使用消息队列修改工作模式：接收模式、发送模式，闲置模式
 * 1. 提供API添加 指令到消息队列
 * 
 * 接收模式：
 * 1. 提供API注册/解注册 接收数据的回调函数
 * 2. 提供API获取/修改 数据刷新频率
 * 3. 提供API开启/关闭 数据保存至文件功能
 * 
 * 发送模式：
 * 1. 提供API获取/修改 数据发送频率
 * 2. 提供API开启/关闭 读取文件发送数据功能
 * 3. 提供API增加/删除 信号单元 用于发送自定义数据
*/

class CanDrive {
public:
    CanDrive(u32 devNum, u32 chNum): devNum(devNum), chNum(chNum) {debugLog("CanDrive constructor");}; // constructor
    ~CanDrive(); // destructor

    // Add your methods here
    int initialize(P_Can_Config pInitConfig);
    int sendData(P_Can_Msg canmsg, u32 items, u32 timeou = 100);
    int receiveData(P_Can_Msg canmsg, u32 Len, u32 timeou = 100);

private:
    // Add your data members here
    u32 devNum;
    u32 chNum;

    void debugLog(const char* message);
};

#endif // CANDRIVE_HPP
