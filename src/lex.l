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
#define PROCESS_QUOTE if (yytext == str_init){std::cout << C_YELLOW << "STRING_LITERAL[" << str << "] " << C_NONE; BEGIN(INITIAL);}\
            else {str += yytext;}
#define PROCESS_BRACKETS if (std::string(yytext).length() == str_bracketlen) {\
            std::cout << C_YELLOW << "STRING_LITERAL[" << str << "] " << C_NONE; BEGIN(INITIAL);}\
            else { str += yytext; }

int comment_bracklen = 0;
#define NEW_COMMENT { comment_bracklen = std::string(yytext).length() - 2; }
#define PROCESS_COMMENT_BRACKETS if (std::string(yytext).length() == comment_bracklen) {\
            std::cout << C_GREY << "COMMENT " << C_NONE; BEGIN(INITIAL);}

#define C_MAGENTA "\033[38;2;255;36;100m"
#define C_NONE "\033[0m"
#define C_PURPLE "\033[38;2;190;139;249m"
#define C_YELLOW "\033[38;2;236;212;108m"
#define C_GREEN "\033[38;2;150;204;68m"
#define C_CYAN "\033[38;2;58;220;238m"
#define C_ORANGE "\033[38;2;255;146;51m"
#define C_GREY "\033[38;2;150;150;150m"

void yyerror (char const *s) { fprintf (stderr, "ERROR: %s\n", s); }

struct span {
    unsigned int lineno;
    unsigned int pos;
};

struct declaration {
    struct span *sp;
};
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

0(x|X)[0-9a-fA-f]+ {printf("HEX_LITERAL[%s] ", yytext);}
0(b|B)[0-1]+ {printf("BIN_LITERAL[%s] ", yytext);}
[0-9]+[.]?[0-9]*   {printf("\033[38;2;190;139;249mNUMBER_LITERAL[%s]\033[0m ", yytext);}
[-][>]       {printf("%s%s%s", C_MAGENTA, "-> ", C_NONE);}
[+]          {printf("%s%s%s", C_MAGENTA, "+ ", C_NONE);}
[-]          {printf("%s%s%s", C_MAGENTA, "- ", C_NONE);}
[*]          {printf("%s%s%s", C_MAGENTA, "* ", C_NONE);}
[/]          {printf("%s%s%s", C_MAGENTA, "/ ", C_NONE);}
[\%]         {printf("%s%s%s", C_MAGENTA, "%% ", C_NONE);}
[#]          {printf("%s%s%s", C_MAGENTA, "# ", C_NONE);}
[=][=]       {printf("%s%s%s", C_MAGENTA, "== ", C_NONE);}
[~][=]       {printf("%s%s%s", C_MAGENTA, "~= ", C_NONE);}
[~]          {printf("%s%s%s", C_MAGENTA, "~ ", C_NONE);}
[<][=]       {printf("%s%s%s", C_MAGENTA, "<= ", C_NONE);}
[>][=]       {printf("%s%s%s", C_MAGENTA, ">= ", C_NONE);}
[<]          {printf("%s%s%s", C_MAGENTA, "< ", C_NONE);}
[>]          {printf("%s%s%s", C_MAGENTA, "> ", C_NONE);}
[=]          {printf("%s%s%s", C_MAGENTA, "= ", C_NONE);}
\(           {printf("( ");}
\)           {printf(") ");}
[{]          {printf("{ ");}
[}]          {printf("} ");}
\[           {printf("[ ");}
\]           {printf("] ");}
[;]          {printf("; ");}
[:]          {printf(": ");}
[,]          {printf(", ");}
[.]          {printf(". ");}
num          {printf("%s%s%s", C_ORANGE, "KW_NUM ", C_NONE);}
str          {printf("%s%s%s", C_ORANGE, "KW_STR ", C_NONE);}
table        {printf("%s%s%s", C_ORANGE, "KW_TABLE ", C_NONE);}
nil          {printf("%s%s%s", C_ORANGE, "KW_NIL ", C_NONE);}
and          {printf("KW_AND ");}
break        {printf("KW_BREAK ");}
do           {printf("KW_DO ");}
else         {printf("KW_ELSE ");}
elseif       {printf("KW_ELSEIF ");}
bool         {printf("KW_BOOL");}
end          {printf("%s%s%s", C_MAGENTA, "KW_END ", C_NONE);}
false        {printf("%s%s%s", C_PURPLE, "KW_FALSE ", C_NONE);}
for          {printf("KW_FOR ");}
function     {printf("%s%s%s", C_CYAN, "KW_FUNCTION ", C_NONE);}
if           {printf("KW_IF ");}
in           {printf("KW_IN ");}
local        {printf("KW_LOCAL ");}
not          {printf("KW_NOT ");}
or           {printf("KW_OR ");}
repeat       {printf("KW_REPEAT ");}
return       {printf("%s%s%s", C_MAGENTA, "KW_RETURN ", C_NONE);}
then         {printf("%s%s%s", C_MAGENTA, "KW_THEN ", C_NONE);}
true         {printf("%s%s%s", C_PURPLE, "KW_TRUE ", C_NONE);}
until        {printf("KW_UNTIL ");}
while        {printf("KW_WHILE ");}
[a-zA-Z_][a-zA-Z0-9_]*  {printf("%s%s%s%s%s", C_GREEN, "ID[", yytext, "] ", C_NONE);}
--.+         {printf("%s%s%s", C_GREY, "COMMENT", C_NONE);}
.            {printf("%s", "UNKNOWN_TOKEN");}
%%
  
int yywrap(){return 1;}
int main(){
    yylex();
    return 0;
}
