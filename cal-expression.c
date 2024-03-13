#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

double num; // 선언된 int들 double형식으로 변경
enum
{
    NULL_TOKEN,
    NUMBER,
    PLUS,
    STAR,
    LP,
    RP,
    END
} token;

void get_token();
void error(int i);
double expression();
double term();
double factor();

int main()
{
    double result;
    printf("Enter an expression: ");
    get_token();
    result = expression();
    if (token != END)
        error(3);
    else
        printf("Result: %lf\n", result); // 실수 출력 형식으로 변경
    return 0;
}

double expression()
{
    double result = term();
    while (token == PLUS)
    {
        get_token();
        result = result + term();
    }
    return result;
}

double term()
{
    double result = factor();
    while (token == STAR)
    {
        get_token();
        result = result * factor();
    }
    return result;
}

double factor()
{
    double result;
    if (token == NUMBER)
    {
        result = num;
        get_token();
    }
    else if (token == LP)
    {
        get_token();
        result = expression();
        if (token == RP)
            get_token();
        else
            error(2);
    }
    else
    {
        error(1);
    }
    return result;
}

void get_token()
{
    char ch;
    while ((ch = getchar()) == ' ')
        ;
    if (isdigit(ch) || ch == '.') // 소수점도 인식할 수 있게끔 수정
    {
        ungetc(ch, stdin);
        scanf("%lf", &num); // double 형식으로 입력
        token = NUMBER;
    }
    else
    {
        switch (ch)
        {
        case '+':
            token = PLUS;
            break;
        case '*':
            token = STAR;
            break;
        case '(':
            token = LP;
            break;
        case ')':
            token = RP;
            break;
        case '\n':
            token = END;
            break;
        default:
            error(0);
            break;
        }
    }
}

void error(int i)
{
    static const char *errors[] = {
        "Unknown error",
        "Invalid number",
        "Missing right parenthesis",
        "Extra input"};
    printf("Error: %s\n", errors[i]);
    exit(1);
}
