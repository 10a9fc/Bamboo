#include "parse.h"

void Print_AST(void* node)
{
    Node* v = node;
    switch (v->type)
    {
    case NODE_BINARY_EXPR:
        printf("{ left: ");
        Print_AST(v->value.binaryExpr->left);
        printf(", right: ");
        Print_AST(v->value.binaryExpr->right);
        printf(", operator: %d, type: BinaryExpr }", (int)v->value.binaryExpr->operator);
        break;
    case NODE_UNARY_EXPR:
        printf("{ value: ");
        Print_AST(v->value.unaryExpr->value);
        printf(", operator: %d, type: UnaryExpr }", (int)v->value.unaryExpr->operator);
        break;
    case NODE_PROGRAM:
        printf("{ body: [ ");
        Foreach_List(v->value.program->body, Print_AST);
        printf(" ], type: Program }");
        break;
    case NODE_NUMBER:
        printf("{ value: %lf, type: Number }", (double)v->value.number->number);
        break;
    case NODE_IDENTIFIER:
        printf("{ value: %s, type: Identifier }", v->value.identifier->identifier);
        break;
    case NODE_ASSIGN_EXPR:
        printf("{ name: ");
        Print_AST(v->value.assignExpr->name);
        printf(", expr: ");
        Print_AST(v->value.assignExpr->expr);
        printf(", type: AssignExpr }");
        break;
    case NODE_VAR_DECLARATION:
        printf("{ name: ");
        Print_AST(v->value.varDeclaration->name);
        printf(", expr: ");
        Print_AST(v->value.varDeclaration->expr);
        printf(", type: VarDeclaration }");
        break;
    default:
        printf("error");
        break;
    }
}

Node* Produce_AST(Lexer* lexer)
{
    Node* ret = Init_NodeProgram(10);

    while (NotEof(lexer) && GetToken(lexer)->type != TOKEN_RBRACE)
    {
        Push_List(ret->value.program->body, Parse_Stmt(lexer));
    }

    return ret;
}

Node* Parse_Stmt(Lexer* lexer)
{
    switch (GetToken(lexer)->type)
    {
    case TOKEN_LET:
        return Parse_Var_Declaration(lexer);
    case TOKEN_WHILE:
        return Parse_While(lexer);
    case TOKEN_IF:
        return Parse_If(lexer);
    case TOKEN_PRINT:
        return Parse_Print(lexer);
    default:
        return Parse_Expr(lexer);
    }
}

Node* Parse_Print(Lexer* lexer)
{
    EatToken(lexer);
    EatToken(lexer);

    Node* expr = Parse_Stmt(lexer);

    EatToken(lexer);
    return Init_NodePrint(expr);
}

Node* Parse_While(Lexer* lexer)
{
    EatToken(lexer);
    EatToken(lexer);
    Node* expr = Parse_Expr(lexer);
    EatToken(lexer);

    EatToken(lexer);
    Node* program = Produce_AST(lexer);
    EatToken(lexer);

    return Init_NodeWhile(expr, program);
}

Node* Parse_If(Lexer* lexer)
{
    EatToken(lexer);
    EatToken(lexer);
    Node* expr = Parse_Expr(lexer);
    EatToken(lexer);

    EatToken(lexer);
    Node* program = Produce_AST(lexer);
    EatToken(lexer);

    Node* ret = Init_NodeIf(expr, program);

    if (GetToken(lexer)->type == TOKEN_ELSE)
    {
        EatToken(lexer);
        EatToken(lexer);
        ret->value.nodeIf->elseProgram = Produce_AST(lexer);
        EatToken(lexer);
    }

    return ret;
}

Node* Parse_Var_Declaration(Lexer* lexer)
{
    EatToken(lexer);
    Node* name = Parse_Primary_Expr(lexer);
    EatToken(lexer);
    Node* expr = Parse_Stmt(lexer);

    return Init_NodeVarDeclaration(name, expr);
}


Node* Parse_Expr(Lexer* lexer)
{
    return Parse_Assign_Expr(lexer);
}

