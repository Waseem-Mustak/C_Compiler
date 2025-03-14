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


#line 192 "y.tab.c"

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
    WHILE = 262,                   /* WHILE  */
    RETURN = 263,                  /* RETURN  */
    PRINTLN = 264,                 /* PRINTLN  */
    INCOP = 265,                   /* INCOP  */
    DECOP = 266,                   /* DECOP  */
    ASSIGNOP = 267,                /* ASSIGNOP  */
    NOT = 268,                     /* NOT  */
    LPAREN = 269,                  /* LPAREN  */
    RPAREN = 270,                  /* RPAREN  */
    LCURL = 271,                   /* LCURL  */
    RCURL = 272,                   /* RCURL  */
    LSQUARE = 273,                 /* LSQUARE  */
    RSQUARE = 274,                 /* RSQUARE  */
    COMMA = 275,                   /* COMMA  */
    SEMICOLON = 276,               /* SEMICOLON  */
    INT = 277,                     /* INT  */
    FLOAT = 278,                   /* FLOAT  */
    VOID = 279,                    /* VOID  */
    CONST_INT = 280,               /* CONST_INT  */
    CONST_FLOAT = 281,             /* CONST_FLOAT  */
    ID = 282,                      /* ID  */
    ADDOP = 283,                   /* ADDOP  */
    MULOP = 284,                   /* MULOP  */
    RELOP = 285,                   /* RELOP  */
    LOGICOP = 286                  /* LOGICOP  */
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
#define WHILE 262
#define RETURN 263
#define PRINTLN 264
#define INCOP 265
#define DECOP 266
#define ASSIGNOP 267
#define NOT 268
#define LPAREN 269
#define RPAREN 270
#define LCURL 271
#define RCURL 272
#define LSQUARE 273
#define RSQUARE 274
#define COMMA 275
#define SEMICOLON 276
#define INT 277
#define FLOAT 278
#define VOID 279
#define CONST_INT 280
#define CONST_FLOAT 281
#define ID 282
#define ADDOP 283
#define MULOP 284
#define RELOP 285
#define LOGICOP 286

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 124 "2005091.y"

    SymbolInfo* symbolInfo; 

