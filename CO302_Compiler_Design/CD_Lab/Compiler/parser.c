#include "global.h"
int lookahead;

parse( )
{
    lookahead = lexan();
    while (lookahead != DONE) 
    {
        expr(); match(';');
    }
}

expr( )
{
    int t;
    term();
    while(1)
        switch (lookahead) 
        {
        case '+' : case '-':
            t = lookahead;
            match(lookahead); term(); emit(t, NONE);
            continue;
        default:
            return;
        }
}

term()
{
    int t;
    factor();
    while(1)
        switch (lookahead) 
        {
            case '*' : case '/' : case DIV : case MOD:
                t = lookahead;
                match(lookahead); factor(); emit(t, NONE);
                continue;
            default:
                return;
        }
}

factor()
{
    switch(lookahead) 
    {
        case '(':
            match('('); expr(); match(')'); break;
        case NUM:
            emit (NUM, tokenval); match(NUM); break;
        case ID:
            emit(ID, tokenval); match(ID); break;
        default:
            error("syntax error");
    }
}

match(t)
    int t;
{
    if (lookahead == t)
        lookahead = lexan();
    else error("syntax error");
}