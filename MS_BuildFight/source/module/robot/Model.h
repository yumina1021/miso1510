//=============================================================================
//
// MS_BuildFight [Model.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CMODEL_H_
#define _CMODEL_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "../../common.h"
//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
class CCamera;
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	PLAYER_WIDTH	(10.0f)		// プレイヤーの幅
#define	PLAYER_HEIGHT	(10.0f)		// プレイヤーの高さ
#define	PLAYER_RADIUS	(10.0f)		// プレイヤーの半径
#define PLAYER_SIZE		(20)
#define TEXTURE_MAX		(4)
// モデルパーツ
typedef enum
{
	MODELPARTS_BODY = 0,	// [0]体
	MODELPARTS_HEAD,		// [1]頭
	MODELPARTS_RIGHTARM,	// [2]右腕
	MODELPARTS_RIGHTHAND,	// [3]右手
	MODELPARTS_RIGHTFINGER,	// [4]右指
	MODELPARTS_LETTARM,		// [5]左腕
	MODELPARTS_LETTHAND,	// [6]左手
	MODELPARTS_LETTFINGER,	// [7]右指
	MODELPARTS_RIGHTLEG,	// [8]右腿
	MODELPARTS_RIGHTFOOT,	// [9]右足
	MODELPARTS_LEFTLEG,		// [10]左腿
	MODELPARTS_LEFTFOOT,	// [11]左足
	MODELPARTS_MAX
} MODELPARTS;

// モーションの種類
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,	// [0]ニュートラル
	MOTIONTYPE_SHOT,		// [1]ショット
	MOTIONTYPE_SHOT2,		// [1]ショット
	MOTIONTYPE_ROLLING,
	MOTIONTYPE_ROLLINGS,
	MOTIONTYPE_SELECT,
	MOTIONTYPE_MAX
} MOTIONTYPE;

//*********************************************************
// キー要素
//*********************************************************
typedef struct
{
	float fPosX;	// X軸位置
	float fPosY;	// Y軸位置
	float fPosZ;	// Z軸位置
	float fRotX;	// X軸回転
	float fRotY;	// Y軸回転
	float fRotZ;	// Z軸回転
} KEY;
//*********************************************************
// キー情報
//*********************************************************
typedef struct
{
	int nFrame;					// 再生フレーム
	KEY aKey[MODELPARTS_MAX];	// 各モデルのキー要素
} KEY_INFO;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CModel
{
	public:
		CModel(void);//コンストラクタ
		~CModel(void);//デストラクタ

		static CModel *Create(LPDIRECT3DDEVICE9 pDevice,int nType,int nModelNum,D3DXVECTOR3 pos,D3DXVECTOR3 rot);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,int nType,int nModelNum);//初期化
		void Uninit(void);//終了
		void Update(void);//更新
		void Draw(LPDIRECT3DTEXTURE9 pD3DTex, SHADER_SET* shader,CCamera* camera);//描画

		void SetPos(D3DXVECTOR3 pos){m_Pos=pos;};
		void SetPos(float fx,float fy,float fz){m_Pos.x=fx;m_Pos.y=fy;m_Pos.z=fz;};
		D3DXVECTOR3 GetPos(void){return m_Pos;};

		void SetRot(D3DXVECTOR3 rot){m_Rot=rot;};
		void SetRot(float fx,float fy,float fz){m_Rot.x=fx;m_Rot.y=fy;m_Rot.z=fz;};
		D3DXVECTOR3 GetRot(void){return m_Rot;};

		HRESULT SetModel(const char *pFilename);

		void SetPosOrg(D3DXVECTOR3 pos){ m_PosOrg = pos; };
		void SetRotOrg(D3DXVECTOR3 rot){ m_RotOrg = rot; };

		void EnableDisp(bool bDisp){ m_bDisp = bDisp; };
		D3DXMATRIX GetMtxWorld(void){ return m_mtxWorld; };

		D3DXVECTOR3 *GetVtxMin(void){ return &m_vtxMin; };
		D3DXVECTOR3 *GetVtxMax(void){ return &m_vtxMax; };

		LPD3DXBUFFER GetMatBuff(void){ return m_pD3DXBuffMatModel; };

		D3DXVECTOR3 GetRotCamera(void){ return m_RotCamera; };

		void SetParent(CModel *pModel){ m_pParent = pModel; };
		void SetChild(CModel *pModel){ m_pChild = pModel; };

		void SetMtxView(D3DXMATRIX changeMtx){ m_mtxview = changeMtx; };
		void SetRotCamera (D3DXVECTOR3 rotCamera){};

	private:
		LPDIRECT3DDEVICE9	m_pDevice;				//pDeviceオブジェクト(描画に必要)	

		D3DXMATRIX			m_MtxView;				//ビューマトリクス

		LPD3DXMESH			m_pD3DXMeshModel;		//メッシュ情報へのポインタ
		LPD3DXBUFFER		m_pD3DXBuffMatModel;	//マテリアル情報へのポインタ
		DWORD				m_nNumMatModel;			//マテリアル情報の数

		D3DXMATRIX			m_mtxWorld;				//ワールドマトリックス
		D3DXMATRIX			m_mtxview;				//ワールドマトリックス

		D3DXVECTOR3			m_vtxMin;				//頂点の最小値
		D3DXVECTOR3			m_vtxMax;				//頂点の最大値

		D3DXVECTOR3			m_Pos;					//位置
		D3DXVECTOR3			m_Rot;					//向き
		D3DXVECTOR3			m_PosOrg;					//位置
		D3DXVECTOR3			m_RotOrg;					//向き
		D3DXVECTOR3			m_Scl;					//大きさ

		D3DXVECTOR3			m_RotCamera;			//カメラの向き

		D3DXVECTOR3			m_rotDestModel;			//目的の向き

		bool				m_bTransParent;			//半透明ON/OFF
		bool				m_bDisp;				//表示ON/OFF

		CModel				*m_pParent;				//親モデルへのポインタ	
		CModel				*m_pChild;				//子モデルへのポインタ

		static const char	*m_apModelName[];
};

#endif

/////////////EOF////////////