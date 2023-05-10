%{
    #include "node.h"
    #include <cstring>
    #define YYERROR_VERBOSE 1
    NBlock *programBlock; /* the top level root node of our final AST */
    SymbolTableStorage *symtab_storage = new SymbolTableStorage(new ScopedSymbolTable());
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
%}


/* %define parse.error verbose */
/* %define parse.trace */
%define locations
%printer { fprintf (yyo, "%s ", yylval.string->c_str()); } <token>

/* Represents the many different ways we can access our data */
%union {
    Node *node;
    NBlock *block;
    NExpression *expr;
    NStatement *stmt;
    std::vector<NStatement*> *statlist;
    NIfStatement *ifstmt;
    std::vector<conditionBlock*> *elif;
    std::vector<NExpression*> *expr_list;
    std::vector<NIdentifier*> *ident_list;
    std::vector<NType*> *typelist;
    std::vector<NDeclarationStatement *> *typed_var_list;
    std::vector<keyvalPair*> *keyval_pair_list;
    keyvalPair *keyval_pair;
    NTableConstructor *table_constructor;
    NDeclarationStatement *typed_var;
    NIdentifier *ident;
    NType *type_ident;
    NFunctionDeclaration *function_decl;
    NStructDeclaration *struct_decl;
    StructBody *struct_body;
    std::vector<NIdentifier*> *varlist;
    std::string *string;
    NFunctionType *function_type;

    int token;
}

/* Define our terminal symbols (tokens). This should
   match our tokens.l lex file. We also define the node type
   they represent.
 */
%token <string> L_STRING L_NUM ID
%token <token> OP_PERCENT OP_HASH OP_EQUALEQUAL OP_NOTEQUAL
%token <token> OP_LESSEQ OP_MOREEQ OP_LESS OP_MORE OP_EQUAL
%token <token> OP_LBRACE OP_RBRACE OP_LCURLY_BRACE OP_LSQUARE_BRACE
%token <token> OP_RSQUARE_BRACE OP_RCURLY_BRACE
%token <token> OP_SEMICOLON OP_COLON OP_COMMA OP_DOTDOT OP_DOT
%token <token> KW_CONST KW_SELF KW_STATIC KW_STRUCT KW_NUM KW_NEW
%token <token> KW_STR KW_BOOL KW_TABLE KW_NIL
%token <token> KW_AND KW_BREAK KW_DO KW_ELSE KW_ELSEIF KW_END
%token <token> KW_FALSE KW_FOR KW_FUNCTION KW_IF KW_IN KW_LOCAL
%token <token> KW_NOT KW_OR KW_REPEAT KW_RETURN KW_THEN KW_TRUE
%token <token> KW_UNTIL KW_WHILE COMMENT
%token <token> ERROR

/* Define the type of node our nonterminal symbols represent.
   The types refer to the %union declaration above. Ex: when
   we call an ident (defined by union type ident) we are really
   calling an (NIdentifier*). It makes the compiler happy.
 */
%type <block> program block stmt_list
%type <stmt> stmt var_decl retstat for_numeric for_generic var_assignment break
%type <ifstmt> if_stmt
%type <elif> elseif
%type <function_decl> function_decl
%type <expr> expr term function_call access_member exp
%type <ident> ident
%type <type_ident> type_ident
%type <binop> binop
%type <unop> unop
%type <typed_var> typed_var
%type <typed_var_list> typed_var_list
%type <expr_list> expr_list
%type <ident_list> ident_list
%type <struct_decl> struct_decl
%type <struct_body> struct_body
%type <function_type> function_type
%type <typelist> typelist
%type <table_constructor> table_constructor
%type <keyval_pair_list> keyval_pair_list
%type <keyval_pair> keyval_pair


%token <token> OP_ARROW OP_PLUS OP_MINUS OP_STAR OP_SLASHSLASH OP_SLASH OP_CARET
/* Operator precedence for mathematical operators */
%left KW_OR
%left KW_AND
%left OP_LESS OP_MORE OP_LESSEQ OP_MOREEQ OP_EQUALEQUAL OP_NOTEQUAL
%left OP_PLUS OP_MINUS
%left OP_STAR OP_SLASH OP_SLASHSLASH OP_PERCENT
%right OP_CARET
%nonassoc UMINUS

