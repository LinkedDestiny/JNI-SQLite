#include "com_link_storage_jni_JniClient.h"
#include "SQLite.h"
#include "QueryFactory.h"
#include "LogCat.h"
#include "JniCode.h"
#include <android/asset_manager.h>
#include <stdio.h>
#include <string>

using namespace std;
using namespace Database;

#ifdef __cplusplus
extern "C" {
#endif

#define DB_FILE "/data/data/com.link.storage/test.db"

#ifndef TAG
#define TAG 	"Test"
#endif

void testInsert(SQLite3* database);
void testSelect(SQLite3* database);
void testUpdate(SQLite3* database);
void testDelete(SQLite3* database);

JNIEXPORT jstring JNICALL Java_com_link_storage_jni_JniClient_addStr
  (JNIEnv * env, jobject object, jstring file_name ) {

	SQLite3* database = new SQLite3();

	if( !database->open(DB_FILE, NULL) ) {
		log(LOG_ERROR, TAG , "open database failed");
	}

	try {
		database->begin();
		//testInsert();
		testUpdate(database);
		testSelect(database);
		//	testDelete();
		//	testSelect();
		database->commit();
	} catch (SQLException &e) {
		log(LOG_DEBUG, TAG , e.what());
		try {
			database->rollback();
		} catch (SQLException &ex) {
			log(LOG_DEBUG, TAG , ex.what());
		}
	}


	database->close();
	return env->NewStringUTF("SUCCESS");
}

JNIEXPORT jint JNICALL Java_com_link_storage_jni_JniClient_add
  (JNIEnv *env, jobject object, jint a, jint b) {

	return 1;
}

void testInsert(SQLite3* database) {


//	std::string sql = "create table Test (pid integer primary key , \
//			name varchar(20), score float )";
//	if(!database.create(sql)) {
//		log(LOG_ERROR, TAG , database.errMsg().c_str() );
//		char buff[20];
//		sprintf(buff, "errno = %d\n" , database.errCode() );
//		log(LOG_DEBUG, TAG , buff);
//	}

	Insert* insert = QueryFactory::newInsert();

	SqlValue* value = new SqlValue(7);
	SqlValue* name = new SqlValue("danyang");
	SqlValue* score = new SqlValue(5.6);
	insert->into("Test")
			->col("pid" , value)
			->col("name" , name)
			->col("score" , score );
	log(LOG_DEBUG, TAG , insert->__toString().c_str());
	Statement* stmt =
			database->prepare( insert->__toString() );
	stmt->bindValues( insert->getBindValues() );

	stmt->execute();

	stmt->close();
}

void testSelect(SQLite3* database) {
	std::string msg = "";

	Select* select = QueryFactory::newSelect();
	Statement* stmt;
	SqlValue* value = new SqlValue();
	value->setInteger(1);

	select->from("Test")
			->col("pid")
			->col("name")
			->col("score")
			->where("pid > ?" , value);

	log(LOG_DEBUG, TAG , select->__toString().c_str());
	stmt = database->prepare( select->__toString() );
	stmt->bindValues( select->getBindValues() );
	stmt->execute();

	SQL_VALUES_VEC* result = (SQL_VALUES_VEC*)stmt->getResult();
	SQL_VALUES_VEC::iterator iter;
	FOREACH( *result, iter ) {
		SQL_V_VEC::iterator s_iter;
		FOREACH( *(*iter), s_iter ) {
			switch( (*s_iter)->type ) {
				case INTEGER:{
					char buff[50];
					sprintf(buff, "Select %s = %d\n" , (*s_iter)->name.c_str(), (*s_iter)->data.integer );
					log(LOG_DEBUG, TAG , buff);
					break;
				}
				case TEXT:{
					char buff[50];
					sprintf(buff, "Select %s = %s\n" , (*s_iter)->name.c_str(),(*s_iter)->data.s );
					log(LOG_DEBUG, TAG , buff);
					break;
				}
				case DOUBLE:{
					char buff[50];
					sprintf(buff, "Select %s = %lf\n" , (*s_iter)->name.c_str(),(*s_iter)->data.doub );
					log(LOG_DEBUG, TAG , buff);
					break;
				}
			}

		}
	}

	stmt->close();
}

void testUpdate(SQLite3* database) {
	Update* update = QueryFactory::newUpdate();
	Statement* stmt;
	SqlValue* value = new SqlValue(5);
	SqlValue* new_value = new SqlValue(8);
	update->table("Test")
			->col("pid" , new_value)
			->where("pid = ?" , value);
	log(LOG_DEBUG, TAG , update->__toString().c_str());
	stmt = database->prepare( update->__toString() );
	stmt->bindValues( update->getBindValues() );

	stmt->execute();
	stmt->close();
}

void testDelete(SQLite3* database) {

	Delete* del = QueryFactory::newDelete();
	SqlValue* value = new SqlValue(10);

	del->from("Test")
		->where("p_id = ?" , value);

	log(LOG_DEBUG, TAG , del->__toString().c_str());
	Statement* stmt =
			database->prepare( del->__toString() );
	stmt->bindValues( del->getBindValues() );

	stmt->execute();

	stmt->close();
}

#ifdef __cplusplus
}
#endif
