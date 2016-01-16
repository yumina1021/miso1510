//=============================================================================
//
// MS_BuildFight [LocusEffect.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CUPIN_H_
#define _CUPIN_H_
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
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCupin
{
	public:
		CCupin();//コンストラクタ
		~CCupin();//デストラクタ

		static CCupin* Create(LPDIRECT3DDEVICE9 pDevice);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);//初期化
		void Uninit(void);//終了
		void Update(void);//更新
		void Draw(void);//描画

		void SetFlag(bool change){ m_bFlag = change; };
		bool GetFlag(){ return m_bFlag; };
		void SetDrawFlag(bool change){ m_bDrawFlag = change; };
		bool GetDrawFlag(){ return m_bDrawFlag; };
		float EsasingNone(float paramMin, float paramMax, float paramTime);

	private :
		LPDIRECT3DDEVICE9		m_pDevice;			// pDeviceオブジェクト(描画に必要)

		int m_texid;
		float m_timer;
		float m_s_timer[5];
		bool m_bFlag;
		bool m_bDrawFlag;
		Cform2D* m_pcupin[5];
		D3DXVECTOR3 m_pos[5];
		D3DXVECTOR3 m_s_pos;
};

#endif

/////////////EOF////////////