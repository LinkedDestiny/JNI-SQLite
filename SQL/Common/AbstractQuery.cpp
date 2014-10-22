#include "AbstractQuery.h"
using namespace Database;

AbstractQuery::AbstractQuery() {
	_limit = _offset = -1;
}

AbstractQuery* AbstractQuery::addWhere(const std::string& andor,
		const std::string& cond , SqlValue* value) {

	if( this->_where.size() == 0 ) {
		this->_where.push_back( cond );
	} else {
		this->_where.push_back( andor +cond );
	}

	this->bind_where.push_back( value );
}

std::string AbstractQuery::buildWhere() {
	if( this->_where.size() == 0 ) {
		return EMPTY;
	}
	return WHERE + indent(this->_where);
}

AbstractQuery* AbstractQuery::addOrderBy(const SQL_S_VEC& lists ) {
	SQL_S_VEC::const_iterator iter;
	FOREACH( lists, iter ) {
		this->order_by.push_back( *iter );
	}
	return this;
}

std::string AbstractQuery::buildOrderBy() {
	if( this->order_by.size() == 0 ) {
		return EMPTY;
	}
	return EOF + "ORDER BY" + indentCsv(this->order_by);
}

void AbstractQuery::setFlag(const std::string& flag, bool enable) {
	if( enable && this ) {
		this->flags.push_back( flag );
	} else {
		SQL_S_VEC::iterator iter = this->flags.begin();
		FOREACH(this->flags, iter) {
			string tmp = (*iter);
			if( tmp == flag ) {
				this->flags.erase( iter );
				break;
			}
		}
	}
}

void AbstractQuery::resetFlags() {
	this->flags.clear();
}

std::string AbstractQuery::buildFlags() {
	if( this->flags.size() == 0 ) {
		return EMPTY;
	}
}

std::string AbstractQuery::buildLimit() {
	std::string clause = "";
	if( _limit >= 0 ) {
		clause += SQL_EOF;
		clause += "LIMIT ";
		clause += _limit;
	}
	if( _offset >= 0 ) {
		clause += SQL_EOF;
		clause += "OFFSET ";
		clause += _offset;
	}
	return clause;
}


