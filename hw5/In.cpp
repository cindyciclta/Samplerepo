#include <iostream>
#include "In.h"
#include "ArithmeticExpression.h"
#include "Command.h"
#include <map>
#include <string>
using namespace std;

In::In(std::map<int,Command*> *line, std::map<std::string, int>* varMap,
	std::map<std::string,std::map<int,int>> *arrMap,std::stack<int>* jumpfrom)
{
	_line=line;
	_varMap=varMap;
	_arrMap=arrMap;
	_jumpfrom=jumpfrom;
	
}
In::~In(){

};
void In::executeProgram()
{

	std::map<int,Command*>::iterator (it)=_line->begin();

int currLine;
while(it != _line->end())
{
	// cout<< "what is the command: "<<it->second->getName()<<endl;
	programCounter=it->first;
	// cout << "programcrounter is "<<programCounter<<endl;
    currLine=executeCurrentLine(programCounter,it);

    if(currLine == programCounter && (it->second->getName() != "End")
    	&& (it->second->getName() != "Return"))
    {

    	it++;
    	
    }
    else if((currLine == programCounter && (it->second->getName() != "End")
    	&& it->second->getName() == "Return"))
    {
    	// cout<< "went into return"<<endl;
    	if(_jumpfrom->empty())
    	{

    	it++;
    	}
    	else 
    	{
    		currLine=executeCurrentLine(it->first,it);
    	}
    }
    
 
    else if (currLine != programCounter 
    	&& (it->second->getName() != "End"))
    {
    	// it=currLine;
    	it = ((_line)->find(currLine));
    	// cout<<"SKIPPED line to " <<it->first<<endl;
    	
    }
    else if((currLine == programCounter )
    	&& (it->second->getName() == "End"))
    {
    	break;
    }
    // cout << "programcrounter after is "<<programCounter<<endl;

}
   

}

int In::executeCurrentLine(int num,std::map<int,Command*>:: iterator &it)
{
	
	int temp=(*_line)[num]->execute(it,_line,_varMap,_arrMap,_jumpfrom);
	return temp;
}