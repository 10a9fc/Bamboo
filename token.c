#include "token.h"

Token* Init_Token(TokenType type, char* data, int line, int pos)
{
    Token* ret = malloc(sizeof(Token));

    ret->line = line;
    ret->pos = pos;

    if (data != NULL)
    {
        int len = strlen(data);

        ret->data = malloc(len + 1);
        memcpy(ret->data, data, len);
        ret->data[len] = '\0';
    }
    else
    {
        ret->data = NULL;
    }

    ret->type = type;

    return ret;
}

void Destroy_Token(void* token)
{
    Token* tk = token;

    if (tk->data != NULL)
    {
        free(tk->data);
    }

    free(tk);
}

char* Data_Token(Token* token)
{
    return token->data;
}

int Line_Token(Token* token)
{
    return token->line;
}

int Pos_Token(Token* token)
{
    return token->pos;
}

TokenType Type_Token(Token* token)
{
    return token->type;
}

