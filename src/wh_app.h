//---------------------------------------------------------------------------

#ifndef wh_appH
#define wh_appH

#include <windows.h>
#include "sys_ini.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <locale>
#include <string>
//---------------------------------------------------------------------------

namespace wh {

using app::ini;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::transform;

string char2oem(string in);
string oem2char(string in);
string to_lower(string in);

// ������� ��������� � ����������� �����������
class app {
public:
	ini ini;

	app();
	// ��������� �������
	string wrong(string);
	// ������
	string help(string);
	// ������ ����������
	string version(string);

	// �����
	string quit(string);
};

};

//---------------------------------------------------------------------------

#endif
