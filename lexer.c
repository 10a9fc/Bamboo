#include "lexer.h"

#pragma warning(disable:4996)

Dictionary* tokenDic;

Lexer* Init_Lexer(char* data)
{
    Lexer* lexer = malloc(sizeof(Lexer));

    lexer->tokens = Init_LinkedList();
    lexer->pos = 0;
    lexer->line = 1;
    lexer->p = NULL;

    int len = strlen(data);
    lexer->data = malloc(len + 1);
    strcpy(lexer->data, data);

    lexer->len = len;

    return lexer;
}

void Destroy_Lexer(Lexer* lexer)
{
    free(lexer->data);

    Foreach_LinkedList(lexer->tokens, Destroy_Token);
    Destroy_LinkedList(lexer->tokens);

    free(lexer);
}

int Line_Lexer(Lexer* lexer)
{
    return lexer->line;
}

int Pos_Lexer(Lexer* lexer)
{
    return lexer->pos;
}


void Skin_White_Space(Lexer* lexer)
{
    while (Has_Next(lexer))
    {
        if (Read_Char(lexer) == '\n')
        {
            Next_Char(lexer);
            lexer->line += 1;
        }
        else if (Read_Char(lexer) == '\t' || Read_Char(lexer) == ' ')
        {
            Next_Char(lexer);
        }
        else
        {
            return;
        }
    }
}

char Read_Char(Lexer* lexer)
{
    return lexer->data[lexer->pos];
}

void Next_Char(Lexer* lexer)
{
    lexer->pos += 1;
}

bool Has_Next(Lexer* lexer)
{
    return lexer->pos < lexer->len;
}


void Do_Lexer(Lexer* lexer)
{
    while (Has_Next(lexer))
    {
        Skin_White_Space(lexer);

        switch (Read_Char(lexer))
        {
        case '+':
            Next_Char(lexer);
            if (Read_Char(lexer) == '=') {
                Add_Token_Lexer(lexer, Init_Token(TOKEN_PLUS_ASSIGN, NULL, Line_Lexer(lexer), Pos_Lexer(lexer))); Next_Char(lexer);
            }
            else {
                Add_Token_Lexer(lexer, Init_Token(TOKEN_PLUS, NULL, Line_Lexer(lexer), Pos_Lexer(lexer)));
            }
            continue;
        case '-':
            Next_Char(lexer);
            if (Read_Char(lexer) == '=') {
                Add_Token_Lexer(lexer, Init_Token(TOKEN_MINUS_ASSIGN, NULL, Line_Lexer(lexer), Pos_Lexer(lexer))); Next_Char(lexer);
            }
            else {
                Add_Token_Lexer(lexer, Init_Token(TOKEN_MINUS, NULL, Line_Lexer(lexer), Pos_Lexer(lexer)));
            }
            continue;
        case '*':
            Next_Char(lexer);
            if (Read_Char(lexer) == '=') {
                Add_Token_Lexer(lexer, Init_Token(TOKEN_ASTERISK_ASSIGN, NULL, Line_Lexer(lexer), Pos_Lexer(lexer))); Next_Char(lexer);
            }
            else {
                Add_Token_Lexer(lexer, Init_Token(TOKEN_ASTERISK, NULL, Line_Lexer(lexer), Pos_Lexer(lexer)));
            }
            continue;
        case '/':
            Next_Char(lexer);
            if (Read_Char(lexer) == '=') {
                Add_Token_Lexer(lexer, Init_Token(TOKEN_SLASH_ASSIGN, NULL, Line_Lexer(lexer), Pos_Lexer(lexer))); Next_Char(lexer);
            }
            else {
                Add_Token_Lexer(lexer, Init_Token(TOKEN_SLASH, NULL, Line_Lexer(lexer), Pos_Lexer(lexer)));
            }
            continue;
        case '=':
            Next_Char(lexer);
            if (Read_Char(lexer) == '=') {
                Add_Token_Lexer(lexer, Init_Token(TOKEN_ASSIGN_ASSIGN, NULL, Line_Lexer(lexer), Pos_Lexer(lexer))); Next_Char(lexer);
            }
            else {
                Add_Token_Lexer(lexer, Init_Token(TOKEN_ASSIGN, NULL, Line_Lexer(lexer), Pos_Lexer(lexer)));
            }
            continue;
        case '<':
            Next_Char(lexer);
            if (Read_Char(lexer) == '=') {
                Add_Token_Lexer(lexer, Init_Token(TOKEN_LESS_ASSIGN, NULL, Line_Lexer(lexer), Pos_Lexer(lexer))); Next_Char(lexer);
            }
            else {
                Add_Token_Lexer(lexer, Init_Token(TOKEN_LESS, NULL, Line_Lexer(lexer), Pos_Lexer(lexer)));
            }
            continue;
        case '>':
            Next_Char(lexer);
            if (Read_Char(lexer) == '=') {
                Add_Token_Lexer(lexer, Init_Token(TOKEN_GREATER_ASSIGN, NULL, Line_Lexer(lexer), Pos_Lexer(lexer))); Next_Char(lexer);
            }
            else {
                Add_Token_Lexer(lexer, Init_Token(TOKEN_GREATER, NULL, Line_Lexer(lexer), Pos_Lexer(lexer)));
            }
            continue;
        case '!':
            Next_Char(lexer);
            if (Read_Char(lexer) == '=') {
                Add_Token_Lexer(lexer, Init_Token(TOKEN_NOT_ASSIGN, NULL, Line_Lexer(lexer), Pos_Lexer(lexer))); Next_Char(lexer);
            }
            else {
                Add_Token_Lexer(lexer, Init_Token(TOKEN_NOT, NULL, Line_Lexer(lexer), Pos_Lexer(lexer)));
            }
            continue;
        case '(':
            Add_Token_Lexer(lexer, Init_Token(TOKEN_LPAREN, NULL, Line_Lexer(lexer), Pos_Lexer(lexer))); Next_Char(lexer);
            continue;
        case ')':
            Add_Token_Lexer(lexer, Init_Token(TOKEN_RPAREN, NULL, Line_Lexer(lexer), Pos_Lexer(lexer))); Next_Char(lexer);
            continue;
        case '{':
            Add_Token_Lexer(lexer, Init_Token(TOKEN_LBRACE, NULL, Line_Lexer(lexer), Pos_Lexer(lexer))); Next_Char(lexer);
            continue;
        case '}':
            Add_Token_Lexer(lexer, Init_Token(TOKEN_RBRACE, NULL, Line_Lexer(lexer), Pos_Lexer(lexer))); Next_Char(lexer);
            continue;
        case ';':
            Add_Token_Lexer(lexer, Init_Token(TOKEN_SEMICOLON, NULL, Line_Lexer(lexer), Pos_Lexer(lexer))); Next_Char(lexer);
            continue;
        }

        Read_Token(lexer);
    }
    Add_Token_Lexer(lexer, Init_Token(TOKEN_EOF, NULL, 0, 0));
    lexer->p = lexer->tokens->head;
}

