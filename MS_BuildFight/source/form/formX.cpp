//=============================================================================
//
// MS_BuildFight [CformX.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "formX.h"
#include "../module/robot/PlayerM.h"
#include "../module/robot/EnemyM.h"
#include "../administer/scene/Game.h"
#include "../module/etc/Camera.h"
#include "../administer/Maneger.h"
#include "../exten_common.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CformX :: CformX(OBJTYPE objType,int nPriority) : Cform(objType,nPriority)
{
	nTextureNum=0;

	for(int i=0;i<TEXTURE_MAX;i++)
	{
		m_pD3DTex[i]=NULL;
	}

	m_bDeathFlag=false;
	m_nDeathCount=0;

}
//=============================================================================
// デストラクタ
//=============================================================================
CformX :: ~CformX(void)
{
}
//=============================================================================
// CformX生成
//=============================================================================
CformX *CformX::Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot,bool set,bool enemy)
{
	CformX *pformX;

	pformX = new CformX();
	if(enemy==true)
	{
		pformX->Init(pDevice,"data/MODEL/ring.x","data/TEXTURE/toumei6.png");
	}else
	{
		pformX->Init(pDevice,"data/MODEL/ring.x",NULL);
	}
	pformX->SetPos(pos);
	pformX->SetRot(rot);
	pformX->SetViewFlag(set);
	pformX->m_bEnemyFlag=enemy;

	return pformX;
}
//=============================================================================
// CformX生成
//=============================================================================
CformX *CformX::Create(LPDIRECT3DDEVICE9 pDevice, LPSTR pModNameStr, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CformX *pformX;

	pformX = new CformX();
	pformX->Init(pDevice, pModNameStr, NULL);
	pformX->SetPos(pos);
	pformX->SetRot(rot);

	return pformX;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CformX :: Init(LPDIRECT3DDEVICE9 pDevice,LPSTR pFileName,LPSTR pTexName)
{
	//デバイスの取得
	m_pDevice=pDevice;

	//フィールドの初期化
	m_Pos = D3DXVECTOR3(0.0f,0.00001f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//xファイルの設定
	if(FAILED(D3DXLoadMeshFromX(pFileName,
								D3DXMESH_SYSTEMMEM,
								m_pDevice,
								NULL,
								&m_pD3DXBuffMatModel,
								NULL,
								&m_nNumMatModel,
								&m_pD3DXMeshModel)))
	{
		return E_FAIL;
	}

	//頂点要素配列を作る
	D3DVERTEXELEMENT9 vElement[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },		//座標
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },		//法線
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },	//UV
		{ 0, 32, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0 },	//tangent
		{ 0, 44, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 },//バイノーマル
		D3DDECL_END(),	//最後に必ず入れる
	};

	//コンバートする
	LPD3DXMESH pTempMesh = m_pD3DXMeshModel;
	pTempMesh->CloneMesh(D3DXMESH_SYSTEMMEM, &vElement[0], m_pDevice, &m_pD3DXMeshModel);

	//従法線を作成
	D3DXComputeTangentFrame(m_pD3DXMeshModel, 0);

	if (pTempMesh)
	{
		pTempMesh->Release();
		pTempMesh = NULL;
	}

	//テクスチャの設定
	if(pTexName!=NULL)
	{
		D3DXCreateTextureFromFile(m_pDevice,pTexName,&m_pD3DTex[0]);
	}
	else
	{
		m_pD3DTex[0]=NULL;
	}

	// キューブテクスチャの読み込み
	D3DXCreateCubeTextureFromFile(pDevice,					// デバイスへのポインタ
		"data/TEXTURE/sky.dds",		// ファイルの名前
		&m_pD3DTextureCube);		// 読み込むメモリー

	m_bEnemyFlag=false;

	//ピクセルシェーダー用に変換1
	Create_PS("source/shader/basicPS.hlsl", "PS_DIFFUSE", &m_shader.ps, &m_shader.psc, m_pDevice);

	//バーテックスシェーダー用に変換1
	Create_VS("source/shader/basicVS.hlsl", "VS", &m_shader.vs, &m_shader.vsc, m_pDevice);
	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CformX :: Uninit(void)
{
	//様々なオブジェクトの終了（開放）処理
	for(int i=0;i<TEXTURE_MAX;i++)
	{
		if(m_pD3DTex[i]!=NULL)
		{
			m_pD3DTex[i]->Release();
			m_pD3DTex[i]=NULL;
		}
	}

	if (m_pD3DTextureCube != NULL)
	{// マテリアルの開放
		m_pD3DTextureCube->Release();
		m_pD3DTextureCube = NULL;
	}

	if(m_pD3DXMeshModel!=NULL)
	{
		m_pD3DXMeshModel->Release();
		m_pD3DXMeshModel=NULL;
	}
	if(m_pD3DXBuffMatModel!=NULL)
	{
		m_pD3DXBuffMatModel->Release();
		m_pD3DXBuffMatModel=NULL;
	}

	Cform::Release();
}
//=============================================================================
// 更新
//=============================================================================
void CformX :: Update(void)
{

	//正規化
	m_rotDestModel.x = Rotation_Normalizer(m_rotDestModel.x);
	m_rotDestModel.y = Rotation_Normalizer(m_rotDestModel.y);
	m_rotDestModel.z = Rotation_Normalizer(m_rotDestModel.z);

	D3DXVECTOR3 fDiffRot;

	//目的の向きへの差
	fDiffRot = m_rotDestModel - m_Rot;

	//謎の回転回避用
	if ((fDiffRot.x<-(D3DX_PI)) || (fDiffRot.x>(D3DX_PI)))
	{
		fDiffRot.x *= -1;
	}
	if ((fDiffRot.y<-(D3DX_PI)) || (fDiffRot.y>(D3DX_PI)))
	{
		fDiffRot.y *= -1;
	}
	if ((fDiffRot.z<-(D3DX_PI)) || (fDiffRot.z>(D3DX_PI)))
	{
		fDiffRot.z *= -1;
	}

	//変更値代入
	m_Rot += fDiffRot*0.015f;

	//正規化
	m_Rot.x = Rotation_Normalizer(m_Rot.x);
	m_Rot.y = Rotation_Normalizer(m_Rot.y);
	m_Rot.z = Rotation_Normalizer(m_Rot.z);

}
//=============================================================================
// 描画
//=============================================================================
void CformX::Draw(void)
{
	CCamera* pCamera = CManager::GetCamera();

	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	D3DXMATRIX world, view, proj, rot, pos;
	D3DXMATRIX invWorld, invTransWorld;

	//ビュー行列
	D3DXVECTOR3 eye(0.0f, 50.0f, -100.0f);
	D3DXVECTOR3 at(0.0f, 20.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	D3DXVECTOR3 lightVec(m_Pos.x - 0.20f, m_Pos.y - 0.0f, m_Pos.z- 0.80f);
	D3DXCOLOR   lightDiffuse(0.8f, 0.8f, 0.8f, 1.0f);
	D3DXCOLOR   lightDiffuse2(0.8f, 0.4f, 0.4f, 1.0f);
	D3DXCOLOR   lightAmbient(0.5f, 0.5f, 0.5f, 1.0f);

	eye = pCamera->GetPosP();
	at = pCamera->GetPosR();
	up = pCamera->GetVecUp();

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rot.y, m_Rot.x, m_Rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &rot);

	//移動を反映
	D3DXMatrixTranslation(&pos, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &pos);

	D3DXMatrixInverse(&invWorld, NULL, &m_mtxWorld);
	D3DXMatrixInverse(&invTransWorld, NULL, &m_mtxWorld);
	D3DXMatrixTranspose(&invTransWorld, &invTransWorld);

	D3DXVec3TransformCoord(&lightVec, &lightVec, &invWorld);

	D3DXMatrixLookAtLH(&view, &eye, &at, &up);

	D3DXMatrixPerspectiveFovLH(&proj, D3DXToRadian(45), 960.0f / 540.0f, 10.0f, 100000.0f);

	D3DXMATRIX wvp = m_mtxWorld*view*proj;
	D3DXVECTOR3 cameraVec = at - eye;

	D3DXVec3Normalize(&cameraVec, &cameraVec);
	D3DXVec3Normalize(&lightVec, &lightVec);

	// ワールドマトリックスの設定
	//m_pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//デフォルトのマテリアル情報取得
	m_pDevice->GetMaterial(&matDef);
	pD3DXMat = (D3DXMATERIAL*)m_pD3DXBuffMatModel->GetBufferPointer();

	m_shader.vsc->SetMatrix(m_pDevice, "world", &m_mtxWorld);
	m_shader.vsc->SetMatrix(m_pDevice, "gWvp", &wvp);
	m_shader.vsc->SetMatrix(m_pDevice, "worldInvTranspose", &invTransWorld);

	m_shader.psc->SetFloatArray(m_pDevice, "CameraVec", (float*)&cameraVec, 3);
	m_shader.psc->SetFloatArray(m_pDevice, "LightDir", (float*)&lightVec, 3);

	m_shader.vsc->SetVector(m_pDevice, "LightDiffuse", (D3DXVECTOR4*)&lightDiffuse);
	m_shader.vsc->SetVector(m_pDevice, "LightDiffuse2", (D3DXVECTOR4*)&lightDiffuse2);
	m_shader.vsc->SetVector(m_pDevice, "LightAmbient", (D3DXVECTOR4*)&lightAmbient);
	m_shader.vsc->SetFloatArray(m_pDevice, "Pos", (float*)&eye, 3);

	if (m_pD3DTex[0] != NULL)
	{
		unsigned int s0 = m_shader.psc->GetSamplerIndex("texSampler");
		m_pDevice->SetTexture(s0, m_pD3DTex[0]);
	}
	else
	{
		m_pDevice->SetTexture(0, NULL);		//テクスチャは使わない
	}

	unsigned int s0;
	s0 = m_shader.psc->GetSamplerIndex("texSamplerCube");
	m_pDevice->SetTexture(s0, m_pD3DTextureCube);

	//マテリアルの個数分ループ
	for (int nCntMat = 0; nCntMat<(int)m_nNumMatModel; nCntMat++)
	{
		m_shader.vsc->SetVector(m_pDevice, "MatDiffuse", (D3DXVECTOR4*)&pD3DXMat[nCntMat].MatD3D.Diffuse);
		m_shader.psc->SetVector(m_pDevice, "MatDiffuse", (D3DXVECTOR4*)&pD3DXMat[nCntMat].MatD3D.Diffuse);
		m_shader.vsc->SetVector(m_pDevice, "MatAmbient", (D3DXVECTOR4*)&pD3DXMat[nCntMat].MatD3D.Ambient);
		m_pDevice->SetVertexShader(m_shader.vs);
		m_pDevice->SetPixelShader(m_shader.ps);

		m_pD3DXMeshModel->DrawSubset(nCntMat);			//モデルのパーツを描画
	}

	//マテリアルをもとに戻す！
	m_pDevice->SetMaterial(&matDef);

	m_pDevice->SetVertexShader(NULL);
	m_pDevice->SetPixelShader(NULL);

}

void CformX ::SetTexture(LPSTR pTexName,int num)
{
	if(pTexName!=NULL)
	{
		D3DXCreateTextureFromFile(m_pDevice,pTexName,&m_pD3DTex[num]);
	}else
	{
		m_pD3DTex[num]=NULL;
	}
}
/////////////EOF////////////