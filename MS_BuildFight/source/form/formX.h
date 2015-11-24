//=============================================================================
//
// MS_BuildFight [formX.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CSCENEX_H_
#define _CSCENEX_H_
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
#define TEXTURE_MAX		(4)
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CformX  : public Cform
{
	public:
		CformX(OBJTYPE objType=OBJTYPE_X,int nPriority=5);//コンストラクタ
		~CformX(void);//デストラクタ

		static CformX *Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot,bool set,bool enemy);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,LPSTR pFileName,LPSTR pTexName);//初期化
		void Uninit(void);//終了
		void Update(void);//更新
		void Draw(void);//描画

		void SetPos(D3DXVECTOR3 pos){m_Pos=pos;};
		void SetPos(float fx,float fy,float fz){m_Pos.x=fx;m_Pos.y=fy;m_Pos.z=fz;};
		D3DXVECTOR3 GetPos(void){return m_Pos;};
		void SetRot(D3DXVECTOR3 rot){m_rotDestModel=rot;};
		void SetRot(float fx,float fy,float fz){m_rotDestModel.x=fx;m_rotDestModel.y=fy;m_rotDestModel.z=fz;};
		D3DXVECTOR3 GetRot(void){return m_Rot;};
		void SetScl(D3DXVECTOR3 scl){m_Scl=scl;};
		void SetScl(float fx,float fy,float fz){m_Pos.x=fx;m_Pos.y=fy;m_Pos.z=fz;};
		D3DXVECTOR3 GetScl(void){return m_Scl;};
		void SetMtxView (D3DXMATRIX changeMtx){m_MtxView=changeMtx;};
		D3DXMATRIX GetMtxView (void){return m_MtxView;};
		D3DXVECTOR3 GetRotCamera (void){return m_RotCamera;};
		void SetRotCamera (D3DXVECTOR3 rotCamera){m_RotCamera=rotCamera;};
		void SetTexture(LPSTR pTexName,int num);
		void SetTextureNum(int num){nTextureNum=num;};
		void SetViewFlag(bool	change){m_bDeathFlag=change;};
		void ResetCount(int nCount){m_nDeathCount=nCount;};

		void SetShader(SHADER_SET shader){ m_shader = shader;};

	protected:
		LPD3DXMESH			m_pD3DXMeshModel;		//メッシュ情報へのポインタ
	private:

		LPDIRECT3DTEXTURE9	m_pD3DTex[TEXTURE_MAX];	//テクスチャ表示用
		LPDIRECT3DCUBETEXTURE9 m_pD3DTextureCube;	// テクスチャ読み込み場所

		LPDIRECT3DDEVICE9	m_pDevice;				// pDeviceオブジェクト(描画に必要)	

		D3DXMATRIX			m_MtxView;				//ビューマトリクス
		D3DXMATRIX			m_mtxWorld;				// ワールドマトリックス

		LPD3DXBUFFER		m_pD3DXBuffMatModel;	//マテリアル情報へのポインタ
		DWORD				m_nNumMatModel;			//マテリアル情報の数

		D3DXVECTOR3			m_Pos;					//位置
		D3DXVECTOR3			m_Rot;					//向き
		D3DXVECTOR3			m_Scl;					//大きさ

		D3DXVECTOR3			m_RotCamera;			//カメラの向き

		D3DXVECTOR3			m_rotDestModel;			//目的の向き

		int					nTextureNum;			//テクスチャーの番号

		bool				m_bDeathFlag;
		int					m_nDeathCount;

		bool				m_bEnemyFlag;

		SHADER_SET			m_shader;

};

#endif

/////////////EOF////////////