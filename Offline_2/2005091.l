%option noyywrap

%x SINGLE_LINE_COMMENT
%x MULTI_LINE_COMMENT
%x STRING_STATE
%x CHAR_STATE

%{

#include "bits/stdc++.h"
#include "2005091_SymbolTable.h"
#include "2005091_ScopeTable.h"
#include "2005091_SymbolInfo.h"
using namespace std;




string multiline_comment,singleline_comment,WHOLE_STRING,WHOLE_CHAR;
int temLineNo;
int single_line_flag;
int total_error=0,total_warning=0;
int tab_count=0,space_count=0,Indentation_flag=0,required_tab=0;

extern ofstream logout;
extern ofstream errout;
// extern YYSTYPE yylval;
extern SymbolTable* symbolTable;

// external variable ends

void error_output(string errorType,string error){
	logout<<"Error at line "<<yylineno<<": "<<errorType<<" "<<error<<"\n"<<endl;
	errout<<"Error at line "<<yylineno<<": "<<errorType<<" "<<error<<"\n"<<endl;
	error_count++;
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

void printInTokenAndLogFile(string token,string lexem)
{
    tokenout<<"<"<<toUpper(token)<<", "<<lexem<<">"<<endl;
    log_file<<"Line# "<<yylineno<<": Token <"<<toUpper(token)<<"> Lexeme "<<lexem<<" found"<<endl;
}

void printInTokenAndLogFile(string token,char lexem)
{
    tokenout<<"<"<<toUpper(token)<<", "<<lexem<<">"<<endl;
    log_file<<"Line# "<<yylineno<<": Token <"<<toUpper(token)<<"> Lexeme "<<lexem<<" found"<<endl;
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

void check_Indentation()
{
    if(Indentation_flag==0)
    {
        if(space_count)
        {
            log_file<<"Line# "<<yylineno<<": Warning, tab requrired but got space."<<endl;
            total_warning++;
        }
        else
        {
            if(tab_count!=required_tab)
            {
                log_file<<"Line# "<<yylineno<<": warning, "<<required_tab<<" of tabs needed but got "<<tab_count<<" tabs."<<endl;
                total_warning++;
            }
        }
        Indentation_flag=1;
    }
}
void initilize_values(){tab_count=space_count=Indentation_flag=0;}


%}

KEYWORD if|else|for|while|do|break|int|char|float|double|void|return|switch|case|default|continue
CONST_CHAR '.'|'\\\\'|'\\\''|'\\\"'|'\\n'|'\\t'|'\\a'|'\\f'|'\\r'|'\\b'|'\\v'|'\\0'

SPACE_ [ ]
TAB_ [\t]
WHITESPACE [\f\r\v]+
LETTER [a-zA-Z]
DIGIT [0-9]
NEWLINE \n
%%


{NEWLINE} {check_Indentation();initilize_values();yylineno++;}
{KEYWORD} {
    check_Indentation();
    printInTokenAndLogFile(yytext,yytext);
}
{DIGIT}+ {
    check_Indentation();
    printInTokenAndLogFile("CONST_INT",yytext);
}

({DIGIT}+)?(\.?{DIGIT}+)(E[+-]?{DIGIT}+)? {
    check_Indentation();
    printInTokenAndLogFile("CONST_FLOAT",yytext);
}

({DIGIT}*\.{DIGIT}*\.[0-9E+-\.]*) {
    check_Indentation();
    total_error++;
    log_file<<"Error at line# "<<yylineno<<": TOO_MANY_DECIMAL_POINTS "<<yytext<<endl;
}

({DIGIT}+)?(\.?{DIGIT}+)E[+-]?([0-9E+-\.]*) {
    check_Indentation();
    total_error++;
    log_file<<"Error at line# "<<yylineno<<": ILLFORMED_NUMBER "<<yytext<<endl;
}



\' {
    check_Indentation();
    WHOLE_CHAR="\'";
    temLineNo=yylineno;
    BEGIN(CHAR_STATE);
}
<CHAR_STATE>\\\\ {WHOLE_CHAR+="\\\\";}
<CHAR_STATE>\\\' {WHOLE_CHAR+="\\\'";}


<CHAR_STATE>\r\n {
    initilize_values(); //for Indentation
    total_error++;
    log_file<<"Error at line# "<<yylineno<<": UNFINISHED_CONST_CHAR "<<WHOLE_CHAR<<endl;
    yylineno++;
    BEGIN(INITIAL);
}


<CHAR_STATE>\' {
    WHOLE_CHAR+="\'";
    if(WHOLE_CHAR.size()>4)
    {
        total_error++;
        log_file<<"Error at line# "<<yylineno<<": MULTICHAR_CONST_CHAR "<<WHOLE_CHAR<<endl;
    }
    else if(WHOLE_CHAR.size()==4&&WHOLE_CHAR[1]!='\\')
    {
        total_error++;
        log_file<<"Error at line# "<<yylineno<<": MULTICHAR_CONST_CHAR "<<WHOLE_CHAR<<endl;
    }
    else if(WHOLE_CHAR.size()==2)
    {
        total_error++;
        log_file<<"Error at line# "<<yylineno<<": EMPTY_CONST_CHAR ''"<<endl;
    }
    else
    {
        char ch; 
        if(WHOLE_CHAR.size()==4) 
        { 
            ch=character_func(WHOLE_CHAR[2]); 
        } 
        else ch=WHOLE_CHAR[1]; 
        printInTokenAndLogFile("CONST_CHAR",ch); 
    }
    BEGIN(INITIAL);
}
<CHAR_STATE><<EOF>> {
    total_error++;
    log_file<<"Error at line# "<<yylineno<<": UNFINISHED_CONST_CHAR "<<WHOLE_CHAR<<endl;
    BEGIN(INITIAL);
}
<CHAR_STATE>. {WHOLE_CHAR+=yytext[0];}






