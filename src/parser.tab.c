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
#line 1 "parser.y"

    #include "node.h"
    #include <cstring>
    #define YYERROR_VERBOSE 1
    NBlock *programBlock; /* the top level root node of our final AST */

    extern int yylex();
    extern char* yytext;
    extern std::string linebuf;
    extern std::string errortext;
    extern int yylineno;
    void yyerror(const char *s) {
        std::string print = std::string(s, s + strlen(s));
        if (errortext != "") {
            print = errortext;
            errortext = "";
        }

        /* TODO: print column? */
        std::cout << "Error on line " << yylineno << ": "<< linebuf <<\
                "\n\t '" << yytext << "': " << print << "\n\n";
    }

    /* void yyerror (YYLTYPE *locp, char const *s) { */
    /*     printf("YYERROR: %s\n", s); */
    /* } */

#line 99 "parser.tab.c"

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


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
    L_STRING = 258,                /* L_STRING  */
    L_NUM = 259,                   /* L_NUM  */
    ID = 260,                      /* ID  */
    OP_PERCENT = 261,              /* OP_PERCENT  */
    OP_HASH = 262,                 /* OP_HASH  */
    OP_EQUALEQUAL = 263,           /* OP_EQUALEQUAL  */
    OP_NOTEQUAL = 264,             /* OP_NOTEQUAL  */
    OP_LESSTHAN = 265,             /* OP_LESSTHAN  */
    OP_LARGERTHAN = 266,           /* OP_LARGERTHAN  */
    OP_LESS = 267,                 /* OP_LESS  */
    OP_MORE = 268,                 /* OP_MORE  */
    OP_EQUAL = 269,                /* OP_EQUAL  */
    OP_LBRACE = 270,               /* OP_LBRACE  */
    OP_RBRACE = 271,               /* OP_RBRACE  */
    OP_LCURLY_BRACE = 272,         /* OP_LCURLY_BRACE  */
    OP_LSQUARE_BRACE = 273,        /* OP_LSQUARE_BRACE  */
    OP_RSQUARE_BRACE = 274,        /* OP_RSQUARE_BRACE  */
    OP_RCURLY_BRACE = 275,         /* OP_RCURLY_BRACE  */
    OP_SEMICOLON = 276,            /* OP_SEMICOLON  */
    OP_COLON = 277,                /* OP_COLON  */
    OP_COMMA = 278,                /* OP_COMMA  */
    OP_DOTDOT = 279,               /* OP_DOTDOT  */
    OP_DOT = 280,                  /* OP_DOT  */
    KW_CONST = 281,                /* KW_CONST  */
    KW_SELF = 282,                 /* KW_SELF  */
    KW_STATIC = 283,               /* KW_STATIC  */
    KW_STRUCT = 284,               /* KW_STRUCT  */
    KW_NUM = 285,                  /* KW_NUM  */
    KW_NEW = 286,                  /* KW_NEW  */
    KW_STR = 287,                  /* KW_STR  */
    KW_BOOL = 288,                 /* KW_BOOL  */
    KW_TABLE = 289,                /* KW_TABLE  */
    KW_NIL = 290,                  /* KW_NIL  */
    KW_AND = 291,                  /* KW_AND  */
    KW_BREAK = 292,                /* KW_BREAK  */
    KW_DO = 293,                   /* KW_DO  */
    KW_ELSE = 294,                 /* KW_ELSE  */
    KW_ELSEIF = 295,               /* KW_ELSEIF  */
    KW_END = 296,                  /* KW_END  */
    KW_FALSE = 297,                /* KW_FALSE  */
    KW_FOR = 298,                  /* KW_FOR  */
    KW_FUNCTION = 299,             /* KW_FUNCTION  */
    KW_IF = 300,                   /* KW_IF  */
    KW_IN = 301,                   /* KW_IN  */
    KW_LOCAL = 302,                /* KW_LOCAL  */
    KW_NOT = 303,                  /* KW_NOT  */
    KW_OR = 304,                   /* KW_OR  */
    KW_REPEAT = 305,               /* KW_REPEAT  */
    KW_RETURN = 306,               /* KW_RETURN  */
    KW_THEN = 307,                 /* KW_THEN  */
    KW_TRUE = 308,                 /* KW_TRUE  */
    KW_UNTIL = 309,                /* KW_UNTIL  */
    KW_WHILE = 310,                /* KW_WHILE  */
    COMMENT = 311,                 /* COMMENT  */
    ERROR = 312,                   /* ERROR  */
    OP_ARROW = 313,                /* OP_ARROW  */
    OP_PLUS = 314,                 /* OP_PLUS  */
    OP_MINUS = 315,                /* OP_MINUS  */
    OP_STAR = 316,                 /* OP_STAR  */
    OP_SLASHSLASH = 317,           /* OP_SLASHSLASH  */
    OP_SLASH = 318                 /* OP_SLASH  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 37 "parser.y"

    Node *node;
    NBlock *block;
    NExpression *expr;
    NStatement *stmt;
    std::vector<NStatement*> *statlist;
    NIfStatement *ifstmt;
    std::vector<conditionBlock*> *elif;
    std::vector<NExpression*> *expr_list;
    std::vector<NIdentifier*> *ident_list;
    std::vector<NDeclarationStatement *> *typed_var_list;
    NDeclarationStatement *typed_var;
    NIdentifier *ident;
    NIdentifier *type_ident;
    NFunctionDeclaration *function_decl;
    NStructDeclaration *struct_decl;
    StructBody *struct_body;
    std::vector<NIdentifier*> *varlist;
    std::string *string;

    int token;
    int binop;
    int unop;

#line 234 "parser.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_L_STRING = 3,                   /* L_STRING  */
  YYSYMBOL_L_NUM = 4,                      /* L_NUM  */
  YYSYMBOL_ID = 5,                         /* ID  */
  YYSYMBOL_OP_PERCENT = 6,                 /* OP_PERCENT  */
  YYSYMBOL_OP_HASH = 7,                    /* OP_HASH  */
  YYSYMBOL_OP_EQUALEQUAL = 8,              /* OP_EQUALEQUAL  */
  YYSYMBOL_OP_NOTEQUAL = 9,                /* OP_NOTEQUAL  */
  YYSYMBOL_OP_LESSTHAN = 10,               /* OP_LESSTHAN  */
  YYSYMBOL_OP_LARGERTHAN = 11,             /* OP_LARGERTHAN  */
  YYSYMBOL_OP_LESS = 12,                   /* OP_LESS  */
  YYSYMBOL_OP_MORE = 13,                   /* OP_MORE  */
  YYSYMBOL_OP_EQUAL = 14,                  /* OP_EQUAL  */
  YYSYMBOL_OP_LBRACE = 15,                 /* OP_LBRACE  */
  YYSYMBOL_OP_RBRACE = 16,                 /* OP_RBRACE  */
  YYSYMBOL_OP_LCURLY_BRACE = 17,           /* OP_LCURLY_BRACE  */
  YYSYMBOL_OP_LSQUARE_BRACE = 18,          /* OP_LSQUARE_BRACE  */
  YYSYMBOL_OP_RSQUARE_BRACE = 19,          /* OP_RSQUARE_BRACE  */
  YYSYMBOL_OP_RCURLY_BRACE = 20,           /* OP_RCURLY_BRACE  */
  YYSYMBOL_OP_SEMICOLON = 21,              /* OP_SEMICOLON  */
  YYSYMBOL_OP_COLON = 22,                  /* OP_COLON  */
  YYSYMBOL_OP_COMMA = 23,                  /* OP_COMMA  */
  YYSYMBOL_OP_DOTDOT = 24,                 /* OP_DOTDOT  */
  YYSYMBOL_OP_DOT = 25,                    /* OP_DOT  */
  YYSYMBOL_KW_CONST = 26,                  /* KW_CONST  */
  YYSYMBOL_KW_SELF = 27,                   /* KW_SELF  */
  YYSYMBOL_KW_STATIC = 28,                 /* KW_STATIC  */
  YYSYMBOL_KW_STRUCT = 29,                 /* KW_STRUCT  */
  YYSYMBOL_KW_NUM = 30,                    /* KW_NUM  */
  YYSYMBOL_KW_NEW = 31,                    /* KW_NEW  */
  YYSYMBOL_KW_STR = 32,                    /* KW_STR  */
  YYSYMBOL_KW_BOOL = 33,                   /* KW_BOOL  */
  YYSYMBOL_KW_TABLE = 34,                  /* KW_TABLE  */
  YYSYMBOL_KW_NIL = 35,                    /* KW_NIL  */
  YYSYMBOL_KW_AND = 36,                    /* KW_AND  */
  YYSYMBOL_KW_BREAK = 37,                  /* KW_BREAK  */
  YYSYMBOL_KW_DO = 38,                     /* KW_DO  */
  YYSYMBOL_KW_ELSE = 39,                   /* KW_ELSE  */
  YYSYMBOL_KW_ELSEIF = 40,                 /* KW_ELSEIF  */
  YYSYMBOL_KW_END = 41,                    /* KW_END  */
  YYSYMBOL_KW_FALSE = 42,                  /* KW_FALSE  */
  YYSYMBOL_KW_FOR = 43,                    /* KW_FOR  */
  YYSYMBOL_KW_FUNCTION = 44,               /* KW_FUNCTION  */
  YYSYMBOL_KW_IF = 45,                     /* KW_IF  */
  YYSYMBOL_KW_IN = 46,                     /* KW_IN  */
  YYSYMBOL_KW_LOCAL = 47,                  /* KW_LOCAL  */
  YYSYMBOL_KW_NOT = 48,                    /* KW_NOT  */
  YYSYMBOL_KW_OR = 49,                     /* KW_OR  */
  YYSYMBOL_KW_REPEAT = 50,                 /* KW_REPEAT  */
  YYSYMBOL_KW_RETURN = 51,                 /* KW_RETURN  */
  YYSYMBOL_KW_THEN = 52,                   /* KW_THEN  */
  YYSYMBOL_KW_TRUE = 53,                   /* KW_TRUE  */
  YYSYMBOL_KW_UNTIL = 54,                  /* KW_UNTIL  */
  YYSYMBOL_KW_WHILE = 55,                  /* KW_WHILE  */
  YYSYMBOL_COMMENT = 56,                   /* COMMENT  */
  YYSYMBOL_ERROR = 57,                     /* ERROR  */
  YYSYMBOL_OP_ARROW = 58,                  /* OP_ARROW  */
  YYSYMBOL_OP_PLUS = 59,                   /* OP_PLUS  */
  YYSYMBOL_OP_MINUS = 60,                  /* OP_MINUS  */
  YYSYMBOL_OP_STAR = 61,                   /* OP_STAR  */
  YYSYMBOL_OP_SLASHSLASH = 62,             /* OP_SLASHSLASH  */
  YYSYMBOL_OP_SLASH = 63,                  /* OP_SLASH  */
  YYSYMBOL_YYACCEPT = 64,                  /* $accept  */
  YYSYMBOL_program = 65,                   /* program  */
  YYSYMBOL_block = 66,                     /* block  */
  YYSYMBOL_stmt_list = 67,                 /* stmt_list  */
  YYSYMBOL_stmt = 68,                      /* stmt  */
  YYSYMBOL_for_generic = 69,               /* for_generic  */
  YYSYMBOL_for_numeric = 70,               /* for_numeric  */
  YYSYMBOL_if_stmt = 71,                   /* if_stmt  */
  YYSYMBOL_elseif = 72,                    /* elseif  */
  YYSYMBOL_retstat = 73,                   /* retstat  */
  YYSYMBOL_ident_list = 74,                /* ident_list  */
  YYSYMBOL_expr = 75,                      /* expr  */
  YYSYMBOL_function_call = 76,             /* function_call  */
  YYSYMBOL_expr_list = 77,                 /* expr_list  */
  YYSYMBOL_term = 78,                      /* term  */
  YYSYMBOL_binop = 79,                     /* binop  */
  YYSYMBOL_unop = 80,                      /* unop  */
  YYSYMBOL_typed_var = 81,                 /* typed_var  */
  YYSYMBOL_typed_var_list = 82,            /* typed_var_list  */
  YYSYMBOL_var_decl = 83,                  /* var_decl  */
  YYSYMBOL_function_decl = 84,             /* function_decl  */
  YYSYMBOL_struct_decl = 85,               /* struct_decl  */
  YYSYMBOL_struct_body = 86,               /* struct_body  */
  YYSYMBOL_type_ident = 87,                /* type_ident  */
  YYSYMBOL_ident = 88                      /* ident  */
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

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   331

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  156

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   318


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   111,   111,   114,   117,   118,   119,   120,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   136,
     140,   142,   146,   148,   150,   152,   156,   158,   161,   164,
     165,   168,   169,   170,   171,   172,   176,   177,   180,   181,
     184,   185,   186,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   200,   203,   206,   207,   210,   211,   214,   215,
     216,   217,   218,   219,   222,   223,   226,   227,   228,   229,
     232,   233,   234,   235,   236,   237,   238,   241
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "L_STRING", "L_NUM",
  "ID", "OP_PERCENT", "OP_HASH", "OP_EQUALEQUAL", "OP_NOTEQUAL",
  "OP_LESSTHAN", "OP_LARGERTHAN", "OP_LESS", "OP_MORE", "OP_EQUAL",
  "OP_LBRACE", "OP_RBRACE", "OP_LCURLY_BRACE", "OP_LSQUARE_BRACE",
  "OP_RSQUARE_BRACE", "OP_RCURLY_BRACE", "OP_SEMICOLON", "OP_COLON",
  "OP_COMMA", "OP_DOTDOT", "OP_DOT", "KW_CONST", "KW_SELF", "KW_STATIC",
  "KW_STRUCT", "KW_NUM", "KW_NEW", "KW_STR", "KW_BOOL", "KW_TABLE",
  "KW_NIL", "KW_AND", "KW_BREAK", "KW_DO", "KW_ELSE", "KW_ELSEIF",
  "KW_END", "KW_FALSE", "KW_FOR", "KW_FUNCTION", "KW_IF", "KW_IN",
  "KW_LOCAL", "KW_NOT", "KW_OR", "KW_REPEAT", "KW_RETURN", "KW_THEN",
  "KW_TRUE", "KW_UNTIL", "KW_WHILE", "COMMENT", "ERROR", "OP_ARROW",
  "OP_PLUS", "OP_MINUS", "OP_STAR", "OP_SLASHSLASH", "OP_SLASH", "$accept",
  "program", "block", "stmt_list", "stmt", "for_generic", "for_numeric",
  "if_stmt", "elseif", "retstat", "ident_list", "expr", "function_call",
  "expr_list", "term", "binop", "unop", "typed_var", "typed_var_list",
  "var_decl", "function_decl", "struct_decl", "struct_body", "type_ident",
  "ident", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-82)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-4)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -82,    22,   -82,   275,   -82,   -82,   -82,    32,    24,   -82,
      32,    32,     9,   -82,     9,     9,   -82,   -82,   -82,   -82,
     -82,   -82,   -82,   -82,   -82,    48,    10,    26,     8,     0,
      39,    40,   -82,   -82,     9,   -82,    20,   108,   -82,   -82,
       9,    61,   -14,   238,   136,     9,    14,   249,   -82,   -82,
     -82,    16,    62,   -82,   -82,    55,   -82,    32,     9,     9,
      27,   145,   -82,   -82,   -82,   -82,   -82,   -82,   -82,   -82,
     -82,   -82,   -82,     9,   238,     9,   -82,   238,   -82,   238,
      57,   -82,   -82,   -82,   -82,   -82,   -82,   -82,    63,   -82,
     -82,   -82,   249,    38,   -82,    32,   -82,   -22,   167,    28,
      59,   -82,    -4,   238,   238,    50,   -82,     9,     9,   -82,
     -82,    51,   -82,   -82,     9,   249,    52,    31,   -82,     9,
      25,   -82,   238,   238,   -82,    54,    75,   -82,   -82,   249,
      56,   -82,   179,   -82,     9,   -82,     9,   -82,    58,   -82,
     -82,   -82,   -82,   203,   211,    64,   -82,    65,   -82,   -82,
     -82,   -82,   -82,   -82,    69,   -82
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       7,     0,     2,     0,     1,     5,    77,     0,     0,     7,
       0,     0,     0,     7,     0,     0,     6,     4,    18,    17,
      11,     9,     8,    10,    12,     0,     0,     0,     0,     0,
      29,     0,    41,    40,     0,    52,     0,     0,    35,    31,
       0,    42,     0,    28,     0,     0,     0,     0,    64,    66,
      67,     0,     0,     7,    54,     0,    13,     0,     0,     0,
       0,     0,    16,    48,    49,    51,    50,     7,    43,    44,
      45,    46,    47,     0,    33,     0,     7,    56,    36,    38,
       0,    76,    72,    70,    71,    73,    74,    75,     0,    65,
      68,    69,     0,     0,     7,     0,    30,     0,     0,     7,
       0,    34,    25,    32,    15,     0,    37,     0,     0,    53,
      62,     0,    55,     7,     0,     0,     0,     7,     7,     0,
      23,    14,    39,    57,    63,     0,     0,     7,    61,     0,
       0,    24,     0,     7,     0,    19,     0,     7,     0,     7,
      59,     7,    22,     0,     0,     0,    60,     0,    26,     7,
       7,    20,    58,    27,     0,    21
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -82,   -82,    -9,   -82,   -82,   -82,   -82,   -82,   -82,   -82,
     -82,    -7,    93,    44,   -82,   -82,   -82,   -23,    43,   -82,
      -6,   -82,   -82,   -81,    -1
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     3,    17,    18,    19,    36,   120,    20,
      29,    79,    38,    80,    39,    73,    40,    54,    55,    22,
      23,    24,    51,    88,    41
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      28,   107,    25,    49,    42,    37,    26,    43,    44,    30,
      31,   109,    32,    33,     6,     6,   113,    32,    33,     6,
      50,     6,     4,    57,    34,    52,    52,    61,    90,    34,
      78,     6,     6,    74,   127,   118,   119,     6,    77,    27,
      75,     8,    53,    99,    93,    91,    58,     8,   139,    56,
      52,    48,    98,    59,    11,    60,    96,    89,   102,    52,
      11,    62,    45,    46,   133,   134,   103,   105,   104,    35,
      47,    94,   112,   106,    35,   117,    46,   108,    95,   110,
     107,    63,    95,    64,    92,   111,   115,    65,    66,   129,
     116,   121,   124,   128,    52,   135,    21,   140,   136,   146,
     122,   123,    97,   100,   125,   151,   152,   126,   130,   131,
     155,     0,   132,   137,    63,     0,    64,     0,   138,     0,
      65,    66,     0,     0,   142,     0,     0,   143,   145,   144,
     147,     0,   148,     0,    68,    69,    70,    71,    72,     0,
     153,   154,    63,     0,    64,     0,     0,     0,    65,    66,
       0,    63,     0,    64,     0,     0,     0,    65,    66,     0,
      67,   101,     0,     0,     0,     0,     0,    68,    69,    70,
      71,    72,     0,    63,    76,    64,     0,     0,     0,    65,
      66,     0,     0,     0,     0,    63,     0,    64,     0,     0,
     114,    65,    66,     0,     0,    68,    69,    70,    71,    72,
       0,     0,     0,     0,    68,    69,    70,    71,    72,    63,
       0,    64,     0,     0,     0,    65,    66,    63,     0,    64,
       0,     0,     0,    65,    66,     0,    68,    69,    70,    71,
      72,   141,     0,     0,     0,     0,     0,     0,    68,    69,
      70,    71,    72,     0,    63,     0,    64,     0,     0,   150,
      65,    66,     0,     0,    81,   149,     0,     0,     0,     0,
       0,     0,    68,    69,    70,    71,    72,     0,     0,     0,
      68,    69,    70,    71,    72,    -3,     5,     0,     0,    82,
       6,    83,    84,    85,    86,     0,     0,     0,     0,     0,
       0,     0,     0,    87,     0,     0,     0,    68,    69,    70,
      71,    72,     0,     0,     7,     0,     8,     0,     0,     0,
       0,     0,     0,     9,    -3,    -3,    -3,     0,    10,    11,
      12,     0,     0,     0,     0,    13,    14,     0,     0,    -3,
      15,    16
};

