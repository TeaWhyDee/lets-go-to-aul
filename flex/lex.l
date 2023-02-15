
/*** Definition Section has one variable
which can be accessed inside yylex() 
and main() ***/
%{
int count = 0;
%}

/*  
    The following should not only print, but also return shit,
    I think we need bison configured first.
*/
%%
[ \t]+
\".+\"       {printf("STRING_LITERAL\n");}
[0-9]+  {printf("NUM\n");}
[+]          {printf("OP_PLUS\n");}
[-]          {printf("OP_MINUS\n");}
[*]          {printf("OP_STAR\n");}
[/]          {printf("OP_SLASH\n");}
[\%]          {printf("OP_PERCENT\n");}
[#]          {printf("OP_HASH\n");}
[=][=]         {printf("OP_EQUALEQUAL\n");}
[~][=]          {printf("OP_NOTEQUAL\n");}
[~]          {printf("OP_TILDE\n");}
[<][=]         {printf("OP_LESSTHAN\n");}
[>][=]         {printf("OP_LARGERTHAN\n");}
[<]          {printf("OP_LESS\n");}
[>]          {printf("OP_MORE\n");}
[=]          {printf("OP_EQUAL\n");}
[(]          {printf("OP_OPENING_BRACKET\n");}
[)]          {printf("OP_CLOSING_BRACKET\n");}
[{]          {printf("OP_OPENING_CURLY_BRACKET\n");}
[}]          {printf("OP_CLOSING_CURLY_BRACKET\n");}
[;]          {printf("OP_SEMICOLON\n");}
[:]          {printf("OP_COLON\n");}
[,]          {printf("OP_COMMA\n");}
[.]          {printf("OP_DOT\n");}
[a-zA-z][a-zA-z0-9_]*\(\) {printf("FUNCTION_CALL\n");}
num {printf("KW_NUM\n");}
str {printf("KW_STR\n");}
tuple {printf("KW_TUPLE\n");}
nil        {printf("KW_NIL\n");}
and        {printf("KW_AND\n");}
break      {printf("KW_BREAK\n");}
do         {printf("KW_DO\n");}
else       {printf("KW_ELSE\n");}
elseif     {printf("KW_ELSEIF\n");}
end        {printf("KW_END\n");}
false      {printf("KW_FALSE\n");}
for        {printf("KW_FOR\n");}
function   {printf("KW_FUNCTION\n");}
if         {printf("KW_IF\n");}
in         {printf("KW_IN\n");}
local      {printf("KW_LOCAL\n");}
not        {printf("KW_NOT\n");}
or         {printf("KW_OR\n");}
repeat     {printf("KW_REPEAT\n");}
return     {printf("KW_RETURN\n");}
then       {printf("KW_THEN\n");}
true       {printf("KW_TRUE\n");}
until      {printf("KW_UNTIL\n");}
while      {printf("KW_WHILE\n");}
[a-zA-z][a-zA-z0-9_]* {printf("ID\n");}
%%
  
int yywrap(){}
int main(){
    yylex();
    printf("\n");
    
    return 0;
}
