#ifndef _INSERT_H_
#define _INSERT_H_

#include "Common.h"
#include "InsertInterface.h"
#include "AbstractDmlQuery.h"

namespace Database
{

class Insert : 	virtual public AbstractDmlQuery,
				virtual public InsertInterface
{
public:

	Insert* into(const std::string& table);

	Insert* col(const std::string& col, SqlValue* value);

	Insert* cols(const SQL_V_MAP& cols);
protected:
	std::string build();

	std::string buildInto();

	std::string buildValuesForInsert();


protected:
	/**
	 * The table to insert into
	 */
	std::string table;
};

}

#endif
