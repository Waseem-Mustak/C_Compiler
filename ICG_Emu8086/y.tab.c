/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "2005091.y"

#include <bits/stdc++.h>
#include <typeinfo>

#include "2005091_SymbolInfo.h"
#include "2005091_SymbolTable.h"
#include "2005091_ScopeTable.h"

using namespace std;

ofstream logout;
ofstream errorout;
ofstream parseout;
ofstream codeout;
ofstream optout;

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

bool isVoidTypeSpecifier(SymbolInfo* typeSpecifier){
	if( typeSpecifier->getTypeSpecifier() == "VOID" ){
		return true;
	}
	return false;
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

string currentFunction;
void functionCheck(SymbolInfo* nameOfFunction,SymbolInfo* typeSpecifier)
{
    nameOfFunction->setIsFunction(true);
	nameOfFunction->setTypeSpecifier(typeSpecifier->getTypeSpecifier());
	nameOfFunction->setParameterList(symbolInfoArguments->getParameterList());
		
    currentFunction = nameOfFunction->getName();  

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




// intermediate code generation

bool hasMain = false;

vector<string> globalVariables;

int LABEL_COUNTER = 0;

int getLabelCounter(){
	
	return LABEL_COUNTER;
}
string newLabel(){
	LABEL_COUNTER++;
	return "label"+to_string(LABEL_COUNTER);
}
string getOpcode(string op){
	string opcode = "";
	if(op == "<") opcode ="JL";
	else if(op == ">") opcode ="JG";
	else if(op == ">=") opcode ="JGE";
	else if(op == "<=") opcode ="JLE";
	else if(op == "==") opcode ="JE";
	else if(op == "!=") opcode ="JNE";
	return opcode;
}

vector<string> get3address(string code){


	string stripped = code;
	while(stripped[stripped.size()-1] == ' ' or stripped[stripped.size()-1] == '\t' ) stripped.pop_back();
	reverse(stripped.begin(),stripped.end());
	while(stripped[stripped.size()-1] == ' ' or stripped[stripped.size()-1] == '\t' ) stripped.pop_back();
	reverse(stripped.begin(),stripped.end());

	vector<string> codes,codes2;
	vector<string> ret;
	stringstream ss(stripped);
 
    while (ss.good()) {
        string substr;
        getline(ss, substr, ' ');
        codes.push_back(substr);
    }
	if( codes.size()>0 ) ret.push_back(codes[0]);
	else ret.push_back("");
	if( codes.size()>1 ){
		stringstream ss(codes[1]);
		while (ss.good()) {
			string substr;
			getline(ss, substr, ',');
			codes2.push_back(substr);
		}	
	}
	if( codes2.size() == 0 ) {
		ret.push_back("");ret.push_back("");
	}else if( codes2.size() == 1 ){
		ret.push_back(codes2[0]);ret.push_back("");
	}else{
		ret.push_back(codes2[0]);
		ret.push_back(codes2[1]);
	}
	ret.push_back(code);
	// cout<<ret[0]<<" | "<<ret[1]<<" | "<<ret[2]<<endl;
	return ret;

}
// void optimizeCode(string code){
// 	// removing redundant move T - T
// 	vector<string> codes;
// 	stringstream ss(code);
// 	vector<vector<string>> optimized;
 
//     while (ss.good()) {
//         string substr;
//         getline(ss, substr, '\n');
//         codes.push_back(substr);
//     }
// 	for(auto code:codes) get3address(code);
// 	int lines = codes.size();
// 	// cout<<"debug line count::"<<lines<<endl;

// 	vector<string> prevthadd = {"","",""};
// 	for(int i=0;i<lines;i++){
// 		if( codes[i][0] == ';' ){
// 			auto thadd = get3address(codes[i]);
// 			optimized.push_back(thadd);
// 			continue;
// 		}

		
// 		vector<string> thadd = get3address(codes[i]);
// 		if( optimized.size() == 0 ){
// 			optimized.push_back(thadd);
// 			continue;
// 		}

// 	//	cout<<thadd[1]<<"="<<prevthadd[1]<<" "<<(thadd[1] == prevthadd[1])<<" || "<<thadd[2]<<"="<<prevthadd[2]<<" "<<(thadd[2] == prevthadd[2])<<endl;
// 		auto prevthadd = optimized.back();
// 		if( thadd[0] == "MOV" and prevthadd[0] == "MOV" ){
// 			if( thadd[1] == prevthadd[1] and thadd[2] == prevthadd[2] ){
// 				cout<<"optimized :) "<<endl;
// 			}else if(thadd[1] == prevthadd[2] and thadd[2] == prevthadd[1]){
// 				cout<<"optimized :) "<<endl;
// 			}else{
// 				optimized.push_back(thadd);
// 			}
// 		}else if( thadd[0] == "POP" ){
// 			if( prevthadd[0] == "PUSH" ){
// 				cout<<"optimized POP :) "<<endl;
// 				optimized.pop_back();
// 			}else{
				
// 				optimized.push_back(thadd);
// 			}
// 		}else{
// 			optimized.push_back(thadd);
		
// 		}

// 	}
// 	for(auto thadd:optimized){
// 		optout<<thadd[3]<<endl;
// 	}
// }





#line 336 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IF = 258,                      /* IF  */
    ELSE = 259,                    /* ELSE  */
    LOWER_THAN_ELSE = 260,         /* LOWER_THAN_ELSE  */
    FOR = 261,                     /* FOR  */
    STRUCT = 262,                  /* STRUCT  */
    WHILE = 263,                   /* WHILE  */
    RETURN = 264,                  /* RETURN  */
    PRINTLN = 265,                 /* PRINTLN  */
    INCOP = 266,                   /* INCOP  */
    DECOP = 267,                   /* DECOP  */
    ASSIGNOP = 268,                /* ASSIGNOP  */
    NOT = 269,                     /* NOT  */
    LPAREN = 270,                  /* LPAREN  */
    RPAREN = 271,                  /* RPAREN  */
    LCURL = 272,                   /* LCURL  */
    RCURL = 273,                   /* RCURL  */
    LSQUARE = 274,                 /* LSQUARE  */
    RSQUARE = 275,                 /* RSQUARE  */
    COMMA = 276,                   /* COMMA  */
    SEMICOLON = 277,               /* SEMICOLON  */
    INT = 278,                     /* INT  */
    FLOAT = 279,                   /* FLOAT  */
    VOID = 280,                    /* VOID  */
    CONST_INT = 281,               /* CONST_INT  */
    CONST_FLOAT = 282,             /* CONST_FLOAT  */
    ID = 283,                      /* ID  */
    ADDOP = 284,                   /* ADDOP  */
    MULOP = 285,                   /* MULOP  */
    RELOP = 286,                   /* RELOP  */
    LOGICOP = 287                  /* LOGICOP  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define IF 258
#define ELSE 259
#define LOWER_THAN_ELSE 260
#define FOR 261
#define STRUCT 262
#define WHILE 263
#define RETURN 264
#define PRINTLN 265
#define INCOP 266
#define DECOP 267
#define ASSIGNOP 268
#define NOT 269
#define LPAREN 270
#define RPAREN 271
#define LCURL 272
#define RCURL 273
#define LSQUARE 274
#define RSQUARE 275
#define COMMA 276
#define SEMICOLON 277
#define INT 278
#define FLOAT 279
#define VOID 280
#define CONST_INT 281
#define CONST_FLOAT 282
#define ID 283
#define ADDOP 284
#define MULOP 285
#define RELOP 286
#define LOGICOP 287

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 268 "2005091.y"

    SymbolInfo* symbolInfo; 

#line 457 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_LOWER_THAN_ELSE = 5,            /* LOWER_THAN_ELSE  */
  YYSYMBOL_FOR = 6,                        /* FOR  */
  YYSYMBOL_STRUCT = 7,                     /* STRUCT  */
  YYSYMBOL_WHILE = 8,                      /* WHILE  */
  YYSYMBOL_RETURN = 9,                     /* RETURN  */
  YYSYMBOL_PRINTLN = 10,                   /* PRINTLN  */
  YYSYMBOL_INCOP = 11,                     /* INCOP  */
  YYSYMBOL_DECOP = 12,                     /* DECOP  */
  YYSYMBOL_ASSIGNOP = 13,                  /* ASSIGNOP  */
  YYSYMBOL_NOT = 14,                       /* NOT  */
  YYSYMBOL_LPAREN = 15,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 16,                    /* RPAREN  */
  YYSYMBOL_LCURL = 17,                     /* LCURL  */
  YYSYMBOL_RCURL = 18,                     /* RCURL  */
  YYSYMBOL_LSQUARE = 19,                   /* LSQUARE  */
  YYSYMBOL_RSQUARE = 20,                   /* RSQUARE  */
  YYSYMBOL_COMMA = 21,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 22,                 /* SEMICOLON  */
  YYSYMBOL_INT = 23,                       /* INT  */
  YYSYMBOL_FLOAT = 24,                     /* FLOAT  */
  YYSYMBOL_VOID = 25,                      /* VOID  */
  YYSYMBOL_CONST_INT = 26,                 /* CONST_INT  */
  YYSYMBOL_CONST_FLOAT = 27,               /* CONST_FLOAT  */
  YYSYMBOL_ID = 28,                        /* ID  */
  YYSYMBOL_ADDOP = 29,                     /* ADDOP  */
  YYSYMBOL_MULOP = 30,                     /* MULOP  */
  YYSYMBOL_RELOP = 31,                     /* RELOP  */
  YYSYMBOL_LOGICOP = 32,                   /* LOGICOP  */
  YYSYMBOL_YYACCEPT = 33,                  /* $accept  */
  YYSYMBOL_start = 34,                     /* start  */
  YYSYMBOL_program = 35,                   /* program  */
  YYSYMBOL_unit = 36,                      /* unit  */
  YYSYMBOL_struct_definition = 37,         /* struct_definition  */
  YYSYMBOL_var_declaration1 = 38,          /* var_declaration1  */
  YYSYMBOL_func_declaration = 39,          /* func_declaration  */
  YYSYMBOL_func_definition = 40,           /* func_definition  */
  YYSYMBOL_41_1 = 41,                      /* $@1  */
  YYSYMBOL_42_2 = 42,                      /* $@2  */
  YYSYMBOL_parameter_list = 43,            /* parameter_list  */
  YYSYMBOL_compound_statement = 44,        /* compound_statement  */
  YYSYMBOL_var_declaration = 45,           /* var_declaration  */
  YYSYMBOL_type_specifier = 46,            /* type_specifier  */
  YYSYMBOL_declaration_list = 47,          /* declaration_list  */
  YYSYMBOL_statements = 48,                /* statements  */
  YYSYMBOL_statement = 49,                 /* statement  */
  YYSYMBOL_expression_statement = 50,      /* expression_statement  */
  YYSYMBOL_variable = 51,                  /* variable  */
  YYSYMBOL_expression = 52,                /* expression  */
  YYSYMBOL_logic_expression = 53,          /* logic_expression  */
  YYSYMBOL_rel_expression = 54,            /* rel_expression  */
  YYSYMBOL_simple_expression = 55,         /* simple_expression  */
  YYSYMBOL_term = 56,                      /* term  */
  YYSYMBOL_unary_expression = 57,          /* unary_expression  */
  YYSYMBOL_factor = 58,                    /* factor  */
  YYSYMBOL_argument_list = 59,             /* argument_list  */
  YYSYMBOL_arguments = 60,                 /* arguments  */
  YYSYMBOL_lcurl = 61                      /* lcurl  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   175

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  130

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   287


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   283,   283,   308,   312,   318,   322,   326,   330,   335,
     342,   346,   350,   362,   374,   374,   407,   407,   436,   443,
     451,   457,   464,   476,   482,   523,   526,   529,   533,   538,
     544,   548,   554,   558,   563,   567,   574,   578,   599,   618,
     638,   656,   687,   697,   701,   706,   720,   760,   765,   784,
     790,   809,   815,   841,   847,   863,   869,   903,   915,   934,
     941,   948,   977,   981,   985,   989,  1003,  1016,  1022,  1026,
    1034,  1042
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE",
  "LOWER_THAN_ELSE", "FOR", "STRUCT", "WHILE", "RETURN", "PRINTLN",
  "INCOP", "DECOP", "ASSIGNOP", "NOT", "LPAREN", "RPAREN", "LCURL",
  "RCURL", "LSQUARE", "RSQUARE", "COMMA", "SEMICOLON", "INT", "FLOAT",
  "VOID", "CONST_INT", "CONST_FLOAT", "ID", "ADDOP", "MULOP", "RELOP",
  "LOGICOP", "$accept", "start", "program", "unit", "struct_definition",
  "var_declaration1", "func_declaration", "func_definition", "$@1", "$@2",
  "parameter_list", "compound_statement", "var_declaration",
  "type_specifier", "declaration_list", "statements", "statement",
  "expression_statement", "variable", "expression", "logic_expression",
  "rel_expression", "simple_expression", "term", "unary_expression",
  "factor", "argument_list", "arguments", "lcurl", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-77)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      26,   -22,   -77,   -77,   -77,    15,    26,   -77,   -77,   -77,
     -77,   -77,     0,     5,   -77,   -77,     1,    32,    51,    36,
       9,    12,   -77,   140,   -77,    28,    25,    -3,    30,    17,
      43,    41,   -77,    60,   -77,    53,    75,    51,   -77,   -77,
      76,   -77,   -77,   -77,    63,   -77,    53,    73,    86,    88,
      94,    95,   123,    96,   123,   123,   -77,   -77,   -77,   -77,
      19,   123,   -77,   -77,    90,   -77,   -77,    71,    99,   -77,
      92,    -6,    98,   -77,   -77,   -77,   -77,   -77,   123,   133,
     123,   100,   101,    83,   -77,   114,   123,   123,   -77,   -77,
     -77,   -77,   -77,   123,   -77,   123,   123,   123,   123,   119,
     133,   120,   -77,   137,   -77,   -77,   138,   112,   136,   -77,
     -77,    98,   128,   -77,   117,   123,   117,   144,   -77,   123,
     -77,   163,   152,   -77,   -77,   -77,   117,   117,   -77,   -77
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    25,    26,    27,     0,     2,     4,     8,     6,
       7,     5,     0,     0,     1,     3,    30,     0,     0,     0,
       0,     0,    24,     0,    10,     0,    16,     0,    21,     0,
      28,     0,    11,    30,    13,     0,    14,     0,    20,    31,
       0,     9,    71,    17,     0,    12,     0,    19,     0,     0,
       0,     0,     0,     0,     0,     0,    23,    43,    63,    64,
      45,     0,    36,    34,     0,    32,    35,    60,     0,    47,
      49,    51,    53,    55,    59,    15,    18,    29,     0,     0,
       0,     0,     0,    60,    58,     0,    68,     0,    57,    22,
      33,    65,    66,     0,    44,     0,     0,     0,     0,     0,
       0,     0,    42,     0,    62,    70,     0,    67,     0,    48,
      50,    54,    52,    56,     0,     0,     0,     0,    61,     0,
      46,    38,     0,    40,    41,    69,     0,     0,    39,    37
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -77,   -77,   -77,   164,   -77,   -77,   -77,   -77,   -77,   -77,
     -77,   -25,     8,    11,   -77,   -77,   -59,   -76,   -54,   -51,
     -74,    74,    77,    79,   -52,   -77,   -77,   -77,   -77
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     5,     6,     7,     8,    23,     9,    10,    46,    35,
      27,    62,    63,    25,    17,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,   106,   107,    44
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      83,    81,    84,   100,    85,    90,    13,    83,    11,    88,
      43,    12,   105,    36,    11,    14,    19,    12,    37,   109,
      20,    75,    18,    96,   115,    97,    24,    99,    16,   101,
      28,    32,    83,     1,    86,    29,   108,    39,    87,    83,
      30,    83,    83,    83,    83,   125,   113,    34,    47,     2,
       3,     4,    26,    21,    22,   121,    33,   123,    38,     2,
       3,     4,    40,    41,   122,    83,    49,   128,   129,    50,
      42,    51,    52,    53,     2,     3,     4,    54,    55,    20,
      42,    56,    91,    92,    93,    57,     2,     3,     4,    58,
      59,    60,    61,    49,    91,    92,    50,    45,    51,    52,
      53,    76,    48,    78,    54,    55,    77,    42,    89,    79,
      80,    82,    57,     2,     3,     4,    58,    59,    60,    61,
      49,    94,   102,    50,    95,    51,    52,    53,    98,   103,
     104,    54,    55,   119,    42,   114,   116,    54,    55,    57,
       2,     3,     4,    58,    59,    60,    61,    54,    55,    58,
      59,    60,    61,   117,   118,    57,   120,    96,    31,    58,
      59,    60,    61,     2,     3,     4,   124,   126,   127,   110,
      15,     0,     0,     0,   112,   111
};

static const yytype_int8 yycheck[] =
{
      54,    52,    54,    79,    55,    64,    28,    61,     0,    61,
      35,     0,    86,    16,     6,     0,    15,     6,    21,    93,
      19,    46,    17,    29,   100,    31,    18,    78,    28,    80,
      19,    23,    86,     7,    15,    26,    87,    20,    19,    93,
      28,    95,    96,    97,    98,   119,    98,    22,    37,    23,
      24,    25,    16,    21,    22,   114,    28,   116,    28,    23,
      24,    25,    19,    22,   115,   119,     3,   126,   127,     6,
      17,     8,     9,    10,    23,    24,    25,    14,    15,    19,
      17,    18,    11,    12,    13,    22,    23,    24,    25,    26,
      27,    28,    29,     3,    11,    12,     6,    22,     8,     9,
      10,    28,    26,    15,    14,    15,    20,    17,    18,    15,
      15,    15,    22,    23,    24,    25,    26,    27,    28,    29,
       3,    22,    22,     6,    32,     8,     9,    10,    30,    28,
      16,    14,    15,    21,    17,    16,    16,    14,    15,    22,
      23,    24,    25,    26,    27,    28,    29,    14,    15,    26,
      27,    28,    29,    16,    16,    22,    20,    29,    18,    26,
      27,    28,    29,    23,    24,    25,    22,     4,    16,    95,
       6,    -1,    -1,    -1,    97,    96
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,    23,    24,    25,    34,    35,    36,    37,    39,
      40,    45,    46,    28,     0,    36,    28,    47,    17,    15,
      19,    21,    22,    38,    45,    46,    16,    43,    46,    26,
      28,    18,    45,    28,    22,    42,    16,    21,    28,    20,
      19,    22,    17,    44,    61,    22,    41,    46,    26,     3,
       6,     8,     9,    10,    14,    15,    18,    22,    26,    27,
      28,    29,    44,    45,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    44,    28,    20,    15,    15,
      15,    52,    15,    51,    57,    52,    15,    19,    57,    18,
      49,    11,    12,    13,    22,    32,    29,    31,    30,    52,
      50,    52,    22,    28,    16,    53,    59,    60,    52,    53,
      54,    56,    55,    57,    16,    50,    16,    16,    16,    21,
      20,    49,    52,    49,    22,    53,     4,    16,    49,    49
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    33,    34,    35,    35,    36,    36,    36,    36,    37,
      38,    38,    39,    39,    41,    40,    42,    40,    43,    43,
      43,    43,    44,    44,    45,    46,    46,    46,    47,    47,
      47,    47,    48,    48,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    50,    50,    51,    51,    52,    52,    53,
      53,    54,    54,    55,    55,    56,    56,    57,    57,    57,
      58,    58,    58,    58,    58,    58,    58,    59,    59,    60,
      60,    61
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     6,
       1,     2,     6,     5,     0,     7,     0,     6,     4,     3,
       2,     1,     3,     2,     3,     1,     1,     1,     3,     6,
       1,     4,     1,     2,     1,     1,     1,     7,     5,     7,
       5,     5,     3,     1,     2,     1,     4,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     2,     2,     1,
       1,     4,     3,     1,     1,     2,     2,     1,     0,     3,
       1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* start: program  */
#line 283 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"start","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                        (yyval.symbolInfo)->printParseTree(parseout,0); 

                                                        if(total_error == 0){
                                                            (yyval.symbolInfo)->code = (yyvsp[0].symbolInfo)->code;
                                                            codeout<<".MODEL SMALL\n.STACK 1000H\n.DATA\n\tFIXED_POINT_MULTIPLIER DW 64H\n\tCR EQU 0Dh\n\tLF EQU 0Ah\n\tNEWLINEM DB CR,LF,'$'\n\tTEN DW 10\n";
                                                            optout<<".MODEL SMALL\n.STACK 1000H\n.DATA\n\tFIXED_POINT_MULTIPLIER DW 64H\n\tCR EQU 0Dh\n\tLF EQU 0Ah\n\tNEWLINEM DB CR,LF,'$'\n\tTEN DW 10\n";
                                                            for(auto variable:globalVariables){
                                                                codeout<<'\t'<<variable<<" DW 0\n";
                                                                optout<<'\t'<<variable<<" DW 0\n";
                                                            }
                                                            codeout<<"\n\n\nNEWLINE PROC \n\t\n\tPUSH AX\n\tPUSH DX\n\t\n\tLEA DX, NEWLINEM\n\tMOV AH,9\n\tINT 21h\n\t\n\tPOP DX\n\tPOP AX \n\tRET\n   \nNEWLINE ENDP\n\nPRINTNUMBER PROC\n\tPUSH CX\n\tMOV CX,0   \n\t\n\tCMP AX,0\t\t\t \n\tJG PRINTNUMBER_START \n\t\n\tCMP AX,0\n\tJNE NOT_ZERO\n\tMOV DX,0\n\tADD DL,'0'\n\tMOV AH, 02H\n\tINT 21H\nCALL NEWLINE \n\tPOP CX  \n\tRET\n\t\n\t\n\tNOT_ZERO:\n\tPUSH AX\n\tMOV DX,'-'\n\tMOV AH, 02H\n\tINT 21H \n\tPOP AX  \n\tNEG AX\n\t\n\tPRINTNUMBER_START:\n\tCMP AX,0\n\tJE PRINTNUMBER_END \n\t\n\tXOR DX, DX\n\tDIV TEN\n\tADD DL, '0'\n\tPUSH DX\n\tINC CX\n\tJMP PRINTNUMBER_START\n\t\n\tPRINTNUMBER_END:\n\t\n\tPRINTNUMBER_LOOP:\n\t\t\n\t\tPOP DX\n\t\tMOV AH, 02H\n\t\tINT 21H\n\t\n\tLOOP PRINTNUMBER_LOOP\nCALL NEWLINE \n\tPOP CX\n\tRET\n\t\nPRINTNUMBER ENDP\n\n";
                                                            optout<<"\n\n\nNEWLINE PROC \n\t\n\tPUSH AX\n\tPUSH DX\n\t\n\tLEA DX, NEWLINEM\n\tMOV AH,9\n\tINT 21h\n\t\n\tPOP DX\n\tPOP AX \n\tRET\n   \nNEWLINE ENDP\n\nPRINTNUMBER PROC\n\tPUSH CX\n\tMOV CX,0   \n\t\n\tCMP AX,0\t\t\t \n\tJG PRINTNUMBER_START \n\t\n\tCMP AX,0\n\tJNE NOT_ZERO\n\tMOV DX,0\n\tADD DL,'0'\n\tMOV AH, 02H\n\tINT 21H\nCALL NEWLINE \n\tPOP CX  \n\tRET\n\t\n\t\n\tNOT_ZERO:\n\tPUSH AX\n\tMOV DX,'-'\n\tMOV AH, 02H\n\tINT 21H \n\tPOP AX  \n\tNEG AX\n\t\n\tPRINTNUMBER_START:\n\tCMP AX,0\n\tJE PRINTNUMBER_END \n\t\n\tXOR DX, DX\n\tDIV TEN\n\tADD DL, '0'\n\tPUSH DX\n\tINC CX\n\tJMP PRINTNUMBER_START\n\t\n\tPRINTNUMBER_END:\n\t\n\tPRINTNUMBER_LOOP:\n\t\t\n\t\tPOP DX\n\t\tMOV AH, 02H\n\t\tINT 21H\n\t\n\tLOOP PRINTNUMBER_LOOP\nCALL NEWLINE \n\tPOP CX\n\tRET\n\t\nPRINTNUMBER ENDP\n\n";
                                                            codeout<<(yyval.symbolInfo)->code<<endl;
                                                            // optimizeCode($$->code);
                                                            codeout<<"END main\n";
                                                            optout<<"END main\n";
                                                        }



                                                    }
#line 1613 "y.tab.c"
    break;

  case 3: /* program: program unit  */
#line 308 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"program","",(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                        (yyval.symbolInfo)->code = (yyvsp[-1].symbolInfo)->code+(yyvsp[0].symbolInfo)->code;
                                                    }
