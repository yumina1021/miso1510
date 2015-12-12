//=============================================================================
//
// MS_BuildFight [form3D.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CSCENE3D_H_
#define _CSCENE3D_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "form.h"
//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_SIZE_X		(50)	// テクスチャの幅
#define TEXTURE_SIZE_Y		(50)	// テクスチャの高さ
#define	NUM_VERTEX			(4)		// 頂点数
#define	NUM_POLYGON			(2)		// ポリゴン数
#define SUM_INDEX(X,Z) ((X+1)*(Z-1)+((X+1)*(Z+1))+(Z-1)*2)
//*****************************************************************************
// クラス定義
//*****************************************************************************
class Cform3D  : public Cform
{
	public:
		Cform3D(int nPriority = 4);//コンストラクタ
		~Cform3D(void);//デストラクタ

		static Cform3D *Create(LPDIRECT3DDEVICE9 pDevice,LPSTR pTexName,D3DXVECTOR3 pos,D3DXVECTOR3 rot);
		static Cform3D *Create(LPDIRECT3DDEVICE9 pDevice, LPSTR pTexName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float width, float height);


		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,LPSTR pTexName);//初期化
		HRESULT Init(LPDIRECT3DDEVICE9 pDevice, LPSTR pTexName, float fTexSizeX, float fTexSizeY);
		void Uninit(void);//終了
		void Update(void);//更新
		void Draw(void);//描画

		void SetPos(D3DXVECTOR3 pos){m_Pos=pos;};
		void SetPos(float fx,float fy,float fz){m_Pos.x=fx;m_Pos.y=fy;m_Pos.z=fz;};
		D3DXVECTOR3 GetPos(void){return m_Pos;};
		void SetRot(D3DXVECTOR3 rot){m_Rot=rot;};
		void SetRot(float fx,float fy,float fz){m_Rot.x=fx;m_Rot.y=fy;m_Rot.z=fz;};
		D3DXVECTOR3 GetRot(void){return m_Rot;};
		void SetMtxView (D3DXMATRIX changeMtx){m_MtxView=changeMtx;};
		void SetRotCamera (D3DXVECTOR3 rotCamera){m_RotCamera=rotCamera;};
		void SetTexture(LPDIRECT3DTEXTURE9 pTex){m_pD3DTex=pTex;};
	
		float GetHeight(D3DXVECTOR3 pos, D3DXVECTOR3 *pNormal);
		float GetHeightPolygon(const D3DXVECTOR3& P0, const D3DXVECTOR3& P1, const D3DXVECTOR3& P2,
											D3DXVECTOR3 pos, D3DXVECTOR3 *pNormal = NULL);

		void SetLength(float width, float height);
		D3DXVECTOR2 GetLengthWH(void){ return D3DXVECTOR2(m_fLength, m_fAngle); };
		void SetLength(float length){ m_fLength = length; };
		float GetLength(void){ return m_fLength; };
		void SetDiffuse(float r, float g, float b, float a);





	protected:
		LPDIRECT3DTEXTURE9  	m_pD3DTex;			//テクスチャ表示用
		LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;		//頂点情報格納ワーク(動的)
		LPDIRECT3DDEVICE9		m_pDevice;			// pDeviceオブジェクト(描画に必要)

		D3DXMATRIX				m_MtxView;			//ビューマトリクス

		D3DXVECTOR3				m_Pos;				//位置
		D3DXVECTOR3				m_Rot;				//向き

		D3DXVECTOR3				m_Scl;				//大きさ
		float m_fLength;						// ポリゴンの中心から頂点までの長さ
		float m_fAngle;							// ポリゴンと頂点を結んだ直線の傾き
		D3DXVECTOR3				m_RotCamera;

};

#endif

/////////////EOF////////////