#include <windows.h>
#include <stdio>
#include <stdlib>
#include <iostream>
#include <sql.h>
#include <sqlext.h>
#include <string>
#include "wh_app.h"
#include "wh_connection.h"
#include <map>
//#include "odbc32.lib"

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;

int main(int argc, char** argv)
{
	wh::app app;
	wh::connection conn;

	if(!conn.init("DSN="+app.ini.get("connection","DSN")+";Uid="
	+app.ini.get("connection","Uid")+";Pwd="+app.ini.get("connection","Pwd")+""))
		return 1;

	// объявляю команды
	// todo: нужно сделать отдельный класс конечно
	typedef string(__closure * fptr)(string);
	map<string, fptr> command;
	command["s"] = &conn.select;
	command["h"] = &app.help;
	command["v"] = &app.version;
	command["q"] = &app.quit;
	command["a"] = &conn.add_product;
	command["i"] = &conn.prod_in_state;
	command["l"] = &conn.store_state;
//	command["c"] = &conn.check_store;
/*
	// словом тоже можно
	command["store"] = &conn.store_state;
	command["select"] = &conn.select;
	command["help"] = &app.help;
	command["version"] = &app.version;
	command["quit"] = &app.quit;

	// и по русски
	command["выход"] = &app.quit;
	command["помощь"] = &app.help;
*/
	string cl;
	string res;

	// бесконечный цикл пока пользователь не даст команду на выход
	typedef map<string, fptr>::iterator whmi;
	while (true)
	{
		cl = "";
		cout << ("команда->");
		cin >> cl;
//		cl+=" ";
		whmi mi = command.find(wh::to_lower(cl));
//		whmi mi = command.find(wh::to_lower(cl.substr(0,cl.find(" ",0))));
		if (mi == command.end()) {
			app.wrong(cl);
			continue;
		}
		res = (*mi).second(wh::to_lower(cl));
		if (res == "quit")
			break;
	}
	return 0;
}