#line 311 "y.tab.c"

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
  YYSYMBOL_WHILE = 7,                      /* WHILE  */
  YYSYMBOL_RETURN = 8,                     /* RETURN  */
  YYSYMBOL_PRINTLN = 9,                    /* PRINTLN  */
  YYSYMBOL_INCOP = 10,                     /* INCOP  */
  YYSYMBOL_DECOP = 11,                     /* DECOP  */
  YYSYMBOL_ASSIGNOP = 12,                  /* ASSIGNOP  */
  YYSYMBOL_NOT = 13,                       /* NOT  */
  YYSYMBOL_LPAREN = 14,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 15,                    /* RPAREN  */
  YYSYMBOL_LCURL = 16,                     /* LCURL  */
  YYSYMBOL_RCURL = 17,                     /* RCURL  */
  YYSYMBOL_LSQUARE = 18,                   /* LSQUARE  */
  YYSYMBOL_RSQUARE = 19,                   /* RSQUARE  */
  YYSYMBOL_COMMA = 20,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 21,                 /* SEMICOLON  */
  YYSYMBOL_INT = 22,                       /* INT  */
  YYSYMBOL_FLOAT = 23,                     /* FLOAT  */
  YYSYMBOL_VOID = 24,                      /* VOID  */
  YYSYMBOL_CONST_INT = 25,                 /* CONST_INT  */
  YYSYMBOL_CONST_FLOAT = 26,               /* CONST_FLOAT  */
  YYSYMBOL_ID = 27,                        /* ID  */
  YYSYMBOL_ADDOP = 28,                     /* ADDOP  */
  YYSYMBOL_MULOP = 29,                     /* MULOP  */
  YYSYMBOL_RELOP = 30,                     /* RELOP  */
  YYSYMBOL_LOGICOP = 31,                   /* LOGICOP  */
  YYSYMBOL_YYACCEPT = 32,                  /* $accept  */
  YYSYMBOL_start = 33,                     /* start  */
  YYSYMBOL_program = 34,                   /* program  */
  YYSYMBOL_unit = 35,                      /* unit  */
  YYSYMBOL_func_declaration = 36,          /* func_declaration  */
  YYSYMBOL_func_definition = 37,           /* func_definition  */
  YYSYMBOL_38_1 = 38,                      /* $@1  */
  YYSYMBOL_39_2 = 39,                      /* $@2  */
  YYSYMBOL_parameter_list = 40,            /* parameter_list  */
  YYSYMBOL_compound_statement = 41,        /* compound_statement  */
  YYSYMBOL_var_declaration = 42,           /* var_declaration  */
  YYSYMBOL_type_specifier = 43,            /* type_specifier  */
  YYSYMBOL_declaration_list = 44,          /* declaration_list  */
  YYSYMBOL_statements = 45,                /* statements  */
  YYSYMBOL_statement = 46,                 /* statement  */
  YYSYMBOL_expression_statement = 47,      /* expression_statement  */
  YYSYMBOL_variable = 48,                  /* variable  */
  YYSYMBOL_expression = 49,                /* expression  */
  YYSYMBOL_logic_expression = 50,          /* logic_expression  */
  YYSYMBOL_rel_expression = 51,            /* rel_expression  */
  YYSYMBOL_simple_expression = 52,         /* simple_expression  */
  YYSYMBOL_term = 53,                      /* term  */
  YYSYMBOL_unary_expression = 54,          /* unary_expression  */
  YYSYMBOL_factor = 55,                    /* factor  */
  YYSYMBOL_argument_list = 56,             /* argument_list  */
  YYSYMBOL_arguments = 57,                 /* arguments  */
  YYSYMBOL_lcurl = 58                      /* lcurl  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   155

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  123

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   286


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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   145,   145,   151,   154,   159,   162,   165,   169,   181,
     193,   193,   203,   203,   212,   219,   227,   233,   240,   245,
     251,   268,   271,   274,   278,   283,   289,   293,   299,   302,
     306,   309,   312,   315,   318,   321,   324,   327,   330,   334,
     337,   341,   355,   383,   387,   402,   407,   416,   421,   429,
     434,   442,   447,   473,   480,   487,   493,   498,   526,   529,
     533,   536,   544,   553,   557,   561,   566,   571
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
  "LOWER_THAN_ELSE", "FOR", "WHILE", "RETURN", "PRINTLN", "INCOP", "DECOP",
  "ASSIGNOP", "NOT", "LPAREN", "RPAREN", "LCURL", "RCURL", "LSQUARE",
  "RSQUARE", "COMMA", "SEMICOLON", "INT", "FLOAT", "VOID", "CONST_INT",
  "CONST_FLOAT", "ID", "ADDOP", "MULOP", "RELOP", "LOGICOP", "$accept",
  "start", "program", "unit", "func_declaration", "func_definition", "$@1",
  "$@2", "parameter_list", "compound_statement", "var_declaration",
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

#define YYPACT_NINF (-71)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      36,   -71,   -71,   -71,     2,    36,   -71,   -71,   -71,   -71,
      -1,   -71,   -71,    21,     3,    -2,   -16,    35,   -71,    32,
      -4,    37,    42,    48,   -71,    54,    55,    36,   -71,   -71,
      53,   -71,   -71,    66,   -71,    54,    69,    62,    83,    88,
      89,     5,    90,     5,     5,   -71,   -71,   -71,   -71,    34,
       5,   -71,   -71,    80,    92,   -71,   -71,    74,    91,   -71,
      79,    26,    82,   -71,   -71,   -71,   -71,   -71,     5,     5,
       5,   101,    96,    39,   -71,   113,     5,     5,   -71,   111,
     -71,   -71,   -71,   -71,     5,   -71,     5,     5,     5,     5,
     115,   118,   120,   -71,   121,   -71,   -71,   122,   127,   114,
     -71,   -71,    82,   110,   -71,   118,     5,   118,   128,   -71,
       5,   -71,   144,   118,   -71,   -71,   -71,   118,     5,   -71,
     135,   118,   -71
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    21,    22,    23,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    26,     0,     0,     0,     0,    20,    12,
       0,    17,     0,    24,     9,     0,    10,     0,    16,    27,
       0,    67,    13,     0,     8,     0,    15,     0,     0,     0,
       0,     0,     0,     0,     0,    19,    39,    59,    60,    41,
       0,    32,    30,     0,     0,    28,    31,    56,     0,    43,
      45,    47,    49,    51,    55,    11,    14,    25,     0,     0,
       0,     0,     0,    56,    54,     0,    64,     0,    53,    26,
      18,    29,    61,    62,     0,    40,     0,     0,     0,     0,
       0,     0,     0,    38,     0,    58,    66,     0,    63,     0,
      44,    46,    50,    48,    52,     0,     0,     0,     0,    57,
       0,    42,    34,     0,    36,    37,    65,     0,     0,    35,
       0,     0,    33
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -71,   -71,   -71,   146,   -71,   -71,   -71,   -71,   -71,   -18,
      38,    10,   -71,   -71,   -50,   -71,   -42,   -41,   -70,    67,
      64,    68,   -38,   -71,   -71,   -71,   -71
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,     7,     8,    35,    25,    20,    51,
      52,    53,    14,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    97,    98,    33
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      71,    73,    11,    75,    81,    74,    96,    32,    73,    22,
      10,    26,    78,    19,   100,    10,    27,    65,    43,    44,
       1,     2,     3,    17,    18,    21,    13,    90,    91,    92,
      47,    48,    49,    50,    73,    15,    99,    36,     9,    16,
     116,   106,    73,     9,    73,    73,    73,    73,    76,    82,
      83,   104,    77,    24,    87,   112,    88,   114,     1,     2,
       3,    29,    23,   118,    28,   113,    30,   119,    73,    38,
      31,   122,    39,    40,    41,    42,    34,   120,    37,    43,
      44,    67,    31,    45,    82,    83,    84,    46,     1,     2,
       3,    47,    48,    49,    50,    38,    66,    68,    39,    40,
      41,    42,    69,    70,    72,    43,    44,    79,    31,    80,
      86,    89,    85,    46,     1,     2,     3,    47,    48,    49,
      50,    38,    93,    94,    39,    40,    41,    42,    95,    16,
     105,    43,    44,   111,    31,   107,   108,   109,    87,    46,
       1,     2,     3,    47,    48,    49,    50,   110,   117,   115,
     121,    12,   103,   101,     0,   102
};

static const yytype_int8 yycheck[] =
{
      41,    43,     0,    44,    54,    43,    76,    25,    50,    25,
       0,    15,    50,    15,    84,     5,    20,    35,    13,    14,
      22,    23,    24,    20,    21,    15,    27,    68,    69,    70,
      25,    26,    27,    28,    76,    14,    77,    27,     0,    18,
     110,    91,    84,     5,    86,    87,    88,    89,    14,    10,
      11,    89,    18,    21,    28,   105,    30,   107,    22,    23,
      24,    19,    27,   113,    27,   106,    18,   117,   110,     3,
      16,   121,     6,     7,     8,     9,    21,   118,    25,    13,
      14,    19,    16,    17,    10,    11,    12,    21,    22,    23,
      24,    25,    26,    27,    28,     3,    27,    14,     6,     7,
       8,     9,    14,    14,    14,    13,    14,    27,    16,    17,
      31,    29,    21,    21,    22,    23,    24,    25,    26,    27,
      28,     3,    21,    27,     6,     7,     8,     9,    15,    18,
      15,    13,    14,    19,    16,    15,    15,    15,    28,    21,
      22,    23,    24,    25,    26,    27,    28,    20,     4,    21,
      15,     5,    88,    86,    -1,    87
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    22,    23,    24,    33,    34,    35,    36,    37,    42,
      43,     0,    35,    27,    44,    14,    18,    20,    21,    15,
      40,    43,    25,    27,    21,    39,    15,    20,    27,    19,
      18,    16,    41,    58,    21,    38,    43,    25,     3,     6,
       7,     8,     9,    13,    14,    17,    21,    25,    26,    27,
      28,    41,    42,    43,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    41,    27,    19,    14,    14,
      14,    49,    14,    48,    54,    49,    14,    18,    54,    27,
      17,    46,    10,    11,    12,    21,    31,    28,    30,    29,
      49,    49,    49,    21,    27,    15,    50,    56,    57,    49,
      50,    51,    53,    52,    54,    15,    46,    15,    15,    15,
      20,    19,    46,    49,    46,    21,    50,     4,    46,    46,
      49,    15,    46
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    35,    36,    36,
      38,    37,    39,    37,    40,    40,    40,    40,    41,    41,
      42,    43,    43,    43,    44,    44,    44,    44,    45,    45,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    47,
      47,    48,    48,    49,    49,    50,    50,    51,    51,    52,
      52,    53,    53,    54,    54,    54,    55,    55,    55,    55,
      55,    55,    55,    56,    56,    57,    57,    58
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       0,     7,     0,     6,     4,     3,     2,     1,     3,     2,
       3,     1,     1,     1,     3,     6,     1,     4,     1,     2,
       1,     1,     1,     9,     5,     7,     5,     5,     3,     1,
       2,     1,     4,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     2,     2,     1,     1,     4,     3,     1,
       1,     2,     2,     1,     0,     3,     1,     1
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
#line 145 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"start","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                        (yyval.symbolInfo)->printParseTree(parseout,0); 
                                                    }
#line 1437 "y.tab.c"
    break;

  case 3: /* program: program unit  */
