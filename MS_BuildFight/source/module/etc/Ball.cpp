//=============================================================================
//
// MS_BuildFight [CBall.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "Ball.h"
#include "LocusEffect.h"
#include "../../exten_common.h"
//*****************************************************************************
// 静的変数
//*****************************************************************************
const LPSTR CBall::m_ModelName[]=
{
	"data/MODEL/ball.x",
};
//=============================================================================
// コンストラクタ
//=============================================================================
CBall :: CBall():CformX(OBJTYPE_X,4)
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CBall :: ~CBall(void)
{
}
//=============================================================================
// CBall生成
//=============================================================================
CBall *CBall::Create(LPDIRECT3DDEVICE9 pDevice,int nType,D3DXVECTOR3 movePos,D3DXVECTOR3 moveRot)
{

	CBall *pformX;

	pformX = new CBall();
	pformX->Init(pDevice,nType);
	pformX->SetPos(movePos);
	pformX->SetRot(moveRot);

	return pformX;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CBall :: Init(LPDIRECT3DDEVICE9 pDevice,int nType)
{
	//デバイスの取得
	m_pDevice=pDevice;

	//建物の初期化
	CformX::Init(m_pDevice,m_ModelName[nType],NULL);

	m_bViewFlag = true;

	m_bGoal = false;

	//エフェクト追加
	m_pLocusEffect = CLocusEffect::Create(pDevice, NULL, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pLocusEffect->SetFlag(true);

	//ピクセルシェーダー用に変換1
	Create_PS("source/shader/basicPS.hlsl", "PS_DIFFUSE", &shaderSet.ps, &shaderSet.psc, m_pDevice);

	//バーテックスシェーダー用に変換1
	Create_VS("source/shader/basicVS.hlsl", "VS", &shaderSet.vs, &shaderSet.vsc, m_pDevice);

	CformX::SetShader(shaderSet);

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CBall :: Uninit(void)
{
	//様々なオブジェクトの終了（開放）処理

	CformX::Uninit();

}
//=============================================================================
// 更新
//=============================================================================
void CBall :: Update(void)
{
	//エフェクトに座標設定
	m_pLocusEffect->SetPosBuffer(CformX::GetPos());
	m_pLocusEffect->SetPos(CformX::GetPos());

	//更新呼び出し
	CformX::Update();
}
//=============================================================================
// 描画
//=============================================================================
void CBall :: Draw(void)
{
	if (m_bViewFlag)
	{
		m_pLocusEffect->Draw();
		CformX::Draw();
	}
}
/////////////EOF////////////