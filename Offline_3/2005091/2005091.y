%{
#include <bits/stdc++.h>
#include <typeinfo>

#include "2005091_SymbolInfo.h"
#include "2005091_SymbolTable.h"
#include "2005091_ScopeTable.h"

using namespace std;

ofstream logout;
ofstream errorout;
ofstream parseout;

SymbolTable* symbolTable=new SymbolTable(11);
SymbolInfo* symbolInfoArguments=new SymbolInfo();
int mycnt=0;

extern int line_count;
extern int total_error;
extern FILE *yyin;


string concatName(vector<SymbolInfo*> tem)
{
    string tem_name="";
    for(auto va:tem)
    {
        tem_name+=" ";
        tem_name+=va->getType();
    }
    return tem_name;
}

void errorPrint(string tem)
{
    total_error++;
    errorout<<"Line# "<<line_count<< ": "<<tem<<endl;
}

string changeTypeSpecifier(SymbolInfo* tem_1,SymbolInfo* tem_2)
{
    if((tem_1->getTypeSpecifier()=="error")||(tem_1->getTypeSpecifier()=="VOID"))return "error";
    else if((tem_2->getTypeSpecifier()=="error")||(tem_2->getTypeSpecifier()=="VOID"))return "error";
    else
    {
        if((tem_1->getTypeSpecifier()=="FLOAT"))return "FLOAT";
        else if((tem_2->getTypeSpecifier()=="FLOAT"))return "FLOAT";
        else
        {
            return "INT";
        }
    }
}


SymbolInfo* createNewSymbolInfo(vector<SymbolInfo*> listOfName,string type,string TypeSpecifier,SymbolInfo* startTime,SymbolInfo* endTime,vector<SymbolInfo*> expensionList)
{
    return new SymbolInfo(concatName(listOfName),type,TypeSpecifier,startTime->getStart(),endTime->getEnd(),false,logout,expensionList); 
}

void checkParameters(vector<SymbolInfo*> list_1,vector<SymbolInfo*> list_2,SymbolInfo* tem)
{
    int n=list_1.size();
    for(int i=0;i<n;i++)
    {
        if(list_1[i]->getTypeSpecifier()!=list_2[i]->getTypeSpecifier())
        {
            errorPrint("Type mismatch for argument "+to_string(i+1)+" of '"+tem->getName()+"'");
        }
    }
}


void functionCheck(SymbolInfo* nameOfFunction,SymbolInfo* typeSpecifier)
{
    nameOfFunction->setIsFunction(true);
	nameOfFunction->setTypeSpecifier(typeSpecifier->getTypeSpecifier());
	nameOfFunction->setParameterList(symbolInfoArguments->getParameterList());
		
	SymbolInfo* temFunc=symbolTable->LookUpSymbol(nameOfFunction->getName());

    if(temFunc==NULL)return;

	if(temFunc->getIsDeclared()==false)
    {
        errorPrint("\'"+nameOfFunction->getName()+"\' redeclared as different kind of symbol");
	}
    else
    {
		if(temFunc->getTypeSpecifier()!=nameOfFunction->getTypeSpecifier())
        {
			errorPrint("Conflicting types for\'"+nameOfFunction->getName()+"\'");
		}
        int n=temFunc->getParameterList().size();
        int m=nameOfFunction->getParameterList().size();
		if(n==m)
        {
            checkParameters(temFunc->getParameterList(),nameOfFunction->getParameterList(),nameOfFunction);
		}
        else
        {
            errorPrint("Conflicting types for\'"+nameOfFunction->getName()+"\'");
		}
	}
}





void yyerror(string s)
{
    logout<<"Error at line "<<line_count<<": "<<s<<endl;
}

int yyparse(void);
int yylex(void);

%}



%union{
    SymbolInfo* symbolInfo; 
}

%token<symbolInfo> IF ELSE LOWER_THAN_ELSE FOR WHILE RETURN PRINTLN INCOP DECOP ASSIGNOP NOT LPAREN RPAREN LCURL RCURL LSQUARE RSQUARE COMMA SEMICOLON INT FLOAT VOID CONST_INT CONST_FLOAT ID ADDOP MULOP RELOP LOGICOP 
%type<symbolInfo> lcurl start program unit func_declaration func_definition parameter_list compound_statement var_declaration type_specifier declaration_list statements statement expression_statement variable expression logic_expression rel_expression simple_expression term unary_expression factor argument_list arguments 


