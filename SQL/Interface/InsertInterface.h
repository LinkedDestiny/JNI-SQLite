#ifndef _INSERTINTERFACE_H_
#define _INSERTINTERFACE_H_

#include "Common.h"
#include "Interface.h"

namespace Database
{

class InsertInterface : virtual public ValuesInterface
{
public:
	virtual InsertInterface* into(const std::string& table)=0;
};

}

#endif
