 #ifndef ARITHMETICEXPRESSION_H
 #define ARITHMETICEXPRESSION_H
#include <iostream>
#include <stack>
#include <map>
#include <string>
// This file is for classes that have to do with arithmetic expressions

class ArithmeticExpression {
  // abstract class for an arithmetic expression

public:
  virtual void print (std::ostream & o) const = 0; 
  virtual ~ArithmeticExpression(){};
  // // pure virtual print function. Don't implement!
  // virtual void set(ArithmeticExpression* ae)=0;
  virtual int get() const =0;
  virtual std::string getType() const =0;
   virtual std::string getName() const =0;
// protected:
  // std::map<std::string,int> *VarMap;
};

/* if you prefer to have an abstract "BinaryArithmeticExpresion"
   class or something like that, feel free to insert it and
   have Addition inherit from that instead. */




class Addition : public ArithmeticExpression {
 public:
  Addition (ArithmeticExpression *ae1, ArithmeticExpression *ae2, int _line,
    std::map<std::string,std::map<int,int>> *arr);
  ~Addition ();
  // virtual void set(ArithmeticExpression* ae);
  virtual int get() const;
  virtual void print (std::ostream & o) const;
  virtual std::string getType() const;
  virtual std::string getName() const {return _var;};
  // because the class is not abstract, we must implement print
  
 private:
  ArithmeticExpression *_ae1, *_ae2; // the left and right term
  std::string name;
  std::string _var="";
  int line;
  std::map<std::string,std::map<int,int>> *_arr;
};

class Constant : public ArithmeticExpression
{
public:
  Constant(int x, int _line);
  ~Constant();
  virtual void print (std::ostream & o) const;
  virtual int get() const ;
  virtual std::string getType() const;
  virtual std::string getName() const;
private:
  int _x;
  std::string name;
  std::string _var="";
  int line;
};

class Variable : public ArithmeticExpression
{ 
public:

  Variable(std::string var,std::map<std::string,int> *varMap, int _line);
  // Variable(std::string var);
  ~Variable();
  virtual int get() const ;
  virtual void print(std::ostream & o) const;
  // void set(ArithmeticExpression* ae);
  virtual std::string getType() const;
  virtual std::string getName() const {return _var;};
protected:
  std::map<std::string ,int> *_varMap;

private:
  std::string _var;
  std::string name;
  // ArithmeticExpression *_ae;
  int line;

  int value;
  
};


class Divide : public ArithmeticExpression {

public:
  Divide (ArithmeticExpression *ae1, ArithmeticExpression *ae2, int _line,
    std::map<std::string,std::map<int,int>> *arr);
  ~Divide();

virtual void print (std::ostream & o) const;
virtual int get() const ;
virtual std::string getType() const;
virtual std::string getName() const {return _var;};
  
 private:
  ArithmeticExpression *_ae1, *_ae2; // the left and right term
  int left,right;
  std::string name;
  int line;
  std::string _var="";
  std::map<std::string,std::map<int,int>> *_arr;
};

class Multiply : public ArithmeticExpression {
public:
  Multiply (ArithmeticExpression *ae1, ArithmeticExpression *ae2, int _line,
    std::map<std::string,std::map<int,int>> *arr);
  ~Multiply();
virtual int get() const ;
virtual void print (std::ostream & o) const;
virtual std::string getType() const;
virtual std::string getName() const {return _var;};


  
 private:
  ArithmeticExpression *_ae1, *_ae2; // the left and right term
  std::string name;
  std::string _var="";
  int line;
  std::map<std::string,std::map<int,int>> *_arr;
};

class Subtract : public ArithmeticExpression {
public:
  Subtract (ArithmeticExpression *ae1, ArithmeticExpression *ae2,int _line,
    std::map<std::string,std::map<int,int>> *arr);
   ~Subtract ();
virtual int get() const ;

  virtual void print (std::ostream & o) const;
  virtual std::string getType() const;
  virtual std::string getName() const {return _var;};
  
  
 private:
  ArithmeticExpression *_ae1, *_ae2; // the left and right term
  std::string name;
  std::string _var="";
  int line;
  std::map<std::string,std::map<int,int>> *_arr;
};

class Array : public ArithmeticExpression {
public:
  Array (std::string name, ArithmeticExpression *ae1,
    std::map<std::string,std::map<int,int>> *arr, int _line);
  ~Array ();

  virtual void print (std::ostream & o) const;
  virtual int get() const ;
  virtual std::string getType() const;
  virtual std::string getName() const;
protected:
  std::map<std::string,std::map<int,int>> *_arr;
 private:
  ArithmeticExpression *_ae1;
  std::string _name;
  std::string objectname;
  int line;

};



// add below other classes that are needed
#endif