Node* Parse_Logical_Expr(Lexer* lexer)
{
    Node* left = Parse_Addition_Expr(lexer);

    while (NotEof(lexer) && (Type_Token(GetToken(lexer)) == TOKEN_ASSIGN_ASSIGN ||
        Type_Token(GetToken(lexer)) == TOKEN_NOT_ASSIGN ||
        Type_Token(GetToken(lexer)) == TOKEN_GREATER ||
        Type_Token(GetToken(lexer)) == TOKEN_GREATER_ASSIGN ||
        Type_Token(GetToken(lexer)) == TOKEN_LESS ||
        Type_Token(GetToken(lexer)) == TOKEN_LESS_ASSIGN))
    {
        NodeUnaryOperator op;
        if (Type_Token(GetToken(lexer)) == TOKEN_ASSIGN_ASSIGN)
        {
            op = NODE_OPERATOR_EQUAL;
        }
        else if (Type_Token(GetToken(lexer)) == TOKEN_NOT_ASSIGN)
        {
            op = NODE_OPERATOR_NOT_EQUAL;
        }
        else if (Type_Token(GetToken(lexer)) == TOKEN_GREATER)
        {
            op = NODE_OPERATOR_GREATER;
        }
        else if (Type_Token(GetToken(lexer)) == TOKEN_GREATER_ASSIGN)
        {
            op = NODE_OPERATOR_GREATER_EQUAL;
        }
        else if (Type_Token(GetToken(lexer)) == TOKEN_LESS)
        {
            op = NODE_OPERATOR_LESS;
        }
        else if (Type_Token(GetToken(lexer)) == TOKEN_LESS_ASSIGN)
        {
            op = NODE_OPERATOR_LESS_EQUAL;
        }

        EatToken(lexer);

        Node* right = Parse_Addition_Expr(lexer);
        left = Init_NodeBinaryExpr(left, right, op);
    }

    return left;
}

Node* Parse_Assign_Expr(Lexer* lexer)
{
    Node* left = Parse_Logical_Expr(lexer);

    while (NotEof(lexer) && Type_Token(GetToken(lexer)) == TOKEN_ASSIGN)
    {
        EatToken(lexer);
        Node* right = Parse_Stmt(lexer);

        left = Init_NodeAssignExpr(left, right);
    }

    return left;
}

Node* Parse_Addition_Expr(Lexer* lexer)
{
    Node* left = Parse_Multiplication_Expr(lexer);

    while (NotEof(lexer) && (Type_Token(GetToken(lexer)) == TOKEN_PLUS || Type_Token(GetToken(lexer)) == TOKEN_MINUS))
    {
        NodeUnaryOperator op;
        if (Type_Token(EatToken(lexer)) == TOKEN_PLUS)
        {
            op = NODE_OPERATOR_ADD;
        }
        else
        {
            op = NODE_OPERATOR_SUBTRACT;
        }

        Node* right = Parse_Multiplication_Expr(lexer);
        left = Init_NodeBinaryExpr(left, right, op);
    }

    return left;
}

Node* Parse_Multiplication_Expr(Lexer* lexer)
{
    Node* left = Parse_Unary_Expr(lexer);

    while (NotEof(lexer) && (Type_Token(GetToken(lexer)) == TOKEN_ASTERISK || Type_Token(GetToken(lexer)) == TOKEN_SLASH))
    {
        NodeBinaryOperator op;
        if (Type_Token(EatToken(lexer)) == TOKEN_ASTERISK)
        {
            op = NODE_OPERATOR_MULTIPLY;
        }
        else
        {
            op = NODE_OPERATOR_DIVIDE;
        }

        Node* right = Parse_Unary_Expr(lexer);
        left = Init_NodeBinaryExpr(left, right, op);
    }

    return left;
}

Node* Parse_Unary_Expr(Lexer* lexer)
{
    if (Type_Token(GetToken(lexer)) == TOKEN_MINUS || Type_Token(GetToken(lexer)) == TOKEN_PLUS)
    {
        NodeUnaryOperator op;
        if (Type_Token(EatToken(lexer)) == TOKEN_MINUS)
        {
            op = NODE_OPERATOR_MINUS;
        }
        else
        {
            op = NODE_OPERATOR_PLUS;
        }

        Node* value = Parse_Primary_Expr(lexer);
        return Init_NodeUnaryExpr(value, op);
    }
    return Parse_Primary_Expr(lexer);
}

Node* Parse_Primary_Expr(Lexer* lexer)
{
    switch (Type_Token(GetToken(lexer)))
    {
    case TOKEN_NUMBER:
        return Init_NodeNumber(atof(Data_Token(EatToken(lexer))));
    case TOKEN_IDENTIFIER:
        return Init_NodeIdentifier(Data_Token(EatToken(lexer)));
    case TOKEN_STRING:
        return Init_NodeString(Data_Token(EatToken(lexer)));
    case TOKEN_LPAREN: {
        EatToken(lexer);
        Node* ret = Parse_Expr(lexer);
        EatToken(lexer);
        return ret;
    }
                     break;
    default:
        printf("nothing");
        break;
    }
}

