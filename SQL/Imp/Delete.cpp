#include "Delete.h"

using namespace Database;

Delete* Delete::from(const std::string& table) {
	this->_table = table;
	return this;
}

Delete* Delete::where(const std::string& cond, SqlValue* value) {
	this->addWhere( AND, cond, value);
	return this;
}

Delete* Delete::orWhere(const std::string& cond, SqlValue* value) {
	this->addWhere( OR, cond, value);
	return this;
}

std::string Delete::build() {
	return DELETE
			+ this->buildFlags()
			+ this->buildFrom()
			+ this->buildWhere()
			+ this->buildOrderBy()
			+ this->buildLimit()
			+ this->buildReturning();
}

std::string Delete::buildFrom() {
	std::string clause = FROM;
	clause += INDENT;
	clause += this->_table;
	return clause;
}
