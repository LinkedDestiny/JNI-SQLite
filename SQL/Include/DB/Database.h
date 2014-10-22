#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <string>

#ifndef SQLITE_HAS_CODEC
#define SQLITE_HAS_CODEC
#endif

#include "sqlite3.h"
#include "Statement.h"

using namespace std;

namespace Database
{


typedef int exec_callback(void *data, int col_count,
			char **col_values, char **col_Name);

typedef int(*prepare_callback)(void *data, sqlite3_stmt *statement);


class Database
{
public:
	virtual bool open(const std::string& db_name, void* options)throw(SQLException) =0;
	virtual bool close()=0;

	virtual Statement* prepare(const std::string& sql)throw(SQLException) =0;
	virtual int execute(const std::string& sql, exec_callback callback)throw(SQLException) =0;

	virtual bool begin()throw(SQLException) =0;
	virtual bool commit()throw(SQLException) =0;
	virtual bool rollback()throw(SQLException) =0;

	int errCode() {return errno; }
	string errMsg() { return msg; }
protected:
	string msg;
	int errno;
};

}


#endif
