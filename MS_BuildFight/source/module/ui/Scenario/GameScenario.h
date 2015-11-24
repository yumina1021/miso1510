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

#define LAST	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, 0, FACIAL_NONE, "�E�E�E", true }

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
//rosa�i�s���N�j
//////////////////////////////////////////////////////////////////////////////////////////////////////
GameScenarioData scenario_rosa_start[5] = 
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "����", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "����", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "����", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "����", false },
	LAST
};
GameScenarioData scenario_rosa_win[4];
GameScenarioData scenario_rosa_lose[4];
GameScenarioData scenario_rosa_harf[4];
//////////////////////////////////////////////////////////////////////////////////////////////////////
//���[���i�j
//////////////////////////////////////////////////////////////////////////////////////////////////////
GameScenarioData scenario_lila_start[4] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "�ʓ|�����Ǒ��肵�Ă�����", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "�܂�Ȃ��킢�����狖���Ȃ�����", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "�o�債�Ă�", false },
	LAST
};
GameScenarioData scenario_lila_win[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "���̒��x�Ȃ́H", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "�����Ɩ{�C�o����", false },
	LAST
};
GameScenarioData scenario_lila_lose[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "�Ȃ��Ȃ���邶���", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "�����Ȃ�����c", false },
	LAST
};
GameScenarioData scenario_lila_harf[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "�������炢", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "���|�I�ȗ͂̍��������Ă�����", false },
	LAST
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//ojyo(��)
//////////////////////////////////////////////////////////////////////////////////////////////////////
GameScenarioData scenario_ojyo_start[5];
GameScenarioData scenario_ojyo_win[4];
GameScenarioData scenario_ojyo_lose[4];
GameScenarioData scenario_ojyo_harf[4];
//////////////////////////////////////////////////////////////////////////////////////////////////////
//tutorial(�`���[�g���A���q)
//////////////////////////////////////////////////////////////////////////////////////////////////////
GameScenarioData scenario_tutorial_start[5];
GameScenarioData scenario_tutorial_win[4];
GameScenarioData scenario_tutorial_lose[4];
GameScenarioData scenario_tutorial_harf[4];
