//---------------------------------------------------------------------------

#pragma hdrstop

#include "wh_app.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace wh {

string to_lower(string in)
{
	char* locale = setlocale(LC_ALL, NULL);
	setlocale(LC_ALL, "rus");
	transform(in.begin(), in.end(), in.begin(), tolower);
	setlocale(LC_ALL, locale);
	return in;
}

app::app()
{
	// устанавливаем кодировку консоли
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

string app::wrong(string s)
{
	cout << " оманда \"" << s << "\" не распознана" << endl;
	help(s);
	return "";
}

string app::help(string)
{
	cout << "ƒоступные команды:\n\
	h - помощь\n\
	v - верси€ программы\n\
	q - выход\n\
	a - приход товара на склад\n\
	i - просмотр таблицы прихода\n\
	l - просмотр склада\n\
	o - выписка товара со слада\n\
	c - просмотр таблицы выписок\n\
	" << endl;
	return "";
}

string app::version(string)
{
	cout << "¬ерси€ 0.1" << endl;
	return "0.1";
}

string app::quit(string)
{
	cout << "«авершение работы." << endl;
	return "quit";
}

};
