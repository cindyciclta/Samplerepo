#include <iostream>
#include <stdexcept>

class If_noLine: public std:: exception
{
private: 
  // PokemonType _type;
public:
  If_noLine(int &_line);
  std::string what();
private:
	int line;

};