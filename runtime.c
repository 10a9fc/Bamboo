#include "runtime.h"

RuntimeValue* Init_RuntimeValue(RuntimeType type)
{
    RuntimeValue* ret = malloc(sizeof(RuntimeValue));
    ret->type = type;

    return ret;
}

void Destroy_RuntimeValue(void* value)
{
    RuntimeValue* v = value;

    switch (v->type)
    {
    case RUNTIME_NULL:
        break;
    case RUNTIME_NUMBER:
        free(v->value.number);
        break;
    case RUNTIME_STRING:
        //free(value->value.string->string);
        //free(value->value.string);
        break;
    case RUNTIME_BOOL:
        //free(value->value.boolean->boolean);
        free(v->value.boolean);
        break;
    }
    free(v);
}

RuntimeValue* Clone_RuntimeValue(RuntimeValue* value)
{
    switch (value->type)
    {
    case RUNTIME_NUMBER:
        return Init_RuntimeNumber(value->value.number->number);
    case RUNTIME_BOOL:
        return Init_RuntimeBool(value->value.boolean->boolean);
    }
}


RuntimeValue* Init_RuntimeNumber(double number)
{
    RuntimeValue* ret = Init_RuntimeValue(RUNTIME_NUMBER);

    ret->value.number = malloc(sizeof(RuntimeNumber));
    ret->value.number->number = number;

    return ret;
}

RuntimeValue* Init_RuntimeBool(bool boolean)
{
    RuntimeValue* ret = Init_RuntimeValue(RUNTIME_BOOL);

    ret->value.boolean = malloc(sizeof(RuntimeBool));
    ret->value.boolean->boolean = boolean;

    return ret;
}

RuntimeValue* Init_RuntimeNull()
{
    return Init_RuntimeValue(RUNTIME_NULL);
}

