
#ifndef COMMAND_H
#define COMMAND_H
#include "BooleanExpression.h"
#include <iostream>
#include <stack>
#include <map>
#include <string>

class Command {
  // abstract class for a BASIC Command

 public:
  virtual void print (std::ostream & o) const = 0;
  virtual ~Command(){};
  virtual int execute( std::map<int,Command*>:: iterator &it,
  	std::map<int,Command*> *commandMap,std::map<std::string, int>* varMap, 
  std::map<std::string,std::map<int,int>> *arrMap, std::stack<int> *jumpfrom) const = 0;
  virtual std::string getName() const=0;
  virtual int getToLine() const=0;
  // pure virtual print function. Don't implement!

};

class IfStatement : public Command
{
public: 
	IfStatement(BooleanExpression *a, int Linenumber,int toline);//lINE NUMBER REDO?
	virtual void print (std::ostream & o) const;
	~IfStatement();
	virtual int execute(std::map<int,Command*>:: iterator &it,
		std::map<int,Command*> *commandMap,
		std::map<std::string, int>* varMap, 
		std::map<std::string,std::map<int,int>> *arrMap,
		std::stack<int> *jumpfrom) const ;
	 virtual std::string getName() const;
	 virtual int getToLine() const {return _toline;};
private:
	BooleanExpression *_a; 
	int line;
	int _toline; 
	std::string name = "IfStatement";
};


class Let : public Command
{
public: 
	Let(ArithmeticExpression *a, ArithmeticExpression *b, int toline);//lINE NUMBER REDO?
	virtual void print (std::ostream & o) const;
	~Let();
	virtual int execute(std::map<int,Command*>:: iterator &it,
		std::map<int,Command*> *commandMap,
	std::map<std::string, int>* varMap, 
	std::map<std::string,std::map<int,int>> *arrMap,
	std::stack<int> *jumpfrom) const;
	virtual std::string getName() const;
	virtual int getToLine() const {return 0;};
private:
	ArithmeticExpression *_a, *_b; 
	int line;
	std::string _var;
	int _value1;
	int _value2;
	std::string name = "Let";

};



class Goto : public Command
{
public: 
	Goto(int line, int toline);//lINE NUMBER REDO?
	virtual void print (std::ostream & o) const;
	~Goto();
	virtual int execute(std::map<int,Command*>:: iterator &it,
		std::map<int,Command*> *commandMap,
		std::map<std::string, int>* varMap, 
		std::map<std::string,std::map<int,int>> *arrMap,
		std::stack<int> *jumpfrom) const;
	virtual std::string getName() const ;
	virtual int getToLine() const{return _toline;};
private:
	int _line;
	int _toline;
	std::string name = "Goto";

};


class Gosub : public Command
{
public: 
	Gosub(int line, int toline);//lINE NUMBER REDO?
	virtual void print (std::ostream & o) const;
	~Gosub();
	virtual int execute(std::map<int,Command*>:: iterator &it,
		std::map<int,Command*> *commandMap,
		std::map<std::string, int>* varMap,
	 std::map<std::string,std::map<int,int>> *arrMap,
	 std::stack<int> *jumpfrom) const;
	virtual std::string getName() const;
	virtual int getToLine() const {return _toline;};
private:
	int _line;
	int _toline;
	std::string name = "Gosub";

};


class Return : public Command
{
public:
	Return(int line);
	~Return();
	virtual void print (std::ostream & o) const;
	virtual int execute(std::map<int,Command*>:: iterator &it,
		std::map<int,Command*> *commandMap,
	std::map<std::string, int>* varMap, 
	std::map<std::string,std::map<int,int>> *arrMap,
	std::stack<int> *jumpfrom) const;
	virtual std::string getName() const;
	virtual int getToLine() const {return 0;};
private:
	int _line;
	std::string name = "Return";


};

class End : public Command
{
public:
	End(int line);
	~End();
	virtual void print (std::ostream & o) const;
	virtual int execute(std::map<int,Command*>:: iterator &it,
		std::map<int,Command*> *commandMap,
	std::map<std::string, int>* varMap, 
	std::map<std::string,std::map<int,int>> *arrMap,
	std::stack<int> *jumpfrom) const;
	virtual std::string getName() const;
	virtual int getToLine() const {return 0;};
private:
	int _line;
	std::string name = "End";


};
class Print : public Command
{
public:
	Print(int line, ArithmeticExpression* ae);
	~Print();
	virtual void print (std::ostream & o) const;
	virtual int execute(std::map<int,Command*>:: iterator &it,
		std::map<int,Command*> *commandMap,
	std::map<std::string, int>* varMap,
	std::map<std::string,std::map<int,int>> *arrMap,
	std::stack<int> *jumpfrom ) const;
	virtual std::string getName() const;
	virtual int getToLine() const {return 0;};
private:
	int _line;
	ArithmeticExpression* _ae;
	std::string name = "Print";

};






// add below other classes that are needed
#endif