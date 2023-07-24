#ifndef EVAL_H
#define EVAL_H

#include "runtime.h"
#include "node.h"
#include "environment.h"

RuntimeValue* Eval(Node* node, Environment* env);

RuntimeValue* Eval_Print(Node* node, Environment* env);

RuntimeValue* Eval_While(Node* node, Environment* env);

RuntimeValue* Eval_If(Node* node, Environment* env);

RuntimeValue* Eval_Program(Node* node, Environment* env);

RuntimeValue* Eval_Binary_Expr(Node* node, Environment* env);

RuntimeValue* Eval_Unary_Expr(Node* node, Environment* env);

RuntimeValue* Eval_Assign_Expr(Node* node, Environment* env);

RuntimeValue* Eval_Identifier(Node* node, Environment* env);

RuntimeValue* Eval_Number(Node* node);

RuntimeValue* Eval_Var_Declaration(Node* node, Environment* env);

#endif

