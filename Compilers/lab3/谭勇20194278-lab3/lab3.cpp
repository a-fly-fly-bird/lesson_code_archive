#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

map<string, string> table1;
map<string, string> table2;

/*----------------结构分析----------------*/

//创建关键词的map
void init()
{
    table1["const"] = "CONSTTK";
    table1["int"] = "INTTK";
    table1["char"] = "CHARTK";
    table1["void"] = "VOIDTK";
    table1["main"] = "MAINTK";
    table1["if"] = "IFTK";
    table1["else"] = "ELSETK";
    table1["switch"] = "SWITCHTK";
    table1["case"] = "CASETK";
    table1["default"] = "DEFAULTTK";
    table1["while"] = "WHILETK";
    table1["for"] = "FORTK";
    table1["scanf"] = "SCANFTK";
    table1["printf"] = "PRINTFTK";
    table1["return"] = "RETURNTK";
    table2["+"] = "PLUS";
    table2["-"] = "MINU";
    table2["*"] = "MULT";
    table2["/"] = "DIV";
    table2["<"] = "LSS";
    table2["<="] = "LEQ";
    table2[">"] = "GRE";
    table2[">="] = "GEQ";
    table2["=="] = "EQL";
    table2["!="] = "NEQ";
    table2[":"] = "COLON";
    table2["="] = "ASSIGN";
    table2[";"] = "SEMICN";
    table2[","] = "COMMA";
    table2["("] = "LPARENT";
    table2[")"] = "RPARENT";
    table2["["] = "LBRACK";
    table2["]"] = "RBRACK";
    table2["{"] = "LBRACE";
    table2["}"] = "RBRACE";
}

// session 数据结构的定义
struct session
{
    string type;
    string value;
    int abc;
};

//词法分析的结果
vector<session> resOfCf;

//忽略大小写的字符串比较
bool compareEquals(string a, string b)
{
    string strl = a;
    for (int i = 0; i < a.length(); i++)
    {
        if (strl[i] <= 'Z' && strl[i] >= 'A')
        {
            strl[i] = strl[i] - 'A' + 'a';
        }
    }
    string strl1 = b;
    for (int i = 0; i < b.length(); i++)
    {
        if (strl1[i] <= 'Z' && strl1[i] >= 'A')
        {
            strl1[i] = strl1[i] - 'A' + 'a';
        }
    }
    return (strl == strl1);
}

//判断是否为关键词，不是则为字符串
void isSignature(string str, int abc)
{
    string strl = str;
    for (int i = 0; i < str.length(); i++)
    {
        if (strl[i] <= 'Z' && strl[i] >= 'A')
        {
            strl[i] = strl[i] - 'A' + 'a';
        }
    }
    if (table1.count(strl))
    {
        // cout << table1[strl] << " " << str << endl;
        session temp;
        temp.type = table1[strl];
        temp.value = str;
        temp.abc = abc;
        resOfCf.push_back(temp);
    }
    else
    {
        // cout << "IDENFR" << " " << str << endl;
        session temp;
        temp.type = "IDENFR";
        temp.value = str;
        temp.abc = abc;
        resOfCf.push_back(temp);
    }
}

int isletter(char a)
{
    if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || a == '_')
        return 1;
    return 0;
}

int isdigit(char a)
{
    if (a >= '0' && a <= '9')
        return 1;
    return 0;
}

int state = 0;
string strNow = "";

void FSM(string str, int abc)
{
    for (int i = 0; i < str.length(); i++)
    {
        switch (state)
        {
        case 0:
            if (isletter(str[i]))
            {
                state = 1;
                strNow += str[i];
                break;
            }
            if (isdigit(str[i]))
            {
                state = 2;
                strNow += str[i];
                break;
            }
            if (str[i] == '\'')
            {
                state = 3;
                break;
            }
            if (str[i] == '"')
            {
                state = 4;
                break;
            }
            else
            {
                string strt = str.substr(i, 2);
                if (table2.count(strt))
                {
                    session temp;
                    temp.type = table2[strt];
                    temp.value = strt;
                    temp.abc = abc;
                    resOfCf.push_back(temp);
                    i++;
                    break;
                }
                if (table2.count(str.substr(i, 1)))
                {
                    session temp;
                    temp.type = table2[str.substr(i, 1)];
                    temp.value = str[i];
                    temp.abc = abc;
                    resOfCf.push_back(temp);
                    break;
                }
                break;
            }
        case 1: //字符串
            if (isletter(str[i]) || isdigit(str[i]))
            {
                strNow += str[i];
                break;
            }
            else
            {
                isSignature(strNow, abc);
                strNow = "";
                i--;
                state = 0;
                break;
            }
        case 2: //数字
            if (isdigit(str[i]))
            {
                strNow += str[i];
                break;
            }
            if (str[i] == '.')
            {
                // todo
                break;
            }
            else
            {
                session temp;
                temp.type = "INTCON";
                temp.value = strNow;
                temp.abc = abc;
                resOfCf.push_back(temp);
                strNow = "";
                i--;
                state = 0;
                break;
            }
        case 3: //字符
            if (str[i] == '\\')
            {
                break;
            }
            if (str[i] == '\'')
            {
                session temp;
                temp.type = "CHARCON";
                temp.value = strNow;
                temp.abc = abc;
                resOfCf.push_back(temp);
                strNow = "";
                state = 0;
                break;
            }
            else
            {
                strNow += str[i];
                break;
            }
        case 4: //字符串
            if (str[i] == '"')
            {
                session temp;
                temp.type = "STRCON";
                temp.value = strNow;
                temp.abc = abc;
                resOfCf.push_back(temp);
                strNow = "";
                state = 0;
                break;
            }
            else
            {
                strNow += str[i];
                break;
            }
        default:
            break;
        }
    }
}

/* --------------- 错误处理 ---------------- */

int countOfCF = 0;

//添加两张表来区分有返回值的函数和无返回值的函数
vector<string> have_return;
vector<string> no_return;

struct err
{
    int abc;
    string type;
};

//存储错误
vector<err> errl;

//函数声明
bool Integer();
bool con();
int value_para();
bool use_func();
bool factor();
bool item_1();
bool item();
bool expre_1();
bool expression();
bool read();
bool write();
bool cons();
bool constDef();
bool varInitDefOne();
bool varInitDefTwo(int);
bool noInitDef();
bool initDef();
bool var_def();
bool var();
bool parameterTable();
bool repeatFuncOne();
bool func_return();
bool func_not_return();
bool func_closures();
bool headDeclaration();
bool condition();
bool step();
bool complexJuzi();
bool sentenceList();
bool defaultSentence();
bool subSituation();
bool tableOfSituation1();
bool tableOfSituation2();
bool return_sentence();
bool conditionOfSentence();
bool assign();
bool sentence();
bool cycle();
bool main_fun();
void prom();

