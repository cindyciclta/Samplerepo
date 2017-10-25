#ifndef BOOLEANEXPRESSION_H

#define BOOLEANEXPRESSION_H

#include "ArithmeticExpression.h"
#include <iostream>
#include <stack>
#include <map>

// This file is for classes that have to do with Boolean expressions

class BooleanExpression {
  // abstract class for a Boolean expression

 public:
  virtual void print (std::ostream & o) const = 0;
  virtual ~BooleanExpression(){};
  virtual bool get() const=0;


  // pure virtual print function. Don't implement!
};

class Equals : public BooleanExpression 
{
public:
	Equals (ArithmeticExpression *ae1, ArithmeticExpression *ae2,
		std::map<std::string,std::map<int,int>> *arr);
	~Equals();
	virtual void print (std::ostream & o) const;
	virtual bool get() const;

private:
	std::map<std::string,std::map<int,int>> *_arr;
	ArithmeticExpression *_ae1, *_ae2;
};

class Lessthan : public BooleanExpression
{
public:
	Lessthan (ArithmeticExpression *ae1, ArithmeticExpression *ae2,
		std::map<std::string,std::map<int,int>> *arr);
	~Lessthan();
	virtual void print (std::ostream & o) const;
	virtual bool get() const;
private:
	ArithmeticExpression *_ae1, *_ae2;
	std::map<std::string,std::map<int,int>> *_arr;
};

class Morethan : public BooleanExpression
{
public:
	Morethan (ArithmeticExpression *ae1, ArithmeticExpression *ae2, 
		std::map<std::string,std::map<int,int>> *arr);
	~Morethan();
	virtual void print (std::ostream & o) const;
	virtual bool get() const;
private:
	ArithmeticExpression *_ae1, *_ae2;
	std::map<std::string,std::map<int,int>> *_arr;
};

#endif