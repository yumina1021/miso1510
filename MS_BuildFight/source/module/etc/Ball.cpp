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

	HRESULT hr;
	LPD3DXBUFFER err;
	LPD3DXBUFFER code;

	//ピクセルシェーダー用に変換
	hr = D3DXCompileShaderFromFile("source/shader/basicPS.hlsl", NULL, NULL, "PS_DIFFUSE", "ps_2_0", 0, &code, &err, &shaderSet.psc);

	if (FAILED(hr))
	{
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		err->Release();
		return false;
	}
	//シェーダーの登録
	hr = pDevice->CreatePixelShader((DWORD*)code->GetBufferPointer(), &shaderSet.ps);

	if (FAILED(hr))
	{
		MessageBox(NULL, "FAILED", "CreatePixelShader", MB_OK);
		return false;
	}

	//バーテックスシェーダー用に変換1
	hr = D3DXCompileShaderFromFile("source/shader/basicVS.hlsl", NULL, NULL, "VS", "vs_2_0", 0, &code, &err, &shaderSet.vsc);
	if (FAILED(hr))
	{
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		err->Release();
		return false;
	}
	//シェーダーの登録
	hr = pDevice->CreateVertexShader((DWORD*)code->GetBufferPointer(), &shaderSet.vs);
	if (FAILED(hr))
	{
		MessageBox(NULL, "FAILED", "CreateVertexShader", MB_OK);
		return false;
	}

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
		CformX::Draw();
	}
}
/////////////EOF////////////