#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>

#define LIMIT 100

char keywords[][LIMIT] = {
	"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum",
	"extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static",
	"struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};
char arithmeticOps[][LIMIT] = {"+", "-", "*", "/", "%"};
char arithmeticAssignmentOps[][LIMIT] = {"+=", "-=", "*=", "/=", "%="};
char relationalOps[][LIMIT] = {"<", "<=", ">", ">=", "==", "!="};
char bitwiseOps[][LIMIT] = {"^", "&", "|", "<<", ">>"};
char unaryOps[][LIMIT] = {"-", "++", "--"};
char assignmentOp[][LIMIT] = {"="};
char specialCharacters[][LIMIT] = {";", ",", ".", "[", "]", "(", ")", "{", "}", "[", "]"};
char functionCalls[][LIMIT] = {"printf", "scanf", "getch", "clrscr", "main"};

typedef struct Table
{
	char identifierName[LIMIT];
	char type[LIMIT];
	int bytes;
	int address;
	char value[LIMIT];
} Table;

// int len_keyword = 32;
// int len_arithmeticOps = 5;
// int len_arithmeticAssignmentOps = 5;
// int len_relationalOps = 6;
// int len_bitwiseOps = 5;
// int len_unaryOps = 3;
// int len_assignmentOp = 1;
// int len_specialCharacters = 11;