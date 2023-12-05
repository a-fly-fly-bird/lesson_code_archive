#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <stack>

using namespace std;

map<string, string> table1;

int tokenNum = 0;
int tokenNow = 1;
string strInit[10000];
string token[10000];

string s_define[1000];
int top = 0;

map<string, string> memint;

map<string, string> memStr;

string memeryConstructure[10000];

int memstrCnt = 0;

bool reg_t[10] = {0};

bool reg_s[8] = {0};

map<string, string> reg;

struct Error
{
	int line;
	string type;
};

Error err[10000];
int errcnt = 0;
int linenum[10000];

struct Mips
{
	string op;
	string rs;
	string rt;
	string rd;
};

Mips mips[10000];

int mipsNum = 0;

struct Mid
{
	string op;
	string rs;
	string rt;
	string rd;
};

Mid mid[10000];

int midNum = 0;

// 初始化
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
}

void printSignaure(string str, int rowptr)
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

		token[++tokenNum] = table1[strl];
		strInit[tokenNum] = str;
		linenum[tokenNum] = rowptr;
	}
	else
	{

		token[++tokenNum] = "IDENFR";
		strInit[tokenNum] = str;
		linenum[tokenNum] = rowptr;
	}
}
int state = 0;
string strNow = "";
int checkExpre(int abc);
bool checkSentence(int abc);
void FSM(string str, int rowptr)
{
	for (int i = 0; i < str.length(); i++)
	{

		if (state == 0 && ((str[i] <= 'Z' && str[i] >= 'A') || (str[i] <= 'z' && str[i] >= 'a') || str[i] == '_'))
		{
			state = 1;
			strNow += str[i];
			continue;
		}
		if (state == 1)
		{
			if ((str[i] <= 'Z' && str[i] >= 'A') || (str[i] <= 'z' && str[i] >= 'a') || str[i] == '_' || (str[i] <= '9' && str[i] >= '0'))
			{
				state = 1;
				strNow += str[i];
				if (i == str.length() - 1)
				{
					printSignaure(strNow, rowptr);
					state = 0;
					strNow = "";
				}
			}
			else
			{
				printSignaure(strNow, rowptr);
				state = 0;
				strNow = "";
				i--;
				continue;
			}
		}

		if (state == 0 && (str[i] <= '9' && str[i] >= '0'))
		{
			state = 2;
			strNow += str[i];
			continue;
		}
		if (state == 2)
		{
			if (str[i] <= '9' && str[i] >= '0')
			{
				strNow += str[i];
				if (i == str.length() - 1)
				{

					token[++tokenNum] = "INTCON";
					strInit[tokenNum] = strNow;
					linenum[tokenNum] = rowptr;
					state = 0;
					strNow = "";
				}
				continue;
			}
			else
			{

				token[++tokenNum] = "INTCON";
				strInit[tokenNum] = strNow;
				linenum[tokenNum] = rowptr;
				state = 0;
				strNow = "";
				i--;
				continue;
			}
		}

		if (state == 0 && (str[i] == '\''))
		{
			state = 3;
			continue;
		}
		if (state == 3)
		{
			if (str[i] == '\'')
			{

				token[++tokenNum] = "CHARCON";
				strInit[tokenNum] = strNow;
				linenum[tokenNum] = rowptr;
				strNow = "";
				state = 0;
				continue;
			}
			else
			{
				strNow += str[i];
				continue;
			}
		}

		if (state == 0 && (str[i] == '\"'))
		{
			state = 4;
			continue;
		}
		if (state == 4)
		{
			if (str[i] == '\"')
			{

				token[++tokenNum] = "STRCON";
				strInit[tokenNum] = strNow;
				linenum[tokenNum] = rowptr;
				strNow = "";
				state = 0;
				continue;
			}
			else
			{
				strNow += str[i];
				continue;
			}
		}

		if (state == 0 && (str[i] == '+'))
		{
			strNow += str[i];
			state = 5;

			token[++tokenNum] = "PLUS";
			strInit[tokenNum] = strNow;
			linenum[tokenNum] = rowptr;
			state = 0;
			strNow = "";
			continue;
		}

		if (state == 0 && (str[i] == '-'))
		{
			strNow += str[i];
			state = 6;

			token[++tokenNum] = "MINU";
			strInit[tokenNum] = strNow;
			linenum[tokenNum] = rowptr;
			state = 0;
			strNow = "";
			continue;
		}

		if (state == 0 && (str[i] == '*'))
		{
			strNow += str[i];
			state = 7;

			token[++tokenNum] = "MULT";
			strInit[tokenNum] = strNow;
			linenum[tokenNum] = rowptr;
			state = 0;
			strNow = "";
			continue;
		}

		if (state == 0 && (str[i] == '/'))
		{
			strNow += str[i];
			state = 8;

			token[++tokenNum] = "DIV";
			strInit[tokenNum] = strNow;
			linenum[tokenNum] = rowptr;
			state = 0;
			strNow = "";
			continue;
		}

		if (state == 0 && (str[i] == ':'))
		{
			strNow += str[i];
			state = 9;

			token[++tokenNum] = "COLON";
			strInit[tokenNum] = strNow;
			linenum[tokenNum] = rowptr;
			state = 0;
			strNow = "";
			continue;
		}

		if (state == 0 && (str[i] == ';'))
		{
			strNow += str[i];
			state = 10;

			token[++tokenNum] = "SEMICN";
			strInit[tokenNum] = strNow;
			linenum[tokenNum] = rowptr;
			state = 0;
			strNow = "";
			continue;
		}

		if (state == 0 && (str[i] == ','))
		{
			strNow += str[i];
			state = 11;

			token[++tokenNum] = "COMMA";
			strInit[tokenNum] = strNow;
			linenum[tokenNum] = rowptr;
			state = 0;
			strNow = "";
			continue;
		}

		if (state == 0 && (str[i] == '('))
		{
			strNow += str[i];
			state = 12;

			token[++tokenNum] = "LPARENT";
			strInit[tokenNum] = strNow;
			linenum[tokenNum] = rowptr;
			state = 0;
			strNow = "";
			continue;
		}

		if (state == 0 && (str[i] == ')'))
		{
			strNow += str[i];
			state = 13;

			token[++tokenNum] = "RPARENT";
			strInit[tokenNum] = strNow;
			linenum[tokenNum] = rowptr;
			state = 0;
			strNow = "";
			continue;
		}

		if (state == 0 && (str[i] == '['))
		{
			strNow += str[i];
			state = 14;

			token[++tokenNum] = "LBRACK";
			strInit[tokenNum] = strNow;
			linenum[tokenNum] = rowptr;
			state = 0;
			strNow = "";
			continue;
		}

		if (state == 0 && (str[i] == ']'))
		{
			strNow += str[i];
			state = 15;

			token[++tokenNum] = "RBRACK";
			strInit[tokenNum] = strNow;
			linenum[tokenNum] = rowptr;
			state = 0;
			strNow = "";
			continue;
		}

		if (state == 0 && (str[i] == '{'))
		{
			strNow += str[i];
			state = 16;

			token[++tokenNum] = "LBRACE";
			strInit[tokenNum] = strNow;
			linenum[tokenNum] = rowptr;
			state = 0;
			strNow = "";
			continue;
		}

		if (state == 0 && (str[i] == '}'))
		{
			strNow += str[i];
			state = 17;

			token[++tokenNum] = "RBRACE";
			strInit[tokenNum] = strNow;
			linenum[tokenNum] = rowptr;
			state = 0;
			strNow = "";
			continue;
		}

		if (state == 0 && str[i] == '=')
		{
			state = 18;
			strNow += str[i];
			if (i == str.length() - 1)
			{
				state = 0;

				token[++tokenNum] = "ASSIGN";
				strInit[tokenNum] = strNow;
				linenum[tokenNum] = rowptr;
				strNow = "";
			}
			continue;
		}
		if (state == 18)
		{
			if (str[i] == '=')
			{
				state = 19;
				strNow += str[i];
				state = 0;

				token[++tokenNum] = "EQL";
				strInit[tokenNum] = strNow;
				linenum[tokenNum] = rowptr;
				strNow = "";
				continue;
			}
			else
			{
				state = 0;

				token[++tokenNum] = "ASSIGN";
				strInit[tokenNum] = strNow;
				linenum[tokenNum] = rowptr;
				strNow = "";
				i--;
				continue;
			}
		}
		if (state == 0 && str[i] == '!')
		{
			state = 20;
			strNow += str[i];
			continue;
		}
		if (state == 20 && str[i] == '=')
		{
			state = 20;
			strNow += str[i];
			state = 0;

			token[++tokenNum] = "NEQ";
			strInit[tokenNum] = strNow;
			linenum[tokenNum] = rowptr;
			strNow = "";
			continue;
		}
		if (state == 0 && str[i] == '>')
		{
			state = 21;
			strNow += str[i];
			if (i == str.length() - 1)
			{
				state = 0;

				token[++tokenNum] = "GRE";
				strInit[tokenNum] = strNow;
				linenum[tokenNum] = rowptr;
				strNow = "";
			}
			continue;
		}
		if (state == 21)
		{
			if (str[i] == '=')
			{
				state = 22;
				strNow += str[i];
				state = 0;

				token[++tokenNum] = "GEQ";
				strInit[tokenNum] = strNow;
				linenum[tokenNum] = rowptr;
				strNow = "";
				continue;
			}
			else
			{
				state = 0;

				token[++tokenNum] = "GRE";
				strInit[tokenNum] = strNow;
				linenum[tokenNum] = rowptr;
				strNow = "";
				i--;
				continue;
			}
		}
		if (state == 0 && str[i] == '<')
		{
			state = 23;
			strNow += str[i];
			if (i == str.length() - 1)
			{
				state = 0;

				token[++tokenNum] = "LSS";
				strInit[tokenNum] = strNow;
				linenum[tokenNum] = rowptr;
				strNow = "";
			}
			continue;
		}
		if (state == 23)
		{
			if (str[i] == '=')
			{
				state = 24;
				strNow += str[i];
				state = 0;

				token[++tokenNum] = "LEQ";
				strInit[tokenNum] = strNow;
				linenum[tokenNum] = rowptr;
				strNow = "";
				continue;
			}
			else
			{
				state = 0;

				token[++tokenNum] = "LSS";
				strInit[tokenNum] = strNow;
				linenum[tokenNum] = rowptr;
				strNow = "";
				i--;
				continue;
			}
		}
	}
}

