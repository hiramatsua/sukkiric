/* 関数の演習プログラム 複数の引数arg */
/* func5.c */
#include <stdio.h>

/* 関数add定義 ２つの引数を受けて足し算 */
void add(int x, int y)
{
    int ans;

    ans = x + y;
    printf("%d + %d = %d\n", x, y, ans);
}

/* main */
int main(void)
{
    printf("２つの引数を渡して足し算します。\n");
    /* add関数の呼び出し 引数arg２つ */
    printf("テスト１\n");
    add(1, 2);
    printf("テスト２\n");
    add(10, 20);
    printf("テスト３\n");
    add(100, 215);
    printf("処理が正常に実行されました。\n");
    
    return 0;
}