%left COMMA
%right ASSIGNOP
%left LOGICOP
%left RELOP
%left ADDOP
%left MULOP
%left LCURL RCURL
%left LPAREN RPAREN

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
start : program                                     {
                                                        $$=createNewSymbolInfo({$1},"start","",$1,$1,{$1});
                                                        $$->printParseTree(parseout,0); 
                                                    }
    ;

program : program unit                              {
                                                        $$=createNewSymbolInfo({$1,$2},"program","",$1,$2,{$1,$2});
                                                    }
    | unit                                          {
                                                        $$=createNewSymbolInfo({$1},"program","",$1,$1,{$1});
                                                    }
    ;
    
unit : var_declaration                              {
                                                        $$=createNewSymbolInfo({$1},"unit","",$1,$1,{$1});
                                                    }
    | func_declaration                              {
                                                        $$=createNewSymbolInfo({$1},"unit","",$1,$1,{$1});
                                                    }
    | func_definition                               {
                                                        $$=createNewSymbolInfo({$1},"unit","",$1,$1,{$1});
                                                    }
    ;
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON    {
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4,$5,$6},"func_declaration","",$1,$6,{$1,$2,$3,$4,$5,$6}); 
                                                        $2->setTypeSpecifier($1->getTypeSpecifier()); 
                                                        $2->setParameterList($4->getParameterList()); 
                                                        $2->setIsFunction(true);
                                                        $2->setIsDeclared(true);
                                                        symbolInfoArguments->setParameterList({}); 
                                                        if(!symbolTable->InsertNewSymbolInfo($2))
                                                        {
                                                            errorPrint("Redeclaring function");
                                                        }
                                                    }
        |   type_specifier ID LPAREN RPAREN SEMICOLON { 
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4,$5},"func_declaration","",$1,$5,{$1,$2,$3,$4,$5}); 
                                                        $2->setTypeSpecifier($1->getTypeSpecifier()); 
                                                        $2->setIsFunction(true);
                                                        $2->setIsDeclared(true);
                                                        symbolInfoArguments->setParameterList({});
                                                        if(!symbolTable->InsertNewSymbolInfo($2))
                                                        {
                                                            errorPrint("Redeclaring function");
                                                        }
                                                    }
        ;
func_definition  : type_specifier ID LPAREN parameter_list RPAREN {functionCheck($2,$1);} compound_statement {
    
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4,$5,$7},"func_definition","",$1,$7,{$1,$2,$3,$4,$5,$7});
                                                        $2->setTypeSpecifier($1->getTypeSpecifier()); 
                                                        $2->setParameterList($4->getParameterList()); 
                                                        $2->setIsFunction(true);
                                                        $2->setIsDeclared(true); 
                                                        symbolInfoArguments->setParameterList({}); 
                                                        symbolTable->InsertNewSymbolInfo($2);
                                                    }
        |   type_specifier ID LPAREN RPAREN {functionCheck($2,$1);} compound_statement {
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4,$6},"func_definition","",$1,$6,{$1,$2,$3,$4,$6});
                                                        $2->setTypeSpecifier($1->getTypeSpecifier()); 
                                                        $2->setIsFunction(true);
                                                        $2->setIsDeclared(true); 
                                                        symbolInfoArguments->setParameterList({}); 
                                                        symbolTable->InsertNewSymbolInfo($2);
                                                    }
        ;
parameter_list   : parameter_list COMMA type_specifier ID {
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4},"parameter_list","",$1,$4,{$1,$2,$3,$4}); 
                                                        $4->setTypeSpecifier($3->getTypeSpecifier());
                                                        $$->setParameterList($1->getParameterList()); 
                                                        $$->addParameter($4); 
                                                        symbolInfoArguments->setParameterList($$->getParameterList()); 
                                                    }
        |   parameter_list COMMA type_specifier     {
                                                        $$=createNewSymbolInfo({$1,$2,$3},"parameter_list","",$1,$3,{$1,$2,$3}); 
                                                        
                                                        SymbolInfo* tem=new SymbolInfo("","ID",$3->getTypeSpecifier(),10000,10000,false,logout,{});
                                                        $$->setParameterList($1->getParameterList()); 
                                                        $$->addParameter(tem);
                                                        symbolInfoArguments->setParameterList($$->getParameterList()); 
                                                    }
        |   type_specifier ID                       {
                                                        $$=createNewSymbolInfo({$1,$2},"parameter_list","",$1,$2,{$1,$2}); 
                                                        $2->setTypeSpecifier($1->getTypeSpecifier());
                                                        $$->addParameter($2);
                                                        symbolInfoArguments->setParameterList($$->getParameterList());
                                                    }
        |   type_specifier                          {
                                                        $$=createNewSymbolInfo({$1},"parameter_list","",$1,$1,{$1}); 
                                                        SymbolInfo* tem=new SymbolInfo("","ID",$1->getTypeSpecifier(),10000,10000,false,logout,{});
                                                        $$->addParameter(tem); 
                                                        symbolInfoArguments->setParameterList($$->getParameterList()); 
                                                    }
        ;