bool ERROR = false;

void error(int abc)
{
	ERROR = true;
	cout << "ERROR" << abc << endl;
}

void check_charcon_s(int abc)
{
	for (int i = 0; i < strInit[abc].length(); i++)
	{
		if (strInit[abc][i] == ' ' || strInit[abc][i] == '!' || (strInit[abc][i] >= '#' && strInit[abc][i] <= '~'))
		{
			continue;
		}
		else
		{
			err[++errcnt].line = linenum[abc - 1];
			err[errcnt].type = "a";
		}
	}
}

void check_charcon_c(int abc)
{

	if (strInit[abc] == "+" || strInit[abc] == "-" || strInit[abc] == "*" || strInit[abc] == "/" || (strInit[abc] >= "A" && strInit[abc] <= "Z") || (strInit[abc] >= "a" && strInit[abc] <= "z") || (strInit[abc] >= "0" && strInit[abc] <= "9") || strInit[abc] == "_")
	{
		return;
	}
	else
	{
		err[++errcnt].line = linenum[abc - 1];
		err[errcnt].type = "a";
	}
}

void check_exist(int abc)
{
	string str = strInit[abc];
	for (int i = 1; i <= top; i++)
	{
		if (s_define[i] == str)
		{
			return;
		}
	}
	err[++errcnt].line = linenum[abc - 1];
	err[errcnt].type = "c";
}

int rs = 1;
void check_redefine(int abc)
{
	string str = strInit[abc];
	for (int i = rs; i <= top; i++)
	{
		if (s_define[i] == str)
		{
			err[++errcnt].line = linenum[abc - 1];
			err[errcnt].type = "b";
			return;
		}
	}
}

map<string, int> mp_paraNum;
int paracnt = 0;
int valueparacnt = 0;
void check_paraNum(int abc)
{
	if (mp_paraNum[strInit[abc]] != valueparacnt)
	{
		err[++errcnt].line = linenum[abc];
		err[errcnt].type = "d";
	}
}

map<string, string> mp_paratype;

string valuetypeNow = "";

string typeNow = "";

string type = "1";

void check_paratype(int abc)
{
	if (mp_paratype[strInit[abc]] != valuetypeNow)
	{
		err[++errcnt].line = linenum[abc - 1];
		err[errcnt].type = "e";
	}
}

map<string, int> mpType;

void check_iftype(int abc)
{
	if (type == "0")
	{
		err[++errcnt].line = linenum[abc - 1];
		err[errcnt].type = "f";
	}
}
int return_type = 0;
void check_noreturn_error(int abc)
{
	err[++errcnt].line = linenum[abc - 1];
	err[errcnt].type = "g";
}
bool return_pd = false;
bool return_int = true;
void check_return_error(int abc)
{
	err[++errcnt].line = linenum[abc - 1];
	err[errcnt].type = "h";
}

void checkArrayIndex(int abc)
{
	err[++errcnt].line = linenum[abc - 1];
	err[errcnt].type = "i";
}
map<string, bool> const_pd;
void checkConstTK(int abc)
{
	if (const_pd[strInit[abc]])
	{
		err[++errcnt].line = linenum[abc];
		err[errcnt].type = "j";
	}
}

void checkFenhao(int abc)
{
	err[++errcnt].line = linenum[abc - 1];
	err[errcnt].type = "abc";
}

void checkPRA(int abc)
{
	err[++errcnt].line = linenum[abc - 1];
	err[errcnt].type = "l";
}

void checkKuoHao(int abc)
{
	err[++errcnt].line = linenum[abc - 1];
	err[errcnt].type = "m";
}

void checkArrayNomatch(int abc)
{
	err[++errcnt].line = linenum[abc - 1];
	err[errcnt].type = "n";
}

void checkChangNoMatch(int abc)
{
	err[++errcnt].line = linenum[abc - 1];
	err[errcnt].type = "o";
}

void checkNoDef(int abc)
{
	err[++errcnt].line = linenum[abc - 1];
	err[errcnt].type = "p";
}