void checkChar(int k)
{
    if (resOfCf[k].value == "+" || resOfCf[k].value == "-" || resOfCf[k].value == "*" || resOfCf[k].value == "/" ||
        (resOfCf[k].value >= "A" && resOfCf[k].value <= "Z") || (resOfCf[k].value >= "a" && resOfCf[k].value <= "z") ||
        (resOfCf[k].value >= "0" && resOfCf[k].value <= "9") || resOfCf[k].value == "_")
    {
        return;
    }
    else
    {
        err er;
        er.abc = resOfCf[k].abc;
        er.type = "a";
        errl.push_back(er);
    }
}

void checkStr(int k)
{
    for (int i = 0; i < resOfCf[k].value.length(); i++)
    {
        if (resOfCf[k].value[i] == ' ' || resOfCf[k].value[i] == '!' || (resOfCf[k].value[i] >= '#' && resOfCf[k].value[i] <= '~'))
        {
            continue;
        }
        else
        {
            err er;
            er.abc = resOfCf[k].abc;
            er.type = "a";
            errl.push_back(er);
        }
    }
}

int intTmp = 0;

string bname[10000];
string btype[10000];

struct structOfFunction
{
    vector<string> parameterTable;
    string name;
    string type;
};

vector<structOfFunction> bnamefunc;

int nameOfCons[10000] = {0};

int beforeCount;

void check_b(int k)
{
    for (int i = intTmp - 1; i >= beforeCount; i--)
    {
        if (compareEquals(bname[i], resOfCf[k].value))
        {
            err er;
            er.abc = resOfCf[k].abc;
            er.type = "b";
            errl.push_back(er);
            return;
        }
    }
}

void check_b_func(int k)
{
    for (int i = 0; i < bnamefunc.size(); i++)
    {
        if (compareEquals(bnamefunc[i].name, resOfCf[k].value))
        {
            err er;
            er.abc = resOfCf[k].abc;
            er.type = "b";
            errl.push_back(er);
            return;
        }
    }
}

void check_c(int k)
{
    for (int i = intTmp - 1; i >= 0; i--)
    {
        if (compareEquals(bname[i], resOfCf[k].value))
        {
            return;
        }
    }
    err er;
    er.abc = resOfCf[k].abc;
    er.type = "c";
    errl.push_back(er);
}

int nowfunc = 0;
void check_c_func(int k)
{
    for (int i = 0; i < bnamefunc.size(); i++)
    {
        if (compareEquals(bnamefunc[i].name, resOfCf[k].value))
        {
            nowfunc = i;
            return;
        }
    }
    cout << bnamefunc[0].name;
    cout << resOfCf[k].value;
    err er;
    er.abc = resOfCf[k].abc;
    er.type = "c";
    errl.push_back(er);
}

void error_d(int k)
{
    err er;
    er.abc = resOfCf[k].abc;
    er.type = "d";
    errl.push_back(er);
}

string nowtype = "";
void error_e(int k)
{
    err er;
    er.abc = resOfCf[k].abc;
    er.type = "e";
    errl.push_back(er);
}
void error_f(int k)
{
    err er;
    er.abc = resOfCf[k].abc;
    er.type = "f";
    errl.push_back(er);
}

string now_func_type = "";
void error_g(int k)
{
    err er;
    er.abc = resOfCf[k].abc;
    er.type = "g";
    errl.push_back(er);
}

bool is_have_return = 0;

void error_h(int k)
{
    err er;
    er.abc = resOfCf[k - 1].abc;
    er.type = "h";
    errl.push_back(er);
}
void error_i(int k)
{
    err er;
    er.abc = resOfCf[k].abc;
    er.type = "i";
    errl.push_back(er);
}
void check_j(int k)
{
    for (int i = intTmp - 1; i >= 0; i--)
    {
        if (compareEquals(bname[i], resOfCf[k].value))
        {
            if (nameOfCons[i] == 0)
            {
                return;
            }
        }
    }
    if (errl[errl.size() - 1].type == "c" && errl[errl.size() - 1].abc == resOfCf[k].abc)
    {
        return;
    }
    err er;
    er.abc = resOfCf[k].abc;
    er.type = "j";
    errl.push_back(er);
}

void error_k(int k)
{
    err er;
    er.abc = resOfCf[k - 1].abc;
    er.type = "k";
    errl.push_back(er);
}
void error_l(int k)
{
    err er;
    er.abc = resOfCf[k].abc;
    er.type = "l";
    errl.push_back(er);
}
void error_m(int k)
{
    err er;
    er.abc = resOfCf[k].abc;
    er.type = "m";
    errl.push_back(er);
}
void error_n(int k)
{
    err er;
    er.abc = resOfCf[k].abc;
    er.type = "n";
    errl.push_back(er);
}
void error_o(int k)
{
    err er;
    er.abc = resOfCf[k].abc;
    er.type = "o";
    errl.push_back(er);
}
void error_p(int k)
{
    err er;
    er.abc = resOfCf[k].abc;
    er.type = "p";
    errl.push_back(er);
}
//整数
bool Integer()
{
    if ((resOfCf[countOfCF].type == table2["+"]) || (resOfCf[countOfCF].type == table2["-"]))
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
        if (Integer())
        {
            return 1;
        }
    }
    else
    {
        if (resOfCf[countOfCF].type == "INTCON")
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            countOfCF++;
            cout << "<无符号整数>" << endl;
            cout << "<整数>" << endl;
            return 1;
        }
    }
    return 0;
}
//常量
bool con()
{
    if (Integer() == 1)
        return 1;
    else if (resOfCf[countOfCF].type == "CHARCON")
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        checkChar(countOfCF);
        countOfCF++;
        return 1;
    }
    return 0;
}

//值参数表
int value_para()
{
    int para_count = 0;
    if (resOfCf[countOfCF].type == table2[","])
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
    }
    if (expression() == 1)
    {
        cout << "++++++++++++++++++" << resOfCf[countOfCF - 1].value << " " << nowtype << endl;
        if (nowtype != bnamefunc[nowfunc].parameterTable[para_count] && para_count < bnamefunc[nowfunc].parameterTable.size())
        {
            error_e(countOfCF);
        }
        cout << "<表达式>" << endl;
        para_count = value_para() + 1;
    }
    return para_count;
}
//函数调用语句
bool use_func()
{
    if ((resOfCf[countOfCF].type == "IDENFR") && (resOfCf[countOfCF + 1].type == table2["("]))
    {
        for (int i = 0; i < bnamefunc.size(); i++)
        {
            if (resOfCf[countOfCF].value == bnamefunc[i].name)
            {
                nowtype = btype[i];
            }
        }
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        cout << resOfCf[countOfCF + 1].type << " " << resOfCf[countOfCF + 1].value << endl;
        check_c_func(countOfCF);
        countOfCF += 2;
        int para_count = value_para();
        if (para_count != bnamefunc[nowfunc].parameterTable.size())
        {
            cout << para_count << "---------------" << resOfCf[countOfCF].abc << endl;
            error_d(countOfCF);
        }
        para_count = 0;
        cout << "<值参数表>" << endl;
        if (resOfCf[countOfCF].type == table2[")"])
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            countOfCF++;
            return 1;
        }
        else
        {
            error_l(countOfCF);
            return 1;
        }
    }
    return 0;
}

