//=============================================================================
//
// MS_BuildFight [CButton.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CBUTTON_H_
#define _CBUTTON_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CharPicture.h"

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************
enum class BUTTON_STATE : unsigned short
{
	PUSH_OFF = 0,	// 押されていない
	SELECTED,		// 選択中
	DESELECT,		// 
	PUSH_ON,		// 押している
	HIDE,			// 

};
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CButton : public CCharPicture
{
	public:
		CButton();		//コンストラクタ
		~CButton(void);	//デストラクタ

		static CButton *Create(LPDIRECT3DDEVICE9 pDevice,
			PictureNum nType,
			D3DXVECTOR3 pos,
			float fwidth,
			float fheight);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,
						PictureNum nType,
						D3DXVECTOR3 pos,
						float fwidth,
						float fheight);	// 初期化
		void Uninit(void);				// 終了
		void Update(void);				// 更新
		void Draw(void);				// 描画

		void SetButtonState(BUTTON_STATE paramState){ state = paramState; };// ボタンの状態の遷移
		static void ChangeSelectButtonState(CButton* paramDeselectPtr, CButton* paramSelectPtr);
	private:
		BUTTON_STATE	state;
		float			m_fDiffuse;
};

#endif

/////////////EOF////////////