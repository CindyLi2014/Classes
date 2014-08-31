//Cindy Li

#include "LongInt.h"

LongInt LongInt::operator+ (const LongInt& v1)
{
	if(v1.valsStk.isEmpty())
		return *this;
	else if(this->valsStk.isEmpty())
		return v1;

	LongInt rV;
	StackLi<short> valsStk1 = v1.valsStk;
	StackLi<short> valsStk2 = this->valsStk;
	short carry = 0;
	while(!valsStk1.isEmpty() || !valsStk2.isEmpty())
	{
		short sV1 = valsStk1.isEmpty() ? 0: valsStk1.topAndPop();
		short sV2 = valsStk2.isEmpty() ? 0: valsStk2.topAndPop();
		short sum = sV1+sV2+carry;
		carry = sum > 9;
		short sV = carry ? (sum-10) : sum;
		rV.valsList.insert(sV, rV.valsList.zeroth());
	}
	
	if(carry)
		rV.valsList.insert(1, rV.valsList.zeroth());

	return rV;
}

ostream& operator<<(ostream&out, const LongInt& vOut)
{
  ListItr<short> it = vOut.valsList.first();
	while(!it.isPastEnd())
	{
		out << it.retrieve();
		it.advance();
	}

	return out; 
}

istream& operator >> (istream& in, LongInt& v)
{
	char c = in.get();
	while(c != '\n')
	{
		if(c<'0' || c>'9')
		{
			cout << "Input has Nondigit!" << endl;
			throw NOTDIGIT;
		}
		v.valsStk.push(c-'0');
		c = in.get();
	}

	return in; 
}
