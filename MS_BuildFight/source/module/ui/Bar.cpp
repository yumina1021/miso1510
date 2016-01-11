//=============================================================================
//
// MS_BuildFight [CBar.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "Bar.h"
#include "../../administer/Texture.h"
//=============================================================================
// コンストラクタ
//=============================================================================
CBar :: CBar()
{

}
//=============================================================================
// デストラクタ
//=============================================================================
CBar :: ~CBar(void)
{
}
//=============================================================================
// CBar生成
//=============================================================================
CBar *CBar::Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXCOLOR color,float width,float height)
{
	CBar *pBar;

	pBar = new CBar();
	pBar->Init(pDevice,pos,color,width,height);

	return pBar;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CBar :: Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXCOLOR color,float width,float height)
{

	m_pDevice=pDevice;

	//テクスチャの読み込み
	m_texid = TEXTURE_BLUE;
	//D3DXCreateTextureFromFile(m_pDevice,"data/TEXTURE/bar2.png",&m_pD3DTex);

	//頂点バッファの生成(メモリの確認)
	if(FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*POINT_MAX,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_2D,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuff,
											NULL)))
	{
		return E_FAIL;
	}

	m_Pos=pos;
	m_Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);

	//ポリゴン対角線の長さ初期化
	m_fLength = sqrtf(((width/2)*(width/2))+((height/2)*(height/2)));

	//ポリゴン対角線の角度初期化
	m_fAngle = atan2f((width/2),(height/2));

	D3DXVECTOR3 Setpos[POINT_MAX];					//ポリゴンの位置
	
	//回転
	Setpos[0].x = m_Pos.x + (sin(-m_Rot.z - m_fAngle)*m_fLength);
	Setpos[0].y = m_Pos.y - (cos(-m_Rot.z - m_fAngle)*m_fLength);
	Setpos[1].x = m_Pos.x + (sin(-m_Rot.z + m_fAngle)*m_fLength);
	Setpos[1].y = m_Pos.y - (cos(-m_Rot.z + m_fAngle)*m_fLength);
	Setpos[2].x = m_Pos.x + (sin(m_Rot.z - m_fAngle)*m_fLength);
	Setpos[2].y = m_Pos.y + (cos(m_Rot.z - m_fAngle)*m_fLength);
	Setpos[3].x = m_Pos.x + (sin(m_Rot.z + m_fAngle)*m_fLength);
	Setpos[3].y = m_Pos.y + (cos(m_Rot.z + m_fAngle)*m_fLength);

	VERTEX_2D *pVtx;

	//ロック
	m_pD3DVtxBuff->Lock(0,0,(void**)&pVtx,0);

	//ポリゴンの設定

	pVtx[0].vtx=D3DXVECTOR3(Setpos[0].x,Setpos[0].y,0.0f);//x,yの順
	pVtx[1].vtx=D3DXVECTOR3(Setpos[1].x,Setpos[1].y,0.0f);
	pVtx[2].vtx=D3DXVECTOR3(Setpos[2].x,Setpos[2].y,0.0f);
	pVtx[3].vtx=D3DXVECTOR3(Setpos[3].x,Setpos[3].y,0.0f);

	pVtx[0].hrw=1.0f;//1.0f固定
	pVtx[1].hrw=1.0f;
	pVtx[2].hrw=1.0f;
	pVtx[3].hrw=1.0f;

	pVtx[0].diffuse = D3DXCOLOR(color);
	pVtx[1].diffuse = D3DXCOLOR(color);
	pVtx[2].diffuse = D3DXCOLOR(color);
	pVtx[3].diffuse = D3DXCOLOR(color);

	pVtx[0].tex = D3DXVECTOR2(0,0);//画像のUV値　U,Vの順
	pVtx[1].tex = D3DXVECTOR2(1,0);
	pVtx[2].tex = D3DXVECTOR2(0,1);
	pVtx[3].tex = D3DXVECTOR2(1,1);

	//アンロック
	m_pD3DVtxBuff->Unlock();

	m_bViewFlag=true;

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CBar :: Uninit(void)
{
	//様々なオブジェクトの終了（開放）処理

	//if(m_pD3DTex!=NULL)
	//{
	//	m_pD3DTex->Release();
	//	m_pD3DTex=NULL;
	//}
	if(m_pD3DVtxBuff!=NULL)
	{
		m_pD3DVtxBuff->Release();
		m_pD3DVtxBuff=NULL;
	}

	delete this;
}
//=============================================================================
// 更新
//=============================================================================
void CBar :: Update(void)
{

}
//=============================================================================
// 描画
//=============================================================================
void CBar :: Draw(void)
{
	if(m_bViewFlag)
	{
		//様々なオブジェクトの描画処理
		m_pDevice->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_2D));

		//テクスチャの設定
		m_pDevice->SetTexture(0, CTexture::GetTex(m_texid));

		//頂点フォーマットの描画
		m_pDevice->SetFVF(FVF_VERTEX_2D);

		//ポリゴンの描画
		m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
	}
}
/////////////EOF////////////