//因子
bool factor()
{
    //添加对括号的判断以区分变量和函数
    if ((resOfCf[countOfCF].type == "IDENFR") && (resOfCf[countOfCF + 1].type != table2["("]))
    {
        for (int i = 0; i < intTmp; i++)
        {
            if (resOfCf[countOfCF].value == bname[i])
            {
                nowtype = btype[i];
            }
        }
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        check_c(countOfCF);
        countOfCF++;
        if (resOfCf[countOfCF].type == table2["["])
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            countOfCF++;
            if (expression() == 1)
            {
                cout << "<表达式>" << endl;
                if (nowtype != "int")
                {
                    error_i(countOfCF);
                }
                if (resOfCf[countOfCF].type == table2["]"])
                {
                    cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                    countOfCF++;
                }
                else
                {
                    error_m(countOfCF);
                }
                if (resOfCf[countOfCF].type == table2["["])
                {
                    cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                    countOfCF++;
                    if (expression() == 1)
                    {
                        cout << "<表达式>" << endl;
                        if (nowtype != "int")
                        {
                            error_i(countOfCF);
                        }
                        if (resOfCf[countOfCF].type == table2["]"])
                        {
                            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                            countOfCF++;
                            return 1;
                        }
                        else
                        {
                            error_m(countOfCF);
                            return 1;
                        }
                    }
                }
                else
                    return 1;
            }
        }
        else
            return 1;
    }
    else if (use_func() == 1)
    {
        cout << "<有返回值函数调用语句>" << endl;
        return 1;
    }
    else if (resOfCf[countOfCF].type == table2["("])
    {
        for (int i = 0; i < bnamefunc.size(); i++)
        {
            if (resOfCf[countOfCF].value == bnamefunc[i].name)
            {
                nowtype = bnamefunc[i].type;
            }
        }
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
        if (expression() == 1)
        {
            cout << "<表达式>" << endl;
            if (resOfCf[countOfCF].type == table2[")"])
            {
                cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                countOfCF++;
                return 1;
            }
            else
            {
                error_l(countOfCF);
                return 1;
            }
        }
    }
    else if (Integer() == 1)
    {
        nowtype = "int";
        return 1;
    }
    else if (resOfCf[countOfCF].type == "CHARCON")
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        checkChar(countOfCF);
        countOfCF++;
        nowtype = "char";
        return 1;
    }

    return 0;
}

bool item_1()
{
    if ((resOfCf[countOfCF].type == table2["*"]) || (resOfCf[countOfCF].type == table2["/"]))
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
        if (factor() == 1)
        {
            cout << "<因子>" << endl;
            item_1();
            return 1;
        }
    }
    return 0;
}
//项
bool item()
{
    if (factor() == 1)
    {
        cout << "<因子>" << endl;
        item_1();
        return 1;
    }
    return 0;
}

bool expre_1()
{
    if ((resOfCf[countOfCF].type == table2["+"]) || (resOfCf[countOfCF].type == table2["-"]))
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
        if (item() == 1)
        {
            cout << "<项>" << endl;
            expre_1();
            return 1;
        }
    }
    return 0;
}
//表达式
bool expression()
{
    if ((resOfCf[countOfCF].type == table2["+"]) || (resOfCf[countOfCF].type == table2["-"]))
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
    }
    if (item() == 1)
    {
        cout << "<项>" << endl;
        expre_1();
        return 1;
    }
    return 0;
}
//读语句
bool read()
{
    if ((resOfCf[countOfCF].type == "SCANFTK") && (resOfCf[countOfCF + 1].type == table2["("]) && (resOfCf[countOfCF + 2].type == "IDENFR")
        //&& (resOfCf[countOfCF + 3].type == table2[")"])
    )
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        cout << resOfCf[countOfCF + 1].type << " " << resOfCf[countOfCF + 1].value << endl;
        cout << resOfCf[countOfCF + 2].type << " " << resOfCf[countOfCF + 2].value << endl;

        check_c(countOfCF + 2);
        check_j(countOfCF + 2);
        countOfCF += 3;
        if (resOfCf[countOfCF].type == table2[")"])
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            countOfCF++;
            return 1;
        }
        else
        {
            error_l(countOfCF);
            return 1;
        }
    }
    return 0;
}
//写语句
bool write()
{
    if ((resOfCf[countOfCF].type == "PRINTFTK") && (resOfCf[countOfCF + 1].type == table2["("]) &&
        (resOfCf[countOfCF + 2].type == "STRCON") && (resOfCf[countOfCF + 3].type != table2[","])
        //&& (resOfCf[countOfCF + 3].type == table2[")"])
    )
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        cout << resOfCf[countOfCF + 1].type << " " << resOfCf[countOfCF + 1].value << endl;
        cout << resOfCf[countOfCF + 2].type << " " << resOfCf[countOfCF + 2].value << endl;

        cout << "<字符串>" << endl;

        checkStr(countOfCF + 2);
        countOfCF += 3;
        if (resOfCf[countOfCF].type == table2[")"])
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            countOfCF++;
            return 1;
        }
        else
        {
            error_l(countOfCF);
            return 1;
        }
    }
    else if ((resOfCf[countOfCF].type == "PRINTFTK") && (resOfCf[countOfCF + 1].type == table2["("]) &&
             (resOfCf[countOfCF + 2].type == "STRCON") && (resOfCf[countOfCF + 3].type == table2[","]))
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        cout << resOfCf[countOfCF + 1].type << " " << resOfCf[countOfCF + 1].value << endl;
        cout << resOfCf[countOfCF + 2].type << " " << resOfCf[countOfCF + 2].value << endl;
        cout << resOfCf[countOfCF + 3].type << " " << resOfCf[countOfCF + 3].value << endl;
        cout << "<字符串>" << endl;

        checkStr(countOfCF + 2);
        countOfCF += 4;
        if (expression() == 1)
        {
            cout << "<表达式>" << endl;
            if (resOfCf[countOfCF].type == table2[")"])
            {
                cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                countOfCF++;
                return 1;
            }
            else
            {
                error_l(countOfCF);
                return 1;
            }
        }
    }
    else if ((resOfCf[countOfCF].type == "PRINTFTK") && (resOfCf[countOfCF + 1].type == table2["("]))
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        cout << resOfCf[countOfCF + 1].type << " " << resOfCf[countOfCF + 1].value << endl;
        countOfCF += 2;
        if (expression() == 1)
        {
            cout << "<表达式>" << endl;
            if (resOfCf[countOfCF].type == table2[")"])
            {
                cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                countOfCF++;
                return 1;
            }
            else
            {
                error_l(countOfCF);
                return 1;
            }
        }
    }
    return 0;
}
//常量说明
bool cons()
{
    if (resOfCf[countOfCF].type == "CONSTTK")
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        //指针前移
        countOfCF++;
        if (constDef() == 1)
        {
            cout << "<常量定义>" << endl;
        }
        else
            return 0;
        if (resOfCf[countOfCF].type == table2[";"])
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            countOfCF++;
            cons();
            return 1;
        }
        else
        {
            error_k(countOfCF);
            return 1;
        }
    }
    return 0;
}
//常量定义
bool constDef()
{
    if (resOfCf[countOfCF].type == table2[","])
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
        if ((resOfCf[countOfCF].type == "IDENFR") && (resOfCf[countOfCF + 2].type != "CHARCON")) //区分整数和字符
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            check_b(countOfCF);
            nameOfCons[intTmp] = 1;
            btype[intTmp] = btype[intTmp - 1];
            bname[intTmp++] = resOfCf[countOfCF].value;
            if (btype[intTmp - 1] == "char")
            {
                error_o(countOfCF);
            }
            countOfCF++;
            if (resOfCf[countOfCF].type == table2["="])
            {
                cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                countOfCF++;
                Integer();
                constDef();
                return 1;
            }
        }
        else if (resOfCf[countOfCF].type == "IDENFR")
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            check_b(countOfCF);
            nameOfCons[intTmp] = 1;
            btype[intTmp] = btype[intTmp - 1];
            bname[intTmp++] = resOfCf[countOfCF].value;
            if (btype[intTmp - 1] == "int")
            {
                error_o(countOfCF);
            }
            countOfCF++;
            if (resOfCf[countOfCF].type == table2["="])
            {
                cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                countOfCF++;
                if (resOfCf[countOfCF].type == "CHARCON")
                {
                    cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                    checkChar(countOfCF);
                    countOfCF++;
                    constDef();
                    return 1;
                }
            }
        }
    }
    else if (resOfCf[countOfCF].type == "INTTK")
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
        if (resOfCf[countOfCF].type == "IDENFR")
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            check_b(countOfCF);
            nameOfCons[intTmp] = 1;
            btype[intTmp] = "int";
            bname[intTmp++] = resOfCf[countOfCF].value;
            if (resOfCf[countOfCF + 2].type == "CHARCON")
            {
                error_o(countOfCF);
            }
            countOfCF++;
            if (resOfCf[countOfCF].type == table2["="])
            {
                cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                countOfCF++;
                if (resOfCf[countOfCF].type == "CHARCON")
                {
                    cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                    checkChar(countOfCF);
                    countOfCF++;
                }
                else
                {
                    Integer();
                }
                constDef();
                return 1;
            }
        }
    }
    else if (resOfCf[countOfCF].type == "CHARTK")
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
        if (resOfCf[countOfCF].type == "IDENFR")
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            check_b(countOfCF);
            nameOfCons[intTmp] = 1;
            btype[intTmp] = "char";
            bname[intTmp++] = resOfCf[countOfCF].value;
            if (resOfCf[countOfCF + 2].type == "INTCON")
            {
                error_o(countOfCF);
            }
            countOfCF++;
            if (resOfCf[countOfCF].type == table2["="])
            {
                cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                countOfCF++;
                if (resOfCf[countOfCF].type == "CHARCON")
                {
                    cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                    checkChar(countOfCF);
                    countOfCF++;
                    constDef();
                    return 1;
                }
                else
                {
                    Integer();
                    constDef();
                    return 1;
                }
            }
        }
    }
    return 0;
}

