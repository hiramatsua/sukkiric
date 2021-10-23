/* 関数の演習プログラム 複数の引数arg 戻り値return */
/* func51.c */
#include <stdio.h>

/* 関数add定義 ２つの引数を受けて足し算 答え：戻り値*/
int add(int x, int y)
{
    int ans;

    ans = x + y;
    return ans;
}

/* main */
int main(void)
{
    int ans1;
    int ans2;

    printf("２つの引数を渡して足し算します。\n");
    /* add関数の呼び出し 引数arg２つ */
    printf("テスト１\n");
    ans1 = add(1, 2);
    printf("%d + %d = %d\n", 1, 2, ans1);
    printf("テスト２\n");
    ans2 = add(10, 20);
    printf("%d + %d = %d\n", 10, 20, ans2);
    printf("処理が正常に実行されました。\n");
    
    return 0;
}