%start program

%%
program : block { programBlock = $1; }
    ;

block : stmt_list
    ;

stmt_list : stmt_list stmt { $1->statements.push_back($<stmt>2); }
          | stmt_list error
          | stmt_list COMMENT
          | /* empty */    { $$ = new NBlock(); }
    ;

stmt : var_decl
     | access_member
     | break
     | var_assignment
     | function_call
     | function_decl
     | retstat
     | struct_decl
     | KW_DO block KW_END { $$ = new NDoStatement($2); }
     | KW_WHILE expr KW_DO block KW_END { $$ = new NWhileStatement($2, $4); }
     | KW_REPEAT block KW_UNTIL expr { $$ = new NRepeatUntilStatement($4, $2); }
     | KW_IF if_stmt KW_END { $$ = $2; }
     | for_numeric
     | for_generic
    ;

for_generic : KW_FOR ident_list KW_IN expr KW_DO block KW_END {
            $$ = new NGenericForStatement(*$2, $4, $6); }
    ;

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
    ;

elseif : KW_ELSEIF expr KW_THEN block { $$ = new std::vector<conditionBlock*>();
       $$->push_back( new std::pair<NExpression *, NBlock *>($2, $4) );}
       | elseif KW_ELSEIF expr KW_THEN block { $1->push_back( new std::pair<NExpression *, NBlock *>($3, $5) );}
    ;

retstat : KW_RETURN expr { $$ = new NReturnStatement($2, Position(@retstat.first_line, @retstat.first_column)); }
    ;

ident_list : ident {$$ = new std::vector<NIdentifier *>(); $$ -> push_back($1);}
         | ident_list OP_COMMA ident {$$ -> push_back($3);}
    ;

var_assignment : access_member OP_EQUAL expr { $$ = new NAssignmentStatement($1, $3); }
               /* { $$ = new NDeclarationStatement($1, $4); } */
    ;

expr : term
     | access_member
     | exp
     /* | expr binop expr {$$ = new NBinaryOperatorExpression($1, $2, $3);} */
     /* | unop expr */
     | OP_LBRACE expr OP_RBRACE {$$ = $2;}
     | function_call
     | OP_LCURLY_BRACE table_constructor OP_RCURLY_BRACE { $$ = $2; }
     | KW_TRUE { new NBool(true); }
     | KW_FALSE { new NBool(false); }
    ;

access_member : access_member OP_LSQUARE_BRACE expr OP_RSQUARE_BRACE { $$ = new NAccessKey($1, $3); }
              | access_member OP_DOT ident { $$ = new NAccessKey($1, $3); }
              /* | access_member OP_DOT function_call { $$ = new NExpressionCall($1, $3); } */
              | access_member OP_LBRACE OP_RBRACE {$$ = new NExpressionCall($1, std::vector<NExpression *>());}
              | access_member OP_LBRACE expr_list OP_RBRACE {$$ = new NExpressionCall($1, *$3);}
              | KW_SELF { std::string* str = new std::string("self");
            //   hotfix for position, should be fixed later
                            $$ = new NIdentifier(str, Position(0, 0)); }
              | ident
              | function_call
    ;

table_constructor : expr_list { $$ = new NTableConstructor(); $$->expressionList = *$1; }
    | keyval_pair_list { $$ = new NTableConstructor(); $$->keyvalPairList = *$1; }
    | /* empty */  { $$ = new NTableConstructor(); }
    ;

keyval_pair_list : keyval_pair { $$ = new std::vector<std::pair<NIdentifier*, NExpression*>*>;
                                 $$->push_back($1); }
                 | keyval_pair_list OP_COMMA keyval_pair { $1->push_back($3); }
    ;

keyval_pair : ident OP_EQUAL expr { $$ = new std::pair<NIdentifier*, NExpression*>($1, $3); }
    ;

function_call : ident OP_LBRACE OP_RBRACE {$$ = new NExpressionCall($1, std::vector<NExpression *>());}
              | ident OP_LBRACE expr_list OP_RBRACE { $$ = new NExpressionCall($1, *$3); }
    ;

