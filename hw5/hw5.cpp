 #include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "In.h"
#include "ArithmeticExpression.h"
#include "BooleanExpression.h"
#include "Command.h"
#include <string>
#include <stdlib.h>
#include <cctype>
#include <algorithm>
#include <stack>
#include <map>
#include <string>
#include <stdexcept>
#include "exception.h"


using namespace std;



ArithmeticExpression* parse(string x, int& i, map<string,int> *_store,
  map<string,map<int,int>> *_arrStore, int _line)
{
  ArithmeticExpression* ae1=NULL;
  ArithmeticExpression* curr=NULL;
  ArithmeticExpression* curr2=NULL;
  char save_operator='0'; 
  bool found_array=false;
  string name="";
  map<string, int> *store = _store;
  map<string,map<int,int>> *arrStore = _arrStore;
 // cout << x <<endl;
int namecount=0;
int total_let=0;


 for(int j=i;j<(signed)x.length();j++)
  { //this is to find if there is an array

    
    if(x[j]=='[')
    {
      found_array = true;
      break;
    }
  }

  if(isalpha(x[i]))
  {
        namecount=i;
          while(isalpha(x[namecount])&& total_let <=8)
          //count how many letters I have
          {
            
            namecount++;
            total_let++;
            
          }
          name=x.substr(i,total_let);
          // cout << "NAME IS " << name <<endl;

  }


    while((unsigned)i <= (unsigned)x.length())
    {
      // cout << x [i]<<endl;
    //
       if(x[i]=='(')
      {
        // cout << "RECURSION "<<endl;
        curr = parse(x,++i, store,arrStore,_line);//my x
      }
      else if(found_array==true && isalpha(x[i]) && x[i+total_let]=='[')
      {
        
          name=x.substr(i,total_let);
          // cout << "NAME INSIDE ARRAY PARSER IS "<< name <<endl;
          i=i+(total_let+1);
          curr = parse(x,i,store,arrStore,_line);

        ae1 = new Array(name,curr,arrStore,_line);
    
        return ae1;
      }

      else if((x[i]=='+' || x[i]=='-'|| x[i]=='/' || x[i]=='*'))
      { 
        //cout << "Found ae is "<< found_AE <<endl;
        if((ae1 != NULL || curr != NULL || curr2 !=NULL) && save_operator =='0')
        {
          save_operator=x[i];
           // cout << "Went into save_operator" <<endl;
          curr2 = parse(x,++i,store,arrStore,_line);
        
         }
         else  //its a negative number!
         {
            // cout <<"WENT INTO INTEGER"<<endl;
              int j=(i+1);
              int num_digits=0;
               while(isdigit(x[j])&& num_digits <=8)//count how many numbers I have
              {
                j++;
                num_digits++;
              }
              int integer =-stoi( x.substr((1+i),num_digits));
              // cout <<  "INTEGER IS: " <<integer <<endl;
              ae1 = new Constant(integer,_line);
             
               i=i+(num_digits);
               return ae1;
          
         }
      }

      else if(isalpha(x[i]) )//base case
      {
        string temp = x.substr(i,total_let);
        ae1 = new Variable(temp,store,_line);


        
        i=i+(total_let-1);

        return ae1;
       
      }

      else if (isdigit(x[i]))//base case
      {
        int j=i;
        int num_digits=0;
         while(isdigit(x[j])&& num_digits <=8)//count how many numbers I have
        {
          j++;
          num_digits++;
        }

        int integer =stoi( x.substr(i,num_digits));
        ae1 = new Constant(integer,_line);
        i=i+(num_digits-1);
        return ae1;
       
      }


      else if(x[i]==')') //found ending bracket
       {
          break;
          

          // return ae1;

       }

       i++;

       // return ae1;
     }



          if(save_operator == '+' && (ae1 != NULL || curr != NULL || curr2 !=NULL))
            {
            // cout << "went into add" <<endl;
            ae1 = new Addition(curr,curr2,_line,arrStore);
            
            save_operator ='0';
          

          }
          else if(save_operator == '*' && (ae1 != NULL || curr != NULL || curr2 !=NULL))
          {
            
            ae1 = new Multiply(curr,curr2,_line,arrStore);
           
            save_operator='0';
          }
          else if(save_operator == '/' && (ae1 != NULL || curr != NULL || curr2 !=NULL))
          {
           
            ae1 = new Divide(curr,curr2,_line,arrStore);
          
            save_operator='0';
          }
          else if(save_operator == '-' && (ae1 != NULL || curr != NULL || curr2 !=NULL))
          {
            
            ae1 = new Subtract(curr,curr2,_line,arrStore);
           
            save_operator='0';
          }

        return ae1;


}

