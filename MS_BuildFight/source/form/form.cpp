//=============================================================================
//
// MS_BuildFight [Cform.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "form.h"

//*****************************************************************************
// 静的変数
//*****************************************************************************
// リスト用
Cform *Cform::m_pTop[NUM_PRIORITY] = {};
Cform *Cform::m_pCur[NUM_PRIORITY] = {};
//=============================================================================
// コンストラクタ
//=============================================================================
Cform :: Cform(OBJTYPE objType,int nPriority)
{
	LinkList(nPriority);
	m_bDelete = false;
	m_objType=objType;
}
//=============================================================================
// デストラクタ
//=============================================================================
Cform :: ~Cform(void)
{

}
//=============================================================================
// リスト内オブジェ更新
//=============================================================================
void Cform::UpdateAll(void)
{
	for(int i=0;i<NUM_PRIORITY;i++)
	{
		Cform *pform = m_pTop[i];

		while(pform)
		{
			Cform *pformNext = pform->m_pNext;

			// オブジェクトの更新処理
			pform->Update();

			pform = pformNext;
		}

		pform = m_pTop[i];

		while(pform)
		{
			Cform *pformNext = pform->m_pNext;
			if(pform->m_bDelete==true)
			{
				pform->UnlinkList();
				delete pform;
			}
			pform = pformNext;
		}
	}
}
//=============================================================================
// リスト内オブジェ更新
//=============================================================================
void Cform::UpdateGame(void)
{
	for(int i=0;i<NUM_PRIORITY;i++)
	{
		Cform *pform = m_pTop[i];

		while(pform)
		{
			Cform *pformNext = pform->m_pNext;

			if(!(pform->GetObjType()==OBJTYPE_PAUSE))
			{
				// オブジェクトの更新処理
				pform->Update();
			}
			pform = pformNext;
		}

		pform = m_pTop[i];

		while(pform)
		{
			Cform *pformNext = pform->m_pNext;
			if(pform->m_bDelete==true)
			{
				pform->UnlinkList();
				delete pform;
			}
			pform = pformNext;
		}
	}
}
//=============================================================================
// リスト内オブジェ更新
//=============================================================================
void Cform::UpdatePause(void)
{
	for(int i=0;i<NUM_PRIORITY;i++)
	{
		Cform *pform = m_pTop[i];

		while(pform)
		{
			Cform *pformNext = pform->m_pNext;

			if(pform->GetObjType()==OBJTYPE_PAUSE)
			{
				// オブジェクトの更新処理
				pform->Update();
			}

			pform = pformNext;
		}
	}
}
//=============================================================================
// リスト内オブジェ更新
//=============================================================================
void Cform::UpdateGameEnd(void)
{
	for(int i=0;i<NUM_PRIORITY;i++)
	{
		Cform *pform = m_pTop[i];

		while(pform)
		{
			Cform *pformNext = pform->m_pNext;

			if((!(pform->GetObjType()==OBJTYPE_PLAYER))&&(!(pform->GetObjType()==OBJTYPE_ENEMY))&&(!(pform->GetObjType()==OBJTYPE_TIMER)))
			{
				// オブジェクトの更新処理
				pform->Update();
			}
			pform = pformNext;
		}

		pform = m_pTop[i];

		while(pform)
		{
			Cform *pformNext = pform->m_pNext;
			if(pform->m_bDelete==true)
			{
				pform->UnlinkList();
				delete pform;
			}
			pform = pformNext;
		}
	}
}
//=============================================================================
// リスト内オブジェ描画
//=============================================================================
void Cform::DrawAll(D3DXMATRIX changeMtx,D3DXVECTOR3 rotCamera)
{
	for(int i=0;i<NUM_PRIORITY;i++)
	{
		Cform *pform = m_pTop[i];

		while(pform)
		{ 
			Cform *pformNext = pform->m_pNext;

			pform->SetRotCamera(rotCamera);

			pform->SetMtxView(changeMtx);

			// オブジェクトの描画処理
			pform->Draw();

			pform = pformNext;
		}
	}
}
//=============================================================================
// リスト内オブジェ描画
//=============================================================================
void Cform::DrawGame(D3DXMATRIX changeMtx,D3DXVECTOR3 rotCamera)
{
	for(int i=0;i<NUM_PRIORITY;i++)
	{
		Cform *pform = m_pTop[i];

		while(pform)
		{ 
			Cform *pformNext = pform->m_pNext;

			if(!(pform->GetObjType()==OBJTYPE_PAUSE))
			{
				pform->SetRotCamera(rotCamera);

				pform->SetMtxView(changeMtx);

				// オブジェクトの描画処理
				pform->Draw();
			}
			pform = pformNext;
		}
	}
}
//=============================================================================
// リスト内オブジェ描画
//=============================================================================
void Cform::DrawPause(D3DXMATRIX changeMtx,D3DXVECTOR3 rotCamera)
{
	for(int i=0;i<NUM_PRIORITY;i++)
	{
		Cform *pform = m_pTop[i];

		while(pform)
		{ 
			Cform *pformNext = pform->m_pNext;

			if(pform->GetObjType()==OBJTYPE_PAUSE)
			{
				pform->SetRotCamera(rotCamera);

				pform->SetMtxView(changeMtx);

				// オブジェクトの描画処理
				pform->Draw();
			}
			pform = pformNext;
		}
	}
}
//=============================================================================
// オブジェクトを破棄
//=============================================================================
void Cform::Release(void)
{
	// デリートフラグを立てる
	m_bDelete = true;
}

