//=============================================================================
//
// MS_BuildFight [CLock.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "Lock.h"
#include "../etc/Camera.h"
#include "../../administer/Maneger.h"
//*****************************************************************************
// 静的変数
//*****************************************************************************
const LPSTR CLock::m_apTextureName[]=
{
	"data/TEXTURE/lock.png",
	"data/TEXTURE/lockon.png"
};
//=============================================================================
// コンストラクタ
//=============================================================================
CLock :: CLock():CformBillBoard(7)
{
	m_nTextureNum=0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CLock :: ~CLock(void)
{
}
//=============================================================================
// CLock生成
//=============================================================================
CLock *CLock::Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CLock *pformBillBoard;

	pformBillBoard = new CLock();
	pformBillBoard->Init(pDevice,pos,rot);

	return pformBillBoard;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CLock :: Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	m_pDevice=pDevice;

	//初期化
	//CformBillBoard::Init(m_pDevice,m_apTextureName[0],pos,rot,50,50);
	CformBillBoard::Init(m_pDevice,m_apTextureName[0],20,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));


	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CLock :: Uninit(void)
{
	//様々なオブジェクトの終了（開放）処理
	CformBillBoard::Uninit();

}
//=============================================================================
// 更新
//=============================================================================
void CLock :: Update(void)
{
	//D3DXMATRIX  mtxWorld;
	//D3DXMATRIX mtxTranslate,mtxParent;

	CCamera *pCamera;
	pCamera = CManager::GetCamera();
	//CEnemyM *pEnemy;
	//pEnemy = CManager::GetEnemy();
	D3DXVECTOR3 setPos =pCamera->GetPointView();

	//mtxParent=pEnemy->GetMtxWorld();

	//D3DXMatrixIdentity(&mtxWorld);
	//D3DXMatrixTranslation(&mtxTranslate,setPos.x,setPos.y,setPos.z);
	//D3DXMatrixMultiply(&mtxWorld,&mtxWorld,&mtxTranslate);
	//D3DXMatrixMultiply(&mtxWorld,&mtxWorld,&mtxParent);

	setPos.y+=50;
	CformBillBoard::SetPos(D3DXVECTOR3(setPos.x,setPos.y,setPos.z));

	CformBillBoard::Update();
}
//=============================================================================
// 描画
//=============================================================================
void CLock :: Draw(void)
{
	CformBillBoard::Draw();
}
/////////////EOF////////////