/* renshu45.c */
#include <stdio.h>

int main(void)
{
    /* 温度tempature 30℃初期値*/
    int tempature = 30;
    /* 変数ans、返答 */
    int ans = 1;

    while (ans == 1){
    /* 現在の設定温度表示 */
      printf("現在の設定温度は%2d℃です。\n", tempature);
    /* 暑いですか？ */
      printf("暑いですか？ YES=1 NO=0 :");
      scanf("%d", &ans);

      /* YESであれば、温度を-1する */
      if (ans == 1){
        tempature--;
      }else{
        printf("処理を終了します。\n");
        return 0;
      }
    }
    printf("処理を終了します。\n");
    return 0;
}