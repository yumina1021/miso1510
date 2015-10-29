//=============================================================================
//
// MS_BuildFight [LocusEffect.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "LocusEffect.h"
//=============================================================================
// コンストラクタ
//=============================================================================
CLocusEffect :: CLocusEffect(OBJTYPE objtype,int nPriority) : Cform(objtype,nPriority)
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CLocusEffect :: ~CLocusEffect(void)
{
}
//=============================================================================
// CLocusEffect生成
//=============================================================================
CLocusEffect *CLocusEffect::Create(LPDIRECT3DDEVICE9 pDevice,LPSTR pTexName,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CLocusEffect *pLocusEffect;

	pLocusEffect = new CLocusEffect();
	pLocusEffect->Init(pDevice,pTexName);
	//pLocusEffect->SetPos(pos);

	return pLocusEffect;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CLocusEffect :: Init(LPDIRECT3DDEVICE9 pDevice,LPSTR pTexName)
{
	m_pDevice=pDevice;

	int nNumBlockX=1;
	int nNumBlockZ=1;

	//テクスチャの設定
	D3DXCreateTextureFromFile(m_pDevice,"data/TEXTURE/toumei2.png",&m_pD3DTex);

	//フィールドの初期化
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	m_fLength = sqrtf((float)(((TEXTURE_SIZE_X / 2) * (TEXTURE_SIZE_X / 2)) + ((TEXTURE_SIZE_Y / 2) * (TEXTURE_SIZE_Y / 2))));
	m_fAngle = atan2f((TEXTURE_SIZE_X / 2), (TEXTURE_SIZE_Y / 2));

	//頂点情報の設定
	if(FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)* 2 * BUFFER_MAX,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuff,
											NULL)))
	{
		return E_FAIL;
	}

	for(int i=0;i<BUFFER_MAX;i++)
	{
		PosBuff[i]=D3DXVECTOR3(0.0f,0.0f,0.0f);
		ColorBuff[i]=D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
	}

	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for(int i=0;i<BUFFER_MAX;i++)
	{
		pVtx[i].vtx=PosBuff[i];
		pVtx[i].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
		pVtx[i].diffuse= ColorBuff[i];
		pVtx[i].tex = D3DXVECTOR2(0,0);
	}

	// 頂点データをアンロックする
	m_pD3DVtxBuff->Unlock();

	m_bFlag = false;

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CLocusEffect :: Uninit(void)
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
void CLocusEffect :: Update(void)
{
	VERTEX_3D *pVtx;

	if (m_bFlag)
	{
		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < BUFFER_MAX / 2; i++)
		{
			pVtx[i * 2].vtx = PosBuff[i * 2];
			pVtx[i * 2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[i * 2].diffuse = ColorBuff[i * 2];
			pVtx[i * 2].tex = D3DXVECTOR2(0, 0);

			pVtx[i * 2 + 1].vtx = PosBuff[i * 2 + 1];
			pVtx[i * 2 + 1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[i * 2 + 1].diffuse = ColorBuff[i * 2 + 1];
			pVtx[i * 2 + 1].tex = D3DXVECTOR2(1, 0);
		}

		// 頂点データをアンロックする
		m_pD3DVtxBuff->Unlock();
	}
}
//=============================================================================
// 描画
//=============================================================================
void CLocusEffect :: Draw(void)
{
	if (m_bFlag)
	{
		//m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);	// 結果 = 転送先(DEST) - 転送元(SRC)
		//m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		// SRC(これから描画する側) + DEST(既に描画されてる側)
		m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		// SRCを半透明合成するよ
		m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		// DESTをそのまま描画するよ
		m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

		//マトリックスの設定
		D3DXMatrixIdentity(&mtxWorld);
		D3DXMatrixScaling(&mtxScl, m_Scl.x, m_Scl.y, m_Scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
		//D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);
		D3DXMatrixTranslation(&mtxTranslate, 0.0f, 0.0f, 0.0f);

		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);
		m_pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		//頂点バッファをデータストリームにバインド
		m_pDevice->SetStreamSource(0, m_pD3DVtxBuff, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		m_pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		//m_pDevice->SetTexture(0,m_pD3DTex);
		m_pDevice->SetTexture(0, NULL);


		//ポリゴンの描画
		m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 120);

		m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定
		////m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			// 結果 = 転送元(SRC) + 転送先(DEST)
	}
}

//=============================================================================
// セット
//=============================================================================
//void CLocusEffect :: SetPosBuffer(D3DXVECTOR3 pos1,D3DXVECTOR3 pos2,D3DXMATRIX mtxWorld)
void CLocusEffect :: SetPosBuffer(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 posA=pos;

	//D3DXVec3TransformCoord(&posA,&pos1,&mtxWorld);
	//D3DXVec3TransformCoord(&posB,&pos2,&mtxWorld);

	for(int i=119;i>0;i--)
	{
		PosBuff[i*2+1]=PosBuff[((i-1)*2)+1];
		PosBuff[i*2]=PosBuff[(i-1)*2];

		if(ColorBuff[((i-1)*2)].a>0.0f)
		{
			ColorBuff[(i-1)*2].a -= 0.01f;
		}else
		{
			ColorBuff[(i-1)*2].a = 0.0f;
		}
		
		if(ColorBuff[((i-1)*2)+1].a>0.0f)
		{
			ColorBuff[((i-1)*2)+1].a -= 0.03f;
		}else
		{
			ColorBuff[((i-1)*2)+1].a = 0.0f;
		}

		ColorBuff[i*2+1]=ColorBuff[((i-1)*2)+1];
		ColorBuff[i*2]=ColorBuff[(i-1)*2];
	}

	PosBuff[0]=D3DXVECTOR3(posA.x,posA.y,posA.z);
	PosBuff[1]=D3DXVECTOR3(posA.x,posA.y+3.0f,posA.z);

	ColorBuff[0]=D3DXCOLOR(1.0f,0.0f,0.0f,0.2f);
	ColorBuff[1]=D3DXCOLOR(0.0f,0.0f,1.0f,0.8f);

}
/////////////EOF////////////