//=============================================================================
// オブジェクト全体を破棄
//=============================================================================
void Cform::ReleaseAll(void)
{
	for(int i=0;i<NUM_PRIORITY;i++)
	{
		Cform *pform = m_pTop[i];

		while(pform)
		{
			Cform *pformNext = pform->m_pNext;

			// オブジェクトの終了処理
			pform->Uninit();

			pform->UnlinkList();

			delete pform;

			pform = pformNext;
		}
	}
}
//=============================================================================
// リストに登録
//=============================================================================
void Cform::LinkList(int nPriority)
{
	// プライオリティを設定
	m_nPriority = nPriority;

	//リストの先頭が無い時
	if(!m_pTop[m_nPriority])
	{
		m_pTop[m_nPriority] = this;
	}
	//リストの現在が無い時
	if(!m_pCur[m_nPriority])
	{
		m_pCur[m_nPriority] = this;
	}
	//現在の次のリストに自分を
	m_pCur[m_nPriority]->m_pNext = this;

	//現在のリストが自分なら
	if(m_pCur[m_nPriority] == this)
	{
		m_pPrev = NULL;	
	}
	else
	{
		m_pPrev = m_pCur[m_nPriority];
	}
	//現在に自分を
	m_pCur[m_nPriority] = this;
	m_pNext = NULL;
}

//=============================================================================
// リストから削除
//=============================================================================
void Cform::UnlinkList(void)
{
	Cform *pform, *pformNext, *pformPrev;

	pform = m_pTop[m_nPriority];
	while(pform)
	{
		//次のインスタンスを保存
		pformNext = pform->m_pNext;

		if(pform == this)
		{
			if(pform->m_pPrev!=NULL)
			{
				//西條テク(アローアロー)
				//自分の前の次のやつを自分の次のやつに変更
				pform->m_pPrev->m_pNext = pform->m_pNext;
			}
			if(pform->m_pNext!=NULL)
			{
				//自分の次の前のやつを自分の前のやつに変更
				pform->m_pNext->m_pPrev = pform->m_pPrev;
			}
			if(pform == m_pTop[m_nPriority])
			{
				//
				m_pTop[m_nPriority] = pformNext;
			}
		}

		pform = pformNext;
	}
	// リストの現在位置(pCur)から先頭(pTop)に向かって辿っていく
	pform = m_pCur[m_nPriority];
	while(pform)
	{
		pformPrev = pform->m_pPrev;

		if(pform == this)
		{// 対象のオブジェクトが自分(this)の場合
			if(pform->m_pPrev)
			{// 対象のオブジェクトの前にオブジェクトが存在する場合
				// 自分(this)の前のオブジェクトの次のオブジェクトを自分(this)の次のオブジェクトにする
				pform->m_pPrev->m_pNext = pform->m_pNext;
			}
			if(pform->m_pNext)
			{// 対象のオブジェクトの次にオブジェクトが存在する場合
				// 自分(this)の次のオブジェクトの前のオブジェクトを自分(this)の前のオブジェクトのする
				pform->m_pNext->m_pPrev = pform->m_pPrev;
			}

			if(pform == m_pCur[m_nPriority])
			{// 対象のオブジェクトが現在のオブジェクト(pCur)の場合
				m_pCur[m_nPriority] = pformPrev;
			}
		}

		pform = pformPrev;
	}
}
/////////////EOF////////////