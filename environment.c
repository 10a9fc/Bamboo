#include "environment.h"

Environment* Init_Environment(Environment* parent)
{
    Environment* ret = malloc(sizeof(Environment));

    ret->parent = parent;
    ret->values = Init_Dictionary();

    return ret;
}

void Destroy_Environment(Environment* env)
{
    Foreach_Dictionary(env->values, Destroy_RuntimeValue);
    Destroy_Dictionary(env->values);

    free(env);
}


void DeclareVar_Environment(Environment* env, char* name, RuntimeValue* value)
{
    if (Find_Dictionary(env->values, name) != NULL)
    {
        //...
        return;
    }

    Push_Dictionary(env->values, name, value);
}

void AssignVar_Environment(Environment* env, char* name, RuntimeValue* value)
{
    Environment* e = Find_Environment(env, name);
    if (e == NULL)
    {
        //...
        return;
    }

    Destroy_RuntimeValue(Find_Dictionary(e->values, name));
    Set_Dictionary(e->values, name, value);
}

RuntimeValue* LookUp_Environment(Environment* env, char* name)
{
    Environment* e = Find_Environment(env, name);

    if (e == NULL)
    {
        return NULL;
    }

    return Find_Dictionary(e->values, name);
}

Environment* Find_Environment(Environment* env, char* name)
{
    if (Find_Dictionary(env->values, name) != NULL)
    {
        return env;
    }
    else
    {
        if (env->parent != NULL)
        {
            return Find_Environment(env->parent, name);
        }
        else
        {
            return NULL;
        }
    }
}

