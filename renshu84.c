/* 演習84 割り勘を計算するプログラム */
/* renshu84.c */
#include <stdio.h>
#include <stdlib.h>

typedef char String[1024];

/* 入力された値をint型変換して戻す */
int iscanf(void)
{
    String inputStr;

    scanf("%s", inputStr);    
    return atoi(inputStr);
}

int calcPayment(int amount, int people)
{
    double dnum;
    int pay;

    dnum = (double)amount / people;
    pay = (int)(dnum / 100) * 100;
    if (dnum > pay) {
        pay = pay + 100;
    }
    return pay;
}

void showPayment(int pay, int payorg, int people)
{
    printf("*** 支払額 ***\n");
    printf("一人当たり%d円（%d人）、幹事は%d円です\n", pay, people - 1, payorg); 
}

/* main */
int main(void)
{
    int amount; //支払い総額
    int people; //参加人数 
    int pay;    //一名あたりの支払額
    int payorg; //幹事の支払額

    //計算データの入力
    printf("支払い総額を入力してください：");
    amount = iscanf();
    // printf("%d\n", amount);
    printf("参加人数を入力してください：");
    people = iscanf();
    // printf("%d\n", people);

    // 割り勘の計算
    pay = calcPayment(amount, people);
    printf("%d\n", pay);
    // 幹事の支払い額、結果を計算
    payorg = amount - pay * (people -1);
    showPayment(pay, payorg, people);

    printf("処理が正常に実行されました。\n");
    return 0;
}