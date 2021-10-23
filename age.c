/* 暗証番号（４桁）を乱数で算出するプログラム */
/* renshu33.c */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
int main(void)
{
    /* 暗証番号PIN */
    int pin1, pin2, pin3, pin4;
 
    /* 生まれた年を入力 */
    printf("あなたの生まれた年を入力してください：");
    scanf("%4d", &input_year);
    /* 年月日と時分秒をtm構造体の各パラメタから変数に代入 */
    year = local->tm_year + 1900;        /* 1900年からの年数が取得されるため */
     
    /* 年齢を算出 */
    calc_age = year - input_year;
    /* 算出した年齢を表示 */
    printf("あなたは、%4d年生まれです。", input_year);
    printf("あなたの年齢は、%d歳です。\n", calc_age);
     
    return 0;
}