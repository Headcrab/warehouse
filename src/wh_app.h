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

// команды связанные с управлением приложением
class app {
public:

	ini ini;

	app();
	// ошибочная команда
	string wrong(string); 
	// помощь
	string help(string);
	// версия приложения
	string version(string);

	// выход
	string quit(string);
};

};

//---------------------------------------------------------------------------

#endif
