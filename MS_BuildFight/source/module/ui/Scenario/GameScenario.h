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
#define DEFAULT_TEXT_SPEED	(10)

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
GameScenarioData scenario_rosa_start[5] = 
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "ああ", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "いい", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "うう", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "ええ", false },
	LAST
};
GameScenarioData scenario_rosa_win[4];
GameScenarioData scenario_rosa_lose[4];
GameScenarioData scenario_rosa_harf[4];
//////////////////////////////////////////////////////////////////////////////////////////////////////
//リーラ（青）
//////////////////////////////////////////////////////////////////////////////////////////////////////
GameScenarioData scenario_lila_start[4] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "面倒だけど相手してあげる", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "つまらない戦いしたら許さないから", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "覚悟してね", false },
	LAST
};
GameScenarioData scenario_lila_win[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "その程度なの？", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "もっと本気出して", false },
	LAST
};
GameScenarioData scenario_lila_lose[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "なかなかやるじゃん", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "負けないから…", false },
	LAST
};
GameScenarioData scenario_lila_harf[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "同じくらい", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "圧倒的な力の差を見せてあげる", false },
	LAST
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//ojyo(黄)
//////////////////////////////////////////////////////////////////////////////////////////////////////
GameScenarioData scenario_ojyo_start[5];
GameScenarioData scenario_ojyo_win[4];
GameScenarioData scenario_ojyo_lose[4];
GameScenarioData scenario_ojyo_harf[4];
//////////////////////////////////////////////////////////////////////////////////////////////////////
//tutorial(チュートリアル子)
//////////////////////////////////////////////////////////////////////////////////////////////////////
GameScenarioData scenario_tutorial_start[5];
GameScenarioData scenario_tutorial_win[4];
GameScenarioData scenario_tutorial_lose[4];
GameScenarioData scenario_tutorial_harf[4];