#line 1622 "y.tab.c"
    break;

  case 4: /* program: unit  */
#line 312 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"program","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                        (yyval.symbolInfo)->code = (yyvsp[0].symbolInfo)->code;
                                                    }
#line 1631 "y.tab.c"
    break;

  case 5: /* unit: var_declaration  */
#line 318 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"unit","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                        (yyval.symbolInfo)->code = (yyvsp[0].symbolInfo)->code;
                                                    }
#line 1640 "y.tab.c"
    break;

  case 6: /* unit: func_declaration  */
#line 322 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"unit","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                        (yyval.symbolInfo)->code = (yyvsp[0].symbolInfo)->code;
                                                    }
#line 1649 "y.tab.c"
    break;

  case 7: /* unit: func_definition  */
#line 326 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"unit","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                        (yyval.symbolInfo)->code = (yyvsp[0].symbolInfo)->code;
                                                    }
#line 1658 "y.tab.c"
    break;

  case 8: /* unit: struct_definition  */
#line 330 "2005091.y"
                                                      {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"unit","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                    }
#line 1666 "y.tab.c"
    break;

  case 9: /* struct_definition: STRUCT ID LCURL var_declaration1 RCURL SEMICOLON  */
#line 335 "2005091.y"
                                                                     {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-5].symbolInfo),(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"struct_definition","",(yyvsp[-5].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-5].symbolInfo),(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                    }
