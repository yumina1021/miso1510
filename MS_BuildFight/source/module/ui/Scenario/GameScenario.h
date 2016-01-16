//=============================================================================
//
// MS_BuildFight [GameScenario.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#include "../Character.h"

#define DEFAULT_TEXT_X	(210)
#define DEFAULT_TEXT_Y	(590)
#define DEFAULT_TEXT_SPEED	(5)

#define LAST	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, 0, FACIAL_NONE, "・・・", true }

typedef struct
{
	float x;
	float y;
	float speed;
	FasialType type;
	char* font;
	bool lastflag;
}GameScenarioData;

//////////////////////////////////////////////////////////////////////////////////////////////////////
//rosa（ピンク）
//////////////////////////////////////////////////////////////////////////////////////////////////////
GameScenarioData scenario_rosa_start[4] = 
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "あなたが私の相手？", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_NORMAL, "私に勝てるかしら？", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "勝てたらご褒美あげるわっ♪", true },
	LAST
};
GameScenarioData scenario_rosa_win[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_NORMAL, "なかなかやるじゃない", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "ご褒美につられてるのかな？", true },
	LAST
};
GameScenarioData scenario_rosa_lose[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "つまらないわねぇ", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "あんたマグロ？", true },
	LAST
};
GameScenarioData scenario_rosa_harf[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "同じくらいか", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_NORMAL, "まぁまだ本気出してないし…", true },
	LAST
};
GameScenarioData scenario_rosa_cupin[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "入った～", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "気持ちいいプレイだったわ！", true },
	LAST
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//リーラ（青）
//////////////////////////////////////////////////////////////////////////////////////////////////////
GameScenarioData scenario_lila_start[4] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "面倒だけど相手してあげる", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "つまらない戦いしたら許さないから", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "覚悟してね", true },
	LAST
};
GameScenarioData scenario_lila_win[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "その程度なの？", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "もっと本気出して", true },
	LAST
};
GameScenarioData scenario_lila_lose[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "なかなかやるじゃん", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "負けないから…", true },
	LAST
};
GameScenarioData scenario_lila_harf[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "同じくらい", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "圧倒的な力の差を見せてあげる", true },
	LAST
};
GameScenarioData scenario_lila_cupin[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "ナイスプレー", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_NORMAL, "次も期待するよ…", true },
	LAST
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//ojyo(黄)
//////////////////////////////////////////////////////////////////////////////////////////////////////
GameScenarioData scenario_ojyo_start[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "わたくしの相手はあなた？", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_NORMAL, "平民の分際でわたくしと戦えるのです。光栄に思いなさい！", true },
	LAST
};
GameScenarioData scenario_ojyo_win[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "ふーん。この程度？(平民の分際でやるじゃない…)", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_NORMAL, "手加減してあげただけだから。これからよ！", true },
	LAST
};
GameScenarioData scenario_ojyo_lose[3]=
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "こんなものなのかしら？わたくしの圧勝ね", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_NORMAL, "さぁもっと差を開いて差し上げますわ！", true },
	LAST
};
GameScenarioData scenario_ojyo_harf[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "天に仰ぎ見るべきこの我を同じ大地に立たせるか！", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_NORMAL, "その不敬、万死に値する！！", true },
	LAST
};
GameScenarioData scenario_ojyo_cupin[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "ナイスインですわ！", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_NORMAL, "褒美を与えますわ！", true },
	LAST
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//tutorial(チュートリアル子)
//////////////////////////////////////////////////////////////////////////////////////////////////////
GameScenarioData scenario_tutorial_start[4] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "さぁゲームスタートです！", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "勝利の女神はどちらに微笑むか！？", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "注目の一戦です！！", true },
	LAST
};
GameScenarioData scenario_tutorial_win[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "現在相手が先行しております！", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "あなたも頑張ってください！", true },
	LAST
};
GameScenarioData scenario_tutorial_lose[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "相手を突き放す快進撃！", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "すごい！すごいですよー", true },
	LAST
};
GameScenarioData scenario_tutorial_harf[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "現在同じくらいの距離です。", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "まだまだ勝敗はわかりません！", true },
	LAST
};
GameScenarioData scenario_tutorial_cupin[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "お見事！", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_NORMAL, "ナイスゲームですよ！", true },
	LAST
};
