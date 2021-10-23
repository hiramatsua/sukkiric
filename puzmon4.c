/* パズルRPGプログラム Ver4.0 */
/* puzmon4.c */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include <stdbool.h>

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
// <<d>>宝石数
enum {MAX_GEMS = 14};

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

// 構造体型宣言＜バトルフィールド＞
typedef struct BATTLE_FIELD {
    Party* eParty;      /* パーティー */
    Monster* eEnemy;    /* 敵モンスター */
    Element gems[MAX_GEMS]; /* 宝石 */
} BattleField;

// 関数宣言
int goDungeon(char* playerName, Dungeon* eDungeon, Party* eParty);
int doBattle(char* playerName, Monster* eMonster, Party* eParty);
Party organizeParty(char* playName, Monster* monsters, int numMonsters);
void showParty(Party* eParty);
void showBattleField(BattleField *pField);

void doAttack(BattleField* eField);
void onPlayerTurn(char* playerName, BattleField* eField);
void onEnemyTurn(char* playerName, BattleField* eField);
void doEnemyAttack(char* playerName, BattleField* eField);

void printMonsterName(Monster* monsters);
void fillGems(Element* gems);
void printGems(Element* gems);
void printGem(Element element);

// main
int main(int argc, char** argv)
{
    char* PLAYER = argv[1];
    
    if (!PLAYER) {
        printf("ERROR : プレイヤー名を指定して起動してください。");
        return ERR;
    }
    // ゲーム開始 初期画面
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
        knockDownMonsterNum += doBattle(playerName, &(eDungeon->monsters[i]), eParty);
        // hp残のチェック 0以下でbreak
        if(eParty->hp <= 0) {
            printf("%sはダンジョンから逃げ出した…\n", playerName);
            break;
        } else {
            printf("%sはさらに奥へと進んだ。\n", playerName);
            printf("==========\n\n");
            printf("何かキーを押してください。\n");
            getchar();
        }
    }
    return knockDownMonsterNum;
}

// <<3>>バトル開始から終了までの流れ
int doBattle(char* playerName, Monster* eMonster, Party* eParty)
{
    int winFlg = 1;     /* 勝ちフラグ */
    int loseFlg = 0;    /* 負けフラグ */    

    // printf("%s", enemyName);
    printMonsterName(eMonster);
    printf("が現れた！\n");

    // バトルフィールドの宝石スロットの準備と初期化
    BattleField field = {eParty, eMonster};   /* 変数field（型：BattleField）*/
    fillGems(field.gems);   /* Element* gems */

    // 交互ターン繰り返し
    while (1) {
        // パーティー側のターン
        onPlayerTurn(playerName, &field);
        if (eMonster->hp <= 0) {    // モンスタHP0以下
            printMonsterName(eMonster);
            printf("を倒した！\n");
            return winFlg;
            //break;
        }
        // モンスター側のターン
        onEnemyTurn(playerName, &field);
        if (eParty->hp <= 0) {    // パーティHP0以下
            printf("%sは倒れた。。。\n", playerName);
            return loseFlg;
            //break;
        }
    }
}

// <<6>>プレイヤーターン開始から終了までの流れ
void onPlayerTurn(char* playerName, BattleField* eField)
{
    printf("【%sのターン】\n", playerName);
    showBattleField(eField);
    doAttack(eField);
}

// <<7>>パーティの攻撃の開始から終了までの流れ
void doAttack(BattleField* eField)
{
    int pDamage = 80;

    printf("ダミーの攻撃で%dのダメージを与えた。\n", pDamage);
    eField->eEnemy->hp -= pDamage;
    // printf("モンスターのHP=%d", (eEnemy->hp) - pDamage);
}

// <<8>>敵モンスターターン開始から終了までの流れ
void onEnemyTurn(char* playerName, BattleField* eField)
{
    printf("【%s】のターン\n", eField->eEnemy->name);
    doEnemyAttack(playerName, eField);
}

// <<9>>モンスターの攻撃の開始から終了までの流れ
void doEnemyAttack(char* playerName, BattleField* eField)
{
    int mDamage = 20;

    eField->eParty->hp -= mDamage;
    printf("%sは、%dのダメージを受けた。\n", playerName, mDamage);
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
    // 変数partyInfo に代入
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

// バトルフィールドの宝石スロットにランダムに宝石を発生させる
void fillGems(Element* gems) {
    
    for(int i = 0; i < MAX_GEMS; i++) {
        gems[i] = rand() % EMPTY;
        // printf("%d", gems[i]);
    }
    // printf("\n");
}

// バトルフィールドの宝石スロット14個分を画面表示させる
void printGems(Element* gems) {

    for(int i = 0; i < MAX_GEMS; i++) {
        printf(" ");
        printGem(gems[i]);
    }
    printf("\n");
}

// 宝石1個分を画面表示させる
void printGem(Element element) {

    // printf("\x1b[30m");       // 黒文字
    // printf("\x1b[4%dm", ELEMENT_COLORS[element]); // 属性色背景
    printf("%c", ELEMENT_SYMBOLS[element]);
    // printf("\x1b[0m");        // 色指定解除
}

//バトルフィールド情報の表示をする
void showBattleField(BattleField *eField) {
    
    printf("------------------------------\n\n");
    printf("          ");
    // 敵モンスターHPの表示
    printMonsterName(eField->eEnemy);
    printf("\n       HP= %4d / %4d\n", eField->eEnemy->hp, eField->eEnemy->maxhp);
    printf("\n\n");
    // パーティHPの表示
    for(int i = 0; i < eField->eParty->numMonsters; i++) {
        printMonsterName(&(eField->eParty->monsters[i]));
        printf("  ");
    }
    printf("\n");
    printf("       HP= %4d / %4d\n", eField->eParty->hp, eField->eParty->maxHp);
    printf("------------------------------\n");
    printf(" ");
    // 宝石スロットの表示
    for(int i = 0; i < MAX_GEMS; i++ ){
        printf("%c ", 'A'+i);
    }
    printf("\n");
    printGems(eField->gems);
    printf("------------------------------\n");
}
