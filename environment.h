#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "dictionary.h"
#include "runtime.h"

typedef struct ENVIRONMENT
{
	struct ENVIRONMENT* parent;
	Dictionary* values;
}Environment;

Environment* Init_Environment(Environment* parent);

void Destroy_Environment(Environment* env);


void DeclareVar_Environment(Environment* env, char* name, RuntimeValue* value);

void AssignVar_Environment(Environment* env, char* name, RuntimeValue* value);

RuntimeValue* LookUp_Environment(Environment* env, char* name);

Environment* Find_Environment(Environment* env, char* name);

#endif // !ENVIRONMENT_H

