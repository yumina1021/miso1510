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
GameScenarioData scenario_rosa_start[4] = 
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "���Ȃ������̑���H", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_NORMAL, "���ɏ��Ă邩����H", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "���Ă��炲�J������������", false },
	LAST
};
GameScenarioData scenario_rosa_win[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_NORMAL, "�Ȃ��Ȃ���邶��Ȃ�", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "���J���ɂ��Ă�̂��ȁH", false },
	LAST
};
GameScenarioData scenario_rosa_lose[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "�܂�Ȃ���˂�", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "���񂽃}�O���H", false },
	LAST
};
GameScenarioData scenario_rosa_harf[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "�������炢��", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_NORMAL, "�܂��܂��{�C�o���ĂȂ����c", false },
	LAST
};
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
GameScenarioData scenario_ojyo_start[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "�킽�����̑���͂��Ȃ��H", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_NORMAL, "�����̕��ۂł킽�����Ɛ킦��̂ł��B���h�Ɏv���Ȃ����I", false },
	LAST
};
GameScenarioData scenario_ojyo_win[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SAD, "�Ӂ[��B���̒��x�H(�����̕��ۂł�邶��Ȃ��c)", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_NORMAL, "��������Ă���������������B���ꂩ���I", false },
	LAST
};
GameScenarioData scenario_ojyo_lose[3]=
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "����Ȃ��̂Ȃ̂�����H�킽�����̈�����", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_NORMAL, "���������ƍ����J���č����グ�܂���I", false },
	LAST
};
GameScenarioData scenario_ojyo_harf[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_ANGERY, "�V�ɋ�����ׂ����̉�𓯂���n�ɗ������邩�I", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_NORMAL, "���̕s�h�A�����ɒl����I�I", false },
	LAST
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
//tutorial(�`���[�g���A���q)
//////////////////////////////////////////////////////////////////////////////////////////////////////
GameScenarioData scenario_tutorial_start[4] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "�����Q�[���X�^�[�g�ł��I", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "�����̏��_�͂ǂ���ɔ��΂ނ��I�H", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "���ڂ̈��ł��I�I", false },
	LAST
};
GameScenarioData scenario_tutorial_win[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "���ݑ��肪��s���Ă���܂��I", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "���Ȃ����撣���Ă��������I", false },
	LAST
};
GameScenarioData scenario_tutorial_lose[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "�����˂��������i���I", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "�������I�������ł���[", false },
	LAST
};
GameScenarioData scenario_tutorial_harf[3] =
{
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "���ݓ������炢�̋����ł��B", false },
	{ DEFAULT_TEXT_X, DEFAULT_TEXT_Y, DEFAULT_TEXT_SPEED, FACIAL_SMILE, "�܂��܂����s�͂킩��܂���I", false },
	LAST
};
