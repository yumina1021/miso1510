//=============================================================================
//
// MS_BuildFight [Cform3D.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "form3D.h"
#include "../module/field/meshfielddata.h"
//=============================================================================
// コンストラクタ
//=============================================================================
Cform3D :: Cform3D(int nPriority) : Cform(OBJTYPE_3D,nPriority)
{
}
//=============================================================================
// デストラクタ
//=============================================================================
Cform3D :: ~Cform3D(void)
{
}
//=============================================================================
// Cform3D生成
//=============================================================================
Cform3D *Cform3D::Create(LPDIRECT3DDEVICE9 pDevice,LPSTR pTexName,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	Cform3D *pform3D;

	pform3D = new Cform3D();
	pform3D->Init(pDevice,pTexName);
	pform3D->SetPos(pos);

	return pform3D;
}
//=============================================================================
// Cform3D生成
//=============================================================================
Cform3D *Cform3D::Create(LPDIRECT3DDEVICE9 pDevice, LPSTR pTexName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float width, float height)
{
	Cform3D *pform3D;

	pform3D = new Cform3D();
	pform3D->Init(pDevice, pTexName, width, height);
	pform3D->SetPos(pos);
	pform3D->SetRot(rot);

	return pform3D;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT Cform3D :: Init(LPDIRECT3DDEVICE9 pDevice,LPSTR pTexName)
{
	m_pDevice=pDevice;

	int nNumBlockX=1;
	int nNumBlockZ=1;


	//テクスチャの設定
	D3DXCreateTextureFromFile(m_pDevice,pTexName,&m_pD3DTex);

	//フィールドの初期化
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	m_fLength = sqrtf((float)(((TEXTURE_SIZE_X / 2) * (TEXTURE_SIZE_X / 2)) + ((TEXTURE_SIZE_Y / 2) * (TEXTURE_SIZE_Y / 2))));
	m_fAngle = atan2f((TEXTURE_SIZE_X / 2), (TEXTURE_SIZE_Y / 2));

	//頂点情報の設定
	if(FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)* NUM_VERTEX,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuff,
											NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].vtx.x = -sinf(m_fAngle) * m_fLength;
	pVtx[0].vtx.y = 0.0f;
	pVtx[0].vtx.z = -cosf(m_fAngle) * m_fLength;

	pVtx[1].vtx.x = -sinf(m_fAngle) * m_fLength;
	pVtx[1].vtx.y = 0.0f;
	pVtx[1].vtx.z = cosf(m_fAngle) * m_fLength;

	pVtx[2].vtx.x = sinf(m_fAngle) * m_fLength;
	pVtx[2].vtx.y = 0.0f;
	pVtx[2].vtx.z = -cosf(m_fAngle) * m_fLength;

	pVtx[3].vtx.x = sinf(m_fAngle) * m_fLength;
	pVtx[3].vtx.y = 0.0f;
	pVtx[3].vtx.z = cosf(m_fAngle) * m_fLength;

	// 頂点座標の設定
	D3DXVECTOR3 vec0, vec1;
	D3DXVECTOR3 nor0, nor1;

	vec0 = pVtx[1].vtx - pVtx[0].vtx;
	vec1 = pVtx[2].vtx - pVtx[1].vtx;

	D3DXVec3Cross(&nor0, &vec0, &vec1);

	D3DXVec3Normalize(&nor0, &nor0);

	vec0 = pVtx[2].vtx - pVtx[1].vtx;
	vec1 = pVtx[2].vtx - pVtx[3].vtx;

	D3DXVec3Cross(&nor1, &vec0, &vec1);

	D3DXVec3Normalize(&nor1, &nor1);

	pVtx[0].nor = nor0;
	pVtx[1].nor.x = (nor0.x + nor1.x) / 2;
	pVtx[1].nor.y = (nor0.y + nor1.y) / 2;
	pVtx[1].nor.z = (nor0.z + nor1.z) / 2;
	pVtx[2].nor.x = (nor0.x + nor1.x) / 2;
	pVtx[2].nor.y = (nor0.y + nor1.y) / 2;
	pVtx[2].nor.z = (nor0.z + nor1.z) / 2;
	pVtx[3].nor = nor1;

	// 反射光の設定
	pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// 頂点データをアンロックする
	m_pD3DVtxBuff->Unlock();

	return S_OK;
}


