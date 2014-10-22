#ifndef _SQLEXCEPTION_H_
#define _SQLEXCEPTION_H_

using namespace std;

#include "string.h"
#include "Exception.h"

namespace Database
{

class SQLException : public exception
{
public:
	SQLException() {
		_msg = new char[18];
		strcpy(_msg, DEFAULT_MSG );
		_errno = DEFAULT_ERRNO;
	}

	SQLException(const char* msg) {
		this->_msg = new char[strlen(msg)];
		strcpy(this->_msg, msg);
		_errno = DEFAULT_ERRNO;
	}

	SQLException(const char* msg, int errno) {
		_msg = new char[strlen(msg)];
		strcpy(_msg, msg);
		_errno = errno;
	}

	SQLException(const SQLException& e) {
		this->_msg = new char[strlen(e._msg)];
		strcpy(this->_msg, e._msg);
		_errno = e._errno;
	}

	const char* what() const throw() {
		return _msg;
	}

	int errno(){ return _errno; }

private:
	char* _msg;
	int _errno;
};

}

#endif
