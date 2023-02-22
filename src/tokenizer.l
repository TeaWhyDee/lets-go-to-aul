%{
#include <iostream>
#include <string>
#include "tokens.cpp"

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

0(x|X)[0-9a-fA-f]+ {yylval.string=yytext; return HEX_LITERAL}
0(b|B)[0-1]+ {yylval.string=yytext; return BIN_LITERAL;}
[0-9]+[.]?[0-9]*   {yylval.number=stold(yytext); return NUMBER_LITERAL;}
[->]       {return RIGHT_ARROW;}
num          {return KW_NUM;}
str          {return KW_STR;}
table        {return KW_TABLE;}
nil          {return KW_NIL;}
and          {return KW_AND;}
break        {return KW_BREAK;}
do           {return KW_DO;}
else         {return KW_ELSE;}
elseif       {return KW_ELSEIF;}
bool         {return KW_BOOL;}
end          {return KW_END;}
false        {return KW_FALSE;}
for          {return KW_FOR;}
function     {return KW_FUNCTION;}
if           {return KW_IF;}
in           {return KW_IN;}
local        {return KW_LOCAL;}
not          {return KW_NOT;}
or           {return KW_OR;}
repeat       {return KW_REPEAT;}
return       {return KW_RETURN;}
then         {return KW_THEN;}
true         {return KW_TRUE;}
until        {return KW_UNTIL;}
while        {return KW_WHILE;}
[a-zA-Z0-9_]*  {yylval.string=yytext; return ID;}
--.+         {}
.            {}
%%
  
int yywrap(){return 1;}
int main(){
    yylex();
    return 0;
}
