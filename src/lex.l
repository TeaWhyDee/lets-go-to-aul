%{
#include <iostream>
#include <string>
int enter_dblquotes = 0;
std::string str;
#define NEW_STR str = std::string();
#define ADD_STR str += yytext;
void yyerror (char const *s) {
   /* fprintf (stderr, "%s\n", s); */
   printf("%s\n", s);
}
%}

%x SINGLE_STRING

%%
[ \t]+
\"                          { NEW_STR; BEGIN(SINGLE_STRING); }
<SINGLE_STRING>{
  \\\n              {str += "\n";}
  /* escape other characters */
  \n                yyerror("the string misses \" to termiate before newline");
  <<EOF>>           yyerror("the string misses \" to terminate before EOF");
  ([^\\\"\n]|\\.)*  {ADD_STR;}
  \"                {std::cout << "STRING_LITERAL[" << str << "] "; BEGIN(INITIAL);}
  .                 ;
}
[0-9]+[.]?[0-9]*   {printf("NUMBER_LITERAL ");}
[+]          {printf("OP_PLUS ");}
[-]          {printf("OP_MINUS ");}
[*]          {printf("OP_STAR ");}
[/]          {printf("OP_SLASH ");}
[\%]         {printf("OP_PERCENT ");}
[#]          {printf("OP_HASH ");}
[=][=]       {printf("OP_EQUALEQUAL ");}
[~][=]       {printf("OP_NOTEQUAL ");}
[~]          {printf("OP_TILDE ");}
[<][=]       {printf("OP_LESSTHAN ");}
[>][=]       {printf("OP_LARGERTHAN ");}
[<]          {printf("OP_LESS ");}
[>]          {printf("OP_MORE ");}
[=]          {printf("OP_EQUAL ");}
[(]          {printf("OP_LBRACE ");}
[)]          {printf("OP_RBRACE ");}
[{]          {printf("OP_LCURLY_BRACE ");}
[}]          {printf("OP_RCURLY_BRACE ");}
[;]          {printf("OP_SEMICOLON ");}
[:]          {printf("OP_COLON ");}
[,]          {printf("OP_COMMA ");}
[.]          {printf("OP_DOT ");}
[a-zA-z][a-zA-z0-9_]*\(\)  {printf("FUNCTION_CALL ");}
num        {printf("KW_NUM ");}
str        {printf("KW_STR ");}
tuple      {printf("KW_TUPLE ");}
nil        {printf("KW_NIL ");}
and        {printf("KW_AND ");}
break      {printf("KW_BREAK ");}
do         {printf("KW_DO ");}
else       {printf("KW_ELSE ");}
elseif     {printf("KW_ELSEIF ");}
end        {printf("KW_END ");}
false      {printf("KW_FALSE ");}
for        {printf("KW_FOR ");}
function   {printf("KW_FUNCTION ");}
if         {printf("KW_IF ");}
in         {printf("KW_IN ");}
local      {printf("KW_LOCAL ");}
not        {printf("KW_NOT ");}
or         {printf("KW_OR ");}
repeat     {printf("KW_REPEAT ");}
return     {printf("KW_RETURN ");}
then       {printf("KW_THEN ");}
true       {printf("KW_TRUE ");}
until      {printf("KW_UNTIL ");}
while      {printf("KW_WHILE ");}
[a-zA-z][a-zA-z0-9_]*  {printf("ID ");}
--.+       {printf("COMMENT");}
%%
  
int yywrap(){}
int main(){
    yylex();
    printf(" ");
    
    return 0;
}
