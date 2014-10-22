#ifndef _LIMITINTERFACE_H_
#define _LIMITINTERFACE_H_

#include "Common.h"

namespace Database
{

/**
 * An interface for LIMIT clauses.
 *
 */
class LimitInterface
{
public:
	virtual LimitInterface* limit( int limit ) = 0;
};

/**
 *  An interface for LIMIT...OFFSET clauses.
 *
 */
class LimitOffsetInterface : virtual public LimitInterface
{
public:
	virtual LimitOffsetInterface* offset(int offset) = 0;
};

/**
 * An interface for WHERE clauses.
 */
class WhereInterface
{
public:
	virtual WhereInterface* where(const std::string& cond, SqlValue* value)=0;
	virtual WhereInterface* orWhere(const std::string& cond, SqlValue* value)=0;
};

/**
 * An interface for ORDER BY clauses.
 */
class OrderByInterface
{
public:
	virtual OrderByInterface* orderBy(const SQL_S_VEC& spec)=0;
};

/**
 * An interface for setting column values.
 */
class ValuesInterface
{
public:
	virtual ValuesInterface* col(const std::string& col, SqlValue* value = NULL)=0;
	virtual ValuesInterface* cols(const SQL_V_MAP& cols)=0;
};



}

#endif