void Add_Token_Lexer(Lexer* lexer, Token* token)
{
    PushBack_LinkedList(lexer->tokens, token);
}

void Read_Token(Lexer* lexer)
{
    int len = 0;
    char* start = lexer->data + lexer->pos;


    if (IsDigit(Read_Char(lexer)))
    {
        while (IsDigit(Read_Char(lexer)) || Read_Char(lexer) == '.')
        {
            len += 1;
            Next_Char(lexer);
        }
        char* s = malloc(len + 1);
        memcpy(s, start, len);
        s[len] = '\0';

        Add_Token_Lexer(lexer, Init_Token(TOKEN_NUMBER, s, Line_Lexer(lexer), Pos_Lexer(lexer)));
        free(s);
    }
    else if (IsAlpha(Read_Char(lexer)))
    {
        while (IsAlpha(Read_Char(lexer)) || IsDigit(Read_Char(lexer)))
        {
            len += 1;
            Next_Char(lexer);
        }
        char* s = malloc(len + 1);
        memcpy(s, start, len);
        s[len] = '\0';

        if (Find_Dictionary(tokenDic, s) != NULL)
        {
            Add_Token_Lexer(lexer, Init_Token((TokenType)Find_Dictionary(tokenDic, s), NULL, Line_Lexer(lexer), Pos_Lexer(lexer)));
        }
        else
        {
            Add_Token_Lexer(lexer, Init_Token(TOKEN_IDENTIFIER, s, Line_Lexer(lexer), Pos_Lexer(lexer)));
        }

        free(s);
    }
    else
    {

    }
}


Token* GetToken(Lexer* lexer)
{
    return lexer->p->elem;
}

Token* EatToken(Lexer* lexer)
{
    Token* ret = lexer->p->elem;
    lexer->p = lexer->p->next;
    return ret;
}

bool NotEof(Lexer* lexer)
{
    return GetToken(lexer)->type != TOKEN_EOF;
}


bool IsAlpha(char c)
{
    return ('a' <= c && 'z' >= c) || ('A' <= c && 'Z' >= c);
}

bool IsDigit(char c)
{
    return '0' <= c && '9' >= c;
}