BooleanExpression* boolparse(string x, int &i, map<string, int> *_store,
    map<string,map<int,int>> *_arrStore, int _line)
{

  ArithmeticExpression* ae1=NULL;
  ArithmeticExpression* ae2=NULL;
  BooleanExpression* total=NULL;
  char save_operator='0'; 
  bool left=false; //this is to find if its right or left
  bool right = false; //b.c I need two separate AE
  // bool isthereae = false;
  map<string, int> *store=_store;
  map<string,map<int,int>> *arrStore=_arrStore;

  while((unsigned)i <= ((unsigned)x.length()-1))
  {
    
    
    if (x[i]=='<' || x[i] == '>' || x[i] == '=')
    {
      save_operator=x[i];

    
    }
    else if(x[i]=='(' && left == false)
    {
      // cout << "went to left"<<endl;
      ae1 = parse(x,i,store, arrStore,_line);
      left = true;
       // isthereae = true;
    }
    
    else if(x[i]=='(' && right ==false)
    {
      
      ae2 = parse(x,i,store, arrStore,_line);
      right = true;
       // isthereae = true;

    }
    else if (x[i]=='-' && left == false)
    {
        int j=i+1;
        int num_digits=0;

         while(isdigit(x[j])&& num_digits <=8)//count how many numbers I have
        {
          j++;
          num_digits++;
        }
        num_digits++;
        string integer =x.substr(i,num_digits);
        int pos=0;
        ae1 = parse(integer,pos,store, arrStore,_line);
        i=i+pos;
        left = true;
         // isthereae =true;
    }


    else if(isalpha(x[i]) && left == false)
    {
        
        int j=i;
        int num_letters=0;
        while(isalpha(x[j])&& num_letters <=8)//count how many letters I have
        {
          
          j++;
          num_letters++;
          
        }
        
        if(x[i+num_letters]=='[')
        {
          int a=0;
          while(x[j+num_letters+a] != ']')
          {
            a++;
          }
          string temp = x.substr(i,num_letters+a+2);
          int pos=0;
          ae1 = parse(temp,pos,store,arrStore,_line);
          i=i+(pos);
        }
        else{

          string temp = x.substr(i,num_letters);
          int pos=0;
          ae1 = parse(temp,pos,store, arrStore,_line);
          i=i+pos;
        }

        
     
        left = true;
         // isthereae = true;
        
    }
      else if (isdigit(x[i]) && left == false)//base case
      {
        // cout << "went in left"<<endl;
        int j=i;
        int num_digits=0;

         while(isdigit(x[j])&& num_digits <=8)//count how many numbers I have
        {
          j++;
          num_digits++;
        }

        string integer =x.substr(i,x.length());
        int pos=0;
        ae1 = parse(integer,pos,store,arrStore,_line);
        i=i+(pos);
        left = true;
         // isthereae = true;
       
      }
      else if (x[i]=='-' && right == false)
        {//negative nums
                int j=i+1;
            int num_digits=0;

             while(isdigit(x[j])&& num_digits <=8)//count how many numbers I have
            {
              j++;
              num_digits++;
            }
            num_digits++;
            string integer =x.substr(i,num_digits);
            int pos=0;
            ae2 = parse(integer,pos,store,arrStore,_line);
            i=i+pos;
            right = true;
            // isthereae = true;
        }
    else if(isalpha(x[i]) && right == false)
    {
        int j=i;
        int num_letters=0;

        while(isalpha(x[j])&& num_letters <=8)//count how many letters I have
        {
          
          j++;
          num_letters++;
          
        }
        if(x[i+num_letters]=='[')
        {
          int a=0;
          while(x[j+num_letters+a] != ']')
          {
            a++;
          }
          string temp = x.substr(i,num_letters+a+2);

          int pos=0;
          ae2 = parse(temp,pos,store,arrStore,_line);
          i=i+(pos);
        }
        else
        {
          string temp = x.substr(i,num_letters);
        // cout << "num_letters RIGHT IS "<< num_letters<<endl;
          int pos=0;
          ae2 = parse(temp,pos,store,arrStore,_line);
          i=i+pos;
        }
        
        right = true;
        // isthereae = true;
    }

      else if (isdigit(x[i]) && right == false)//base case
      {
        // cout << "went in right"<<endl;
        int j=i;
        int num_digits=0;
         while(isdigit(x[j])&& num_digits <=8)//count how many numbers I have
        {
          j++;
          num_digits++;
        }

        string integer =x.substr(i,x.length());
        int pos=0;
        ae2 = parse(integer,pos,store,arrStore,_line);
        i=i+(pos);
        right = true;
         // isthereae = true;
      }
    i++;
  }


  if(save_operator == '>')
   { 
    total = new Morethan(ae2,ae1,arrStore);
  }
  else if(save_operator == '<')
  {

    total = new Lessthan(ae1,ae2,arrStore);
  }
  else if(save_operator == '=')
  {
    total = new Equals(ae1,ae2,arrStore);
  }
      return total;
}






