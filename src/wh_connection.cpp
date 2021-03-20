//---------------------------------------------------------------------------
#pragma hdrstop

#include "wh_connection.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace wh {

void extract_error(
    char* fn,
    SQLHANDLE handle,
    SQLSMALLINT type)
{
	SQLINTEGER i = 0;
	SQLINTEGER native;
	SQLCHAR state[7];
	SQLCHAR text[256];
	SQLSMALLINT len;
	SQLRETURN ret;
	do {
		ret = SQLGetDiagRec(type, handle, ++i, state, &native, text,
		    sizeof(text), &len);
		if (SQL_SUCCEEDED(ret))
			cout << state << i << native << text << endl;
	} while (ret == SQL_SUCCESS);
}

int connection::init(string const& init_str)
{
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
	SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	SQLSetConnectAttr(env, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_ON, SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);

	// задаем DSN, пользователя и пароль
	SQLRETURN error = SQLDriverConnect(dbc, NULL, (unsigned char*)init_str.c_str(), SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);
	if (error == SQL_SUCCESS || error == SQL_SUCCESS_WITH_INFO) {
		cout << "Соединение установлено" << endl;
		return 1;
	}
	cout << "Невозможно подключиться к базе данных" << endl;
	return 0;
}

void connection::show_table(string tbl)
{
	int row = 0;
	SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
	SQLExecDirect(stmt, (unsigned char*)("select * from " + tbl).c_str(), SQL_NTS);
	// количество колонок
	SQLNumResultCols(stmt, &columns);
	cout << endl;
	while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
		SQLUSMALLINT i;
		row++;
		// цикл по колонкам
		for (i = 1; i <= columns; i++) {
			SQLINTEGER indicator;
			char buf[512];
			// получем данные солонки
			ret = SQLGetData(stmt, i, SQL_C_CHAR, buf, sizeof(buf), &indicator);
			if (SQL_SUCCEEDED(ret)) {
				// пустые игнорируем
				if (indicator == SQL_NULL_DATA)
					*buf = *string("NULL").c_str();
				cout << "|" << std::setfill(' ') << std::setw(20) << buf << " ";
			}
		}
		cout << "|" << endl;
	}
	cout << endl;
	SQLFreeStmt(stmt, SQL_CLOSE);
}

string connection::select(string s)
{
	string tbl;
	cout << "table name:";
	cin >> tbl;
	show_table(tbl);
	return "";
}

string connection::add_product(string)
{
	int prov, prod, store;
	double count;
	show_table("provider");
	cout << "поставщик:";
	cin >> prov;

	show_table("product");
	cout << "продукт:";
	cin >> prod;

	cout << "количество:";
	cin >> count;

	show_table("stores");
	cout << "склад:";
	cin >> store;

	string sql = "arrival " + to_string(prov) + ", " + to_string(prod) + ", " + to_string(count) + ", " + to_string(store) + "";
	SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
	SQLSetConnectAttr(env, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_ON, SQL_IS_INTEGER);
	SQLExecDirect(stmt, (unsigned char*)sql.c_str(), SQL_NTS);
	SQLFreeStmt(stmt, SQL_CLOSE);
	SQLFreeHandle(SQL_HANDLE_STMT, stmt);

	return "";
}

string connection::store_state(string)
{
	show_table("store_state");
	return "";
}

string connection::prod_in_state(string)
{
	show_table("prod_in_state");
	return "";
}

string connection::outgo_product(string)
{
	int prov, prod, store;
	double count;
	show_table("clients");
	cout << "получатель:";
	cin >> prov;

	show_table("product");
	cout << "продукт:";
	cin >> prod;

	cout << "количество:";
	cin >> count;

	show_table("stores");
	cout << "склад:";
	cin >> store;

	string sql = "consumption " + to_string(prov) + ", " + to_string(prod) + ", " + to_string(count) + ", " + to_string(store) + "";
	SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
	SQLSetConnectAttr(env, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_ON, SQL_IS_INTEGER);
	SQLExecDirect(stmt, (unsigned char*)sql.c_str(), SQL_NTS);
	SQLFreeStmt(stmt, SQL_CLOSE);
	SQLFreeHandle(SQL_HANDLE_STMT, stmt);

	return "";
}

string connection::prod_out_state(string)
{
	show_table("prod_out_state");
	return "";
}

};