#line 151 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"program","",(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                    }
#line 1445 "y.tab.c"
    break;

  case 4: /* program: unit  */
#line 154 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"program","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                    }
#line 1453 "y.tab.c"
    break;

  case 5: /* unit: var_declaration  */
#line 159 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"unit","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                    }
#line 1461 "y.tab.c"
    break;

  case 6: /* unit: func_declaration  */
#line 162 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"unit","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                    }
#line 1469 "y.tab.c"
    break;

  case 7: /* unit: func_definition  */
#line 165 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"unit","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                    }
#line 1477 "y.tab.c"
    break;

  case 8: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 169 "2005091.y"
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
#line 1494 "y.tab.c"
    break;

  case 9: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 181 "2005091.y"
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
#line 1510 "y.tab.c"
    break;

  case 10: /* $@1: %empty  */
#line 193 "2005091.y"
                                                                  {functionCheck((yyvsp[-3].symbolInfo),(yyvsp[-4].symbolInfo));}
#line 1516 "y.tab.c"
    break;

  case 11: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN $@1 compound_statement  */
#line 193 "2005091.y"
                                                                                                             {
    
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-6].symbolInfo),(yyvsp[-5].symbolInfo),(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo)},"func_definition","",(yyvsp[-6].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-6].symbolInfo),(yyvsp[-5].symbolInfo),(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo)});
                                                        (yyvsp[-5].symbolInfo)->setTypeSpecifier((yyvsp[-6].symbolInfo)->getTypeSpecifier()); 
                                                        (yyvsp[-5].symbolInfo)->setParameterList((yyvsp[-3].symbolInfo)->getParameterList()); 
                                                        (yyvsp[-5].symbolInfo)->setIsFunction(true);
                                                        (yyvsp[-5].symbolInfo)->setIsDeclared(true); 
                                                        symbolInfoArguments->setParameterList({}); 
                                                        symbolTable->InsertNewSymbolInfo((yyvsp[-5].symbolInfo));
                                                    }
