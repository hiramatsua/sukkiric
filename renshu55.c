/* 数字当てゲーム */
/* renshu55.c */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int answer;     /* 回答する数字 */
    int ansNum = 0; /* 回答の回数 */
    int number;     /* 答え数字 */
    int flag = 0;   /* 当たり判別 */

    /* 乱数を生成する準備 と 答え数字を乱数生成する*/
    srand((unsigned)time(0UL));
    number = rand() % 10;

    /* 説明分表示 */
    printf("** 数字当てゲーム\n");
    printf("回答のチャンスは４回までです。\n");

    /* 外れたら繰り返し */
    while (ansNum < 4){
      printf("１桁の数字を入力してください。");
    /* 数字を入力１～９ */
      scanf("%d", &answer);
    /* 回答の回数＋１*/
      ansNum++;
    /* 当たり判別 */
      if (answer == number){
        flag = 1;        
      }else{
        if (answer > number){
          printf("残念！ヒント：答えは入力した数字よりも小さいです。\n");
        }else{
          printf("残念！ヒント：答えは入力した数字よりも大きいです。\n");
        }
        flag = 0;
      }
      /* 当たりであれば終了 */
      if (flag == 1){
        break;
      }  
    }
    if (flag == 0){
      printf("答えは、%d でした。\n", number);
    }
    if (flag == 1){
      printf("おめでとうございます！正解です。\n");
    }
    printf("処理を終了します。\n");
    return 0;
}