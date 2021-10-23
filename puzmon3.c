/* パズルRPGプログラム Ver4.0 */
/* puzmon4.c */
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

// 構造体型宣言<パーティー>
typedef struct {
    char* playerName; /* プレイヤー名 */
    Monster* monsters;/* 味方モンスター */
    int numMonsters;  /* 味方モンスター数 */
    int maxHp;        /* 最大HP */
    int hp;           /* HP */
    int defense;      /* 防御力 */
} Party;

// 関数宣言
int goDungeon(char* playerName, Dungeon* eDungeon, Party* eParty);
int doBattle(char* playerName, Monster* enemyName);
void printMonsterName(Monster* monsters);
Party organizeParty(char* playName, Monster* monsters, int numMonsters);
void showParty(Party* eParty);

// main
int main(int argc, char** argv)
{
    char* PLAYER = argv[1];
    
    if (!PLAYER) {
        printf("ERROR : プレイヤー名を指定して起動してください。");
        return ERR;
    }
    printf("*** Puzzle & Monsters game ***\n");
    // パーティ準備
    Party party = organizeParty(PLAYER, allies, 4);
    // ダンジョン初期化
    Dungeon dungeon = {enemy, 5};    
    // goDungeon関数を実行
    int winCnt = goDungeon(PLAYER, &dungeon, &party);
    
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
int goDungeon(char* playerName, Dungeon* eDungeon, Party* eParty)
{
    int knockDownMonsterNum = 0;

    // プレイヤーHP/最大HPの算出とメッセージ表示
    printf("%sのパーティ（HP=%d）はダンジョンに到着した。\n", playerName, eParty->hp);
    showParty(eParty);
    // doBattle関数を実行
    for (int i = 0; i < eDungeon->monsterNum; i++) {
        knockDownMonsterNum += doBattle(playerName, &(eDungeon->monsters[i]));
        // hp残のチェック 0以下でbreak
        if(eParty->hp <= 0) {
            printf("%sはダンジョンから逃げ出した…\n", playerName);
            break;
        } else {
            printf("%sはさらに奥へと進んだ。\n", playerName);
            printf("==========\n\n");
        }
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

// (A)モンスター名のカラー表示
void printMonsterName(Monster* eMonsters)
{
    char symbol = ELEMENT_SYMBOLS[eMonsters->element];

    // 文字色をカラーコードnに設定
    // printf("\x1b[3%dm", ELEMENT_COLORS[eEnemy->element]);
    // シンボル＋モンスター名＋シンボルを表示・.
    printf("%c%s%c", symbol, eMonsters->name, symbol);
    
}

// (4)パーティ編成処理
Party organizeParty(char* playerName, Monster* monsters, int numMonsters)
{
  int sumHp = 0;
  int sumDefense = 0;
  int avgDefense = 0;

  for(int i = 0; i < numMonsters; i++) {
    sumHp += monsters[i].hp;
    sumDefense += monsters[i].defense;
    // printf("%s\n", monsters[i].name);
  }
  avgDefense = sumDefense / numMonsters;

  Party partyInfo = {playerName, monsters, numMonsters, sumHp, sumHp, avgDefense};
  
  return partyInfo;
}

// (5)パーティ編成情報の一覧表示
void showParty(Party* eParty)
{
    printf("＜パーティ編成＞----------\n");
    for(int i = 0; i < eParty->numMonsters; i++) {
        // シンボル＋モンスター名＋シンボルを表示 
        printMonsterName(&(eParty->monsters[i]));
        printf("  HP=%4d 攻撃=%3d 防御=%3d\n",
        eParty->monsters[i].hp,
        eParty->monsters[i].attack,
        eParty->monsters[i].defense
        );
    }
    printf("------------------------\n\n");    
}