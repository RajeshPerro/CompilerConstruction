#include "iostream"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "fstream"
#include "limits"
#include <cstdlib>

using namespace std;

fstream& GotoLine(fstream& file, unsigned int num){
    file.seekg(ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(std::numeric_limits<streamsize>::max(),'\n');
    }
    return file;
}

fstream ReadFile;
char *symbols;
int numOfSymbol=0;
//char *finalState;
string *finalState;
string *rules;
string *nameOfstates;
int numOfState;
string fileName;

int check(int state,char value)
{
	//cout <<"state: "<< state<<" value:"<<value<<endl;

	if(value == symbols[0])
		return state+1;
	else if(value == symbols[1])
		return state+2;
	else if(value == symbols[2])
		return state+3;
}	

int main(int argc, char const *argv[])
{
	
	

	char *inputData;
	inputData = new char[sizeof(char)];
	string sourceFileName;
	symbols = new char[sizeof(char)];
	 
	cout<<"Give your input : ";
	gets(inputData);
	int len = strlen(inputData);

	cout<<"Please Give the Source File name : ";
	cin>>fileName;
	sourceFileName = fileName.append(".txt");

	ReadFile.open(sourceFileName);

	/*<<<-- Reading 1st line that menas symbols for our machine from our input text file-->>>*/
	GotoLine(ReadFile,2);
	int cnt=0;
	while (ReadFile.peek() != '\n') 
	{
  		 ReadFile >> symbols[cnt++];
  		 numOfSymbol++;
  		
	}
	cout<<"Number of Sysmbols : "<<numOfSymbol<<endl;
	cout<<"<<<---Sysmbols for our machine--->>>"<<endl;
	for (int i = 0; i < cnt; ++i)
	{
		printf(" %c ",symbols[i]);
	}
	cout<<endl;
	/*<<<-- Reading 2nd line (the number of state) from our input text file-->>>*/
	GotoLine(ReadFile, 4);
	ReadFile>>numOfState;
	cout<<"Number of state : "<<numOfState<<endl;

	/*<<<-- Reading 3rd line (final states) from our input text file-->>>*/
	finalState = new string[numOfState];
	GotoLine(ReadFile,6);
	int cnt1=0;
	while (ReadFile.peek() != '\n') 
	{
  		 ReadFile >> finalState[cnt1++];
  		
	}
	cout<<"<<<---Final states--->>>"<<endl;
	for (int i = 0; i < cnt1; ++i)
	{
		cout<<finalState[i]<<" ";
	}
	cout<<endl;


	/*<<<-- Reading 4th line to end of file (rules) from our input text file-->>>*/
	int rulesSize = (numOfState*numOfSymbol)+numOfState;
	//cout<<rulesSize<<endl;
	rules = new string[rulesSize];
	int r=0;
	//int iccha = numOfState+8;
	for (int i = 8; i <  numOfState+8; i++)
	{
		GotoLine(ReadFile,i);
		 while (ReadFile.peek() != '\n')
		 {
			ReadFile>>rules[r++];
		}
		
	}
	 //cout<<"r = "<<r<<endl;
	cout<<"<<<---Rules of our machine--->>>"<<endl;
	
	for (int j=1, i = 0; i < r; ++i,j++)
	{
		cout<<rules[i]<<" ";

		if (j==(numOfSymbol+1))
		{
			cout<<endl;
			j=0;
		}
		
	}
	cout<<endl;

	nameOfstates = new string[numOfState+1];
	int arrpos=0;
	for (int j=0, i = 0; i < r; ++i,j++)
	{
		if (i==0)
		{
			nameOfstates [arrpos++] = rules[0];
		}
		else if(j == (numOfSymbol+1))
		{
			nameOfstates [arrpos++] = rules[i];	
			j=0;
		}
		
		
	}
	


	//starting main program
	
	 int *rong;
	 rong = new int[numOfState];
	 int ff = 0;
	 for(int x = 0,j=0; x<numOfState; x++)
	 {
	 	rong[ff++] = j;
	 	j+=4;
	 }

	 

	 int init = 0, bb;
	 for(int i=0; i<len; i++)
	 {
	 	bb = check(init, inputData[i]);

	 	for (int k = 0; k < numOfState; ++k)
	 	{
	 		/* code */
	 		if(rules[bb] == nameOfstates[k])
	 		{
	 			init = rong[k];
	 			break;
	 		}
	 	}


	 	

	 }

	 for (int i = 0; i < cnt1; ++i)
	 {
	 	if (rules[init] == finalState[i])
	 	{
	 		cout <<"The state is  : "<< rules[init] <<" and it's a final state. So, ";
	 		cout<<"Accepted.!!"<<endl;
	 		break;
	 	}
	 	else
	 	{
	 		cout<<"Sorry.!! Not accepted.!!"<<endl;
	 		break;
	 	}
	 }	

	ReadFile.close();
	return 0;
}











