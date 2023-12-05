#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

fstream f("testfile.txt");
ofstream o("output.txt");

map<string, string> mapping;

void init()
{
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
}

bool intN();
bool con();
bool valuePara();
bool funcR();
bool funcNotR();
bool factor();
bool itemOne();
bool item();
bool expreOne();
bool expre();
bool read();
bool write();
bool cons();
bool conD();
bool varInitOne();
bool varInitTwo();
bool varNoInit();
bool varInit();
bool varD();
bool var();
bool para();
bool functionReturn();
bool functionNotReturn();
bool funcClosures();
bool declareHead();
bool condition();
bool step();
bool complexSentence();
bool manySentence();
bool defaultSentence();
bool situatioonSubsen();
bool situationTable();
bool situationSentence();
bool returnSentence();
bool conditionSentence();
bool assign();
bool sentence();
bool cycly();
bool mainF();
void prom();
struct token
{
    string str;
    string type;
};

vector<token> lexicalAnalysisResults;

int grammer_i = 0;

vector<string> have_return;
vector<string> no_return;

void judge(string str)
{
    string temp = str;
    for (int i = 0; i < str.length(); i++)
        if (temp[i] <= 'Z' && temp[i] >= 'A')
            temp[i] = temp[i] - 'A' + 'a';
    if (mapping.count(temp))
    {
        token tmp;
        tmp.str = str;
        tmp.type = mapping[temp];
        lexicalAnalysisResults.push_back(tmp);
    }
    else
    {
        token tmp;
        tmp.str = str;
        tmp.type = "IDENFR";
        lexicalAnalysisResults.push_back(tmp);
    }
}

int isletter(char a)
{
    if ((a >= 'a' && a <= 'z') || (a >= 'A' & a <= 'Z') || a == '_')
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

string temp = "";

void op(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        switch (state)
        {
        case 0:
            if (isletter(str[i]))
            {
                state = 1;
                temp += str[i];
                break;
            }
            if (isdigit(str[i]))
            {
                state = 2;
                temp += str[i];
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
                if (mapping.count(strt))
                {
                    token tmp;
                    tmp.str = strt;
                    tmp.type = mapping[strt];
                    lexicalAnalysisResults.push_back(tmp);
                    i++;
                    break;
                }
                if (mapping.count(str.substr(i, 1)))
                {
                    token tmp;
                    tmp.str = str[i];
                    tmp.type = mapping[str.substr(i, 1)];
                    lexicalAnalysisResults.push_back(tmp);
                    break;
                }
                break;
            }
        case 1:
            if (isletter(str[i]) || isdigit(str[i]))
            {
                temp += str[i];
                break;
            }
            else
            {
                judge(temp);
                temp = "";
                i--;
                state = 0;
                break;
            }
        case 2:
            if (isdigit(str[i]))
            {
                temp += str[i];
                break;
            }
            if (str[i] == '.')
            {
                break;
            }
            else
            {
                token tmp;
                tmp.str = temp;
                tmp.type = "INTCON";
                lexicalAnalysisResults.push_back(tmp);
                temp = "";
                i--;
                state = 0;
                break;
            }
        case 3:
            if (str[i] == '\\')
            {
                break;
            }
            if (str[i] == '\'')
            {
                if (temp.length() == 1)
                {
                    token tmp;
                    tmp.str = temp;
                    tmp.type = "CHARCON";
                    lexicalAnalysisResults.push_back(tmp);
                    temp = "";
                    state = 0;
                    break;
                }
                else if (temp.length() == 0)
                {
                }
            }
            else
            {
                temp += str[i];
                break;
            }
        case 4:
            if (str[i] == '"')
            {
                token tmp;
                tmp.str = temp;
                tmp.type = "STRCON";
                lexicalAnalysisResults.push_back(tmp);
                cout << "STRCON" << endl;
                temp = "";
                state = 0;
                break;
            }
            else
            {
                temp += str[i];
                break;
            }
        default:
            break;
        }
    }
}

bool intN()
{
    if ((lexicalAnalysisResults[grammer_i].type == "PLUS") || (lexicalAnalysisResults[grammer_i].type == "MINU"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
        if (lexicalAnalysisResults[grammer_i].type == "INTCON")
        {
            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
            grammer_i++;
            o << "<无符号整数>" << endl;
            o << "<整数>" << endl;
            return 1;
        }
    }
    else
    {
        if (lexicalAnalysisResults[grammer_i].type == "INTCON")
        {
            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
            grammer_i++;
            o << "<无符号整数>" << endl;
            o << "<整数>" << endl;
            return 1;
        }
    }
    return 0;
}

bool con()
{
    if (intN() == 1)
        return 1;
    else if (lexicalAnalysisResults[grammer_i].type == "CHARCON")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
        return 1;
    }
    return 0;
}

