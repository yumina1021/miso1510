//=============================================================================
//
// MS_BuildFight [CFade.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CFADE_H_
#define _CFADE_H_
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
	FADE_NONE =0,	//しない
	FADE_IN,		//イン
	FADE_IN_END,	//イン終了
	FADE_OUT,		//アウト
	FADE_OUT_END,	//アウト終了
	FADE_MAX
}FADEMODE;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CFade  : public Cform2D
{
	public:
		CFade();//コンストラクタ
		~CFade(void);//デストラクタ

		static CFade *Create(LPDIRECT3DDEVICE9 pDevice,int type);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,int type);//初期化
		void Uninit(void);//終了
		void Update(void);//更新
		void Draw(void);//描画

		void StartFade(FADEMODE fade,int nCount,D3DXCOLOR color, int type);

		void SetFade(FADEMODE fade){m_fadeType=fade;};
		FADEMODE GetFade(void){return m_fadeType;};
		bool GetPlayFade(void){return m_bfade;};

	private:
		LPDIRECT3DDEVICE9	m_pDevice;				// pDeviceオブジェクト(描画に必要)
		int					m_nCount;				//フェード時間
		static const LPSTR	m_apTextureName[];		//テクスチャー
		bool				m_bfade;				//フェードしているか
		FADEMODE			m_fadeType;				//フェードの状態
		float				m_fAlpha;				//アルファ値
		D3DXCOLOR			m_color;				//色
		static int			m_tex_id;
};

#endif

/////////////EOF////////////