static const yytype_int16 yycheck[] =
{
       9,    23,     3,    26,    13,    12,     7,    14,    15,    10,
      11,    92,     3,     4,     5,     5,    38,     3,     4,     5,
      26,     5,     0,    23,    15,    26,    27,    34,    51,    15,
      16,     5,     5,    40,   115,    39,    40,     5,    45,    15,
      54,    31,    16,    16,    53,    51,    46,    31,   129,    41,
      51,    41,    59,    14,    44,    15,    57,    41,    67,    60,
      44,    41,    14,    15,    39,    40,    73,    76,    75,    60,
      22,    16,    95,    16,    60,    16,    15,    14,    23,    41,
      23,     6,    23,     8,    22,    94,    58,    12,    13,    58,
      99,    41,    41,    41,    95,    41,     3,    41,    23,    41,
     107,   108,    58,    60,   113,    41,    41,   114,   117,   118,
      41,    -1,   119,    38,     6,    -1,     8,    -1,   127,    -1,
      12,    13,    -1,    -1,   133,    -1,    -1,   134,   137,   136,
     139,    -1,   141,    -1,    59,    60,    61,    62,    63,    -1,
     149,   150,     6,    -1,     8,    -1,    -1,    -1,    12,    13,
      -1,     6,    -1,     8,    -1,    -1,    -1,    12,    13,    -1,
      52,    16,    -1,    -1,    -1,    -1,    -1,    59,    60,    61,
      62,    63,    -1,     6,    38,     8,    -1,    -1,    -1,    12,
      13,    -1,    -1,    -1,    -1,     6,    -1,     8,    -1,    -1,
      23,    12,    13,    -1,    -1,    59,    60,    61,    62,    63,
      -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,     6,
      -1,     8,    -1,    -1,    -1,    12,    13,     6,    -1,     8,
      -1,    -1,    -1,    12,    13,    -1,    59,    60,    61,    62,
      63,    52,    -1,    -1,    -1,    -1,    -1,    -1,    59,    60,
      61,    62,    63,    -1,     6,    -1,     8,    -1,    -1,    38,
      12,    13,    -1,    -1,     5,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    59,    60,    61,    62,    63,    -1,    -1,    -1,
      59,    60,    61,    62,    63,     0,     1,    -1,    -1,    30,
       5,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    -1,    -1,    -1,    59,    60,    61,
      62,    63,    -1,    -1,    29,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    39,    40,    41,    -1,    43,    44,
      45,    -1,    -1,    -1,    -1,    50,    51,    -1,    -1,    54,
      55,    56
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    65,    66,    67,     0,     1,     5,    29,    31,    38,
      43,    44,    45,    50,    51,    55,    56,    68,    69,    70,
      73,    76,    83,    84,    85,    88,    88,    15,    66,    74,
      88,    88,     3,     4,    15,    60,    71,    75,    76,    78,
      80,    88,    66,    75,    75,    14,    15,    22,    41,    81,
      84,    86,    88,    16,    81,    82,    41,    23,    46,    14,
      15,    75,    41,     6,     8,    12,    13,    52,    59,    60,
      61,    62,    63,    79,    75,    54,    38,    75,    16,    75,
      77,     5,    30,    32,    33,    34,    35,    44,    87,    41,
      81,    84,    22,    66,    16,    23,    88,    77,    75,    16,
      82,    16,    66,    75,    75,    66,    16,    23,    14,    87,
      41,    66,    81,    38,    23,    58,    66,    16,    39,    40,
      72,    41,    75,    75,    41,    66,    75,    87,    41,    58,
      66,    66,    75,    39,    40,    41,    23,    38,    66,    87,
      41,    52,    66,    75,    75,    66,    41,    66,    66,    52,
      38,    41,    41,    66,    66,    41
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    64,    65,    66,    67,    67,    67,    67,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    69,
      70,    70,    71,    71,    71,    71,    72,    72,    73,    74,
      74,    75,    75,    75,    75,    75,    76,    76,    77,    77,
      78,    78,    78,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    80,    81,    82,    82,    83,    83,    84,    84,
      84,    84,    84,    84,    85,    85,    86,    86,    86,    86,
      87,    87,    87,    87,    87,    87,    87,    88
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     2,     0,     1,     1,
       1,     1,     1,     3,     5,     4,     3,     1,     1,     7,
       9,    11,     6,     4,     5,     3,     4,     5,     2,     1,
       3,     1,     3,     2,     3,     1,     3,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     3,     3,     5,     9,     7,
       8,     6,     5,     6,     3,     4,     1,     1,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1
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

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_OP_PERCENT: /* OP_PERCENT  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1165 "parser.tab.c"
        break;

    case YYSYMBOL_OP_HASH: /* OP_HASH  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1171 "parser.tab.c"
        break;

    case YYSYMBOL_OP_EQUALEQUAL: /* OP_EQUALEQUAL  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1177 "parser.tab.c"
        break;

    case YYSYMBOL_OP_NOTEQUAL: /* OP_NOTEQUAL  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1183 "parser.tab.c"
        break;

    case YYSYMBOL_OP_LESSTHAN: /* OP_LESSTHAN  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1189 "parser.tab.c"
        break;

    case YYSYMBOL_OP_LARGERTHAN: /* OP_LARGERTHAN  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1195 "parser.tab.c"
        break;

    case YYSYMBOL_OP_LESS: /* OP_LESS  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1201 "parser.tab.c"
        break;

    case YYSYMBOL_OP_MORE: /* OP_MORE  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1207 "parser.tab.c"
        break;

    case YYSYMBOL_OP_EQUAL: /* OP_EQUAL  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1213 "parser.tab.c"
        break;

    case YYSYMBOL_OP_LBRACE: /* OP_LBRACE  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1219 "parser.tab.c"
        break;

    case YYSYMBOL_OP_RBRACE: /* OP_RBRACE  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1225 "parser.tab.c"
        break;

    case YYSYMBOL_OP_LCURLY_BRACE: /* OP_LCURLY_BRACE  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1231 "parser.tab.c"
        break;

    case YYSYMBOL_OP_LSQUARE_BRACE: /* OP_LSQUARE_BRACE  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1237 "parser.tab.c"
        break;

    case YYSYMBOL_OP_RSQUARE_BRACE: /* OP_RSQUARE_BRACE  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1243 "parser.tab.c"
        break;

    case YYSYMBOL_OP_RCURLY_BRACE: /* OP_RCURLY_BRACE  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1249 "parser.tab.c"
        break;

    case YYSYMBOL_OP_SEMICOLON: /* OP_SEMICOLON  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1255 "parser.tab.c"
        break;

    case YYSYMBOL_OP_COLON: /* OP_COLON  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1261 "parser.tab.c"
        break;

    case YYSYMBOL_OP_COMMA: /* OP_COMMA  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1267 "parser.tab.c"
        break;

    case YYSYMBOL_OP_DOTDOT: /* OP_DOTDOT  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1273 "parser.tab.c"
        break;

    case YYSYMBOL_OP_DOT: /* OP_DOT  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1279 "parser.tab.c"
        break;

    case YYSYMBOL_KW_CONST: /* KW_CONST  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1285 "parser.tab.c"
        break;

    case YYSYMBOL_KW_SELF: /* KW_SELF  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1291 "parser.tab.c"
        break;

    case YYSYMBOL_KW_STATIC: /* KW_STATIC  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1297 "parser.tab.c"
        break;

    case YYSYMBOL_KW_STRUCT: /* KW_STRUCT  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1303 "parser.tab.c"
        break;

    case YYSYMBOL_KW_NUM: /* KW_NUM  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1309 "parser.tab.c"
        break;

    case YYSYMBOL_KW_NEW: /* KW_NEW  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1315 "parser.tab.c"
        break;

    case YYSYMBOL_KW_STR: /* KW_STR  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1321 "parser.tab.c"
        break;

    case YYSYMBOL_KW_BOOL: /* KW_BOOL  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1327 "parser.tab.c"
        break;

    case YYSYMBOL_KW_TABLE: /* KW_TABLE  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1333 "parser.tab.c"
        break;

    case YYSYMBOL_KW_NIL: /* KW_NIL  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1339 "parser.tab.c"
        break;

    case YYSYMBOL_KW_AND: /* KW_AND  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1345 "parser.tab.c"
        break;

    case YYSYMBOL_KW_BREAK: /* KW_BREAK  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1351 "parser.tab.c"
        break;

    case YYSYMBOL_KW_DO: /* KW_DO  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1357 "parser.tab.c"
        break;

    case YYSYMBOL_KW_ELSE: /* KW_ELSE  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1363 "parser.tab.c"
        break;

    case YYSYMBOL_KW_ELSEIF: /* KW_ELSEIF  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1369 "parser.tab.c"
        break;

    case YYSYMBOL_KW_END: /* KW_END  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1375 "parser.tab.c"
        break;

    case YYSYMBOL_KW_FALSE: /* KW_FALSE  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1381 "parser.tab.c"
        break;

    case YYSYMBOL_KW_FOR: /* KW_FOR  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1387 "parser.tab.c"
        break;

    case YYSYMBOL_KW_FUNCTION: /* KW_FUNCTION  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1393 "parser.tab.c"
        break;

    case YYSYMBOL_KW_IF: /* KW_IF  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1399 "parser.tab.c"
        break;

    case YYSYMBOL_KW_IN: /* KW_IN  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1405 "parser.tab.c"
        break;

    case YYSYMBOL_KW_LOCAL: /* KW_LOCAL  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1411 "parser.tab.c"
        break;

    case YYSYMBOL_KW_NOT: /* KW_NOT  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1417 "parser.tab.c"
        break;

    case YYSYMBOL_KW_OR: /* KW_OR  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1423 "parser.tab.c"
        break;

    case YYSYMBOL_KW_REPEAT: /* KW_REPEAT  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1429 "parser.tab.c"
        break;

    case YYSYMBOL_KW_RETURN: /* KW_RETURN  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1435 "parser.tab.c"
        break;

    case YYSYMBOL_KW_THEN: /* KW_THEN  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1441 "parser.tab.c"
        break;

    case YYSYMBOL_KW_TRUE: /* KW_TRUE  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1447 "parser.tab.c"
        break;

    case YYSYMBOL_KW_UNTIL: /* KW_UNTIL  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1453 "parser.tab.c"
        break;

    case YYSYMBOL_KW_WHILE: /* KW_WHILE  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1459 "parser.tab.c"
        break;

    case YYSYMBOL_COMMENT: /* COMMENT  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1465 "parser.tab.c"
        break;

    case YYSYMBOL_ERROR: /* ERROR  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1471 "parser.tab.c"
        break;

    case YYSYMBOL_OP_ARROW: /* OP_ARROW  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1477 "parser.tab.c"
        break;

    case YYSYMBOL_OP_PLUS: /* OP_PLUS  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1483 "parser.tab.c"
        break;

    case YYSYMBOL_OP_MINUS: /* OP_MINUS  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1489 "parser.tab.c"
        break;

    case YYSYMBOL_OP_STAR: /* OP_STAR  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1495 "parser.tab.c"
        break;

    case YYSYMBOL_OP_SLASHSLASH: /* OP_SLASHSLASH  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1501 "parser.tab.c"
        break;

    case YYSYMBOL_OP_SLASH: /* OP_SLASH  */
#line 34 "parser.y"
         { fprintf (yyo, "%s ", yylval.string->c_str()); }
#line 1507 "parser.tab.c"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: block  */
#line 111 "parser.y"
                { programBlock = (yyvsp[0].block); }
#line 2197 "parser.tab.c"
    break;

  case 4: /* stmt_list: stmt_list stmt  */
#line 117 "parser.y"
                           { (yyvsp[-1].block)->statements.push_back((yyvsp[0].stmt)); }
#line 2203 "parser.tab.c"
    break;

  case 7: /* stmt_list: %empty  */
#line 120 "parser.y"
                           { (yyval.block) = new NBlock(); }
#line 2209 "parser.tab.c"
    break;

  case 13: /* stmt: KW_DO block KW_END  */
#line 128 "parser.y"
                          { (yyval.stmt) = new NDoStatement((yyvsp[-1].block)); }
#line 2215 "parser.tab.c"
    break;

  case 14: /* stmt: KW_WHILE expr KW_DO block KW_END  */
#line 129 "parser.y"
                                        { (yyval.stmt) = new NWhileStatement((yyvsp[-3].expr), (yyvsp[-1].block)); }
#line 2221 "parser.tab.c"
    break;

  case 15: /* stmt: KW_REPEAT block KW_UNTIL expr  */
#line 130 "parser.y"
                                     { (yyval.stmt) = new NRepeatUntilStatement((yyvsp[0].expr), (yyvsp[-2].block)); }
#line 2227 "parser.tab.c"
    break;

  case 16: /* stmt: KW_IF if_stmt KW_END  */
#line 131 "parser.y"
                            { (yyval.stmt) = (yyvsp[-1].ifstmt); }
#line 2233 "parser.tab.c"
    break;

  case 19: /* for_generic: KW_FOR ident_list KW_IN expr_list KW_DO block KW_END  */
#line 136 "parser.y"
                                                                   {
            (yyval.stmt) = new NGenericForStatement(*(yyvsp[-5].ident_list), *(yyvsp[-3].expr_list), (yyvsp[-1].block)); }
#line 2240 "parser.tab.c"
    break;

  case 20: /* for_numeric: KW_FOR ident OP_EQUAL expr OP_COMMA expr KW_DO block KW_END  */
#line 140 "parser.y"
                                                                          { 
            (yyval.stmt) = new NNumericForStatement((yyvsp[-7].ident), (yyvsp[-5].expr), (yyvsp[-3].expr), new NNum((double)1), (yyvsp[-1].block)); }
#line 2247 "parser.tab.c"
    break;

  case 21: /* for_numeric: KW_FOR ident OP_EQUAL expr OP_COMMA expr OP_COMMA expr KW_DO block KW_END  */
#line 142 "parser.y"
                                                                                        { 
                    (yyval.stmt) = new NNumericForStatement((yyvsp[-9].ident), (yyvsp[-7].expr), (yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].block)); }