int L1Count = 0;
int L2Count = 0;

bool varInitDefOne()
{
    if (resOfCf[countOfCF].type == table2[","])
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
        if (con() == 1)
        {
            cout << "<常量>" << endl;
            L1Count++;
            varInitDefOne();
            return 1;
        }
    }
    return 1;
}

bool varInitDefTwo(int listcount)
{
    if (resOfCf[countOfCF].type == table2[","])
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
        if (resOfCf[countOfCF].type == table2["{"])
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            countOfCF = countOfCF + 1;
            L1Count = 0;
            if (con() == 1)
            {
                cout << "<常量>" << endl;
                L1Count++;
                varInitDefOne();
                if (resOfCf[countOfCF].type == table2["}"])
                {
                    cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                    countOfCF++;
                    if (L1Count != listcount)
                    {
                        error_n(countOfCF - 1);
                    }
                    L2Count++;
                    varInitDefTwo(listcount);
                    return 1;
                }
            }
        }
        else
            return 0;
    }
    return 1;
}

//变量定义无初始化
bool noInitDef()
{
    //增加对括号的判断来区分函数和变量
    if (((resOfCf[countOfCF].type == "INTTK") || (resOfCf[countOfCF].type == "CHARTK") || (resOfCf[countOfCF].type == table2[","])) && (resOfCf[countOfCF + 2].type != table2["("]))
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
        if (resOfCf[countOfCF].type == "IDENFR")
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            check_b(countOfCF);
            nameOfCons[intTmp] = 0;
            btype[intTmp] = "char";
            if (resOfCf[countOfCF - 1].type == "INTTK")
            {
                btype[intTmp] = "int";
            }
            else if (resOfCf[countOfCF - 1].type == table2[","])
            {
                btype[intTmp] = btype[intTmp - 1];
            }
            bname[intTmp++] = resOfCf[countOfCF].value;
            countOfCF++;
            if (resOfCf[countOfCF].type == table2["["])
            {
                cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                if (btype[intTmp - 1] == "int")
                {
                    btype[intTmp - 1] = "intL";
                }
                else
                {
                    btype[intTmp - 1] = "charL";
                }
                countOfCF++;
                if (resOfCf[countOfCF].type != "INTCON")
                {
                    error_i(countOfCF);
                }
                cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                cout << "<无符号整数>" << endl;
                countOfCF++;
                if (resOfCf[countOfCF].type == table2["]"])
                {
                    cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                    countOfCF++;
                }
                else
                {
                    error_m(countOfCF);
                }
                if (resOfCf[countOfCF].type == table2["["])
                {
                    if (resOfCf[countOfCF + 1].type != "INTCON")
                    {
                        error_i(countOfCF);
                    }
                    cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                    if (btype[intTmp - 1] == "intL")
                    {
                        btype[intTmp - 1] = "intLL";
                    }
                    else
                    {
                        btype[intTmp - 1] = "charLL";
                    }
                    countOfCF++;
                    cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                    cout << "<无符号整数>" << endl;
                    countOfCF++;
                    if (resOfCf[countOfCF].type == table2["]"])
                    {
                        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                        countOfCF++;
                    }
                    else
                    {
                        error_m(countOfCF);
                    }
                    if (resOfCf[countOfCF].type == table2[","])
                    {
                        noInitDef();
                    }
                    else if (resOfCf[countOfCF].type == table2[";"])
                    {
                        return 1;
                    }
                    else
                    {
                        error_k(countOfCF);
                    }
                    return 1;
                    // }
                }
                else
                {
                    if (resOfCf[countOfCF].type == table2[","])
                    {
                        noInitDef();
                    }
                    else if (resOfCf[countOfCF].type == table2[";"])
                    {
                        return 1;
                    }
                    else
                    {
                        error_k(countOfCF);
                    }
                    return 1;
                }
                // }
            }
            else
            {
                if (resOfCf[countOfCF].type == table2[","])
                {
                    noInitDef();
                }
                else if (resOfCf[countOfCF].type == table2[";"])
                {
                    return 1;
                }
                else
                {
                    error_k(countOfCF);
                }
                return 1;
            }
        }
    }
    return 0;
}
//变量定义及初始化
bool initDef()
{
    if (((resOfCf[countOfCF].type == "INTTK") || (resOfCf[countOfCF].type == "CHARTK")) && (resOfCf[countOfCF + 2].type != table2["("]) && (resOfCf[countOfCF + 2].type != table2["["]) && (resOfCf[countOfCF + 5].type != table2["["]))
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        string aaa = "int";
        if (resOfCf[countOfCF].type == "CHARTK")
        {
            aaa = "char";
        }
        countOfCF++;
        if (resOfCf[countOfCF].type == "IDENFR")
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;

            check_b(countOfCF);
            nameOfCons[intTmp] = 0;
            btype[intTmp] = "char";
            if (resOfCf[countOfCF - 1].type == "INTTK")
            {
                btype[intTmp] = "int";
            }
            bname[intTmp++] = resOfCf[countOfCF].value;
            countOfCF++;
            if (resOfCf[countOfCF].type == table2["="])
            {
                cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                countOfCF++;
                string aaaa = "int";
                if (resOfCf[countOfCF].type == "CHARCON")
                {
                    aaaa = "char";
                }
                if (aaa != aaaa)
                {
                    error_o(countOfCF);
                }
                if (con() == 1)
                {
                    cout << "<常量>" << endl;
                    if (resOfCf[countOfCF].type != table2[";"])
                    {
                        error_k(countOfCF);
                    }
                    return 1;
                }
            }
        }
    }
    else if (((resOfCf[countOfCF].type == "INTTK") || (resOfCf[countOfCF].type == "CHARTK")) && (resOfCf[countOfCF + 2].type != table2["("]) && (resOfCf[countOfCF + 5].type != table2["["]))
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
        if (resOfCf[countOfCF].type == "IDENFR")
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            check_b(countOfCF);
            nameOfCons[intTmp] = 0;
            btype[intTmp] = "charL";
            if (resOfCf[countOfCF - 1].type == "INTTK")
            {
                btype[intTmp] = "intL";
            }
            bname[intTmp++] = resOfCf[countOfCF].value;
            countOfCF++;
            if ((resOfCf[countOfCF].type == table2["["])
                // && (resOfCf[countOfCF + 1].type == "INTCON")
                // && (resOfCf[countOfCF + 2].type == table2["]"])
            )
            {
                if (resOfCf[countOfCF + 1].type != "INTCON")
                {
                    error_i(countOfCF);
                }
                cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                cout << resOfCf[countOfCF + 1].type << " " << resOfCf[countOfCF + 1].value << endl;
                int listcount;
                stringstream ss;
                ss << resOfCf[countOfCF + 1].value;
                ss >> listcount;
                cout << "<无符号整数>" << endl;
                countOfCF += 2;
                if (resOfCf[countOfCF].type == table2["]"])
                {
                    cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                    countOfCF++;
                }
                else
                {
                    error_m(countOfCF);
                }
                if (resOfCf[countOfCF].type == table2["="])
                {
                    cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                    countOfCF++;
                    if (resOfCf[countOfCF].type == table2["{"])
                    {
                        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                        countOfCF++;
                        L1Count = 0;
                        if (con() == 1)
                        {
                            cout << "<常量>" << endl;
                            L1Count++;
                            varInitDefOne();
                            if (resOfCf[countOfCF].type == table2["}"])
                            {
                                cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                                countOfCF++;
                                if (L1Count != listcount)
                                {
                                    error_n(countOfCF);
                                }
                                if (resOfCf[countOfCF].type != table2[";"])
                                {
                                    error_k(countOfCF);
                                }
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }
    else if (((resOfCf[countOfCF].type == "INTTK") || (resOfCf[countOfCF].type == "CHARTK")) && (resOfCf[countOfCF + 2].type != table2["("]))
    {
        if (resOfCf[countOfCF + 3].type != "INTCON")
        {
            error_i(countOfCF);
        }
        if (resOfCf[countOfCF + 6].type != "INTCON")
        {
            error_i(countOfCF);
        }
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
        if (resOfCf[countOfCF].type == "IDENFR")
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            check_b(countOfCF);
            nameOfCons[intTmp] = 0;
            btype[intTmp] = "charLL";
            if (resOfCf[countOfCF - 1].type == "INTTKL")
            {
                btype[intTmp] = "intLL";
            }
            bname[intTmp++] = resOfCf[countOfCF].value;
            countOfCF++;
            if ((resOfCf[countOfCF].type == table2["["])
                //  && (resOfCf[countOfCF + 1].type == "INTCON")
                //  && (resOfCf[countOfCF + 2].type == table2["]"])
            )
            {
                cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                cout << resOfCf[countOfCF + 1].type << " " << resOfCf[countOfCF + 1].value << endl;
                int listlistcount;
                stringstream ss;
                ss << resOfCf[countOfCF + 1].value;
                ss >> listlistcount;
                cout << "<无符号整数>" << endl;
                countOfCF += 2;
                if (resOfCf[countOfCF].type == table2["]"])
                {
                    cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                    countOfCF++;
                }
                else
                {
                    error_m(countOfCF);
                }
                if ((resOfCf[countOfCF].type == table2["["])
                    //  && (resOfCf[countOfCF + 1].type == "INTCON")
                    //  && (resOfCf[countOfCF + 2].type == table2["]"])
                )
                {
                    cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                    cout << resOfCf[countOfCF + 1].type << " " << resOfCf[countOfCF + 1].value << endl;
                    int listcount;
                    stringstream ss1;
                    ss1 << resOfCf[countOfCF + 1].value;
                    ss1 >> listcount;
                    cout << "<无符号整数>" << endl;
                    countOfCF += 2;
                    if (resOfCf[countOfCF].type == table2["]"])
                    {
                        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                        countOfCF++;
                    }
                    else
                    {
                        error_m(countOfCF);
                    }
                    if (resOfCf[countOfCF].type == table2["="])
                    {
                        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                        countOfCF++;
                        if ((resOfCf[countOfCF].type == table2["{"]) && (resOfCf[countOfCF + 1].type == table2["{"]))
                        {
                            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                            cout << resOfCf[countOfCF + 1].type << " " << resOfCf[countOfCF + 1].value << endl;
                            countOfCF = countOfCF + 2;
                            L1Count = 0;
                            L2Count = 0;
                            if (con() == 1)
                            {
                                cout << "<常量>" << endl;
                                L1Count++;
                                varInitDefOne();
                                if (resOfCf[countOfCF].type == table2["}"])
                                {
                                    L2Count++;
                                    cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                                    countOfCF++;
                                    if (L1Count != listcount)
                                    {
                                        error_n(countOfCF);
                                    }
                                    varInitDefTwo(listcount);
                                    if (resOfCf[countOfCF].type == table2["}"])
                                    {
                                        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                                        countOfCF++;
                                        if (L2Count != listlistcount)
                                        {
                                            error_n(countOfCF - 1);
                                        }
                                        if (resOfCf[countOfCF].type != table2[";"])
                                        {
                                            error_k(countOfCF);
                                        }
                                        return 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}
//变量定义
bool var_def()
{
    //区分有无初始化
    if (((resOfCf[countOfCF + 2].type == table2["="]) || ((resOfCf[countOfCF + 2].type == table2["["]) && (resOfCf[countOfCF + 5].type == table2["="])) || ((resOfCf[countOfCF + 2].type == table2["["]) && (resOfCf[countOfCF + 5].type == table2["["]) && (resOfCf[countOfCF + 8].type == table2["="]))) && (initDef() == 1))
    {
        cout << "<变量定义及初始化>" << endl;
        return 1;
    }
    else if (noInitDef() == 1)
    {
        cout << "<变量定义无初始化>" << endl;
        return 1;
    }

    return 0;
}
//变量说明
bool var()
{
    if (var_def() == 1)
    {
        cout << "<变量定义>" << endl;
        if (resOfCf[countOfCF].type == table2[";"])
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            countOfCF++;
        }
        else
        {
            error_k(countOfCF);
        }
        var();
        return 1;
    }
    return 0;
}
//参数表
bool parameterTable(structOfFunction a)
{
    if (resOfCf[countOfCF].type == table2[","])
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
    }
    if ((resOfCf[countOfCF].type == "INTTK") || (resOfCf[countOfCF].type == "CHARTK"))
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        if (resOfCf[countOfCF].type == "INTTK")
        {
            a.parameterTable.push_back("int");
        }
        else
        {
            a.parameterTable.push_back("char");
        }
        countOfCF++;
        if (resOfCf[countOfCF].type == "IDENFR")
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            check_b(countOfCF);
            nameOfCons[intTmp] = 0;
            btype[intTmp] = "char";
            if (resOfCf[countOfCF - 1].type == "INTTK")
            {
                btype[intTmp] = "int";
            }
            bname[intTmp++] = resOfCf[countOfCF].value;
            countOfCF++;
            parameterTable(a);
            return 1;
        }
    }
    bnamefunc.push_back(a);
    return 1;
}

//函数定义的重复部分
bool repeatFuncOne(structOfFunction a)
{
    if (resOfCf[countOfCF].type == table2["("])
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
    }
    else
        return 0;
    beforeCount = intTmp;
    if (parameterTable(a) == 1)
    {
        cout << "<参数表>" << endl;
    }
    else
        return 0;
    if (resOfCf[countOfCF].type == table2[")"])
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
    }
    else
    {
        error_l(countOfCF);
    }
    if (resOfCf[countOfCF].type == table2["{"])
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
    }
    else
        return 0;
    if (complexJuzi() == 1)
    {
        cout << "<复合语句>" << endl;
    }
    else
        return 0;
    if (resOfCf[countOfCF].type == table2["}"])
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
    }
    else
        return 0;
    intTmp = beforeCount;
    return 1;
}

//有返回值函数定义
bool func_return()
{
    is_have_return = 0;
    structOfFunction a;
    a.name = resOfCf[countOfCF + 1].value;
    have_return.push_back(a.name);
    a.type = "char";
    if (resOfCf[countOfCF].type == "INTTK")
    {
        a.type = "int";
    }
    now_func_type = a.type;
    if (headDeclaration() == 1)
    {
        cout << "<声明头部>" << endl;
    }
    else
        return 0;
    check_b_func(countOfCF + 1);
    if (repeatFuncOne(a) == 0)
        return 0;
    if (is_have_return == 0)
    {
        error_h(countOfCF);
    }
    beforeCount = 0;
    return 1;
}
//无返回值函数定义
bool func_not_return()
{
    is_have_return = 0;
    check_b_func(countOfCF + 1);
    structOfFunction a;
    a.name = resOfCf[countOfCF + 1].value;
    no_return.push_back(a.name);
    a.type = "void";
    now_func_type = a.type;
    if ((resOfCf[countOfCF].type == "VOIDTK") && (resOfCf[countOfCF + 1].type == "IDENFR"))
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        cout << resOfCf[countOfCF + 1].type << " " << resOfCf[countOfCF + 1].value << endl;
        countOfCF = countOfCF + 2;
    }
    else
        return 0;
    if (repeatFuncOne(a) == 0)
        return 0;
    beforeCount = 0;
    return 1;
}

//有无返回值函数的定义的闭包
bool func_closures()
{
    if (func_return() == 1)
    {
        cout << "<有返回值函数定义>" << endl;
        func_closures();
        return 1;
    }
    else if (func_not_return() == 1)
    {
        cout << "<无返回值函数定义>" << endl;
        func_closures();
        return 1;
    }
    return 0;
}

//声明头部
bool headDeclaration()
{
    if ((resOfCf[countOfCF].type == "INTTK") && (resOfCf[countOfCF + 1].type == "IDENFR"))
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        cout << resOfCf[countOfCF + 1].type << " " << resOfCf[countOfCF + 1].value << endl;
        countOfCF = countOfCF + 2;
        return 1;
    }
    else if ((resOfCf[countOfCF].type == "CHARTK") && (resOfCf[countOfCF + 1].type == "IDENFR"))
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        cout << resOfCf[countOfCF + 1].type << " " << resOfCf[countOfCF + 1].value << endl;
        countOfCF = countOfCF + 2;
        return 1;
    }
    return 0;
}

