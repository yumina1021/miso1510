//=============================================================================
//
// MS_BuildFight [ResultScenario.h]
// 15/12/20
// Author : inaina
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
}ResultScenarioData;

//////////////////////////////////////////////////////////////////////////////////////////////////////
//rosa（ピンク）
//////////////////////////////////////////////////////////////////////////////////////////////////////
ResultScenarioData result_rosa[4] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "うふっ、その程度なんですね", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_NORMAL, "私に勝てるかしら？", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "勝てたらご褒美あげるわっ♪", false },
	LAST
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
//リーラ（青）
//////////////////////////////////////////////////////////////////////////////////////////////////////
ResultScenarioData result_lila[4] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "面倒だけど相手してあげる", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "つまらない戦いしたら許さないから", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "覚悟してね", false },
	LAST
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
//ojyo(黄)
//////////////////////////////////////////////////////////////////////////////////////////////////////
ResultScenarioData result_ojyo[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "わたくしの相手はあなた？", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_NORMAL, "平民の分際でわたくしと戦えるのです。光栄に思いなさい！", false },
	LAST
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
//tutorial(チュートリアル子)
//////////////////////////////////////////////////////////////////////////////////////////////////////
ResultScenarioData result_tutorial[4] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "うぐっ。こ、腰が・・・。", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "勝利の女神はどちらに微笑むか！？", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "注目の一戦です！！", false },
	LAST
};

