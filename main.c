
#include"parse.h"
#include"eval.h"


extern Dictionary* tokenDic;

void Init()
{
    tokenDic = Init_Dictionary();
    Push_Dictionary(tokenDic, "let", (void*)TOKEN_LET);
    Push_Dictionary(tokenDic, "for", (void*)TOKEN_FOR);
    Push_Dictionary(tokenDic, "while", (void*)TOKEN_WHILE);
    Push_Dictionary(tokenDic, "if", (void*)TOKEN_IF);
    Push_Dictionary(tokenDic, "elif", (void*)TOKEN_ELIF);
    Push_Dictionary(tokenDic, "else", (void*)TOKEN_ELSE);
    Push_Dictionary(tokenDic, "fn", (void*)TOKEN_FUNCTION);
    Push_Dictionary(tokenDic, "and", (void*)TOKEN_AND);
    Push_Dictionary(tokenDic, "or", (void*)TOKEN_OR);
    Push_Dictionary(tokenDic, "print", (void*)TOKEN_PRINT);
}

void test(void* v)
{
    Token* t = v;
    printf("Token: %s %d\n", t->data, (int)t->type);
}

int main(int argc, char** argv)
{
    Init();
    Environment* env = Init_Environment(NULL);
    DeclareVar_Environment(env, "Pi", Init_RuntimeNumber(3.141592653589));
    DeclareVar_Environment(env, "true", Init_RuntimeBool(true));
    DeclareVar_Environment(env, "false", Init_RuntimeBool(false));

    env = Init_Environment(env);

    if (argc == 1)
    {
        printf("Welcome to Bamboo v0.1\n");
        char data[128];
        while (1)
        {
            printf("> ");
            gets(data);

            if (strcmp(data, "quit") == 0)
            {
                return 0;
            }
            else if (strcmp(data, "help") == 0)
            {
                printf("No chance!\n");
                continue;
            }

            Lexer* l = Init_Lexer(data);
            Do_Lexer(l);
            Node* node = Produce_AST(l);
            //Print_AST(node);
            //printf("\n");
            RuntimeValue* value = Eval(node, env);

            if (value != NULL)
            {
                if (value->type == RUNTIME_NUMBER)
                {
                    printf("%lf\n", value->value.number->number);
                    Destroy_RuntimeValue(value);
                }
                else
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

            Destroy_Node(node);
            Destroy_Lexer(l);
        }
    }
}
