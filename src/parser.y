%{
    #include "node.h"
    #define YYERROR_VERBOSE 1
    NBlock *programBlock; /* the top level root node of our final AST */

    extern int yylex();
    extern int yylineno;
    void yyerror(const char *s) { printf("YYERROR: %s\n", s); }
%}

%define parse.error verbose
%define parse.trace
%printer { fprintf (yyo, "%s ", yylval.string->c_str()); } <token>

/* Represents the many different ways we can access our data */
%union {
    Node *node;
    NBlock *block;
    NExpression *expr;
    NStatement *stmt;
    std::vector<NStatement*> *statlist;
    std::vector<NExpression*> *expr_list;
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
}

/* Define our terminal symbols (tokens). This should
   match our tokens.l lex file. We also define the node type
   they represent.
 */
%token <string> L_STRING L_NUM
%token <token> OP_PERCENT OP_HASH OP_EQUALEQUAL OP_NOTEQUAL
%token <token> OP_LESSTHAN OP_LARGERTHAN OP_LESS OP_MORE OP_EQUAL
%token <token> OP_LBRACE OP_RBRACE OP_LCURLY_BRACE OP_LSQUARE_BRACE
%token <token> OP_RSQUARE_BRACE OP_RCURLY_BRACE
%token <token> OP_SEMICOLON OP_COLON OP_COMMA OP_DOTDOT OP_DOT
%token <token> KW_CONST KW_SELF KW_STATIC KW_STRUCT KW_NUM KW_NEW
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
%type <block> program block
%type <stmt> stmt var_decl
%type <function_decl> function_decl
%type <expr> expr term function_call
%type <ident> ident
%type <type_ident> type_ident
%type <binop> binop
%type <unop> unop
%type <typed_var> typed_var
%type <typed_var_list> typed_var_list
%type <expr_list> expr_list 
%type <struct_decl> struct_decl
%type <struct_body> struct_body
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
program : block { programBlock = $1; }
    ;

block : stmt { $$ = new NBlock(); $$->statements.push_back($<stmt>1); }
      | block stmt { $1->statements.push_back($<stmt>2); }
    ;


stmt : var_decl
     | function_call
     | function_decl
     | struct_decl
     | KW_DO block KW_END { $$ = new NDoStatement($2); }
     | KW_WHILE expr KW_DO block KW_END { $$ = new NWhileStatement($2, $4); }
     | KW_REPEAT block KW_UNTIL expr { $$ = new NRepeatUntilStatement($4, $2); }
     | KW_IF if_stmt KW_END { $$ = $2; }
     | for_numeric
     | for_generic
    ;

for_generic : KW_FOR ident_list KW_IN expr_list KW_DO block KW_END {
            $$ = new NGenericForStatement(*$2, *$4, $6); }

for_numeric : KW_FOR ident OP_EQUAL expr OP_COMMA expr KW_DO block KW_END { 
            $$ = new NNumericForStatement($2, $4, $6, new NNum((double)1), $8); }
            | KW_FOR ident OP_EQUAL expr OP_COMMA expr OP_COMMA expr KW_DO block KW_END { 
                    $$ = new NNumericForStatement($2, $4, $6, $8, $10); }
    ;

if_stmt : expr KW_THEN block elseif KW_ELSE block { $$ = new NIfStatement(*$4, $6);
                $$->conditionBlockList.insert($$->conditionBlockList.begin(), new std::pair<NExpression *, NBlock *>($1, $3) );}
        | expr KW_THEN block elseif { $$ = new NIfStatement(*$4, nullptr);
                $$->conditionBlockList.insert($$->conditionBlockList.begin(), new std::pair<NExpression *, NBlock *>($1, $3) );}
        | expr KW_THEN block KW_ELSE block { $$ = new NIfStatement(std::vector<conditionBlock*>(), $5);
                $$->conditionBlockList.push_back( new std::pair<NExpression *, NBlock *>($1, $3) );}
        | expr KW_THEN block { $$ = new NIfStatement(std::vector<conditionBlock*>(), nullptr);
                $$->conditionBlockList.push_back( new std::pair<NExpression *, NBlock *>($1, $3) );}

elseif : KW_ELSEIF expr KW_THEN block { $$ = new std::vector<conditionBlock*>();
       $$->push_back( new std::pair<NExpression *, NBlock *>($2, $4) );}
       | elseif KW_ELSEIF expr KW_THEN block { $1->push_back( new std::pair<NExpression *, NBlock *>($3, $5) );}