#line 1674 "y.tab.c"
    break;

  case 10: /* var_declaration1: var_declaration  */
#line 342 "2005091.y"
                                   {
        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"var_declaration1","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
}
#line 1682 "y.tab.c"
    break;

  case 11: /* var_declaration1: var_declaration1 var_declaration  */
#line 346 "2005091.y"
                                       {
        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"var_declaration1","",(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
    }
#line 1690 "y.tab.c"
    break;

  case 12: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 350 "2005091.y"
                                                                               {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-5].symbolInfo),(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"func_declaration","",(yyvsp[-5].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-5].symbolInfo),(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                        (yyvsp[-4].symbolInfo)->setTypeSpecifier((yyvsp[-5].symbolInfo)->getTypeSpecifier()); 
                                                        (yyvsp[-4].symbolInfo)->setParameterList((yyvsp[-2].symbolInfo)->getParameterList()); 
                                                        (yyvsp[-4].symbolInfo)->setIsFunction(true);
                                                        (yyvsp[-4].symbolInfo)->setIsDeclared(true);
                                                        symbolInfoArguments->setParameterList({}); 
                                                        if(!symbolTable->InsertNewSymbolInfo((yyvsp[-4].symbolInfo)))
                                                        {
                                                            errorPrint("Redeclaring function");
                                                        }
                                                    }