#line 1531 "y.tab.c"
    break;

  case 12: /* $@2: %empty  */
#line 203 "2005091.y"
                                            {functionCheck((yyvsp[-2].symbolInfo),(yyvsp[-3].symbolInfo));}
#line 1537 "y.tab.c"
    break;

  case 13: /* func_definition: type_specifier ID LPAREN RPAREN $@2 compound_statement  */
#line 203 "2005091.y"
                                                                                       {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-5].symbolInfo),(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo)},"func_definition","",(yyvsp[-5].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-5].symbolInfo),(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo)});
                                                        (yyvsp[-4].symbolInfo)->setTypeSpecifier((yyvsp[-5].symbolInfo)->getTypeSpecifier()); 
                                                        (yyvsp[-4].symbolInfo)->setIsFunction(true);
                                                        (yyvsp[-4].symbolInfo)->setIsDeclared(true); 
                                                        symbolInfoArguments->setParameterList({}); 
                                                        symbolTable->InsertNewSymbolInfo((yyvsp[-4].symbolInfo));
                                                    }
#line 1550 "y.tab.c"
    break;

  case 14: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 212 "2005091.y"
                                                          {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"parameter_list","",(yyvsp[-3].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                        (yyvsp[0].symbolInfo)->setTypeSpecifier((yyvsp[-1].symbolInfo)->getTypeSpecifier());
                                                        (yyval.symbolInfo)->setParameterList((yyvsp[-3].symbolInfo)->getParameterList()); 
                                                        (yyval.symbolInfo)->addParameter((yyvsp[0].symbolInfo)); 
                                                        symbolInfoArguments->setParameterList((yyval.symbolInfo)->getParameterList()); 
                                                    }
#line 1562 "y.tab.c"
    break;

  case 15: /* parameter_list: parameter_list COMMA type_specifier  */
#line 219 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"parameter_list","",(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                        
                                                        SymbolInfo* tem=new SymbolInfo("","ID",(yyvsp[0].symbolInfo)->getTypeSpecifier(),10000,10000,false,logout,{});
                                                        (yyval.symbolInfo)->setParameterList((yyvsp[-2].symbolInfo)->getParameterList()); 
                                                        (yyval.symbolInfo)->addParameter(tem);
                                                        symbolInfoArguments->setParameterList((yyval.symbolInfo)->getParameterList()); 
                                                    }
