#include "Insert.h"

using namespace Database;

Insert* Insert::into(const std::string& table) {
	this->table = table;
	return this;
}

Insert* Insert::col(const std::string& col, SqlValue* value) {
	this->addCol(col, value);
	return this;
}

Insert* Insert::cols(const SQL_V_MAP& cols) {
	SQL_V_MAP::const_iterator iter;
	FOREACH(cols, iter) {
		this->col( iter->first, iter->second );
	}
	return this;
}

std::string Insert::build() {
	return INSERT
				+ this->buildFlags()
	            + this->buildInto()
	            + this->buildValuesForInsert()
	            + this->buildReturning();
}

std::string Insert::buildInto() {
	//TODO quotes table
	return INTO + this->table;
}

std::string Insert::buildValuesForInsert() {
	string clause = "(\n	";
	string placeholder = "";

	SQL_S_VEC::const_iterator iter;
	FOREACH(this->col_values, iter) {
		if(iter == this->col_values.begin()) {
			clause += (*iter);
			placeholder += "\n	?";
			continue;
		}
		clause += INDENTCVS;
		clause += (*iter);
		placeholder += PLACEHOLDER;
	}
	return clause + VALUES + placeholder + "\n)";
}