#line 2254 "parser.tab.c"
    break;

  case 22: /* if_stmt: expr KW_THEN block elseif KW_ELSE block  */
#line 146 "parser.y"
                                                  { (yyval.ifstmt) = new NIfStatement(*(yyvsp[-2].elif), (yyvsp[0].block));
                (yyval.ifstmt)->conditionBlockList.insert((yyval.ifstmt)->conditionBlockList.begin(), new std::pair<NExpression *, NBlock *>((yyvsp[-5].expr), (yyvsp[-3].block)) );}
#line 2261 "parser.tab.c"
    break;

  case 23: /* if_stmt: expr KW_THEN block elseif  */
#line 148 "parser.y"
                                    { (yyval.ifstmt) = new NIfStatement(*(yyvsp[0].elif), nullptr);
                (yyval.ifstmt)->conditionBlockList.insert((yyval.ifstmt)->conditionBlockList.begin(), new std::pair<NExpression *, NBlock *>((yyvsp[-3].expr), (yyvsp[-1].block)) );}
#line 2268 "parser.tab.c"
    break;

  case 24: /* if_stmt: expr KW_THEN block KW_ELSE block  */
#line 150 "parser.y"
                                           { (yyval.ifstmt) = new NIfStatement(std::vector<conditionBlock*>(), (yyvsp[0].block));
                (yyval.ifstmt)->conditionBlockList.push_back( new std::pair<NExpression *, NBlock *>((yyvsp[-4].expr), (yyvsp[-2].block)) );}
