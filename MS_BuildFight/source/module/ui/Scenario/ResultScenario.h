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
ResultScenarioData result_rosa[4] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "���ӂ��A���̒��x�Ȃ�ł���", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_NORMAL, "���ɏ��Ă邩����H", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "���Ă��炲�J������������", false },
	LAST
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
//���[���i�j
//////////////////////////////////////////////////////////////////////////////////////////////////////
ResultScenarioData result_lila[4] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "�ʓ|�����Ǒ��肵�Ă�����", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "�܂�Ȃ��킢�����狖���Ȃ�����", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "�o�債�Ă�", false },
	LAST
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
//ojyo(��)
//////////////////////////////////////////////////////////////////////////////////////////////////////
ResultScenarioData result_ojyo[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "�킽�����̑���͂��Ȃ��H", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_NORMAL, "�����̕��ۂł킽�����Ɛ킦��̂ł��B���h�Ɏv���Ȃ����I", false },
	LAST
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
//tutorial(�`���[�g���A���q)
//////////////////////////////////////////////////////////////////////////////////////////////////////
ResultScenarioData result_tutorial[4] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "�����Q�[���X�^�[�g�ł��I", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "�����̏��_�͂ǂ���ɔ��΂ނ��I�H", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "���ڂ̈��ł��I�I", false },
	LAST
};