expr_list : expr {$$ = new std::vector<NExpression *>(); $$ -> push_back($1);}
          | expr_list OP_COMMA expr {$$ -> push_back($3);}
    ;

term : L_NUM { $$ = new NNum(atof($1->c_str()), Position(@term.first_line, @term.first_column)); delete $1; }
     | L_STRING { $$ = new NString(*$1, Position(@term.first_line, @term.first_column));}
    ;

break : KW_BREAK { $$ = new NBreakStatement(); }
    ;

exp : expr OP_PLUS expr  {$$ = new NBinaryOperatorExpression($1, BinOpType::ADD, $3, Position(@1.first_line, @1.first_column));}
    | expr OP_MINUS expr {$$ = new NBinaryOperatorExpression($1, BinOpType::SUBSTRACT, $3, Position(@1.first_line, @1.first_column));}
    | expr OP_STAR expr {$$ = new NBinaryOperatorExpression($1, BinOpType::MULTIPLY, $3, Position(@1.first_line, @1.first_column));}
    | expr OP_SLASHSLASH expr {$$ = new NBinaryOperatorExpression($1, BinOpType::FLOOR_DIVIDE, $3, Position(@1.first_line, @1.first_column));}
    | expr OP_SLASH expr {$$ = new NBinaryOperatorExpression($1, BinOpType::DIVIDE, $3, Position(@1.first_line, @1.first_column));}
    | expr OP_PERCENT expr {$$ = new NBinaryOperatorExpression($1, BinOpType::MODULO, $3, Position(@1.first_line, @1.first_column));}
    | expr OP_EQUALEQUAL expr {$$ = new NBinaryOperatorExpression($1, BinOpType::EQUAL, $3, Position(@1.first_line, @1.first_column));}
    | expr OP_NOTEQUAL expr {$$ = new NBinaryOperatorExpression($1, BinOpType::NOT_EQUAL, $3, Position(@1.first_line, @1.first_column));}
    | expr OP_MORE expr {$$ = new NBinaryOperatorExpression($1, BinOpType::GREATER_THAN, $3, Position(@1.first_line, @1.first_column));}
    | expr OP_LESS expr {$$ = new NBinaryOperatorExpression($1, BinOpType::LESS_THAN, $3, Position(@1.first_line, @1.first_column));}
    | expr OP_MOREEQ expr {$$ = new NBinaryOperatorExpression($1, BinOpType::GREATER_THAN_OR_EQUAL, $3, Position(@1.first_line, @1.first_column));}
    | expr OP_LESSEQ expr {$$ = new NBinaryOperatorExpression($1, BinOpType::LESS_THAN_OR_EQUAL, $3, Position(@1.first_line, @1.first_column));}
    | expr KW_AND expr {$$ = new NBinaryOperatorExpression($1, BinOpType::AND, $3, Position(@1.first_line, @1.first_column));}
    | expr KW_OR expr {$$ = new NBinaryOperatorExpression($1, BinOpType::OR, $3, Position(@1.first_line, @1.first_column));}
    | expr OP_CARET expr {$$ = new NBinaryOperatorExpression($1, BinOpType::POWER, $3, Position(@1.first_line, @1.first_column));}
    | OP_MINUS expr {$$ = new NUnaryOperatorExpression(UnOpType::MINUS, $2, Position(@1.first_line, @1.first_column));} %prec UMINUS
    | KW_NOT expr {$$ = new NUnaryOperatorExpression(UnOpType::NOT, $2, Position(@1.first_line, @1.first_column));}
    ;

typed_var : ident OP_COLON type_ident {$$ = new NDeclarationStatement($1, $3, nullptr, Position(@ident.first_line, @ident.first_column));}
    ;

typed_var_list: typed_var { $$ = new std::vector<NDeclarationStatement *>(); $$->push_back($1);}
        | typed_var_list OP_COMMA typed_var {$1 -> push_back($3);}
    ;

