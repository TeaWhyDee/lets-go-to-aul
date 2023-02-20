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
#define PROCESS_QUOTE if (yytext == str_init){std::cout << "STRING_LITERAL[" << str << "] "; BEGIN(INITIAL);}\
            else {str += yytext;}
#define PROCESS_BRACKETS if (std::string(yytext).length() == str_bracketlen) {\
            std::cout << "STRING_LITERAL[" << str << "] "; BEGIN(INITIAL);}\
            else { str += yytext; }

void yyerror (char const *s) { fprintf (stderr, "%s\n", s); }
%}

%x STRING
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

[0-9]+[.]?[0-9]*   {printf("NUMBER_LITERAL ");}
[+]          {printf("+ ");}
[-]          {printf("- ");}
[*]          {printf("* ");}
[/]          {printf("/ ");}
[\%]         {printf("% ");}
[#]          {printf("# ");}
[=][=]       {printf("== ");}
[~][=]       {printf("~= ");}
[~]          {printf("~ ");}
[<][=]       {printf("<= ");}
[>][=]       {printf(">= ");}
[<]          {printf("< ");}
[>]          {printf("> ");}
[=]          {printf("= ");}
\(           {printf("( ");}
\)           {printf(") ");}
[{]          {printf("{ ");}
[}]          {printf("} ");}
\[           {printf("[ ");}
\]           {printf("] ");}
[;]          {printf("OP_SEMICOLON ");}
[:]          {printf("OP_COLON ");}
[,]          {printf("OP_COMMA ");}
[.]          {printf("OP_DOT ");}
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
