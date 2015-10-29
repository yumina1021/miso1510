//=============================================================================
//
// MS_BuildFight [Field.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#include "Field.h"
#include "meshfielddata.h"
#include "../../administer/FrustumCulling.h"
#include "../etc/Camera.h"
#include "../../administer/Maneger.h"
#include "../../administer/scene/Game.h"
#include "../robot/PlayerM.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的変数
//*****************************************************************************
const char *CMeshField::m_apTextureName[]=
{
	"data/TEXTURE/field000.jpg",
	"data/TEXTURE/field001.jpg",
	"data/TEXTURE/field002.jpg",
	"data/TEXTURE/field003.jpg",
	"data/TEXTURE/field004.jpg",
	"data/TEXTURE/field005.jpg",
	"data/TEXTURE/field006.jpg"
};

//=============================================================================
// コンストラクタ
//=============================================================================
CMeshField::CMeshField(int nPriority) : Cform3D(nPriority)
{
	m_pD3DTex = NULL;
	m_pD3DVtxBuff = NULL;
	m_pD3DIndexBuff = NULL;
	m_bTransParent = false;

	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_pBuffNormal = NULL;

	m_nNumBlockX = 0;
	m_nNumBlockZ = 0;
	m_nNumVertex = 0;
	m_nNumVertexIndex = 0;
	m_nNumPolygon = 0;
	m_fSizeBlockX = 0.0f;
	m_fSizeBlockZ = 0.0f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMeshField::~CMeshField()
{
}
//=============================================================================
// CMeshField生成
//=============================================================================
CMeshField *CMeshField::Create(LPDIRECT3DDEVICE9 pDevice,int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot,
									int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ)
{
	CMeshField *pMeshField;

	pMeshField = new CMeshField;
	pMeshField->Init(pDevice,nType, pos, rot, nNumBlockX, nNumBlockZ, fSizeBlockX, fSizeBlockZ);

	return pMeshField;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CMeshField::Init(LPDIRECT3DDEVICE9 pDevice,int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot,
								int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ)
{
	m_pDevice=pDevice;

	// ブロック数の設定
	m_nNumBlockX = nNumBlockX;
	m_nNumBlockZ = nNumBlockZ;

	// 頂点数の設定
	m_nNumVertex = (nNumBlockX + 1) * (nNumBlockZ + 1);

	// インデックス数の設定
	m_nNumVertexIndex = (nNumBlockX + 1) * 2 * nNumBlockZ + (nNumBlockZ - 1) * 2;

	// ポリゴン数の設定
	m_nNumPolygon = nNumBlockX * nNumBlockZ * 2 + (nNumBlockZ - 1) * 4;

	// ブロックサイズの設定
	m_fSizeBlockX = fSizeBlockX;
	m_fSizeBlockZ = fSizeBlockZ;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(m_pDevice,m_apTextureName[nType],&m_pD3DTex);

	//フィールドの初期化
	m_Pos = pos;
	m_Rot = rot;
	m_Scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	// オブジェクトの頂点バッファを生成
	if(FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*m_nNumVertex,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuff,
											NULL)))
	{
		return E_FAIL;
	}

	// オブジェクトのインデックスバッファを生成
	if(FAILED(m_pDevice->CreateIndexBuffer(sizeof(WORD)*m_nNumVertexIndex,
											D3DUSAGE_WRITEONLY,
											D3DFMT_INDEX16,
											D3DPOOL_MANAGED,
											&m_pD3DIndexBuff,
											NULL)))
	{
		return E_FAIL;
	}

	// 法線算出用バッファ確保
	m_pBuffNormal = new D3DXVECTOR3 [(m_nNumBlockX * 2) * m_nNumBlockZ];

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;
		const float texSizeX = 1.0f;
		const float texSizeZ = 1.0f;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntVtxZ = 0; nCntVtxZ < (m_nNumBlockZ + 1); nCntVtxZ++)
		{
			for(int nCntVtxX = 0; nCntVtxX < (m_nNumBlockX + 1); nCntVtxX++)
			{
				// 頂点座標の設定
				pVtx[nCntVtxZ * (m_nNumBlockX + 1) + nCntVtxX].vtx.x = -(m_nNumBlockX / 2.0f) * m_fSizeBlockX + nCntVtxX * m_fSizeBlockX;
				pVtx[nCntVtxZ * (m_nNumBlockX + 1) + nCntVtxX].vtx.z = (m_nNumBlockZ / 2.0f) * m_fSizeBlockZ - nCntVtxZ * m_fSizeBlockZ;

				pVtx[nCntVtxZ * (m_nNumBlockX + 1) + nCntVtxX].vtx.y = HIGHT_MAP[nCntVtxZ * (m_nNumBlockX + 1) + nCntVtxX];

				// 反射光の設定
				pVtx[nCntVtxZ * (m_nNumBlockX + 1) + nCntVtxX].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// テクスチャ座標の設定
				pVtx[nCntVtxZ * (m_nNumBlockX + 1) + nCntVtxX].tex.x = texSizeX * nCntVtxX;
				pVtx[nCntVtxZ * (m_nNumBlockX + 1) + nCntVtxX].tex.y = texSizeZ * nCntVtxZ;
			}
		}

		// 頂点データをアンロックする
		m_pD3DVtxBuff->Unlock();
	}

	{// 法線の算出
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		D3DXVECTOR3 *pNor = m_pBuffNormal;
		for(int nCntVtxZ = 0; nCntVtxZ < m_nNumBlockZ; nCntVtxZ++)
		{
			for(int nCntVtxX = 0; nCntVtxX < m_nNumBlockX; nCntVtxX++)
			{
				// 法線の設定
				D3DXVECTOR3 v0,v1,v2;
				D3DXVECTOR3 normal;
				D3DXVECTOR3 *pVtx0,*pVtx1,*pVtx2;

				pVtx0 = &pVtx[nCntVtxZ * (m_nNumBlockX + 1) + nCntVtxX].vtx;
				pVtx1 = &pVtx[(nCntVtxZ + 1) * (m_nNumBlockX + 1) + nCntVtxX].vtx;
				pVtx2 = &pVtx[(nCntVtxZ + 1) * (m_nNumBlockX + 1) + nCntVtxX + 1].vtx;

				v0.x = pVtx1->x - pVtx2->x;
				v0.y = pVtx1->y - pVtx2->y;
				v0.z = pVtx1->z - pVtx2->z;
				v1.x = pVtx0->x - pVtx2->x;
				v1.y = pVtx0->y - pVtx2->y;
				v1.z = pVtx0->z - pVtx2->z;

				D3DXVec3Cross(&v2, &v0, &v1);
				D3DXVec3Normalize(&normal, &v2);

				*pNor = normal;
				pNor++;

				pVtx0 = &pVtx[nCntVtxZ * (m_nNumBlockX + 1) + nCntVtxX].vtx;
				pVtx1 = &pVtx[(nCntVtxZ + 1) * (m_nNumBlockX + 1) + nCntVtxX + 1].vtx;
				pVtx2 = &pVtx[nCntVtxZ * (m_nNumBlockX + 1) + nCntVtxX + 1].vtx;

				v0.x = pVtx1->x - pVtx2->x;
				v0.y = pVtx1->y - pVtx2->y;
				v0.z = pVtx1->z - pVtx2->z;
				v1.x = pVtx0->x - pVtx2->x;
				v1.y = pVtx0->y - pVtx2->y;
				v1.z = pVtx0->z - pVtx2->z;
				D3DXVec3Cross(&v2, &v0, &v1);
				D3DXVec3Normalize(&normal, &v2);

				*pNor = normal;
				pNor++;
			}
		}

		// 頂点データをアンロックする
		m_pD3DVtxBuff->Unlock();
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		D3DXVECTOR3 *pNor = m_pBuffNormal;
		for(int nCntVtxZ = 0; nCntVtxZ < (m_nNumBlockZ + 1); nCntVtxZ++)
		{
			for(int nCntVtxX = 0; nCntVtxX < (m_nNumBlockX + 1); nCntVtxX++)
			{
				// 法線の設定
				D3DXVECTOR3 normal;
				D3DXVECTOR3 norAvg0, norAvg1;

				if(nCntVtxZ == 0)
				{
					if(nCntVtxX == 0)
					{
						normal = (pNor[0] + pNor[1]) / 2;
					}
					else if(nCntVtxX == m_nNumBlockX)
					{
						normal = pNor[m_nNumBlockX * 2 - 1];
					}
					else
					{
						norAvg0 = (pNor[nCntVtxX * 2] + pNor[nCntVtxX * 2 + 1]) / 2;
						normal = (pNor[nCntVtxX * 2 - 1] + norAvg0) / 2;
					}
				}
				else if(nCntVtxZ == m_nNumBlockZ)
				{
					if(nCntVtxX == 0)
					{
						normal = pNor[(m_nNumBlockZ - 1) * m_nNumBlockX * 2];
					}
					else if(nCntVtxX == m_nNumBlockX)
					{
						normal = (pNor[m_nNumBlockZ * m_nNumBlockX * 2 - 2] + pNor[m_nNumBlockZ * m_nNumBlockX * 2 - 1]) / 2;
					}
					else
					{
						norAvg0 = (pNor[(m_nNumBlockZ - 1) * m_nNumBlockX * 2 + nCntVtxX * 2 - 2] + pNor[(m_nNumBlockZ - 1) * m_nNumBlockX * 2 + nCntVtxX * 2 - 1]) / 2;
						normal = (norAvg0 + pNor[(m_nNumBlockZ - 1) * m_nNumBlockX * 2 + nCntVtxX * 2]) / 2;
					}
				}
				else
				{
					if(nCntVtxX == 0)
					{
						norAvg0 = (pNor[nCntVtxZ * m_nNumBlockX * 2] + pNor[nCntVtxZ * m_nNumBlockX * 2 + 1]) / 2;
						normal = (pNor[(nCntVtxZ - 1) * m_nNumBlockX * 2] + norAvg0) / 2;
					}
					else if(nCntVtxX == m_nNumBlockX)
					{
						norAvg0 = (pNor[(nCntVtxZ - 1) * m_nNumBlockX * 2 + nCntVtxX * 2 - 1] + pNor[(nCntVtxZ - 1) * m_nNumBlockX * 2 + nCntVtxX * 2 - 2]) / 2;
						normal = (norAvg0 + pNor[nCntVtxZ * m_nNumBlockX * 2 + nCntVtxX * 2 - 1]) / 2;
					}
					else
					{
						int nIdx0 = (nCntVtxZ - 1) * m_nNumBlockX * 2 + nCntVtxX * 2 - 2;
						int nIdx1 = (nCntVtxZ - 1) * m_nNumBlockX * 2 + nCntVtxX * 2 - 1;
						int nIdx2 = (nCntVtxZ - 1) * m_nNumBlockX * 2 + nCntVtxX * 2;
						int nIdx3 = nCntVtxZ * m_nNumBlockX * 2 + nCntVtxX * 2 - 1;
						int nIdx4 = nCntVtxZ * m_nNumBlockX * 2 + nCntVtxX * 2;
						int nIdx5 = nCntVtxZ * m_nNumBlockX * 2 + nCntVtxX * 2 + 1;

						norAvg0 = (pNor[nIdx0] + pNor[nIdx1]) / 2;
						norAvg1 = (pNor[nIdx4] + pNor[nIdx5]) / 2;
						normal = (norAvg0 + pNor[nIdx2] + pNor[nIdx3] + norAvg1) / 4;
					}
				}

				D3DXVec3Normalize(&normal, &normal);
				pVtx[nCntVtxZ * (m_nNumBlockX + 1) + nCntVtxX].nor = normal;
			}
		}

		// 頂点データをアンロックする
		m_pD3DVtxBuff->Unlock();
	}

	{//インデックスバッファの中身を埋める
		WORD *pIdx;

		// インデックスデータの範囲をロックし、頂点バッファへのポインタを取得
		m_pD3DIndexBuff->Lock(0, 0, (void**)&pIdx, 0);

		int nCntIdx = 0;
		for(int nCntVtxZ = 0; nCntVtxZ < m_nNumBlockZ; nCntVtxZ++)
		{
			if(nCntVtxZ > 0)
			{// 縮退ポリゴンのためのダブりの設定
				pIdx[nCntIdx] = (nCntVtxZ + 1) * (m_nNumBlockX + 1) + 0;
				nCntIdx++;
			}

			for(int nCntVtxX = 0; nCntVtxX < (m_nNumBlockX + 1); nCntVtxX++)
			{
				pIdx[nCntIdx] = (nCntVtxZ + 1) * (m_nNumBlockX + 1) + nCntVtxX;
				nCntIdx++;
				pIdx[nCntIdx] = nCntVtxZ * (m_nNumBlockX + 1) + nCntVtxX;
				nCntIdx++;
			}

			if(nCntVtxZ < (m_nNumBlockZ - 1))
			{// 縮退ポリゴンのためのダブりの設定
				pIdx[nCntIdx] = nCntVtxZ * (m_nNumBlockX + 1) + m_nNumBlockX;
				nCntIdx++;
			}
		}

		// インデックスデータをアンロックする
		m_pD3DIndexBuff->Unlock();
	}

	HRESULT hr;
	LPD3DXBUFFER err;
	LPD3DXBUFFER code;

	//ピクセルシェーダー用に変換
	hr = D3DXCompileShaderFromFile("source/shader/basicPS.hlsl", NULL, NULL, "PS_SHADOW", "ps_2_0", 0, &code, &err, &_psc);

	if (FAILED(hr))
	{
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		err->Release();
		return false;
	}
	//シェーダーの登録
	hr = pDevice->CreatePixelShader((DWORD*)code->GetBufferPointer(), &_ps);

	if (FAILED(hr))
	{
		MessageBox(NULL, "FAILED", "CreatePixelShader", MB_OK);
		return false;
	}

	//バーテックスシェーダー用に変換1
	hr = D3DXCompileShaderFromFile("source/shader/basicVS.hlsl", NULL, NULL, "VS_SHADOW", "vs_2_0", 0, &code, &err, &_vsc[0]);
	if (FAILED(hr))
	{
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		err->Release();
		return false;
	}
	//シェーダーの登録
	hr = pDevice->CreateVertexShader((DWORD*)code->GetBufferPointer(), &_vs[0]);
	if (FAILED(hr))
	{
		MessageBox(NULL, "FAILED", "CreateVertexShader", MB_OK);
		return false;
	}

	//バーテックスシェーダー用に変換1
	hr = D3DXCompileShaderFromFile("source/shader/basicVS.hlsl", NULL, NULL, "VS", "vs_2_0", 0, &code, &err, &_vsc[1]);
	if (FAILED(hr))
	{
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		err->Release();
		return false;
	}
	//シェーダーの登録
	hr = pDevice->CreateVertexShader((DWORD*)code->GetBufferPointer(), &_vs[1]);
	if (FAILED(hr))
	{
		MessageBox(NULL, "FAILED", "CreateVertexShader", MB_OK);
		return false;
	}

	// マテリアルの設定
	m_material.Ambient = D3DXCOLOR(0.25f, 0.25f, 0.25f, 1.0f);
	m_material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_material.Emissive = D3DXCOLOR(0, 0, 0, 0);
	m_material.Specular = D3DXCOLOR(0, 0, 0, 0);
	m_material.Power = 2.0f;

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CMeshField::Uninit(void)
{
	//様々なオブジェクトの終了（開放）処理

	if(m_pD3DTex!=NULL)
	{
		m_pD3DTex->Release();
		m_pD3DTex = NULL;
	}
	if(m_pD3DVtxBuff!=NULL)
	{
		m_pD3DVtxBuff->Release();
		m_pD3DVtxBuff = NULL;
	}
	if(m_pD3DIndexBuff!=NULL)
	{
		m_pD3DIndexBuff->Release();
		m_pD3DIndexBuff = NULL;
	}
	if(m_pBuffNormal!=NULL)
	{
		delete[] m_pBuffNormal;
		m_pBuffNormal = NULL;
	}

	Cform::Release();
}

