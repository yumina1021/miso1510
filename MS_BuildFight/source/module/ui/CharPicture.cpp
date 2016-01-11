//=============================================================================
//
// MS_BuildFight [CCharPicture.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "CharPicture.h"
#include "../../administer/Texture.h"
//*****************************************************************************
// 静的変数
//*****************************************************************************
const int CCharPicture::m_apTextureName[] =
{
	TEXTURE_T_START,
	TEXTURE_T_END,
	TEXTURE_T_END,
	TEXTURE_T_END,

	TEXTURE_S_0,
	TEXTURE_S_1,
	TEXTURE_S_2,
	TEXTURE_S_3,
	TEXTURE_S_4,
	TEXTURE_S_5,
	TEXTURE_S_6,
	TEXTURE_S_7,
	TEXTURE_S_8,
	TEXTURE_S_0,
	TEXTURE_S_0,

	TEXTURE_LEVELSTAR,
	TEXTURE_STAGENAME1,
	TEXTURE_STAGENAME2,
	TEXTURE_STAGENAME3,
	TEXTURE_STAGENAME4,
};
//=============================================================================
// コンストラクタ
//=============================================================================
CCharPicture::CCharPicture() :Cform2D(OBJTYPE_PAUSE, 7),
m_Len(0.0f, 0.0f, 0.0f),
m_FadeCoff(0.02f),
m_Mode(GUI_MODE::NORMAL),
m_NowFade(GUI_FADE::FADE_NONE),
m_Diff(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CCharPicture :: ~CCharPicture(void)
{
}
//=============================================================================
// CCharPicture生成
//=============================================================================
CCharPicture *CCharPicture::Create(LPDIRECT3DDEVICE9 pDevice, PictureNum nType, D3DXVECTOR3 pos, float fwidth, float fheight)
{
	CCharPicture *pform2D;

	pform2D = new CCharPicture();
	pform2D->Init(pDevice, nType, pos, fwidth, fheight);

	return pform2D;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CCharPicture::Init(LPDIRECT3DDEVICE9 pDevice, PictureNum nType, D3DXVECTOR3 pos, float fwidth, float fheight)
{
	m_pDevice = pDevice;
	//フィールドの初期化
	Cform2D::Init(m_pDevice, m_apTextureName[(int)nType], pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), fwidth, fheight);
	m_Len = D3DXVECTOR3(fwidth, fheight, 0.0f);
	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CCharPicture::Uninit(void)
{
	//様々なオブジェクトの終了（開放）処理
	Cform2D::Uninit();
}
//=============================================================================
// 更新
//=============================================================================
void CCharPicture::Update(void)
{
	Cform2D::Update();
}
//=============================================================================
// 描画
//=============================================================================
void CCharPicture::Draw(void)
{
	Cform2D::Draw();
}
//=============================================================================
// FunctionName: ChangeGuiState
// Param: void
// ReturnValue: void
// Content: Guiの状態によって変化させる
//=============================================================================
void CCharPicture::ChangeGuiState(GUI_MODE paramMode){

	// 遷移状態の更新
	m_Mode = paramMode;

	// 指定された状態によって分岐
	switch (paramMode)
	{

		// 通常状態の場合
	case GUI_MODE::NORMAL:

		// α値だけ変える
		m_Diff.a = 1.0f;

		// 色情報を設定
		SetDiffuse(m_Diff.r, m_Diff.g, m_Diff.b, m_Diff.a);

		// 分岐を抜ける
		break;

		// 点滅状態
	case GUI_MODE::FLASH:

		// チカチカさせる
		Flash();

		// 分岐を抜ける
		break;

		// 点滅状態
	case GUI_MODE::DESELECT:

		// ポリゴンを徐々に不透明にする
		m_Diff.a += m_FadeCoff;

		// もしα値が最大だったら
		if (m_Diff.a >= 1.0f)
		{
			m_Diff.a = 1.0f;

			// 通常状態に遷移
			m_Mode = GUI_MODE::NORMAL;

		}

		// 頂点の色の変更
		SetDiffuse(m_Diff.a, m_Diff.a, m_Diff.a, 1.0f);

		// 分岐を抜ける
		break;

		// 表示させたくない状態
	case GUI_MODE::HIDE:

		// α値だけ変える
		m_Diff.a = 0.0f;

		// 色情報を設定
		SetDiffuse(m_Diff.r, m_Diff.g, m_Diff.b, m_Diff.a);

		// 分岐を抜ける
		break;

		// 表示させたくない状態
	case GUI_MODE::GRADUALLY_DESELECT:



		// 分岐を抜ける
		break;
		// 表示させたくない状態
	case GUI_MODE::GRADUALLY_SELECT:

		// ポリゴンを徐々に不透明にする
		m_Diff.a += m_FadeCoff;

		// もしα値が最大だったら
		if (m_Diff.a >= 1.0f)
		{
			m_Diff.a = 1.0f;

			// 通常状態に遷移
			m_Mode = GUI_MODE::NORMAL;

		}

		// 頂点の色の変更
		SetDiffuse(m_Diff.r, m_Diff.g, m_Diff.b, m_Diff.a);

		// 分岐を抜ける
		break;
		// 上記以外の場合
	default:

		// 分岐を抜ける
		break;

	}// switch


}// ChangeGuiState
//=============================================================================
// FunctionName: Flash
// Param: void
// ReturnValue: void
// Content: チカチカ点滅する処理
//=============================================================================
void CCharPicture::Flash(void){

	// フェードの状態遷移の管理
	switch (m_NowFade)
	{

		// フェードインの状態の場合
	case GUI_FADE::FADE_IN:

		// ポリゴンを徐々に透明にする
		m_Diff.a -= m_FadeCoff;

		// スイッチを抜ける
		break;

		// フェードアウトの状態の場合
	case GUI_FADE::FADE_OUT:

		// ポリゴンを徐々に不透明にする
		m_Diff.a += m_FadeCoff;

		// スイッチを抜ける
		break;

	}// swithch

	// もしα値が最大だったら
	if (m_Diff.a >= 1.0f)
	{

		// フェード処理を止める
		m_NowFade = GUI_FADE::FADE_IN;

		// もしα値が最小だったら
	}
	else if (m_Diff.a <= 0.5f)
	{

		// フェード処理を止める
		m_NowFade = GUI_FADE::FADE_OUT;

	}// if

	// 頂点の色の変更
	SetDiffuse(m_Diff.a, m_Diff.a, m_Diff.a, 1.0f);

}// Flash
/////////////EOF////////////