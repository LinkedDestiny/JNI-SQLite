#include "Database.h"
#include "sqlite3.h"
#include "LogCat.h"

using namespace Database;

SQLite_Stmt::~SQLite_Stmt() {
	if(this->statement != NULL) {
		this->close();
	}
}

SQLite_Stmt* SQLite_Stmt::prepare(void* db, const std::string& sql) throw(SQLException) {
	sqlite3_stmt* tmp;
	int errno = sqlite3_prepare_v2((sqlite3*)db, sql.c_str(), -1, &tmp, 0);

	if( tmp == NULL ) {
		throw SQLException(SQL_PREPARE_EXCEPTION, errno);
	}
	this->statement = tmp;
	return this;
}

SQLite_Stmt* SQLite_Stmt::bindValues(const SQL_V_VEC* values) throw(SQLException) {
	sqlite3_stmt* tmp = (sqlite3_stmt*)this->statement;
	if(tmp == NULL) {
		throw SQLException(SQL_STATEMENT_NULL_EXCEPTION,
				SQL_NULL_POINTER);
	}
	int i = 1;
	SQL_V_VEC::const_iterator iter;
	FOREACH( (*values), iter ) {
		bind(tmp, i ++ , *iter);
	}
	isBind = true;
	return this;
}


SQLite_Stmt* SQLite_Stmt::execute() throw(SQLException) {
	int errno;
	if( !isBind ) {
		throw SQLException(SQL_STATEMENT_NULL_EXCEPTION,
				SQL_NOT_BIND_VALUES);
	}
	sqlite3_stmt* tmp = (sqlite3_stmt*)this->statement;
	if(tmp == NULL) {
		throw SQLException(SQL_STATEMENT_NULL_EXCEPTION,
				SQL_NULL_POINTER);
	}
	SQL_VALUES_VEC* value_list = new SQL_VALUES_VEC();
BUSY:
	while( ( errno = sqlite3_step(tmp) ) == SQLITE_ROW ) {
		int i = 0;
		sqlite3_value* value;
		SQL_V_VEC* sets = new SQL_V_VEC();
		int counts = sqlite3_column_count(tmp);
		for(; i < counts ; i ++ ) {
			const char* s_name = sqlite3_column_name(tmp,i);
			value = sqlite3_column_value(tmp,i);
			SqlValue* v = getValue( value );
			v->name = s_name;
			sets->push_back(v);
		}
		value_list->push_back(sets);
	}

	this->dataset = value_list;

	if( errno == SQLITE_DONE ) {		// finish successfully
		errno = SUCCESS;
		return this;
	}
	else if( errno == SQLITE_BUSY ) {	// database busy
		sleep(1);
		goto BUSY;
	}
	else if( errno == SQLITE_OK ){
		errno = SUCCESS;
		return this;
	}
	else {	// error
		throw SQLException(SQL_STATEMENT_NULL_EXCEPTION,
				SQL_PREPARE_STEP_ERROR);
	}

}

SQLite_Stmt* SQLite_Stmt::reset() throw(SQLException) {
	sqlite3_stmt* tmp = (sqlite3_stmt*)this->statement;
	if(tmp == NULL) {
		throw SQLException(SQL_STATEMENT_NULL_EXCEPTION,
						SQL_NULL_POINTER);
	}
	sqlite3_reset(tmp);
	isBind = false;
	return this;
}

void SQLite_Stmt::close() {
	sqlite3_stmt* tmp = (sqlite3_stmt*)this->statement;
	if(tmp != NULL) {
		sqlite3_finalize(tmp);
		this->statement = NULL;
	}
}

void SQLite_Stmt::bind(sqlite3_stmt* stmt, int i , SqlValue*value) {
	int errno;
	switch( value->type ) {
		case INTEGER: {
			errno = sqlite3_bind_int(stmt, i , value->data.integer);
			break;
		}
		case CHAR: {
			errno = sqlite3_bind_int(stmt, i , value->data.character);
			break;
		}
		case TEXT: {
			errno = sqlite3_bind_text(stmt, i , value->data.s , -1 , SQLITE_STATIC);
			break;
		}
		case DOUBLE: {
			errno = sqlite3_bind_double(stmt, i , value->data.doub);
			break;
		}
	}
}

SqlValue* SQLite_Stmt::getValue(sqlite3_value* value) {
	switch(sqlite3_value_type(value)) {
		case SQLITE_INTEGER : {
			return new SqlValue( sqlite3_value_int( value ) );
		}
		case SQLITE3_TEXT : {
			return new SqlValue( (char*)sqlite3_value_text( value ) );
		}
		case SQLITE_FLOAT : {
			return new SqlValue( sqlite3_value_double( value ) );
		}
	}
}

