//=============================================================================
//
// MS_BuildFight [main.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "common.h"
#include "administer/Maneger.h"
#include "administer/Renderer.h"
#include "administer/debugproc.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
bool GameEndFlag;
//=============================================================================
// メイン関数
//  (WINAPI : Win32API関数を呼び出す時の規約)
//  hInstance     : このアプリケーションのインスタンスハンドル(識別子)
//  hPrevInstance : 常にNULL(16bit時代の名残り)
//  lpCmdLine     : コマンドラインから受け取った引数へのポインタ
//  nCmdShow      : アプリケーションの初期ウインドウ表示方法の指定
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//メモリリークチェック
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//マネージャー
	CManager* pManeger;
#ifdef _DEBUG
	int nCountFPS = 0;								// FPSカウンタ
#endif

	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	//ウインドウの準備
	WNDCLASSEX wcex=
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		"window",
		NULL
	};

	HWND hwnd;
	MSG msg;
	GameEndFlag=false;

	//ウインドウの設定
	RegisterClassEx(&wcex);

	//ウインドウの作成
	hwnd=CreateWindowEx(
				0,
				"window",
				"起動外骨格ガンナイト-オーバードバーサス",
				WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				SCREEN_WIDTH,
				SCREEN_HEIGHT,
				NULL,
				NULL,
				hInstance,
				NULL);

	//フレームカウント初期化
	timeBeginPeriod(1);				// 分解能を設定
	dwExecLastTime = timeGetTime();
	dwFPSLastTime = dwExecLastTime;
	dwCurrentTime = 0;
	dwFrameCount = 0;

	//マネージャーの初期化
	pManeger = new CManager;
	pManeger->Init(hInstance,hwnd,TRUE);

	//ウインドウの表示
	ShowWindow(hwnd,nCmdShow);

	//ウインドウの更新
	UpdateWindow(hwnd);

	// メッセージループ
	while(true)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5秒ごとに実行
			{
#ifdef _DEBUG
				nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
#ifdef _DEBUG
				CDebugProc::Print("FPS:%d\n", nCountFPS);
#endif
				dwExecLastTime = dwCurrentTime;

				// 更新処理
				pManeger->Update();

				// 描画処理
				pManeger->Draw();

				dwFrameCount++;

				if(GameEndFlag)
				{
					DestroyWindow(hwnd);
				}
			}
		}
	}

	timeEndPeriod(1);				// 分解能を戻す

	// ウィンドウクラスの登録を解除
	UnregisterClass("window", wcex.hInstance);

	pManeger->Uninit();

	if(pManeger!=NULL)
	{
		delete pManeger;
		pManeger=NULL;
	}

	return (int)msg.wParam;
}
//=============================================================================
// ウインドウプロシージャ
//  (CALLBACK : Win32API関数を呼び出す時の規約)
//  hWnd   : ウィンドウのハンドル
//  uMsg   : メッセージの識別子
//  wParam : メッセージの最初のパラメータ
//  lParam : メッセージの2番目のパラメータ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)//関数の名前を変えても大丈夫
{

	//イベントを処理する関数
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);									// "WM_QUIT"メッセージを返す
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);		// 既定の処理を提供
}
void GameEnd(void)
{
	GameEndFlag=true;
}