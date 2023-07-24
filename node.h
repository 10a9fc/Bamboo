#ifndef NODE_H
#define NODE_H

#include "lexer.h"
#include "list.h"

typedef enum NODE_TYPE
{
	NODE_NUMBER,
	NODE_IDENTIFIER,
	NODE_STRING,

	NODE_PROGRAM,
	NODE_BINARY_EXPR,
	NODE_UNARY_EXPR,
	NODE_ASSIGN_EXPR,
	NODE_VAR_DECLARATION,

	NODE_IF,
	NODE_WHILE,
	NODE_PRINT

}NodeType;

struct NODE;

typedef struct NODE_IDENTIFIER
{
	char* identifier;
}NodeIdentifier;

typedef struct NODE_NUMBER
{
	double number;
}NodeNumber;

typedef struct NODE_STRING
{
	char* string;
}NodeString;

typedef struct NODE_PROGRAM
{
	List* body;
}NodeProgram;

typedef struct NODE_WHILE
{
	struct NODE* expr;
	struct NODE* program;
}NodeWhile;

typedef struct NODE_IF
{
	struct NODE* expr;
	struct NODE* program;
	struct NODE* elseProgram;
}NodeIf;

typedef enum NODE_BINARY_OPERATOR
{
	NODE_OPERATOR_ADD,
	NODE_OPERATOR_SUBTRACT,
	NODE_OPERATOR_MULTIPLY,
	NODE_OPERATOR_DIVIDE,
	NODE_OPERATOR_EQUAL,
	NODE_OPERATOR_NOT_EQUAL,
	NODE_OPERATOR_LESS,
	NODE_OPERATOR_LESS_EQUAL,
	NODE_OPERATOR_GREATER,
	NODE_OPERATOR_GREATER_EQUAL,
}NodeBinaryOperator;

typedef enum NODE_UNARY_OPERATOR
{
	NODE_OPERATOR_PLUS,
	NODE_OPERATOR_MINUS
}NodeUnaryOperator;

typedef struct NODE_BINARY_EXPR
{
	struct NODE* left;
	struct NODE* right;
	NodeBinaryOperator operator;
}NodeBinaryExpr;

typedef struct NODE_UNARY_EXPR
{
	struct NODE* value;
	NodeUnaryOperator operator;
}NodeUnaryExpr;

typedef struct NODE_ASSIGN_EXPR
{
	struct NODE* name;
	struct NODE* expr;
}NodeAssignExpr;

typedef struct NODE_VAR_DECLAATION
{
	struct NODE* name;
	struct NODE* expr;
}NodeVarDeclaration;

typedef struct NODE_PRINT
{
	struct NODE* expr;
}NodePrint;

typedef union NODE_VALUE
{
	NodeVarDeclaration* varDeclaration;
	NodeBinaryExpr* binaryExpr;
	NodeUnaryExpr* unaryExpr;
	NodeAssignExpr* assignExpr;
	NodeProgram* program;
	NodeWhile* nodeWhile;
	NodeIf* nodeIf;
	NodeIdentifier* identifier;
	NodeString* string;
	NodeNumber* number;
	NodePrint* nodePrint;
}NodeValue;

typedef struct NODE
{
	NodeType type;
	NodeValue value;
}Node;

Node* Init_Node(NodeType type);

void Destroy_Node(void* node);


Node* Init_NodeProgram(int capacity);

Node* Init_NodeNumber(double number);

Node* Init_NodeIdentifier(char* identifier);

Node* Init_NodeString(char* string);

Node* Init_NodeBinaryExpr(Node* left, Node* right, NodeBinaryOperator operator);

Node* Init_NodeUnaryExpr(Node* value, NodeUnaryOperator operator);

Node* Init_NodeAssignExpr(Node* name, Node* expr);

Node* Init_NodeVarDeclaration(Node* name, Node* expr);

Node* Init_NodeWhile(Node* expr, Node* program);

Node* Init_NodeIf(Node* expr, Node* program);

Node* Init_NodePrint(Node* expr);

#endif

