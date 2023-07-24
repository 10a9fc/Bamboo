#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum TOKEN_TYPE
{
	TOKEN_EOF,

	TOKEN_NUMBER,
	TOKEN_STRING,

	TOKEN_IDENTIFIER,

	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_LBRACE,
	TOKEN_RBRACE,

	TOKEN_PLUS,
	TOKEN_PLUS_ASSIGN,
	TOKEN_MINUS,
	TOKEN_MINUS_ASSIGN,
	TOKEN_ASTERISK,
	TOKEN_ASTERISK_ASSIGN,
	TOKEN_SLASH,
	TOKEN_SLASH_ASSIGN,

	TOKEN_ASSIGN,
	TOKEN_ASSIGN_ASSIGN,
	TOKEN_NOT_ASSIGN,

	TOKEN_LESS,
	TOKEN_LESS_ASSIGN,
	TOKEN_GREATER,
	TOKEN_GREATER_ASSIGN,

	TOKEN_AND,
	TOKEN_OR,
	TOKEN_NOT,

	TOKEN_FUNCTION,
	TOKEN_LET,
	TOKEN_FOR,
	TOKEN_WHILE,
	TOKEN_IF,
	TOKEN_ELIF,
	TOKEN_ELSE,

	TOKEN_PRINT,

	TOKEN_SEMICOLON,
}TokenType;

typedef struct TOKEN
{
	TokenType type;
	int line;
	int pos;
	char* data;
}Token;

Token* Init_Token(TokenType type, char* data, int line, int pos);

void Destroy_Token(void* token);

char* Data_Token(Token* token);

int Line_Token(Token* token);

int Pos_Token(Token* token);

TokenType Type_Token(Token* token);

#endif