#line 1707 "y.tab.c"
    break;

  case 13: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 362 "2005091.y"
                                                      { 
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"func_declaration","",(yyvsp[-4].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                        (yyvsp[-3].symbolInfo)->setTypeSpecifier((yyvsp[-4].symbolInfo)->getTypeSpecifier()); 
                                                        (yyvsp[-3].symbolInfo)->setIsFunction(true);
                                                        (yyvsp[-3].symbolInfo)->setIsDeclared(true);
                                                        symbolInfoArguments->setParameterList({});
                                                        if(!symbolTable->InsertNewSymbolInfo((yyvsp[-3].symbolInfo)))
                                                        {
                                                            errorPrint("Redeclaring function");
                                                        }
                                                    }
#line 1723 "y.tab.c"
    break;

  case 14: /* $@1: %empty  */
#line 374 "2005091.y"
                                                                  {functionCheck((yyvsp[-3].symbolInfo),(yyvsp[-4].symbolInfo));}
#line 1729 "y.tab.c"
    break;

  case 15: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN $@1 compound_statement  */
#line 374 "2005091.y"
                                                                                                             {
    
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-6].symbolInfo),(yyvsp[-5].symbolInfo),(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo)},"func_definition","",(yyvsp[-6].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-6].symbolInfo),(yyvsp[-5].symbolInfo),(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo)});
                                                        (yyvsp[-5].symbolInfo)->setTypeSpecifier((yyvsp[-6].symbolInfo)->getTypeSpecifier()); 
                                                        (yyvsp[-5].symbolInfo)->setParameterList((yyvsp[-3].symbolInfo)->getParameterList()); 
                                                        (yyvsp[-5].symbolInfo)->setIsFunction(true);
                                                        (yyvsp[-5].symbolInfo)->setIsDeclared(true); 
                                                        symbolInfoArguments->setParameterList({}); 
                                                        symbolTable->InsertNewSymbolInfo((yyvsp[-5].symbolInfo));
                                                        
                                                        //ICG
                                                        (yyval.symbolInfo)->code = "\n\n"+(yyvsp[-5].symbolInfo)->getName() + " PROC\n";
                                                        (yyval.symbolInfo)->code += "\tPUSH BP\n\tMOV BP,SP\n";

                                                        if((yyvsp[-5].symbolInfo)->getName()=="main"){
                                                            hasMain = true;
                                                            (yyval.symbolInfo)->code += "\tMOV AX, @DATA\n\tMOV DS, AX\n\n";
                                                        }
                                                        (yyval.symbolInfo)->code += (yyvsp[-3].symbolInfo)->code+"\n";
                                                        (yyval.symbolInfo)->code += (yyvsp[0].symbolInfo)->code+"\n";
                                                        (yyval.symbolInfo)->code+=(yyvsp[-5].symbolInfo)->getName()+"_exit:\n";
                                                        (yyval.symbolInfo)->code +="\tADD SP,"+to_string(-(yyvsp[0].symbolInfo)->stackOffset)+"\n";
                                                        (yyval.symbolInfo)->code += "\tPOP BP\n";
                                                        
                                                        if((yyvsp[-5].symbolInfo)->getName()=="main"){
                                                            (yyval.symbolInfo)->code+="\tMOV AH,4ch\nINT 21h\n\n";
                                                        }else{
                                                            (yyval.symbolInfo)->code += "\tRET\n";
                                                        }
                                                        (yyval.symbolInfo)->code += "\t"+(yyvsp[-5].symbolInfo)->getName()+" ENDP\n";


                                                    }
#line 1767 "y.tab.c"
    break;

  case 16: /* $@2: %empty  */
#line 407 "2005091.y"
                                            {functionCheck((yyvsp[-2].symbolInfo),(yyvsp[-3].symbolInfo));}
#line 1773 "y.tab.c"
    break;

  case 17: /* func_definition: type_specifier ID LPAREN RPAREN $@2 compound_statement  */
#line 407 "2005091.y"
                                                                                       {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-5].symbolInfo),(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo)},"func_definition","",(yyvsp[-5].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-5].symbolInfo),(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo)});
                                                        (yyvsp[-4].symbolInfo)->setTypeSpecifier((yyvsp[-5].symbolInfo)->getTypeSpecifier()); 
                                                        (yyvsp[-4].symbolInfo)->setIsFunction(true);
                                                        (yyvsp[-4].symbolInfo)->setIsDeclared(true); 
                                                        symbolInfoArguments->setParameterList({}); 
                                                        symbolTable->InsertNewSymbolInfo((yyvsp[-4].symbolInfo));

                                                        //ICG
                                                        (yyval.symbolInfo)->code = "\n\n"+(yyvsp[-4].symbolInfo)->getName()+" PROC\n";
                                                        (yyval.symbolInfo)->code += "\tPUSH BP\n\tMOV BP,SP\n";
                                                        if((yyvsp[-4].symbolInfo)->getName()=="main"){
                                                            hasMain = true;
                                                            (yyval.symbolInfo)->code += "\tMOV AX,@DATA\n\tMOV DS,AX\n\n";
                                                        }

                                                        (yyval.symbolInfo)->code += (yyvsp[0].symbolInfo)->code+"\n";
                                                        (yyval.symbolInfo)->code+=(yyvsp[-4].symbolInfo)->getName()+"_exit:\n";
                                                        (yyval.symbolInfo)->code +="\tADD SP,"+to_string(-(yyvsp[0].symbolInfo)->stackOffset)+"\n";
                                                        (yyval.symbolInfo)->code += "\tPOP BP\n";
                                                        if( (yyvsp[-4].symbolInfo)->getName() == "main" )
                                                            (yyval.symbolInfo)->code+="\tMOV AH,4ch\nINT 21h\n\n";
                                                        else 
                                                            (yyval.symbolInfo)->code += "RET\n";
                                                        
                                                        (yyval.symbolInfo)->code += (yyvsp[-4].symbolInfo)->getName()+" ENDP\n";

                                                    }
#line 1806 "y.tab.c"
    break;

  case 18: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 436 "2005091.y"
                                                          {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"parameter_list","",(yyvsp[-3].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                        (yyvsp[0].symbolInfo)->setTypeSpecifier((yyvsp[-1].symbolInfo)->getTypeSpecifier());
                                                        (yyval.symbolInfo)->setParameterList((yyvsp[-3].symbolInfo)->getParameterList()); 
                                                        (yyval.symbolInfo)->addParameter((yyvsp[0].symbolInfo)); 
                                                        symbolInfoArguments->setParameterList((yyval.symbolInfo)->getParameterList()); 
                                                    }
#line 1818 "y.tab.c"
    break;

  case 19: /* parameter_list: parameter_list COMMA type_specifier  */
#line 443 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"parameter_list","",(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                        
                                                        SymbolInfo* tem=new SymbolInfo("","ID",(yyvsp[0].symbolInfo)->getTypeSpecifier(),10000,10000,false,logout,{});
                                                        (yyval.symbolInfo)->setParameterList((yyvsp[-2].symbolInfo)->getParameterList()); 
                                                        (yyval.symbolInfo)->addParameter(tem);
                                                        symbolInfoArguments->setParameterList((yyval.symbolInfo)->getParameterList()); 
                                                    }
#line 1831 "y.tab.c"
    break;

  case 20: /* parameter_list: type_specifier ID  */
#line 451 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"parameter_list","",(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                        (yyvsp[0].symbolInfo)->setTypeSpecifier((yyvsp[-1].symbolInfo)->getTypeSpecifier());
                                                        (yyval.symbolInfo)->addParameter((yyvsp[0].symbolInfo));
                                                        symbolInfoArguments->setParameterList((yyval.symbolInfo)->getParameterList());
                                                    }
#line 1842 "y.tab.c"
    break;

  case 21: /* parameter_list: type_specifier  */
#line 457 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"parameter_list","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)}); 
                                                        SymbolInfo* tem=new SymbolInfo("","ID",(yyvsp[0].symbolInfo)->getTypeSpecifier(),10000,10000,false,logout,{});
                                                        (yyval.symbolInfo)->addParameter(tem); 
                                                        symbolInfoArguments->setParameterList((yyval.symbolInfo)->getParameterList()); 
                                                    }
#line 1853 "y.tab.c"
    break;

  case 22: /* compound_statement: lcurl statements RCURL  */
#line 464 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"compound_statement","",(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                        
                                                        //ICG
                                                        (yyval.symbolInfo)->code = (yyvsp[-1].symbolInfo)->code;
                                                        (yyval.symbolInfo)->code += (yyvsp[0].symbolInfo)->code;
                                                        (yyval.symbolInfo)->stackOffset = symbolTable->getCurrentScopeTable()->stackOffset; 
		
                                                        //ICG
                                                        symbolTable->PrintAllScopeTable(logout);
                                                        symbolTable->ExitScope();
                                                    }
#line 1870 "y.tab.c"
    break;

  case 23: /* compound_statement: lcurl RCURL  */
#line 476 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"compound_statement","",(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                        symbolTable->PrintAllScopeTable(logout);
                                                        symbolTable->ExitScope();
                                                    }
