//=============================================================================
//
// MS_BuildFight [CformBillBoard.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "formBillBoard.h"
//=============================================================================
// コンストラクタ
//=============================================================================
CformBillBoard :: CformBillBoard(int nPriority) : Cform(OBJTYPE_BILLBOARD,nPriority)
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CformBillBoard :: ~CformBillBoard(void)
{
}
//=============================================================================
// Cform2D生成
//=============================================================================
CformBillBoard *CformBillBoard::Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CformBillBoard *pformBillBoard;

	pformBillBoard = new CformBillBoard();
	pformBillBoard->Init(pDevice,"data/TEXTURE/bullet000.png",10,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	pformBillBoard->SetPos(pos);

	return pformBillBoard;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CformBillBoard :: Init(LPDIRECT3DDEVICE9 pDevice,LPSTR pTexName,float fLength,D3DXCOLOR changeColor)
{

	m_pDevice=pDevice;

	//フィールドの初期化
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//頂点情報の設定
	if(FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&m_pD3DVtxBuff,NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;

	//ロック
	m_pD3DVtxBuff->Lock(0,0,(void**)&pVtx,0);

	pVtx[0].vtx = D3DXVECTOR3(-fLength,fLength,0.0f);//x,yの順
	pVtx[1].vtx = D3DXVECTOR3(fLength,fLength,0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-fLength,-fLength,0.0f);
	pVtx[3].vtx = D3DXVECTOR3(fLength,-fLength,0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);

	pVtx[0].diffuse = D3DXCOLOR(changeColor.r,changeColor.g,changeColor.b,changeColor.a);//色は白
	pVtx[1].diffuse = D3DXCOLOR(changeColor.r,changeColor.g,changeColor.b,changeColor.a);
	pVtx[2].diffuse = D3DXCOLOR(changeColor.r,changeColor.g,changeColor.b,changeColor.a);
	pVtx[3].diffuse = D3DXCOLOR(changeColor.r,changeColor.g,changeColor.b,changeColor.a);

	pVtx[0].tex = D3DXVECTOR2(0,0);//画像のUV値　U,Vの順
	pVtx[1].tex = D3DXVECTOR2(1,0);
	pVtx[2].tex = D3DXVECTOR2(0,1);
	pVtx[3].tex = D3DXVECTOR2(1,1);	
	
	//アンロック
	m_pD3DVtxBuff->Unlock();

	//テクスチャの設定
	if(pTexName!=NULL)
	{
		D3DXCreateTextureFromFile(m_pDevice,pTexName,&m_pD3DTex);
	}else
	{
		m_pD3DTex=NULL;
	}

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CformBillBoard :: Uninit(void)
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
void CformBillBoard :: Update(void)
{

}
//=============================================================================
// 描画
//=============================================================================
void CformBillBoard :: Draw(void)
{
	D3DXMATRIX  mtxWorld;
	//マトリックスの設定
	D3DXMATRIX mtxTranslate;

	//m_pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
	//m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);

	//ワールドマトリックスの設定
	D3DXMatrixIdentity(&mtxWorld);
	D3DXMatrixInverse(&mtxWorld,NULL,&m_MtxView);

	mtxWorld._41=0.0f;
	mtxWorld._42=0.0f;
	mtxWorld._43=0.0f;

	D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);
	D3DXMatrixMultiply(&mtxWorld,&mtxWorld,&mtxTranslate);

	m_pDevice->SetTransform(D3DTS_WORLD,&mtxWorld);

	//頂点バッファをデータストリームにバインド
	m_pDevice->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	m_pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	if(m_pD3DTex!=NULL)
	{
		m_pDevice->SetTexture(0,m_pD3DTex);
	}else
	{
		m_pDevice->SetTexture(0,NULL);
	}

	//ポリゴンの描画
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
	//m_pDevice->SetRenderState(D3DRS_LIGHTING,TRUE);


}
//=============================================================================
// UV値設定
//=============================================================================
void CformBillBoard :: SetUV(float ful,float fur,float fvt,float fvu)
{
	VERTEX_3D *pVtx;

	//ロック
	m_pD3DVtxBuff->Lock(0,0,(void**)&pVtx,0);

	pVtx[0].tex = D3DXVECTOR2(ful,fvt);//画像のUV値　U,Vの順
	pVtx[1].tex = D3DXVECTOR2(fur,fvt);
	pVtx[2].tex = D3DXVECTOR2(ful,fvu);
	pVtx[3].tex = D3DXVECTOR2(fur,fvu);

	//アンロック
	m_pD3DVtxBuff->Unlock();
}

void CformBillBoard :: SetDiffuse(float r,float g,float b,float a)
{
	VERTEX_3D *pVtx;

	//ロック
	m_pD3DVtxBuff->Lock(0,0,(void**)&pVtx,0);

	//ポリゴンの設定
	pVtx[0].diffuse = D3DXCOLOR(r,g,b,a);
	pVtx[1].diffuse = D3DXCOLOR(r,g,b,a);
	pVtx[2].diffuse = D3DXCOLOR(r,g,b,a);
	pVtx[3].diffuse = D3DXCOLOR(r,g,b,a);

	//アンロック
	m_pD3DVtxBuff->Unlock();
}
//=============================================================================
// 座標設定
//=============================================================================
void CformBillBoard::SetVtx(float fLength)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx.x = -fLength;
		pVtx[0].vtx.y = fLength;
		pVtx[0].vtx.z = 0.0f;

		pVtx[1].vtx.x = fLength;
		pVtx[1].vtx.y = fLength;
		pVtx[1].vtx.z = 0.0f;

		pVtx[2].vtx.x = -fLength;
		pVtx[2].vtx.y = -fLength;
		pVtx[2].vtx.z = 0.0f;

		pVtx[3].vtx.x = fLength;
		pVtx[3].vtx.y = -fLength;
		pVtx[3].vtx.z = 0.0f;

		// 頂点データをアンロックする
		m_pD3DVtxBuff->Unlock();
	}	
}
/////////////EOF////////////