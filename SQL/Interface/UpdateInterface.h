#ifndef _UPDATEINTERFACE_H_
#define _UPDATEINTERFACE_H_

#include "Common.h"
#include "Interface.h"

namespace Database
{

class UpdateInterface : virtual public WhereInterface,
						virtual public ValuesInterface
{
public:
	virtual UpdateInterface* table(const std::string& table)=0;
};

}


#endif