compound_statement  :   lcurl statements RCURL      {
                                                        $$=createNewSymbolInfo({$1,$2,$3},"compound_statement","",$1,$3,{$1,$2,$3});
                                                        symbolTable->PrintAllScopeTable(logout);
                                                        symbolTable->ExitScope();
                                                    }
        |   lcurl RCURL                             {
                                                        $$=createNewSymbolInfo({$1,$2},"compound_statement","",$1,$2,{$1,$2});
                                                        symbolTable->PrintAllScopeTable(logout);
                                                        symbolTable->ExitScope();
                                                    }
        ;
var_declaration  : type_specifier declaration_list SEMICOLON {
                                                    $$=createNewSymbolInfo({$1,$2,$3},"var_declaration","",$1,$3,{$1,$2,$3});
                                                    for(auto va:$2->getDeclarationList())
                                                    {
                                                        va->setTypeSpecifier($1->getTypeSpecifier());
                                                    }
                                                    for(auto va:$2->getDeclarationList())
                                                    {
                                                        if(va->getTypeSpecifier()=="VOID") {
                                                            errorPrint("Variable or field '"+ va->getName()+"' declared void");
                                                        }
                                                        else if(!symbolTable->InsertNewSymbolInfo(va)) {
                                                            errorPrint("Conflicting types for\'"+va->getName()+"\'");
                                                        }	
                                                    }
}
        ;
type_specifier   : INT                              {
                                                        $$=createNewSymbolInfo({$1},"type_specifier",$1->getTypeSpecifier(),$1,$1,{$1});
                                                    }
        |   FLOAT                                   {
                                                        $$=createNewSymbolInfo({$1},"type_specifier",$1->getTypeSpecifier(),$1,$1,{$1});
                                                    }
        |   VOID                                    {
                                                        $$=createNewSymbolInfo({$1},"type_specifier",$1->getTypeSpecifier(),$1,$1,{$1});
                                                    }
        ;
declaration_list : declaration_list COMMA ID        {
                                                        $$=createNewSymbolInfo({$1,$2,$3},"declaration_list","",$1,$3,{$1,$2,$3}); 
                                                        $$->setDeclarationList($1->getDeclarationList()); 
                                                        $$->addDeclaration($3);
                                                    }
        |   declaration_list COMMA ID LSQUARE CONST_INT RSQUARE {
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4,$5,$6},"declaration_list","",$1,$6,{$1,$2,$3,$4,$5,$6}); 
                                                        $3->setIsArray(true);
                                                        $$->setDeclarationList($1->getDeclarationList()); 
                                                        $$->addDeclaration($3); 
                                                    }
        |   ID                                      {
                                                        $$=createNewSymbolInfo({$1},"declaration_list","",$1,$1,{$1});
                                                        $$->addDeclaration($1);
                                                    }
        |   ID LSQUARE CONST_INT RSQUARE              {
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4},"declaration_list","",$1,$4,{$1,$2,$3,$4}); 
                                                        $1->setIsArray(true);
                                                        $$->addDeclaration($1);  
                                                    }
        ;
statements       : statement                        {
                                                        $$=createNewSymbolInfo({$1},"statements","",$1,$1,{$1});
                                                    }
        |   statements statement                    {
                                                        $$=createNewSymbolInfo({$1,$2},"statements","",$1,$2,{$1,$2});
                                                    }
        ;