bool checkIntegerUnsigned(int abc)
{
	if (token[abc] == "INTCON")
	{

		return true;
	}
	return false;
}

bool checkInt(int abc)
{
	if (token[abc] == "INTCON")
	{

		return true;
	}
	if (token[abc] == "PLUS" || token[abc] == "MINU")
	{

		if (checkIntegerUnsigned(abc + 1))
		{
		}
		return true;
	}
	return false;
}

bool checkDefinedChang(int abc, int s)
{
	if (s == 0)
	{
		if (token[abc] == "INTTK" && token[abc + 1] == "IDENFR" && token[abc + 2] == "ASSIGN")
		{
			check_redefine(abc + 1);
			s_define[++top] = strInit[abc + 1];
			const_pd[strInit[abc + 1]] = true;

			if (checkInt(abc + 3))
			{
				bool tmp = true;
				if (token[abc + 3] == "INTCON")
				{
					tmp = false;
					memint[strInit[abc + 1]] = strInit[abc + 3];
				}
				else
				{
					if (strInit[abc + 3] == "-")
						memint[strInit[abc + 1]] = "-" + strInit[abc + 4];
					else
						memint[strInit[abc + 1]] = strInit[abc + 4];
				}
				if (token[abc + 4 + tmp] == "COMMA")
				{

					return checkDefinedChang(abc + 5 + tmp, 1);
				}
				else if (token[abc + 4 + tmp] == "SEMICN")
				{

					tokenNow = abc + 5 + tmp;
					return true;
				}
				else
				{
					checkFenhao(abc + 4 + tmp);
				}
			}
			else
			{
				error(abc);
				return false;
			}
		}
		if (token[abc] == "CHARTK" && token[abc + 1] == "IDENFR" && token[abc + 2] == "ASSIGN" && token[abc + 3] == "CHARCON")
		{
			check_redefine(abc + 1);
			s_define[++top] = strInit[abc + 1];
			const_pd[strInit[abc + 1]] = true;

			check_charcon_c(abc + 3);
			memint[strInit[abc + 1]] = strInit[abc + 3];
			if (token[abc + 4] == "COMMA")
			{

				return checkDefinedChang(abc + 5, 2);
			}
			else if (token[abc + 4] == "SEMICN")
			{

				tokenNow = abc + 5;
				return true;
			}
			else
			{
				checkFenhao(abc + 4);
			}
		}
		error(abc);
		return false;
	}
	if (s == 1 && token[abc] == "IDENFR" && token[abc + 1] == "ASSIGN")
	{
		check_redefine(abc);
		s_define[++top] = strInit[abc];
		const_pd[strInit[abc]] = true;

		if (checkInt(abc + 2))
		{
			bool tmp = true;
			if (token[abc + 2] == "INTCON")
			{
				tmp = false;
				memint[strInit[abc]] = strInit[abc + 2];
			}
			else
			{
				if (strInit[abc + 2] == "-")
					memint[strInit[abc]] = "-" + strInit[abc + 3];
				else
					memint[strInit[abc]] = strInit[abc + 3];
			}
			if (token[abc + 3 + tmp] == "COMMA")
			{

				return checkDefinedChang(abc + 4 + tmp, 1);
			}
			else if (token[abc + 3 + tmp] == "SEMICN")
			{

				tokenNow = abc + 4 + tmp;
				return true;
			}
			else
			{
				checkFenhao(abc + 3 + tmp);
			}
		}
		else
		{
			error(abc);
			return false;
		}
	}
	if (s == 2 && token[abc] == "IDENFR" && token[abc + 1] == "ASSIGN" && token[abc + 2] == "CHARCON")
	{
		check_redefine(abc);
		s_define[++top] = strInit[abc];
		const_pd[strInit[abc]] = true;

		check_charcon_c(abc + 2);
		if (token[abc + 3] == "COMMA")
		{

			return checkDefinedChang(abc + 4, 2);
		}
		else if (token[abc + 3] == "SEMICN")
		{
			cout << "<常量定义>" << endl;

			tokenNow = abc + 4;
			return true;
		}
		else
		{
			checkFenhao(abc + 3);
		}
		return false;
	}
	error(abc);
	return false;
}

bool checkChange(bool found)
{
	if (token[tokenNow] != "CONSTTK")
		return found;

	tokenNow++;
	if (checkDefinedChang(tokenNow, 0))
	{
		found = true;
		return checkChange(found);
	}
	return true;
}
int checkStatic(int abc, int s1);
int check_array_dim2(int s1, int abc, int sum2, int cnt)
{
	int ck = checkStatic(abc, 0);
	if (ck == -1)
		return -1;

	cnt++;
	abc = ck;
	if (token[abc] != "COMMA")
	{
		if (sum2 == cnt)
			return abc;
		else
		{
			checkArrayNomatch(abc);
			return abc;
		}
	}

	abc++;
	return check_array_dim2(s1, abc, sum2, cnt);
}

int check_array(int s1, int abc, int dim, int sum1, int sum2, int cnt)
{
	if (dim == 1)
	{
		int ck = checkStatic(abc, 0);
		if (ck == -1)
			return -1;

		cnt++;
		abc = ck;
		if (token[abc] != "COMMA")
		{
			if (sum1 == cnt)
				return abc;
			else
			{
				checkArrayNomatch(abc);
				return abc;
			}
		}

		abc++;
		return check_array(s1, abc, dim, sum1, sum2, cnt);
	}
	else
	{
		if (token[abc] != "LBRACE")
			return -1;

		int ck2 = check_array_dim2(s1, ++abc, sum2, 0);
		if (ck2 == -1)
			return false;
		else
		{
			abc = ck2;
			cnt++;
			if (token[abc] != "RBRACE")
				return -1;
			else
			{

				abc++;
				if (token[abc] != "COMMA")
				{
					if (sum1 == cnt)
						return abc;
					else
					{
						checkArrayNomatch(abc);
						return abc;
					}
				}
				else
				{

					return check_array(s1, abc + 1, dim, sum1, sum2, cnt);
				}
			}
		}
	}
}

int count(string str)
{
	int x = 0;
	for (int i = 0; i < str.length(); i++)
	{
		x = x * 10 + str[i] - '0';
	}
	return x;
}

string find_s_free()
{
	for (int i = 0; i <= 9; i++)
	{
		if (!reg_s[i])
		{
			reg_s[i] = true;
			string sfree = "$s";
			sfree += ('0' + i);
			return sfree;
		}
	}
	return "ERROR";
}

void free_s(string s)
{
	reg_t[s[2] - '0'] = false;
	return;
}

int checkStatic(int abc, int s1);

