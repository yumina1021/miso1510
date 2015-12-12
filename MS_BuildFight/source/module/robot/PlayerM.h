//=============================================================================
//
// MS_BuildFight [CPlayerM.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CPLAYERM_H_
#define _CPLAYERM_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "Model.h"
#include "PlayerBace.h"

#include "../../form/form.h"
#include "../../common.h"
//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************
class CSound;
class CInputKeyboard;
class CformX;
class CEnemyM;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPlayerM  : public Cform
{
	public:
		CPlayerM(OBJTYPE objtype = OBJTYPE_PLAYERM,int nPriority = 5);//コンストラクタ
		~CPlayerM(void);//デストラクタ

		static CPlayerM *Create(LPDIRECT3DDEVICE9 pDevice,int nTypeModel,D3DXVECTOR3 pos,D3DXVECTOR3 rot);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,int nTypeModel,D3DXVECTOR3 pos, D3DXVECTOR3 rot,bool CPU);//初期化
		void Uninit(void);//終了
		void Update(void);//更新
		void Draw(void);//描画
		void Restart(D3DXVECTOR3 pos,D3DXVECTOR3 rot);

		void SetPos(D3DXVECTOR3 pos){m_Pos=pos;};
		void SetPos(float fx,float fy,float fz){m_Pos.x=fx;m_Pos.y=fy;m_Pos.z=fz;};
		D3DXVECTOR3 GetPos(void){return m_Pos;};

		void SetRot(D3DXVECTOR3 rot){m_Rot=rot;};
		void SetRot(float fx,float fy,float fz){m_Rot.x=fx;m_Rot.y=fy;m_Rot.z=fz;};
		D3DXVECTOR3 GetRot(void){return m_Rot;};

		void SetMtxView (D3DXMATRIX changeMtx){};
		D3DXVECTOR3 GetRotCamera (void){return m_RotCamera;};
		void SetRotCamera (D3DXVECTOR3 rotCamera){m_RotCamera=rotCamera;};

		D3DXVECTOR3 GetMove(void){return m_Move;};

		bool IsFinishMotion(void){ return m_bFinishMotion;}

		void SetMotion(MOTIONTYPE motionType);

		int GetType(void){return m_nType;};

	private:

		void UpdateMotion(void);
		void UpdateShotMotion(void);

		float lerp(float a, float b, float per){ return (a*per) + (b*(1 - per)); };
		D3DXVECTOR3 lerpVec(D3DXVECTOR3 a, D3DXVECTOR3 b, float per);

		LPDIRECT3DDEVICE9	m_pDevice;			// pDeviceオブジェクト(描画に必要)

		D3DXVECTOR3		m_Pos;					//位置
		D3DXVECTOR3		m_PosOld;				//前回位置

		D3DXVECTOR3		m_Rot;					//向き
		D3DXVECTOR3		m_rotDestModel;			//目的の向き
		D3DXVECTOR3		m_Move;					// 現在の移動量

		D3DXVECTOR3		m_RotCamera;			//カメラの向き

		MOTIONTYPE		m_motionType;			// モーションタイプ

		SHADER_SET		shaderSet;

		CModel				*m_apModel[MODELPARTS_MAX];	// モデルへのポインタ
		LPDIRECT3DTEXTURE9	m_pD3DTex;		//テクスチャ表示用

		D3DXMATRIX		m_mtxWorld;				// ワールドマトリックス

		int				m_nNumModel;			// モデル数

		int				m_nNumKey;				// キーの数
		KEY_INFO		*m_pKeyInfo;			// キーへのポインタ

		int				m_nKey;					// キーNo.
		int				m_nCountMotion;			// モーションカウンタ

		bool			m_bLoopMotion;			// ループモーションかどうか

		bool			m_bMotion;				// モーションしているかどうか
		bool			m_bFinishMotion;		// モーションが終了しているかどうか

		bool			m_bPause;				// ポーズON/OFF
		bool			m_bDispDebug;			// デバッグ表示ON/OFF
		int				m_nType;				//タイプ保存用

		float			m_fShotMotionRatio;		//打つモーションの割合
		int				m_nShotMotionCntPlus;

		D3DXVECTOR3		m_Min;
		D3DXVECTOR3		m_Max;

};

#endif

/////////////EOF////////////