statement        : var_declaration                  {
                                                        $$=createNewSymbolInfo({$1},"statement","",$1,$1,{$1});
                                                    }
        |   expression_statement                    {
                                                        $$=createNewSymbolInfo({$1},"statement","",$1,$1,{$1});
                                                    }
        |   compound_statement                      {
                                                        $$=createNewSymbolInfo({$1},"statement","",$1,$1,{$1});
                                                    }
        |   FOR LPAREN expression statement expression statement expression RPAREN statement {
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4,$5,$6,$7},"statement","",$1,$7,{$1,$2,$3,$4,$5,$6,$7});
                                                    }
        |   IF LPAREN expression RPAREN statement   {
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4,$5},"statement","",$1,$5,{$1,$2,$3,$4,$5});
                                                    }
        |   IF LPAREN expression RPAREN statement ELSE statement {
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4,$5,$6,$7},"statement","",$1,$7,{$1,$2,$3,$4,$5,$6,$7});
                                                    }
        |   WHILE LPAREN expression RPAREN statement {
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4,$5},"statement","",$1,$5,{$1,$2,$3,$4,$5});
                                                    }
        |   PRINTLN LPAREN ID RPAREN SEMICOLON      {
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4,$5},"statement","",$1,$5,{$1,$2,$3,$4,$5});
                                                    }
        |   RETURN expression SEMICOLON             {
                                                        $$=createNewSymbolInfo({$1,$2,$3},"statement","",$1,$3,{$1,$2,$3});
                                                    }
        ;
expression_statement :  SEMICOLON                   {
                                                        $$=createNewSymbolInfo({$1},"expression_statement","",$1,$1,{$1});
                                                    }
        |   expression SEMICOLON                    {
                                                        $$=createNewSymbolInfo({$1,$2},"expression_statement",$1->getTypeSpecifier(),$1,$2,{$1,$2});
                                                    }
        ;
variable :  ID                                      {
                                                        $$=createNewSymbolInfo({$1},"variable","",$1,$1,{$1}); 
                                                        SymbolInfo* va=symbolTable->LookUpSymbol($1->getName());
                                                        if(va!=NULL)
                                                        {
                                                            $$->setTypeSpecifier(va->getTypeSpecifier());
                                                            $$->setIsArray(va->getIsArray());
                                                        }
                                                        else
                                                        {
                                                            $$->setTypeSpecifier("error");
                                                            errorPrint("Undeclared variable '"+$1->getName()+"'"); 
                                                        }
                                                    }
        |   ID LSQUARE expression RSQUARE           {
                                                        $$=createNewSymbolInfo({$1,$2,$3,$4},"variable","",$1,$4,{$1,$2,$3,$4});
                                                        SymbolInfo* va=symbolTable->LookUpSymbol($1->getName());
                                                        if(va!=NULL)
                                                        {
                                                            if(va->getIsArray()==false)
                                                            {
                                                                $$->setTypeSpecifier("error");
                                                                errorPrint("\'"+$1->getName()+"\' is not an array"); 
                                                            } 
                                                            if($3->getTypeSpecifier()!="INT")
                                                            {
                                                                $$->setTypeSpecifier("error");
                                                                errorPrint("Array subscript is not an integer");
                                                            }
                                                            else 
                                                            {
                                                                $$->setIsArray(false); 
                                                                $$->setTypeSpecifier(va->getTypeSpecifier());
                                                            }
                                                        }
                                                        else
                                                        {
                                                            errorPrint("Undeclared variable '"+$1->getName()+"'"); 
                                                            $$->setTypeSpecifier("error");                                                            
                                                        }
                                                    }
        ;
expression       : logic_expression                     {
                                                            $$=createNewSymbolInfo({$1},"expression",$1->getTypeSpecifier(),$1,$1,{$1});
                                                            $$->setIsArray($1->getIsArray());
                                                        }
        |   variable ASSIGNOP logic_expression          {

                                                            $$=createNewSymbolInfo({$1,$2,$3},"expression","",$1,$3,{$1,$2,$3});
                                                            $$->setIsArray($1->getIsArray());

                                                            if($3->getTypeSpecifier()=="VOID")
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }
                                                            if(($1->getTypeSpecifier()=="INT")&&($3->getTypeSpecifier()=="FLOAT"))
                                                            {
                                                                errorPrint("Warning: possible loss of data in assignment of FLOAT to INT");
                                                            }
                                                        } 
        ;
