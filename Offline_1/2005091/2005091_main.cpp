#include <bits/stdc++.h>
#include "2005091_SymbolTable.h"

using namespace std;

string tokens[10];
void wrong_input(string s1)
{
    cout<<"\tWrong number of arugments for the command "<<s1<<endl;
}

void invalid_input(string s1)
{
    cout<<"\tInvalid argument for the command "<<s1<<endl;
}


int main() {
    FILE *file1=freopen("input.txt","r",stdin);
    FILE *file2=freopen("output.txt","w",stdout);
    int TableSize;
    cin>>TableSize;
    cin.ignore();
    int command_cnt=1;
    SymbolTable SymbolTable(TableSize);



    while(!feof(stdin))
    {
        string inputString,command;
        getline(cin,inputString);


        cout<<"Cmd "<<command_cnt<<": ";
        cout<<inputString<<endl;


        istringstream strstream(inputString);
        int numberOfString=0;
        while(strstream>>command)
        {
            tokens[numberOfString]=command ;
            numberOfString++;
            if(numberOfString>5)break;
        }
        

        command=tokens[0];
        command_cnt++;


        if(command=="I")
        {
            if(numberOfString!=3)
            {
                wrong_input("I");
            }
            else
            {
                string name=tokens[1];
                string type=tokens[2];
                SymbolTable.InsertNewSymbolInfo(name,type);
            }
        }
        else if(command=="L")
        {
            if(numberOfString!=2)
            {
                wrong_input("L");
            }
            else
            {
                string name=tokens[1];
                SymbolTable.LookUpSymbol(name);
            }
        }
        else if(command=="D")
        {
            if(numberOfString!=2)
            {
                wrong_input("D");
            }
            else
            {
                string name=tokens[1];
                SymbolTable.DeleteSymbol(name);
            }
        }
        else if(command=="P")
        {
            if(numberOfString!=2)
            {
                wrong_input("P");
            }
            else
            {
                string tem=tokens[1];
                if(tem=="A")SymbolTable.PrintAllScopeTable();
                else if(tem=="C")SymbolTable.PrintCurrentScopeTable();
                else 
                {
                    invalid_input("P");
                }
            }
        }
        else if(command=="S")
        {
            if(numberOfString!=1)
            {
                wrong_input("S");
            }
            else
            {
                SymbolTable.EnterNewScope();
            }
        }
        else if(command=="E")
        {
            if(numberOfString!=1)
            {
                wrong_input("E");
            }
            else
            {
                SymbolTable.ExitScope();
            }
        }
        else if(command=="Q")
        {
            return 0;
        }
    }
}