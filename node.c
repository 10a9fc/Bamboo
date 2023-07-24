#include "node.h"


#pragma warning(disable:4996)

Node* Init_Node(NodeType type)
{
    Node* ret = malloc(sizeof(Node));

    ret->type = type;

    return ret;
}

void Destroy_Node(void* node)
{
    if (node == NULL)
    {
        return;
    }

    Node* v = node;

    switch (v->type)
    {
    case NODE_PROGRAM:
        Foreach_List(v->value.program->body, Destroy_Node);
        Destroy_List(v->value.program->body);
        free(v->value.program);
        break;
    case NODE_WHILE:
        Destroy_Node(v->value.nodeWhile->expr, Destroy_Node);
        Destroy_Node(v->value.nodeWhile->program);
        free(v->value.nodeWhile);
        break;
    case NODE_IF:
        Destroy_Node(v->value.nodeIf->expr, Destroy_Node);
        Destroy_Node(v->value.nodeIf->program);
        Destroy_Node(v->value.nodeIf->elseProgram);
        free(v->value.nodeIf);
        break;
    case NODE_BINARY_EXPR:
        Destroy_Node(v->value.binaryExpr->left);
        Destroy_Node(v->value.binaryExpr->right);
        free(v->value.binaryExpr);
        break;
    case NODE_UNARY_EXPR:
        Destroy_Node(v->value.unaryExpr->value);
        free(v->value.unaryExpr);
        break;
    case NODE_NUMBER:
        free(v->value.number);
        break;
    case NODE_IDENTIFIER:
        free(v->value.identifier->identifier);
        free(v->value.identifier);
        break;
    case NODE_STRING:
        free(v->value.string->string);
        free(v->value.string);
        break;
    case NODE_ASSIGN_EXPR:
        Destroy_Node(v->value.assignExpr->name);
        Destroy_Node(v->value.assignExpr->expr);
        free(v->value.assignExpr);
        break;
    case NODE_VAR_DECLARATION:
        Destroy_Node(v->value.varDeclaration->name);
        Destroy_Node(v->value.varDeclaration->expr);
        free(v->value.varDeclaration);
        break;
    case NODE_PRINT:
        Destroy_Node(v->value.nodePrint->expr);
        free(v->value.nodePrint);
        break;
    default:
        printf("error");
        break;
    }

    free(v);
}

Node* Init_NodeProgram(int capacity)
{
    Node* ret = Init_Node(NODE_PROGRAM);

    ret->value.program = malloc(sizeof(NodeProgram));
    ret->value.program->body = Init_List(capacity);

    return ret;
}

Node* Init_NodeNumber(double number)
{
    Node* ret = Init_Node(NODE_NUMBER);

    ret->value.number = malloc(sizeof(NodeNumber));
    ret->value.number->number = number;

    return ret;
}

Node* Init_NodeIdentifier(char* identifier)
{
    Node* ret = Init_Node(NODE_IDENTIFIER);

    ret->value.identifier = malloc(sizeof(NodeIdentifier));
    ret->value.identifier->identifier = malloc(strlen(identifier) + 1);
    strcpy(ret->value.identifier->identifier, identifier);

    return ret;
}

Node* Init_NodeString(char* string)
{
    Node* ret = Init_Node(NODE_STRING);

    ret->value.string = malloc(sizeof(NodeString));
    ret->value.string->string = malloc(strlen(string) + 1);
    strcpy(ret->value.string->string, string);

    return ret;
}

Node* Init_NodeBinaryExpr(Node* left, Node* right, NodeBinaryOperator operator)
{
    Node* ret = Init_Node(NODE_BINARY_EXPR);

    ret->value.binaryExpr = malloc(sizeof(NodeBinaryExpr));
    ret->value.binaryExpr->left = left;
    ret->value.binaryExpr->right = right;
    ret->value.binaryExpr->operator = operator;

    return ret;
}

Node* Init_NodeUnaryExpr(Node* value, NodeUnaryOperator operator)
{
    Node* ret = Init_Node(NODE_UNARY_EXPR);

    ret->value.unaryExpr = malloc(sizeof(NodeUnaryExpr));
    ret->value.unaryExpr->value = value;
    ret->value.unaryExpr->operator = operator;

    return ret;
}

Node* Init_NodeAssignExpr(Node* name, Node* expr)
{
    Node* ret = Init_Node(NODE_ASSIGN_EXPR);

    ret->value.assignExpr = malloc(sizeof(NodeAssignExpr));
    ret->value.assignExpr->name = name;
    ret->value.assignExpr->expr = expr;

    return ret;
}

Node* Init_NodeVarDeclaration(Node* name, Node* expr)
{
    Node* ret = Init_Node(NODE_VAR_DECLARATION);

    ret->value.varDeclaration = malloc(sizeof(NodeVarDeclaration));
    ret->value.varDeclaration->name = name;
    ret->value.varDeclaration->expr = expr;

    return ret;
}

Node* Init_NodeWhile(Node* expr, Node* program)
{
    Node* ret = Init_Node(NODE_WHILE);

    ret->value.nodeWhile = malloc(sizeof(NodeWhile));
    ret->value.nodeWhile->expr = expr;
    ret->value.nodeWhile->program = program;

    return ret;
}

Node* Init_NodeIf(Node* expr, Node* program)
{
    Node* ret = Init_Node(NODE_IF);

    ret->value.nodeIf = malloc(sizeof(NodeIf));
    ret->value.nodeIf->expr = expr;
    ret->value.nodeIf->program = program;
    ret->value.nodeIf->elseProgram = NULL;

    return ret;
}

Node* Init_NodePrint(Node* expr)
{
    Node* ret = Init_Node(NODE_PRINT);

    ret->value.nodePrint = malloc(sizeof(NodePrint));
    ret->value.nodePrint->expr = expr;

    return ret;
}
