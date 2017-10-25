#include "ArithmeticExpression.h"
#include <iostream>
#include <string>
#include <stack>
#include <map>
#include "exception.h"
// #include <execept>
using namespace std;

Addition::Addition (ArithmeticExpression *ae1, ArithmeticExpression *ae2,int _line,
  std::map<std::string,std::map<int,int>> *arr)
{
  _ae1 = ae1;
  _ae2 = ae2;
  name = "Addition";
  line = _line;
  _arr=arr;
}


Addition::~Addition ()
{
  delete _ae1;
  delete _ae2;
}
void Addition::print (std::ostream & o) const
{
  o << "(";
  _ae1->print (o);
  o << " + ";
  _ae2->print (o);
  o << ")";
}
Constant::Constant(int x,int _line)
{
	_x = x;
  name = "Constant";
  _var = std::to_string(_x);
  line=_line;
}

Constant::~Constant(){

}
 void Constant::print (std::ostream & o) const
 {
 	o << _x;
 }
Variable::Variable(std::string var, std::map<std::string,int> *varMap,int _line)
 // Variable::Variable(std::string var)
{
	_var = var; 
  value=0;
  _varMap = varMap;
  name = "Variable";
  _varMap->insert(make_pair(_var,0));
  line = _line;

}

Variable::~Variable(){
	

}
void Variable::print(std::ostream & o) const
{
	o << _var;
}

Multiply:: Multiply (ArithmeticExpression *ae1, ArithmeticExpression *ae2, int _line,
  std::map<std::string,std::map<int,int>> *arr)
{
	 _ae1 = ae1;
  	_ae2 = ae2;
    name = "Multiply";
    line=_line;
    _arr=arr;
}
void Multiply::print (std::ostream & o) const
{
	o << "(";
  _ae1->print (o);
  o << " * ";
  _ae2->print (o);
  o << ")";
}

Multiply:: ~Multiply ()
{
	delete _ae1;
  delete _ae2;
}
Divide:: Divide (ArithmeticExpression *ae1, ArithmeticExpression *ae2,int _line,
  std::map<std::string,std::map<int,int>> *arr)
{
	_ae1 = ae1;
  	_ae2 = ae2;
    name = "Divide";
    line=_line;
    _arr=arr;
}
void Divide::print (std::ostream & o) const
{
	o << "(";
  _ae1->print (o);
  o << " / ";
  _ae2->print (o);
  o << ")";
}

Divide:: ~Divide ()
{
	delete _ae1;
  delete _ae2;
}
Subtract:: Subtract (ArithmeticExpression *ae1, ArithmeticExpression *ae2,int _line,
  std::map<std::string,std::map<int,int>> *arr)
{
	_ae1 = ae1;
  _ae2 = ae2;
  name = "Subtract";
  line=_line;
  _arr=arr;
}
void Subtract::print (std::ostream & o) const
{
	o << "(";
  _ae1->print (o);
  o << " - ";
  _ae2->print (o);
  o << ")";
}

Subtract:: ~Subtract ()
{

	delete _ae1;
  delete _ae2;
}

Array:: Array (std::string name, 
  ArithmeticExpression *ae1,std::map<std::string,
  std::map<int,int>> *arr,int _line)
{
	_name = name;
	_ae1 = ae1;
  objectname= "Array";
  _arr=arr;
  line=_line;
}
void Array::print (std::ostream & o) const
{	o<<_name;
	o << "[";
  _ae1->print (o);
  o << "]";
	
}

Array:: ~Array ()
{
	delete _ae1;
}

