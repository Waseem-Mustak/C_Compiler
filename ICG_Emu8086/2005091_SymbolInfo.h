#ifndef SYMBOLINFO_HEADER
#define SYMBOLINFO_HEADER


extern int mycnt;
#include<bits/stdc++.h>
using namespace std;
class SymbolInfo
{
    private:
        SymbolInfo* PointerOfNextSymbollInfo;
        string Name;
        string Type;
        string typeSpecifier;
        vector<SymbolInfo*>declarationlist;
        vector<SymbolInfo*>node;
        vector<SymbolInfo*>parameterlist;
        int lineStart;
        int lineEnd;
        bool isToken;
        bool isDeclared;
        bool isFunction;
        bool isArray=false;
        int size = 0;
    public:

        string code = "";
        string varName = "";
        int stackOffset = 0;
        int pushOffset = 0;


        SymbolInfo(){}
        SymbolInfo(string name, string type, string typespecifier, int linestart, int lineend, bool istoken, ostream& outputStreame, vector<SymbolInfo*> list){
            PointerOfNextSymbollInfo=nullptr;
            Name=name;
            Type=type;
            typeSpecifier=typespecifier;
            lineStart=linestart;
            lineEnd=lineend;
            isToken=istoken;
            isArray=false;
            isFunction=false;

            for(auto va:list)
            {
                node.push_back(va);
            }

            if(isToken==false)
            {
                outputStreame<<Type<<" :"<<Name<<" "<<endl;
            }
            else
            {
                outputStreame<<"Line# "<<lineStart<<": Token <"<<Type<< "> Lexeme "<<Name<<" found"<<endl;
            }
        }
        SymbolInfo(string name,string type)
        {
            PointerOfNextSymbollInfo=nullptr;
            Name=name;
            Type=type;
        }
        
        ~SymbolInfo()
        {
            ;
        }

        void setName(string name)
        {
            Name=name;
        }
        
        string getName()
        {
            return Name;
        }
        void setType(string type)
        {
            Type=type;
        }
        string getType()
        {
            return Type;
        }
        int getSize()
        {
            return size;
        }
        int getStart()
        {
            return lineStart;
        }
        int getEnd()
        {
            return lineEnd;
        }

        void setIsFunction(bool tem)
        {
            isFunction=tem;
        }

        string getStatement()
        {
            if(isToken==true) 
            {
                return Name;
            }
            else 
            {
                string tem="";
                for(auto va:node)
                {
                    tem+=va->getStatement();
                }
                return tem;
            }
        }

        bool getIsArray()
        {
            return isArray;
        }
        

        void printParseTree(ostream& outputStreme,int depth)
        {
            for(int i=0;i<depth;i++) 
            {
                outputStreme<<" ";
            }
            if(isToken==true) 
            {
                outputStreme<<Type<<" : "<<Name<<"\t<Line: "<<lineStart<<">"<<endl;
            }
            else 
            {
                outputStreme<<Type<<" :"<<Name<<" \t<Line: "<<lineStart<<"-"<<lineEnd<<">"<<endl;
            }
            for(auto va:node)
            {
                va->printParseTree(outputStreme,depth+1);
            }
        }


        bool getIsDeclared()
        {
            return isDeclared;
        }

        bool getIsFunction()
        {
            return isFunction;
        }
        void setPointerOfNextSymbollInfo(SymbolInfo* symbolInfo)
        {
            PointerOfNextSymbollInfo=symbolInfo;
        }

        void setTypeSpecifier(string typespecifier)
        {
            typeSpecifier=typespecifier;
        }
        string getTypeSpecifier()
        {
            return typeSpecifier;
        }

        void setIsDeclared(bool tem)
        {
            isDeclared=tem;
        }

        vector<SymbolInfo*> getParameterList()
        {
            return parameterlist;
        }

        void setParameterList(vector<SymbolInfo*> tem)
        {
            parameterlist=tem;
        }

        vector<SymbolInfo*> getDeclarationList()
        {
            return declarationlist;
        }

        void setDeclarationList(vector<SymbolInfo*> tem)
        {
            declarationlist=tem;
        }

        void setIsArray(bool tem)
        {
            isArray=tem;
        }

        void addDeclaration(SymbolInfo* tem)
        {
            declarationlist.push_back(tem);
        }

        void addParameter(SymbolInfo* tem)
        {
            parameterlist.push_back(tem);
        }

        SymbolInfo* getPointerOfNextSymbollInfo()
        {
            return PointerOfNextSymbollInfo;
        }
};
#endif //SYMBOLINFO_HEADER