#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#ifndef SUCCESS
#define SUCCESS						0
#endif

#define DEFAULT_ERRNO 				-10000
#define SQL_NULL_POINTER			-10001
#define SQL_PREPARE_STEP_ERROR		-10002
#define SQL_CREATE_PREPARE_ERROR	-10003
#define SQL_FREE_PREPARE_ERROR		-10004
#define SQL_DATABASE_BUSY			-10005
#define SQL_NOT_BIND_VALUES			-10006

#define DEFAULT_MSG "Unknown Exception"

#define SQL_PREPARE_EXCEPTION \
	"Cannot create a prepared statement"

#define SQL_STATEMENT_NULL_EXCEPTION \
	"Statement is NULL"

#define SQL_NOT_BIND_VALUES_EXCEPTION \
	"Need bind values before executing a statement."

#define SQL_OPEN_DATABASE_EXCEPTOIN \
	"Cannot open database "

#define SQL_DATABASE_ENCRYPT_EXCEPTION \
	"Cannot decrypt database "

#define SQL_CREATE_TABLE_EXCEPTION \
	"Cannot create table with SQL: "

#define SQL_BEGIN_EXCEPTION \
	"Cannot BEGIN TRANSACTION"

#define SQL_COMMIT_EXCEPTION \
	"Cannot COMMIT TRANSACTION"

#define SQL_ROLLBACK_EXCEPTION \
	"Cannot ROLLBACK TRANSACTION"


#endif