bool cycleCheckDefine(int abc, int s1, int s2)
{

	s2 = 2;
	if (token[abc] == "IDENFR" && token[abc + 1] == "ASSIGN")
	{
		s2 = 1;
		check_redefine(abc);
		s_define[++top] = strInit[abc];
		mpType[strInit[abc]] = s1;

		abc++;

		abc++;
		abc = checkStatic(abc, s1);
		if (abc == -1)
			return false;
		else
		{
			cout << "<常量>" << endl;
			if (token[abc] == "COMMA")
			{

				return cycleCheckDefine(abc + 1, 1, s2);
			}
			else if (token[abc] == "SEMICN")
			{

				tokenNow = abc + 1;
				return true;
			}
			else
			{
				checkFenhao(abc);
			}
		}
	}
	else if (token[abc] == "IDENFR" && token[abc + 1] == "LBRACK")
	{
		check_redefine(abc);
		s_define[++top] = strInit[abc];
		mpType[strInit[abc]] = s1;

		abc++;

		int sum1 = 0, sum2 = 0;
		int dim = 1;
		if (checkIntegerUnsigned(++abc))
		{
			sum1 = count(strInit[abc]);
			if (token[++abc] != "RBRACK")
			{
				checkKuoHao(abc - 1);
			}
			abc++;
			if (token[abc] == "LBRACK")
			{
				dim = 2;

				if (checkIntegerUnsigned(++abc))
				{
					sum2 = count(strInit[abc]);
					if (token[++abc] != "RBRACK")
					{
						checkKuoHao(abc - 1);
					}
					abc++;
				}
				else
				{
					checkArrayIndex(abc);
				}
			}
			if (token[abc] == "ASSIGN")
			{

				abc++;
				s2 = 1;
				if (token[abc] != "LBRACE")
				{
					error(abc);
					return false;
				}

				int ck = check_array(s1, ++abc, dim, sum1, sum2, 0);
				if (ck == -1)
					return false;
				else
				{
					abc = ck;
					if (token[abc] != "RBRACE")
					{
						error(abc);
						return false;
					}
				}
				abc++;
			}
			if (token[abc] == "COMMA")
			{

				return cycleCheckDefine(abc + 1, 1, s2);
			}
			if (token[abc] == "SEMICN")
			{

				tokenNow = abc + 1;
				return true;
			}
			else
			{
				checkFenhao(abc);
			}
		}
		else
		{
			checkArrayIndex(abc);
		}
	}
	else if (token[abc] == "IDENFR")
	{
		check_redefine(abc);
		s_define[++top] = strInit[abc];
		mpType[strInit[abc]] = s1;
		s2 = 2;
		string s_tmp = find_s_free();
		reg[strInit[abc]] = s_tmp;

		abc++;
		if (token[abc] == "COMMA")
		{

			return cycleCheckDefine(abc + 1, 1, s2);
		}
		if (token[abc] == "SEMICN")
		{

			tokenNow = abc + 1;
			return true;
		}
		else
		{
			checkFenhao(abc);
		}
	}
	return true;
}

bool cycleCheck(bool found)
{
	if (token[tokenNow + 2] == "LPARENT")
		return found;
	if (token[tokenNow] == "INTTK")
	{
		if (cycleCheckDefine(tokenNow + 1, 1, 0))
		{
			found = true;
			return cycleCheck(found);
		}
		else
			return found;
	}
	if (token[tokenNow] == "CHARTK")
	{
		if (cycleCheckDefine(tokenNow + 1, 2, 0))
		{
			found = true;
			return cycleCheck(found);
		}
		else
			return found;
	}
	return found;
}

int check_para(int abc)
{
	if (token[abc] == "INTTK" || token[abc] == "CHARTK")
	{

		if (token[abc] == "INTTK")
			typeNow += "1";
		else
			typeNow += "0";
		if (token[++abc] == "IDENFR")
			int a = 1;
		else
		{

			return -1;
		}
		s_define[++top] = strInit[abc];
		abc++;
		paracnt++;
		if (token[abc] == "COMMA")
		{

			return check_para(++abc);
		}
		else
			return abc;
	}
	else
		return abc;
}

int check_valuepara(int abc, int vcnt, string vtype)
{
	if (token[abc] == "RPARENT")
		return abc;
	type = "1";
	int ck = checkExpre(abc);
	if (ck != abc)
	{
		vcnt++;
		vtype += type;
		valueparacnt = vcnt;
		valuetypeNow = vtype;
	}

	if (ck != -1)
		abc = ck;
	else
	{
		checkPRA(abc);
		return abc;
	}

	if (token[abc] == "COMMA")
	{

		return check_valuepara(++abc, vcnt, vtype);
	}
	else
		return abc;
}
map<string, bool> mp_return;

bool checkSentenceFuncReturn(int abc)
{
	int str_tmp;
	if (token[abc] == "IDENFR" && token[abc + 1] == "LPARENT")
	{

		str_tmp = abc;
		if (mp_return.count(strInit[abc]) == 0)
		{
			err[++errcnt].line = linenum[abc];
			err[errcnt].type = "c";
		}

		abc++;

		abc++;
	}
	else
		return false;
	valueparacnt = 0;
	valuetypeNow = "";
	abc = check_valuepara(abc, 0, "");
	check_paraNum(str_tmp);
	check_paratype(str_tmp);
	if (abc == -1)
		return false;

	if (token[abc] == "RPARENT")
	{

		abc++;
	}
	else
	{
		checkPRA(abc);
	}
	tokenNow = abc;
	return true;
}

bool checkSentenceWithNoReturn(int abc)
{
	int str_tmp;
	if (token[abc] == "IDENFR" && token[abc + 1] == "LPARENT")
	{

		str_tmp = abc;
		if (mp_return.count(strInit[abc]) == 0)
		{
			err[++errcnt].line = linenum[abc];
			err[errcnt].type = "c";
		}
		if (mp_return.count(strInit[abc]) != 0 && !mp_return[strInit[abc]])
		{

			abc++;

			abc++;
		}
		else
			return false;
	}
	else
		return false;
	valueparacnt = 0;
	valuetypeNow = "";
	abc = check_valuepara(abc, 0, "");
	check_paraNum(str_tmp);
	check_paratype(str_tmp);
	if (abc == -1)
		return false;

	if (token[abc] == "RPARENT")
	{

		abc++;
	}
	else
	{
		checkPRA(abc);
	}
	tokenNow = abc;
	return true;
}

int checkFactors(int abc)
{
	if (token[abc] == "CHARCON")
	{
		check_charcon_c(abc);

		abc++;
		type = "0";
		return abc;
	}
	if (checkSentenceFuncReturn(abc))
		return tokenNow;
	if (token[abc] == "IDENFR" && token[abc + 1] != "LPARENT")
	{
		if (mpType[strInit[abc]] == 2)
			type = "0";
		string type_tmp = type;
		check_exist(abc);

		abc++;
		if (token[abc] == "LBRACK")
		{

			abc++;
			type = "1";
			int ck = checkExpre(abc);
			if (ck != -1)
				abc = ck;
			else
				return -1;

			if (type == "0")
				checkArrayIndex(abc);
			if (token[abc] == "RBRACK")
			{

				abc++;
			}
			else
			{
				checkKuoHao(abc);
			}
			if (token[abc] == "LBRACK")
			{

				abc++;
				type = "1";
				ck = checkExpre(abc);
				if (ck != -1)
					abc = ck;
				else
					return -1;

				if (type == "0")
					checkArrayIndex(abc);
				if (token[abc] == "RBRACK")
				{

					abc++;
				}
				else
				{
					checkKuoHao(abc);
				}
			}
			type = type_tmp;
		}
		return abc;
	}
	if (checkSentenceFuncReturn(abc))
	{
		abc = tokenNow;
	}
	if (token[abc] == "LPARENT")
	{

		abc++;
		int ck = checkExpre(abc);
		if (ck != -1)
			abc = ck;
		else
			return -1;

		if (token[abc] != "RPARENT")
		{
			checkPRA(abc);
		}
		else
		{

			abc++;
		}
		return abc;
	}
	if (checkInt(abc))
	{
		if (token[abc] == "INTCON")
			return abc + 1;
		else
			return abc + 2;
	}
	return abc;
}

