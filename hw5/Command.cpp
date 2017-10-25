
#include "Command.h"
#include <iostream>
#include <stack>
#include <map>
#include "In.h"
#include <stdexcept>
#include "exception.h"
using namespace std;

IfStatement::IfStatement(BooleanExpression *a, int Linenumber, int toline)
{
	_a=a;
	line=Linenumber;
	_toline=toline;
}
IfStatement::~IfStatement()
{
	delete _a;
}
void IfStatement::print (std::ostream & o) const
{
	o<<line;
	o<< " IF ";
  	_a->print (o);
  	o<<" THEN ";
  	o<<"<";
  	o<<_toline;
  	o<<">";
}


Let::Let(ArithmeticExpression *a, ArithmeticExpression *b, int toline)
{
	_a=a;
	_b=b;

	
	line=toline;
}

Let::~Let()
{
	delete _a;
	delete _b;
}
void Let::print (std::ostream & o) const
{
	o<<line;
	o<< " LET ";
  	_a->print (o);
  	o<< " ";
  	_b->print(o);
}



Goto::Goto(int line, int toline)
{
	_line = line;
	_toline = toline;
}
Goto::~Goto()
{
	
}
void Goto::print (std::ostream & o) const
{
	o<<_line;
	o<< " GOTO ";
	o<< "<";
  	o<< _toline;
  	o<< ">";
}

Gosub::Gosub(int line, int toline)
{
	_line = line;
	_toline = toline;
}
Gosub::~Gosub()
{
	
}
void Gosub::print (std::ostream & o) const
{
	o<<_line;
	o<< " GOSUB ";
	o<< "<";
  	o<< _toline;
  	o<< ">";
}

Return::Return(int line)
{
	_line = line;
}
Return::~Return()
{
	
}
void Return::print (std::ostream & o) const
{
	o<< _line;
	o<< " ";
	o<< "RETURN";
}


End::End(int line)
{
	_line = line;
}
End::~End()
{
	
}
void End::print (std::ostream & o) const
{
	o<< _line;
	o<< " ";
	o<< "END";
}

Print::Print(int line, ArithmeticExpression* ae)
{
	_line = line;
	_ae=ae;
}
Print::~Print()
{	
	delete _ae;
	
}
void Print::print (std::ostream & o) const
{
	o<< _line;
	o<< " PRINT ";
	_ae->print(o);
}
std::string IfStatement::getName() const
{
	return name;
}
std::string Let::getName() const
{
	return name;
}
std::string Goto::getName() const
{
	return name;
}
std::string Gosub::getName() const
{
	return name;
}
std::string Return::getName() const
{
	return name;
}
std::string End::getName() const
{
	return name;
}
std::string Print::getName() const
{
	return name;
}

int IfStatement::execute(std::map<int,Command*>:: iterator &it,std::map<int,Command*> *commandMap,
	std::map<string, int>* varMap,
std::map<std::string,std::map<int,int>> *arrMap,
std::stack<int> *jumpfrom ) const
{
	if(_a->get()) //if true
	{
		// cout<< "IT WORKS"<<endl;
		if((*commandMap).find(_toline) != (*commandMap).end())
		{

			return _toline;
		}
		else
		{
			throw(If_noLine(line,_toline));
		}
	}
	else
	{
		return it->first;
	}
	
	// return it->first;
}
int Let::execute(std::map<int,Command*>:: iterator &it,std::map<int,Command*> *commandMap,
	std::map<string, int>* varMap,
std::map<std::string,std::map<int,int>> *arrMap,
std::stack<int> *jumpfrom ) const
{

	if(_a->getType()=="Variable")
	{
		int temp = _b->get();
		std::string var = _a->getName();
		 // cout<< " line is "<< line << " and i'm putting " << temp<<endl;

		if(_b->getType()=="Addition")
		{
			(*varMap)[var]=temp;

		}
		else if (_b->getType()=="Constant")
		{
			(*varMap)[var]=temp;
		}
		else if(_b->getType()== "Multiply")
		{
			(*varMap)[var]=temp;
		}
		else if(_b->getType()== "Divide")
		{
			(*varMap)[var]=temp;
		}
		else if(_b->getType()== "Subtract")
		{
			(*varMap)[var]=temp;
		}
		else if(_b->getType()=="Variable")
		{
			(*varMap)[var]=temp;
		}
		else if(_b->getType()=="Array")
		{
			string namearr = _b->getName();
			(*varMap)[var]=(*arrMap)[namearr][temp];
		}

		
	}
    
    
	else if(_a->getType()=="Array")
	{
		int temp =_a->get();//temp is position in arr
		std::string name = _a->getName();
		int valueB=_b->get();
		if(_b->getType()=="Addition")
		{
			(*arrMap)[name][temp]=valueB;

		}
		 if (_b->getType()=="Constant")
		{
			(*arrMap)[name][temp]=valueB;

		}
		else if(_b->getType()== "Multiply")
		{
			(*arrMap)[name][temp]=valueB;

		}
		else if(_b->getType()== "Divide")
		{
			(*arrMap)[name][temp]=valueB;

		}
		else if(_b->getType()== "Subtract")
		{
			(*arrMap)[name][temp]=valueB;

		}
		else if(_b->getType()=="Variable")
		{

			(*arrMap)[name][temp]=valueB;
		}
		else if(_b->getType()=="Array")
		{
			// cout<< "pos of xe inside is "<<temp<<endl;
			string namearr = _b->getName();
			(*arrMap)[name][temp]=(*arrMap)[namearr][valueB];
			
		}
		

	}
	return it->first;
}

