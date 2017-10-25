#ifndef IN_H
#define IN_H
#include <iostream>
#include "ArithmeticExpression.h"
#include "Command.h"
#include <stack>
// 

class In
{
	public:
		In(std::map<int,Command*> * line, 
			std::map<std::string, int>* varMap,
			std::map<std::string,std::map<int,int>> *arrMap,
			std::stack<int>* jumpfrom);
		~In();
		// void assign(ArithmeticExpression* ae);
		void executeProgram();

		int executeCurrentLine(int num,std::map<int,Command*>:: iterator &it);


	private:
		std::map<int, Command*> *_line;
		std::map<std::string,std::map<int,int>> *_arrMap;
		std::map<std::string, int> *_varMap;
		int programCounter;
		std::stack<int>* _jumpfrom;



};
#endif