int check_item(int abc)
{
	abc = checkFactors(abc);
	if (abc == -1)
		return -1;
	while (token[abc] == "MULT" || token[abc] == "DIV")
	{

		abc++;
		abc = checkFactors(abc);
		if (abc == -1)
			return -1;
		if (ERROR)
			return -1;
	}
	return abc;
}

int checkExpre(int abc)
{
	if (token[abc] == "PLUS" || token[abc] == "MINU")
	{

		abc++;
		type = "1";
	}
	abc = check_item(abc);
	if (abc == -1)
		return -1;
	while (token[abc] == "PLUS" || token[abc] == "MINU")
	{
		type = "1";

		abc++;
		abc = check_item(abc);
		if (abc == -1)
			return -1;
		if (ERROR)
			return -1;
	}
	return abc;
}

int check_condition(int abc)
{
	type = "1";
	abc = checkExpre(abc);
	check_iftype(abc);
	if (abc == -1)
		return -1;

	if (token[abc] == "LSS" || token[abc] == "LEQ" || token[abc] == "GRE" || token[abc] == "GEQ" || token[abc] == "EQL" || token[abc] == "NEQ")
	{

		abc++;
	}
	else
		return -1;
	type = "1";
	abc = checkExpre(abc);
	check_iftype(abc);
	if (abc == -1)
		return -1;

	return abc;
}

bool checkSentenceOnce(int abc)
{

	if (token[abc] == "WHILETK" && token[abc + 1] == "LPARENT")
	{

		abc = check_condition(abc + 2);
		if (abc == -1)
			return false;

		if (token[abc] == "RPARENT")
		{

			abc++;
		}
		else
		{
			checkPRA(abc);
		}
		if (checkSentence(abc))
		{

			return true;
		}
		else
		{
			error(abc);
			return false;
		}
	}

	else if (token[abc] == "FORTK" && token[abc + 1] == "LPARENT" && token[abc + 2] == "IDENFR" && token[abc + 3] == "ASSIGN")
	{
		check_exist(abc + 2);

		abc++;

		abc++;

		abc++;

		abc++;
		abc = checkExpre(abc);
		if (abc == -1)
			return false;

		if (token[abc] == "SEMICN")
		{

			abc++;
		}
		else
		{
			checkFenhao(abc);
		}
		abc = check_condition(abc);
		if (abc == -1)
			return false;
		cout << "<条件>" << endl;
		if (token[abc] == "SEMICN")
		{

			abc++;
		}
		else
		{
			checkFenhao(abc);
		}
		if (token[abc] == "IDENFR" && token[abc + 1] == "ASSIGN" && token[abc + 2] == "IDENFR")
		{
			check_exist(abc);

			abc++;

			abc++;

			abc++;
		}
		else
		{
			error(abc);
			return false;
		}
		if (token[abc] == "PLUS" || token[abc] == "MINU")
		{

			abc++;
		}
		else
		{
			error(abc);
			return false;
		}
		if (checkIntegerUnsigned(abc))
		{

			abc++;
		}
		if (token[abc] == "RPARENT")
		{

			abc++;
		}
		else
		{
			checkPRA(abc);
		}
		if (checkSentence(abc))
		{

			return true;
		}
		else
		{
			error(abc);
			return false;
		}
	}
	else
		return false;
}

bool checkSentenceIF(int abc)
{
	if (token[abc] == "IFTK" && token[abc + 1] == "LPARENT")
	{

		abc++;

		abc++;
	}
	else
		return false;
	abc = check_condition(abc);
	if (abc == -1)
		return false;

	if (token[abc] == "SEMICN")
	{

		abc++;
	}
	if (token[abc] == "RPARENT")
	{

		abc++;
	}
	else
	{
		checkPRA(abc);
	}
	if (checkSentence(abc))
	{

		abc = tokenNow;
		if (token[abc] == "ELSETK")
		{

			abc++;
			if (checkSentence(abc))
			{

				return true;
			}
			else
			{
				error(abc);
				return false;
			}
		}
		return true;
	}
	else
	{
		error(abc);
		return false;
	}
}
string mipsExpres(int sta, int end);
void mips_move(string rs, string rt);

bool check_sentence_assign(int abc)
{
	if (token[abc] == "IDENFR" && token[abc + 1] != "LPARENT")
	{
		check_exist(abc);
		checkConstTK(abc);

		string reg_now = reg[strInit[abc]];
		abc++;
		if (token[abc] == "LBRACK")
		{

			abc++;
			int ck = checkExpre(abc);
			string reg_ans = mipsExpres(abc, ck - 1);
			mips_move(reg_now, reg_ans);
			if (ck != -1)
				abc = ck;
			else
				return false;

			if (token[abc] == "RBRACK")
			{

				abc++;
			}
			else
			{
				checkKuoHao(abc);
			}
			if (token[abc] == "LBRACK")
			{

				abc++;
				ck = checkExpre(abc);
				if (ck != -1)
					abc = ck;
				else
					return false;

				if (token[abc] == "RBRACK")
				{

					abc++;
				}
				else
				{
					checkKuoHao(abc);
				}
			}
		}
		if (token[abc] == "ASSIGN")
		{

			abc++;
			int ck = checkExpre(abc);
			string reg_ans = mipsExpres(abc, ck - 1);
			mips_move(reg_now, reg_ans);
			if (ck != -1)
				abc = ck;
			else
				return false;
		}
		if (token[abc] == "SEMICN")
		{

			abc++;
		}
		else
		{
			checkFenhao(abc);
		}
		tokenNow = abc;
		return true;
	}
	else
		return false;
}

void mipsScanf()
{
	mips[++mipsNum].op = "li";
	mips[mipsNum].rs = "$v0";
	mips[mipsNum].rt = "5";
	mips[++mipsNum].op = "syscall";
}

void mips_move(string rs, string rt);

bool checkReadS(int abc)
{
	if (token[abc] == "SCANFTK" && token[abc + 1] == "LPARENT" && token[abc + 2] == "IDENFR")
	{
		check_exist(abc + 2);
		checkConstTK(abc + 2);
		mipsScanf();
		string sNow = reg[strInit[abc + 2]];
		mips_move(sNow, "$v0");

		abc++;

		abc++;

		abc++;
		if (token[abc] != "RPARENT")
		{
			checkPRA(abc);
		}
		else
		{

			abc++;
		}

		if (token[abc] == "SEMICN")
		{

			abc++;
		}
		else
		{
			checkFenhao(abc);
		}
		tokenNow = abc;
		return true;
	}
	else
		return false;
}

map<string, int> priority;
stack<string> symbol;
stack<string> item;
void init_priority()
{
	priority["*"] = 2;
	priority["/"] = 2;
	priority["+"] = 1;
	priority["-"] = 1;
	priority["("] = 0;
}

