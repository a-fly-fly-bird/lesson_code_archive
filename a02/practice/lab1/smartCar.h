/*
 * 车载软件开发基础 demo 1
 * author: 谭勇
 * date: 2022/10/1
 */

#ifndef HOMEWORK_1_SMARTCAR_H
#define HOMEWORK_1_SMARTCAR_H

#include <string>

using namespace std;

extern int purchaseAmount;

// 学生信息
struct Student {
    // 学号
    string id;
    // 姓名
    string name;
};

// 底盘
struct Underpan {
    // 编号：dp打头的8位数字+字母
    string id;
    // 型号
    string model;
    // 轴距
    double wheelBase;
    // 轮距
    double AxleTrack;
    // 最小离地间隙
    double groundClearance;
    // 最小转弯半径
    double minimumBendingRadius;
    // 驱动形式
    string driveForm;
    // 最大行程
    double batteryLife;
    // 轮胎型号
    string tireModel;
    // 轮胎尺寸
    double tireSize;
};

// AGX套件
struct AGXKits {
    // 型号
    string model;
    // AI
    double AIHashrate;
    // CUDA核心
    double CUDACoreNum;
    // Tensor CORE
    double tensorCORE;
    // 显存
    double memory;
    // 外存
    double storage;
};

// 双目摄像头
struct BinocularCamera {
    // 型号
    string model;
    // 摄像头
    string camera;
    // RGB帧分辨率
    string RGBFrameResolution;
    // RGB帧率
    double RGBFramRate;
    // FOV
    string FOV;
    // 深度帧率
    double frameRateOfDepth;
};

// 多线激光雷达
struct LiDAR {
    // 型号
    string model;
    // 通道数
    double channelNumber;
    // 测试范围
    double testScope;
    // 功耗
    double power;
};

// 9轴陀螺仪
struct Gyroscope {
    // 型号
    string model;
    // 厂家
    string brand;
};

// 液晶显示屏
struct LCD {
    // 型号
    string model;
    // 尺寸
    double size;
};

// 电池模块
struct BatteryModule {
    // 参数
    string parameter;
    // 对外供电
    double externalPowerSupply;
    // 充电时间
    double chargeTime;
};

// 智能小车
struct SmartCar {
    // 自定义，cqusn打头的16位数字+字母
    string id;
    // 底座
    Underpan underpan;
    // 套件
    AGXKits aGXKits;
    // 双目摄像头
    BinocularCamera binocularCamera;
    // 多线激光雷达
    LiDAR liDAR;
    // 9轴陀螺仪
    Gyroscope gyroscope;
    // 液晶显示屏
    LCD lcd;
    // 电池模块
    BatteryModule batteryModule;
};

struct BindInfo {
    Student *student;
    SmartCar *smartCar;
};

ostream &operator<<(ostream &, const Student &);

ostream &operator<<(ostream &, const Underpan &);

ostream &operator<<(ostream &, const AGXKits &);

ostream &operator<<(ostream &, const BinocularCamera &);

ostream &operator<<(ostream &, const LiDAR &);

ostream &operator<<(ostream &, const Gyroscope &);

ostream &operator<<(ostream &, const LCD &);

ostream &operator<<(ostream &, const BatteryModule &);

ostream &operator<<(ostream &, const SmartCar &);

ostream &operator<<(ostream &, const BindInfo &);

SmartCar *inputInformation();

string stringInputInformationHelper(const string &);

string gen_random(int);

Student *inputStudents();

bool bind(Student *, SmartCar *, BindInfo *);

bool mapBind(BindInfo *);

BindInfo *getBindInfo(const string &);

bool saveMap(string);

bool readInfoFromFile(string);

int checkIfNum(string input);

string readInfoFromFileLineM2N(const string &, int, int);

void formatDivision(const string&, char, int);

double doubleInputInformationHelper(const string &requestInfo, double min = numeric_limits<double>::min(),
                                    const string& errorMsg = "信息输入超出规定范围",
                                    double max = numeric_limits<double>::max());

template<class T>
// 默认参数不能在声明和定义中同时出现，所以最好在声明中出现。
T checkInputRange(T input, T min = numeric_limits<T>::min(), string errorMsg = "输入超出规定范围",
                  T max = numeric_limits<T>::max());

#endif //HOMEWORK_1_SMARTCAR_H
