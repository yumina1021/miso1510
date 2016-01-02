//=============================================================================
//
// MS_BuildFight [Sound.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CTEXTURE_H_
#define _CTEXTURE_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "../common.h"
//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	TEXTURE_ARROW = 0,
	TEXTURE_ACTION,
	TEXTURE_BAR,
	TEXTURE_BAR2,
	TEXTURE_BLUE,
	TEXTURE_CHARA,
	TEXTURE_CHARANAME1,
	TEXTURE_CHARANAME2,
	TEXTURE_CHARANAME3,
	TEXTURE_CHARANAME4,
	TEXTURE_CHARAFRAME,
	TEXTURE_CIRCUIT,
	TEXTURE_CIRCUIT_CIRCLE,
	TEXTURE_CRACKER,
	TEXTURE_DRAW,
	TEXTURE_EXPLOSION000,
	TEXTURE_EXPLOSION001,
	TEXTURE_EXPLOSION002,
	TEXTURE_EXPLOSION003,
	TEXTURE_GAGE,
	TEXTURE_GOLFBALL,
	TEXTURE_LEVELSTAR,
	TEXTURE_LICHT,
	TEXTURE_LILA,
	TEXTURE_ROSA,
	TEXTURE_LIGHT,
	TEXTURE_LOADING1,
	TEXTURE_LOADING2,
	TEXTURE_LOADING3,
	TEXTURE_LOSE,
	TEXTURE_LOSER,
	TEXTURE_NUMBER000,
	TEXTURE_NUMBER001,
	TEXTURE_P_CONTINUE,
	TEXTURE_P_QUIT,
	TEXTURE_P_RETRY,
	TEXTURE_PAUSE,
	TEXTURE_PLEASE_JIJI,
	TEXTURE_PLEASE_LICHT,
	TEXTURE_PLEASE_LILA,
	TEXTURE_PLEASE_ROSA,
	TEXTURE_RAINBOW,
	TEXTURE_READY1,
	TEXTURE_READY2,
	TEXTURE_RED,
	TEXTURE_REPLAY,
	TEXTURE_S_0,
	TEXTURE_S_1,
	TEXTURE_S_2,
	TEXTURE_S_3,
	TEXTURE_S_4,
	TEXTURE_S_5,
	TEXTURE_S_6,
	TEXTURE_S_7,
	TEXTURE_S_99,
	TEXTURE_SELECT,
	TEXTURE_SELECTPLAYER1,
	TEXTURE_SELECTPLAYER2,
	TEXTURE_SHOT_JIJI,
	TEXTURE_SHOT_LICHT,
	TEXTURE_SHOT_LILA,
	TEXTURE_SHOT_ROSA,
	TEXTURE_SKY000,
	TEXTURE_SKY004,
	TEXTURE_STAGENAME1,
	TEXTURE_STAGENAME2,
	TEXTURE_STAGENAME3,
	TEXTURE_STAGENAME4,
	TEXTURE_STAR,
	TEXTURE_T_END,
	TEXTURE_T_START,
	TEXTURE_TAMA,
	TEXTURE_TIMEOUT,
	TEXTURE_WIN,
	TEXTURE_WINDOW,
	TEXTURE_WINER,
	TEXTURE_YARD,
	TEXTURE_YELLOW,
	TEXTURE_C_LICHT_DO,
	TEXTURE_C_LICHT_NAKI,
	TEXTURE_C_LICHT_NORMAL,
	TEXTURE_C_LICHT_WARA,
	TEXTURE_C_LILA_DO,
	TEXTURE_C_LILA_NAKI,
	TEXTURE_C_LILA_NORMAL,
	TEXTURE_C_LILA_WARA,
	TEXTURE_C_NAVI_DO,
	TEXTURE_C_NAVI_NAKI,
	TEXTURE_C_NAVI_NORMAL,
	TEXTURE_C_NAVI_WARA,
	TEXTURE_C_ROSA_DO,
	TEXTURE_C_ROSA_NAKI,
	TEXTURE_C_ROSA_NORMAL,
	TEXTURE_C_ROSA_WARA,
	TEXTURE_R_LICHT_WIN,
	TEXTURE_R_LICHT_LOSE,
	TEXTURE_R_ROSA_WIN,
	TEXTURE_R_ROSA_LOSE,
	TEXTURE_R_LILA_WIN,
	TEXTURE_R_LILA_LOSE,
	TEXTURE_R_JIJI_WIN,
	TEXTURE_R_JIJI_LOSE,
	TEXTURE_LABEL_MAX
} TEXTURE_LABEL;

//*****************************************************************************
// �p�����[�^�\���̒�`
//*****************************************************************************


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTexture
{
	public:
		CTexture(void);				//�R���X�g���N�^
		~CTexture(void);				//�f�X�g���N�^

		HRESULT Init(LPDIRECT3DDEVICE9 pdevice);				//������
		void Uninit(void);						//�I��

		static LPDIRECT3DTEXTURE9 GetTex(int id)
		{
			if (id < TEXTURE_ARROW || TEXTURE_LABEL_MAX <= id)
			{
				return NULL;
			}
			return m_pD3DTex[id]; 
		}

	private:
		static LPDIRECT3DTEXTURE9  	m_pD3DTex[TEXTURE_LABEL_MAX];			//�e�N�X�`���\���p
};

#endif

/////////////EOF////////////