var_decl : ident OP_EQUAL expr { $$ = new NDeclarationStatement($ident, $expr, Position(@ident.first_line, @ident.first_column)); }
         | ident OP_COLON type_ident OP_EQUAL expr { $$ = new NDeclarationStatement($ident, $type_ident, $expr, Position(@ident.first_line, @ident.first_column)); }
    ;

function_decl : KW_FUNCTION ident OP_LBRACE typed_var_list OP_RBRACE OP_ARROW typelist block KW_END { $$ = new NFunctionDeclaration($typelist, $ident, $typed_var_list, $block, Position(@ident.first_line, @ident.first_column));}
    |  KW_FUNCTION ident OP_LBRACE typed_var_list OP_RBRACE block KW_END { $$ = new NFunctionDeclaration(nullptr, $ident, $typed_var_list, $block, Position(@ident.first_line, @ident.first_column));}
    |  KW_FUNCTION ident OP_LBRACE OP_RBRACE OP_ARROW typelist block KW_END { $$ = new NFunctionDeclaration($typelist, $ident, new std::vector<NDeclarationStatement*>(), $block, Position(@ident.first_line, @ident.first_column));}
    |  KW_FUNCTION ident OP_LBRACE OP_RBRACE block KW_END { $$ = new NFunctionDeclaration(nullptr, $ident, new std::vector<NDeclarationStatement*>(), $block, Position(@ident.first_line, @ident.first_column));}
    |  KW_NEW OP_LBRACE OP_RBRACE block KW_END { $$ = new NFunctionDeclaration(nullptr, new NIdentifier(new std::string("new"), Position(@KW_NEW.first_line, @KW_NEW.first_column)), new std::vector<NDeclarationStatement*>(), $block, Position(@block.first_line, @block.first_column));}
    |  KW_NEW OP_LBRACE typed_var_list OP_RBRACE block KW_END { $$ = new NFunctionDeclaration(nullptr, new NIdentifier(new std::string("new"), Position(@KW_NEW.first_line, @KW_NEW.first_column)), $typed_var_list, $block, Position(@block.first_line, @block.first_column));}
    ;

struct_decl : KW_STRUCT ident KW_END { $$ = new NStructDeclaration($ident, Position(@ident.first_line, @ident.first_column),new StructBody());}
        |  KW_STRUCT ident struct_body KW_END { $$ = new NStructDeclaration($ident, Position(@ident.first_line, @ident.first_column), $struct_body);}
    ;

struct_body : typed_var { $$ = new StructBody(); $$->fields.push_back($1);}
        | function_decl { $$ = new StructBody(); $$->methods.push_back($1);}
        | struct_body typed_var { $$->fields.push_back($2); }
        | struct_body function_decl { $$->methods.push_back($2); }
    ;

type_ident: KW_STR { $$ = new NStringType(); }
    | KW_BOOL { $$ = new NBoolType(); }
    | KW_NUM { $$ = new NNumType(); }
    | KW_TABLE OP_LSQUARE_BRACE type_ident OP_COMMA type_ident OP_RSQUARE_BRACE { $$ = new NTableType($3, $5); }
    | KW_NIL { $$ = new NNilType(); }
    | function_type
    | ID { $$ = new NStructType(new NIdentifier($ID, Position(@ID.first_line, @ID.first_column))); }
    ;

typelist : type_ident { $$ = new std::vector<NType *>(); $$->push_back($1); }
    | typelist OP_COMMA type_ident { $$->push_back($3); }
    ;

function_type: KW_FUNCTION OP_LBRACE typelist OP_RBRACE OP_ARROW typelist { $$ = new NFunctionType(NIdentifier::fromTypeList($3), $6); }
    | KW_FUNCTION OP_LBRACE typelist OP_RBRACE { $$ = new NFunctionType(NIdentifier::fromTypeList($3), {}); }
    | KW_FUNCTION OP_LBRACE OP_RBRACE OP_ARROW typelist { $$ = new NFunctionType(nullptr, $5); }
    | KW_FUNCTION OP_LBRACE OP_RBRACE { $$ = new NFunctionType({}, {}); }
    ;

ident : ID { $$ = new NIdentifier($ID, Position(@ID.first_line, @ID.first_column)); delete $1; }
    ;
%%