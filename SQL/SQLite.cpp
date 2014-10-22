#include "SQLite.h"

using namespace Database;

bool SQLite3::open(const std::string& db_name, void* options) throw(SQLException) {

	int errno = sqlite3_open_v2(db_name.c_str(), &this->db,
			SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
	if (SQLITE_OK != errno) {
		throw SQLException((SQL_OPEN_DATABASE_EXCEPTOIN + db_name).c_str() ,
				errno );
	}

	errno = sqlite3_key_v2(this->db, db_name.c_str(), "1q2w3e4r", 8 );
	if (SQLITE_OK != errno) {
		throw SQLException((SQL_DATABASE_ENCRYPT_EXCEPTION + db_name).c_str() ,
						errno );
	}
	return true;
}

bool SQLite3::create(const std::string& sql) throw(SQLException) {
	int errno = sqlite3_exec(this->db, sql.c_str(), NULL , NULL, NULL );
	if (SQLITE_OK != errno) {
		throw SQLException((SQL_CREATE_TABLE_EXCEPTION + sql).c_str() ,
								errno );
	}
	return true;
}

bool SQLite3::close() {
	sqlite3_close(this->db);
	return true;
}


int SQLite3::execute(const std::string& sql, exec_callback callback) throw(SQLException) {
	int errno = sqlite3_exec(this->db, sql.c_str() , callback , NULL, NULL );
	return this->errno;
}

bool SQLite3::begin() throw(SQLException) {
	int errno = sqlite3_exec(this->db, BEGIN , NULL , NULL, NULL );
	if (SQLITE_OK != errno) {
		log(LOG_DEBUG, TAG ,"BEGIN Error" );
		throw SQLException(SQL_BEGIN_EXCEPTION ,
										errno );
	}
	return true;
}

bool SQLite3::commit() throw(SQLException) {
	int errno = sqlite3_exec(this->db, COMMIT , NULL , NULL, NULL );
	if (SQLITE_OK != errno) {
		throw SQLException(SQL_COMMIT_EXCEPTION ,
										errno );
	}
	return true;
}

bool SQLite3::rollback() throw(SQLException) {
	int errno = sqlite3_exec(this->db, ROLLBACK , NULL , NULL, NULL );
	if (SQLITE_OK != errno) {
		throw SQLException(SQL_ROLLBACK_EXCEPTION ,
										errno );
	}
	return true;
}


Statement* SQLite3::prepare(const std::string& sql)throw(SQLException) {
	SQLite_Stmt* statement = new SQLite_Stmt();
	return statement->prepare(this->db, sql);
}
