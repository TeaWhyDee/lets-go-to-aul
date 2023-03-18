%{
    #include "node.h"
    #define YYERROR_VERBOSE 1
    NBlock *programBlock; /* the top level root node of our final AST */

    extern int yylex();
    extern int yylineno;
    void yyerror(const char *s) { printf("%s\n", s); }
%}

/* Represents the many different ways we can access our data */
%union {
    Node *node;
    NBlock *block;
    NExpression *expr;
    NStatement *stmt;
    std::vector<NStatement*> *statlist;
    std::vector<NExpression*> *exprlist;
    NIdentifier *ident;
    std::vector<NIdentifier*> *varlist;
    std::string *string;
    int token;
}

/* Define our terminal symbols (tokens). This should
   match our tokens.l lex file. We also define the node type
   they represent.
 */
%token <string> L_STRING L_NUM ID
%token <token> OP_PERCENT OP_HASH OP_EQUALEQUAL OP_NOTEQUAL
%token <token> OP_LESSTHAN OP_LARGERTHAN OP_LESS OP_MORE OP_EQUAL
%token <token> OP_LBRACE OP_RBRACE OP_LCURLY_BRACE OP_LSQUARE_BRACE
%token <token> OP_RSQUARE_BRACE OP_RCURLY_BRACE
%token <token> OP_SEMICOLON OP_COLON OP_COMMA OP_DOTDOT OP_DOT
%token <token> KW_CONST KW_SELF KW_STATIC KW_STRUCT KW_NUM
%token <token> KW_STR KW_BOOL KW_TABLE KW_NIL
%token <token> KW_AND KW_BREAK KW_DO KW_ELSE KW_ELSEIF KW_END
%token <token> KW_FALSE KW_FOR KW_FUNCTION KW_IF KW_IN KW_LOCAL
%token <token> KW_NOT KW_OR KW_REPEAT KW_RETURN KW_THEN KW_TRUE
%token <token> KW_UNTIL KW_WHILE COMMENT

/* Define the type of node our nonterminal symbols represent.
   The types refer to the %union declaration above. Ex: when
   we call an ident (defined by union type ident) we are really
   calling an (NIdentifier*). It makes the compiler happy.
 */
%type <block> program stmts
%type <stmt> stmt var_decl
%type <expr> numeric expr 
%type <ident> ident
/* %type <stmt> stmt var_decl func_decl */
/* %type <token> comparison */
/* %type <expr> numeric expr  */
/* %type <varvec> func_decl_args */
/* %type <exprvec> call_args */
/* %type <block> program stmts block */

%token <token> OP_ARROW OP_PLUS OP_MINUS OP_STAR OP_SLASHSLASH OP_SLASH
/* Operator precedence for mathematical operators */
%left OP_TPLUS OP_TMINUS
%left OP_STAR OP_SLASH OP_SLASHSLASH

%start program

%%
program : stmts { programBlock = $1; }
        ;

stmts : stmt { $$ = new NBlock(); $$->statements.push_back($<stmt>1); }
      | stmts stmt { $1->statements.push_back($<stmt>2); }
      ;

stmt : var_decl


%%

// stmt : var_decl;
// //      | expr { $$ = new NExpressionStatement(*$1); }

// expr : numeric
//      ;

// numeric : L_NUM { $$ = new NDouble(atof($1->c_str())); delete $1; }
//         ;

// var_decl : ident OP_EQUAL expr { $$ = new NDeclaration(*$1, *$3); }
//          ;

// ident : ID { $$ = new NIdentifier(*$1); delete $1; }
//       ;
// %%

/*
comparison : OP_EQUALEQUAL | OP_NOTEQUAL | OP_LESSTHAN | OP_LARGERTHAN 
           | OP_PLUS | OP_MINUS | OP_STAR | OP_SLASH | OP_SLASHSLASH
           ;

program : stmts { programBlock = $1; }
        ;

stmts : stmt { $$ = new NBlock(); $$->statements.push_back($<stmt>1); }
      | stmts stmt { $1->statements.push_back($<stmt>2); }
      ;

stmt : var_decl | func_decl
     | expr { $$ = new NExpressionStatement(*$1); }
     ;

block : TLBRACE stmts TRBRACE { $$ = $2; }
      | TLBRACE TRBRACE { $$ = new NBlock(); }
      ;

var_decl : ident ident { $$ = new NVariableDeclaration(*$1, *$2); }
         | ident ident TEQUAL expr { $$ = new NVariableDeclaration(*$1, *$2, $4); }
         ;
        
func_decl : ident ident TLPAREN func_decl_args TRPAREN block 
            { $$ = new NFunctionDeclaration(*$1, *$2, *$4, *$6); delete $4; }
          ;
    
func_decl_args : blank  { $$ = new VariableList(); }
          | var_decl { $$ = new VariableList(); $$->push_back($<var_decl>1); }
          | func_decl_args TCOMMA var_decl { $1->push_back($<var_decl>3); }
          ;

numeric : TINTEGER { $$ = new NInteger(atol($1->c_str())); delete $1; }
        | TDOUBLE { $$ = new NDouble(atof($1->c_str())); delete $1; }
        ;
    
expr : ident TEQUAL expr { $$ = new NAssignment(*$<ident>1, *$3); }
     | ident TLPAREN call_args TRPAREN { $$ = new NMethodCall(*$1, *$3); delete $3; }
     | ident { $<ident>$ = $1; }
     | numeric
     | expr comparison expr { $$ = new NBinaryOperator(*$1, $2, *$3); }
     | TLPAREN expr TRPAREN { $$ = $2; }
     ;
    
call_args : blank  { $$ = new ExpressionList(); }
          | expr { $$ = new ExpressionList(); $$->push_back($1); }
          | call_args TCOMMA expr  { $1->push_back($3); }
          ;
*/

