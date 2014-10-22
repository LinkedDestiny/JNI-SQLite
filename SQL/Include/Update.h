#ifndef _UPDATE_H_
#define _UPDATE_H_

#include "Common.h"
#include "AbstractDmlQuery.h"
#include "UpdateInterface.h"

namespace Database
{

class Update : virtual public AbstractDmlQuery,
				virtual public UpdateInterface
{
public:
	Update* table( const std::string& table );

	Update* where(const std::string& cond,
			SqlValue* value );
	Update* orWhere(const std::string& cond,
			SqlValue* value );

	Update* col(const std::string& col, SqlValue* value);

	Update* cols(const SQL_V_MAP& cols);

protected:
	std::string build();
	std::string buildTable();
	std::string buildValuesForUpdate();

protected:
	std::string _table;
};

}


#endif