//=============================================================================
// 初期化
//=============================================================================
HRESULT Cform3D::Init(LPDIRECT3DDEVICE9 pDevice, LPSTR pTexName, float fTexSizeX, float fTexSizeY)
{
	m_pDevice = pDevice;

	int nNumBlockX = 1;
	int nNumBlockZ = 1;


	//テクスチャの設定
	D3DXCreateTextureFromFile(m_pDevice, pTexName, &m_pD3DTex);

	//フィールドの初期化
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_fLength = sqrtf((float)(((fTexSizeX / 2) * (fTexSizeX / 2)) + ((fTexSizeY / 2) * (fTexSizeY / 2))));
	m_fAngle = atan2f((fTexSizeX / 2), (fTexSizeY / 2));

	//頂点情報の設定
	if (FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)* NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pD3DVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].vtx.x = -sinf(m_fAngle) * m_fLength;
	pVtx[0].vtx.y = 0.0f;
	pVtx[0].vtx.z = cosf(m_fAngle) * m_fLength;

	pVtx[1].vtx.x = sinf(m_fAngle) * m_fLength;
	pVtx[1].vtx.y = 0.0f;
	pVtx[1].vtx.z = cosf(m_fAngle) * m_fLength;

	pVtx[2].vtx.x = -sinf(m_fAngle) * m_fLength;
	pVtx[2].vtx.y = 0.0f;
	pVtx[2].vtx.z = -cosf(m_fAngle) * m_fLength;

	pVtx[3].vtx.x = sinf(m_fAngle) * m_fLength;
	pVtx[3].vtx.y = 0.0f;
	pVtx[3].vtx.z = -cosf(m_fAngle) * m_fLength;

	pVtx[0].nor.x = 0.0f;
	pVtx[0].nor.y = 1.0f;
	pVtx[0].nor.z = 0.0f;
	pVtx[1].nor.x = 0.0f;
	pVtx[1].nor.y = 1.0f;
	pVtx[1].nor.z = 0.0f;
	pVtx[2].nor.x = 0.0f;
	pVtx[2].nor.y = 1.0f;
	pVtx[2].nor.z = 0.0f;
	pVtx[3].nor.x = 0.0f;
	pVtx[3].nor.y = 1.0f;
	pVtx[3].nor.z = 0.0f;

	// 反射光の設定
	pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// 頂点データをアンロックする
	m_pD3DVtxBuff->Unlock();

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void Cform3D :: Uninit(void)
{
	//様々なオブジェクトの終了（開放）処理

	if(m_pD3DTex!=NULL)
	{
		m_pD3DTex->Release();
		m_pD3DTex=NULL;
	}
	if(m_pD3DVtxBuff!=NULL)
	{
		m_pD3DVtxBuff->Release();
		m_pD3DVtxBuff=NULL;
	}

	Cform::Release();
}
//=============================================================================
// 更新
//=============================================================================
void Cform3D :: Update(void)
{
}
//=============================================================================
// 描画
//=============================================================================
void Cform3D :: Draw(void)
{
	D3DXMATRIX  mtxWorld;
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	//マトリックスの設定
	D3DXMatrixIdentity(&mtxWorld);
	D3DXMatrixScaling(&mtxScl,m_Scl.x,m_Scl.y,m_Scl.z);
	D3DXMatrixMultiply(&mtxWorld,&mtxWorld,&mtxScl);
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_Rot.y,m_Rot.x,m_Rot.z);
	D3DXMatrixMultiply(&mtxWorld,&mtxWorld,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);
	D3DXMatrixMultiply(&mtxWorld,&mtxWorld,&mtxTranslate);
	m_pDevice->SetTransform(D3DTS_WORLD,&mtxWorld);

	//頂点バッファをデータストリームにバインド
	m_pDevice->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	m_pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	m_pDevice->SetTexture(0,m_pD3DTex);

	//ポリゴンの描画
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);


}
//=============================================================================
// カラー設定
//=============================================================================
void Cform3D::SetDiffuse(float r, float g, float b, float a)
{
	VERTEX_3D *pVtx;

	//ロック
	m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの設定
	pVtx[0].diffuse = D3DXCOLOR(r, g, b, a);
	pVtx[1].diffuse = D3DXCOLOR(r, g, b, a);
	pVtx[2].diffuse = D3DXCOLOR(r, g, b, a);
	pVtx[3].diffuse = D3DXCOLOR(r, g, b, a);

	//アンロック
	m_pD3DVtxBuff->Unlock();
}
//=============================================================================
// 地面の高さを取得
//=============================================================================
float Cform3D::GetHeight(D3DXVECTOR3 pos, D3DXVECTOR3 *pNormal)
{
	float fHeight = 0.0f;
	VERTEX_3D *pVtx;
	bool bFinish = false;
	VERTEX_3D *pVtx0, *pVtx1, *pVtx2;
	D3DXVECTOR3 vec0, vec1;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点を右回りに設定
	pVtx0 = &pVtx[0];
	pVtx1 = &pVtx[1];
	pVtx2 = &pVtx[2];

	vec0 = pVtx1->vtx - pVtx0->vtx;
	vec1 = pos - pVtx0->vtx;
	if(((vec0.z * vec1.x) - (vec0.x * vec1.z)) >= 0.0f)
	{
		vec0 = pVtx2->vtx - pVtx1->vtx;
		vec1 = pos - pVtx1->vtx;
		if(((vec0.z * vec1.x) - (vec0.x * vec1.z)) >= 0.0f)
		{
			vec0 = pVtx0->vtx - pVtx2->vtx;
			vec1 = pos - pVtx2->vtx;
			if(((vec0.z * vec1.x) - (vec0.x * vec1.z)) >= 0.0f)
			{
				// ポリゴン上の高さを取得
				fHeight = GetHeightPolygon(pVtx0->vtx, pVtx1->vtx, pVtx2->vtx, pos, pNormal);
				//乗っかってる
				bFinish = true;
			}
		}
	}
	//乗っかってない場合
	if(bFinish == false)
	{
		// 頂点を右回りに設定
		pVtx0 = &pVtx[1];
		pVtx1 = &pVtx[3];
		pVtx2 = &pVtx[2];

		vec0 = pVtx1->vtx - pVtx0->vtx;
		vec1 = pos - pVtx0->vtx;
		if(((vec0.z * vec1.x) - (vec0.x * vec1.z)) >= 0.0f)
		{
			vec0 = pVtx2->vtx - pVtx1->vtx;
			vec1 = pos - pVtx1->vtx;
			if(((vec0.z * vec1.x) - (vec0.x * vec1.z)) >= 0.0f)
			{
				vec0 = pVtx0->vtx - pVtx2->vtx;
				vec1 = pos - pVtx2->vtx;
				if(((vec0.z * vec1.x) - (vec0.x * vec1.z)) >= 0.0f)
				{
					// ポリゴン上の高さを取得
					fHeight = GetHeightPolygon(pVtx0->vtx, pVtx1->vtx, pVtx2->vtx, pos, pNormal);

					bFinish = true;
				}
			}
		}
	}

	// 頂点データをアンロックする
	m_pD3DVtxBuff->Unlock();

	if(bFinish == true)
	{
		//CDebugProc::Print("地面の高さ:%f\n", fHeight);
	}

	return fHeight;
}
//=============================================================================
// 該当するポリゴン上での高さを算出
//=============================================================================
float Cform3D::GetHeightPolygon(const D3DXVECTOR3& P0, const D3DXVECTOR3& P1, const D3DXVECTOR3& P2,
										D3DXVECTOR3 pos, D3DXVECTOR3 *pNormal)
{
	D3DXVECTOR3 vec0,vec1;
	D3DXVECTOR3 normal;
	float fHeight;

	vec0 = P1 - P0;
	vec1 = P2 - P0;

	// ２つの線分の外積から法線を求める
	D3DXVec3Cross(&normal, &vec1, &vec0);

	// 正規化
	D3DXVec3Normalize(&normal, &normal);

	if(normal.y == 0.0f)
	{// 法線が水平なら無視
		return 0.0f;
	}

	// 高さを算出 [("任意の頂点"から"目的の位置"へのベクトル)・法線ベクトル ＝ ０]
	fHeight = P0.y - ((normal.x * (pos.x - P0.x) + normal.z * (pos.z - P0.z)) / normal.y);

	if(pNormal)
	{
		*pNormal = normal;
	}

	return fHeight;
}
/////////////EOF////////////