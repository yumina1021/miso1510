//=============================================================================
//
// MS_BuildFight [CCursor.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "Cursor.h"
#include "../../administer/Input.h"
#include "../../administer/Maneger.h"

//*****************************************************************************
// 静的変数
//*****************************************************************************
const float CURSOR_MOVE_COFF(10.0f);

//=============================================================================
// コンストラクタ
//=============================================================================
CCursor::CCursor() :CCharPicture(),
m_fDiffuse(1.0f),
m_fVelocity(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
m_bUseWiiPad(false),
m_Time(0.0f)
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CCursor :: ~CCursor(void)
{
}
//=============================================================================
// CCursor生成
//=============================================================================
CCursor *CCursor::Create(LPDIRECT3DDEVICE9 pDevice,PictureNum nType,D3DXVECTOR3 pos,float fwidth,float fheight)
{
	CCursor *pform2D;

	pform2D = new CCursor();
	pform2D->Init(pDevice,nType,pos,fwidth,fheight);

	return pform2D;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CCursor :: Init(LPDIRECT3DDEVICE9 pDevice,PictureNum nType,D3DXVECTOR3 pos,float fwidth,float fheight)
{
	//フィールドの初期化
	CCharPicture::Init(pDevice, nType, pos, fwidth, fheight);

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CCursor :: Uninit(void)
{
	//様々なオブジェクトの終了（開放）処理
	CCharPicture::Uninit();
}
//=============================================================================
// 更新
//=============================================================================
void CCursor :: Update(void)
{

	// 移動量の加算
	//AddForce();

	CCharPicture::Update();
}
//=============================================================================
// 描画
//=============================================================================
void CCursor :: Draw(void)
{
	CCharPicture::Draw();
}
//=============================================================================
// カール移動での選択
//=============================================================================
bool CCursor::HitChkRect(const D3DXVECTOR3& paramPos1,
	const D3DXVECTOR3& paramPos2,
	const D3DXVECTOR3& paramLen1,
	const D3DXVECTOR3& paramLen2){

	if (abs(paramPos1.x - paramPos2.x) < (paramLen1.x * 0.5f + paramLen2.x * 0.5f) //横の判定
		&& abs(paramPos1.y - paramPos2.y) < (paramLen1.y * 0.5f + paramLen2.y * 0.5f)) //縦の判定
	{

		// 当たった
		return true;

	}

	// 当たってない
	return false;

}
//=============================================================================
// キーボードを使用しての移動
// Wiiリモコンを使わないカーソル移動はこちらを使う
//=============================================================================
void CCursor::MoveByKeybord(void){

	POINT tmpPointPos;
	D3DXVECTOR3 tmpPos(GetPos());

	HWND tmpWnd = CManager::GetSetWndHandle();

	GetCursorPos(&tmpPointPos);
	ScreenToClient(tmpWnd, &tmpPointPos);

	tmpPos.x = static_cast<float>(tmpPointPos.x);
	tmpPos.y = static_cast<float>(tmpPointPos.y);

	SetPos(tmpPos);

	// 初期化
	m_fVelocity.x = 0.0f;
	m_fVelocity.y = 0.0f;

}
//=============================================================================
// キーボードを使用しての移動
// Wiiリモコンを使わないカーソル移動はこちらを使う
//=============================================================================
void CCursor::AddForce(void){

	D3DXVECTOR3 tmpPos(GetPos());

	// 座標の設定
	SetPos(tmpPos + m_fVelocity);

}
//=============================================================================
// キーボードを使用しての移動
// Wiiリモコンを使わないカーソル移動はこちらを使う
//=============================================================================
void CCursor::SyncCharPos(D3DXVECTOR3 paramSyncPos){

	D3DXVECTOR3 tmpPos(GetPos());

	SetPos(EsasingNone(tmpPos, paramSyncPos, m_Time));

	if (m_Time >= 1.0f)
	{
		m_Time = 0.0f;
	}
	else
	{
		m_Time += 0.02f;
	}

}
//=============================================================================
// キーボードを使用しての移動
//=============================================================================
void CCursor::RadianRot(float& paramRot)
{
	if (paramRot > D3DX_PI)
	{
		paramRot += -D3DX_PI * 2.0f;
	}
	else if (paramRot < -D3DX_PI)
	{
		paramRot += D3DX_PI * 2.0f;
	}
}
//=============================================================================
// Easing処理
//=============================================================================
D3DXVECTOR3 CCursor::EsasingNone(D3DXVECTOR3 paramMinPos, D3DXVECTOR3 paramMaxPos, float paramTime){

	// 線形
	//return (paramMaxPos - paramMinPos)* paramTime + paramMinPos;

	float tmpRet(0.0f);

	if (paramTime < 0.5f)
	{

		// 二次曲線
		tmpRet = (2.0 * paramTime) * (2.0 * paramTime) * 0.5f;

	}
	else
	{
		tmpRet = -((2.0 * paramTime - 2.0f) * (2.0 * paramTime - 2.0f)) * 0.5f + 1.0f;

	}

	return (paramMaxPos - paramMinPos) * tmpRet + paramMinPos;
	
}
/////////////EOF////////////