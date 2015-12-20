//=============================================================================
//
// MS_BuildFight [main.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"				
//描画処理に必要
#include "dinput.h"
#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW

#define DBG_NEW new(_NORMAL_BLOCK,__FILE__,__LINE__)

#define new DBG_NEW

#endif
#endif
//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#pragma comment (lib,"d3d9.lib")	//描画処理に必要
#pragma comment (lib,"d3dx9.lib")	//上の拡張ライブラリ
#pragma comment (lib,"dxguid.lib")	//DirectXコンポーネントに使用
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "winmm.lib")
//*****************************************************************************
// マクロ定義
//*****************************************************************************
// ２Ｄポリゴン頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// ３Ｄポリゴン頂点フォーマット( 頂点座標[3D] / 法線 / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)

#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr) = NULL; } }


#define	GRAVITY					(4.80f)		// 重力
#define	REGIST_MOVE				(0.55f)		// 抵抗値
#define	REGIST_MOVE_AIR			(0.95f)		// 抵抗値(空中)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3	vtx;	//頂点座標
	float		hrw;	//（中身は1.0f）
	D3DCOLOR	diffuse;//反射光
	D3DXVECTOR2	tex;	//テクスチャ座標
}VERTEX_2D;
// 上記３Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3	vtx;		// 頂点座標
	D3DXVECTOR3	nor;		// 法線ベクトル
	D3DCOLOR	diffuse;	// 反射光
	D3DXVECTOR2	tex;		// テクスチャ座標
} VERTEX_3D;

typedef struct
{
	LPDIRECT3DPIXELSHADER9 ps;			//ピクセルシェーダー
	LPD3DXCONSTANTTABLE    psc;		//ピクセルシェーダー用コンスタントテーブル
	LPDIRECT3DVERTEXSHADER9 vs;		//バーテックスシェーダー
	LPD3DXCONSTANTTABLE    vsc;		//バーテックスシェーダー用コンスタントテーブル
}SHADER_SET;

typedef bool NS;

#define N	(true)
#define S	(false)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//カッコイイ！SafeRelease関数!! #defineマクロなんてもう古い
//使い方：＆をつけてね。
template<class Interface>
inline void SafeRelease(Interface** ppInterfaceToRelease)
{
	if(*ppInterfaceToRelease!=nullptr){
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease)=nullptr;
	}
}
void GameEnd(void);
#endif