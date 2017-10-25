#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <iostream>
#include <stdexcept>

class If_noLine: public std:: exception
{

public:
  If_noLine(int _line, int _toline );
  std::string what();
private:
	int line;
	int toline;

};
class Division_zero: public std:: exception
{

public:
  Division_zero(int _line);
  ~Division_zero(){};
  std::string what();
private:
	int line;

};

class Gosub_noline: public std:: exception
{

public:
  Gosub_noline(int _line,int _toline);
  std::string what();
  ~Gosub_noline(){};
private:
	int line;
	int toline;

};

class Gosub_noReturn: public std:: exception
{

public:
  Gosub_noReturn(int _line);
  std::string what();
  ~Gosub_noReturn(){};
private:
	int line;

};
class Goto_noline: public std:: exception
{

public:
  Goto_noline(int _line,int _toline);
  std::string what();
  ~Goto_noline(){};
private:
	int line;
	int toline;

};
#endif