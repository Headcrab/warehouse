//---------------------------------------------------------------------------

#ifndef wh_appH
#define wh_appH

#include <windows.h>
#include <iostream>
#include <string>
#include <locale>
#include <algorithm>
#include <cctype>
#include "sys_ini.h"
//---------------------------------------------------------------------------

namespace wh {

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::transform;
using app::ini;

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