#line 1575 "y.tab.c"
    break;

  case 16: /* parameter_list: type_specifier ID  */
#line 227 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"parameter_list","",(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                        (yyvsp[0].symbolInfo)->setTypeSpecifier((yyvsp[-1].symbolInfo)->getTypeSpecifier());
                                                        (yyval.symbolInfo)->addParameter((yyvsp[0].symbolInfo));
                                                        symbolInfoArguments->setParameterList((yyval.symbolInfo)->getParameterList());
                                                    }
#line 1586 "y.tab.c"
    break;

  case 17: /* parameter_list: type_specifier  */
#line 233 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"parameter_list","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)}); 
                                                        SymbolInfo* tem=new SymbolInfo("","ID",(yyvsp[0].symbolInfo)->getTypeSpecifier(),10000,10000,false,logout,{});
                                                        (yyval.symbolInfo)->addParameter(tem); 
                                                        symbolInfoArguments->setParameterList((yyval.symbolInfo)->getParameterList()); 
                                                    }
#line 1597 "y.tab.c"
    break;

  case 18: /* compound_statement: lcurl statements RCURL  */
#line 240 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"compound_statement","",(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                        symbolTable->PrintAllScopeTable(logout);
                                                        symbolTable->ExitScope();
                                                    }
#line 1607 "y.tab.c"
    break;

  case 19: /* compound_statement: lcurl RCURL  */
#line 245 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"compound_statement","",(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                        symbolTable->PrintAllScopeTable(logout);
                                                        symbolTable->ExitScope();
                                                    }
#line 1617 "y.tab.c"
    break;

  case 20: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 251 "2005091.y"
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
}
#line 1638 "y.tab.c"
    break;

  case 21: /* type_specifier: INT  */
#line 268 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"type_specifier",(yyvsp[0].symbolInfo)->getTypeSpecifier(),(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                    }
#line 1646 "y.tab.c"
    break;

  case 22: /* type_specifier: FLOAT  */
#line 271 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"type_specifier",(yyvsp[0].symbolInfo)->getTypeSpecifier(),(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                    }
#line 1654 "y.tab.c"
    break;

  case 23: /* type_specifier: VOID  */
#line 274 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"type_specifier",(yyvsp[0].symbolInfo)->getTypeSpecifier(),(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                    }
#line 1662 "y.tab.c"
    break;

  case 24: /* declaration_list: declaration_list COMMA ID  */
#line 278 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"declaration_list","",(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                        (yyval.symbolInfo)->setDeclarationList((yyvsp[-2].symbolInfo)->getDeclarationList()); 
                                                        (yyval.symbolInfo)->addDeclaration((yyvsp[0].symbolInfo));
                                                    }
#line 1672 "y.tab.c"
    break;

  case 25: /* declaration_list: declaration_list COMMA ID LSQUARE CONST_INT RSQUARE  */
#line 283 "2005091.y"
                                                                {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-5].symbolInfo),(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"declaration_list","",(yyvsp[-5].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-5].symbolInfo),(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                        (yyvsp[-3].symbolInfo)->setIsArray(true);
                                                        (yyval.symbolInfo)->setDeclarationList((yyvsp[-5].symbolInfo)->getDeclarationList()); 
                                                        (yyval.symbolInfo)->addDeclaration((yyvsp[-3].symbolInfo)); 
                                                    }
#line 1683 "y.tab.c"
    break;

  case 26: /* declaration_list: ID  */
#line 289 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"declaration_list","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                        (yyval.symbolInfo)->addDeclaration((yyvsp[0].symbolInfo));
                                                    }
#line 1692 "y.tab.c"
    break;

  case 27: /* declaration_list: ID LSQUARE CONST_INT RSQUARE  */