int Constant::get() const
{
  return _x;
}
int Variable::get() const
{
  // try{
  
  if(_varMap->find(_var)!= _varMap->end())
  {
    // cout<< "VAR GET IS "<< (*_varMap)[_var]<<endl;

    return (*_varMap)[_var];
  }

  return value;
}
int Multiply::get() const
{
  
  int left;
  int right;

  if (_ae1->getType()=="Array")
  {
    string temp = _ae1->getName();
    int temp2 = _ae1->get();  
    left=(*_arr)[temp][temp2];

  }
  else if(_ae1->getType()=="Constant")
  {
    left=_ae1->get();
  }
  else if(_ae1->getType()=="Variable")
  {
    left=_ae1->get();
  }
  else
  {
    left=_ae1->get();
  }

  if (_ae2->getType()=="Array")
  {
    string temp = _ae2->getName();
    int temp2 = _ae2->get();  
    right=(*_arr)[temp][temp2];

  }
  else if(_ae2->getType()=="Constant")
  {
    right=_ae2->get();
  }
  else if(_ae2->getType()=="Variable")
  {
    right=_ae2->get();
  }
  else
  {
    right=_ae2->get();
  }


  return (left*right);
}
int Divide::get() const
{
  
  int left;
  int right;

  if (_ae1->getType()=="Array")
  {
    string temp = _ae1->getName();
    int temp2 = _ae1->get();  
    left=(*_arr)[temp][temp2];

  }
  else if(_ae1->getType()=="Constant")
  {
    left=_ae1->get();
  }
  else if(_ae1->getType()=="Variable")
  {
    left=_ae1->get();
  }
  else
  {
    left=_ae1->get();
  }

  if (_ae2->getType()=="Array")
  {
    string temp = _ae2->getName();
    int temp2 = _ae2->get();  
    right=(*_arr)[temp][temp2];

  }
  else if(_ae2->getType()=="Constant")
  {
    right=_ae2->get();
  }
  else if(_ae2->getType()=="Variable")
  {
    right=_ae2->get();
  }
  else
  {
    right=_ae2->get();
  }

  if(right==0)
  {
    throw (Division_zero(line));
  }
  else
  {


  return (left/right);
  }
}
int Subtract::get() const
{


  int left;
  int right;

  if (_ae1->getType()=="Array")
  {
    string temp = _ae1->getName();
    int temp2 = _ae1->get();  
    left=(*_arr)[temp][temp2];

  }
  else if(_ae1->getType()=="Constant")
  {
    left=_ae1->get();
  }
  else if(_ae1->getType()=="Variable")
  {
    left=_ae1->get();
  }
  else
  {
    left=_ae1->get();
  }

  if (_ae2->getType()=="Array")
  {
    string temp = _ae2->getName();
    int temp2 = _ae2->get();  
    right=(*_arr)[temp][temp2];

  }
  else if(_ae2->getType()=="Constant")
  {
    right=_ae2->get();
  }
  else if(_ae2->getType()=="Variable")
  {
    right=_ae2->get();
  }
  else
  {
    right=_ae2->get();
  }


  return (left-right);
}
int Addition::get() const
{
  
  int left;
  int right;
  if (_ae1->getType()=="Array")
  {
    string temp = _ae1->getName();
    int temp2 = _ae1->get();  
    left=(*_arr)[temp][temp2];


  }
  else if(_ae1->getType()=="Constant")
  {
    left=_ae1->get();
  }
  else if(_ae1->getType()=="Variable")
  {
    left=_ae1->get();
  }
  else
  {
    left=_ae1->get();
  }

  if (_ae2->getType()=="Array")
  {
     string temp = _ae2->getName();
    int temp2 = _ae2->get();  
    right=(*_arr)[temp][temp2];

  }
  else if(_ae2->getType()=="Constant")
  {
    right=_ae2->get();
  }
  else if(_ae2->getType()=="Variable")
  {
    right=_ae2->get();
  }
  else
  {
    right=_ae2->get();
  }
 
  return (left+right);
}
int Array::get() const
{
int insidepos;

   
  if(_ae1->getType()=="Array")
  {
    insidepos = _ae1->get();
    std::string insidearrname = _ae1->getName();
   
    
    return (*_arr)[insidearrname][insidepos];
  }
  else
  {
    return _ae1->get();//get value from constant,var,or any other ones.
  }

 
}
std::string Variable::getType() const
{
  return name;
}
std::string Constant::getType() const
{
  return name;
}
std::string Addition::getType() const
{
  return name;
}
std::string Subtract::getType() const
{
  return name;
}
std::string Multiply::getType() const
{
  return name;
}
std::string Array::getType() const
{
  return objectname;
}
std::string Divide::getType() const
{
  return name;
}

std::string Array::getName() const
{

  return _name;
}
std::string Constant::getName() const
{
  // _var = std::to_string(_x);
  return _var;
}




