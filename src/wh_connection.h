//---------------------------------------------------------------------------
#ifndef wh_connectionH
#define wh_connectionH
//---------------------------------------------------------------------------
#include <windows.h>
#include <iomanip>
#include <iostream>
#include <sql.h>
#include <sqlext.h>
#include <sstream>
//---------------------------------------------------------------------------

namespace wh {

using std::cin;
using std::cout;
using std::endl;
using std::string;
//using std::to_string;
template <typename T>
string to_string(const T& n)
{
	std::ostringstream stm;
	stm << n;
	return stm.str();
}

void extract_error(
    char* fn,
    SQLHANDLE handle,
    SQLSMALLINT type);

// соединение и команды управления базой
class connection {
	SQLHENV env;
	SQLHDBC dbc;
	SQLHSTMT stmt;
	SQLRETURN ret; /* ODBC API return status */
	SQLSMALLINT columns; /* number of columns in result-set */
public:
	connection() { }
	~connection() { }
	int init(string const& init_str);

	// выборка из указанной таблицы
	string select(string);

	string store_state(string);
	// приход
	string add_product(string);
	// просмотр склада
	//	string check_store(string);
	string prod_in_state(string);

	string outgo_product(string);
	string prod_out_state(string);

private:
	void show_table(string);
};

};

//---------------------------------------------------------------------------

#endif
