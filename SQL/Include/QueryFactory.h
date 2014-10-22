#ifndef _QUERYFACTORY_H_
#define _QUERYFACTORY_H_

#include "Common.h"
#include "Select.h"
#include "Insert.h"
#include "Update.h"
#include "Delete.h"


namespace Database
{

class QueryFactory
{
public:
	static Select* newSelect() {
		return new Select();
	}
	static Insert* newInsert() {
		return new Insert();
	}
	static Update* newUpdate() {
		return new Update();
	}
	static Delete* newDelete() {
		return new Delete();
	}
};

}

#endif
