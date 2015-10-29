//=============================================================================
//
// MS_BuildFight [CBackGround.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CBACKGROUND_H_
#define _CBACKGROUND_H_
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
	BACKGROUND_TITLE=0,
	BACKGROUND_TUTORIAL,
	BACKGROUND_SELECT,
	BACKGROUND_LOAD,
	BACKGROUND_GAME,
	BACKGROUND_GAMECLEAR,
	BACKGROUND_VSEND,
	BACKGROUND_RESULT
}BACKGROUNDTYPE;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBackGround  : public Cform2D
{
	public:
		CBackGround();//コンストラクタ
		~CBackGround(void);//デストラクタ

		static CBackGround *Create(LPDIRECT3DDEVICE9 pDevice,BACKGROUNDTYPE Type);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,BACKGROUNDTYPE Type);//初期化
		void Uninit(void);//終了
		void Update(void);//更新
		void Draw(void);//描画

	private:
		LPDIRECT3DDEVICE9	m_pDevice;				// pDeviceオブジェクト(描画に必要)
		int					m_nCount;				//フェード時間
		static const LPSTR	m_apTextureName[];		//テクスチャー
};

#endif

/////////////EOF////////////