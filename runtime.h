#ifndef RUNTIME_H
#define RUNTIME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum RUNTIME_TYPE
{
	RUNTIME_NUMBER,
	RUNTIME_STRING,
	RUNTIME_BOOL,
	RUNTIME_NULL
}RuntimeType;

typedef struct RUNTIME_NUMBER
{
	double number;
}RuntimeNumber;

typedef struct RUNTIME_BOOL
{
	bool boolean;
}RuntimeBool;

typedef union RUNTIME_UNION
{
	RuntimeNumber* number;
	RuntimeBool* boolean;
}RuntimeUnion;

typedef struct RUNTIME_VALUE
{
	RuntimeType type;
	RuntimeUnion value;
}RuntimeValue;

RuntimeValue* Init_RuntimeValue(RuntimeType type);

void Destroy_RuntimeValue(void* value);

RuntimeValue* Clone_RuntimeValue(RuntimeValue* value);


RuntimeValue* Init_RuntimeNumber(double number);

RuntimeValue* Init_RuntimeBool(bool boolean);

RuntimeValue* Init_RuntimeNull();

#endif

