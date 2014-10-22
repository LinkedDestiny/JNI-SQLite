#ifndef _ABSTRACTQUERY_H_
#define _ABSTRACTQUERY_H_

#include "Common.h"

namespace Database
{

class AbstractQuery
{
public:
	AbstractQuery();

	string __toString(){ return build(); }

	SQL_V_VEC* getBindValues() {
		return &bind_values;
	}

protected:

	// Where
	AbstractQuery* addWhere( const std::string& andor,
			const std::string& cond, SqlValue* value);
	std::string buildWhere();

	// Order
	AbstractQuery* addOrderBy(const SQL_S_VEC& spec);
	std::string buildOrderBy();

	// Flags
	void setFlag(const std::string& flag, bool enable);
	void resetFlags();
	std::string buildFlags();

	std::string buildLimit();

	virtual std::string build()=0;

protected:
	/**
	 * Data to be bound to the query.
	 */
	SQL_V_VEC bind_values;

	/**
	 * The list of WHERE conditions.
	 */
	SQL_S_VEC _where;

	/**
	 * Bind these values to the WHERE conditions.
	 */
	SQL_V_VEC bind_where;

	/**
	 * ORDER BY these columns
	 */
	SQL_S_VEC order_by;

	SQL_S_VEC flags;

	int _limit;
	int _offset;


};


}

#endif
