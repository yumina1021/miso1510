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

#define LAST	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, 0, FACIAL_NONE, "�E�E�E", true }

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
//rosa�i�s���N�j
//////////////////////////////////////////////////////////////////////////////////////////////////////
ResultScenarioData result_rosa_win[2] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "���ӂ��A���̒��x�Ȃ�ł���", false },
	LAST
};

ResultScenarioData result_rosa_lose[2] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "��������A���͂����͂����Ȃ��񂾂���", false },
	LAST
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//���[���i�j
//////////////////////////////////////////////////////////////////////////////////////////////////////
ResultScenarioData result_lila_win[2] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "�܂�Ȃ��A���P���ďo�����Ȃ���", false },
	LAST
};

ResultScenarioData result_lila_lose[2] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "�v����������ˁA����������", false },
	LAST
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
//ojyo(��)
//////////////////////////////////////////////////////////////////////////////////////////////////////
ResultScenarioData result_ojyo_win[2] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "������Ȃ�G��A���[���ق��ق��ق��فI", false },
	LAST
};

ResultScenarioData result_ojyo_lose[2] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "���̂킽���������܂��ɔs���͕̂K�肾�������A�Ȃ��Ȃ��ɖ�����������", false },
	LAST
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
//tutorial(�`���[�g���A���q)
//////////////////////////////////////////////////////////////////////////////////////////////////////
ResultScenarioData result_jiji_lose[2] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "�������B���A�����E�E�E�B", false },
	LAST
};

ResultScenarioData result_jiji_win[2] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "�܂��܂��Ⴂ����ɂ͕�����킢�B", false },
	LAST
};

