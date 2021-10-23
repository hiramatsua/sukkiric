/* 関数の演習プログラム */
/* func3.c */
#include <stdio.h>

/* プロトタイプ宣言 */
void funcA(void);
void funcB(void);

/* main */
int main(void)
{
    printf("関数を呼び出しテストです。\n");
    /* funcA関数の呼び出し */
    funcA();
    printf("処理が正常に実行されました。\n");
    
    return 0;
}

void funcA(void)
{
    printf("関数A funcAを実行します。\n");
    /* 関数B funcB実行 */
    funcB();
} 

void funcB(void)
{
    printf("関数B funcBを実行します。\n");
} 




