//=============================================================================
//
// MS_BuildFight [Field.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "../../form/form3D.h"
//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_TEXTURE		(2)		// テクスチャの総数
//*********************************************************
// メッシュ地面クラス
//*********************************************************
class CMeshField : public Cform3D
{
public:
	CMeshField(int nPriority = 3);
	~CMeshField(void);

	static CMeshField *Create(LPDIRECT3DDEVICE9 pDevice,int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot,
								int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ);

	HRESULT Init(LPDIRECT3DDEVICE9 pDevice,int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot,
								int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ);
	void Uninit(void);
	void Update(void);
	void Draw(int pTexture);

	void SetPos(float x, float y, float z){ m_Pos.x = x; m_Pos.y = y; m_Pos.z = z; }
	void SetPos(D3DXVECTOR3 pos){ m_Pos = pos; }
	D3DXVECTOR3 GetPos(void){ return m_Pos; }

	void SetRot(float x, float y, float z){ m_Rot.x = x; m_Rot.y = y; m_Rot.z = z;}
	void SetRot(D3DXVECTOR3 rot){ m_Rot = rot; }
	D3DXVECTOR3 GetRot(void){ return m_Rot; }

	void SetMtxView (D3DXMATRIX changeMtx){m_MtxView=changeMtx;};
	void SetRotCamera (D3DXVECTOR3 rotCamera){};

	void SetColor(D3DXCOLOR col);

	float GetHeight(D3DXVECTOR3 pos, D3DXVECTOR3 *pNormal = NULL);
	float GetHeightPolygon(D3DXVECTOR3 *pVtx0, D3DXVECTOR3 *pVtx1, D3DXVECTOR3 *pVtx2,
											D3DXVECTOR3 pos, D3DXVECTOR3 *pNormal = NULL);

private:
	//LPDIRECT3DTEXTURE9		m_pD3DTex;		// テクスチャ読み込み場所
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;	// 頂点バッファインターフェースへのポインタ
	LPDIRECT3DDEVICE9		m_pDevice;		// pDeviceオブジェクト(描画に必要)
	LPDIRECT3DINDEXBUFFER9	m_pD3DIndexBuff;	// インデックスバッファインターフェースへのポインタ

	D3DXMATRIX				m_mtxWorld;			// ワールドマトリックス		
	D3DXMATRIX				m_MtxView;			//ビューマトリクス

	D3DMATERIAL9			m_material;				// マテリアル

	D3DXVECTOR3				m_Pos;			// ポリゴン表示位置の中心座標
	D3DXVECTOR3				m_Rot;			// ポリゴンの回転角
	D3DXVECTOR3				m_Scl;			//大きさ

	bool m_bTransParent;					// 半透明かどうか

	D3DXVECTOR3 *m_pBuffNormal;

	int m_nNumBlockX;
	int m_nNumBlockZ;
	int m_nNumVertex;
	int m_nNumVertexIndex;
	int m_nNumPolygon;
	float m_fSizeBlockX;
	float m_fSizeBlockZ;

	static const float m_aHeightFiled[33][33];

	LPDIRECT3DPIXELSHADER9 _ps;			//ピクセルシェーダー
	LPD3DXCONSTANTTABLE    _psc;		//ピクセルシェーダー用コンスタントテーブル
	LPDIRECT3DVERTEXSHADER9 _vs[2];		//バーテックスシェーダー
	LPD3DXCONSTANTTABLE    _vsc[2];		//バーテックスシェーダー用コンスタントテーブル

};

#endif
