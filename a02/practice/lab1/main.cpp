/*
 * 车载软件开发基础 demo 1
 * author: 谭勇
 * date: 2022/10/1
 */

#include <iostream>
#include "smartCar.h"

using namespace std;

int main() {
    auto *smartCars = inputInformation();
    auto *students = inputStudents();
    auto *bindInfos = new BindInfo[purchaseAmount];
    bind(students, smartCars, bindInfos);
    mapBind(bindInfos);
    string stuId = "";
    while (stuId != "-1") {  // 输入没有结束，cin 就返回 true，条件就为真
        cout << "请输入学号查询绑定信息:" << endl;
        cin >> stuId;
        getBindInfo(stuId);
    }
    saveMap("output.txt");
    readInfoFromFile("output.txt");
    formatDivision("程序成功结束运行，欢迎再次使用", '*', 100);
}
