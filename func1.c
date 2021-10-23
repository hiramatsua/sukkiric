/* 関数の演習プログラム */
/* func1.c */
#include <stdio.h>

void hello(void)
{
    printf("hello こんにちは\n");
} 

int main(void)
{
    printf("関数を呼び出します\n");
    /* hello関数の呼び出し */
    hello();
    printf("関数の呼び出しが正常に実行されました。\n");
    
    return 0;
}