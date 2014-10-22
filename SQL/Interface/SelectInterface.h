#ifndef _SELECTINTERFACE_H_
#define _SELECTINTERFACE_H_

#include "Common.h"
#include "Interface.h"

namespace Database
{

class SelectInterface : virtual public WhereInterface,
						virtual public OrderByInterface,
						virtual public LimitOffsetInterface
{
public:
	/**
	 * Sets the number of rows per page.
	 */
	virtual SelectInterface* setPaging(int paging)=0;

	virtual SelectInterface* page(int page)=0;
	/**
	 * Gets the number of rows per page.
	 */
	virtual int getPaging()=0;
	/**
	 * Makes the select FOR UPDATE (or not).
	 */
	virtual SelectInterface* forUpdate(bool enable = true)=0;
	/**
	 * Makes the select DISTINCT (or not).
	 */
	virtual SelectInterface* distinct(bool enable = true)=0;

	/**
	 * Adds columns to the query.
	 */
	virtual SelectInterface* cols(const SQL_S_VEC& cols)=0;

	/**
	 * Adds a FROM element to the query; quotes the table name automatically.
	 */
	virtual SelectInterface* from(const std::string& spec)=0;

	/**
	 * Adds an sub-select to the query.
	 */
	virtual SelectInterface* fromSubSelect(const std::string& spec,
			const std::string& name)=0;

	/**
	 * Adds a JOIN table and columns to the query.
	 */
	virtual SelectInterface* join(const std::string& join,
			const std::string& spec,const std::string& cond)=0;

	/**
	 * Adds a JOIN to an aliased subselect and columns to the query.
	 */
	virtual SelectInterface* joinSubSelect(const std::string& join,
			const std::string& spec, const std::string& name,
			const std::string& cond)=0;

	/**
	 * Adds grouping to the query.
	 */
	virtual SelectInterface* groupBy(const SQL_S_VEC& spec)=0;

	/**
	 * Adds a HAVING condition to the query by AND;
	 */
	virtual SelectInterface* having(const std::string& cond, SqlValue* value)=0;

	/**
	 * Adds a HAVING condition to the query by OR;
	 */
	virtual SelectInterface* orHaving(const std::string& cond, SqlValue* value)=0;

	/**
	 * Takes the current select properties and retains them, then sets
     * UNION for the next set of properties.
	 */
	virtual SelectInterface* Union()=0;

	/**
	 * Takes the current select properties and retains them, then sets
     * UNION ALL for the next set of properties.
	 */
	virtual SelectInterface* unionAll()=0;
};

}


#endif