string find_t_free()
{
	for (int i = 0; i <= 9; i++)
	{
		if (!reg_t[i])
		{
			reg_t[i] = true;
			string tfree = "$t";
			tfree += ('0' + i);
			return tfree;
		}
	}
	return "ERROR";
}

void free_t(string t)
{
	reg_t[t[2] - '0'] = false;
	return;
}

void mips_addi(string rs, string rt, string rd)
{
	mips[++mipsNum].op = "addi";
	mips[mipsNum].rs = rs;
	mips[mipsNum].rt = rt;
	mips[mipsNum].rd = rd;
}
void mips_lw(string rs, string rt);
void mips_mul()
{
	symbol.pop();
	string rs_tmp = find_t_free();
	string rt_tmp;
	string rd_tmp;
	string it1 = item.top();
	item.pop();
	string it2 = item.top();
	item.pop();
	if (it2[0] != '$')
	{
		rt_tmp = find_t_free();
		if (it2[0] < '0' || it2[0] > '9')
		{
			mips_lw(rt_tmp, it2);
		}
		else
			mips_addi(rt_tmp, "$0", it2);
	}
	else
	{
		rt_tmp = it2;
	}
	if (it1[0] != '$')
	{
		rd_tmp = find_t_free();
		if (it1[0] < '0' || it1[0] > '9')
		{
			mips_lw(rd_tmp, it1);
		}
		else
			mips_addi(rd_tmp, "$0", it1);
	}
	else
	{
		rd_tmp = it1;
	}
	mips[++mipsNum].op = "mul";
	mips[mipsNum].rs = rs_tmp;
	mips[mipsNum].rt = rt_tmp;
	mips[mipsNum].rd = rd_tmp;
	free_t(rt_tmp);
	free_t(rd_tmp);
	item.push(rs_tmp);
}

void mips_div()
{
	symbol.pop();
	string rs_tmp = find_t_free();
	string rt_tmp;
	string rd_tmp;
	string it1 = item.top();
	item.pop();
	string it2 = item.top();
	item.pop();
	if (it2[0] != '$')
	{
		rt_tmp = find_t_free();
		if (it2[0] > '0' || it2[0] > '9')
		{
			mips_lw(rt_tmp, it2);
		}
		else
			mips_addi(rt_tmp, "$0", it2);
	}
	else
	{
		rt_tmp = it2;
	}
	if (it1[0] != '$')
	{
		rd_tmp = find_t_free();
		if (it1[0] < '0' || it1[0] > '9')
		{
			mips_lw(rd_tmp, it1);
		}
		else
			mips_addi(rd_tmp, "$0", it1);
	}
	else
	{
		rd_tmp = it1;
	}
	mips[++mipsNum].op = "div";
	mips[mipsNum].rs = rs_tmp;
	mips[mipsNum].rt = rt_tmp;
	mips[mipsNum].rd = rd_tmp;
	free_t(rt_tmp);
	free_t(rd_tmp);
	item.push(rs_tmp);
}

void mips_add()
{
	symbol.pop();
	string rs_tmp = find_t_free();
	string rt_tmp;
	string rd_tmp;
	string it1 = item.top();
	item.pop();
	string it2 = item.top();
	item.pop();
	if (it2[0] != '$')
	{
		rt_tmp = find_t_free();
		if (it2[0] < '0' || it2[0] > '9')
		{
			mips_lw(rt_tmp, it2);
		}
		else
			mips_addi(rt_tmp, "$0", it2);
	}
	else
	{
		rt_tmp = it2;
	}
	if (it1[0] != '$')
	{
		rd_tmp = find_t_free();
		if (it1[0] < '0' || it1[0] > '9')
		{
			mips_lw(rd_tmp, it1);
		}
		else
			mips_addi(rd_tmp, "$0", it1);
	}
	else
	{
		rd_tmp = it1;
	}
	mips[++mipsNum].op = "add";
	mips[mipsNum].rs = rs_tmp;
	mips[mipsNum].rt = rt_tmp;
	mips[mipsNum].rd = rd_tmp;
	free_t(rt_tmp);
	free_t(rd_tmp);
	item.push(rs_tmp);
}

void mips_sub()
{
	symbol.pop();
	string rs_tmp = find_t_free();
	string rt_tmp;
	string rd_tmp;
	string it1 = item.top();
	item.pop();
	string it2 = item.top();
	item.pop();
	if (it2[0] != '$')
	{
		rt_tmp = find_t_free();
		if (it2[0] < '0' || it2[0] > '9')
		{
			mips_lw(rt_tmp, it2);
		}
		else
			mips_addi(rt_tmp, "$0", it2);
	}
	else
	{
		rt_tmp = it2;
	}
	if (it1[0] != '$')
	{
		rd_tmp = find_t_free();
		if (it1[0] < '0' || it1[0] > '9')
		{
			mips_lw(rd_tmp, it1);
		}
		else
			mips_addi(rd_tmp, "$0", it1);
	}
	else
	{
		rd_tmp = it1;
	}
	mips[++mipsNum].op = "sub";
	mips[mipsNum].rs = rs_tmp;
	mips[mipsNum].rt = rt_tmp;
	mips[mipsNum].rd = rd_tmp;
	free_t(rt_tmp);
	free_t(rd_tmp);
	item.push(rs_tmp);
}

void mips_lw(string rs, string rt)
{
	mips[++mipsNum].op = "lw";
	mips[mipsNum].rs = rs;
	mips[mipsNum].rt = rt;
}

string mipsExpres(int sta, int end)
{
	while (!symbol.empty())
		symbol.pop();
	while (!item.empty())
		item.pop();
	for (int i = sta; i <= end; i++)
	{
		if (strInit[i] == "(")
		{
			symbol.push(strInit[i]);
			continue;
		}
		if (strInit[i] == ")")
		{
			while (symbol.top() != "(")
			{
				if (symbol.top() == "*")
				{
					mips_mul();
					continue;
				}
				if (symbol.top() == "/")
				{
					mips_div();
					continue;
				}
				if (symbol.top() == "+")
				{
					mips_add();
					continue;
				}
				if (symbol.top() == "-")
				{
					mips_sub();
					continue;
				}
			}
			symbol.pop();
			continue;
		}
		if (strInit[i] == "+" || strInit[i] == "-" || strInit[i] == "*" || strInit[i] == "/")
		{
			if (symbol.empty())
			{
				symbol.push(strInit[i]);
				continue;
			}
			if (priority[symbol.top()] >= priority[strInit[i]])
			{
				if (symbol.top() == "*")
				{
					mips_mul();
					symbol.push(strInit[i]);
					continue;
				}
				if (symbol.top() == "/")
				{
					mips_div();
					symbol.push(strInit[i]);
					continue;
				}
				if (symbol.top() == "+")
				{
					mips_add();
					symbol.push(strInit[i]);
					continue;
				}
				if (symbol.top() == "-")
				{
					mips_sub();
					symbol.push(strInit[i]);
					continue;
				}
			}
			symbol.push(strInit[i]);
			continue;
		}
		if (reg.count(strInit[i]))
		{
			item.push(reg[strInit[i]]);
			continue;
		}
		else
			item.push(strInit[i]);
	}
	while (!symbol.empty())
	{
		if (symbol.top() == "*")
		{
			mips_mul();
			continue;
		}
		if (symbol.top() == "/")
		{
			mips_div();
			continue;
		}
		if (symbol.top() == "+")
		{
			mips_add();
			continue;
		}
		if (symbol.top() == "-")
		{
			mips_sub();
			continue;
		}
	}
	string ans = item.top();
	if (ans[0] != '$')
	{
		string t_tmp = find_t_free();
		if (memint.count(ans))
		{
			mips_lw(t_tmp, ans);
		}
		if (ans[0] <= '9' && ans[0] >= '0')
		{
			mips_addi(t_tmp, "$0", ans);
		}
		ans = t_tmp;
	}
	return ans;
}

