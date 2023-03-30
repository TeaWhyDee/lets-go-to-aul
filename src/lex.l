%{
#include "node.h"
#include "parser.hpp"
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)
extern "C" int yywrap() {}

#include <iostream>
#include <string>
int enter_dblquotes = 0;
bool str_error = false;
std::string str;
std::string str_init = std::string();
int str_bracketlen = 0;
#define NEW_STR str = std::string(); str_error = false;
#define ADD_STR str += yytext;
#define STR_NUM_ESCAPE SAVE_TOKEN;\
            {std::string s = std::string(yytext); s.erase(0, 1); \
                int n = stoi(s); if (n > 255){yyerror("decimal escape too large");}\
            else {char c = stoi(s); str += c;} }
#define PROCESS_QUOTE SAVE_TOKEN;\
            if (yytext == str_init) {\
                yylval.string = new std::string(str); BEGIN(INITIAL);\
                if (!str_error) return L_STRING;\
                else return ERROR;}\
            else {str += yytext;}
#define PROCESS_BRACKETS \
            if (std::string(yytext).length() == str_bracketlen) {\
                BEGIN(INITIAL);\
                if (!str_error) {\
                    yylval.string = new std::string(str); return L_STRING; }\
                else return ERROR;}\
            else { str += yytext; }

long unsigned int comment_bracklen = 0;
#define NEW_COMMENT { comment_bracklen = std::string(yytext).length() - 2; }
#define PROCESS_COMMENT_BRACKETS if (std::string(yytext).length() == comment_bracklen) {\
            BEGIN(INITIAL);}

 /* ERROR HANDLING STUFF */
#define YY_USER_INIT BEGIN(STARTUP);
void yyerror (char const *s);
char linebuf[500];
std::string errortext = std::string();
%}

%option yylineno

%x STARTUP
%x STRING
%x COMMENT_BRACKETS
%x STRING_NOESCAPE

%%
<STARTUP>{
    ^[^\n]* { strncpy(linebuf, yytext+1, sizeof(linebuf)); BEGIN(INITIAL); yyless(0); }
}

\n.* { strncpy(linebuf, yytext+1, sizeof(linebuf));
    yyless(1);
}

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
  /* \n                {yyerror("the string misses closing quote to termiate before newline");} */
  /* <<EOF>>           {yyerror("the string misses closing quote to terminate before EOF");} */
  \n                {str_error = true; errortext = "Unexpected \\n, string not closed.";}
  <<EOF>>           {str_error = true; BEGIN(INITIAL); errortext = "Unexpected end of file, string not closed.";}
  [\"\']            PROCESS_QUOTE
  ([^\\\""\\'\n])*  {ADD_STR}
  .                 {ADD_STR};
}

\[=*\[              { NEW_STR; str_bracketlen = std::string(yytext).length(); BEGIN(STRING_NOESCAPE); }
<STRING_NOESCAPE>{
  "\n"              {str += "\n";}
  \]=*\]            PROCESS_BRACKETS
  ([^\n\]\[=])*     {ADD_STR}
  .                 {ADD_STR}
}

\-\-\[=*\[     { NEW_COMMENT; BEGIN(COMMENT_BRACKETS); }
<COMMENT_BRACKETS>{
    <<EOF>>        { errortext = "Unexpected EOF, the comment doesn't close"; BEGIN(INITIAL); }
    \]=*\]         PROCESS_COMMENT_BRACKETS
    ([^\]])*       {ADD_STR}
    .              {ADD_STR}
}
--.+           {return COMMENT;}

[ \t]+
[\"\']              { NEW_STR; str_init=yytext; BEGIN(STRING); }
\]=*\]              { errortext = "Unexpected closing square bracket."; return ERROR;}
[0-9]+[.]?[0-9]*   {SAVE_TOKEN; return L_NUM ;}
[-][>]       {return OP_ARROW ;}
[+]          {return OP_PLUS ;}
[-]          {return OP_MINUS ;}
[*]          {return OP_STAR ;}
[/][/]       {return OP_SLASHSLASH ;}
[/]          {return OP_SLASH ;}
[\%]         {return OP_PERCENT ;}
[#]          {return OP_HASH ;}
[=][=]       {return OP_EQUALEQUAL ;}
[~][=]       {return OP_NOTEQUAL ;}
[<][=]       {return OP_LESSTHAN ;}
[>][=]       {return OP_LARGERTHAN ;}
[<]          {return OP_LESS ;}
[>]          {return OP_MORE ;}
[=]          {return OP_EQUAL ;}
\(           {return OP_LBRACE ;}
\)           {return OP_RBRACE ;}
[;]          {return OP_SEMICOLON ;}
[:]          {return OP_COLON ;}
[,]          {return OP_COMMA ;}
[.][.]       {return OP_DOTDOT ;}
[.]          {return OP_DOT ;}
const        {return KW_CONST ;}
new          {return KW_NEW ;}
self         {return KW_SELF ;}
static       {return KW_STATIC ;}
struct       {return KW_STRUCT ;}
num          {return KW_NUM ;}
str          {return KW_STR ;}
bool         {return KW_BOOL ;}
table        {return KW_TABLE ;}
nil          {return KW_NIL ;}
and          {return KW_AND ;}
break        {return KW_BREAK ;}
do           {return KW_DO ;}
else         {return KW_ELSE ;}
elseif       {return KW_ELSEIF ;}
end          {return KW_END ;}
false        {return KW_FALSE ;}
for          {return KW_FOR ;}
function     {return KW_FUNCTION ;}
if           {return KW_IF ;}
in           {return KW_IN ;}
local        {return KW_LOCAL ;}
not          {return KW_NOT ;}
or           {return KW_OR ;}
repeat       {return KW_REPEAT ;}
return       {return KW_RETURN ;}
then         {return KW_THEN ;}
true         {return KW_TRUE;}
until        {return KW_UNTIL ;}
while        {return KW_WHILE ;}
[a-zA-Z0-9_]*  {SAVE_TOKEN; return L_STRING;}
.            {return ERROR;}
%%
  
/* int yywrap(){} */
/* int main(){ */
/*     yylex(); */
/*     printf(" "); */
/*      */
/*     return 0; */
/* } */