#line 293 "2005091.y"
                                                      {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"declaration_list","",(yyvsp[-3].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                        (yyvsp[-3].symbolInfo)->setIsArray(true);
                                                        (yyval.symbolInfo)->addDeclaration((yyvsp[-3].symbolInfo));  
                                                    }
#line 1702 "y.tab.c"
    break;

  case 28: /* statements: statement  */
#line 299 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"statements","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                    }
#line 1710 "y.tab.c"
    break;

  case 29: /* statements: statements statement  */
#line 302 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"statements","",(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                    }
#line 1718 "y.tab.c"
    break;

  case 30: /* statement: var_declaration  */
#line 306 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"statement","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                    }
#line 1726 "y.tab.c"
    break;

  case 31: /* statement: expression_statement  */
#line 309 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"statement","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                    }
#line 1734 "y.tab.c"
    break;

  case 32: /* statement: compound_statement  */
#line 312 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"statement","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                    }
#line 1742 "y.tab.c"
    break;

  case 33: /* statement: FOR LPAREN expression statement expression statement expression RPAREN statement  */
#line 315 "2005091.y"
                                                                                             {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-8].symbolInfo),(yyvsp[-7].symbolInfo),(yyvsp[-6].symbolInfo),(yyvsp[-5].symbolInfo),(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo)},"statement","",(yyvsp[-8].symbolInfo),(yyvsp[-2].symbolInfo),{(yyvsp[-8].symbolInfo),(yyvsp[-7].symbolInfo),(yyvsp[-6].symbolInfo),(yyvsp[-5].symbolInfo),(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo)});
                                                    }
#line 1750 "y.tab.c"
    break;

  case 34: /* statement: IF LPAREN expression RPAREN statement  */
#line 318 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"statement","",(yyvsp[-4].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                    }
#line 1758 "y.tab.c"
    break;

  case 35: /* statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 321 "2005091.y"
                                                                 {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-6].symbolInfo),(yyvsp[-5].symbolInfo),(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"statement","",(yyvsp[-6].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-6].symbolInfo),(yyvsp[-5].symbolInfo),(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                    }
#line 1766 "y.tab.c"
    break;

  case 36: /* statement: WHILE LPAREN expression RPAREN statement  */
#line 324 "2005091.y"
                                                     {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"statement","",(yyvsp[-4].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                    }
#line 1774 "y.tab.c"
    break;

  case 37: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 327 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"statement","",(yyvsp[-4].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-4].symbolInfo),(yyvsp[-3].symbolInfo),(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                    }
#line 1782 "y.tab.c"
    break;

  case 38: /* statement: RETURN expression SEMICOLON  */
#line 330 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"statement","",(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                    }
#line 1790 "y.tab.c"
    break;

  case 39: /* expression_statement: SEMICOLON  */
#line 334 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"expression_statement","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                    }
#line 1798 "y.tab.c"
    break;

  case 40: /* expression_statement: expression SEMICOLON  */
#line 337 "2005091.y"
                                                    {
                                                        (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"expression_statement",(yyvsp[-1].symbolInfo)->getTypeSpecifier(),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                    }
#line 1806 "y.tab.c"
    break;

  case 41: /* variable: ID  */
#line 341 "2005091.y"
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
#line 1825 "y.tab.c"
    break;

  case 42: /* variable: ID LSQUARE expression RSQUARE  */
#line 355 "2005091.y"
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
                                                    }
#line 1857 "y.tab.c"
    break;

  case 43: /* expression: logic_expression  */
#line 383 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"expression",(yyvsp[0].symbolInfo)->getTypeSpecifier(),(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                            (yyval.symbolInfo)->setIsArray((yyvsp[0].symbolInfo)->getIsArray());
                                                        }
#line 1866 "y.tab.c"
    break;

  case 44: /* expression: variable ASSIGNOP logic_expression  */
#line 387 "2005091.y"
                                                        {

                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"expression","",(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                            (yyval.symbolInfo)->setIsArray((yyvsp[-2].symbolInfo)->getIsArray());

                                                            if((yyvsp[0].symbolInfo)->getTypeSpecifier()=="VOID")
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }
                                                            if(((yyvsp[-2].symbolInfo)->getTypeSpecifier()=="INT")&&((yyvsp[0].symbolInfo)->getTypeSpecifier()=="FLOAT"))
                                                            {
                                                                errorPrint("Warning: possible loss of data in assignment of FLOAT to INT");
                                                            }
                                                        }
#line 1885 "y.tab.c"
    break;

  case 45: /* logic_expression: rel_expression  */
#line 402 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"logic_expression",(yyvsp[0].symbolInfo)->getTypeSpecifier(),(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});  
                                                            bool tem=(yyvsp[0].symbolInfo)->getIsArray();
                                                            (yyval.symbolInfo)->setIsArray(tem);
                                                        }
