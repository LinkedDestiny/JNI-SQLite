#ifndef _ABSTRACTDMLQUERY_H_
#define _ABSTRACTDMLQUERY_H_

#include "Common.h"
#include "AbstractQuery.h"

namespace Database
{

class AbstractDmlQuery : virtual public AbstractQuery
{
public:
	SQL_V_VEC* getBindValues();

	AbstractDmlQuery* addCol(const std::string& col,
			SqlValue* value);

	AbstractDmlQuery* addReturing(const SQL_S_VEC& cols);

protected:
	std::string buildReturning();

protected:

	SQL_S_VEC col_values;

	SQL_S_VEC returing;
};

}

#endif