//=============================================================================
// 更新
//=============================================================================
void CMeshField::Update()
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshField::Draw(LPDIRECT3DTEXTURE9 pTexture)
{
	D3DXMATRIX  mtxWorld;
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	SetMtxView(CManager::GetCamera()->GetMtxView());

	// 視錐台　作成
	FRUSTUM	sFrustum;

	//  セットアップする関数
	SetupFOVClipPlanes(VIEW_ANGLE,VIEW_ASPECT,VIEW_NEAR_Z,VIEW_FAR_Z,sFrustum);

	//頂点バッファの中身を埋める
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for(int nCntVtxZ = 0; nCntVtxZ < (m_nNumBlockZ + 1); nCntVtxZ++)
	{
		for(int nCntVtxX = 0; nCntVtxX < (m_nNumBlockX + 1); nCntVtxX++)
		{
			VECTOR3 pos;

			// 頂点座標の設定
			pos.x=pVtx[nCntVtxZ * (m_nNumBlockX + 1) + nCntVtxX].vtx.x;
			pos.z=pVtx[nCntVtxZ * (m_nNumBlockX + 1) + nCntVtxX].vtx.z;
			pos.y=pVtx[nCntVtxZ * (m_nNumBlockX + 1) + nCntVtxX].vtx.y;

			MATRIX4x4 matrix;

			matrix._11 = m_MtxView._11;
			matrix._12 = m_MtxView._12;
			matrix._13 = m_MtxView._13;
			matrix._14 = m_MtxView._14;
			matrix._21 = m_MtxView._21;
			matrix._22 = m_MtxView._22;
			matrix._23 = m_MtxView._23;
			matrix._24 = m_MtxView._24;
			matrix._31 = m_MtxView._31;
			matrix._32 = m_MtxView._32;
			matrix._33 = m_MtxView._33;
			matrix._34 = m_MtxView._34;
			matrix._41 = m_MtxView._41;
			matrix._42 = m_MtxView._42;
			matrix._43 = m_MtxView._43;
			matrix._44 = m_MtxView._44;

			// ???
			if(!MeshFOVCheck(&pos,8,sFrustum,matrix))
			//if( 判定用関数 )  // 視錐台から、外れていたら
			{
				continue;		// 描画しないで、次のモデルへ
			}
		}

	}

	// 頂点データをアンロックする
	m_pD3DVtxBuff->Unlock();

	LPDIRECT3DDEVICE9 pDevice = CManager::GetDevice();

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);

	if (m_bTransParent)
	{
		pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);				// Zバッファを使用しない
	}
	else
	{
		pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);				// Zバッファを使用する
	}

	//ワールド行列変数
	D3DXMATRIX world, view, proj, rot, pos, mtxParent;
	D3DXMATRIX invWorld;

	//ビュー行列
	D3DXVECTOR3 eye(0.0f, 50.0f, -100.0f);
	D3DXVECTOR3 at(0.0f, 20.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	D3DXVECTOR3 lightVec(0.20f, 0.0f, 0.80f);
	D3DXCOLOR   lightDiffuse(0.8f, 0.8f, 0.8f, 1.0f);
	D3DXCOLOR   lightDiffuse2(0.8f, 0.4f, 0.4f, 1.0f);
	D3DXCOLOR   lightAmbient(0.5f, 0.5f, 0.5f, 1.0f);

	CCamera *pCamera;
	// カメラを取得
	pCamera = CManager::GetCamera();

	eye = pCamera->GetPosP();
	at = pCamera->GetPosR();
	up = pCamera->GetVecUp();

	pDevice->GetTransform(D3DTS_WORLD, &mtxParent);

	//ワールド行列
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rot.y, m_Rot.x, m_Rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &rot);

	D3DXMatrixTranslation(&pos, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &pos);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	D3DXMatrixInverse(&invWorld, NULL, &m_mtxWorld);
	D3DXVec3TransformCoord(&lightVec, &lightVec, &invWorld);

	D3DXMatrixLookAtLH(&view, &eye, &at, &up);

	D3DXMatrixPerspectiveFovLH(&proj, D3DXToRadian(45), 960.0f / 540.0f, 10.0f, 100000.0f);

	D3DXMATRIX wvp = m_mtxWorld*view*proj;
	D3DXVECTOR3 cameraVec = at - eye;

	D3DXVec3Normalize(&cameraVec, &cameraVec);
	D3DXVec3Normalize(&lightVec, &lightVec);

	D3DXVECTOR3 playerPos = CGame::GetPlayer()->GetPos();

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをレンダリングパイプラインに設定
	pDevice->SetStreamSource(0, m_pD3DVtxBuff, 0, sizeof(VERTEX_3D));

	// インデックスバッファをレンダリングパイプラインに設定
	pDevice->SetIndices(m_pD3DIndexBuff);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	if (pTexture == NULL)
	{

		pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_XRGB(255, 255, 255));

		_vsc[1]->SetMatrix(pDevice, "world", &m_mtxWorld);
		_vsc[1]->SetMatrix(pDevice, "gWvp", &wvp);

		_vsc[1]->SetFloatArray(pDevice, "LightDir", (float*)&lightVec, 3);
		_vsc[1]->SetVector(pDevice, "LightDiffuse", (D3DXVECTOR4*)&lightDiffuse);
		_vsc[1]->SetVector(pDevice, "LightDiffuse2", (D3DXVECTOR4*)&lightDiffuse2);
		_vsc[1]->SetVector(pDevice, "LightAmbient", (D3DXVECTOR4*)&lightAmbient);
		_vsc[1]->SetFloatArray(pDevice, "CameraVec", (float*)&cameraVec, 3);
		_vsc[1]->SetFloatArray(pDevice, "PlayerPos", (float*)&playerPos, 3);
		_vsc[1]->SetFloatArray(pDevice, "Pos", (float*)&eye, 3);

		// テクスチャの設定
		pDevice->SetTexture(0, m_pD3DTex);

		unsigned int s0 = _psc->GetSamplerIndex("texSampler");
		pDevice->SetTexture(s0, m_pD3DTex);
		pDevice->SetVertexShader(_vs[1]);
	}
	else
	{
		_vsc[0]->SetMatrix(pDevice, "world", &m_mtxWorld);
		_vsc[0]->SetMatrix(pDevice, "gWvp", &wvp);

		_vsc[0]->SetFloatArray(pDevice, "LightDir", (float*)&lightVec, 3);
		_vsc[0]->SetVector(pDevice, "LightDiffuse", (D3DXVECTOR4*)&lightDiffuse);
		_vsc[0]->SetVector(pDevice, "LightDiffuse2", (D3DXVECTOR4*)&lightDiffuse2);
		_vsc[0]->SetVector(pDevice, "LightAmbient", (D3DXVECTOR4*)&lightAmbient);
		_vsc[0]->SetFloatArray(pDevice, "CameraVec", (float*)&cameraVec, 3);
		_vsc[0]->SetFloatArray(pDevice, "PlayerPos", (float*)&playerPos, 3);
		_vsc[0]->SetFloatArray(pDevice, "Pos", (float*)&m_Pos, 3);

		// テクスチャの設定
		pDevice->SetTexture(0, pTexture);

		unsigned int s0 = _psc->GetSamplerIndex("shadowSampler");
		pDevice->SetTexture(s0, pTexture);
		pDevice->SetVertexShader(_vs[0]);
	}
	pDevice->SetPixelShader(_ps);

	// マテリアルの設定
	pDevice->SetMaterial(&m_material);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVertex, 0, m_nNumPolygon);

	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);					// Zバッファを使用する
}

