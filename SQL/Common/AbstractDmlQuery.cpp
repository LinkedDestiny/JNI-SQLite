#include "AbstractDmlQuery.h"

using namespace Database;

SQL_V_VEC* AbstractDmlQuery::getBindValues() {
	SQL_V_VEC* bind_values = AbstractQuery::getBindValues();
	int i = bind_values->size();
	SQL_V_VEC::iterator iter;
	FOREACH( this->bind_where , iter ) {
		bind_values->push_back( *iter );
	}
	return bind_values;
}

AbstractDmlQuery* AbstractDmlQuery::addCol(const std::string& col,
		SqlValue* value) {
	// TODO quotes col
	this->col_values.push_back(col);
	this->bind_values.push_back( value );
	return this;
}

AbstractDmlQuery* AbstractDmlQuery::addReturing(const SQL_S_VEC& cols) {
	SQL_S_VEC::const_iterator iter;
	FOREACH(cols, iter) {
		this->returing.push_back( *iter );
	}
	return this;
}

std::string AbstractDmlQuery::buildReturning(){
	if( this->returing.size() == 0 ) {
		return "";
	}
	return RETURING + indentCsv( this->returing );
}