#line 2275 "parser.tab.c"
    break;

  case 25: /* if_stmt: expr KW_THEN block  */
#line 152 "parser.y"
                             { (yyval.ifstmt) = new NIfStatement(std::vector<conditionBlock*>(), nullptr);
                (yyval.ifstmt)->conditionBlockList.push_back( new std::pair<NExpression *, NBlock *>((yyvsp[-2].expr), (yyvsp[0].block)) );}
#line 2282 "parser.tab.c"
    break;

  case 26: /* elseif: KW_ELSEIF expr KW_THEN block  */
#line 156 "parser.y"
                                      { (yyval.elif) = new std::vector<conditionBlock*>();
       (yyval.elif)->push_back( new std::pair<NExpression *, NBlock *>((yyvsp[-2].expr), (yyvsp[0].block)) );}
#line 2289 "parser.tab.c"
    break;

  case 27: /* elseif: elseif KW_ELSEIF expr KW_THEN block  */
#line 158 "parser.y"
                                             { (yyvsp[-4].elif)->push_back( new std::pair<NExpression *, NBlock *>((yyvsp[-2].expr), (yyvsp[0].block)) );}
#line 2295 "parser.tab.c"
    break;

  case 28: /* retstat: KW_RETURN expr  */
#line 161 "parser.y"
                         { (yyval.stmt) = new NReturnStatement((yyvsp[0].expr)); }
