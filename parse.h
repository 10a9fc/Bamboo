#ifndef PARSE_H
#define PARSE_H

#include "node.h"

void Print_AST(void* node);

Node* Produce_AST(Lexer* lexer);

Node* Parse_Stmt(Lexer* lexer);

Node* Parse_Print(Lexer* lexer);

Node* Parse_While(Lexer* lexer);

Node* Parse_If(Lexer* lexer);

Node* Parse_Var_Declaration(Lexer* lexer);

Node* Parse_Logical_Expr(Lexer* lexer);

Node* Parse_Expr(Lexer* lexer);

Node* Parse_Assign_Expr(Lexer* lexer);

Node* Parse_Addition_Expr(Lexer* lexer);

Node* Parse_Multiplication_Expr(Lexer* lexer);

Node* Parse_Unary_Expr(Lexer* lexer);

Node* Parse_Primary_Expr(Lexer* lexer);

#endif