logic_expression : rel_expression                       {
                                                            $$=createNewSymbolInfo({$1},"logic_expression",$1->getTypeSpecifier(),$1,$1,{$1});  
                                                            bool tem=$1->getIsArray();
                                                            $$->setIsArray(tem);
                                                        }
        |   rel_expression LOGICOP rel_expression       {

                                                            $$=createNewSymbolInfo({$1,$2,$3},"logic_expression","INT",$1,$3,{$1,$2,$3}); 
                                                            if(($1->getTypeSpecifier()=="VOID")||($3->getTypeSpecifier()=="VOID"))
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }
                                                        }
        ;
rel_expression   : simple_expression                    {
                                                            $$=createNewSymbolInfo({$1},"rel_expression",$1->getTypeSpecifier(),$1,$1,{$1});
                                                            bool tem=$1->getIsArray();
                                                            $$->setIsArray(tem);
                                                        }
        |   simple_expression RELOP simple_expression   {
                                                            $$=createNewSymbolInfo({$1,$2,$3},"rel_expression","INT",$1,$3,{$1,$2,$3}); 
                                                            if(($1->getTypeSpecifier()=="VOID")||($3->getTypeSpecifier()=="VOID"))
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }
                                                        }
        ;
simple_expression   :   term                            {
                                                            $$=createNewSymbolInfo({$1},"simple_expression",$1->getTypeSpecifier(),$1,$1,{$1});
                                                            bool tem=$1->getIsArray();
                                                            $$->setIsArray(tem);
                                                        }
        |   simple_expression ADDOP term                {
                                                            $$=createNewSymbolInfo({$1,$2,$3},"simple_expression",changeTypeSpecifier($1,$3),$1,$3,{$1,$2,$3});
                                                            if($3->getTypeSpecifier()=="VOID")
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }
                                                        }
        ;
term : unary_expression                                 {
                                                            $$=createNewSymbolInfo({$1},"term",$1->getTypeSpecifier(),$1,$1,{$1});
                                                            bool tem=$1->getIsArray();
                                                            $$->setIsArray(tem);
                                                        }
        |   term MULOP unary_expression                 {
                                                            $$=createNewSymbolInfo({$1,$2,$3},"term",changeTypeSpecifier($1,$3),$1,$3,{$1,$2,$3});
                                                            if($3->getTypeSpecifier()=="VOID")
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }
                                                            if(($2->getName()=="/")&&($3->getStatement()=="0"))
                                                            { 
                                                                $$->setTypeSpecifier("error");
                                                                errorPrint("Warning: division by zero");
                                                            }
                                                            if(($2->getName()=="%")&&($3->getStatement()=="0"))
                                                            { 
                                                                $$->setTypeSpecifier("error"); 
                                                                errorPrint("Warning: division by zero"); 
                                                            }
                                                            if($2->getName()=="%")
                                                            {
                                                                if(!(($1->getTypeSpecifier()=="INT")&&($3->getTypeSpecifier()=="INT")))
                                                                {
                                                                    $$->setTypeSpecifier("error");
                                                                    errorPrint("Operands of modulus must be integers "); 
                                                                }
                                                            }
                                                        }
        ;
unary_expression : ADDOP unary_expression               {
                                                            $$=createNewSymbolInfo({$1,$2},"unary_expression",$2->getTypeSpecifier(),$1,$2,{$1,$2}); 
                                                            if($2->getTypeSpecifier()=="VOID")
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }
                                                        }
        |   NOT unary_expression                        {
                                                            $$=createNewSymbolInfo({$1,$2},"unary_expression","INT",$1,$2,{$1,$2}); 
                                                            if($2->getTypeSpecifier()=="VOID")
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }
                                                        }
        |   factor                                      {
                                                            $$=createNewSymbolInfo({$1},"unary_expression",$1->getTypeSpecifier(),$1,$1,{$1}); 
                                                            bool tem=$1->getIsArray();
                                                            $$->setIsArray(tem);
                                                        }
        ;
