//=============================================================================
//
// MS_BuildFight [debugproc.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#include <stdio.h>
#include <stdarg.h>
#include "Debugproc.h"
#include "Maneger.h"
//*****************************************************************************
// 静的変数
//*****************************************************************************
LPD3DXFONT CDebugProc::m_pD3DXFont = NULL;
char CDebugProc::m_aStr[1028] = {"\0"};
bool CDebugProc::m_bDisp = true;

//=============================================================================
// CDebugProcコンストラクタ
//=============================================================================
CDebugProc::CDebugProc()
{
	// バッファクリア
	memset(m_aStr, 0, sizeof m_aStr);
}

//=============================================================================
// CDebugProcデストラクタ
//=============================================================================
CDebugProc::~CDebugProc()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
void CDebugProc::Init(LPDIRECT3DDEVICE9 pDevice)
{
	// 情報表示用フォントを初期化
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
					OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pD3DXFont);
}

//=============================================================================
// 開放処理
//=============================================================================
void CDebugProc::Uninit(void)
{
	if(m_pD3DXFont != NULL)
	{// 情報表示用フォントの開放
		m_pD3DXFont->Release();
		m_pD3DXFont = NULL;
	}
}

//=============================================================================
// 書き込み処理
//=============================================================================
void CDebugProc::Print(char *fmt,...)
{
#ifdef _DEBUG
	va_list list;
	char *pCur;
	char aBuf[256]={"\0"};
	char aWk[32];

	va_start(list, fmt);

	pCur = fmt;
	for( ; *pCur; ++pCur)
	{
		if(*pCur != '%')
		{
			sprintf(aWk, "%c", *pCur);
		}
		else
		{
			pCur++;

			switch(*pCur)
			{
			case 'd':
				sprintf(aWk, "%d", va_arg(list, int));
				break;

			case 'f':
				sprintf(aWk, "%f", va_arg(list, double));		// double型で指定
				break;

			case 's':
				sprintf(aWk, "%s", va_arg(list, char*));
				break;

			case 'c':
				sprintf(aWk, "%c", va_arg(list, char));
				break;

			default:
				sprintf(aWk, "%c", *pCur);
				break;
			}
		}
		strcat(aBuf, aWk);
	}

	va_end(list);

	if((strlen(m_aStr) + strlen(aBuf)) < sizeof m_aStr - 1)
	{
		strcat(m_aStr, aBuf);
	}
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void CDebugProc::Draw(void)
{
#ifdef _DEBUG
	if(m_bDisp)
	{
		RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

		m_pD3DXFont->DrawText(NULL, m_aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

		// バッファクリア
		memset(m_aStr, 0, sizeof m_aStr);
	}
#endif
}