#line 1880 "y.tab.c"
    break;

  case 24: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 482 "2005091.y"
                                                             {
                                                    (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"var_declaration","",(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                    for(auto va:(yyvsp[-1].symbolInfo)->getDeclarationList())
                                                    {
                                                        va->setTypeSpecifier((yyvsp[-2].symbolInfo)->getTypeSpecifier());
                                                    }
                                                    for(auto va:(yyvsp[-1].symbolInfo)->getDeclarationList())
                                                    {
                                                        if(va->getTypeSpecifier()=="VOID") {
                                                            errorPrint("Variable or field '"+ va->getName()+"' declared void");
                                                        }
                                                        else if(!symbolTable->InsertNewSymbolInfo(va)) {
                                                            errorPrint("Conflicting types for\'"+va->getName()+"\'");
                                                        }	
                                                    }

                                                    //ICG
                                                    string comment = (yyval.symbolInfo)->getName();
                                                    std::replace( comment.begin(), comment.end(), '\n', ' '); // replace all 'x' to 'y'
                                                    (yyval.symbolInfo)->code += "; "+comment+"\n";

                                                    if( !isVoidTypeSpecifier((yyvsp[-2].symbolInfo)) ){
                                                        for(auto symbolInfo:(yyvsp[-1].symbolInfo)->getDeclarationList()){
                                                            symbolInfo->setTypeSpecifier((yyvsp[-2].symbolInfo)->getTypeSpecifier());
                                                            
                                                            bool inserted = symbolTable->InsertNewSymbolInfo(symbolInfo);
                                                            if( !inserted ){
                                                                // print("Multiple declaration of",symbolInfo->getName());
                                                            }else if(symbolTable->getCurrentScopeTable()->getScopeId() == "1"){
                                                                symbolInfo->stackOffset = 0;
                                                                globalVariables.push_back(symbolInfo->getName());
                                                            }else{
                                                                if( symbolInfo->getIsArray() )
                                                                    (yyval.symbolInfo)->code+="\tSUB SP,"+to_string(2*symbolInfo->getSize())+"\n";
                                                                else
                                                                    (yyval.symbolInfo)->code+="\tSUB SP,2\n";
                                                            }
                                                        }
                                                    }
}
#line 1925 "y.tab.c"
    break;

  case 25: /* type_specifier: INT  */
#line 523 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"type_specifier",(yyvsp[0].symbolInfo)->getTypeSpecifier(),(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                    }
#line 1933 "y.tab.c"
    break;

  case 26: /* type_specifier: FLOAT  */
#line 526 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"type_specifier",(yyvsp[0].symbolInfo)->getTypeSpecifier(),(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                    }
#line 1941 "y.tab.c"
    break;

  case 27: /* type_specifier: VOID  */
#line 529 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"type_specifier",(yyvsp[0].symbolInfo)->getTypeSpecifier(),(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                    }
#line 1949 "y.tab.c"
    break;

  case 28: /* declaration_list: declaration_list COMMA ID  */
#line 533 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"declaration_list","",(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                        (yyval.symbolInfo)->setDeclarationList((yyvsp[-2].symbolInfo)->getDeclarationList()); 
                                                        (yyval.symbolInfo)->addDeclaration((yyvsp[0].symbolInfo));
                                                    }
#line 1959 "y.tab.c"
    break;

  case 29: /* declaration_list: declaration_list COMMA ID LSQUARE CONST_INT RSQUARE  */
#line 538 "2005091.y"
                                                                {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-5].symbolInfo),(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"declaration_list","",(yyvsp[-5].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-5].symbolInfo),(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                        (yyvsp[-3].symbolInfo)->setIsArray(true);
                                                        (yyval.symbolInfo)->setDeclarationList((yyvsp[-5].symbolInfo)->getDeclarationList()); 
                                                        (yyval.symbolInfo)->addDeclaration((yyvsp[-3].symbolInfo)); 
                                                    }
#line 1970 "y.tab.c"
    break;

  case 30: /* declaration_list: ID  */
#line 544 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"declaration_list","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                        (yyval.symbolInfo)->addDeclaration((yyvsp[0].symbolInfo));
                                                    }
#line 1979 "y.tab.c"
    break;

  case 31: /* declaration_list: ID LSQUARE CONST_INT RSQUARE  */
#line 548 "2005091.y"
                                                      {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"declaration_list","",(yyvsp[-3].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                        (yyvsp[-3].symbolInfo)->setIsArray(true);
                                                        (yyval.symbolInfo)->addDeclaration((yyvsp[-3].symbolInfo));  
                                                    }
#line 1989 "y.tab.c"
    break;

  case 32: /* statements: statement  */
#line 554 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"statements","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                        (yyval.symbolInfo)->code = (yyvsp[0].symbolInfo)->code;
                                                    }
#line 1998 "y.tab.c"
    break;

  case 33: /* statements: statements statement  */
#line 558 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"statements","",(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                        (yyval.symbolInfo)->code = (yyvsp[-1].symbolInfo)->code + '\n' + (yyvsp[0].symbolInfo)->code;
                                                    }
#line 2007 "y.tab.c"
    break;

  case 34: /* statement: var_declaration  */
#line 563 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"statement","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                    (yyval.symbolInfo)->code = (yyvsp[0].symbolInfo)->code;
                                                    }
#line 2016 "y.tab.c"
    break;

  case 35: /* statement: expression_statement  */
#line 567 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"statement","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                        string comment = (yyval.symbolInfo)->getName();
                                                        std::replace( comment.begin(), comment.end(), '\n', ' '); // replace all 'x' to 'y'
                                                        (yyval.symbolInfo)->code += "; "+comment+"\n";
                                                        (yyval.symbolInfo)->code += (yyvsp[0].symbolInfo)->code;                           
                                                    }
#line 2028 "y.tab.c"
    break;

  case 36: /* statement: compound_statement  */
#line 574 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"statement","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                        (yyval.symbolInfo)->code = (yyvsp[0].symbolInfo)->code;                            
                                                    }
#line 2037 "y.tab.c"
    break;

  case 37: /* statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement  */
#line 578 "2005091.y"
                                                                                             {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-6].symbolInfo),(yyvsp[-5].symbolInfo),(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"statement","",(yyvsp[-6].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-6].symbolInfo),(yyvsp[-5].symbolInfo),(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                        string comment = (yyval.symbolInfo)->getName();
                                                        std::replace( comment.begin(), comment.end(), '\n', ' '); // replace all 'x' to 'y'
                                                        (yyval.symbolInfo)->code += "; "+comment+"\n";

                                                        //string label = to_string( getLabelCounter() );
                                                        string label_loop = newLabel();//"for_loop"+label;
                                                        string label_end = newLabel();//"for_end"+label;

                                                        (yyval.symbolInfo)->code+=(yyvsp[-4].symbolInfo)->code;
                                                        (yyval.symbolInfo)->code+=label_loop+":\n";
                                                        (yyval.symbolInfo)->code+=(yyvsp[-3].symbolInfo)->code;
                                                        (yyval.symbolInfo)->code+="\tJCXZ "+label_end+"\n";
                                                        (yyval.symbolInfo)->code+=(yyvsp[0].symbolInfo)->code;
                                                        (yyval.symbolInfo)->code+=(yyvsp[-2].symbolInfo)->code;
                                                        (yyval.symbolInfo)->code+="\tJMP "+label_loop+"\n";
                                                        (yyval.symbolInfo)->code+=label_end+":\n";                            
                                                    
                                                    
                                                    }
#line 2063 "y.tab.c"
    break;

  case 38: /* statement: IF LPAREN expression RPAREN statement  */
#line 599 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"statement","",(yyvsp[-4].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                    
                                                        string comment = (yyval.symbolInfo)->getName();
                                                        std::replace( comment.begin(), comment.end(), '\n', ' '); // replace all 'x' to 'y'
                                                        (yyval.symbolInfo)->code += "; "+comment+"\n";

                                                    //	string label = to_string(getLabelCounter());
                                                        string label_false = newLabel();//"if_false" +label;
                                                        string label_true = newLabel();//"if_true" +label;

                                                        (yyval.symbolInfo)->code += (yyvsp[-2].symbolInfo)->code+"\n";
                                                        (yyval.symbolInfo)->code += "\tJCXZ "+label_false+"\n"; //l1
                                                        (yyval.symbolInfo)->code += (yyvsp[0].symbolInfo)->code+"\n";
                                                        (yyval.symbolInfo)->code += "\tJMP "+label_true+"\n"; //l2
                                                        (yyval.symbolInfo)->code += label_false+":\n"; //
                                                        (yyval.symbolInfo)->code += label_true+":\n";                            
                                                    
                                                    }
