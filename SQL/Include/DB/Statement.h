#ifndef _STATEMENT_H_
#define _STATEMENT_H_

#include "sqlite3.h"
#include "Common.h"
#include <unistd.h>

namespace Database
{

class Statement
{
public:
	virtual ~Statement(){}
	/**
	 * Create a prepare_statement
	 */
	virtual Statement* prepare(void* db, const std::string& sql) throw(SQLException) =0;

	virtual Statement* bindValues(const SQL_V_VEC* values)throw(SQLException)=0;

	virtual Statement* execute()throw(SQLException)=0;

	virtual Statement* reset()throw(SQLException)=0;

	virtual void close()=0;

	void* getResult(){ return dataset; }

protected:
	void* statement;
	void* dataset;

	bool isBind;
};

class SQLite_Stmt : virtual public Statement
{
public:

	~SQLite_Stmt();

	SQLite_Stmt* prepare(void* db, const std::string& sql) throw(SQLException);

	SQLite_Stmt* bindValues(const SQL_V_VEC* values) throw(SQLException);

	SQLite_Stmt* execute() throw(SQLException);

	SQLite_Stmt* reset() throw(SQLException);

	void close();

protected:
	void bind(sqlite3_stmt* stmt, int i , SqlValue*value);
	SqlValue* getValue(sqlite3_value* value);
};

}


#endif
