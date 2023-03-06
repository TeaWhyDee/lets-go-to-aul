%{
#include <iostream>
#include <string>
int enter_dblquotes = 0;
std::string str;
std::string str_init = std::string();
int str_bracketlen = 0;
#define NEW_STR str = std::string();
#define ADD_STR str += yytext;
#define STR_NUM_ESCAPE {std::string s = std::string(yytext); s.erase(0, 1); \
            int n = stoi(s); if (n > 255){yyerror("decimal escape too large");}\
            else {char c = stoi(s); str += c;} }
#define PROCESS_QUOTE if (yytext == str_init){std::cout << "L_STRING" << str << "] "; BEGIN(INITIAL);}\
            else {str += yytext;}
#define PROCESS_BRACKETS if (std::string(yytext).length() == str_bracketlen) {\
            std::cout << "L_STIRNG[" << str << "] "; BEGIN(INITIAL);}\
            else { str += yytext; }

int comment_bracklen = 0;
#define NEW_COMMENT { comment_bracklen = std::string(yytext).length() - 2; }
#define PROCESS_COMMENT_BRACKETS if (std::string(yytext).length() == comment_bracklen) {\
            std::cout << "COMMENT "; BEGIN(INITIAL);}

void yyerror (char const *s) { fprintf (stderr, "ERROR: %s\n", s); }
%}

%x STRING
%x COMMENT
%x STRING_NOESCAPE

%%
[ \t]+
[\"\']              { NEW_STR; str_init=yytext; BEGIN(STRING); }
\]=*\]              { yyerror("right square bracket before left square bracket"); }
<STRING>{
  "\\\n"            {str += "\n";}
  "\\\""            {str += '"';}
  "\\'"             {str += "'";}
  "\\\\"            {str += "\\";}
  "\\n"             {str += "\n";}
  "\\a"             {str += "\a";}
  "\\b"             {str += "\b";}
  "\\f"             {str += "\f";}
  "\\r"             {str += "\r";}
  "\\t"             {str += "\t";}
  "\\v"             {str += "\v";}
  \\[0-9]{1,3}      STR_NUM_ESCAPE
  \n                yyerror("the string misses \" to termiate before newline");
  <<EOF>>           yyerror("the string misses \" to terminate before EOF");
  [\"\']            PROCESS_QUOTE
  ([^\\\""\n])*     {ADD_STR}
  .                 {ADD_STR};
}

\[=*\[              { NEW_STR; str_bracketlen = std::string(yytext).length(); BEGIN(STRING_NOESCAPE); }
<STRING_NOESCAPE>{
  "\n"              {str += "\n";}
  \]=*\]            PROCESS_BRACKETS
  ([^\n\]\[=])*     {ADD_STR}
  .                 {ADD_STR}
}

\-\-\[=*\[     { NEW_COMMENT; BEGIN(COMMENT); }
<COMMENT>{
    <<EOF>>        { yyerror("the comment doesn't close"); BEGIN(INITIAL); }
    \]=*\]         PROCESS_COMMENT_BRACKETS
    ([^\]])*       {ADD_STR}
    .              {ADD_STR}
}

[0-9]+[.]?[0-9]*   {printf("L_NUM ");}
[-][>]       {printf("OP_ARROW ");}
[+]          {printf("OP_PLUS ");}
[-]          {printf("OP_MINUS ");}
[*]          {printf("OP_STAR ");}
[/][/]       {printf("OP_SLASHSLASH ");}
[/]          {printf("OP_SLASH ");}
[\%]         {printf("OP_PERCENT ");}
[#]          {printf("OP_HASH ");}
[=][=]       {printf("OP_EQUALEQUAL ");}
[~][=]       {printf("OP_NOTEQUAL ");}
[<][=]       {printf("OP_LESSTHAN ");}
[>][=]       {printf("OP_LARGERTHAN ");}
[<]          {printf("OP_LESS ");}
[>]          {printf("OP_MORE ");}
[=]          {printf("OP_EQUAL ");}
\(           {printf("OP_LBRACE ");}
\)           {printf("OP_RBRACE ");}
[{]          {printf("OP_LCURLY_BRACE ");}
\[           {printf("OP_LSQUARE_BRACE ");}
\]           {printf("OP_RSQUARE_BRACE ");}
[}]          {printf("OP_RCURLY_BRACE ");}
[;]          {printf("OP_SEMICOLON ");}
[:]          {printf("OP_COLON ");}
[,]          {printf("OP_COMMA ");}
[.][.]       {printf("OP_DOTDOT ");}
[.]          {printf("OP_DOT ");}
struct       {printf("KW_STRUCT ");}
const        {printf("KW_CONST ");}
num          {printf("KW_NUM ");}
str          {printf("KW_STR ");}
table        {printf("KW_TABLE ");}
nil          {printf("KW_NIL ");}
and          {printf("KW_AND ");}
break        {printf("KW_BREAK ");}
do           {printf("KW_DO ");}
else         {printf("KW_ELSE ");}
elseif       {printf("KW_ELSEIF ");}
end          {printf("KW_END ");}
false        {printf("KW_FALSE ");}
for          {printf("KW_FOR ");}
function     {printf("KW_FUNCTION ");}
if           {printf("KW_IF ");}
in           {printf("KW_IN ");}
local        {printf("KW_LOCAL ");}
not          {printf("KW_NOT ");}
or           {printf("KW_OR ");}
repeat       {printf("KW_REPEAT ");}
return       {printf("KW_RETURN ");}
then         {printf("KW_THEN ");}
true         {printf("KW_TRUE ");}
until        {printf("KW_UNTIL ");}
while        {printf("KW_WHILE ");}
[a-zA-Z0-9_]*  {printf("ID[%s] ", yytext);}
--.+         {printf("COMMENT");}
.            {printf(yytext);}
%%
  
int yywrap(){}
int main(){
    yylex();
    printf(" ");
    
    return 0;
}
