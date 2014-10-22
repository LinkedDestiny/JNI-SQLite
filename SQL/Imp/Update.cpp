#include "Update.h"

using namespace Database;

Update* Update::table(const std::string& table) {
	this->_table = table;
	return this;
}

Update* Update::where(const std::string& cond, SqlValue* value) {
	this->addWhere( AND, cond, value);
	return this;
}

Update* Update::orWhere(const std::string& cond, SqlValue* value) {
	this->addWhere( OR, cond, value);
	return this;
}

Update* Update::col(const std::string& col, SqlValue* value) {
	this->addCol(col, value);
	return this;
}

Update* Update::cols(const SQL_V_MAP& cols) {
	SQL_V_MAP::const_iterator iter;
	FOREACH(cols, iter) {
		this->col( iter->first, iter->second );
	}
	return this;
}

std::string Update::build(){
	return UPDATE
			+ this->buildFlags()
			+ this->buildTable()
			+ this->buildValuesForUpdate()
			+ this->buildWhere()
			+ this->buildOrderBy()
			+ this->buildLimit()
			+ this->buildReturning();
}

std::string Update::buildTable() {
	return INDENT + this->_table;
}

std::string Update::buildValuesForUpdate() {
	string clause = UPDATE_SET;
	SQL_S_VEC::const_iterator iter;
	FOREACH(this->col_values, iter) {
		if(iter == this->col_values.begin()) {
			clause += (*iter);
			clause += " = ?";
			continue;
		}
		clause += INDENTCVS;
		clause += (*iter);
		clause += " = ?";
	}
	return clause;
}