int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide an input file." << endl;
    return -1;
  }


  ifstream input(argv[1]);
  if(input.fail())
  {
    cerr <<  "File "<< argv[1]<< " cannot be opened."<<endl;
    return -1;
  }

  string curr=""; // the current line
  string temp="";
  BooleanExpression* output2=NULL;
  Command* com=NULL;
  ArithmeticExpression* output1=NULL;
  ArithmeticExpression* output3=NULL;

  map<int,Command*> *commandMap;//stores line and commands
  commandMap = new map<int, Command*>;

  map<string, int> *varMap;//stores the varaible value
  varMap = new map<string, int>;
  
  map<string,map<int,int>>* arrMap;
  arrMap = new map<string,map<int,int>>;


  //loop to read all lines of the program
  while(getline(input, curr)) {
    stringstream ss;
    ss << curr;
    string command; // the command
    unsigned int line;  // the line number
    ss >> line;
    ss >> command;
    string total="";
    
    if (command == "PRINT"){
      // you obviously need to put a lot of stuff here and in the other cases
      while(ss >> temp)
      { 
        total = total+temp; //read in all the line
      }

  
    int num_brackets=0;
    int num_square=0;
        for(int i=0;i<(signed)total.length();i++)
        {
          if(total[i]=='(')
          {
            num_brackets++;

          }
          else if (total[i]==')' && num_brackets !=0)
          {
            num_brackets--;
          }
          else if (total[i]=='[')
          {
            num_square++;
          }
          else if (total[i]==']' && num_square !=0)
          {
            num_square++;
          }

          if((total[i]==']' ||total[i]==')') && num_brackets==0)
          { 
            
            string cut = total.substr(0,total.length());
            int k=0;
            output1 =parse(cut,k,varMap,arrMap,line);
            com = new Print(line,output1);
      
            // com->print(cout);
            // cout <<endl;
            commandMap->insert(std::make_pair(line,com));
            // delete com;
            break;
          }
          else 
          {
            string cut = total.substr(0,total.length());
            int k=0;
            output1 =parse(cut,k,varMap,arrMap,line);
            com = new Print(line,output1);
            commandMap->insert(std::make_pair(line,com));
            // com->print(cout);
            // cout <<endl;
            // delete com;
            break;
          }

        }
      
      

    }
    else if (command == "LET") {
      int counter =0;
      string temp2="";
      string temp3="";
      while(ss>>temp)
      {
        if(counter ==0)
        {
         
          temp2 = temp;

        }
        total=total+temp;
        counter++;
      }
      // cout << "total is "<<total <<endl;
      if(isalpha(temp2[temp2.length()-1]) && total[temp2.length()]!='[')
      { //first is a variable
        int goin=0;
        int goin2=0;
        string first = total.substr(0,temp2.length());
        string second = total.substr(temp2.length(),total.length()-temp2.length());
        output1 = parse(first,goin,varMap,arrMap,line);
        output3 = parse(second,goin2,varMap,arrMap,line);
        // int value = output3->get();
        com = new Let(output1,output3,line);
       
      }
      else if((isalpha(temp2[temp2.length()-1]) && (total[temp2.length()]=='['))
        || ((signed)temp2.find('[')!=-1))
      { //first is an array
        int bracket=0;
        bool foundbrack=false;
        // int c_pos=0;
        int c=0;
        int position=0;

          for(int i=0;i<(signed)total.length();i++)
          {
            if(total[i]=='[' && c==0)
            {
              bracket++;
              foundbrack=true;
              // c_pos=i;
              c++;
            }
            else if(total[i]=='[' && c!=0)
            {
              bracket++;
              foundbrack=true;
            }
            else if (total[i]==']')
            {
              bracket --;
              foundbrack=true;
            }

            if(bracket ==0 && foundbrack==true)
            {
              position =i;
              break;
            }
          }

        int goin=0;
        int goin2=0;
        string first = total.substr(0,position+1);
        string second = total.substr(position+1,total.length()-position+1);
        output1 = parse(first,goin,varMap,arrMap,line);
        output3 = parse(second,goin2,varMap,arrMap,line);
        com = new Let(output1,output3,line);
      }

      commandMap->insert(std::make_pair(line,com));

      // delete com;
    }



    else if (command == "GOTO") {
      int _toline;
      ss >> _toline;
      com = new Goto(line, _toline);
      // com->print(cout);
      // cout <<endl;

      // delete com;
      commandMap->insert(std::make_pair(line,com));

    }
    else if (command == "IF") {
         
      int num;
      string then;
       while(ss >> temp)
      { 
        if(temp != "THEN")
        {
          total = total+temp; //read in all the line
        }
        else if(temp == "THEN")
        {
          then = temp;
          break;
        }
      }

      ss>>num;//get line num
      int k=0;
      output2= boolparse(total,k,varMap,arrMap,line);
      com = new IfStatement(output2,line,num);

 
      commandMap->insert(std::make_pair(line,com));
      // delete com;
    }
    else if (command == "GOSUB") {

      int _toline;
      ss >> _toline;
      com = new Gosub(line, _toline);
      // com->print(cout);
      // cout <<endl;
      commandMap->insert(std::make_pair(line,com));
       // delete com;
    }
    else if (command == "RETURN") {
      com = new Return(line);
      // com->print(cout);
      // cout <<endl;
      commandMap->insert(std::make_pair(line,com));
       // delete com;
    }
    else if (command == "END") {

      com = new End(line);
      // com->print(cout);
      // cout <<endl;
      commandMap->insert(std::make_pair(line,com));
       // delete com;
    }
    else {
      // This should never happen - print an error?
    }



 
  }


