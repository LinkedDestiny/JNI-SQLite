#include "Common.h"
using namespace Database;

void SqlValue::setInteger(int i) {
	type = INTEGER;
	data.integer = i;
}

void SqlValue::setCharacter(char c) {
	type = CHAR;
	data.character = c;
}

void SqlValue::setText(const char* s) {
	type = TEXT;
	int len = strlen(s);
	data.s = new char[len];
	strcpy(data.s , s);
}

void SqlValue::setDouble(double d) {
	type = DOUBLE;
	data.doub = d;
}

std::string Database::indent(const SQL_S_VEC& list) {
	string s = EMPTY;
	SQL_S_VEC::const_iterator iter;
	FOREACH( list, iter ) {
		s += ( INDENT + (*iter) );
	}
	return s;
}

std::string Database::indentCsv(const SQL_S_VEC& list) {
	string s = INDENT;
	SQL_S_VEC::const_iterator iter;
	FOREACH( list, iter ) {

		if(iter == list.begin()) {
			s += (*iter);
			continue;
		}
		s += ( INDENTCVS + *iter );
	}
	return s;
}

std::string Database::implode(const std::string& delimiter, const SQL_S_VEC& list) {
	string s = EMPTY;
	SQL_S_VEC::const_iterator iter;
	FOREACH( list, iter ) {

		if(iter == list.begin()) {
			s += (*iter);
			continue;
		}
		s += ( delimiter + *iter );
	}
	return s;
}
