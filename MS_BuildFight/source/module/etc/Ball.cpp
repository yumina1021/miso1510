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
#include "../../administer/Debugproc.h"
//*****************************************************************************
// 静的変数
//*****************************************************************************
const LPSTR CBall::m_ModelName[]=
{
	"data/MODEL/ball.x",
	"data/MODEL/ball.x",
	"data/MODEL/ball.x",
	"data/MODEL/ball.x",
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
	switch (nType)
	{
	case 0:Create_PS("source/shader/basicPS.hlsl", "PS_BALL_ROSA", &shaderSet.ps, &shaderSet.psc, m_pDevice);break;
	case 1:Create_PS("source/shader/basicPS.hlsl", "PS_BALL_LIRA", &shaderSet.ps, &shaderSet.psc, m_pDevice);break;
	case 2:Create_PS("source/shader/basicPS.hlsl", "PS_BALL_THEME", &shaderSet.ps, &shaderSet.psc, m_pDevice);break;
	case 3:Create_PS("source/shader/basicPS.hlsl", "PS_BALL_HAGE", &shaderSet.ps, &shaderSet.psc, m_pDevice); break;
	default:Create_PS("source/shader/basicPS.hlsl", "PS_DIFFUSE", &shaderSet.ps, &shaderSet.psc, m_pDevice); break;
	}

	//バーテックスシェーダー用に変換1
	Create_VS("source/shader/basicVS.hlsl", "VS", &shaderSet.vs, &shaderSet.vsc, m_pDevice);

	CformX::SetShader(shaderSet);

	shot_num = 0;

	m_MovVelocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RotVelocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Mass = 1.0f;
	m_MOI = 100.0f;
	m_MovResist = 0.02f;
	m_RotResist = 0.02f;
	m_alpha = 0.4f;

	CformX::SetTexture("data/TEXTURE/tama.jpg", 0);

	m_bmove = false;
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
	if (m_bmove)
	{
		m_MovVelocity -= m_MovVelocity * m_MovResist;
		m_RotVelocity -= m_RotVelocity * m_RotResist;

		D3DXVECTOR3 pos = CformX::GetPos();
		pos += m_MovVelocity;
		CformX::SetPos(pos);
		//エフェクトに座標設定
		m_pLocusEffect->SetPosBuffer(CformX::GetPos());
		m_pLocusEffect->SetPos(CformX::GetPos());
	}
	CDebugProc::Print("velocity::x:%fy:%f:z:%f\n", m_MovVelocity.x, m_MovVelocity.y, m_MovVelocity.z);
	//更新呼び出し
	CformX::Update();
}
//=============================================================================
// 描画
//=============================================================================
void CBall :: Draw(void)
{
	shaderSet.psc->SetFloatArray(m_pDevice, "g_ballalpha", (float*)&m_alpha, 1);
	if (m_bViewFlag)
	{
		m_pLocusEffect->Draw();
		CformX::Draw();
	}
}
//=============================================================================
// 物理演算
//=============================================================================
void CBall::AddForce(D3DXVECTOR3 Force, D3DXVECTOR3 Position)
{
	m_MovVelocity += Force / m_Mass;
	D3DXVECTOR3 vec, torq;
	vec = Position - CformX::GetPos();
	D3DXVec3Cross(&torq, &vec, &Force);
	m_RotVelocity += torq / m_MOI;
}
//=============================================================================
// 物理演算
//=============================================================================
void CBall::AddForce(D3DXVECTOR3 force)
{
	D3DXVECTOR3 acc;
	acc = force / m_Mass;
	m_MovVelocity += acc;
}
/////////////EOF////////////