#line 2087 "y.tab.c"
    break;

  case 39: /* statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 618 "2005091.y"
                                                                 {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-6].symbolInfo),(yyvsp[-5].symbolInfo),(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"statement","",(yyvsp[-6].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-6].symbolInfo),(yyvsp[-5].symbolInfo),(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                    
                                                        string comment = (yyval.symbolInfo)->getName();
                                                        std::replace( comment.begin(), comment.end(), '\n', ' '); // replace all 'x' to 'y'
                                                        (yyval.symbolInfo)->code += "; "+comment+"\n";

                                                        //string label = to_string(getLabelCounter());
                                                        string label_false = newLabel();//"if_false" +label;
                                                        string label_true = newLabel();//"if_true" +label;

                                                        (yyval.symbolInfo)->code += (yyvsp[-4].symbolInfo)->code+"\n";
                                                        (yyval.symbolInfo)->code += "\tJCXZ "+label_false+"\n"; //l1
                                                        (yyval.symbolInfo)->code += (yyvsp[-2].symbolInfo)->code+"\n";
                                                        (yyval.symbolInfo)->code += "\tJMP "+label_true+"\n"; //l2
                                                        (yyval.symbolInfo)->code += label_false+":\n"; // xxx
                                                        (yyval.symbolInfo)->code += (yyvsp[0].symbolInfo)->code+"\n";
                                                        (yyval.symbolInfo)->code += label_true+":\n";                            
                                                    
                                                    }
#line 2112 "y.tab.c"
    break;

  case 40: /* statement: WHILE LPAREN expression RPAREN statement  */
#line 638 "2005091.y"
                                                     {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"statement","",(yyvsp[-4].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                        string comment = (yyval.symbolInfo)->getName();
                                                        std::replace( comment.begin(), comment.end(), '\n', ' '); // replace all 'x' to 'y'
                                                        (yyval.symbolInfo)->code += "; "+comment+"\n";

                                                        
                                                        string label_loop =newLabel();
                                                        string label_end = newLabel();

                                                        (yyval.symbolInfo)->code+=label_loop+":\n";
                                                        (yyval.symbolInfo)->code+=(yyvsp[-2].symbolInfo)->code;
                                                        (yyval.symbolInfo)->code+="\tJCXZ "+label_end+"\n";
                                                        (yyval.symbolInfo)->code+=(yyvsp[0].symbolInfo)->code;
                                                        (yyval.symbolInfo)->code+="\tJMP "+label_loop+"\n";
                                                        (yyval.symbolInfo)->code+=label_end+":\n";                            
                                                    
                                                    }
#line 2135 "y.tab.c"
    break;

  case 41: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 656 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"statement","",(yyvsp[-4].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                        string comment = (yyval.symbolInfo)->getName();
                                                        std::replace( comment.begin(), comment.end(), '\n', ' '); // replace all 'x' to 'y'
                                                        (yyval.symbolInfo)->code += "; "+comment+"\n";

                                                        if( !symbolTable->LookUpSymbol((yyvsp[-2].symbolInfo)->getName()) ){
                                                            // error_output("Undeclared variable",$3->getName());
                                                        }else{
                                                            ////////////
                                                            auto searchedSymbol = symbolTable->LookUpSymbol((yyvsp[-2].symbolInfo)->getName());
                                                        
                                                            if( !searchedSymbol ){
                                                                // error_output("Undeclared variable",$3->getName());
                                                                
                                                            }else if(searchedSymbol->getIsArray()){
                                                                // error_output("Type mismatch,",$3->getName()+" is an array");
                                                                (yyval.symbolInfo)->setTypeSpecifier("error");
                                                            }else {
                                                                (yyval.symbolInfo)->stackOffset =  searchedSymbol->stackOffset;
                                                                if( (yyval.symbolInfo)->stackOffset != 0 ) (yyval.symbolInfo)->varName = to_string((yyval.symbolInfo)->stackOffset)+"[BP]"; // actual variable
                                                                else (yyval.symbolInfo)->varName = (yyvsp[-2].symbolInfo)->getName(); // global variable

                                                            //	$$->code += "\tMOV AX,"+$$->varName+"\n";
                                                                (yyval.symbolInfo)->code += "\tMOV AX,"+(yyval.symbolInfo)->varName+"\n\tCALL PRINTNUMBER\n";

                                                            }
                                                            ///////////	
                                                        }                            
                                                    
                                                    }
#line 2171 "y.tab.c"
    break;

  case 42: /* statement: RETURN expression SEMICOLON  */
#line 687 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"statement","",(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                        string comment = (yyval.symbolInfo)->getName();
                                                        std::replace( comment.begin(), comment.end(), '\n', ' '); // replace all 'x' to 'y'
                                                        (yyval.symbolInfo)->code += "; "+comment+"\n";

                                                        (yyval.symbolInfo)->code += (yyvsp[-1].symbolInfo)->code;
                                                        (yyval.symbolInfo)->code +="\tMOV DX,CX\n\tJMP "+currentFunction+"_exit\n";                            
                                                    }
#line 2185 "y.tab.c"
    break;

  case 43: /* expression_statement: SEMICOLON  */
#line 697 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"expression_statement","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                        (yyval.symbolInfo)->code+=(yyvsp[0].symbolInfo)->code;                            
                                                    }
#line 2194 "y.tab.c"
    break;

  case 44: /* expression_statement: expression SEMICOLON  */
#line 701 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"expression_statement",(yyvsp[-1].symbolInfo)->getTypeSpecifier(),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                        (yyval.symbolInfo)->code = (yyvsp[-1].symbolInfo)->code;                            
                                                    }
#line 2203 "y.tab.c"
    break;

  case 45: /* variable: ID  */
#line 706 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"variable","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)}); 
                                                        SymbolInfo* va=symbolTable->LookUpSymbol((yyvsp[0].symbolInfo)->getName());
                                                        if(va!=NULL)
                                                        {
                                                            (yyval.symbolInfo)->setTypeSpecifier(va->getTypeSpecifier());
                                                            (yyval.symbolInfo)->setIsArray(va->getIsArray());
                                                        }
                                                        else
                                                        {
                                                            (yyval.symbolInfo)->setTypeSpecifier("error");
                                                            errorPrint("Undeclared variable '"+(yyvsp[0].symbolInfo)->getName()+"'"); 
                                                        }
                                                    }
#line 2222 "y.tab.c"
    break;

  case 46: /* variable: ID LSQUARE expression RSQUARE  */
#line 720 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"variable","",(yyvsp[-3].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                        SymbolInfo* va=symbolTable->LookUpSymbol((yyvsp[-3].symbolInfo)->getName());
                                                        if(va!=NULL)
                                                        {
                                                            if(va->getIsArray()==false)
                                                            {
                                                                (yyval.symbolInfo)->setTypeSpecifier("error");
                                                                errorPrint("\'"+(yyvsp[-3].symbolInfo)->getName()+"\' is not an array"); 
                                                            } 
                                                            if((yyvsp[-1].symbolInfo)->getTypeSpecifier()!="INT")
                                                            {
                                                                (yyval.symbolInfo)->setTypeSpecifier("error");
                                                                errorPrint("Array subscript is not an integer");
                                                            }
                                                            else 
                                                            {
                                                                (yyval.symbolInfo)->setIsArray(false); 
                                                                (yyval.symbolInfo)->setTypeSpecifier(va->getTypeSpecifier());
                                                            }
                                                        }
                                                        else
                                                        {
                                                            errorPrint("Undeclared variable '"+(yyvsp[-3].symbolInfo)->getName()+"'"); 
                                                            (yyval.symbolInfo)->setTypeSpecifier("error");                                                            
                                                        }
                                                        if( (yyvsp[-1].symbolInfo)->getTypeSpecifier()!= "CONST_INT" and (yyvsp[-1].symbolInfo)->getTypeSpecifier()!= "INT" ){
                                                            // error_output("Expression inside third brackets not an integer","");	
                                                        }else{
                                                            // use bx for index
                                                            (yyval.symbolInfo)->code+=(yyvsp[-1].symbolInfo)->code;
                                                            (yyval.symbolInfo)->code+="\tMOV BX,CX\n";
                                                            (yyval.symbolInfo)->code+="\tSHL BX,1\n";
                                                            (yyval.symbolInfo)->code+="\tNEG BX\n";
                                                            (yyval.symbolInfo)->code+="\tADD BX,"+to_string(va->stackOffset)+"\n";
                                                            (yyval.symbolInfo)->code+="\tADD BX,BP\n";
                                                            (yyval.symbolInfo)->varName = "[BX]";
                                                        }
                                                    }
#line 2266 "y.tab.c"
    break;

  case 47: /* expression: logic_expression  */
#line 760 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"expression",(yyvsp[0].symbolInfo)->getTypeSpecifier(),(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                            (yyval.symbolInfo)->setIsArray((yyvsp[0].symbolInfo)->getIsArray());
                                                            (yyval.symbolInfo)->code = (yyvsp[0].symbolInfo)->code;                            
                                                        }
#line 2276 "y.tab.c"
    break;

  case 48: /* expression: variable ASSIGNOP logic_expression  */
#line 765 "2005091.y"
                                                        {

                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"expression","",(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                            (yyval.symbolInfo)->setIsArray((yyvsp[-2].symbolInfo)->getIsArray());

                                                            if((yyvsp[0].symbolInfo)->getTypeSpecifier()=="VOID")
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }
                                                            else if(((yyvsp[-2].symbolInfo)->getTypeSpecifier()=="INT")&&((yyvsp[0].symbolInfo)->getTypeSpecifier()=="FLOAT"))
                                                            {
                                                                errorPrint("Warning: possible loss of data in assignment of FLOAT to INT");
                                                            }else{
                                                                (yyval.symbolInfo)->code += (yyvsp[-2].symbolInfo)->code;
                                                                (yyval.symbolInfo)->code += (yyvsp[0].symbolInfo)->code;
                                                                (yyval.symbolInfo)->code += "\tMOV "+(yyvsp[-2].symbolInfo)->varName+",CX\n";
                                                            }
                                                        }
