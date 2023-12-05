#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

map<string, string> mapping;

// 初始化
void init()
{
    mapping["const"] = "CONSTTK";
    mapping["int"] = "INTTK";
    mapping["char"] = "CHARTK";
    mapping["void"] = "VOIDTK";
    mapping["main"] = "MAINTK";
    mapping["if"] = "IFTK";
    mapping["else"] = "ELSETK";
    mapping["switch"] = "SWITCHTK";
    mapping["case"] = "CASETK";
    mapping["default"] = "DEFAULTTK";
    mapping["while"] = "WHILETK";
    mapping["for"] = "FORTK";
    mapping["scanf"] = "SCANFTK";
    mapping["printf"] = "PRINTFTK";
    mapping["return"] = "RETURNTK";
    // ---------- 这是分割线,以上与IDENFR一起判断, 一下独立判断
    mapping["+"] = "PLUS";
    mapping["-"] = "MINU";
    mapping["*"] = "MULT";
    mapping["/"] = "DIV";
    mapping["<"] = "LSS";
    mapping["<="] = "LEQ";
    mapping[">"] = "GRE";
    mapping[">="] = "GEQ";
    mapping["=="] = "EQL";
    mapping["!="] = "NEQ";
    mapping[":"] = "COLON";
    mapping["="] = "ASSIGN";
    mapping[";"] = "SEMICN";
    mapping[","] = "COMMA";
    mapping["("] = "LPARENT";
    mapping[")"] = "RPARENT";
    mapping["["] = "LBRACK";
    mapping["]"] = "RBRACK";
    mapping["{"] = "LBRACE";
    mapping["}"] = "RBRACE";
}

// 判断是否是关键字
void isKeyword(string str)
{
    string s = str;
    // lower string
    for (int i = 0; i < str.length(); i++)
    {
        if (s[i] <= 'Z' && s[i] >= 'A')
        {
            s[i] = s[i] - 'A' + 'a';
        }
    }
    // 如果是关键字
    if (mapping.count(s))
    {
        cout << mapping[s] << " " << str << endl;
    }
    // 不是关键字就是标识符
    else
        cout << "IDENFR " << str << endl;
}

// 是否是字符
int isletter(char a)
{
    if ((a >= 'a' && a <= 'z') || (a >= 'A' & a <= 'Z') || a == '_')
        return 1;
    return 0;
}

// 是否是数字
int isdigit(char a)
{
    if (a >= '0' && a <= '9')
        return 1;
    return 0;
}

// 初始state为0, 根据类别变化
int state = 0;

// 单词(词素)
string word = "";

// 有限状态机函数
void FSM(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        switch (state)
        {
        // 初始判断
        case 0:
            // KEYWORD和IDENFR, 分割线以上部分
            if (isletter(str[i]))
            {
                state = 1;
                word += str[i];
                break;
            }
            // INTCON
            if (isdigit(str[i]))
            {
                state = 2;
                word += str[i];
                break;
            }
            // CHARCON
            if (str[i] == '\'')
            {
                state = 3;
                break;
            }
            // STRCON
            if (str[i] == '"')
            {
                state = 4;
                break;
            }
            // KEYWORD, 分割线以下部分
            else
            {
                if (mapping.count(str.substr(i, 2)))
                {
                    cout << mapping[str.substr(i, 2)] << " " << str.substr(i, 2) << endl;
                    // 一次性取了俩,手动多跳一次i
                    i++;
                    break;
                }
                else if (mapping.count(str.substr(i, 1)))
                {
                    cout << mapping[str.substr(i, 1)] << " " << str[i] << endl;
                    break;
                }
                break;
            }
        // KEYWORD
        case 1:
            if (isletter(str[i]) || isdigit(str[i]))
            {
                word += str[i];
                break;
            }
            else
            {
                // 不是关键字则是IDENFR
                isKeyword(word);
                word = "";
                // 返回左边索引,避免漏掉判断类似main(中的(这样的情况
                i--;
                state = 0;
                break;
            }
        // INTCON
        case 2:
            if (isdigit(str[i]))
            {
                word += str[i];
                break;
            }
            else
            {
                cout << "INTCON " << word << endl;
                word = "";
                i--;
                state = 0;
                break;
            }
        // CHARCON
        case 3:
            // 不严谨的判断右单引号
            if (str[i] == '\'')
            {
                if (word.length() == 1)
                {
                    cout << "CHARCON " << word << endl;
                    word = "";
                    state = 0;
                    break;
                }
                else
                {
                    cout << "format error: " << word << " is not char" << endl;
                    word = "";
                    state = 0;
                    break;
                }
            }
            else if (str[i] == '\\')
            {
                if (str[i + 1] == '\\')
                {
                    word += '\\';
                    i++;
                    break;
                }
                else if (str[i + 1] == '\'')
                {
                    word += '\'';
                    i++;
                    break;
                }
            }
            else
            {   
                word += str[i];
                break;
            }
        // STRCON
        case 4:
            // 不严谨的判断右双引号
            if (str[i] == '"')
            {
                cout << "STRCON " << word << endl;
                word = "";
                state = 0;
                break;
            }
            else if (str[i] == '\\')
            {
                word += str.substr(i, 2);
                i++;
                break;
            }
            else
            {
                word += str[i];
                break;
            }
        default:
            break;
        }
    }
}

int main()
{
    freopen("testfile.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    init();
    string str;
    while (getline(cin, str))
    {
        FSM(str);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}