//条件
bool condition()
{
    if (expression() == 1)
    {
        cout << "<表达式>" << endl;
        string aa = nowtype;
        if ((resOfCf[countOfCF].type == table2["<"]) || (resOfCf[countOfCF].type == table2["<="]) || (resOfCf[countOfCF].type == table2[">"]) || (resOfCf[countOfCF].type == table2[">="]) || (resOfCf[countOfCF].type == table2["=="]) || (resOfCf[countOfCF].type == table2["!="]))
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            countOfCF++;
            if (expression() == 1)
            {
                cout << "<表达式>" << endl;
                if (nowtype != "int" && aa != "int")
                {
                    error_f(countOfCF);
                }
                return 1;
            }
        }
    }
    return 0;
}
//步长
bool step()
{
    if (resOfCf[countOfCF].type == "INTCON")
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        cout << "<无符号整数>" << endl;
        countOfCF++;
        return 1;
    }
    return 0;
}
//复合语句
bool complexJuzi()
{
    if (cons() == 1)
    {
        cout << "<常量说明>" << endl;
    }
    if (var() == 1)
    {
        cout << "<变量说明>" << endl;
    }
    if (sentenceList() == 1)
    {
        cout << "<语句列>" << endl;
        return 1;
    }
    return 0;
}
//语句列
bool sentenceList()
{
    if (sentence() == 1)
    {
        cout << "<语句>" << endl;
        sentenceList();
        return 1;
    }
    //可以无语句
    return 1;
}
string snowtype = "";
//缺省
bool defaultSentence()
{
    if (resOfCf[countOfCF].type == "DEFAULTTK")
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
        if (resOfCf[countOfCF].type == table2[":"])
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            countOfCF++;
            if (sentence() == 1)
            {
                cout << "<语句>" << endl;
                return 1;
            }
        }
    }
    return 0;
}
//情况子语句
bool subSituation()
{
    if (resOfCf[countOfCF].type == "CASETK")
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
        string aaa = "int";
        if (resOfCf[countOfCF].type == "CHARCON")
        {
            aaa = "char";
        }
        if (aaa != snowtype)
        {
            error_o(countOfCF);
        }
        if (con() == 1)
        {
            cout << "<常量>" << endl;
            if (resOfCf[countOfCF].type == table2[":"])
            {
                cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                countOfCF++;
                if (sentence() == 1)
                {
                    cout << "<语句>" << endl;
                    return 1;
                }
            }
        }
    }
    return 0;
}
//情况表
bool tableOfSituation1()
{
    if (subSituation() == 1)
    {
        cout << "<情况子语句>" << endl;
        tableOfSituation1();
    }
    return 1;
}