#line 2299 "y.tab.c"
    break;

  case 49: /* logic_expression: rel_expression  */
#line 784 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"logic_expression",(yyvsp[0].symbolInfo)->getTypeSpecifier(),(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});  
                                                            bool tem=(yyvsp[0].symbolInfo)->getIsArray();
                                                            (yyval.symbolInfo)->setIsArray(tem);
                                                            (yyval.symbolInfo)->code = (yyvsp[0].symbolInfo)->code;
                                                        }
#line 2310 "y.tab.c"
    break;

  case 50: /* logic_expression: rel_expression LOGICOP rel_expression  */
#line 790 "2005091.y"
                                                        {

                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"logic_expression","INT",(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                            if(((yyvsp[-2].symbolInfo)->getTypeSpecifier()=="VOID")||((yyvsp[0].symbolInfo)->getTypeSpecifier()=="VOID"))
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }

                                                            string labelEnd = newLabel();
                                                            (yyval.symbolInfo)->code += (yyvsp[-2].symbolInfo)->code;
                                                            (yyval.symbolInfo)->code += "\tCMP CX,0\n";
                                                            if( (yyvsp[-1].symbolInfo)->getName() == "&&" )
                                                                (yyval.symbolInfo)->code += "\tJCXZ "+labelEnd+"\n";
                                                            else
                                                                (yyval.symbolInfo)->code += "\tJNZ "+labelEnd+"\n";
                                                            (yyval.symbolInfo)->code += (yyvsp[0].symbolInfo)->code;
                                                            (yyval.symbolInfo)->code += labelEnd+":\n";
                                                        }
#line 2333 "y.tab.c"
    break;

  case 51: /* rel_expression: simple_expression  */
#line 809 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"rel_expression",(yyvsp[0].symbolInfo)->getTypeSpecifier(),(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                            bool tem=(yyvsp[0].symbolInfo)->getIsArray();
                                                            (yyval.symbolInfo)->setIsArray(tem);
                                                            (yyval.symbolInfo)->code = (yyvsp[0].symbolInfo)->code;
                                                        }
#line 2344 "y.tab.c"
    break;

  case 52: /* rel_expression: simple_expression RELOP simple_expression  */
#line 815 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"rel_expression","INT",(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                            if(((yyvsp[-2].symbolInfo)->getTypeSpecifier()=="VOID")||((yyvsp[0].symbolInfo)->getTypeSpecifier()=="VOID"))
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }else{
                                                                (yyval.symbolInfo)->setTypeSpecifier("INT");

                                                                string opcode = getOpcode((yyvsp[-1].symbolInfo)->getName());

                                                                string labelTrue = newLabel();
                                                                string labelFalse = newLabel();
                                                                (yyval.symbolInfo)->code+=(yyvsp[-2].symbolInfo)->code ;
                                                                (yyval.symbolInfo)->code+="\tPUSH CX\n"; 
                                                                (yyval.symbolInfo)->code+=(yyvsp[0].symbolInfo)->code;
                                                                (yyval.symbolInfo)->code+="\tPOP AX\n";
                                                                (yyval.symbolInfo)->code+="\tCMP AX,CX\n";
                                                                (yyval.symbolInfo)->code+="\t"+opcode+" "+labelTrue+"\n";
                                                                (yyval.symbolInfo)->code+="\tMOV CX,0\n";
                                                                (yyval.symbolInfo)->code+="\tJMP "+labelFalse+"\n";
                                                                (yyval.symbolInfo)->code+=labelTrue+":\n";
                                                                (yyval.symbolInfo)->code+="\tMOV CX,1\n";
                                                                (yyval.symbolInfo)->code+=labelFalse+":\n";
                                                            }
                                                        }
#line 2374 "y.tab.c"
    break;

  case 53: /* simple_expression: term  */
#line 841 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"simple_expression",(yyvsp[0].symbolInfo)->getTypeSpecifier(),(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                            bool tem=(yyvsp[0].symbolInfo)->getIsArray();
                                                            (yyval.symbolInfo)->setIsArray(tem);
                                                            (yyval.symbolInfo)->code = (yyvsp[0].symbolInfo)->code;
                                                        }
#line 2385 "y.tab.c"
    break;

  case 54: /* simple_expression: simple_expression ADDOP term  */
#line 847 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"simple_expression",changeTypeSpecifier((yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo)),(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                            if((yyvsp[0].symbolInfo)->getTypeSpecifier()=="VOID")
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }else{
                                                                (yyval.symbolInfo)->code = (yyvsp[-2].symbolInfo)->code+(yyvsp[0].symbolInfo)->code;
                                                                if( (yyvsp[-1].symbolInfo)->getName() == "+" )
                                                                    (yyval.symbolInfo)->code += "\tPOP AX\n\tADD AX,CX\n\tMOV CX,AX\n";
                                                                else
                                                                    (yyval.symbolInfo)->code += "\tPOP AX\n\tSUB AX,CX\n\tMOV CX,AX\n";
                                                            }


                                                        }
#line 2405 "y.tab.c"
    break;

  case 55: /* term: unary_expression  */
#line 863 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"term",(yyvsp[0].symbolInfo)->getTypeSpecifier(),(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                            bool tem=(yyvsp[0].symbolInfo)->getIsArray();
                                                            (yyval.symbolInfo)->setIsArray(tem);
                                                            (yyval.symbolInfo)->code = (yyvsp[0].symbolInfo)->code;
                                                        }
#line 2416 "y.tab.c"
    break;

  case 56: /* term: term MULOP unary_expression  */
#line 869 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"term",changeTypeSpecifier((yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo)),(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                            if((yyvsp[0].symbolInfo)->getTypeSpecifier()=="VOID")
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }
                                                            else if(((yyvsp[-1].symbolInfo)->getName()=="/")&&((yyvsp[0].symbolInfo)->getStatement()=="0"))
                                                            { 
                                                                (yyval.symbolInfo)->setTypeSpecifier("error");
                                                                errorPrint("Warning: division by zero");
                                                            }
                                                            else if(((yyvsp[-1].symbolInfo)->getName()=="%")&&((yyvsp[0].symbolInfo)->getStatement()=="0"))
                                                            { 
                                                                (yyval.symbolInfo)->setTypeSpecifier("error"); 
                                                                errorPrint("Warning: division by zero"); 
                                                            }
                                                            else if((yyvsp[-1].symbolInfo)->getName()=="%")
                                                            {
                                                                if(!(((yyvsp[-2].symbolInfo)->getTypeSpecifier()=="INT")&&((yyvsp[0].symbolInfo)->getTypeSpecifier()=="INT")))
                                                                {
                                                                    (yyval.symbolInfo)->setTypeSpecifier("error");
                                                                    errorPrint("Operands of modulus must be integers "); 
                                                                }
                                                            }else{
                                                                (yyval.symbolInfo)->code += (yyvsp[-2].symbolInfo)->code+(yyvsp[0].symbolInfo)->code;
                                                                if( (yyvsp[-1].symbolInfo)->getName() == "*" )
                                                                    (yyval.symbolInfo)->code+="\tPOP AX\nIMUL CX\n\tMOV CX,AX\n";
                                                                else if( (yyvsp[-1].symbolInfo)->getName() == "/" )
                                                                    (yyval.symbolInfo)->code+="\tPOP AX\nCWD\nIDIV CX\n\tMOV CX,AX\n";
                                                                else if( (yyvsp[-1].symbolInfo)->getName() == "%" )
                                                                    (yyval.symbolInfo)->code+="\tPOP AX\nCWD\nIDIV CX\n\tMOV CX,DX\n";
                                                            }
                                                        }
#line 2454 "y.tab.c"
    break;

  case 57: /* unary_expression: ADDOP unary_expression  */
#line 903 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"unary_expression",(yyvsp[0].symbolInfo)->getTypeSpecifier(),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                            if((yyvsp[0].symbolInfo)->getTypeSpecifier()=="VOID")
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }else{
                                                                (yyval.symbolInfo)->setTypeSpecifier((yyvsp[0].symbolInfo)->getTypeSpecifier());
                                                                (yyval.symbolInfo)->code+=(yyvsp[0].symbolInfo)->code;
                                                                if((yyvsp[-1].symbolInfo)->getName() == "-")
                                                                    (yyval.symbolInfo)->code+="NEG CX\n";
                                                            }
                                                        }
#line 2471 "y.tab.c"
    break;

  case 58: /* unary_expression: NOT unary_expression  */
