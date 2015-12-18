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
// インクルードファイル
//*****************************************************************************
#include "../../form/form2D.h"
//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************
typedef enum
{
	circuit_wall = 0,
	circuit_circle,
	action,
	please_shot_rosa,
	please_shot_lila,
	please_shot_licht,
	please_shot_jiji,
	shot_ball_rosa,
	shot_ball_lila,
	shot_ball_licht,
	shot_ball_jiji,
	judge_timeout,
	Tutoriale,
	ready1,
	ready2,
	gage,
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
// クラス定義
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

		CEffect();//コンストラクタ
		~CEffect(void);//デストラクタ

		static CEffect *Create(LPDIRECT3DDEVICE9 pDevice, EffectNum nType, D3DXVECTOR3 movePos, D3DXVECTOR3 moveRot, float width=1300, float height=750);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice, EffectNum nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float width, float height);//初期化
		void Uninit(void);//終了
		void Update(void);//更新
		void Draw(void);//描画
		
		//通常描画
		void SetView(bool change){if (change == true){m_effectPhase = VIEW;}else{m_effectPhase = NOT_VIEW;}};

		//時間付きで描画
		void SetView(bool change, int time){ if (change == true){ m_effectPhase = COUNT_VIEW; } else{ m_effectPhase = NOT_VIEW; } m_nCount = time; };

		//フェードイン
		void FadeIn(int time, EFFECT_FADE type);

		//フェードイン後時間付き
		void FadeInAfterCount(int fadeTime, EFFECT_FADE type, int viewTime);

		//フェードイン後フェードアウト
		void FadeInAfterFadeOut(int fadeInTime, EFFECT_FADE intype, int viewTime, int fadeOutTime, EFFECT_FADE outtype);

		//フェードアウト
		void FadeOut(int time, EFFECT_FADE type);

	private:
		void FadeMove(void);
		LPDIRECT3DDEVICE9	m_pDevice;				// pDeviceオブジェクト(描画に必要)
		int					m_nCount;
		float				m_nCountFade;
		float				m_nCountFadeMax;
		static const LPSTR	m_apTextureName[];
		EFFECT_PHASE		m_effectPhase;
		EFFECT_FADE			m_FadeType;
		D3DXVECTOR3			m_firstPos;
		D3DXVECTOR2			m_startPos;				//開始点
		D3DXVECTOR2			m_distPos;				//到着点
		float				m_nCountFadeA;			//一時的確保用
		EFFECT_FADE			m_FadeTypeA;			//一時的確保用
};

#endif

/////////////EOF////////////