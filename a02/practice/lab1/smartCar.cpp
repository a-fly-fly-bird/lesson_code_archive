/*
 * 车载软件开发基础 demo 1
 * author: 谭勇
 * date: 2022/10/1
 * keymap: collapse all: command + shift + - (+)
 */

#include "smartCar.h"
#include <ctime>
#include <iostream>
#include <unistd.h>
#include <string>
#include <limits>
#include <map>
#include <fstream>

using namespace std;

// global var
int purchaseAmount = 0;
int availableAmount = 0;
int studentAmount = 0;
map<string, BindInfo *> bindMap;

ostream &operator<<(ostream &os, const Student &student) {
    return os << "学生的编号是：" << student.id << endl
              << "姓名是：" << student.name << endl;
}

ostream &operator<<(ostream &os, const Underpan &underpan) {
    return os << "底盘的编号是：" << underpan.id << endl
              << "型号是：" << underpan.model << endl
              << "轴距是: " << underpan.wheelBase << " mm" << endl
              << "轮距是: " << underpan.AxleTrack << " mm" << endl
              << "最小离地间隙是：" << underpan.groundClearance << " mm"  << endl
              << "最小转弯半径是：" << underpan.minimumBendingRadius << " m" << endl
              << "驱动形式是：" << underpan.driveForm << endl
              << "最大行程是：" << underpan.batteryLife << " km" << endl
              << "轮胎型号是：" << underpan.tireModel << endl
              << "轮胎尺寸是：" << underpan.tireSize << " mm" << endl;
}

ostream &operator<<(ostream &os, const AGXKits &aGXKits) {
    return os << "AGX组件的型号是：" << aGXKits.model << endl
              << "AI是：" << aGXKits.AIHashrate << " TOPS" << endl
              << "CUDA核心是：" << aGXKits.CUDACoreNum << endl
              << "Tensor CORE是：" << aGXKits.tensorCORE << endl
              << "显存是：" << aGXKits.memory << " G" << endl
              << "存储是：" << aGXKits.storage << " G" << endl;
}


ostream &operator<<(ostream &os, const BinocularCamera &binocularCamera) {
    return os << "双目摄像机的型号是：" << binocularCamera.model << endl
              << "摄像头是：" << binocularCamera.camera << endl
              << "RGB帧分辨率是：" << binocularCamera.RGBFrameResolution << endl
              << "RGB帧率是：" << binocularCamera.RGBFramRate << endl
              << "FOV是：" << binocularCamera.FOV << endl
              << "深度帧率是：" << binocularCamera.frameRateOfDepth << endl;
}

ostream &operator<<(ostream &os, const LiDAR &liDAR) {
    return os << "激光雷达的型号是：" << liDAR.model << endl
              << "通道数是：" << liDAR.channelNumber << endl
              << "测试范围是：" << liDAR.testScope << " m" << endl
              << "功耗是：" << liDAR.power << " w" << endl;
}

ostream &operator<<(ostream &os, const Gyroscope &gyroscope) {
    return os << "陀螺仪的型号是：" << gyroscope.model << endl
              << "厂商是：" << gyroscope.brand << endl;
}

ostream &operator<<(ostream &os, const LCD &lcd) {
    return os << "液晶显示屏的型号是：" << lcd.model << endl
              << "尺寸是：" << lcd.size << endl;
}

ostream &operator<<(ostream &os, const BatteryModule &batteryModule) {
    return os << "电池模组的参数是：" << batteryModule.parameter << endl
              << "对外供电是：" << batteryModule.externalPowerSupply << " V" << endl
              << "充电时间是：" << batteryModule.chargeTime << " H" << endl;
}

ostream &operator<<(ostream &os, const SmartCar &smartCar) {
    return os << "智能小车的编号是：" << smartCar.id << endl
              << smartCar.underpan << endl
              << smartCar.aGXKits << endl
              << smartCar.binocularCamera << endl
              << smartCar.liDAR << endl
              << smartCar.gyroscope << endl
              << smartCar.lcd << endl
              << smartCar.batteryModule << endl;
}

ostream &operator<<(ostream &os, const BindInfo &bindInfo) {
    return os << "绑定的学生信息是：\n" << *bindInfo.student << endl
              << "绑定的智能汽车信息是：\n" << *bindInfo.smartCar << endl;
}

bool saveMap(string filename) {
    formatDivision("开始保存数据到文件", '*', 100);
    ofstream of;
    of.open(filename);
    of << purchaseAmount - availableAmount << endl;
    map<string, BindInfo *>::iterator iter;
    iter = bindMap.begin();
    while (iter != bindMap.end()) {
        of << iter->first << ' ' << *iter->second << endl;
        iter++;
    }
    of.close();
    formatDivision("保存成功", '*', 100);
}