retstat : KW_RETURN expr { $$ = new NReturnStatement($2); }
    ;

ident_list : ident {$$ = new std::vector<NIdentifier *>(); $$ -> push_back($1);}
         | ident_list OP_COMMA ident {$$ -> push_back($3);}
    ;
      /* | expr { $$ = new NExpressionStatement(*$1); } */

expr : term
     | expr binop expr {$$ = new NBinaryOperatorExpression($1, $2, $3);}
     | unop expr {$$ = new NUnaryOperatorExpression($1, $2);}
     | function_call
    ;

prefix_expr : term
            | 

function_call : ident OP_LBRACE OP_RBRACE {$$ = new NFunctionCall($1, std::vector<NExpression *>());}
              | ident OP_LBRACE expr_list OP_RBRACE { $$ = new NFunctionCall($1, *$3); }
    ;

expr_list : expr {$$ = new std::vector<NExpression *>(); $$ -> push_back($1);}
          | expr_list OP_COMMA expr {$$ -> push_back($3);}
    ;

term : L_NUM { $$ = new NNum(atof($1->c_str())); delete $1; }
     | L_STRING { $$ = new NString(*$1);}
    ;

binop : OP_PLUS
      | OP_MINUS
      | OP_STAR
      | OP_SLASHSLASH
      | OP_SLASH
      | OP_PERCENT
      | OP_EQUALEQUAL
    ;

unop : OP_MINUS
    ;

typed_var : ident OP_COLON type_ident {$$ = new NDeclarationStatement($1, $3, new NExpression());}
    ;

typed_var_list: typed_var { $$ = new std::vector<NDeclarationStatement *>(); $$->push_back($1);}
        | typed_var_list OP_COMMA typed_var {$1 -> push_back($3);}
    ;

var_decl : ident OP_EQUAL expr { $$ = new NDeclarationStatement($1, $3); }
         | ident OP_COLON type_ident OP_EQUAL expr { $$ = new NDeclarationStatement($1, $3, $5); }
    ;

function_decl : KW_FUNCTION ident OP_LBRACE typed_var_list OP_RBRACE OP_ARROW type_ident block KW_END { $$ = new NFunctionDeclaration($7, $2, $4, $8);}
    |  KW_FUNCTION ident OP_LBRACE typed_var_list OP_RBRACE block KW_END { $$ = new NFunctionDeclaration(nullptr, $2, $4, $6);}
    |  KW_FUNCTION ident OP_LBRACE OP_RBRACE OP_ARROW type_ident block KW_END { $$ = new NFunctionDeclaration($6, $2, new std::vector<NDeclarationStatement*>(), $7);}
    |  KW_FUNCTION ident OP_LBRACE OP_RBRACE block KW_END { $$ = new NFunctionDeclaration(nullptr, $2, new std::vector<NDeclarationStatement*>(), $5);}
    |  KW_NEW OP_LBRACE OP_RBRACE block KW_END { $$ = new NFunctionDeclaration(nullptr, new NIdentifier(new std::string("new")), new std::vector<NDeclarationStatement*>(), $4);}
    |  KW_NEW OP_LBRACE typed_var_list OP_RBRACE block KW_END { $$ = new NFunctionDeclaration(nullptr, new NIdentifier(new std::string("new")), $3, $5);}
    ;

struct_decl : KW_STRUCT ident KW_END { $$ = new NStructDeclaration($2, new StructBody());}
        |  KW_STRUCT ident struct_body KW_END { $$ = new NStructDeclaration($2, $3);}
    ;

struct_body : typed_var { $$ = new StructBody(); $$->fields.push_back($1);}
        | function_decl { $$ = new StructBody(); $$->methods.push_back($1);}
        | struct_body typed_var { $$->fields.push_back($2); }
        | struct_body function_decl { $$->methods.push_back($2); };
    ;

type_ident: KW_STR { $$ = new NIdentifier(new std::string("str")); }
    | KW_BOOL { $$ = new NIdentifier(new std::string("bool")); }
    | KW_NUM { $$ = new NIdentifier(new std::string("num")); }
    | KW_TABLE { $$ = new NIdentifier(new std::string("table")); }
    | KW_NIL { $$ = new NIdentifier(new std::string("nil")); }
    | KW_FUNCTION { $$ = new NIdentifier(new std::string("function")); }
    | L_STRING { $$ = new NIdentifier(yylval.string); }
    ;

ident : L_STRING { $$ = new NIdentifier($1); delete $1; }
%%

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

