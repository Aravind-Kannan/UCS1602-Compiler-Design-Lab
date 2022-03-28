%{
#include <stdio.h>
int print(char token[], char tokenType[])
{
    printf("%s\t\t\t--->%s\n", token, tokenType);
}
%}

ws [ \t]
digit [0-9]
alpha [a-zA-Z]
keyword (auto)|(break)|(case)|(char)|(const)|(continue)|(default)|(do)|(double)|(else)|(enum)|(extern)|(float)|(for)|(goto)|(if)|(int)|(long)|(register)|(return)|(short)|(signed)|(sizeof)|(static)|(struct)|(switch)|(typedef)|(union)|(unsigned)|(void)|(volatile)|(while)
arithmetic (\+)|(\-)|(\*)|(\/)|(%)
relational (>)|(<)|(>=)|(<=)|(==)|(!=)
logical (!)|(&&)|(\|\|)
special (;)|(,)|(\.)|(\[)|(\])|(\{)|(\})|(\()|(\))
bitwise (^)|(&)|(\|)|(>>)|(<<)
unary (\+\+)|(\-\-)|(\-)

%%
\n {}
ws+ {}
{keyword} {print(yytext, "Keyword");}
#.* {print(yytext, "Preprocessor Directive");}
(_|{alpha})+(_|{alpha}|{digit})* {print(yytext, "Identifier");}
{digit}+ {print(yytext, "Integer Constant");}
{digit}+\.{digit} {print(yytext, "Double Constant");}
\'.\' {print(yytext, "Character Constant");}
\".*\" {print(yytext, "String Constant");}
{arithmetic} {print(yytext, "Arithmetic Operator");}
{arithmetic}= {print(yytext, "Arithmetic Assignment Operator");}
{relational} {print(yytext, "Relational Operator");}
{logical} {print(yytext, "Logical Operator");}
{special} {print(yytext, "Special Character");}
({alpha}|_)+\(.*\) {print(yytext, "Function");}
\/\/.* {print(yytext, "Single Line Comment");}
\/\*(.|\n)*\*\/ {print(yytext, "Multi Line Comment");}
= {print(yytext, "Assignment Operator");}
{bitwise} {print(yytext, "Bitwise Operator");}
{unary} {print(yytext, "Unary Operator");}
%%



int main(int argc, char* argv[])
{
    yyin = fopen(argv[1],"r");
    yylex();
    return 0;
}
