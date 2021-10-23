/* 暗証番号（４桁）を乱数で生成するプログラム */
/* renshu33.c */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
int main(void)
{
    /* 暗証番号PIN */
    int pin1, pin2, pin3, pin4;
 
    /* 4桁の暗証番号を乱数で生成する */
    printf("4桁の暗証番号を乱数で生成します。\n");
    /* 乱数を生成する準備 */
    srand((unsigned)time(0UL));
    /* 暗証番号１桁め */
    pin1 = rand() % 10;
    /* 暗証番号２桁め */
    pin2 = rand() % 10;
    /* 暗証番号３桁め */
    pin3 = rand() % 10;
    /* 暗証番号４桁め */
    pin4 = rand() % 10;
    /* 生成した暗証番号を表示 */
    printf("生成した暗証番号→%d%d%d%d", pin4, pin3, pin2, pin1);
    
    return 0;
}