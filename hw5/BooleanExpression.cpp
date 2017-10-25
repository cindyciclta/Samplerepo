#include <iostream>
#include "BooleanExpression.h"
#include <string>
#include <stack>
#include <map>
using namespace std;
Equals:: Equals (ArithmeticExpression *ae1, ArithmeticExpression *ae2,
	std::map<std::string,std::map<int,int>> *arr)
{
	_ae1=ae1;
	_ae2=ae2;
	_arr=arr;
}
Equals::~Equals()
{
	delete _ae1;
	delete _ae2;
}
void Equals::print (std::ostream & o) const
{
	o << "[";
  _ae1->print (o);
  o << " = ";
  _ae2->print (o);
  o << "]";
}

Lessthan:: Lessthan (ArithmeticExpression *ae1, ArithmeticExpression *ae2,
	std::map<std::string,std::map<int,int>> *arr)
{
	_ae1=ae1;
	_ae2=ae2;
	_arr=arr;
}
Lessthan::~Lessthan()
{
	delete _ae1;
	delete _ae2;
}
void Lessthan::print (std::ostream & o) const
{
	o << "[";
  _ae1->print (o);
  o << " < ";
  _ae2->print (o);
  o << "]";
}

Morethan:: Morethan (ArithmeticExpression *ae1, ArithmeticExpression *ae2,
	std::map<std::string,std::map<int,int>> *arr)
{
	_ae1=ae1;
	_ae2=ae2;
	_arr=arr;
}
Morethan::~Morethan()
{
	delete _ae1;
	delete _ae2;
}
void Morethan::print (std::ostream & o) const
{
	o << "[";
  _ae1->print (o);
  o << " < ";
  _ae2->print (o);
  o << "]";
}

bool Equals::get() const
{
	int left,right;

	if (_ae1->getType()=="Array")
	{
		string temp = _ae1->getName();
		int temp2 = _ae1->get();	
		left=(*_arr)[temp][temp2];
	}
	else
	{
		left = _ae1->get();
	}

	if(_ae2->getType()=="Array")
	{
		string temp = _ae2->getName();
		int temp2 = _ae2->get();	
		right=(*_arr)[temp][temp2];
	}
	else
	{
		right=_ae2->get();
	}



	if(left==right)
	{
		return true;
	}
	return false;
}
bool Lessthan::get() const
{
	int left,right;

	if (_ae1->getType()=="Array")
	{
		string temp = _ae1->getName();
		int temp2 = _ae1->get();	
		left=(*_arr)[temp][temp2];

	}
	else
	{
		left = _ae1->get();
		
	}

	if(_ae2->getType()=="Array")
	{
		string temp = _ae2->getName();
		int temp2 = _ae2->get();	
		right=(*_arr)[temp][temp2];
	}
	else
	{
		right=_ae2->get();
		
	}



	if(left<right)
	{
		return true;
	}
	return false;
}
bool Morethan::get() const
{
	// cout<< _ae1->getName() << " is "<< _ae1->get()<<endl;
	// cout<< _ae2->getName() << " is "<< _ae2->get()<<endl;
	int left,right;

	if (_ae2->getType()=="Array")
	{
		string temp = _ae2->getName();
		int temp2 = _ae2->get();	
		left=(*_arr)[temp][temp2];
	}
	else
	{
		left = _ae2->get();
	}

	if(_ae1->getType()=="Array")
	{
		string temp = _ae1->getName();
		int temp2 = _ae1->get();	
		right=(*_arr)[temp][temp2];
	}
	else
	{
		right=_ae1->get();
	}



	if(right<left)
	{
		return true;
	}
	return false;
}
