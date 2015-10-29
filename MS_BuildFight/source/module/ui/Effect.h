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
	effect001=0,
	effect002,
	effect003,
	effect000,
	effect010,
	Eeffect001,
	Eeffect002,
	Eeffect003,
	Eeffect000,
	Eeffect010,
	Tutorialeffect001,
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
	EffectMaxNum
}EffectNum;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEffect  : public Cform2D
{
	public:
		CEffect();//コンストラクタ
		~CEffect(void);//デストラクタ

		static CEffect *Create(LPDIRECT3DDEVICE9 pDevice,EffectNum nType,D3DXVECTOR3 movePos,D3DXVECTOR3 moveRot);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,EffectNum nType,D3DXVECTOR3 pos,D3DXVECTOR3 rot);//初期化
		void Uninit(void);//終了
		void Update(void);//更新
		void Draw(void);//描画
		void SetViewFlag(bool change,int time){m_ViewFlag=change;m_nCount=time;};

	private:
		LPDIRECT3DDEVICE9	m_pDevice;				// pDeviceオブジェクト(描画に必要)
		int					m_nCount;
		static const LPSTR	m_apTextureName[];
		bool				m_ViewFlag;
};

#endif

/////////////EOF////////////