#line 2301 "parser.tab.c"
    break;

  case 29: /* ident_list: ident  */
#line 164 "parser.y"
                   {(yyval.ident_list) = new std::vector<NIdentifier *>(); (yyval.ident_list) -> push_back((yyvsp[0].ident));}
#line 2307 "parser.tab.c"
    break;

  case 30: /* ident_list: ident_list OP_COMMA ident  */
#line 165 "parser.y"
                                     {(yyval.ident_list) -> push_back((yyvsp[0].ident));}
#line 2313 "parser.tab.c"
    break;

  case 32: /* expr: expr binop expr  */
#line 169 "parser.y"
                       {(yyval.expr) = new NBinaryOperatorExpression((yyvsp[-2].expr), (yyvsp[-1].binop), (yyvsp[0].expr));}
#line 2319 "parser.tab.c"
    break;

  case 33: /* expr: unop expr  */
#line 170 "parser.y"
                 {(yyval.expr) = new NUnaryOperatorExpression((yyvsp[-1].unop), (yyvsp[0].expr));}
#line 2325 "parser.tab.c"
    break;

  case 34: /* expr: OP_LBRACE expr OP_RBRACE  */
#line 171 "parser.y"
                                {(yyval.expr) = (yyvsp[-1].expr);}
#line 2331 "parser.tab.c"
    break;

  case 36: /* function_call: ident OP_LBRACE OP_RBRACE  */