bool valuePara()
{
    if (lexicalAnalysisResults[grammer_i].type == "COMMA")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
    }
    if (expre() == 1)
    {
        o << "<表达式>" << endl;
        valuePara();
    }
    return 1;
}

bool funcR()
{
    if ((lexicalAnalysisResults[grammer_i].type == "IDENFR") && (lexicalAnalysisResults[grammer_i + 1].type == "LPARENT"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
        grammer_i += 2;
        if (valuePara() == 1)
        {
            o << "<值参数表>" << endl;
            if (lexicalAnalysisResults[grammer_i].type == "RPARENT")
            {
                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                grammer_i++;
                return 1;
            }
        }
    }
    return 0;
}

bool funcNotR()
{
    if ((lexicalAnalysisResults[grammer_i].type == "IDENFR") && (lexicalAnalysisResults[grammer_i + 1].type == "LPARENT"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
        grammer_i += 2;
        if (valuePara() == 1)
        {
            o << "<值参数表>" << endl;
            if (lexicalAnalysisResults[grammer_i].type == "RPARENT")
            {
                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                grammer_i++;
                return 1;
            }
        }
    }
    return 0;
}

bool factor()
{

    if ((lexicalAnalysisResults[grammer_i].type == "IDENFR") && (lexicalAnalysisResults[grammer_i + 1].type != "LPARENT"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
        if (lexicalAnalysisResults[grammer_i].type == "LBRACK")
        {
            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
            grammer_i++;
            if (expre() == 1)
            {
                o << "<表达式>" << endl;
                if (lexicalAnalysisResults[grammer_i].type == "RBRACK")
                {
                    o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                    grammer_i++;
                    if (lexicalAnalysisResults[grammer_i].type == "LBRACK")
                    {
                        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                        grammer_i++;
                        if (expre() == 1)
                        {
                            o << "<表达式>" << endl;
                            if (lexicalAnalysisResults[grammer_i].type == "RBRACK")
                            {
                                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                                grammer_i++;
                                return 1;
                            }
                        }
                    }
                    else
                        return 1;
                }
            }
        }
        else
            return 1;
    }
    else if (lexicalAnalysisResults[grammer_i].type == "LPARENT")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
        if (expre() == 1)
        {
            o << "<表达式>" << endl;
            if (lexicalAnalysisResults[grammer_i].type == "RPARENT")
            {
                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                grammer_i++;
                return 1;
            }
        }
    }
    else if (intN() == 1)
        return 1;
    else if (lexicalAnalysisResults[grammer_i].type == "CHARCON")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
        return 1;
    }
    else if (funcR() == 1)
    {
        o << "<有返回值函数调用语句>" << endl;
        return 1;
    }
    return 0;
}

bool itemOne()
{
    if ((lexicalAnalysisResults[grammer_i].type == "MULT") || (lexicalAnalysisResults[grammer_i].type == "DIV"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
        if (factor() == 1)
        {
            o << "<因子>" << endl;
            itemOne();
            return 1;
        }
    }
    return 0;
}

bool item()
{
    if (factor() == 1)
    {
        o << "<因子>" << endl;
        itemOne();
        return 1;
    }
    return 0;
}

bool expreOne()
{
    if ((lexicalAnalysisResults[grammer_i].type == "PLUS") || (lexicalAnalysisResults[grammer_i].type == "MINU"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
        if (item() == 1)
        {
            o << "<项>" << endl;
            expreOne();
            return 1;
        }
    }
    return 0;
}

bool expre()
{
    if ((lexicalAnalysisResults[grammer_i].type == "PLUS") || (lexicalAnalysisResults[grammer_i].type == "MINU"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
    }
    if (item() == 1)
    {
        o << "<项>" << endl;
        expreOne();
        return 1;
    }
    return 0;
}

bool read()
{
    if ((lexicalAnalysisResults[grammer_i].type == "SCANFTK") && (lexicalAnalysisResults[grammer_i + 1].type == "LPARENT") && (lexicalAnalysisResults[grammer_i + 2].type == "IDENFR") && (lexicalAnalysisResults[grammer_i + 3].type == "RPARENT"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
        o << lexicalAnalysisResults[grammer_i + 2].type << " " << lexicalAnalysisResults[grammer_i + 2].str << endl;
        o << lexicalAnalysisResults[grammer_i + 3].type << " " << lexicalAnalysisResults[grammer_i + 3].str << endl;
        grammer_i += 4;
        return 1;
    }
    return 0;
}

bool write()
{
    if ((lexicalAnalysisResults[grammer_i].type == "PRINTFTK") && (lexicalAnalysisResults[grammer_i + 1].type == "LPARENT") && (lexicalAnalysisResults[grammer_i + 2].type == "STRCON") && (lexicalAnalysisResults[grammer_i + 3].type == "RPARENT"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
        o << lexicalAnalysisResults[grammer_i + 2].type << " " << lexicalAnalysisResults[grammer_i + 2].str << endl;

        o << "<字符串>" << endl;

        o << lexicalAnalysisResults[grammer_i + 3].type << " " << lexicalAnalysisResults[grammer_i + 3].str << endl;
        grammer_i += 4;
        return 1;
    }
    else if ((lexicalAnalysisResults[grammer_i].type == "PRINTFTK") && (lexicalAnalysisResults[grammer_i + 1].type == "LPARENT") && (lexicalAnalysisResults[grammer_i + 2].type == "STRCON") && (lexicalAnalysisResults[grammer_i + 3].type == "COMMA"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
        o << lexicalAnalysisResults[grammer_i + 2].type << " " << lexicalAnalysisResults[grammer_i + 2].str << endl;
        o << "<字符串>" << endl;
        o << lexicalAnalysisResults[grammer_i + 3].type << " " << lexicalAnalysisResults[grammer_i + 3].str << endl;
        grammer_i += 4;
        if (expre() == 1)
        {
            o << "<表达式>" << endl;
            if (lexicalAnalysisResults[grammer_i].type == "RPARENT")
            {
                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                grammer_i++;
                return 1;
            }
        }
    }
    else if ((lexicalAnalysisResults[grammer_i].type == "PRINTFTK") && (lexicalAnalysisResults[grammer_i + 1].type == "LPARENT"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
        grammer_i += 2;
        if (expre() == 1)
        {
            o << "<表达式>" << endl;
            if (lexicalAnalysisResults[grammer_i].type == "RPARENT")
            {
                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                grammer_i++;
                return 1;
            }
        }
    }
    return 0;
}

bool cons()
{
    if (lexicalAnalysisResults[grammer_i].type == "CONSTTK")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;

        grammer_i++;
        if (conD() == 1)
            o << "<常量定义>" << endl;
        else
            return 0;
        if (lexicalAnalysisResults[grammer_i].type == "SEMICN")
        {
            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
            grammer_i++;
            cons();
            return 1;
        }
    }
    return 0;
}

bool conD()
{
    if (lexicalAnalysisResults[grammer_i].type == "COMMA")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
        if ((lexicalAnalysisResults[grammer_i].type == "IDENFR") && (lexicalAnalysisResults[grammer_i + 2].type != "CHARCON"))
        {
            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
            grammer_i++;
            if (lexicalAnalysisResults[grammer_i].type == "ASSIGN")
            {
                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                grammer_i++;
                intN();
                conD();
                return 1;
            }
        }
        else if (lexicalAnalysisResults[grammer_i].type == "IDENFR")
        {
            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
            grammer_i++;
            if (lexicalAnalysisResults[grammer_i].type == "ASSIGN")
            {
                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                grammer_i++;
                if (lexicalAnalysisResults[grammer_i].type == "CHARCON")
                {
                    o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                    grammer_i++;
                    conD();
                    return 1;
                }
            }
        }
    }
    else if (lexicalAnalysisResults[grammer_i].type == "INTTK")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
        if (lexicalAnalysisResults[grammer_i].type == "IDENFR")
        {
            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
            grammer_i++;
            if (lexicalAnalysisResults[grammer_i].type == "ASSIGN")
            {
                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                grammer_i++;
                intN();
                conD();
                return 1;
            }
        }
    }
    else if (lexicalAnalysisResults[grammer_i].type == "CHARTK")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
        if (lexicalAnalysisResults[grammer_i].type == "IDENFR")
        {
            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
            grammer_i++;
            if (lexicalAnalysisResults[grammer_i].type == "ASSIGN")
            {
                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                grammer_i++;
                if (lexicalAnalysisResults[grammer_i].type == "CHARCON")
                {
                    o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                    grammer_i++;
                    conD();
                    return 1;
                }
            }
        }
    }
    return 0;
}

bool varInitOne()
{
    if (lexicalAnalysisResults[grammer_i].type == "COMMA")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
        if (con() == 1)
        {
            o << "<常量>" << endl;
            varInitOne();
            return 1;
        }
    }
    return 1;
}

bool varInitTwo()
{
    if (lexicalAnalysisResults[grammer_i].type == "COMMA")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
        if (lexicalAnalysisResults[grammer_i].type == "LBRACE")
        {
            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
            grammer_i = grammer_i + 1;
            if (con() == 1)
            {
                o << "<常量>" << endl;
                varInitOne();
                if (lexicalAnalysisResults[grammer_i].type == "RBRACE")
                {
                    o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                    grammer_i++;
                    varInitTwo();
                    return 1;
                }
            }
        }
        else
            return 0;
    }
    return 1;
}

bool varNoInit()
{

    if (((lexicalAnalysisResults[grammer_i].type == "INTTK") || (lexicalAnalysisResults[grammer_i].type == "CHARTK") || (lexicalAnalysisResults[grammer_i].type == "COMMA")) && (lexicalAnalysisResults[grammer_i + 2].type != "LPARENT"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
        if (lexicalAnalysisResults[grammer_i].type == "IDENFR")
        {
            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
            grammer_i++;
            if (lexicalAnalysisResults[grammer_i].type == "LBRACK")
            {
                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                grammer_i++;
                if (lexicalAnalysisResults[grammer_i].type == "INTCON")
                {
                    o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                    o << "<无符号整数>" << endl;
                    grammer_i++;
                    if (lexicalAnalysisResults[grammer_i].type == "RBRACK")
                    {
                        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                        grammer_i++;
                        if (lexicalAnalysisResults[grammer_i].type == "LBRACK")
                        {
                            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                            grammer_i++;
                            if (lexicalAnalysisResults[grammer_i].type == "INTCON")
                            {
                                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                                o << "<无符号整数>" << endl;
                                grammer_i++;
                                if (lexicalAnalysisResults[grammer_i].type == "RBRACK")
                                {
                                    o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                                    grammer_i++;
                                    varNoInit();
                                    return 1;
                                }
                            }
                        }
                        else
                        {
                            varNoInit();
                            return 1;
                        }
                    }
                }
            }
            else
            {
                varNoInit();
                return 1;
            }
        }
    }
    return 0;
}

bool varInit()
{

    if (((lexicalAnalysisResults[grammer_i].type == "INTTK") || (lexicalAnalysisResults[grammer_i].type == "CHARTK")) && (lexicalAnalysisResults[grammer_i + 2].type != "LPARENT") && (lexicalAnalysisResults[grammer_i + 2].type != "LBRACK") && (lexicalAnalysisResults[grammer_i + 5].type != "LBRACK"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
        if (lexicalAnalysisResults[grammer_i].type == "IDENFR")
        {
            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
            grammer_i++;
            if (lexicalAnalysisResults[grammer_i].type == "ASSIGN")
            {
                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                grammer_i++;
                if (con() == 1)
                {
                    o << "<常量>" << endl;
                    return 1;
                }
            }
        }
    }

    else if (((lexicalAnalysisResults[grammer_i].type == "INTTK") || (lexicalAnalysisResults[grammer_i].type == "CHARTK")) && (lexicalAnalysisResults[grammer_i + 2].type != "LPARENT") && (lexicalAnalysisResults[grammer_i + 5].type != "LBRACK"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
        if (lexicalAnalysisResults[grammer_i].type == "IDENFR")
        {
            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
            grammer_i++;
            if ((lexicalAnalysisResults[grammer_i].type == "LBRACK") && (lexicalAnalysisResults[grammer_i + 1].type == "INTCON") && (lexicalAnalysisResults[grammer_i + 2].type == "RBRACK"))
            {
                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
                o << "<无符号整数>" << endl;
                o << lexicalAnalysisResults[grammer_i + 2].type << " " << lexicalAnalysisResults[grammer_i + 2].str << endl;
                grammer_i = grammer_i + 3;
                if (lexicalAnalysisResults[grammer_i].type == "ASSIGN")
                {
                    o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                    grammer_i++;
                    if (lexicalAnalysisResults[grammer_i].type == "LBRACE")
                    {
                        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                        grammer_i++;
                        if (con() == 1)
                        {
                            o << "<常量>" << endl;
                            varInitOne();
                            if (lexicalAnalysisResults[grammer_i].type == "RBRACE")
                            {
                                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                                grammer_i++;
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }

    else if (((lexicalAnalysisResults[grammer_i].type == "INTTK") || (lexicalAnalysisResults[grammer_i].type == "CHARTK")) && (lexicalAnalysisResults[grammer_i + 2].type != "LPARENT"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
        if (lexicalAnalysisResults[grammer_i].type == "IDENFR")
        {
            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
            grammer_i++;
            if ((lexicalAnalysisResults[grammer_i].type == "LBRACK") && (lexicalAnalysisResults[grammer_i + 1].type == "INTCON") && (lexicalAnalysisResults[grammer_i + 2].type == "RBRACK"))
            {
                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
                o << "<无符号整数>" << endl;
                o << lexicalAnalysisResults[grammer_i + 2].type << " " << lexicalAnalysisResults[grammer_i + 2].str << endl;
                grammer_i = grammer_i + 3;
                if ((lexicalAnalysisResults[grammer_i].type == "LBRACK") && (lexicalAnalysisResults[grammer_i + 1].type == "INTCON") && (lexicalAnalysisResults[grammer_i + 2].type == "RBRACK"))
                {
                    o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                    o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
                    o << "<无符号整数>" << endl;
                    o << lexicalAnalysisResults[grammer_i + 2].type << " " << lexicalAnalysisResults[grammer_i + 2].str << endl;
                    grammer_i = grammer_i + 3;
                    if (lexicalAnalysisResults[grammer_i].type == "ASSIGN")
                    {
                        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                        grammer_i++;
                        if ((lexicalAnalysisResults[grammer_i].type == "LBRACE") && (lexicalAnalysisResults[grammer_i + 1].type == "LBRACE"))
                        {
                            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                            o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
                            grammer_i = grammer_i + 2;
                            if (con() == 1)
                            {
                                o << "<常量>" << endl;
                                varInitOne();
                                if (lexicalAnalysisResults[grammer_i].type == "RBRACE")
                                {
                                    o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                                    grammer_i++;
                                    varInitTwo();
                                    if (lexicalAnalysisResults[grammer_i].type == "RBRACE")
                                    {
                                        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                                        grammer_i++;
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

bool varD()
{

    if (((lexicalAnalysisResults[grammer_i + 2].type == "ASSIGN") || ((lexicalAnalysisResults[grammer_i + 2].type == "LBRACK") && (lexicalAnalysisResults[grammer_i + 5].type == "ASSIGN")) || ((lexicalAnalysisResults[grammer_i + 2].type == "LBRACK") && (lexicalAnalysisResults[grammer_i + 5].type == "LBRACK") && (lexicalAnalysisResults[grammer_i + 8].type == "ASSIGN"))) && (varInit() == 1))
    {
        o << "<变量定义及初始化>" << endl;
        return 1;
    }
    else if (varNoInit() == 1)
    {
        o << "<变量定义无初始化>" << endl;
        return 1;
    }

    return 0;
}

bool var()
{
    if (varD() == 1)
    {
        o << "<变量定义>" << endl;
        if (lexicalAnalysisResults[grammer_i].type == "SEMICN")
        {
            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
            grammer_i++;
            var();
            return 1;
        }
    }
    return 0;
}

bool para()
{
    if (lexicalAnalysisResults[grammer_i].type == "COMMA")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
    }
    if ((lexicalAnalysisResults[grammer_i].type == "INTTK") || (lexicalAnalysisResults[grammer_i].type == "CHARTK"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
        if (lexicalAnalysisResults[grammer_i].type == "IDENFR")
        {
            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
            grammer_i++;
            para();
            return 1;
        }
    }
    return 1;
}

bool functionReturn()
{
    string name = lexicalAnalysisResults[grammer_i + 1].str;
    if (declareHead() == 1)
    {
        o << "<声明头部>" << endl;
    }
    else
        return 0;
    if (lexicalAnalysisResults[grammer_i].type == "LPARENT")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
    }
    else
        return 0;
    if (para() == 1)
    {
        o << "<参数表>" << endl;
    }
    else
        return 0;
    if (lexicalAnalysisResults[grammer_i].type == "RPARENT")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
    }
    else
        return 0;
    if (lexicalAnalysisResults[grammer_i].type == "LBRACE")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
    }
    else
        return 0;
    if (complexSentence() == 1)
    {
        o << "<复合语句>" << endl;
    }
    else
        return 0;
    if (lexicalAnalysisResults[grammer_i].type == "RBRACE")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
    }
    else
        return 0;
    have_return.push_back(name);
    return 1;
}

bool functionNotReturn()
{
    string name = lexicalAnalysisResults[grammer_i + 1].str;
    if ((lexicalAnalysisResults[grammer_i].type == "VOIDTK") && (lexicalAnalysisResults[grammer_i + 1].type == "IDENFR"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
        grammer_i = grammer_i + 2;
    }
    else
        return 0;
    if (lexicalAnalysisResults[grammer_i].type == "LPARENT")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
    }
    else
        return 0;
    if (para() == 1)
    {
        o << "<参数表>" << endl;
    }
    else
        return 0;
    if (lexicalAnalysisResults[grammer_i].type == "RPARENT")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
    }
    else
        return 0;
    if (lexicalAnalysisResults[grammer_i].type == "LBRACE")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
    }
    else
        return 0;
    if (complexSentence() == 1)
    {
        o << "<复合语句>" << endl;
    }
    else
        return 0;
    if (lexicalAnalysisResults[grammer_i].type == "RBRACE")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
    }
    else
        return 0;
    no_return.push_back(name);
    return 1;
}

bool funcClosures()
{
    if (functionReturn() == 1)
    {
        o << "<有返回值函数定义>" << endl;
        funcClosures();
        return 1;
    }
    else if (functionNotReturn() == 1)
    {
        o << "<无返回值函数定义>" << endl;
        funcClosures();
        return 1;
    }
    return 0;
}

bool declareHead()
{
    if ((lexicalAnalysisResults[grammer_i].type == "INTTK") && (lexicalAnalysisResults[grammer_i + 1].type == "IDENFR"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
        grammer_i = grammer_i + 2;
        return 1;
    }
    else if ((lexicalAnalysisResults[grammer_i].type == "CHARTK") && (lexicalAnalysisResults[grammer_i + 1].type == "IDENFR"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
        grammer_i = grammer_i + 2;
        return 1;
    }
    return 0;
}

bool condition()
{
    if (expre() == 1)
    {
        o << "<表达式>" << endl;
        if ((lexicalAnalysisResults[grammer_i].type == "LSS") || (lexicalAnalysisResults[grammer_i].type == "LEQ") || (lexicalAnalysisResults[grammer_i].type == "GRE") || (lexicalAnalysisResults[grammer_i].type == "GEQ") || (lexicalAnalysisResults[grammer_i].type == "EQL") || (lexicalAnalysisResults[grammer_i].type == "NEQ"))
        {
            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
            grammer_i++;
            if (expre() == 1)
            {
                o << "<表达式>" << endl;
                return 1;
            }
        }
    }
    return 0;
}

bool step()
{
    if (lexicalAnalysisResults[grammer_i].type == "INTCON")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        o << "<无符号整数>" << endl;
        grammer_i++;
        return 1;
    }
    return 0;
}

bool complexSentence()
{
    if (cons() == 1)
    {
        o << "<常量说明>" << endl;
    }
    if (var() == 1)
    {
        o << "<变量说明>" << endl;
    }
    if (manySentence() == 1)
    {
        o << "<语句列>" << endl;
        return 1;
    }
    return 0;
}

bool manySentence()
{
    if (sentence() == 1)
    {
        o << "<语句>" << endl;
        manySentence();
        return 1;
    }

    return 1;
}

bool defaultSentence()
{
    if (lexicalAnalysisResults[grammer_i].type == "DEFAULTTK")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
        if (lexicalAnalysisResults[grammer_i].type == "COLON")
        {
            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
            grammer_i++;
            if (sentence() == 1)
            {
                o << "<语句>" << endl;
                return 1;
            }
        }
    }
    return 0;
}

bool situatioonSubsen()
{
    if (lexicalAnalysisResults[grammer_i].type == "CASETK")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
        if (con() == 1)
        {
            o << "<常量>" << endl;
            if (lexicalAnalysisResults[grammer_i].type == "COLON")
            {
                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                grammer_i++;
                if (sentence() == 1)
                {
                    o << "<语句>" << endl;
                    return 1;
                }
            }
        }
    }
    return 0;
}

bool situationTable()
{
    if (situatioonSubsen() == 1)
    {
        o << "<情况子语句>" << endl;
        situationTable();
    }
    return 1;
}

bool situationSentence()
{
    if ((lexicalAnalysisResults[grammer_i].type == "SWITCHTK") && (lexicalAnalysisResults[grammer_i + 1].type == "LPARENT"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
        grammer_i += 2;
        if (expre() == 1)
        {
            o << "<表达式>" << endl;
            if ((lexicalAnalysisResults[grammer_i].type == "RPARENT") && (lexicalAnalysisResults[grammer_i + 1].type == "LBRACE"))
            {
                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
                grammer_i += 2;
                if (situationTable() == 1)
                {
                    o << "<情况表>" << endl;
                    if (defaultSentence() == 1)
                    {
                        o << "<缺省>" << endl;
                        if (lexicalAnalysisResults[grammer_i].type == "RBRACE")
                        {
                            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                            grammer_i++;
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

bool returnSentence()
{
    if (lexicalAnalysisResults[grammer_i].type == "RETURNTK")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
        if (lexicalAnalysisResults[grammer_i].type == "LPARENT")
        {
            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
            grammer_i++;
            if (expre() == 1)
            {
                o << "<表达式>" << endl;
                if (lexicalAnalysisResults[grammer_i].type == "RPARENT")
                {
                    o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                    grammer_i++;
                    return 1;
                }
            }
        }
        else
            return 1;
    }
    return 0;
}

bool conditionSentence()
{
    if ((lexicalAnalysisResults[grammer_i].type == "IFTK") && (lexicalAnalysisResults[grammer_i + 1].type == "LPARENT"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
        grammer_i += 2;
        if (condition() == 1)
        {
            o << "<条件>" << endl;
            if (lexicalAnalysisResults[grammer_i].type == "RPARENT")
            {
                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                grammer_i++;
                if (sentence() == 1)
                {
                    o << "<语句>" << endl;
                    if (lexicalAnalysisResults[grammer_i].type == "ELSETK")
                    {
                        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                        grammer_i++;
                        if (sentence() == 1)
                        {
                            o << "<语句>" << endl;
                            return 1;
                        }
                    }
                    else
                        return 1;
                }
            }
        }
    }
    return 0;
}

bool assign()
{
    if ((lexicalAnalysisResults[grammer_i].type == "IDENFR") && (lexicalAnalysisResults[grammer_i + 1].type == "ASSIGN"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
        grammer_i += 2;
        if (expre() == 1)
        {
            o << "<表达式>" << endl;
            return 1;
        }
    }

    else if ((lexicalAnalysisResults[grammer_i].type == "IDENFR") && (lexicalAnalysisResults[grammer_i + 1].type == "LBRACK") && (lexicalAnalysisResults[grammer_i + 4].type != "LBRACK"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
        grammer_i += 2;
        if (expre() == 1)
        {
            o << "<表达式>" << endl;
            if ((lexicalAnalysisResults[grammer_i].type == "RBRACK") && (lexicalAnalysisResults[grammer_i + 1].type == "ASSIGN"))
            {
                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
                grammer_i += 2;
                if (expre() == 1)
                {
                    o << "<表达式>" << endl;
                    return 1;
                }
            }
        }
    }
    else if ((lexicalAnalysisResults[grammer_i].type == "IDENFR") && (lexicalAnalysisResults[grammer_i + 1].type == "LBRACK"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
        grammer_i += 2;
        if (expre() == 1)
        {
            o << "<表达式>" << endl;
            if ((lexicalAnalysisResults[grammer_i].type == "RBRACK") && (lexicalAnalysisResults[grammer_i + 1].type == "LBRACK"))
            {
                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
                grammer_i += 2;
                if (expre() == 1)
                {
                    o << "<表达式>" << endl;
                    if ((lexicalAnalysisResults[grammer_i].type == "RBRACK") && (lexicalAnalysisResults[grammer_i + 1].type == "ASSIGN"))
                    {
                        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                        o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
                        grammer_i += 2;
                        if (expre() == 1)
                        {
                            o << "<表达式>" << endl;
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

bool sentence()
{
    if (cycly() == 1)
    {
        o << "<循环语句>" << endl;
        return 1;
    }
    else if (conditionSentence() == 1)
    {
        o << "<条件语句>" << endl;
        return 1;
    }

    else if ((std::count(have_return.begin(), have_return.end(), lexicalAnalysisResults[grammer_i].str) > 0) && (funcR() == 1))
    {
        o << "<有返回值函数调用语句>" << endl;
        if (lexicalAnalysisResults[grammer_i].type == "SEMICN")
        {
            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
            grammer_i++;
            return 1;
        }
    }
    else if ((std::count(no_return.begin(), no_return.end(), lexicalAnalysisResults[grammer_i].str) > 0) && (funcNotR() == 1))
    {
        o << "<无返回值函数调用语句>" << endl;
        if (lexicalAnalysisResults[grammer_i].type == "SEMICN")
        {
            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
            grammer_i++;
            return 1;
        }
    }
    else if (assign() == 1) /*&& (lexicalAnalysisResults[grammer_i + 1].type == "ASSIGN"))*/
    {
        o << "<赋值语句>" << endl;
        if (lexicalAnalysisResults[grammer_i].type == "SEMICN")
        {
            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
            grammer_i++;
            return 1;
        }
    }
    else if (read() == 1)
    {
        o << "<读语句>" << endl;
        if (lexicalAnalysisResults[grammer_i].type == "SEMICN")
        {
            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
            grammer_i++;
            return 1;
        }
    }
    else if (write() == 1)
    {
        o << "<写语句>" << endl;
        if (lexicalAnalysisResults[grammer_i].type == "SEMICN")
        {
            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
            grammer_i++;
            return 1;
        }
    }
    else if (situationSentence() == 1)
    {
        o << "<情况语句>" << endl;
        return 1;
    }
    else if (lexicalAnalysisResults[grammer_i].type == "SEMICN")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
        return 1;
    }
    else if (returnSentence() == 1)
    {
        o << "<返回语句>" << endl;
        if (lexicalAnalysisResults[grammer_i].type == "SEMICN")
        {
            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
            grammer_i++;
            return 1;
        }
    }
    else if (lexicalAnalysisResults[grammer_i].type == "LBRACE")
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        grammer_i++;
        if (manySentence() == 1)
        {
            o << "<语句列>" << endl;
            if (lexicalAnalysisResults[grammer_i].type == "RBRACE")
            {
                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                grammer_i++;
                return 1;
            }
        }
    }
    return 0;
}

bool cycly()
{
    if ((lexicalAnalysisResults[grammer_i].type == "WHILETK") && (lexicalAnalysisResults[grammer_i + 1].type == "LPARENT"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
        grammer_i = grammer_i + 2;
        if (condition() == 1)
        {
            o << "<条件>" << endl;
            if (lexicalAnalysisResults[grammer_i].type == "RPARENT")
            {
                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                grammer_i++;
                if (sentence() == 1)
                {
                    o << "<语句>" << endl;
                    return 1;
                }
            }
        }
    }
    else if ((lexicalAnalysisResults[grammer_i].type == "FORTK") && (lexicalAnalysisResults[grammer_i + 1].type == "LPARENT") && (lexicalAnalysisResults[grammer_i + 2].type == "IDENFR") && (lexicalAnalysisResults[grammer_i + 3].type == "ASSIGN"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
        o << lexicalAnalysisResults[grammer_i + 2].type << " " << lexicalAnalysisResults[grammer_i + 2].str << endl;
        o << lexicalAnalysisResults[grammer_i + 3].type << " " << lexicalAnalysisResults[grammer_i + 3].str << endl;
        grammer_i = grammer_i + 4;
        if (expre() == 1)
        {
            o << "<表达式>" << endl;
            if (lexicalAnalysisResults[grammer_i].type == "SEMICN")
            {
                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                grammer_i++;
                if (condition() == 1)
                {
                    o << "<条件>" << endl;
                    if ((lexicalAnalysisResults[grammer_i].type == "SEMICN") && (lexicalAnalysisResults[grammer_i + 1].type == "IDENFR") && (lexicalAnalysisResults[grammer_i + 2].type == "ASSIGN") && (lexicalAnalysisResults[grammer_i + 3].type == "IDENFR"))
                    {
                        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                        o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
                        o << lexicalAnalysisResults[grammer_i + 2].type << " " << lexicalAnalysisResults[grammer_i + 2].str << endl;
                        o << lexicalAnalysisResults[grammer_i + 3].type << " " << lexicalAnalysisResults[grammer_i + 3].str << endl;
                        grammer_i = grammer_i + 4;
                        if ((lexicalAnalysisResults[grammer_i].type == "PLUS") || (lexicalAnalysisResults[grammer_i].type == "MINU"))
                        {
                            o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                            grammer_i++;
                            if (step() == 1)
                            {
                                o << "<步长>" << endl;
                                if (lexicalAnalysisResults[grammer_i].type == "RPARENT")
                                {
                                    o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                                    grammer_i++;
                                    if (sentence() == 1)
                                    {
                                        o << "<语句>" << endl;
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

bool mainF()
{
    if ((lexicalAnalysisResults[grammer_i].type == "VOIDTK") && (lexicalAnalysisResults[grammer_i + 1].type == "MAINTK") && (lexicalAnalysisResults[grammer_i + 2].type == "LPARENT") && (lexicalAnalysisResults[grammer_i + 3].type == "RPARENT") && (lexicalAnalysisResults[grammer_i + 4].type == "LBRACE"))
    {
        o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
        o << lexicalAnalysisResults[grammer_i + 1].type << " " << lexicalAnalysisResults[grammer_i + 1].str << endl;
        o << lexicalAnalysisResults[grammer_i + 2].type << " " << lexicalAnalysisResults[grammer_i + 2].str << endl;
        o << lexicalAnalysisResults[grammer_i + 3].type << " " << lexicalAnalysisResults[grammer_i + 3].str << endl;
        o << lexicalAnalysisResults[grammer_i + 4].type << " " << lexicalAnalysisResults[grammer_i + 4].str << endl;
        grammer_i += 5;
        if (complexSentence() == 1)
        {
            o << "<复合语句>" << endl;
            if (lexicalAnalysisResults[grammer_i].type == "RBRACE")
            {
                o << lexicalAnalysisResults[grammer_i].type << " " << lexicalAnalysisResults[grammer_i].str << endl;
                grammer_i++;
                return 1;
            }
        }
    }
    return 0;
}

void prom()
{
    if (cons() == 1)
        o << "<常量说明>" << endl;
    if (var() == 1)
        o << "<变量说明>" << endl;
    funcClosures();
    if (mainF() == 1)
        o << "<主函数>" << endl;
    o << "<程序>" << endl;
}

int main()
{

    init();
    string str;
    while (getline(f, str))
        op(str);
    f.close();
    prom();
}
