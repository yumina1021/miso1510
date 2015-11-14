//=============================================================================
//
// MS_BuildFight [CButton.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "Button.h"

//*****************************************************************************
// 静的変数
//*****************************************************************************
//=============================================================================
// コンストラクタ
//=============================================================================
CButton::CButton() :CCharPicture()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CButton :: ~CButton(void)
{
}
//=============================================================================
// CButton生成
//=============================================================================
CButton *CButton::Create(LPDIRECT3DDEVICE9 pDevice,PictureNum nType,D3DXVECTOR3 pos,float fwidth,float fheight)
{
	CButton *pform2D;

	pform2D = new CButton();
	pform2D->Init(pDevice,nType,pos,fwidth,fheight);

	return pform2D;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CButton :: Init(LPDIRECT3DDEVICE9 pDevice,PictureNum nType,D3DXVECTOR3 pos,float fwidth,float fheight)
{
	//フィールドの初期化
	CCharPicture::Init(pDevice, nType, pos, fwidth, fheight);

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CButton :: Uninit(void)
{
	//様々なオブジェクトの終了（開放）処理
	CCharPicture::Uninit();
}
//=============================================================================
// 更新
//=============================================================================
void CButton :: Update(void)
{

	switch (state)
	{

		// 選択されていない場合
	case BUTTON_STATE::PUSH_OFF:

		// Guiの状態の更新
		ChangeGuiState(GUI_MODE::NORMAL);

		// 分岐を抜ける
		break;

	case BUTTON_STATE::SELECTED:

		// Guiの状態の更新
		ChangeGuiState(GUI_MODE::FLASH);

		// 分岐を抜ける
		break;

	case BUTTON_STATE::DESELECT:

		if (GetGuiMode() == GUI_MODE::NORMAL)
		{

			state = BUTTON_STATE::PUSH_OFF;

		}
		else
		{
			ChangeGuiState(GUI_MODE::DESELECT);

		}
		// 分岐を抜ける
		break;


	case BUTTON_STATE::PUSH_ON:

		// Guiの状態の更新
		ChangeGuiState(GUI_MODE::NORMAL);

		// 分岐を抜ける
		break;

	case BUTTON_STATE::HIDE:

		// Guiの状態の更新
		ChangeGuiState(GUI_MODE::HIDE);

		// 分岐を抜ける
		break;

		// 上記以外の条件の場合
	default:

		// 分岐を抜ける
		break;
	}

	CCharPicture::Update();
}
//=============================================================================
// 描画
//=============================================================================
void CButton::Draw(void)
{
	CCharPicture::Draw();
}

//=============================================================================
// 描画
//=============================================================================
void CButton::ChangeSelectButtonState(CButton* paramDeselectPtr, CButton* paramSelectPtr){
	
	paramDeselectPtr->SetButtonState(BUTTON_STATE::DESELECT);
	paramSelectPtr->SetButtonState(BUTTON_STATE::SELECTED);


}

/////////////EOF////////////