#line 176 "parser.y"
                                          {(yyval.expr) = new NFunctionCall((yyvsp[-2].ident), std::vector<NExpression *>());}
#line 2337 "parser.tab.c"
    break;

  case 37: /* function_call: ident OP_LBRACE expr_list OP_RBRACE  */
#line 177 "parser.y"
                                                    { (yyval.expr) = new NFunctionCall((yyvsp[-3].ident), *(yyvsp[-1].expr_list)); }
#line 2343 "parser.tab.c"
    break;

  case 38: /* expr_list: expr  */
#line 180 "parser.y"
                 {(yyval.expr_list) = new std::vector<NExpression *>(); (yyval.expr_list) -> push_back((yyvsp[0].expr));}
#line 2349 "parser.tab.c"
    break;

  case 39: /* expr_list: expr_list OP_COMMA expr  */
#line 181 "parser.y"
                                    {(yyval.expr_list) -> push_back((yyvsp[0].expr));}
#line 2355 "parser.tab.c"
    break;

  case 40: /* term: L_NUM  */
#line 184 "parser.y"
             { (yyval.expr) = new NNum(atof((yyvsp[0].string)->c_str())); delete (yyvsp[0].string); }
#line 2361 "parser.tab.c"
    break;

  case 41: /* term: L_STRING  */
