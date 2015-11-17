//=============================================================================
//
// MS_BuildFight [CEffect.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CEFFECT_H_
#define _CEFFECT_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "../../form/form2D.h"
//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************
typedef enum
{
	circuit_wall = 0,
	circuit_circle,
	action,
	please_shot,
	shot_ball,
	judge_timeout,
	Tutoriale,
	ready1,
	ready2,
	/*
	Eeffect002,
	Eeffect003,
	Eeffect000,
	Eeffect010,
	Tutorialeffect002,
	Tutorialeffect003,
	Tutorialeffect004,
	Tutorialeffect005,
	Tutorialeffect006,
	Tutorialeffect007,
	Tutorialeffect008,
	Selecteffect001,
	Selecteffect002,
	Selecteffect003,
	Selecteffect000,
	Selecteffect010,
	Selecteffect999,
	Selecteffect1000,
	SelecteffectMatching,
	Gready,
	Gstart,
	Gwin,
	Glose,
	Gtimeout,
	GReplay,
	GameCleareffect001,
	GameCleareffect002,
	*/
	EffectMaxNum
}EffectNum;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEffect  : public Cform2D
{
	public:

		enum EFFECT_PHASE
		{
			NOT_VIEW = 0,
			VIEW,
			COUNT_VIEW,
			FADE_IN,
			FADE_IN_COUNT,
			FADE_IN_OUT,
			FADE_OUT,
			MAX_PHASE
		};
		enum EFFECT_FADE
		{
			UP = 0,
			DOWN,
			RIGHT,
			LEFT,
			UP_LEFT,
			DOWN_RIGHT,
		};

		CEffect();//�R���X�g���N�^
		~CEffect(void);//�f�X�g���N�^

		static CEffect *Create(LPDIRECT3DDEVICE9 pDevice, EffectNum nType, D3DXVECTOR3 movePos, D3DXVECTOR3 moveRot, float width=1300, float height=750);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice, EffectNum nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float width, float height);//������
		void Uninit(void);//�I��
		void Update(void);//�X�V
		void Draw(void);//�`��
		
		//�ʏ�`��
		void SetView(bool change){if (change == true){m_effectPhase = VIEW;}else{m_effectPhase = NOT_VIEW;}};

		//���ԕt���ŕ`��
		void SetView(bool change, int time){ if (change == true){ m_effectPhase = COUNT_VIEW; } else{ m_effectPhase = NOT_VIEW; } m_nCount = time; };

		//�t�F�[�h�C��
		void FadeIn(int time, EFFECT_FADE type);

		//�t�F�[�h�C���㎞�ԕt��
		void FadeInAfterCount(int fadeTime, EFFECT_FADE type, int viewTime);

		//�t�F�[�h�C����t�F�[�h�A�E�g
		void FadeInAfterFadeOut(int fadeInTime, EFFECT_FADE intype, int viewTime, int fadeOutTime, EFFECT_FADE outtype);

		//�t�F�[�h�A�E�g
		void FadeOut(int time, EFFECT_FADE type);

	private:
		void FadeMove(void);
		LPDIRECT3DDEVICE9	m_pDevice;				// pDevice�I�u�W�F�N�g(�`��ɕK�v)
		int					m_nCount;
		float				m_nCountFade;
		float				m_nCountFadeMax;
		static const LPSTR	m_apTextureName[];
		EFFECT_PHASE		m_effectPhase;
		EFFECT_FADE			m_FadeType;
		D3DXVECTOR3			m_firstPos;
		D3DXVECTOR2			m_startPos;				//�J�n�_
		D3DXVECTOR2			m_distPos;				//�����_
		float				m_nCountFadeA;			//�ꎞ�I�m�ۗp
		EFFECT_FADE			m_FadeTypeA;			//�ꎞ�I�m�ۗp
};

#endif

/////////////EOF////////////