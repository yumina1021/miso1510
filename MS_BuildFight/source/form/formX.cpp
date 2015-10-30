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

	m_bEnemyFlag=false;

	HRESULT hr;
	LPD3DXBUFFER err;
	LPD3DXBUFFER code;

	//ピクセルシェーダー用に変換
	hr = D3DXCompileShaderFromFile("source/shader/basicPS.hlsl", NULL, NULL, "PS_DIFFUSE", "ps_2_0", 0, &code, &err, &m_shader.psc);

	if (FAILED(hr))
	{
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		err->Release();
		return false;
	}
	//シェーダーの登録
	hr = pDevice->CreatePixelShader((DWORD*)code->GetBufferPointer(), &m_shader.ps);

	if (FAILED(hr))
	{
		MessageBox(NULL, "FAILED", "CreatePixelShader", MB_OK);
		return false;
	}

	//バーテックスシェーダー用に変換1
	hr = D3DXCompileShaderFromFile("source/shader/basicVS.hlsl", NULL, NULL, "VS", "vs_2_0", 0, &code, &err, &m_shader.vsc);
	if (FAILED(hr))
	{
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		err->Release();
		return false;
	}
	//シェーダーの登録
	hr = pDevice->CreateVertexShader((DWORD*)code->GetBufferPointer(), &m_shader.vs);
	if (FAILED(hr))
	{
		MessageBox(NULL, "FAILED", "CreateVertexShader", MB_OK);
		return false;
	}

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
	if(m_bDeathFlag)
	{
		D3DXVECTOR3 pos;

		if(m_bEnemyFlag==false)
		{
			CPlayerM *pPlayer;
			pPlayer=CGame::GetPlayer();
			pos=pPlayer->GetPos();
		}else
		{
			CEnemyM *pEnemy;
			pEnemy=CGame::GetEnemy(0);
			pos=pEnemy->GetPos();
		}
		m_Pos.x=pos.x;
		m_Pos.y=pos.y+100;
		m_Pos.z=pos.z;

		if(m_nDeathCount>1240)
		{
			m_nDeathCount=0;
			this->Uninit();
		}else
		{
			m_nDeathCount++;
		}
	}
	//正規化
	if(m_rotDestModel.y<-(D3DX_PI))
	{
		m_rotDestModel.y =(D3DX_PI);
	}
	if(m_rotDestModel.y>(D3DX_PI))
	{
		m_rotDestModel.y =-(D3DX_PI);
	}

	float fDiffRotY;

	//目的の向きへの差
	fDiffRotY = m_rotDestModel.y - m_Rot.y;

	//謎の回転回避用
	if((fDiffRotY<-(D3DX_PI))||(fDiffRotY>(D3DX_PI)))
	{
		fDiffRotY *= -1;
	}

	//変更値代入
	m_Rot.y += fDiffRotY*0.15f;

	//正規化
	if(m_Rot.y<-(D3DX_PI))
	{
		m_Rot.y =(D3DX_PI);
	}
	if(m_Rot.y>(D3DX_PI))
	{
		m_Rot.y =-(D3DX_PI);
	}

	//高さ
	if(m_Pos.y<0)
	{
		m_Pos.y=0.00001f;
	}
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
	D3DXMATRIX invWorld;

	//ビュー行列
	D3DXVECTOR3 eye(0.0f, 50.0f, -100.0f);
	D3DXVECTOR3 at(0.0f, 20.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	D3DXVECTOR3 lightVec(0.20f, 0.0f, 0.80f);
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
	D3DXVec3TransformCoord(&lightVec, &lightVec, &invWorld);

	D3DXMatrixLookAtLH(&view, &eye, &at, &up);

	D3DXMatrixPerspectiveFovLH(&proj, D3DXToRadian(45), 960.0f / 540.0f, 10.0f, 100000.0f);

	D3DXMATRIX wvp = m_mtxWorld*view*proj;
	D3DXVECTOR3 cameraVec = at - eye;

	D3DXVec3Normalize(&cameraVec, &cameraVec);
	D3DXVec3Normalize(&lightVec, &lightVec);

	// ワールドマトリックスの設定
	m_pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//デフォルトのマテリアル情報取得
	m_pDevice->GetMaterial(&matDef);
	pD3DXMat = (D3DXMATERIAL*)m_pD3DXBuffMatModel->GetBufferPointer();

	m_shader.vsc->SetMatrix(m_pDevice, "world", &m_mtxWorld);
	m_shader.vsc->SetMatrix(m_pDevice, "gWvp", &wvp);

	m_shader.vsc->SetFloatArray(m_pDevice, "LightDir", (float*)&lightVec, 3);
	m_shader.vsc->SetVector(m_pDevice, "LightDiffuse", (D3DXVECTOR4*)&lightDiffuse);
	m_shader.vsc->SetVector(m_pDevice, "LightDiffuse2", (D3DXVECTOR4*)&lightDiffuse2);
	m_shader.vsc->SetVector(m_pDevice, "LightAmbient", (D3DXVECTOR4*)&lightAmbient);
	m_shader.vsc->SetFloatArray(m_pDevice, "CameraVec", (float*)&cameraVec, 3);
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

	//マテリアルの個数分ループ
	for (int nCntMat = 0; nCntMat<(int)m_nNumMatModel; nCntMat++)
	{
		m_shader.vsc->SetVector(m_pDevice, "MatDiffuse", (D3DXVECTOR4*)&pD3DXMat[nCntMat].MatD3D.Diffuse);
		m_shader.vsc->SetVector(m_pDevice, "MatAmbient", (D3DXVECTOR4*)&pD3DXMat[nCntMat].MatD3D.Ambient);
		m_pDevice->SetVertexShader(m_shader.vs);
		m_pDevice->SetPixelShader(m_shader.ps);

		m_pD3DXMeshModel->DrawSubset(nCntMat);			//モデルのパーツを描画
	}

	//マテリアルをもとに戻す！
	m_pDevice->SetMaterial(&matDef);
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