#line 1895 "y.tab.c"
    break;

  case 46: /* logic_expression: rel_expression LOGICOP rel_expression  */
#line 407 "2005091.y"
                                                        {

                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"logic_expression","INT",(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                            if(((yyvsp[-2].symbolInfo)->getTypeSpecifier()=="VOID")||((yyvsp[0].symbolInfo)->getTypeSpecifier()=="VOID"))
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }
                                                        }
#line 1908 "y.tab.c"
    break;

  case 47: /* rel_expression: simple_expression  */
#line 416 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"rel_expression",(yyvsp[0].symbolInfo)->getTypeSpecifier(),(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                            bool tem=(yyvsp[0].symbolInfo)->getIsArray();
                                                            (yyval.symbolInfo)->setIsArray(tem);
                                                        }
#line 1918 "y.tab.c"
    break;

  case 48: /* rel_expression: simple_expression RELOP simple_expression  */
#line 421 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"rel_expression","INT",(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                            if(((yyvsp[-2].symbolInfo)->getTypeSpecifier()=="VOID")||((yyvsp[0].symbolInfo)->getTypeSpecifier()=="VOID"))
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }
                                                        }
#line 1930 "y.tab.c"
    break;

  case 49: /* simple_expression: term  */
#line 429 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"simple_expression",(yyvsp[0].symbolInfo)->getTypeSpecifier(),(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                            bool tem=(yyvsp[0].symbolInfo)->getIsArray();
                                                            (yyval.symbolInfo)->setIsArray(tem);
                                                        }
#line 1940 "y.tab.c"
    break;

  case 50: /* simple_expression: simple_expression ADDOP term  */
#line 434 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"simple_expression",changeTypeSpecifier((yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo)),(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                            if((yyvsp[0].symbolInfo)->getTypeSpecifier()=="VOID")
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }
                                                        }
#line 1952 "y.tab.c"
    break;

  case 51: /* term: unary_expression  */
#line 442 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"term",(yyvsp[0].symbolInfo)->getTypeSpecifier(),(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                            bool tem=(yyvsp[0].symbolInfo)->getIsArray();
                                                            (yyval.symbolInfo)->setIsArray(tem);
                                                        }
#line 1962 "y.tab.c"
    break;

  case 52: /* term: term MULOP unary_expression  */
#line 447 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"term",changeTypeSpecifier((yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo)),(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                            if((yyvsp[0].symbolInfo)->getTypeSpecifier()=="VOID")
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }
                                                            if(((yyvsp[-1].symbolInfo)->getName()=="/")&&((yyvsp[0].symbolInfo)->getStatement()=="0"))
                                                            { 
                                                                (yyval.symbolInfo)->setTypeSpecifier("error");
                                                                errorPrint("Warning: division by zero");
                                                            }
                                                            if(((yyvsp[-1].symbolInfo)->getName()=="%")&&((yyvsp[0].symbolInfo)->getStatement()=="0"))
                                                            { 
                                                                (yyval.symbolInfo)->setTypeSpecifier("error"); 
                                                                errorPrint("Warning: division by zero"); 
                                                            }
                                                            if((yyvsp[-1].symbolInfo)->getName()=="%")
                                                            {
                                                                if(!(((yyvsp[-2].symbolInfo)->getTypeSpecifier()=="INT")&&((yyvsp[0].symbolInfo)->getTypeSpecifier()=="INT")))
                                                                {
                                                                    (yyval.symbolInfo)->setTypeSpecifier("error");
                                                                    errorPrint("Operands of modulus must be integers "); 
                                                                }
                                                            }
                                                        }
#line 1992 "y.tab.c"
    break;

  case 53: /* unary_expression: ADDOP unary_expression  */
#line 473 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"unary_expression",(yyvsp[0].symbolInfo)->getTypeSpecifier(),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                            if((yyvsp[0].symbolInfo)->getTypeSpecifier()=="VOID")
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }
                                                        }
#line 2004 "y.tab.c"
    break;

  case 54: /* unary_expression: NOT unary_expression  */
#line 480 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"unary_expression","INT",(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                            if((yyvsp[0].symbolInfo)->getTypeSpecifier()=="VOID")
                                                            {
                                                                errorPrint("Void cannot be used in expression ");
                                                            }
                                                        }
#line 2016 "y.tab.c"
    break;

  case 55: /* unary_expression: factor  */