int Goto::execute(std::map<int,Command*>:: iterator &it,std::map<int,Command*> *commandMap,
	std::map<string, int>* varMap,
	std::map<std::string,std::map<int,int>> *arrMap,
	std::stack<int> *jumpfrom) const
{
	if((*commandMap).find(_toline) != (*commandMap).end())
	{

		return _toline;
	}
	else
	{
		throw(Goto_noline(_line, _toline));
	}
}
int Gosub::execute(std::map<int,Command*>:: iterator &it,std::map<int,Command*> *commandMap,
	std::map<string, int>* varMap,
std::map<std::string,std::map<int,int>> *arrMap,
std::stack<int> *jumpfrom ) const
{
	// cout<<" jumpfrom is "<< it->first<<endl<<endl;
	jumpfrom->push(it->first);
	if((*commandMap).find(_toline) != (*commandMap).end())
		{

			return _toline;
		}
		else
		{
			throw(Gosub_noline(_line,_toline));
		}
	
}
int Return::execute(std::map<int,Command*>:: iterator &it,std::map<int,Command*> *commandMap,
	std::map<string, int>* varMap,
std::map<std::string,std::map<int,int>> *arrMap,
std::stack<int> *jumpfrom ) const
{ 

	if(!jumpfrom->empty())
	{
	
		int temp = jumpfrom->top();
		
		jumpfrom->pop();
		
		it = commandMap->find(temp);
		
		it++;
		if((*commandMap).find(it->first) != (*commandMap).end())
		{ 
			// cout<<"here?"<<endl;
			
			return it->first;//will turn 120
		}
		else
		{
			throw(Gosub_noReturn(_line));
		}
		//return it->first;
	}
	else
		{
			throw(Gosub_noReturn(_line));
		}



		
		

}
int End::execute(std::map<int,Command*>:: iterator &it,std::map<int,Command*> *commandMap,
	std::map<string, int>* varMap,
std::map<std::string,std::map<int,int>> *arrMap,
std::stack<int> *jumpfrom ) const
{	
	return it->first;
}
int Print::execute(std::map<int,Command*>:: iterator &it,std::map<int,Command*> *commandMap,
	std::map<string, int>* varMap,
std::map<std::string,std::map<int,int>> *arrMap,
std::stack<int> *jumpfrom ) const
{
	if(_ae->getType()=="Constant")
	{
		cout<< _ae->get()<<endl;
	}
	else if (_ae->getType()=="Array")
	{
		string name = _ae->getName();
		int temp = _ae->get();
		cout<<(*arrMap)[name][temp]<<endl;
	}
	else if(_ae->getType() == "Variable")
	{
		string x = _ae->getName();
		cout<< (*varMap)[x]<<endl;
	}
	else 
	{
		// cout<< "went in here?"<<endl;
		cout<< _ae->get()<<endl;
	}
	
	return it->first;
}