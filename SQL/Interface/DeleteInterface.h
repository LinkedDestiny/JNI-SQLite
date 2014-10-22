#ifndef _DELETEINTERFACE_H_
#define _DELETEINTERFACE_H_

#include "Common.h"
#include "Interface.h"

namespace Database
{

class DeleteInterface : virtual public WhereInterface
{
public:
	virtual DeleteInterface* from(const std::string& from)=0;
};

}


#endif
