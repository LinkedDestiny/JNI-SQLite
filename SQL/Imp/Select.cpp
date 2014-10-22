#include "Select.h"
using namespace Database;

Select::Select() {
	this->for_update = false;
	this->from_key = -1;
	this->paging = 10;
}

std::string Select::__toString() {
	std::string unions = "";
	if( this->unions.size() > 0 ) {
		unions = implode( SQL_EOF , this->unions );
	}
	return unions + this->build();
}

Select* Select::setPaging(int paging) {
	this->paging = paging;
	return this;
}

int Select::getPaging() {
	return this->paging;
}

SQL_V_VEC* Select::getBindValues() {
	bind_values.clear();
	SQL_V_VEC::const_iterator iter;

	FOREACH(this->bind_where, iter) {
		bind_values.push_back(*iter);
	}

	FOREACH(this->bind_having, iter) {
		bind_values.push_back(*iter);
	}
	return &bind_values;
}

Select* Select::forUpdate(bool enable) {
	this->for_update = enable;
	return this;
}

Select* Select::distinct(bool enable) {
	this->setFlag( DISTINCT , enable);
	return this;
}

Select* Select::cols(const SQL_S_VEC& cols) {
	SQL_S_VEC::const_iterator iter;
	FOREACH(cols, iter) {
		this->_cols.push_back( *iter );
	}
	return this;
}

Select* Select::col(const std::string& col) {
	this->_cols.push_back( col );
	return this;
}

Select* Select::from(const std::string& spec) {
	// TODO quotes the table name
	SQL_S_VEC arr;
	arr.push_back(spec);
	this->_from.push_back( arr );
	from_key ++;
	return this;
}

Select* Select::fromSubSelect(const std::string& spec,
		const std::string& name){
	string clause = "(";
	clause += INDENT;
	clause += spec ;
	clause += "\n	) AS " ;
	clause += name;
	// TODO quotes the table name
	SQL_S_VEC arr(1);
	arr.push_back(clause);
	this->_from.push_back( arr );
	from_key ++;
	return this;
}

Select* Select::join(const std::string& join,
		const std::string& spec,const std::string& cond) {
	if( this->_from.size() == 0 ) {
		throw SQLException("Cannot join() without from() first.");
	}
	string clause = join + JOIN;
	// TODO quotes the name
	clause += spec;
	clause += this->fixJoinCondition(cond);
	this->_from[from_key].push_back( clause );
	return this;
}

Select* Select::joinSubSelect(const std::string& join,
		const std::string& spec, const std::string& name,
		const std::string& cond) {
	if( this->_from.size() == 0 ) {
		throw SQLException("Cannot join() without from() first.");
	}
	string clause = join + JOIN;
	clause += "(";
	// TODO quotes the name
	clause += spec;
	clause += ") AS ";
	// TODO quotes the name
	clause += name;
	clause += this->fixJoinCondition(cond);
	this->_from[from_key].push_back( clause );
	return this;
}

Select* Select::groupBy(const SQL_S_VEC& spec) {
	SQL_S_VEC::const_iterator iter;
	FOREACH(spec, iter) {
		this->group_by.push_back(*iter);
	}
	return this;
}

Select* Select::having(const std::string& cond, SqlValue* value) {
	if(this->_having.size() == 0 ) {
		this->_having.push_back( cond );
	} else {
		this->_having.push_back( AND + cond );
	}

	this->bind_having.push_back( value );
	return this;
}

Select* Select::orHaving(const std::string& cond, SqlValue* value) {
	if(this->_having.size() == 0 ) {
		this->_having.push_back( cond );
	} else {
		this->_having.push_back( OR + cond );
	}

	this->bind_having.push_back( value );
	return this;
}

Select* Select::Union() {
	string clause = this->build() + "\n UNION";

	this->reset();
	this->unions.push_back( clause );
	return this;
}

Select* Select::unionAll() {
	string clause = this->build() + "\n UNION ALL";

	this->reset();
	this->unions.push_back( clause );
	return this;
}

Select* Select::page(int page) {
	this->_limit 	= -1;
	this->_offset 	= -1;

	if( page > 0 ) {
		this->_limit = paging;
		this->_offset = paging * (page - 1);
	}
}

Select* Select::where(const std::string& cond, SqlValue* value) {
	this->addWhere( AND, cond, value);
	return this;
}

Select* Select::orWhere(const std::string& cond, SqlValue* value) {
	this->addWhere( OR, cond, value);
	return this;
}

Select* Select::limit(int limit) {
	this->_limit = limit;
	return this;
}

Select* Select::offset(int offset) {
	this->_offset = offset;
	return this;
}

Select* Select::orderBy(const SQL_S_VEC& spec) {
	this->addOrderBy(spec);
	return this;
}

void Select::reset() {
	this->resetFlags();
	this->_cols.clear();
	this->_from.clear();

	this->_where.clear();
	this->group_by.clear();
	this->_having.clear();
	this->order_by.clear();

	this->from_key 	= -1;
	this->_limit 	= -1;
	this->_offset 	= -1;
	this->for_update = false;
}

std::string Select::fixJoinCondition(std::string cond) {
	if(cond.empty()) {
		return "";
	}
	// TODO quotes the name

	if(cond.find_first_of(ON)) {
		return cond;
	}
	if(cond.find_first_of(USING)) {
		return cond;
	}
	return ON + cond;
}

std::string Select::build() {
	return SELECT
			+ this->buildFlags()
			+ this->buildCols()
			+ this->buildFrom()
			+ this->buildWhere()
			+ this->buildGroupBy()
			+ this->buildHaving()
			+ this->buildOrderBy()
			+ this->buildLimit()
			+ this->buildForUpdate();
}

std::string Select::buildCols() {
	if( this->_cols.size() == 0 ) {
		throw SQLException("No columns in the SELECT.");
	}

	return indentCsv( this->_cols );
}

std::string Select::buildFrom() {
	if( this->_from.size() == 0 ) {
		throw SQLException("There is no from field! You must set a 'from table'");
	}
	SQL_S_VEC refs;
	SQL_ARRAY_VEC::iterator iter;
	FOREACH(this->_from, iter) {
		refs.push_back( implode(SQL_EOF, *iter ) );
	}
	return FROM + indentCsv(refs);
}

std::string Select::buildGroupBy() {
	if( this->group_by.size() == 0 ) {
		return "";
	}

	return GROUP_BY + indentCsv( this->group_by );
}

std::string Select::buildHaving() {
	if( this->_having.size() == 0 ) {
		return "";
	}

	return HAVING + indentCsv( this->_having );
}

std::string Select::buildForUpdate() {
	if( !this->for_update) {
		return "";
	}

	return FOR_UPDATE;
}

