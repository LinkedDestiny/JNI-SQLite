#ifndef _COMMON_H_
#define _COMMON_H_

#include <string>
#include <map>
#include <vector>
#include <typeinfo>
#include <string.h>
#include "LogCat.h"
#include "SQLException.h"

#define TAG 	"Log"

using namespace std;

namespace Database
{

/******************** Default Value ******************/

#define SQL_EOF 		"\n"
#define EMPTY			""

#define INDENT 			"\n	"
#define INDENTCVS 		",\n	"
#define PLACEHOLDER		",\n	?"

#define AND 			"AND "
#define OR 				"OR "


#define DISTINCT		"DISTINCT"
#define JOIN			" JOIN"
#define ON				"ON "
#define USING			"USING "
#define WHERE			"\nWHERE"
#define FROM			"\nFROM"
#define GROUP_BY		"\nGROUP BY"
#define HAVING			"\nHAVING"
#define FOR_UPDATE		"\nFOR UPDATE"
#define RETURING		"\nRETURING"
#define INTO			" INTO "
#define VALUES			"\n) VALUES ("
#define UPDATE_SET		"\nSET\n	"

#define SELECT			"SELECT"
#define INSERT			"INSERT"
#define UPDATE			"UPDATE"
#define DELETE			"DELETE"

#define BEGIN			"BEGIN TRANSACTION"
#define COMMIT			"COMMIT"
#define ROLLBACK		"ROLLBACK"



/******************** Default Value End **************/

union SQL_Data
{
	int integer;
	char character;
	char* s;
	double doub;
};

enum SQL_Type
{
	INTEGER,
	CHAR,
	TEXT,
	DOUBLE
};

class SqlValue
{
public:
	SqlValue(){ }

	SqlValue(int i){ setInteger(i); }
	SqlValue(char c){ setCharacter(c); }
	SqlValue(const char* s){ setText(s); }
	SqlValue(double d){ setDouble(d); }
	void setInteger(int i);
	void setCharacter(char c);
	void setText(const char* s);
	void setDouble(double d);

	std::string name;
	SQL_Data data;
	SQL_Type type;
};

/********************** Data Set *********************/
typedef map<std::string, SqlValue*> 		SQL_V_MAP;
typedef vector<std::string> 				SQL_S_VEC;
typedef vector<SqlValue*>					SQL_V_VEC;
typedef vector<SQL_S_VEC>					SQL_ARRAY_VEC;
typedef vector< SQL_V_VEC* >				SQL_VALUES_VEC;

#define FOREACH(v,iter) \
	for((iter) = (v).begin(); (iter) != (v).end(); (iter) ++ )

/********************** Data Set End *****************/

/****************** common function ******************/

std::string indent(const SQL_S_VEC& list);
std::string indentCsv(const SQL_S_VEC& list);
std::string implode(const std::string& delimiter, const SQL_S_VEC& list);

/****************** common function End **************/
}

#endif