#line 185 "parser.y"
                { (yyval.expr) = new NString(*(yyvsp[0].string));}
#line 2367 "parser.tab.c"
    break;

  case 42: /* term: ident  */
#line 186 "parser.y"
             { (yyval.expr) = new NIdentifier(&((yyvsp[0].ident)->name)); }
#line 2373 "parser.tab.c"
    break;

  case 53: /* typed_var: ident OP_COLON type_ident  */
#line 203 "parser.y"
                                      {(yyval.typed_var) = new NDeclarationStatement((yyvsp[-2].ident), (yyvsp[0].type_ident), new NExpression());}
#line 2379 "parser.tab.c"
    break;

  case 54: /* typed_var_list: typed_var  */
#line 206 "parser.y"
                          { (yyval.typed_var_list) = new std::vector<NDeclarationStatement *>(); (yyval.typed_var_list)->push_back((yyvsp[0].typed_var));}
#line 2385 "parser.tab.c"
    break;

  case 55: /* typed_var_list: typed_var_list OP_COMMA typed_var  */
#line 207 "parser.y"
                                            {(yyvsp[-2].typed_var_list) -> push_back((yyvsp[0].typed_var));}
#line 2391 "parser.tab.c"
    break;

  case 56: /* var_decl: ident OP_EQUAL expr  */
#line 210 "parser.y"
                               { (yyval.stmt) = new NDeclarationStatement((yyvsp[-2].ident), (yyvsp[0].expr)); }
#line 2397 "parser.tab.c"
    break;

  case 57: /* var_decl: ident OP_COLON type_ident OP_EQUAL expr  */