#line 487 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"unary_expression",(yyvsp[0].symbolInfo)->getTypeSpecifier(),(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)}); 
                                                            bool tem=(yyvsp[0].symbolInfo)->getIsArray();
                                                            (yyval.symbolInfo)->setIsArray(tem);
                                                        }
#line 2026 "y.tab.c"
    break;

  case 56: /* factor: variable  */
#line 493 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"factor",(yyvsp[0].symbolInfo)->getTypeSpecifier(),(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                            bool tem=(yyvsp[0].symbolInfo)->getIsArray();
                                                            (yyval.symbolInfo)->setIsArray(tem);
                                                        }
#line 2036 "y.tab.c"
    break;

  case 57: /* factor: ID LPAREN argument_list RPAREN  */
#line 498 "2005091.y"
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
                                                                }
                                                            }
                                                            else
                                                            {
                                                                errorPrint("Undeclared function '"+(yyvsp[-3].symbolInfo)->getName()+"'");
                                                            }
                                                        }
#line 2069 "y.tab.c"
    break;

  case 58: /* factor: LPAREN expression RPAREN  */
#line 526 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"factor",(yyvsp[-2].symbolInfo)->getTypeSpecifier(),(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)});
                                                        }
#line 2077 "y.tab.c"
    break;

  case 59: /* factor: CONST_INT  */
#line 530 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"factor","INT",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                        }
#line 2085 "y.tab.c"
    break;

  case 60: /* factor: CONST_FLOAT  */
#line 533 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"factor","FLOAT",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)});
                                                        }
#line 2093 "y.tab.c"
    break;

  case 61: /* factor: variable INCOP  */
#line 536 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"factor",(yyvsp[-1].symbolInfo)->getTypeSpecifier(),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                            if((yyvsp[-1].symbolInfo)->getTypeSpecifier()=="VOID" )
                                                            {
                                                                (yyval.symbolInfo)->setTypeSpecifier("error");
                                                                errorPrint("Variable or field '"+(yyvsp[-1].symbolInfo)->getName()+"' declared void");
                                                            }
                                                        }
#line 2106 "y.tab.c"
    break;

  case 62: /* factor: variable DECOP  */
#line 544 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"factor",(yyvsp[-1].symbolInfo)->getTypeSpecifier(),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                            if((yyvsp[-1].symbolInfo)->getTypeSpecifier()=="VOID" )
                                                            {
                                                                (yyval.symbolInfo)->setTypeSpecifier("error");
                                                                errorPrint("Variable or field '"+(yyvsp[-1].symbolInfo)->getName()+"' declared void");
                                                            }
                                                        }
#line 2119 "y.tab.c"
    break;

  case 63: /* argument_list: arguments  */
#line 553 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"argument_list","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)}); 
                                                            (yyval.symbolInfo)->setParameterList((yyvsp[0].symbolInfo)->getParameterList());
                                                        }
#line 2128 "y.tab.c"
    break;

  case 64: /* argument_list: %empty  */
#line 557 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=new SymbolInfo(concatName({}),"argument_list","",line_count,line_count,false,logout,{});
                                                        }
#line 2136 "y.tab.c"
    break;

  case 65: /* arguments: arguments COMMA logic_expression  */
#line 561 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)},"arguments","",(yyvsp[-2].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[-2].symbolInfo),(yyvsp[-1].symbolInfo),(yyvsp[0].symbolInfo)}); 
                                                            (yyval.symbolInfo)->setParameterList((yyvsp[-2].symbolInfo)->getParameterList()); 
                                                            (yyval.symbolInfo)->addParameter((yyvsp[0].symbolInfo));
                                                        }
#line 2146 "y.tab.c"
    break;

  case 66: /* arguments: logic_expression  */
#line 566 "2005091.y"
                                                        {
                                                            (yyval.symbolInfo)=createNewSymbolInfo({(yyvsp[0].symbolInfo)},"arguments","",(yyvsp[0].symbolInfo),(yyvsp[0].symbolInfo),{(yyvsp[0].symbolInfo)}); 
                                                            (yyval.symbolInfo)->addParameter((yyvsp[0].symbolInfo));
                                                        }
#line 2155 "y.tab.c"
    break;

  case 67: /* lcurl: LCURL  */
#line 571 "2005091.y"
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
#line 2173 "y.tab.c"
    break;


#line 2177 "y.tab.c"

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

#line 588 "2005091.y"

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
