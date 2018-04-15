#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define BSIZE 128 //Buffer size
#define NONE -1
#define EOS '\0'
#define NUM 256
#define DIV 257
#define MOD 258
#define ID 259
#define DONE 260

int tokenval; // value of token attribute;

int lineno;
struct entry 
{
    char *lexptr;
    int token;
};
struct entry symtable[100];