#line 211 "parser.y"
                                                   { (yyval.stmt) = new NDeclarationStatement((yyvsp[-4].ident), (yyvsp[-2].type_ident), (yyvsp[0].expr)); }
#line 2403 "parser.tab.c"
    break;

  case 58: /* function_decl: KW_FUNCTION ident OP_LBRACE typed_var_list OP_RBRACE OP_ARROW type_ident block KW_END  */
#line 214 "parser.y"
                                                                                                      { (yyval.function_decl) = new NFunctionDeclaration((yyvsp[-2].type_ident), (yyvsp[-7].ident), (yyvsp[-5].typed_var_list), (yyvsp[-1].block));}
#line 2409 "parser.tab.c"
    break;

  case 59: /* function_decl: KW_FUNCTION ident OP_LBRACE typed_var_list OP_RBRACE block KW_END  */
#line 215 "parser.y"
                                                                         { (yyval.function_decl) = new NFunctionDeclaration(nullptr, (yyvsp[-5].ident), (yyvsp[-3].typed_var_list), (yyvsp[-1].block));}
#line 2415 "parser.tab.c"
    break;

  case 60: /* function_decl: KW_FUNCTION ident OP_LBRACE OP_RBRACE OP_ARROW type_ident block KW_END  */
#line 216 "parser.y"
                                                                              { (yyval.function_decl) = new NFunctionDeclaration((yyvsp[-2].type_ident), (yyvsp[-6].ident), new std::vector<NDeclarationStatement*>(), (yyvsp[-1].block));}
#line 2421 "parser.tab.c"
    break;

  case 61: /* function_decl: KW_FUNCTION ident OP_LBRACE OP_RBRACE block KW_END  */
#line 217 "parser.y"
                                                          { (yyval.function_decl) = new NFunctionDeclaration(nullptr, (yyvsp[-4].ident), new std::vector<NDeclarationStatement*>(), (yyvsp[-1].block));}
#line 2427 "parser.tab.c"
    break;

  case 62: /* function_decl: KW_NEW OP_LBRACE OP_RBRACE block KW_END  */
#line 218 "parser.y"
                                               { (yyval.function_decl) = new NFunctionDeclaration(nullptr, new NIdentifier(new std::string("new")), new std::vector<NDeclarationStatement*>(), (yyvsp[-1].block));}
#line 2433 "parser.tab.c"
    break;

  case 63: /* function_decl: KW_NEW OP_LBRACE typed_var_list OP_RBRACE block KW_END  */
#line 219 "parser.y"
                                                              { (yyval.function_decl) = new NFunctionDeclaration(nullptr, new NIdentifier(new std::string("new")), (yyvsp[-3].typed_var_list), (yyvsp[-1].block));}
#line 2439 "parser.tab.c"
    break;

  case 64: /* struct_decl: KW_STRUCT ident KW_END  */
#line 222 "parser.y"
                                     { (yyval.struct_decl) = new NStructDeclaration((yyvsp[-1].ident), new StructBody());}
#line 2445 "parser.tab.c"
    break;

  case 65: /* struct_decl: KW_STRUCT ident struct_body KW_END  */
#line 223 "parser.y"
                                              { (yyval.struct_decl) = new NStructDeclaration((yyvsp[-2].ident), (yyvsp[-1].struct_body));}
#line 2451 "parser.tab.c"
    break;

  case 66: /* struct_body: typed_var  */
#line 226 "parser.y"
                        { (yyval.struct_body) = new StructBody(); (yyval.struct_body)->fields.push_back((yyvsp[0].typed_var));}
#line 2457 "parser.tab.c"
    break;

  case 67: /* struct_body: function_decl  */
#line 227 "parser.y"
                        { (yyval.struct_body) = new StructBody(); (yyval.struct_body)->methods.push_back((yyvsp[0].function_decl));}
#line 2463 "parser.tab.c"
    break;

  case 68: /* struct_body: struct_body typed_var  */
#line 228 "parser.y"
                                { (yyval.struct_body)->fields.push_back((yyvsp[0].typed_var)); }
#line 2469 "parser.tab.c"
    break;

  case 69: /* struct_body: struct_body function_decl  */
#line 229 "parser.y"
                                    { (yyval.struct_body)->methods.push_back((yyvsp[0].function_decl)); }
#line 2475 "parser.tab.c"
    break;

  case 70: /* type_ident: KW_STR  */
#line 232 "parser.y"
                   { (yyval.type_ident) = new NIdentifier(new std::string("str")); }
#line 2481 "parser.tab.c"
    break;

  case 71: /* type_ident: KW_BOOL  */
#line 233 "parser.y"
              { (yyval.type_ident) = new NIdentifier(new std::string("bool")); }
#line 2487 "parser.tab.c"
    break;

  case 72: /* type_ident: KW_NUM  */
#line 234 "parser.y"
             { (yyval.type_ident) = new NIdentifier(new std::string("num")); }
#line 2493 "parser.tab.c"
    break;

  case 73: /* type_ident: KW_TABLE  */
#line 235 "parser.y"
               { (yyval.type_ident) = new NIdentifier(new std::string("table")); }
#line 2499 "parser.tab.c"
    break;

  case 74: /* type_ident: KW_NIL  */
#line 236 "parser.y"
             { (yyval.type_ident) = new NIdentifier(new std::string("nil")); }
#line 2505 "parser.tab.c"
    break;

  case 75: /* type_ident: KW_FUNCTION  */
#line 237 "parser.y"
                  { (yyval.type_ident) = new NIdentifier(new std::string("function")); }
#line 2511 "parser.tab.c"
    break;

  case 76: /* type_ident: ID  */
#line 238 "parser.y"
         { (yyval.type_ident) = new NIdentifier(yylval.string); }
#line 2517 "parser.tab.c"
    break;

  case 77: /* ident: ID  */
#line 241 "parser.y"
           { (yyval.ident) = new NIdentifier((yyvsp[0].string)); delete (yyvsp[0].string); }
#line 2523 "parser.tab.c"
    break;


#line 2527 "parser.tab.c"

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
  *++yylsp = yyloc;

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 243 "parser.y"