//=============================================================================
// 色設定
//=============================================================================
void CMeshField::SetColor(D3DXCOLOR col)
{
}

//=============================================================================
// 地面の高さを取得
//=============================================================================
float CMeshField::GetHeight(D3DXVECTOR3 pos, D3DXVECTOR3 *pNormal)
{
	float fHeight = 0.0f;
	VERTEX_3D *pVtx;
	bool bFinish = false;
	VERTEX_3D *pVtx0, *pVtx1, *pVtx2;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for(int nCntVtxZ = 0; nCntVtxZ < m_nNumBlockZ; nCntVtxZ++)
	{
		for(int nCntVtxX = 0; nCntVtxX < m_nNumBlockX; nCntVtxX++)
		{
			pVtx0 = &pVtx[(nCntVtxZ + 1) * (m_nNumBlockX + 1) + nCntVtxX];
			pVtx1 = &pVtx[nCntVtxZ * (m_nNumBlockX + 1) + nCntVtxX];
			pVtx2 = &pVtx[(nCntVtxZ + 1) * (m_nNumBlockX + 1) + nCntVtxX + 1];

			if((pVtx1->vtx.z - pVtx0->vtx.z) * (pos.x - pVtx0->vtx.x)
				- (pVtx1->vtx.x - pVtx0->vtx.x) * (pos.z - pVtx0->vtx.z) >= 0.0f)
			{
				if((pVtx2->vtx.z - pVtx1->vtx.z) * (pos.x - pVtx1->vtx.x)
					- (pVtx2->vtx.x - pVtx1->vtx.x) * (pos.z - pVtx1->vtx.z) >= 0.0f)
				{
					if((pVtx0->vtx.z - pVtx2->vtx.z) * (pos.x - pVtx2->vtx.x)
						- (pVtx0->vtx.x - pVtx2->vtx.x) * (pos.z - pVtx2->vtx.z) >= 0.0f)
					{
						// ポリゴン上の高さを取得
						fHeight = GetHeightPolygon((D3DXVECTOR3*)&pVtx0->vtx, (D3DXVECTOR3*)&pVtx1->vtx, (D3DXVECTOR3*)&pVtx2->vtx, pos, pNormal);

						bFinish = true;
						break;
					}
				}
			}

			pVtx0 = &pVtx[nCntVtxZ * (m_nNumBlockX + 1) + nCntVtxX];
			pVtx1 = &pVtx[nCntVtxZ * (m_nNumBlockX + 1) + nCntVtxX + 1];
			pVtx2 = &pVtx[(nCntVtxZ + 1) * (m_nNumBlockX + 1) + nCntVtxX + 1];

			if((pVtx1->vtx.z - pVtx0->vtx.z) * (pos.x - pVtx0->vtx.x)
				- (pVtx1->vtx.x - pVtx0->vtx.x) * (pos.z - pVtx0->vtx.z) >= 0.0f)
			{
				if((pVtx2->vtx.z - pVtx1->vtx.z) * (pos.x - pVtx1->vtx.x)
					- (pVtx2->vtx.x - pVtx1->vtx.x) * (pos.z - pVtx1->vtx.z) >= 0.0f)
				{
					if((pVtx0->vtx.z - pVtx2->vtx.z) * (pos.x - pVtx2->vtx.x)
						- (pVtx0->vtx.x - pVtx2->vtx.x) * (pos.z - pVtx2->vtx.z) >= 0.0f)
					{
						// ポリゴン上の高さを取得
						fHeight = GetHeightPolygon((D3DXVECTOR3*)&pVtx0->vtx, (D3DXVECTOR3*)&pVtx1->vtx, (D3DXVECTOR3*)&pVtx2->vtx, pos, pNormal);

						bFinish = true;
						break;
					}
				}
			}
		}

		if(bFinish == true)
		{
			break;
		}
	}

	// 頂点データをアンロックする
	m_pD3DVtxBuff->Unlock();

	if(bFinish == true)
	{
//		CDebugProc::Print("地面の高さ      :%f\n", fHeight);
	}

	return fHeight;
}

//=============================================================================
// 該当するポリゴン上での高さを算出
//=============================================================================
float CMeshField::GetHeightPolygon(D3DXVECTOR3 *pVtx0, D3DXVECTOR3 *pVtx1, D3DXVECTOR3 *pVtx2,
															D3DXVECTOR3 pos, D3DXVECTOR3 *pNormal)
{
	D3DXVECTOR3 vec0, vec1;
	D3DXVECTOR3 normal;
	float fHeight;

	vec0 = *pVtx1 - *pVtx0;
	vec1 = *pVtx2 - *pVtx0;

	// ２つの線分の外積から法線を求める
	D3DXVec3Cross(&normal, &vec0, &vec1);

	// 正規化
	D3DXVec3Normalize(&normal, &normal);

	if(normal.y == 0.0f)
	{// 法線が水平なら無視
		return 0.0f;
	}

	// 高さを算出 [("任意の頂点"から"目的の位置"へのベクトル)・法線ベクトル ＝ ０]
	fHeight = pVtx0->y - ((normal.x * (pos.x - pVtx0->x) + normal.z * (pos.z - pVtx0->z)) / normal.y);

	if(pNormal)
	{
		*pNormal = normal;
	}

	return fHeight;
}

/////////////EOF////////////