bool readInfoFromFile(string filename) {
    formatDivision("开始读取文件中的数据", '*', 100);
    string input;
    const int LINES_PER_DATA = 48;
    int now_data = 0;
    ifstream infile;
    infile.open(filename);
    string num_s;
    getline(infile, num_s);
    int num = stoi(num_s);
    while (input != "exit") {
        cout << "请输入指令：" << endl;
        cin >> input;
        cin.get();
        if (input == "n") {
            if (now_data < num) {
                ++now_data;
                cout << "第" << now_data << "个数据是：\n" << endl;
                cout << readInfoFromFileLineM2N(filename, (now_data - 1) * LINES_PER_DATA + 2,
                                                now_data * LINES_PER_DATA + 2);
            } else {
                cout << "已经是最后一个数据了。" << endl;
            }
        } else if (input == "p") {
            if (now_data > 1) {
                --now_data;
                cout << "第" << now_data << "个数据是：\n" << endl;
                cout << readInfoFromFileLineM2N(filename, (now_data - 1) * LINES_PER_DATA + 2,
                                                now_data * LINES_PER_DATA + 2);
            } else {
                cout << "已经是第一个数据了。" << endl;
            }
        } else {
            cout << "退出输入：exit" << endl;
            continue;
        }
    }
    formatDivision("读取完毕", '*', 100);
}


string readInfoFromFileLineM2N(const string &filename, int begin, int end) {
    string rawLine;
    string content;
    ifstream infile;
    infile.open(filename);
    for (int i = 0; i < begin;) {
        if (infile.get() == '\n') i++;
    }
    for (int i = begin; i < end; ++i) {
        getline(infile, rawLine);
        content += rawLine + "\n";
    }
    infile.close();
    return content;
}

BindInfo *getBindInfo(const string &stuId) {
    auto iter = bindMap.find(stuId);
    if (iter != bindMap.end()) {
        formatDivision("绑定信息", '*', 100);
        cout << *iter->second << endl;
        return iter->second;
    } else {
        cout << "没有该学生信息。\n" << endl;
        return nullptr;
    }
}

bool mapBind(BindInfo *bindInfos) {
    for (int i = 0; i < studentAmount; ++i) {
        if (bindMap.find(bindInfos[i].student->id) == bindMap.end()) {
            bindMap.insert(pair<string, BindInfo *>(bindInfos[i].student->id, &bindInfos[i]));
        } else {
            availableAmount += 1;
            cout << "该学生已经存在绑定信息，请更换绑定。" << endl;
        }
    }
    return true;
}

bool bind(Student *students, SmartCar *smartCars, BindInfo *bindInfos) {
    for (int i = purchaseAmount - availableAmount; i < purchaseAmount - availableAmount + studentAmount; ++i) {
        bindInfos[i].student = &students[i];
        bindInfos[i].smartCar = &smartCars[i];
        cout << "绑定信息是：" << endl
             << bindInfos[i] << endl;
    }
    availableAmount -= studentAmount;
    formatDivision("绑定完成", '*', 100);
    return true;
}

Student *inputStudents() {
    // https://stackoverflow.com/questions/17335816/clear-screen-using-c
    // clear screen in linux or windows
    cout << "\033[2J\033[1;1H";
    cout << "请输入需要小车的人数：";
    cin >> studentAmount;
    studentAmount = checkInputRange(studentAmount, 0, "输入不是正数，或者超出了可用的小车的范围。请重新输入：", availableAmount);
    auto *students = new Student[studentAmount];
    for (int i = 0; i < studentAmount; ++i) {
        students[i].id = stringInputInformationHelper("学号");
        students[i].name = stringInputInformationHelper("姓名");
        formatDivision("第" + to_string(i + 1) + " 个学生的数据是:", '*', 100);
        cout << students[i] << endl;
    }
    formatDivision("信息录入完成", '*', 100);
    return students;
}