factor  :   variable                                    {
                                                            $$=createNewSymbolInfo({$1},"factor",$1->getTypeSpecifier(),$1,$1,{$1});
                                                            bool tem=$1->getIsArray();
                                                            $$->setIsArray(tem);
                                                        }
        |   ID LPAREN argument_list RPAREN              {
                                                            $$=createNewSymbolInfo({$1,$2,$3,$4},"factor","error",$1,$4,{$1,$2,$3,$4}); 
                                                            SymbolInfo* va=symbolTable->LookUpSymbol($1->getName());
                                                            if(va!=NULL) 
                                                            {
                                                                $$->setTypeSpecifier(va->getTypeSpecifier());
                                                                vector<SymbolInfo*> tem_1=$3->getParameterList();
                                                                vector<SymbolInfo*> tem_2=va->getParameterList();
                                                                int n=tem_1.size();
                                                                int m=tem_2.size();
                                                                if(n<m)
                                                                {
                                                                    errorPrint("Too few arguments to function '"+$1->getName()+"'");
                                                                }
                                                                else if(n>m) 
                                                                {
                                                                    errorPrint("Too many arguments to function '"+$1->getName()+"'");
                                                                }
                                                                else
                                                                {                                                                    
                                                                    checkParameters(tem_1,tem_2,$1);
                                                                }
                                                            }
                                                            else
                                                            {
                                                                errorPrint("Undeclared function '"+$1->getName()+"'");
                                                            }
                                                        }
        |   LPAREN expression RPAREN                    {
                                                            $$=createNewSymbolInfo({$1,$2,$3},"factor",$1->getTypeSpecifier(),$1,$3,{$1,$2,$3});
                                                        }
        |   CONST_INT
                                                        {
                                                            $$=createNewSymbolInfo({$1},"factor","INT",$1,$1,{$1});
                                                        }
        |   CONST_FLOAT                                 {
                                                            $$=createNewSymbolInfo({$1},"factor","FLOAT",$1,$1,{$1});
                                                        }
        |   variable INCOP                              {
                                                            $$=createNewSymbolInfo({$1,$2},"factor",$1->getTypeSpecifier(),$1,$2,{$1,$2}); 
                                                            if($1->getTypeSpecifier()=="VOID" )
                                                            {
                                                                $$->setTypeSpecifier("error");
                                                                errorPrint("Variable or field '"+$1->getName()+"' declared void");
                                                            }
                                                        }
        |   variable DECOP                              {
                                                            $$=createNewSymbolInfo({$1,$2},"factor",$1->getTypeSpecifier(),$1,$2,{$1,$2}); 
                                                            if($1->getTypeSpecifier()=="VOID" )
                                                            {
                                                                $$->setTypeSpecifier("error");
                                                                errorPrint("Variable or field '"+$1->getName()+"' declared void");
                                                            }
                                                        }
        ;
argument_list    : arguments                            {
                                                            $$=createNewSymbolInfo({$1},"argument_list","",$1,$1,{$1}); 
                                                            $$->setParameterList($1->getParameterList());
                                                        }
        |                                               {
                                                            $$=new SymbolInfo(concatName({}),"argument_list","",line_count,line_count,false,logout,{});
                                                        }
        ;
arguments        : arguments COMMA logic_expression     {
                                                            $$=createNewSymbolInfo({$1,$2,$3},"arguments","",$1,$3,{$1,$2,$3}); 
                                                            $$->setParameterList($1->getParameterList()); 
                                                            $$->addParameter($3);
                                                        }
        |   logic_expression                            {
                                                            $$=createNewSymbolInfo({$1},"arguments","",$1,$1,{$1}); 
                                                            $$->addParameter($1);
                                                        }
        ;
lcurl : LCURL                                           {
                                                            $$=$1;
                                                            symbolTable->EnterNewScope(); 
                                                            for(auto va:symbolInfoArguments->getParameterList())
                                                            {
                                                                if(symbolTable->InsertNewSymbolInfo(va)==false)
                                                                {
                                                                    errorPrint("Redefinition of parameter \'"+va->getName()+"\'");
                                                                    break;
                                                                }
                                                            }
                                                            symbolInfoArguments->setParameterList({});	
                                                        }	
		;
    


%%
int main(int argc,char *argv[]){
    FILE *fp;

    if((fp=fopen(argv[1],"r"))==NULL){
        printf("Cannot Open Input File.\n");
        exit(1);
    }

    logout.open("log.txt");
    errorout.open("error.txt");
    parseout.open("paesetree.txt");

    yyin=fp;
    yyparse();
    
    logout<<"Total Lines: "<<line_count<<endl;
    logout<<"Total Errors: "<<total_error<<endl;
    cout<<"All done"<<endl;

    fclose(yyin);
    logout.close();
    errorout.close();
    parseout.close();
    return 0;
}