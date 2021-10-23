/* パズルRPGプログラム Ver0.1*/
/* puzmon0.c */
#include <stdio.h>

typedef char String[1024];

// 列挙型宣言
typedef struct {  
    String name;  /* 名前 */
    int hp;       /* HP */
    int attack;   /* 攻撃力 */
    int defense;  /* 防御力 */  
} Monster;

/* 味方モンスター */
Monster allies[] = {{"朱雀", 150, 25, 10},
                    {"青龍", 150, 15, 10},
                    {"白虎", 150, 20, 5},
                    {"玄武", 150, 15, 15}
};
/* 敵モンスター */
Monster enemy[] = {{"スライム", 100, 10, 5},
                   {"ゴブリン", 200, 20, 15},
                   {"オオコウモリ", 300, 30, 25},
                   {"ウェアウルフ", 400, 40, 30},
                   {"ドラゴン", 800, 50, 40}
};

// グローバル定数の宣言
#define ERR 1;
#define OK 0;

// 関数宣言

// main
int main(int argc, char** argv)
{
    char* PLAYER = argv[1];
    int knockDownMonsterNum = 0;

    if (!PLAYER) {
        printf("プレイヤー名を指定して起動してください。");
        return ERR;
    }
    printf("*** Puzzle & Monsters game ***\n");
    printf("%sはダンジョンに到着した。\n", PLAYER);
    for (int i = 0; i < 5; i++) {
        printf("%sが現れた！\n", enemy[i].name);
        printf("%sを倒した！\n", enemy[i].name);
        knockDownMonsterNum++;
    }
    printf("%sはダンジョンを制覇した！\n", PLAYER);
    printf("*** GAME CLEARED! ***\n");
    printf("倒したモンスター数＝%d\n", knockDownMonsterNum);
    return OK;
}