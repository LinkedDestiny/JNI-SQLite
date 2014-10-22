#ifndef _DELETE_H_
#define _DELETE_H_

#include "Common.h"
#include "AbstractDmlQuery.h"
#include "DeleteInterface.h"

namespace Database
{

class Delete : virtual public AbstractDmlQuery,
				virtual public DeleteInterface
{
public:
	Delete* from(const std::string& table);

	Delete* where(const std::string& cond,
			SqlValue* value );
	Delete* orWhere(const std::string& cond,
			SqlValue* value );

protected:
	std::string build();
	std::string buildFrom();

protected:
	std::string _table;
};

}


#endif
