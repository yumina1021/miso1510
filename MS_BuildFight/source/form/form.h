//=============================================================================
//
// MS_BuildFight [form.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CFORM_H_
#define _CFORM_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "../common.h"
//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_PRIORITY	(8)

typedef enum
{
	OBJTYPE_NONE=0,
	OBJTYPE_2D,
	OBJTYPE_3D,
	OBJTYPE_BILLBOARD,
	OBJTYPE_X,
	OBJTYPE_MODEL,
	OBJTYPE_PLAYER,
	OBJTYPE_PLAYERM,
	OBJTYPE_ENEMY,
	OBJTYPE_GIMMICK,
	OBJTYPE_BULLET,
	OBJTYPE_PAUSE,
	OBJTYPE_TIMER,
	OBJTYPE_MAX
}OBJTYPE;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Cform
{
	public:
		Cform(OBJTYPE objType,int nPriority = 3);				//コンストラクタ
		virtual ~Cform(void);					//デストラクタ

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);	//初期化
		virtual void Uninit(void)=0;			//終了
		virtual void Update(void)=0;			//更新
		virtual void Draw(void)=0;

		void LinkList(int nPriority);
		void UnlinkList(void);
		void Release(void);

		static void UpdateAll(void);

		static void UpdateGame(void);
		static void UpdateGameEnd(void);
		static void UpdatePause(void);

		static void DrawAll(D3DXMATRIX changeMtx,D3DXVECTOR3 rotCamera);

		static void DrawGame(D3DXMATRIX changeMtx,D3DXVECTOR3 rotCamera);
		static void DrawPause(D3DXMATRIX changeMtx,D3DXVECTOR3 rotCamera);

		static void ReleaseAll(void);

		virtual void SetPos(D3DXVECTOR3 pos)=0;
		virtual void SetPos(float fx,float fy,float fz)=0;
		virtual D3DXVECTOR3 GetPos(void)=0;
		virtual void SetRot(D3DXVECTOR3 rot)=0;
		virtual void SetRot(float fx,float fy,float fz)=0;
		virtual D3DXVECTOR3 GetRot(void)=0;

		virtual void SetMtxView(D3DXMATRIX changeMtx){};
		virtual void SetRotCamera(D3DXVECTOR3 rotCamera){};

		virtual void SetPosOld(D3DXVECTOR3 pos){};
		virtual D3DXVECTOR3 GetPosOld(void){return D3DXVECTOR3(0.0f,0.0f,0.0f);};
		virtual void SetRotOld(D3DXVECTOR3 rot){};
		virtual D3DXVECTOR3 GetRotOld(void){return D3DXVECTOR3(0.0f,0.0f,0.0f);};

		virtual D3DXVECTOR3 GetVertexMin(void){return D3DXVECTOR3(0.0f,0.0f,0.0f);};
		virtual D3DXVECTOR3 GetVertexMax(void){return D3DXVECTOR3(0.0f,0.0f,0.0f);};

		OBJTYPE GetObjType(void){return m_objType;};
		Cform *GetTop(void){return m_pTop[5];};

		Cform	*m_pNext;						// 次のオブジェ
	private:
		// リスト用
		static	Cform *m_pTop[NUM_PRIORITY];	// リストの先頭位置
		static	Cform *m_pCur[NUM_PRIORITY];	// リストの現在位置
		Cform	*m_pPrev;						// 前のオブジェ

		int		m_nPriority;					// リスト用変数
		bool	m_bDelete;						// オブジェクト削除
		OBJTYPE	m_objType;						// タイプ
};

#endif

/////////////EOF////////////