"-"|"+" {check_Indentation();printInTokenAndLogFile("ADDOP",yytext);}

"*"|"/"|"%"	{check_Indentation();printInTokenAndLogFile("MULOP",yytext);}

"++"|"--" {check_Indentation();printInTokenAndLogFile("INCOP",yytext);}

"<"|"<="|">"|">="|"=="|"!="	{check_Indentation();printInTokenAndLogFile("RELOP",yytext);}

"="	{check_Indentation();printInTokenAndLogFile("ASSIGNOP",yytext);}

"&&"|"||" {check_Indentation();printInTokenAndLogFile("LOGICOP",yytext);}

"&"|"|"|"^"|"<<"|">>" {check_Indentation();printInTokenAndLogFile("BITOP",yytext);}

"!"	{check_Indentation();printInTokenAndLogFile("NOT",yytext);}

"("	{check_Indentation();printInTokenAndLogFile("LPAREN",yytext);}

")"	{check_Indentation();printInTokenAndLogFile("RPAREN",yytext);}

"{"	{
    check_Indentation();
    printInTokenAndLogFile("LCURL",yytext);
    symbolTable.EnterNewScope();
    required_tab++;
}

"}"	{
    printInTokenAndLogFile("RCURL",yytext);
    symbolTable.ExitScope();
    required_tab--;
    check_Indentation();
}

"["	{check_Indentation();printInTokenAndLogFile("LSQUARE",yytext);}

"]"	{check_Indentation();printInTokenAndLogFile("RSQUARE",yytext);}

","	{check_Indentation();printInTokenAndLogFile("COMMA",yytext);}

";"	{check_Indentation();printInTokenAndLogFile("SEMICOLON",yytext);}





(_|{LETTER})({LETTER}|{DIGIT}|_)* {
    check_Indentation();
    printInTokenAndLogFile("ID",yytext);
    if(symbolTable.InsertNewSymbolInfo(yytext,"ID"))
    {
        symbolTable.PrintAllScopeTable(log_file);
    }
    else
    {
        log_file<<"\t"<<yytext<<" already exists in the current ScopeTable"<<endl;
    }
}


{DIGIT}({LETTER}|{DIGIT}|_)* {
    check_Indentation();
    total_error++;
    log_file<<"Error at line# "<<yylineno<<": INVALID_ID_SUFFIX_NUM_PREFIX "<<yytext<<endl;
}




\/\/ {
    check_Indentation();
    temLineNo=yylineno;
    singleline_comment="//";
    BEGIN(SINGLE_LINE_COMMENT);
}
<SINGLE_LINE_COMMENT>\\\r\n {initilize_values();singleline_comment+="\\\n";yylineno++;}

<SINGLE_LINE_COMMENT>\r\n {
    initilize_values(); //for Indentation
    log_file<<"Line# "<<temLineNo<<": Token " <<"<SINGLE LINE COMMENT>"<<" Lexeme "<<singleline_comment<<" found"<<endl;
    yylineno++;
    BEGIN(INITIAL);
}
<SINGLE_LINE_COMMENT><<EOF>> {
    log_file<<"Line# "<<temLineNo<<": Token " <<"<SINGLE LINE COMMENT>"<<" Lexeme "<<singleline_comment<<" found"<<endl;
    BEGIN(INITIAL);
}
<SINGLE_LINE_COMMENT>. {singleline_comment+=yytext[0];}



