/* 関数の演習プログラム 引数argあり */
/* func4.c */
#include <stdio.h>

/* 型の定義 */
typedef char String[512];

/* プロトタイプ宣言 */
void hello(String name);

/* main */
int main(void)
{
    printf("関数を呼び出しテストです。\n");
    /* hello関数の呼び出し 引数arg */
    hello("テスト１");
    hello("テスト２");
    hello("テスト３");
    printf("処理が正常に実行されました。\n");
    
    return 0;
}

void hello(String name)
{
    printf("%sさん、こんにちは。\n", name);
}