#line 915 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"unary_expression","INT",(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                            if((yyvsp[0].symbolInfo)->getTypeSpecifier()=="VOID")
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }else{
                                                            (yyval.symbolInfo)->setTypeSpecifier("INT");
                                                            (yyval.symbolInfo)->code+=(yyvsp[0].symbolInfo)->code;
                                                            //string label = to_string( getLabelCounter() );
                                                            string labelEnd =newLabel();// "not_end"+label;
                                                            string labelOne = newLabel();//"not_one"+label;
                                                            (yyval.symbolInfo)->code+=(yyvsp[0].symbolInfo)->code;
                                                            (yyval.symbolInfo)->code+="\tJCXZ "+labelOne+"\n";
                                                            (yyval.symbolInfo)->code+="\tMOV CX,0\n";
                                                            (yyval.symbolInfo)->code+=labelOne+":\n";
                                                            (yyval.symbolInfo)->code+="\tMOV CX,1\n";
                                                            (yyval.symbolInfo)->code+=labelEnd+":\n";
		}
                                                        }
#line 2495 "y.tab.c"
    break;

  case 59: /* unary_expression: factor  */
#line 934 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"unary_expression",(yyvsp[0].symbolInfo)->getTypeSpecifier(),(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)}); 
                                                            bool tem=(yyvsp[0].symbolInfo)->getIsArray();
                                                            (yyval.symbolInfo)->setIsArray(tem);
                                                            (yyval.symbolInfo)->code = (yyvsp[0].symbolInfo)->code;
                                                        }
#line 2506 "y.tab.c"
    break;

  case 60: /* factor: variable  */
#line 941 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"factor",(yyvsp[0].symbolInfo)->getTypeSpecifier(),(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                            bool tem=(yyvsp[0].symbolInfo)->getIsArray();
                                                            (yyval.symbolInfo)->setIsArray(tem);
                                                            (yyval.symbolInfo)->code+=(yyvsp[0].symbolInfo)->code;
		                                                    (yyval.symbolInfo)->code += "\tMOV CX,"+(yyvsp[0].symbolInfo)->varName+"\n";
                                                        }
#line 2518 "y.tab.c"
    break;

  case 61: /* factor: ID LPAREN argument_list RPAREN  */
#line 948 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"factor","error",(yyvsp[-3].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                            SymbolInfo* va=symbolTable->LookUpSymbol((yyvsp[-3].symbolInfo)->getName());
                                                            if(va!=NULL) 
                                                            {
                                                                (yyval.symbolInfo)->setTypeSpecifier(va->getTypeSpecifier());
                                                                vector<SymbolInfo*> tem_1=(yyvsp[-1].symbolInfo)->getParameterList();
                                                                vector<SymbolInfo*> tem_2=va->getParameterList();
                                                                int n=tem_1.size();
                                                                int m=tem_2.size();
                                                                if(n<m)
                                                                {
                                                                    errorPrint("Too few arguments to function '"+(yyvsp[-3].symbolInfo)->getName()+"'");
                                                                }
                                                                else if(n>m) 
                                                                {
                                                                    errorPrint("Too many arguments to function '"+(yyvsp[-3].symbolInfo)->getName()+"'");
                                                                }
                                                                else
                                                                {                                                                    
                                                                    checkParameters(tem_1,tem_2,(yyvsp[-3].symbolInfo));
                                                                    (yyval.symbolInfo)->code +=(yyvsp[-1].symbolInfo)->code+"\tCALL "+(yyvsp[-3].symbolInfo)->getName()+"\n\tMOV CX,DX\n"+"\tADD SP,"+to_string((yyvsp[-1].symbolInfo)->stackOffset)+"\n";
                                                                }
                                                            }
                                                            else
                                                            {
                                                                errorPrint("Undeclared function '"+(yyvsp[-3].symbolInfo)->getName()+"'");
                                                            }
                                                        }
#line 2552 "y.tab.c"
    break;

  case 62: /* factor: LPAREN expression RPAREN  */
#line 977 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"factor",(yyvsp[-2].symbolInfo)->getTypeSpecifier(),(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                            (yyval.symbolInfo)->code = (yyvsp[-1].symbolInfo)->code;
                                                        }
#line 2561 "y.tab.c"
    break;

  case 63: /* factor: CONST_INT  */
#line 981 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"factor","INT",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                            (yyval.symbolInfo)->code = "\tMOV CX,"+(yyvsp[0].symbolInfo)->getName()+"\n";
                                                        }
#line 2570 "y.tab.c"
    break;

  case 64: /* factor: CONST_FLOAT  */
#line 985 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"factor","FLOAT",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                            (yyval.symbolInfo)->code = "\tMOV CX,"+(yyvsp[0].symbolInfo)->getName()+"\n";
                                                        }
#line 2579 "y.tab.c"
    break;

  case 65: /* factor: variable INCOP  */
#line 989 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"factor",(yyvsp[-1].symbolInfo)->getTypeSpecifier(),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                            if((yyvsp[-1].symbolInfo)->getTypeSpecifier()=="VOID" )
                                                            {
                                                                (yyval.symbolInfo)->setTypeSpecifier("error");
                                                                errorPrint("Variable or field '"+(yyvsp[-1].symbolInfo)->getName()+"' declared void");
                                                            }else{
                                                                (yyval.symbolInfo)->setTypeSpecifier((yyvsp[-1].symbolInfo)->getTypeSpecifier());
                                                                (yyval.symbolInfo)->code += (yyvsp[-1].symbolInfo)->code;
                                                                (yyval.symbolInfo)->code += "\tMOV CX,"+(yyvsp[-1].symbolInfo)->varName+"\n";
                                                                (yyval.symbolInfo)->code += "\tINC "+(yyvsp[-1].symbolInfo)->varName+"\n";
                                                                
                                                            }
                                                        }
#line 2598 "y.tab.c"
    break;

  case 66: /* factor: variable DECOP  */
#line 1003 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"factor",(yyvsp[-1].symbolInfo)->getTypeSpecifier(),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                            if((yyvsp[-1].symbolInfo)->getTypeSpecifier()=="VOID" )
                                                            {
                                                                (yyval.symbolInfo)->setTypeSpecifier("error");
                                                                errorPrint("Variable or field '"+(yyvsp[-1].symbolInfo)->getName()+"' declared void");
                                                            }else{
                                                                (yyval.symbolInfo)->setTypeSpecifier((yyvsp[-1].symbolInfo)->getTypeSpecifier());
                                                                (yyval.symbolInfo)->code += "\tMOV CX,"+(yyvsp[-1].symbolInfo)->varName+"\n";
                                                                (yyval.symbolInfo)->code += "\t MOV AX,CX\n\tSUB AX,1\n\tMOV "+(yyvsp[-1].symbolInfo)->varName+",AX\n";
                                                            }
                                                        }
#line 2615 "y.tab.c"
    break;

  case 67: /* argument_list: arguments  */
#line 1016 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"argument_list","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)}); 
                                                            (yyval.symbolInfo)->setParameterList((yyvsp[0].symbolInfo)->getParameterList());
                                                            (yyval.symbolInfo)->code+=(yyvsp[0].symbolInfo)->code;
		                                                    (yyval.symbolInfo)->stackOffset = (yyvsp[0].symbolInfo)->stackOffset;
                                                        }
#line 2626 "y.tab.c"
    break;

  case 68: /* argument_list: %empty  */
#line 1022 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=new SymbolInfo(concatName({}),"argument_list","",line_count,line_count,false,logout,{});
                                                        }
#line 2634 "y.tab.c"
    break;

  case 69: /* arguments: arguments COMMA logic_expression  */
#line 1026 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"arguments","",(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                            (yyval.symbolInfo)->setParameterList((yyvsp[-2].symbolInfo)->getParameterList()); 
                                                            (yyval.symbolInfo)->addParameter((yyvsp[0].symbolInfo));
                                                            (yyval.symbolInfo)->code+=(yyvsp[-2].symbolInfo)->code+(yyvsp[0].symbolInfo)->code;
                                                            (yyval.symbolInfo)->code+="\tPUSH CX\n";
                                                            (yyval.symbolInfo)->stackOffset = (yyvsp[-2].symbolInfo)->stackOffset + 2;
                                                        }
#line 2647 "y.tab.c"
    break;

  case 70: /* arguments: logic_expression  */
#line 1034 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"arguments","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)}); 
                                                            (yyval.symbolInfo)->addParameter((yyvsp[0].symbolInfo));
                                                            (yyval.symbolInfo)->code+=(yyvsp[0].symbolInfo)->code;
                                                            (yyval.symbolInfo)->code+="\tPUSH CX\n";
                                                            (yyval.symbolInfo)->stackOffset = 2;
                                                        }
#line 2659 "y.tab.c"
    break;

  case 71: /* lcurl: LCURL  */
#line 1042 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=(yyvsp[0].symbolInfo);
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
#line 2677 "y.tab.c"
    break;


#line 2681 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1059 "2005091.y"

int main(int argc,char *argv[]){
    FILE *fp;

    if((fp=fopen(argv[1],"r"))==NULL){
        printf("Cannot Open Input File.\n");
        exit(1);
    }

    logout.open("log.txt");
    errorout.open("error.txt");
    parseout.open("paesetree.txt");
    codeout.open("emu8086.txt");
    /* optout.open("optcode.txt"); */

    yyin=fp;
    yyparse();
    
    logout<<"Total Lines: "<<line_count<<endl;
    logout<<"Total Errors: "<<total_error<<endl;
    cout<<"All done"<<endl;

    fclose(yyin);
    logout.close();
    errorout.close();
    parseout.close();
    codeout.close();
    /* optout.close(); */
    return 0;
}
