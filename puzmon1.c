/* パズルRPGプログラム Ver2.0 */
/* puzmon2.c */
#include <stdio.h>

typedef char String[1024];

// 列挙型宣言

// グローバル定数の宣言
#define ERR 1;
#define OK 0;
// <<b>>属性別の記号
const char ELEMENT_SYMBOLS[EMPTY+1] = {'$','~','@','#','&', ' '};
// <<c>>属性別のカラーコード（ディスプレイ制御シーケンス用）
const char ELEMENT_COLORS[EMPTY+1] = {1,6,2,3,5,0};

// 構造体型宣言
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

// 関数宣言
int goDungeon(char* playerName);
int doBattle(char* playerName, char* enemyName);

// main
int main(int argc, char** argv)
{
    char* PLAYER = argv[1];
    
    if (!PLAYER) {
        printf("ERROR : プレイヤー名を指定して起動してください。");
        return ERR;
    }
    printf("*** Puzzle & Monsters game ***\n");
    // goDungeon関数を実行
    int winCnt = goDungeon(PLAYER);
    
    // ゲーム終了の処理
    if (winCnt == 5) {
        printf("%sはダンジョンを制覇した！\n", PLAYER);
        printf("*** GAME CLEARED! ***\n");
    }else{
        printf("*** GAME OVER! ***\n");
    }
    
    printf("倒したモンスター数＝%d\n", winCnt);
    return OK;
}

// <<2>>ダンジョンへ
int goDungeon(char* playerName)
{
    int knockDownMonsterNum = 0;

    printf("%sはダンジョンに到着した。\n", playerName);
    // doBattle関数を実行
    for (int i = 0; i < 5; i++) {
        knockDownMonsterNum += doBattle(playerName, enemy[i].name);
    }
    return knockDownMonsterNum;
}

// <<3>>バトル開始から終了までの流れ
int doBattle(char* playerName, char* enemyName)
{
    int win = 1;  /* 勝ち+1 */

    printf("%sが現れた！\n", enemyName);
    // ダミーの戦い
    printf("%sを倒した！\n", enemyName);
    return win;
}