stack<int>* jumpfrom;
jumpfrom = new stack<int>;


map<int, Command*>::iterator it ;

for(it = commandMap->begin(); it != commandMap->end();it++)
{
   it->second->print(cout);
   cout <<endl;
   // delete it->second;
}


In work(commandMap,varMap,arrMap,jumpfrom);
try{

work.executeProgram();
}
catch(If_noLine & e)
{
  cout<< e.what()<<endl;
  return -1;
}
catch(Division_zero & f)
{
  cout<< f.what()<<endl;
  return -1;
}
catch(Gosub_noline & g)
{
  cout<< g.what()<<endl;
  return -1;
}
catch(Gosub_noReturn & h)
{
  cout<< h.what()<<endl;
  return -1;
}
catch(Goto_noline & i)
{
  cout<< i.what()<<endl;
  return -1;
}


   
  








map<int, Command*>::iterator it2 ;

for(it2 = commandMap->begin(); it2 != commandMap->end();it2++)
{
  
   delete it2->second;
}

// map<string, map<int,int>>::iterator it3 ;

// for(it = commandMap->find(9); it != commandMap->end();it++)
// {
//    // cout<<it2->first<<endl;
//   cout << it->first << " "<<it->second<<endl;
// // }
// cout<< "inside map is A "<<(*arrMap)["A"][1]<<endl;
// cout<< "inside map is XE "<<(*arrMap)["XE"][10]<<endl;
// cout<< "inside map is E "<<(*arrMap)["E"][14]<<endl;
// cout<< "inside map is E "<<(*arrMap)["X"][20]<<endl;





delete commandMap;
delete varMap;
delete arrMap;
delete jumpfrom;


  return 0;
}
