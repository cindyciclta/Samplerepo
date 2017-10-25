#include <iostream>
#include <stdexcept>
#include "exception.h"

using namespace std;
If_noLine::If_noLine(int _line,int _toline)
  {
    line = _line;
    toline=_toline;
  }

std::string If_noLine::what()
  {
  	std:: string message = "Error in Line ";
    message = message + std::to_string(line) +": IF jump to non-existent line "
    + std::to_string(toline)+".";
    return message;

  }

Division_zero::Division_zero(int _line)
  {
    line = _line;
  }

std::string Division_zero::what()
  {
  	std:: string message = "Error in Line ";
    message = message + std::to_string(line) +": Division by 0.";
    return message;
  }

Gosub_noline::Gosub_noline(int _line,int _toline)
  {
    line = _line;
    toline=_toline;
  }

std::string Gosub_noline::what()
  {
  	std:: string message = "Error in Line ";
    message = message + std::to_string(line) +": GOSUB to non-existent line "
    + std::to_string(toline)+".";
    return message;
  }

Gosub_noReturn::Gosub_noReturn(int _line)
  {
    line = _line;
  }

std::string Gosub_noReturn::what()
  {
    std:: string message = "Error in Line ";
    message = message + std::to_string(line) +": No matching GOSUB for RETURN.";
    return message;
	}

Goto_noline::Goto_noline(int _line,int _toline)
  {
    line = _line;
    toline=_toline;
  }

std::string Goto_noline::what()
  {
  	std:: string message = "Error in Line ";
    message = message + std::to_string(line) +": GOTO to non-existent line "
    + std::to_string(toline)+".";
    return message;
  }