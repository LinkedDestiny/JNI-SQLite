#ifndef _SELECT_H_
#define _SELECT_H_

#include "Common.h"
#include "SelectInterface.h"
#include "AbstractQuery.h"

namespace Database
{

class Select : 	virtual public AbstractQuery,
				virtual public SelectInterface
{
public:
	Select();

	std::string __toString();

	/**
	 * Sets the number of rows per page.
	 */
	Select* setPaging(int paging);

	/**
	 * Gets the number of rows per page.
	 */
	int getPaging();

	/**
	 * Gets the values to bind to placeholders.
	 */
	SQL_V_VEC* getBindValues();

	/**
	 * Makes the select FOR UPDATE (or not).
	 */
	Select* forUpdate(bool enable);

	/**
	 *  Makes the select DISTINCT (or not).
	 */
	Select* distinct(bool enable);

	/**
	 * Adds columns to the query.
	 */
	Select* cols(const SQL_S_VEC& cols);

	Select* col(const std::string& col);

	Select* from(const std::string& spec);

	Select* fromSubSelect(const std::string& spec,
			const std::string& name);

	Select* join(const std::string& join,
			const std::string& spec,const std::string& cond);

	// TODO inner , left, natural , right

	Select* joinSubSelect(const std::string& join,
				const std::string& spec, const std::string& name,
				const std::string& cond);

	Select* groupBy(const SQL_S_VEC& spec);

	Select* having(const std::string& cond, SqlValue* value);

	Select* orHaving(const std::string& cond, SqlValue* value);

	Select* Union();

	Select* unionAll();

	/**
	 * Sets the limit and count by page number.
	 */
	Select* page(int page);

	std::string build();

	Select* where(const std::string& cond, SqlValue* value);
	Select* orWhere(const std::string& cond, SqlValue* value);

	Select* limit(int limit);
	Select* offset(int offset);

	Select* orderBy(const SQL_S_VEC& spec);

protected:
	std::string fixJoinCondition(std::string cond);

	void reset();

	std::string buildCols();
	std::string buildFrom();
	std::string buildGroupBy();
	std::string buildHaving();
	std::string buildForUpdate();

protected:
	/**
	 * an array of union SELECT statements
	 */
	SQL_S_VEC 	unions;

	bool 		for_update;

	/**
	 * The columns to be selected.
	 */
	SQL_S_VEC 	_cols;

	/**
	 * Select from there tables; Includes JOIN clauses.
	 */
	SQL_ARRAY_VEC 	_from;

	int 		from_key;

	/**
	 * GROUP BY these columns.
	 */
	SQL_S_VEC	group_by;

	/**
	 * The list of Having conditions.
	 */
	SQL_S_VEC	_having;

	SQL_V_VEC	bind_having;

	int 		paging;
};


}

#endif