\/\* {
    check_Indentation();
    multiline_comment="/*";
    temLineNo=yylineno;
    BEGIN(MULTI_LINE_COMMENT);
}
<MULTI_LINE_COMMENT>\n {multiline_comment+="\n";yylineno++;}
<MULTI_LINE_COMMENT>\*\/ {
    multiline_comment+="*/";
    log_file<<"Line# "<<temLineNo<<": Token " <<"<MULTI LINE COMMENT>"<<" Lexeme "<<multiline_comment<<" found"<<endl;
    BEGIN(INITIAL);
}
<MULTI_LINE_COMMENT><<EOF>> {
    total_error++;
    log_file<<"Error at line# "<<yylineno<<": UNFINISHED_COMMENT "<<multiline_comment<<endl;
    BEGIN(INITIAL);
}
<MULTI_LINE_COMMENT>. {multiline_comment+=yytext[0];}




\" {
    check_Indentation();
    WHOLE_STRING="\"";
    temLineNo=yylineno;
    single_line_flag=1;
    BEGIN(STRING_STATE);
}
<STRING_STATE>\\\\ {WHOLE_STRING+="\\\\";}
<STRING_STATE>\\\r\n {WHOLE_STRING+="\\\n";yylineno++;single_line_flag=0;}
<STRING_STATE>\\\" {WHOLE_STRING+="\\\"";}


<STRING_STATE>\r\n {
    initilize_values(); //for Indentation
    total_error++;
    log_file<<"Error at line# "<<yylineno<<": UNFINISHED_STRING "<<WHOLE_STRING<<endl;
    yylineno++;
    BEGIN(INITIAL);
}

<STRING_STATE>\" {
    WHOLE_STRING+="\"";
    if(single_line_flag)log_file<<"Line# "<<temLineNo<<": Token " <<"<SINGLE LINE STRING>"<<" Lexeme "<<WHOLE_STRING<<" found"<<endl;
    else log_file<<"Line# "<<temLineNo<<": Token " <<"<MULTI LINE STRING>"<<" Lexeme "<<WHOLE_STRING<<" found"<<endl;
    int flag=0;
    int n=WHOLE_STRING.size();
    string token_string;
    for(int i=1;i<n-1;i++)
    {
        char ch=WHOLE_STRING[i];
        char ch1=WHOLE_STRING[i+1];
        if(!((ch=='\\'&&ch1=='\n')||(ch=='\n')))
        {
            token_string.push_back(ch);
        }
    }

    n=token_string.size();
    string final_token_string;
    for(int i=0;i<n;i++)
    {
        if(token_string[i]=='\\')
        {
            i++;
            final_token_string.push_back(character_func(token_string[i]));
        }
        else final_token_string.push_back(token_string[i]);
    }
    if(single_line_flag)tokenout<<"<"<<toUpper("SINGLE LINE STRING")<<", "<<final_token_string<<">"<<endl;
    else tokenout<<"<"<<toUpper("MULTI LINE STRING")<<", "<<final_token_string<<">"<<endl;
    BEGIN(INITIAL);
}
<STRING_STATE><<EOF>> {
    total_error++;
    log_file<<"Error at line# "<<yylineno<<": UNFINISHED_STRING "<<WHOLE_STRING<<endl;
    BEGIN(INITIAL);
}
<STRING_STATE>. {WHOLE_STRING+=yytext[0];}

 
{SPACE_} {space_count++;};
{TAB_} {tab_count++;};
{WHITESPACE}+ {}

. {
    check_Indentation();
    total_error++;
    log_file<<"Error at line# "<<yylineno<<": UNRECOGNIZED_CHAR "<<yytext<<endl;
}

%%

int main(int argc,char *argv[]){
	
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}

	tokenout.open("2005091_token.txt");
	log_file.open("2005091_log.txt");

	yyin= fin;
    yylineno=1;
	yylex();
	fclose(yyin);

    symbolTable.PrintAllScopeTable(log_file);
    log_file<<"Total lines: "<<yylineno<<endl;
    log_file<<"Total errors: "<<total_error<<endl;
    log_file<<"Total warnings: "<<total_warning<<endl;

	
	tokenout.close();
	log_file.close();
	return 0;
}