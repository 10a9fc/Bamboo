#include "eval.h"

RuntimeValue* Eval(Node* node, Environment* env)
{
    switch (node->type)
    {
    case NODE_PROGRAM:
        return Eval_Program(node, env);
    case NODE_WHILE:
        return Eval_While(node, env);
    case NODE_IF:
        return Eval_If(node, env);
    case NODE_BINARY_EXPR:
        return Eval_Binary_Expr(node, env);
    case NODE_UNARY_EXPR:
        return Eval_Unary_Expr(node, env);
    case NODE_ASSIGN_EXPR:
        return Eval_Assign_Expr(node, env);
    case NODE_IDENTIFIER:
        return Eval_Identifier(node, env);
    case NODE_NUMBER:
        return Eval_Number(node);
    case NODE_VAR_DECLARATION:
        return Eval_Var_Declaration(node, env);
    case NODE_PRINT:
        return Eval_Print(node, env);
    }
}

RuntimeValue* Eval_Print(Node* node, Environment* env)
{
    RuntimeValue* value = Eval(node->value.nodePrint->expr, env);

    if (value != NULL)
    {
        if (value->type == RUNTIME_NUMBER)
        {
            printf("%lf\n", value->value.number->number);
            Destroy_RuntimeValue(value);
        }
        else if(value->type == RUNTIME_BOOL)
        {
            if (value->value.boolean->boolean)
            {
                printf("true\n");
            }
            else
            {
                printf("false\n");
            }
            Destroy_RuntimeValue(value);
        }
    }
    else
    {
        printf("null\n");
    }

    return NULL;
}

RuntimeValue* Eval_While(Node* node, Environment* env)
{
    Node* expr = node->value.nodeWhile->expr;
    Node* program = node->value.nodeWhile->program;

    RuntimeValue* cond = Eval(expr, env);
    RuntimeValue* ret = NULL;

    while (cond->value.boolean->boolean)
    {
        if (ret != NULL)
        {
            Destroy_RuntimeValue(ret);
        }

        Environment* newEnv = Init_Environment(env);
        ret = Eval(program, newEnv);
        Destroy_Environment(newEnv);

        Destroy_RuntimeValue(cond);
        cond = Eval(expr, env);
    }

    Destroy_RuntimeValue(cond);
    //Destroy_Environment(newEnv);

    return ret;
}

RuntimeValue* Eval_If(Node* node, Environment* env)
{
    Environment* newEnv = Init_Environment(env);

    Node* expr = node->value.nodeIf->expr;
    Node* program = node->value.nodeIf->program;
    Node* elseProgram = node->value.nodeIf->elseProgram;

    RuntimeValue* cond = Eval(expr, env);
    RuntimeValue* ret = NULL;

    if (cond->value.boolean->boolean)
    {
        ret = Eval(program, newEnv);
    }
    else
    {
        if (elseProgram != NULL)
        {
            ret = Eval(elseProgram, newEnv);
        }
    }

    Destroy_RuntimeValue(cond);
    Destroy_Environment(newEnv);

    return ret;
}

RuntimeValue* Eval_Program(Node* node, Environment* env)
{
    RuntimeValue* ret = NULL;
    for (int i = 0; i < node->value.program->body->size; ++i)
    {
        if (ret != NULL)
        {
            Destroy_RuntimeValue(ret);
        }
        ret = Eval(At_List(node->value.program->body, i), env);
    }
    return ret;
}

RuntimeValue* Eval_Binary_Expr(Node* node, Environment* env)
{
    RuntimeValue* left = Eval(node->value.binaryExpr->left, env);
    RuntimeValue* right = Eval(node->value.binaryExpr->right, env);

    double ln = left->value.number->number;
    double rn = right->value.number->number;

    Destroy_RuntimeValue(left);
    Destroy_RuntimeValue(right);

    switch (node->value.binaryExpr->operator)
    {
    case NODE_OPERATOR_EQUAL:
        return Init_RuntimeBool(ln == rn);
    case NODE_OPERATOR_NOT_EQUAL:
        return Init_RuntimeBool(ln != rn);
    case NODE_OPERATOR_LESS:
        return Init_RuntimeBool(ln < rn);
    case NODE_OPERATOR_LESS_EQUAL:
        return Init_RuntimeBool(ln <= rn);
    case NODE_OPERATOR_GREATER:
        return Init_RuntimeBool(ln > rn);
    case NODE_OPERATOR_GREATER_EQUAL:
        return Init_RuntimeBool(ln >= rn);
    case NODE_OPERATOR_ADD:
        return Init_RuntimeNumber(ln + rn);
    case NODE_OPERATOR_SUBTRACT:
        return Init_RuntimeNumber(ln - rn);
    case NODE_OPERATOR_MULTIPLY:
        return Init_RuntimeNumber(ln * rn);
    case NODE_OPERATOR_DIVIDE:
        return Init_RuntimeNumber(ln / rn);
    default:
        printf("error");
        break;
    }
}

RuntimeValue* Eval_Unary_Expr(Node* node, Environment* env)
{

    RuntimeValue* value = Eval(node->value.unaryExpr->value, env);
    double n = value->value.number->number;

    Destroy_RuntimeValue(value);

    switch (node->value.unaryExpr->operator)
    {
    case NODE_OPERATOR_PLUS:
        return Init_RuntimeNumber(n);
    case NODE_OPERATOR_MINUS:
        return Init_RuntimeNumber(0 - n);
    }
}

RuntimeValue* Eval_Assign_Expr(Node* node, Environment* env)
{
    char* name = (node->value.assignExpr->name)->value.identifier->identifier;
    RuntimeValue* value = Eval(node->value.assignExpr->expr, env);
    AssignVar_Environment(env, name, value);
    return Clone_RuntimeValue(value);
}

RuntimeValue* Eval_Identifier(Node* node, Environment* env)
{
    RuntimeValue* value = LookUp_Environment(env, node->value.identifier->identifier);
    return Clone_RuntimeValue(value);
}

RuntimeValue* Eval_Number(Node* node)
{
    return Init_RuntimeNumber(node->value.number->number);
}

RuntimeValue* Eval_Var_Declaration(Node* node, Environment* env)
{
    RuntimeValue* value = Eval(node->value.varDeclaration->expr, env);
    DeclareVar_Environment(env, (node->value.varDeclaration->name)->value.identifier->identifier, value);
    return NULL;
}

