%option noyywrap

%{

#include "bits/stdc++.h"
#include "2005091_SymbolTable.h"
#include "2005091_ScopeTable.h"
#include "2005091_SymbolInfo.h"
#include "y.tab.h"
using namespace std;





int total_error=0,total_warning=0;
int line_count=1;
int space_count=0,tab_count=0;

extern SymbolTable* symbolTable;
extern ofstream logout;
extern ofstream errorout;
extern ofstream parseout;


void error_output(string errorType,string error){
	logout<<"Error at line "<<line_count<<": "<<errorType<<" "<<error<<endl;
	// errorout<<"Error at line "<<line_count<<": "<<errorType<<" "<<error<<endl;
	total_error++;
}


string toUpper(string s)
{
    string tem;
    for(auto character:s)
    {
        tem.push_back(toupper(character));
    }
    return tem;
}



char character_func(char tem)
{
    char ch;
    if(tem=='\'')ch='\'';
    else if(tem=='\"')ch='\"';
    else if(tem=='n')ch='\n';
    else if(tem=='t')ch='\t';
    else if(tem=='\\')ch='\\';
    else if(tem=='a')ch='\a';
    else if(tem=='f')ch='\f';
    else if(tem=='r')ch='\r';
    else if(tem=='b')ch='\b';
    else if(tem=='v')ch='\v';
    else if(tem=='0')ch='\0';
    else ch=tem;
    return ch;
}

// void createNewSymbolInfo(string name,string type)
// {
//     yylval.symbolInfo=new SymbolInfo(name,type);
// }

void createNewSymbolInfo(string name,string type,string typeSpecifier)
{
    yylval.symbolInfo=new SymbolInfo(name,type,typeSpecifier,line_count,line_count,true,logout,{});
}





%}

KEYWORD if|else|for|while|do|break|int|char|float|double|void|return|switch|case|default|continue

SPACE_ [ ]
TAB_ [\t]
WHITESPACE [\f\r\v]+
LETTER [a-zA-Z]
DIGIT [0-9]
NEWLINE \n


%%

"if" {createNewSymbolInfo(yytext,"IF","");return IF;}
"else" {createNewSymbolInfo(yytext,"ELSE","");return ELSE;}
"for" {createNewSymbolInfo(yytext,"FOR","");return FOR;}
"while" {createNewSymbolInfo(yytext,"WHILE","");return WHILE;}
"return" {createNewSymbolInfo(yytext,"RETURN","");return RETURN;}
"PRINTLN" {createNewSymbolInfo(yytext,"PRINTLN","");return PRINTLN;}
"int" {createNewSymbolInfo(yytext,"INT","INT");return INT;}
"float" {createNewSymbolInfo(yytext,"FLOAT","FLOAT");return FLOAT;}
"void" {createNewSymbolInfo(yytext,"VOID","VOID");return VOID;}
"struct" {createNewSymbolInfo(yytext,"STRUCT","STRUCT");return STRUCT;}


{NEWLINE} {line_count++;}
{DIGIT}+ {
	createNewSymbolInfo(yytext,"CONST_INT","INT");
	return CONST_INT;
}

({DIGIT}+)?(\.?{DIGIT}+)(E[+-]?{DIGIT}+)? {
    createNewSymbolInfo(yytext,"CONST_FLOAT","FLOAT");
	return CONST_FLOAT;
}

({DIGIT}*\.{DIGIT}*\.[0-9E+-\.]*) {
	// error_output("Too many decimal points",yytext);
}

({DIGIT}+)?(\.?{DIGIT}+)E[+-]?([0-9E+-\.]*) {
    // error_output("Ill formed number",yytext);
}







"-"|"+" {createNewSymbolInfo(yytext,"ADDOP","");return ADDOP;}

"*"|"/"|"%"	{createNewSymbolInfo(yytext,"MULOP","");return MULOP;}

"++"|"--" {createNewSymbolInfo(yytext,"INCOP","");return INCOP;}

"<"|"<="|">"|">="|"=="|"!="	{createNewSymbolInfo(yytext,"RELOP","");return RELOP;}

"="  {createNewSymbolInfo(yytext,"ASSIGNOP","");return ASSIGNOP;}

"&&"|"||"  {createNewSymbolInfo(yytext,"LOGICOP","");return LOGICOP;}

"!"  {createNewSymbolInfo(yytext,"NOT","");return NOT;}

"("  {createNewSymbolInfo(yytext,"LPAREN","");return LPAREN;}

")"  {createNewSymbolInfo(yytext,"RPAREN","");return RPAREN;}

"{"  {createNewSymbolInfo(yytext,"LCURL","");return LCURL;}

"}"  {createNewSymbolInfo(yytext,"RCURL","");return RCURL;}

"["  {createNewSymbolInfo(yytext,"LSQUARE","");return LSQUARE;}

"]"  {createNewSymbolInfo(yytext,"RSQUARE","");return RSQUARE;}

","  {createNewSymbolInfo(yytext,"COMMA","");return COMMA;}

";"  {createNewSymbolInfo(yytext,"SEMICOLON","");return SEMICOLON;}






(_|{LETTER})({LETTER}|{DIGIT}|_)* {
    createNewSymbolInfo(yytext,"ID","");
	return ID;
}


{DIGIT}({LETTER}|{DIGIT}|_)* {
    // error_output("Invalid prefix on ID or invalid suffix on Number",yytext);
}
 
{SPACE_} {space_count++;};
{TAB_} {tab_count++;};
{WHITESPACE}+ {}

<<EOF>> {
    return 0;
}

. {
    // error_output("UNRECOGNIZED_CHAR",yytext);
}

%%
