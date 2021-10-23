/* renshu53.c */
#include <stdio.h>

int main(void)
{
    int num;
    /* 数字を入力１～９ */
    printf("数字を入力してください（１－９）:");
    scanf("%d", &num);

    switch (num){
      case 1:
      case 2:
        printf("バッテリー\n");
        break;
      case 3:
      case 4:
      case 5:
      case 6:
        printf("内野手\n");
        break;
      case 7:
      case 8:
      case 9:
        printf("外野手\n");
        break;  
      default:
        printf("該当なし\n");
        break;  
    }
    printf("処理を終了します。\n");
    return 0;
}