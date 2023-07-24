#ifndef LEXER_H
#define LEXER_H

#include "dictionary.h"
#include "linkedList.h"
#include "token.h"
#include <stdbool.h>

typedef struct LEXER {
	int pos;
	int line;
	int len;
	char* data;

	LinkedListNode* p;
	LinkedList* tokens;
}Lexer;

Lexer* Init_Lexer(char* data);

void Destroy_Lexer(Lexer* lexer);

int Line_Lexer(Lexer* lexer);

int Pos_Lexer(Lexer* lexer);


void Skin_White_Space(Lexer* lexer);

char Read_Char(Lexer* lexer);

void Next_Char(Lexer* lexer);

bool Has_Next(Lexer* lexer);


void Do_Lexer(Lexer* lexer);

void Add_Token_Lexer(Lexer* lexer, Token* token);

void Read_Token(Lexer* lexer);


Token* GetToken(Lexer* lexer);

Token* EatToken(Lexer* lexer);

bool NotEof(Lexer* lexer);


bool IsAlpha(char c);

bool IsDigit(char c);

#endif 