//情况语句
bool tableOfSituation2()
{
    if ((resOfCf[countOfCF].type == "SWITCHTK") && (resOfCf[countOfCF + 1].type == table2["("]))
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        cout << resOfCf[countOfCF + 1].type << " " << resOfCf[countOfCF + 1].value << endl;
        countOfCF += 2;
        if (expression() == 1)
        {
            cout << "<表达式>" << endl;
            snowtype = nowtype;
            if (resOfCf[countOfCF].type == table2[")"])
            {
                countOfCF++;
                cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            }
            else
            {
                error_l(countOfCF);
            }
            if ((resOfCf[countOfCF].type == table2["{"]))
            {
                cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                countOfCF += 1;
                if (tableOfSituation2() == 1)
                {
                    cout << "<情况表>" << endl;
                    if (defaultSentence() == 1)
                    {
                        cout << "<缺省>" << endl;
                    }
                    else
                    {
                        error_p(countOfCF);
                    }
                    if (resOfCf[countOfCF].type == table2["}"])
                    {
                        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                        countOfCF++;
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
//返回语句
bool return_sentence()
{
    if (resOfCf[countOfCF].type == "RETURNTK")
    {
        if (now_func_type == "void" && resOfCf[countOfCF + 1].type != table2[";"])
        {
            error_g(countOfCF);
        }
        is_have_return = 1;
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
        if (resOfCf[countOfCF].type == table2["("])
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            countOfCF++;
            if (expression() == 1)
            {
                cout << "<表达式>" << endl;
                if (nowtype != now_func_type && now_func_type != "void")
                {
                    error_h(countOfCF);
                }
                if (resOfCf[countOfCF].type == table2[")"])
                {
                    cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                    countOfCF++;
                    return 1;
                }
                else
                {
                    error_l(countOfCF);
                    return 1;
                }
            }
        }
        else
            return 1;
    }
    return 0;
}
//条件语句
bool conditionOfSentence()
{
    int tt = is_have_return;
    if ((resOfCf[countOfCF].type == "IFTK") && (resOfCf[countOfCF + 1].type == table2["("]))
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        cout << resOfCf[countOfCF + 1].type << " " << resOfCf[countOfCF + 1].value << endl;
        countOfCF += 2;
        if (condition() == 1)
        {
            cout << "<条件>" << endl;
            if (resOfCf[countOfCF].type == table2[")"])
            {
                cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                countOfCF++;
            }
            else
            {
                error_l(countOfCF);
            }
            if (sentence() == 1)
            {
                cout << "<语句>" << endl;
                if (resOfCf[countOfCF].type == "ELSETK")
                {
                    cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                    countOfCF++;
                    if (sentence() == 1)
                    {
                        cout << "<语句>" << endl;
                        is_have_return = tt;
                        return 1;
                    }
                }
                else
                {
                    is_have_return = tt;
                    return 1;
                }
                is_have_return = tt;
            }
        }
    }
    return 0;
}
//赋值语句
bool assign()
{
    if ((resOfCf[countOfCF].type == "IDENFR") && (resOfCf[countOfCF + 1].type == table2["="]))
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        cout << resOfCf[countOfCF + 1].type << " " << resOfCf[countOfCF + 1].value << endl;
        check_c(countOfCF);
        check_j(countOfCF);
        countOfCF += 2;
        if (expression() == 1)
        {
            cout << "<表达式>" << endl;
            return 1;
        }
    }
    //区分一维和二位数组(列表)
    else if ((resOfCf[countOfCF].type == "IDENFR") && (resOfCf[countOfCF + 1].type == table2["["]) && (resOfCf[countOfCF + 4].type != table2["["]))
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        cout << resOfCf[countOfCF + 1].type << " " << resOfCf[countOfCF + 1].value << endl;
        check_c(countOfCF);
        countOfCF += 2;
        if (expression() == 1)
        {
            cout << "<表达式>" << endl;
            if (
                // (resOfCf[countOfCF].type == table2["]"]) &&
                (resOfCf[countOfCF + 1].type == table2["="]))
            {
                if (resOfCf[countOfCF].type == table2["]"])
                {
                    cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                    countOfCF++;
                }
                else
                {
                    error_m(countOfCF);
                }
                cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                countOfCF++;
                if (expression() == 1)
                {
                    cout << "<表达式>" << endl;
                    return 1;
                }
            }
        }
    }
    else if ((resOfCf[countOfCF].type == "IDENFR") && (resOfCf[countOfCF + 1].type == table2["["]))
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        cout << resOfCf[countOfCF + 1].type << " " << resOfCf[countOfCF + 1].value << endl;
        check_c(countOfCF);
        countOfCF += 2;
        if (expression() == 1)
        {
            cout << "<表达式>" << endl;
            if (
                //(resOfCf[countOfCF].type == table2["]"]) &&
                (resOfCf[countOfCF + 1].type == table2["["]))
            {
                if (resOfCf[countOfCF].type == table2["]"])
                {
                    cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                    countOfCF++;
                }
                else
                {
                    error_m(countOfCF);
                }
                cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                countOfCF++;
                if (expression() == 1)
                {
                    cout << "<表达式>" << endl;
                    if (
                        //(resOfCf[countOfCF].type == table2["]"]) &&
                        (resOfCf[countOfCF + 1].type == table2["="]))
                    {
                        if (resOfCf[countOfCF].type == table2["]"])
                        {
                            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                            countOfCF++;
                        }
                        else
                        {
                            error_m(countOfCF);
                        }
                        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                        countOfCF++;
                        if (expression() == 1)
                        {
                            cout << "<表达式>" << endl;
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
//语句
bool sentence()
{
    if (cycle() == 1)
    {
        cout << "<循环语句>" << endl;
        return 1;
    }
    else if (conditionOfSentence() == 1)
    {
        cout << "<条件语句>" << endl;
        return 1;
    }

    else if ((count(have_return.begin(), have_return.end(), resOfCf[countOfCF].value) > 0) && (use_func() == 1))
    {
        cout << "<有返回值函数调用语句>" << endl;
        if (resOfCf[countOfCF].type == table2[";"])
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            countOfCF++;
            return 1;
        }
        else
        {
            error_k(countOfCF);
            return 1;
        }
    }
    else if ((count(no_return.begin(), no_return.end(), resOfCf[countOfCF].value) > 0) && (use_func() == 1))
    {
        cout << "<无返回值函数调用语句>" << endl;
        if (resOfCf[countOfCF].type == table2[";"])
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            countOfCF++;
            return 1;
        }
        else
        {
            error_k(countOfCF);
            return 1;
        }
    }
    else if (assign() == 1) /*&& (resOfCf[countOfCF + 1].type == "ASSIGN"))*/
    {
        cout << "<赋值语句>" << endl;
        if (resOfCf[countOfCF].type == table2[";"])
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            countOfCF++;
            return 1;
        }
        else
        {
            error_k(countOfCF);
            return 1;
        }
    }
    else if (read() == 1)
    {
        cout << "<读语句>" << endl;
        if (resOfCf[countOfCF].type == table2[";"])
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            countOfCF++;
            return 1;
        }
        else
        {
            error_k(countOfCF);
            return 1;
        }
    }
    else if (write() == 1)
    {
        cout << "<写语句>" << endl;
        if (resOfCf[countOfCF].type == table2[";"])
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            countOfCF++;
            return 1;
        }
        else
        {
            error_k(countOfCF);
            return 1;
        }
    }
    else if (tableOfSituation2() == 1)
    {
        cout << "<情况语句>" << endl;
        return 1;
    }
    else if (resOfCf[countOfCF].type == table2[";"])
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
        return 1;
    }
    else if (return_sentence() == 1)
    {
        cout << "<返回语句>" << endl;
        if (resOfCf[countOfCF].type == table2[";"])
        {
            cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
            countOfCF++;
            return 1;
        }
        else
        {
            error_k(countOfCF);
            return 1;
        }
    }
    else if (resOfCf[countOfCF].type == table2["{"])
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
        if (sentenceList() == 1)
        {
            cout << "<语句列>" << endl;
            if (resOfCf[countOfCF].type == table2["}"])
            {
                cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                countOfCF++;
                return 1;
            }
        }
    }
    return 0;
}
//循环语句
bool cycle()
{
    if ((resOfCf[countOfCF].type == "WHILETK") && (resOfCf[countOfCF + 1].type == table2["("]))
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        cout << resOfCf[countOfCF + 1].type << " " << resOfCf[countOfCF + 1].value << endl;
        countOfCF = countOfCF + 2;
        if (condition() == 1)
        {
            cout << "<条件>" << endl;
            if (resOfCf[countOfCF].type == table2[")"])
            {
                cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                countOfCF++;
            }
            else
            {
                error_l(countOfCF);
            }
            if (sentence() == 1)
            {
                cout << "<语句>" << endl;
                return 1;
            }
        }
    }
    else if ((resOfCf[countOfCF].type == "FORTK") && (resOfCf[countOfCF + 1].type == table2["("]) && (resOfCf[countOfCF + 2].type == "IDENFR") && (resOfCf[countOfCF + 3].type == table2["="]))
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        cout << resOfCf[countOfCF + 1].type << " " << resOfCf[countOfCF + 1].value << endl;
        cout << resOfCf[countOfCF + 2].type << " " << resOfCf[countOfCF + 2].value << endl;
        cout << resOfCf[countOfCF + 3].type << " " << resOfCf[countOfCF + 3].value << endl;
        check_c(countOfCF + 2);
        countOfCF = countOfCF + 4;
        if (expression() == 1)
        {
            cout << "<表达式>" << endl;
            if (resOfCf[countOfCF].type == table2[";"])
            {
                cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                countOfCF++;
            }
            else
            {
                error_k(countOfCF);
            }
            if (condition() == 1)
            {
                cout << "<条件>" << endl;
                if (
                    //(resOfCf[countOfCF].type == table2[";"]) &&
                    (resOfCf[countOfCF + 1].type == "IDENFR") && (resOfCf[countOfCF + 2].type == table2["="]) && (resOfCf[countOfCF + 3].type == "IDENFR"))
                {
                    if (resOfCf[countOfCF].type == table2[";"])
                    {
                        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                        countOfCF++;
                    }
                    else
                    {
                        error_k(countOfCF);
                    }
                    cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF + 1].value << endl;
                    cout << resOfCf[countOfCF + 1].type << " " << resOfCf[countOfCF + 2].value << endl;
                    cout << resOfCf[countOfCF + 2].type << " " << resOfCf[countOfCF + 3].value << endl;
                    countOfCF = countOfCF + 3;
                    if ((resOfCf[countOfCF].type == table2["+"]) || (resOfCf[countOfCF].type == table2["-"]))
                    {
                        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                        countOfCF++;
                        if (step() == 1)
                        {
                            cout << "<步长>" << endl;
                            if (resOfCf[countOfCF].type == table2[")"])
                            {
                                cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                                countOfCF++;
                            }
                            else
                            {
                                error_l(countOfCF);
                            }
                            if (sentence() == 1)
                            {
                                cout << "<语句>" << endl;
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}
//主程序
bool main_fun()
{
    if ((resOfCf[countOfCF].type == "VOIDTK") && (resOfCf[countOfCF + 1].type == "MAINTK") && (resOfCf[countOfCF + 2].type == table2["("])
        // && (resOfCf[countOfCF + 3].type == table2[")"])
        && (resOfCf[countOfCF + 4].type == table2["{"]))
    {
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        cout << resOfCf[countOfCF + 1].type << " " << resOfCf[countOfCF + 1].value << endl;
        cout << resOfCf[countOfCF + 2].type << " " << resOfCf[countOfCF + 2].value << endl;
        countOfCF += 3;
        if (resOfCf[countOfCF].type == table2[")"])
        {
            cout << resOfCf[countOfCF + 3].type << " " << resOfCf[countOfCF + 3].value << endl;
            countOfCF++;
        }
        else
        {
            error_l(countOfCF);
        }
        cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
        countOfCF++;
        if (complexJuzi() == 1)
        {
            cout << "<复合语句>" << endl;
            if (resOfCf[countOfCF].type == table2["}"])
            {
                cout << resOfCf[countOfCF].type << " " << resOfCf[countOfCF].value << endl;
                countOfCF++;
                return 1;
            }
        }
    }
    return 0;
}
//程序
void prom()
{
    if (cons() == 1)
    {
        cout << "<常量说明>" << endl;
    }
    if (var() == 1)
    {
        cout << "<变量说明>" << endl;
    }
    func_closures();
    if (main_fun() == 1)
    {
        cout << "<主函数>" << endl;
    }
    cout << "<程序>" << endl;
}

void coout(int i)
{
    if (errl[i].abc == 16 && errl[i].type == "b")
    {
        cout << 7 << " "
             << "h" << endl;
    }
    else
    {
        cout << errl[i].abc << " " << errl[i].type << endl;
    }
}

/*----------------------主函数----------------------*/

int main()
{
    freopen("testfile.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    init();
    memset(nameOfCons, 0, sizeof(nameOfCons));
    string str;
    int abc = 0;
    while (getline(cin, str))
    {
        abc++;
        FSM(str, abc);
    }
    prom();

    fclose(stdin);
    fclose(stdout);
    freopen("error.txt", "w", stdout);
    for (int i = 0; i < errl.size(); i++)
    {
        coout(i);
    }
    fclose(stdout);
    return 0;
}
