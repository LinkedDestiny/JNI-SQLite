#ifndef _SQLITE_H_
#define _SQLITE_H_

#include "Database.h"
#include "LogCat.h"

#ifndef TAG
#define TAG 	"SQLite"
#endif

namespace Database
{

class SQLite3 : virtual public Database
{
public:

	bool open(const std::string& db_name, void* options)throw(SQLException) ;

	bool create(const std::string& sql )throw(SQLException) ;

	Statement* prepare(const std::string& sql)throw(SQLException) ;

	int execute(const std::string& sql, exec_callback callback)throw(SQLException) ;

	bool begin()throw(SQLException) ;
	bool commit()throw(SQLException) ;
	bool rollback()throw(SQLException) ;

	bool close();

protected:
	sqlite3* db;
};

}

#endif