void mips_printStr(int cnt)
{
	mips[++mipsNum].op = "li";
	mips[mipsNum].rs = "$v0";
	mips[mipsNum].rt = "4";
	mips[++mipsNum].op = "la";
	mips[mipsNum].rs = "$a0";
	mips[mipsNum].rt = "conststr";
	mips[mipsNum].rt += ('0' + cnt);
	mips[++mipsNum].op = "syscall";
}

void mips_move(string rs, string rt)
{
	mips[++mipsNum].op = "move";
	mips[mipsNum].rs = rs;
	mips[mipsNum].rt = rt;
}

void mips_printVal(string reg_ans)
{
	mips[++mipsNum].op = "li";
	mips[mipsNum].rs = "$v0";
	mips[mipsNum].rt = "1";
	mips_move("$a0", reg_ans);
	mips[++mipsNum].op = "syscall";
}

void mips_print_newline()
{
	mips[++mipsNum].op = "li";
	mips[mipsNum].rs = "$v0";
	mips[mipsNum].rt = "4";
	mips[++mipsNum].op = "la";
	mips[mipsNum].rs = "$a0";
	mips[mipsNum].rt = "newline";
	mips[++mipsNum].op = "syscall";
}

int checkStatic(int abc, int s1)
{
	if (checkInt(abc))
	{
		if (token[abc] != "INTCON")
			abc++;
		if (s1 == 2)
			checkChangNoMatch(abc);
	}
	else if (token[abc] == "CHARCON")
	{

		check_charcon_c(abc);
		if (s1 == 1)
			checkChangNoMatch(abc);
	}
	else
		return -1;
	return abc + 1;
}

bool checkSubcase(int abc, int s1)
{
	if (token[abc] == "CASETK")
	{

		abc++;
		abc = checkStatic(abc, s1);

		if (abc == -1)
			return false;
		if (token[abc] == "COLON")
		{

			abc++;
			if (checkSentence(abc))
			{

				return true;
			}
		}
		else
		{
			error(abc);
			return false;
		}
	}
	else
		return false;
	return true;
}

bool checkSentenceWrite(int abc)
{
	if (token[abc] == "PRINTFTK" && token[abc + 1] == "LPARENT")
	{

		abc++;

		abc++;
	}
	else
		return false;
	if (token[abc] == "STRCON")
	{

		memeryConstructure[++memstrCnt] = strInit[abc];
		mips_printStr(memstrCnt);

		abc++;

		if (token[abc] == "COMMA")
		{

			abc++;
			int ck = checkExpre(abc);
			string reg_ans = mipsExpres(abc, ck - 1);
			mips_printVal(reg_ans);
			if (reg_ans[1] == 't')
				free_t(reg_ans);
			if (ck != -1)
				abc = ck;
			else
				return false;

			if (token[abc] == "RPARENT")
			{

				abc++;
			}
		}
		else if (token[abc] == "RPARENT")
		{

			abc++;
		}
	}
	else
	{
		int ck = checkExpre(abc);
		string reg_ans = mipsExpres(abc, ck - 1);
		mips_printVal(reg_ans);
		if (ck != -1)
			abc = ck;

		if (token[abc] == "RPARENT")
		{

			abc++;
		}
	}
	if (token[abc] == "SEMICN")
	{
		abc++;
	}
	mips_print_newline();
	tokenNow = abc;
	return true;
}

int checkCaseTable(int abc, int s1)
{
	bool pd = false;
	while (checkSubcase(abc, s1))
	{
		pd = true;
		abc = tokenNow;
		if (ERROR)
			return -1;
	}
	if (pd)
	{

		return abc;
	}
	else
		return -1;
}

int checkDefault(int abc)
{
	if (token[abc] == "DEFAULTTK")
	{

		abc++;
		if (token[abc] == "COLON")
		{

			abc++;
			if (checkSentence(abc))
			{

				return tokenNow;
			}
		}
		else
			return -1;
	}
	else
		return -1;
	return true;
}

bool checkSentenceCase(int abc)
{
	if (token[abc] == "SWITCHTK" && token[abc + 1] == "LPARENT")
	{

		abc++;

		abc++;
	}
	else
		return false;
	type = "1";
	int ck = checkExpre(abc);
	int s1 = 1;
	if (type == "0")
		s1 = 2;
	if (ck != -1)
		abc = ck;
	else
		return false;

	if (token[abc] == "RPARENT")
	{

		abc++;
	}
	else
	{
		checkPRA(abc);
	}
	if (token[abc] == "LBRACE")
	{

		abc++;
		abc = checkCaseTable(abc, s1);
		if (abc == -1)
			return false;
		int ck = checkDefault(abc);
		if (ck == -1)
		{
			checkNoDef(abc);
		}
		else
			abc = ck;
		if (token[abc] == "RBRACE")
		{

			abc++;
		}
		else
		{

			error(abc);
			return false;
		}
	}
	else
	{
		error(abc);
		return false;
	}
	tokenNow = abc;
	return true;
}

bool checkSentenceReturn(int abc)
{
	if (token[abc] == "RETURNTK")
	{

		abc++;
	}
	else
		return false;
	return_pd = true;
	if (token[abc] == "SEMICN")
	{

		abc++;
		tokenNow = abc;
		if (return_type == 2)
		{
			check_return_error(abc);
		}
		return true;
	}
	else if (token[abc] == "LPARENT")
	{
		if (token[abc + 1] == "RPARENT" && return_type == 2)
		{
			check_return_error(abc);
		}
		if (return_type == 1)
			check_noreturn_error(abc);

		abc++;
		type = "1";
		int ck = checkExpre(abc);
		if ((type == "1" && !return_int) || (type == "0" && return_int))
		{
			if (return_type == 2)
				check_return_error(abc);
		}
		if (ck != -1)
			abc = ck;
		else
			return false;

		if (token[abc] == "RPARENT")
		{

			abc++;
		}
		else
		{
			checkPRA(abc);
		}
		if (token[abc] == "SEMICN")
		{

			abc++;
		}
		else
		{
			error(abc);
			return false;
		}
		tokenNow = abc;
		return true;
	}
	else
	{
		checkFenhao(abc);
	}
	return true;
}

bool checkSentenceRow();

