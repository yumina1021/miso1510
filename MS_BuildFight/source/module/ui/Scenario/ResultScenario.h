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
ResultScenarioData result_rosa_win[2] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "うふっ、その程度なんですね", false },
	LAST
};

ResultScenarioData result_rosa_lose[2] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "もう一回よ、次はこうはいかないんだから", false },
	LAST
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//リーラ（青）
//////////////////////////////////////////////////////////////////////////////////////////////////////
ResultScenarioData result_lila_win[2] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "つまらない、特訓して出直しなさい", false },
	LAST
};

ResultScenarioData result_lila_lose[2] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "思ったよりやるわね、見直したわ", false },
	LAST
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
//ojyo(黄)
//////////////////////////////////////////////////////////////////////////////////////////////////////
ResultScenarioData result_ojyo_win[2] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "粋がるなよ雑種、おーっほっほっほっほ！", false },
	LAST
};

ResultScenarioData result_ojyo_lose[2] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "このわたくしがおまえに敗れるのは必定だったか、なかなかに愉しかったぞ", false },
	LAST
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
//tutorial(チュートリアル子)
//////////////////////////////////////////////////////////////////////////////////////////////////////
ResultScenarioData result_jiji_lose[2] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "うぐっ。こ、腰が・・・。", false },
	LAST
};

ResultScenarioData result_jiji_win[2] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "まだまだ若いもんには負けんわい。", false },
	LAST
};

