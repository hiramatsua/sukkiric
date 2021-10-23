/* 数字当てゲーム */
/* renshu74.c */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    const int KETA = 3; /* 桁数 */
    int answer[KETA];   /* 答え数字 */
    int input[KETA];    /* 入力される数字 */
    int retry = 1;      /* コンティニュー? */
    
    /* 乱数を生成する準備 と 答え数字を乱数生成する*/
    srand((unsigned)time(0UL));
    /* 各桁に生成した乱数を答え数字answerに格納する。*/
    for (int i = 0; i < KETA; i++){
      answer[i] = rand() % 10;
    }
    
    /* 説明分表示 */
    printf("** 数字当てゲーム\n");
    printf("%d桁の数字を当ててください。\n", KETA);

    /* メイン処理 */
    while (retry == 1){
      int hit = 0;  /* 一致した数 */
      int blow = 0; /* 含まれる数 */
      /* 〇桁目の予想数字を入力してもらう */
      for (int j = 0; j < KETA; j++){
        printf("%d桁目の予想を0-9の数字で入力してください。", j+1);
      /* 数字を入力１～９ */
        scanf("%1d", &input[j]);
      }
      /* 一致しているか？ */
      for (int i = 0; i < KETA; i++){
        if (answer[i] == input[i]){
          hit++;
        }
        for (int j = 0; j < KETA; j++){
          if(answer[i] == input[j] && i != j){
            blow++;
          }
        }
      }
      printf("%dヒット！%dブロー！", hit, blow);
      if (hit == KETA){
        printf("正解です！");
        break;
      }else{
        printf("続けますか？<1:続ける／0:やめる＞");
        scanf("%d", &retry);
      }
    }
    
    printf("\n正解は");
    for (int i = 0; i < KETA; i++){
      printf("%d", answer[i]);
    }
    printf("でした。\n");
    printf("処理を終了します。\n");
    return 0;
}