SmartCar *inputInformation() {
    cout << "请输入采购的小车数量：";
    string input;
    cin >> input;
    purchaseAmount = checkIfNum(input);
    purchaseAmount = checkInputRange(purchaseAmount, 0, "数量不合法, 请重新输入采购的小车数量:");
    cout << "你采购的小车数是：" << purchaseAmount << endl;
    auto *smartCars = new SmartCar[purchaseAmount];
    string underpan[] = {"型号", "轴距(mm)", "轮距(mm)", "最小离地间隙(mm)", "最小转弯半径(m)", "驱动形式",
                         "最大行程(km)", "轮胎型号", "轮胎尺寸(mm)"};
    for (int i = 0; i < purchaseAmount; ++i) {
        // 随机数生成
        srand((unsigned) time(NULL) * getpid());
        string random_gen = gen_random(11);
        smartCars[i].id = "cqusn" + random_gen;
        // 底盘
        srand((unsigned) time(NULL) * getpid());
        random_gen = gen_random(6);
        smartCars[i].underpan.id = "dp" + random_gen;
        smartCars[i].underpan.model = stringInputInformationHelper(underpan[0]);
        smartCars[i].underpan.wheelBase = doubleInputInformationHelper(underpan[1], 0.0, "轴距输入范围错误");
        smartCars[i].underpan.AxleTrack = doubleInputInformationHelper(underpan[2], 0.0, "轮距输入范围错误");
        smartCars[i].underpan.groundClearance = doubleInputInformationHelper(underpan[3], 0.0, "最小离地间隙输入范围错误");
        smartCars[i].underpan.minimumBendingRadius = doubleInputInformationHelper(underpan[4], 0.0, "最小转弯半径输入范围错误");
        smartCars[i].underpan.driveForm = stringInputInformationHelper(underpan[5]);
        smartCars[i].underpan.batteryLife = doubleInputInformationHelper(underpan[6], 0.0, "最大行程输入范围错误");
        smartCars[i].underpan.tireModel = stringInputInformationHelper(underpan[7]);
        smartCars[i].underpan.tireSize = doubleInputInformationHelper(underpan[8], 0.0, "轮胎尺寸输入有误");
        // AGXKits
        smartCars[i].aGXKits.model = stringInputInformationHelper("型号");
        smartCars[i].aGXKits.AIHashrate = doubleInputInformationHelper("AI(TOPS)");
        smartCars[i].aGXKits.CUDACoreNum = doubleInputInformationHelper("CUDA核心");
        smartCars[i].aGXKits.tensorCORE = doubleInputInformationHelper("Tensor CORE");
        smartCars[i].aGXKits.memory = doubleInputInformationHelper("显存(G)");
        smartCars[i].aGXKits.storage = doubleInputInformationHelper("存储(G)");
        // 双目摄像头
        smartCars[i].binocularCamera.model = stringInputInformationHelper("型号");
        smartCars[i].binocularCamera.camera = stringInputInformationHelper("摄像头");
        smartCars[i].binocularCamera.RGBFrameResolution = stringInputInformationHelper("RGB帧分辨率");
        smartCars[i].binocularCamera.RGBFramRate = doubleInputInformationHelper("RGB帧率", 0.0);
        smartCars[i].binocularCamera.FOV = stringInputInformationHelper("FOV");
        smartCars[i].binocularCamera.frameRateOfDepth = doubleInputInformationHelper("深度帧率", 0.0);
        // 多线激光雷达
        smartCars[i].liDAR.model = stringInputInformationHelper("型号");
        smartCars[i].liDAR.channelNumber = doubleInputInformationHelper("通道数", 0.0);
        smartCars[i].liDAR.testScope = doubleInputInformationHelper("测试范围(m)", 0.0);
        smartCars[i].liDAR.power = doubleInputInformationHelper("功耗(w)", 0.0);
        // 9轴陀螺仪
        smartCars[i].gyroscope.model = stringInputInformationHelper("型号");
        smartCars[i].gyroscope.brand = stringInputInformationHelper("厂商");
        // 液晶显示屏
        smartCars[i].lcd.model = stringInputInformationHelper("型号");
        smartCars[i].lcd.size = doubleInputInformationHelper("尺寸", 0.0);
        // 电池模块
        smartCars[i].batteryModule.parameter = stringInputInformationHelper("参数");
        smartCars[i].batteryModule.externalPowerSupply = doubleInputInformationHelper("对外供电(V)", 0.0);
        smartCars[i].batteryModule.chargeTime = doubleInputInformationHelper("充电时间(H)", 0.0);

        formatDivision("\n第 " + to_string(i + 1) + " 个小车的数据是", '*', 100);
        cout << smartCars[i] << endl;
    }
    availableAmount = purchaseAmount;
    formatDivision("小车信息录入完成", '*', 100);
    return smartCars;
}

// 检查数字是否超出范围
template<class T>
T checkInputRange(T input, T min, string errorMsg, T max) {
    if (input > max || input < min) {
        cout << errorMsg;
        cin >> input;
        input = checkInputRange(input, min, errorMsg, max);
    }
    return input;
}

int checkIfNum(string input){
    int res;
    try{
        res = stoi(input);
    }catch(exception e){
        cout << "输入的不是数字,请重新输入: ";
        cin >> input;
        res = checkIfNum(input);
    }
    return res;
}

string stringInputInformationHelper(const string &requestInfo) {
    cout << "请输入" << requestInfo << "信息：";
    string info;
    cin >> info;
    return info;
}

double doubleInputInformationHelper(const string &requestInfo, double min, const string& errorMsg, double max) {
    cout << "请输入" << requestInfo << "信息：";
    string info;
    double res;
    cin >> info;
    // check if double
    try {
        res = stod(info);
    } catch (const exception &) {
        cout << "输入的不是数字，请重新输入。" << endl;
        res = doubleInputInformationHelper(requestInfo, min, errorMsg, max);
    }
    res = checkInputRange(res, min, errorMsg, max);
    return res;
}

string gen_random(const int len) {
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

void formatDivision(const string &info, char divisionChar, int numOfDivChar) {
    int len = info.length();
    int halfNumOfDiv = (numOfDivChar - len - 2) / 2;
    for (int i = 0; i < halfNumOfDiv; ++i) {
        cout << divisionChar;
    }
    cout << " " << info << " ";
    for (int i = 0; i < halfNumOfDiv; ++i) {
        cout << divisionChar;
    }
    cout << endl << endl;
}