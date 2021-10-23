/* 演習82 うるう年判定プログラム */
/* renshu82.c */
#include <stdio.h>
#include <stdbool.h>

/* 関数isLeapYear定義 arg：西暦年 */
bool isLeapYear(int year)
{
    // printf("isLeapYear\n");    
    return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
}

/* main */
int main(void)
{
    int inpYear;

    printf("うるう年判定する西暦年を入力してください：");
    scanf("%d", &inpYear);
    if (isLeapYear(inpYear)) {
        printf("%d年は、うるう年です。\n");
    }else{
        printf("%d年は、うるう年ではありません。\n");
    }
    
    printf("処理が正常に実行されました。\n");
    return 0;
}