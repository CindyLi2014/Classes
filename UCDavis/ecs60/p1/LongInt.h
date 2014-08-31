//Cindy Li

#ifndef _LONGINT_H
#define _LONGINT_H

#include <iostream>
#include "StackLi.h"
#include "LinkedList.h"

using namespace std;

const int NOTDIGIT = 9999;

class LongInt
{
public:

//Overloaded Operators
  LongInt operator+ (const LongInt&);
  friend istream& operator>>(istream&, LongInt& );
  friend ostream& operator<<(ostream&, const LongInt&);

private:
	StackLi<short> valsStk;
	List<short> valsList;//Queue is good choice, too
};

#endif //_LONGINT_H