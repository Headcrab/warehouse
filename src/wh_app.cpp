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
	// ������������� ��������� �������
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

string app::wrong(string s)
{
	cout << "������� \"" << s << "\" �� ����������" << endl;
	help(s);
	return "";
}

string app::help(string)
{
	cout << "��������� �������:\n\
	h - ������\n\
	v - ������ ���������\n\
	q - �����\n\
	a - ������ ������ �� �����\n\
	i - �������� ������� �������\n\
	l - �������� ������\n\
	o - ������� ������ �� �����\n\
	c - �������� ������� �������\n\
	" << endl;
	return "";
}

string app::version(string)
{
	cout << "������ 0.1" << endl;
	return "0.1";
}

string app::quit(string)
{
	cout << "���������� ������." << endl;
	return "quit";
}

};
