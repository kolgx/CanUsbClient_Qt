#ifndef MAINPROCESS_HPP
#define MAINPROCESS_HPP

/**
 * 1. Can线上数据 录制
 * 2. Can线上数据 回放
 * 3. Can线上数据 实时分析
 * 4. 自定义Can数据，支持增删，文件形式存储&读取
*/

class MainProcess
{
public:
    MainProcess(); // Constructor
    ~MainProcess(); // Destructor

    void run(); // Method to start the main process

private:
};

#endif // MAINPROCESS_HPP