bool checkSentence(int abc)
{
	if (token[abc] == "LBRACE")
	{

		tokenNow = abc + 1;
		if (checkSentenceRow())
		{

			int x = 1;
		}
		else
			return false;
		abc = tokenNow;
		if (token[abc] == "RBRACE")
		{

			tokenNow = abc + 1;
			return true;
		}
		else
		{
			error(2475);
			return false;
		}
	}
	if (token[abc] == "SEMICN")
	{

		tokenNow = abc + 1;
		return true;
	}
	if (checkSentenceOnce(abc))
	{

		return true;
	}
	if (checkSentenceIF(abc))
	{

		return true;
	}
	if (checkSentenceWithNoReturn(abc))
	{
		abc = tokenNow;
		if (token[abc] == "SEMICN")
		{

			tokenNow = abc + 1;
		}
		else
		{
			checkFenhao(abc);
		}
		return true;
	}
	if (checkSentenceFuncReturn(abc))
	{
		abc = tokenNow;
		if (token[abc] == "SEMICN")
		{

			tokenNow = abc + 1;
		}
		else
		{
			checkFenhao(abc);
		}
		return true;
	}
	if (check_sentence_assign(abc))
	{
		return true;
	}
	if (checkReadS(abc))
	{
		return true;
	}
	if (checkSentenceWrite(abc))
	{
		return true;
	}
	if (checkSentenceCase(abc))
	{

		return true;
	}
	if (checkSentenceReturn(abc))
	{
		return true;
	}
	return false;
}

bool checkSentenceRow()
{
	while (checkSentence(tokenNow))
	{

		if (ERROR)
			return false;
		int x = 1;
	}
	return true;
}

bool checkCompoud(int abc)
{
	tokenNow = abc;
	if (checkChange(false))
	{
	}
	if (cycleCheck(false))
	{
	}
	if (checkSentenceRow())
	{

		return true;
	}
	return false;
}

bool checkReturnFunc(int abc)
{
	string func;
	int top_tmp = top;
	if ((token[abc] == "INTTK" || token[abc] == "CHARTK") && token[abc + 1] == "IDENFR" && token[abc + 2] == "LPARENT")
	{
		if (token[abc] == "INTTK")
			return_int = true;
		else
			return_int = false;
		cout << token[abc] << " " << strInit[abc] << endl;
		cout << token[abc + 1] << " " << strInit[abc + 1] << endl;
		check_redefine(abc + 1);
		s_define[++top] = strInit[abc + 1];
		func = strInit[abc + 1];
		mp_return[func] = true;

		paracnt = 0;
		typeNow = "";
		int ck = check_para(abc + 3);
		mp_paraNum[strInit[abc + 1]] = paracnt;
		mp_paratype[strInit[abc + 1]] = typeNow;
		if (ck == -1)
		{
			return false;
		}
		else
			abc = ck;

		if (token[abc] != "RPARENT")
		{
			checkPRA(abc);
		}

		abc++;
		if (token[abc] != "LBRACE")
		{
			error(abc);
			return false;
		}
		else
		{

			return_type = 2;
			return_pd = false;
			if (checkCompoud(++abc))
			{

				abc = tokenNow;
				if (token[abc] == "RBRACE")
				{

					abc++;
				}
				else
				{
					error(abc);
					return false;
				}
			}
			if (!return_pd)
				check_return_error(abc);
			tokenNow = abc;
			top = top_tmp;
			return true;
		}
	}
	else
		return false;
}

bool checkFuncNoReturn(int abc)
{
	string func;
	int top_tmp = top;
	if (token[abc] == "VOIDTK" && token[abc + 1] == "IDENFR" && token[abc + 2] == "LPARENT")
	{

		func = strInit[abc + 1];
		mp_return[func] = false;

		paracnt = 0;
		typeNow = "";
		int ck = check_para(abc + 3);
		mp_paraNum[strInit[abc + 1]] = paracnt;
		mp_paratype[strInit[abc + 1]] = typeNow;
		if (ck == -1)
		{
			return false;
		}
		else
			abc = ck;

		if (token[abc] != "RPARENT")
		{
			checkPRA(abc);
		}

		abc++;
		if (token[abc] != "LBRACE")
		{
			error(2673);
			return false;
		}
		else
		{

			return_type = 1;
			if (checkCompoud(++abc))
			{

				abc = tokenNow;
				if (token[abc] == "RBRACE")
				{

					abc++;
				}
				else
				{
					error(2691);
					return false;
				}
			}
			tokenNow = abc;
			top = top_tmp;
			return true;
		}
	}
	else
		return false;
}

bool checkMain(int abc)
{
	if (token[abc] == "VOIDTK" && token[abc + 1] == "MAINTK" && token[abc + 2] == "LPARENT")
	{

		abc++;

		abc++;

		abc++;
		if (token[abc] != "RPARENT")
			checkPRA(abc);

		abc++;
	}
	else
		return false;
	if (token[abc] != "LBRACE")
	{
		error(2720);
		return false;
	}

	abc++;
	return_type = 1;
	if (checkCompoud(abc))
	{

		abc = tokenNow;
		if (token[abc] != "RBRACE")
		{
			return false;
		}

		abc++;
		return true;
	}
	else
	{
		return false;
	}
}

bool checkProgram()
{
	if (checkChange(false))
	{
	}
	if (cycleCheck(false))
	{
	}
	rs = top + 1;
	while (!checkMain(tokenNow))
	{
		int top_tmp = top;
		if (checkFuncNoReturn(tokenNow))
		{
		}
		top = top_tmp;
		top_tmp = top;
		if (checkReturnFunc(tokenNow))
		{
		}
		top = top_tmp;
		if (ERROR)
		{
			return false;
		}
	}

	return true;
}

void syntaxAnalysis()
{
	if (checkProgram())
		cout << "";
}

int main()
{
	freopen("testfile.txt", "r", stdin);
	init();
	init_priority();
	ERROR = false;
	int timeLast = 0;
	string str;
	int linecnt = 0;
	tokenNum = 0;
	while (getline(cin, str))
	{
		linecnt++;
		FSM(str, linecnt);
		if (timeLast == tokenNum)
		{
			linecnt--;
		}
		else
		{
			timeLast = tokenNum;
		}
	}
	tokenNow = 1;

	freopen("mips.txt", "w", stdout);
	syntaxAnalysis();

	int linelast = 0;
	cout << ".data" << endl;
	cout << "newline: .asciiz \"\\n\"" << endl;
	map<string, string>::iterator it = memint.begin();
	while (it != memint.end())
	{
		cout << it->first << ": .word " << it->second << endl;
		it++;
	}
	it = memStr.begin();
	while (it != memStr.end())
	{
		cout << it->first << ": .asciiz " << it->second << endl;
		it++;
	}
	for (int i = 1; i <= memstrCnt; i++)
	{
		cout << "conststr" << i << ":"
			 << " .asciiz \"" << memeryConstructure[i] << "\"" << endl;
	}
	cout << ".text" << endl;
	cout << "main:" << endl;
	bool fst = true;
	for (int i = 1; i <= mipsNum; i++)
	{
		if (fst)
		{
			fst = false;
		}
		else
			cout << endl;
		cout << mips[i].op;
		if (mips[i].rs == "")
			continue;
		else
			cout << " " << mips[i].rs;
		if (mips[i].rt == "")
			continue;
		else
			cout << ", " << mips[i].rt;
		if (mips[i].rd == "")
			continue;
		else
			cout << ", " << mips[i].rd;
	}
	fclose(stdin);
	fclose(stdout);

	return 0;
}
