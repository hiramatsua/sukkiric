/* パズルRPGプログラム Ver2.0 */
/* puzmon2.c */
#include <stdio.h>

typedef char String[1024];

// 列挙型宣言
typedef enum Element {FIRE, WATER, WIND, EARTH, LIFE, EMPTY} Element;

// グローバル定数の宣言
#define ERR 1;
#define OK 0;
/* <<b>>属性別の記号 */
const char ELEMENT_SYMBOLS[EMPTY+1] = {'$', '~', '@', '#', '&', ' '};
/* <<c>>属性別のカラーコード（ディスプレイ制御シーケンス用）*/
const char ELEMENT_COLORS[EMPTY+1] = {1, 6, 2, 3, 5, 0};

// 構造体型宣言<モンスター>
typedef struct {  
    String name;      /* 名前 */
    int hp;           /* HP */
    int maxhp;        /* 最大HP */
    Element element;  /* 属性 */
    int attack;       /* 攻撃力 */
    int defense;      /* 防御力 */  
} Monster;

/* 味方モンスター */
Monster allies[] = {{"朱雀", 150, 150, FIRE, 25, 10},
                    {"青龍", 150, 150, WIND, 15, 10},
                    {"白虎", 150, 150, EARTH, 20, 5},
                    {"玄武", 150, 150, WATER, 15, 15}
};
/* 敵モンスター */
Monster enemy[] = {{"スライム", 100, 100, WATER, 10, 5},
                   {"ゴブリン", 200, 200, EARTH, 20, 15},
                   {"オオコウモリ", 300, 300, WIND, 30, 25},
                   {"ウェアウルフ", 400, 400, WIND, 40, 30},
                   {"ドラゴン", 800, 800, FIRE, 50, 40}
};

// 構造体型宣言<ダンジョン>
typedef struct {
    Monster* monsters;
    int monsterNum;
} Dungeon;

// 関数宣言
int goDungeon(char* playerName, Dungeon* eDungeon);
int doBattle(char* playerName, Monster* enemyName);
void printMonsterName(Monster* monster);

// main
int main(int argc, char** argv)
{
    char* PLAYER = argv[1];
    
    if (!PLAYER) {
        printf("ERROR : プレイヤー名を指定して起動してください。");
        return ERR;
    }
    printf("*** Puzzle & Monsters game ***\n");
    // ダンジョン初期化
    Dungeon dungeon = {enemy, 5};    
    // goDungeon関数を実行
    int winCnt = goDungeon(PLAYER, &dungeon);
    
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
int goDungeon(char* playerName, Dungeon* eDungeon)
{
    int knockDownMonsterNum = 0;

    printf("%sはダンジョンに到着した。\n", playerName);
    // doBattle関数を実行
    for (int i = 0; i < eDungeon->monsterNum; i++) {
        knockDownMonsterNum += doBattle(playerName, &(eDungeon->monsters[i]));
    }
    return knockDownMonsterNum;
}

// <<3>>バトル開始から終了までの流れ
int doBattle(char* playerName, Monster* enemyName)
{
    int win = 1;  /* 勝ち+1 */

    // printf("%s", enemyName);
    printMonsterName(enemyName);
    printf("が現れた！\n");
    // ダミーの戦い
    printMonsterName(enemyName);
    printf("を倒した！\n");
    return win;
}

void printMonsterName(Monster* eEnemy)
{
    char symbol = ELEMENT_SYMBOLS[eEnemy->element];

    // 文字色をカラーコードnに設定
    // printf("\x1b[3%dm", ELEMENT_COLORS[eEnemy->element]);
    // シンボル＋モンスター名＋シンボルを表示・.
    printf("%c%s%c", symbol, eEnemy->name, symbol);
    
}

