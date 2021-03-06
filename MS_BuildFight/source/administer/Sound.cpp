//=============================================================================
//
// MS_BuildFight [CSound.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "Sound.h"

// 各音素材のパラメータ
PARAM g_aParam[SOUND_LABEL_MAX] =
{
	{ "data/BGM/BGM_TITLE.wav",		true },
	{ "data/BGM/BGM_SELECT.wav",	true },
	{ "data/BGM/BGM_GAME.wav",		true },
	{ "data/BGM/BGM_RESULT.wav",	true },
	{ "data/BGM/INFINITE_SKY.wav",	true },
	{ "data/SE/cursor.wav",			false },
	{ "data/SE/button.wav",			false },
	{ "data/SE/prayer1.wav",		false },
	{ "data/SE/sceneswitch1.wav",	false },
	{ "data/SE/shine1.wav",			false },
	{ "data/SE/trumpet1.wav",		false },
	{ "data/SE/shot.wav",			false },
	{ "data/SE/select.wav",			false },
};

PARAM g_aParamVoice[CHARACTER_MAX][VOICE_LABEL_MAX] =
{
	{
		{ "data/SE/VOICE/rosa/TitleCall_rosa.wav", false },
		{ "data/SE/VOICE/rosa/result_rosa_lose.wav", false },
		{ "data/SE/VOICE/rosa/result_rosa_win.wav", false },
		{ "data/SE/VOICE/rosa/rosa_harf_00.wav", false },
		{ "data/SE/VOICE/rosa/rosa_harf_01.wav", false },
		{ "data/SE/VOICE/rosa/rosa_harf_02.wav", false },
		{ "data/SE/VOICE/rosa/rosa_lose_00.wav", false },
		{ "data/SE/VOICE/rosa/rosa_lose_01.wav", false },
		{ "data/SE/VOICE/rosa/rosa_result.wav", false },
		{ "data/SE/VOICE/rosa/rosa_start_00.wav", false },
		{ "data/SE/VOICE/rosa/rosa_start_01.wav", false },
		{ "data/SE/VOICE/rosa/rosa_start_02.wav", false },
		{ "data/SE/VOICE/rosa/rosa_win_00.wav", false },
		{ "data/SE/VOICE/rosa/rosa_win_01.wav", false },
		{ "data/SE/VOICE/rosa/shot.wav", false },
		{ "data/SE/VOICE/rosa/SpecialTrick_rosa.wav", false },
		{ "data/SE/VOICE/rosa/TitleCall_rosa.wav", false },
	},
	{
		{ "data/SE/VOICE/lila/TitleCall_lila.wav", false },
		{ "data/SE/VOICE/lila/lila_half01.wav", false },
		{ "data/SE/VOICE/lila/lila_losa00.wav", false },
		{ "data/SE/VOICE/lila/lila_losa01.wav", false },
		{ "data/SE/VOICE/lila/lila_lose0.wav", false },
		{ "data/SE/VOICE/lila/lila_shot.wav", false },
		{ "data/SE/VOICE/lila/lila_shot2.wav", false },
		{ "data/SE/VOICE/lila/lila_start_start00.wav", false },
		{ "data/SE/VOICE/lila/lila_start_start01.wav", false },
		{ "data/SE/VOICE/lila/lila_start_start02.wav", false },
		{ "data/SE/VOICE/lila/lila_start_win1.wav", false },
		{ "data/SE/VOICE/lila/lila_start_win2.wav", false },
		{ "data/SE/VOICE/lila/result_lila_lose.wav", false },
		{ "data/SE/VOICE/lila/result_lila_win.wav", false },
		{ "data/SE/VOICE/lila/SpecialTrick_lila.wav", false },
		{ "data/SE/VOICE/lila/TitleCall_lila.wav", false },
		{ "data/SE/VOICE/lila/TitleCall_lila.wav", false },
	},
	{
		{ "data/SE/VOICE/licht/TitleCall_licht.wav", false },
		{ "data/SE/VOICE/licht/ojyo_harf00.wav", false },
		{ "data/SE/VOICE/licht/ojyo_harf01.wav", false },
		{ "data/SE/VOICE/licht/ojyo_lose00.wav", false },
		{ "data/SE/VOICE/licht/ojyo_lose01.wav", false },
		{ "data/SE/VOICE/licht/ojyo_shot.wav", false },
		{ "data/SE/VOICE/licht/ojyo_shot00.wav", false },
		{ "data/SE/VOICE/licht/ojyo_shot01.wav", false },
		{ "data/SE/VOICE/licht/ojyo_shot02.wav", false },
		{ "data/SE/VOICE/licht/ojyo_shot03.wav", false },
		{ "data/SE/VOICE/licht/ojyo_start00.wav", false },
		{ "data/SE/VOICE/licht/ojyo_start01.wav", false },
		{ "data/SE/VOICE/licht/ojyo_win00.wav", false },
		{ "data/SE/VOICE/licht/ojyo_win01.wav", false },
		{ "data/SE/VOICE/licht/result_licht_lose.wav", false },
		{ "data/SE/VOICE/licht/result_licht_win.wav", false },
		{ "data/SE/VOICE/licht/SpecialTrick_licht.wav", false },
	},
	{
		{ "data/SE/VOICE/licht/TitleCall_licht.wav", false },
		{ "data/SE/VOICE/licht/ojyo_harf00.wav", false },
		{ "data/SE/VOICE/licht/ojyo_harf01.wav", false },
		{ "data/SE/VOICE/licht/ojyo_lose00.wav", false },
		{ "data/SE/VOICE/licht/ojyo_lose01.wav", false },
		{ "data/SE/VOICE/licht/ojyo_shot.wav", false },
		{ "data/SE/VOICE/licht/ojyo_shot00.wav", false },
		{ "data/SE/VOICE/licht/ojyo_shot01.wav", false },
		{ "data/SE/VOICE/licht/ojyo_shot02.wav", false },
		{ "data/SE/VOICE/licht/ojyo_shot03.wav", false },
		{ "data/SE/VOICE/licht/ojyo_start00.wav", false },
		{ "data/SE/VOICE/licht/ojyo_start01.wav", false },
		{ "data/SE/VOICE/licht/ojyo_win00.wav", false },
		{ "data/SE/VOICE/licht/ojyo_win01.wav", false },
		{ "data/SE/VOICE/licht/result_licht_lose.wav", false },
		{ "data/SE/VOICE/licht/result_licht_win.wav", false },
		{ "data/SE/VOICE/licht/SpecialTrick_licht.wav", false },
	}

};
//=============================================================================
// コンストラクタ
//=============================================================================
CSound :: CSound(void)
{
	g_pXAudio2 = NULL;
	g_pMasteringVoice = NULL;

	for(int i=0;i<SOUND_LABEL_MAX;i++)
	{
		g_apSourceVoice[i] = NULL;
		g_apDataAudio[i] = NULL;
		g_aSizeAudio[i] = NULL;
	}
	for(int i=0;i<VOICE_LABEL_MAX*CHARACTER_MAX;i++)
	{
		g_apSourceVoice2[i] = NULL;
		g_apDataAudio2[i] = NULL;
		g_aSizeAudio2[i] = NULL;
	}
}
//=============================================================================
// デストラクタ
//=============================================================================
CSound :: ~CSound(void)
{
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CSound :: Init(HWND hWnd)
{
	HRESULT hr;

	// COMライブラリの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&g_pXAudio2, 0);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2オブジェクトの作成に失敗！", "警告！", MB_ICONWARNING);

		// COMライブラリの終了処理
		CoUninitialize();
		return E_FAIL;
	}
	
	// マスターボイスの生成
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "マスターボイスの生成に失敗！", "警告！", MB_ICONWARNING);

		if(g_pXAudio2)
		{
			// XAudio2オブジェクトの開放
			g_pXAudio2->Release();
			g_pXAudio2 = NULL;
		}

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}
	if (g_aParam[0].pFilename != NULL)
	{
		// サウンドデータの初期化
		for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
		{
			HANDLE hFile;
			DWORD dwChunkSize = 0;
			DWORD dwChunkPosition = 0;
			DWORD dwFiletype;
			WAVEFORMATEXTENSIBLE wfx;
			XAUDIO2_BUFFER buffer;

			// バッファのクリア
			memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
			memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

			// サウンドデータファイルの生成
			hFile = CreateFile(g_aParam[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
			if (hFile == INVALID_HANDLE_VALUE)
			{
				MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(1)", "警告！", MB_ICONWARNING);
				return HRESULT_FROM_WIN32(GetLastError());
			}
			if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタを先頭に移動
				MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(2)", "警告！", MB_ICONWARNING);
				return HRESULT_FROM_WIN32(GetLastError());
			}

			// WAVEファイルのチェック
			hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
			if (FAILED(hr))
			{
				MessageBox(hWnd, "WAVEファイルのチェックに失敗！(1)", "警告！", MB_ICONWARNING);
				return S_FALSE;
			}
			hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
			if (FAILED(hr))
			{
				MessageBox(hWnd, "WAVEファイルのチェックに失敗！(2)", "警告！", MB_ICONWARNING);
				return S_FALSE;
			}
			if (dwFiletype != 'EVAW')
			{
				MessageBox(hWnd, "WAVEファイルのチェックに失敗！(3)", "警告！", MB_ICONWARNING);
				return S_FALSE;
			}

			// フォーマットチェック
			hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
			if (FAILED(hr))
			{
				MessageBox(hWnd, "フォーマットチェックに失敗！(1)", "警告！", MB_ICONWARNING);
				return S_FALSE;
			}
			hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
			if (FAILED(hr))
			{
				MessageBox(hWnd, "フォーマットチェックに失敗！(2)", "警告！", MB_ICONWARNING);
				return S_FALSE;
			}

			// オーディオデータ読み込み
			hr = CheckChunk(hFile, 'atad', &g_aSizeAudio[nCntSound], &dwChunkPosition);
			if (FAILED(hr))
			{
				MessageBox(hWnd, "オーディオデータ読み込みに失敗！(1)", "警告！", MB_ICONWARNING);
				return S_FALSE;
			}
			g_apDataAudio[nCntSound] = (BYTE*)malloc(g_aSizeAudio[nCntSound]);
			hr = ReadChunkData(hFile, g_apDataAudio[nCntSound], g_aSizeAudio[nCntSound], dwChunkPosition);
			if (FAILED(hr))
			{
				MessageBox(hWnd, "オーディオデータ読み込みに失敗！(2)", "警告！", MB_ICONWARNING);
				return S_FALSE;
			}

			// ソースボイスの生成
			hr = g_pXAudio2->CreateSourceVoice(&g_apSourceVoice[nCntSound], &(wfx.Format));
			if (FAILED(hr))
			{
				MessageBox(hWnd, "ソースボイスの生成に失敗！", "警告！", MB_ICONWARNING);
				return S_FALSE;
			}

			memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
			buffer.AudioBytes = g_aSizeAudio[nCntSound];
			buffer.pAudioData = g_apDataAudio[nCntSound];
			buffer.Flags = XAUDIO2_END_OF_STREAM;
			if (g_aParam[nCntSound].bLoop == true)
			{
				buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
				buffer.LoopBegin = 0;
				buffer.LoopLength = 0;

			}
			else
			{
				buffer.LoopCount = 0;
			}

			// オーディオバッファの登録
			g_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);
		}
	}

	int nCntNum=0;

	if (g_aParamVoice[0][0].pFilename != NULL)
	{
		// サウンドデータの初期化
		for (int nCntChara = 0; nCntChara < CHARACTER_MAX; nCntChara++)
		{
			for (int nCntSound = 0; nCntSound < VOICE_LABEL_MAX; nCntSound++)
			{

				HANDLE hFile;
				DWORD dwChunkSize = 0;
				DWORD dwChunkPosition = 0;
				DWORD dwFiletype;
				WAVEFORMATEXTENSIBLE wfx;
				XAUDIO2_BUFFER buffer;

				// バッファのクリア
				memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
				memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

				// サウンドデータファイルの生成
				hFile = CreateFile(g_aParamVoice[nCntChara][nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
				if (hFile == INVALID_HANDLE_VALUE)
				{
					MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(1)", "警告！", MB_ICONWARNING);
					return HRESULT_FROM_WIN32(GetLastError());
				}
				if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
				{// ファイルポインタを先頭に移動
					MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(2)", "警告！", MB_ICONWARNING);
					return HRESULT_FROM_WIN32(GetLastError());
				}

				// WAVEファイルのチェック
				hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
				if (FAILED(hr))
				{
					MessageBox(hWnd, "WAVEファイルのチェックに失敗！(1)", "警告！", MB_ICONWARNING);
					return S_FALSE;
				}
				hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
				if (FAILED(hr))
				{
					MessageBox(hWnd, "WAVEファイルのチェックに失敗！(2)", "警告！", MB_ICONWARNING);
					return S_FALSE;
				}
				if (dwFiletype != 'EVAW')
				{
					MessageBox(hWnd, "WAVEファイルのチェックに失敗！(3)", "警告！", MB_ICONWARNING);
					return S_FALSE;
				}

				// フォーマットチェック
				hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
				if (FAILED(hr))
				{
					MessageBox(hWnd, "フォーマットチェックに失敗！(1)", "警告！", MB_ICONWARNING);
					return S_FALSE;
				}
				hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
				if (FAILED(hr))
				{
					MessageBox(hWnd, "フォーマットチェックに失敗！(2)", "警告！", MB_ICONWARNING);
					return S_FALSE;
				}

				// オーディオデータ読み込み
				hr = CheckChunk(hFile, 'atad', &g_aSizeAudio2[nCntNum], &dwChunkPosition);
				if (FAILED(hr))
				{
					MessageBox(hWnd, "オーディオデータ読み込みに失敗！(1)", "警告！", MB_ICONWARNING);
					return S_FALSE;
				}

				g_apDataAudio2[nCntNum] = (BYTE*)malloc(g_aSizeAudio2[nCntNum]);
				hr = ReadChunkData(hFile, g_apDataAudio2[nCntNum], g_aSizeAudio2[nCntNum], dwChunkPosition);
				if (FAILED(hr))
				{
					MessageBox(hWnd, "オーディオデータ読み込みに失敗！(2)", "警告！", MB_ICONWARNING);
					return S_FALSE;
				}

				// ソースボイスの生成
				hr = g_pXAudio2->CreateSourceVoice(&g_apSourceVoice2[nCntNum], &(wfx.Format));
				if (FAILED(hr))
				{
					MessageBox(hWnd, "ソースボイスの生成に失敗！", "警告！", MB_ICONWARNING);
					return S_FALSE;
				}

				memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
				buffer.AudioBytes = g_aSizeAudio2[nCntNum];
				buffer.pAudioData = g_apDataAudio2[nCntNum];
				buffer.Flags = XAUDIO2_END_OF_STREAM;
				if (g_aParamVoice[nCntChara][nCntSound].bLoop == true)
				{
					buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
					buffer.LoopBegin = 0;
					buffer.LoopLength = 0;

				}
				else
				{
					buffer.LoopCount = 0;
				}

				// オーディオバッファの登録
				g_apSourceVoice2[nCntNum]->SubmitSourceBuffer(&buffer);

				nCntNum++;
			}
		}
	}

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CSound :: Uninit(void)
{
	// 一時停止
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound])
		{
			// 一時停止
			g_apSourceVoice[nCntSound]->Stop(0);
	
			// ソースボイスの破棄
			g_apSourceVoice[nCntSound]->DestroyVoice();
			g_apSourceVoice[nCntSound] = NULL;
	
			// オーディオデータの開放
			free(g_apDataAudio[nCntSound]);
			g_apDataAudio[nCntSound] = NULL;
		}
	}

	for(int nCntSound = 0; nCntSound < VOICE_LABEL_MAX*CHARACTER_MAX; nCntSound++)
	{
		if(g_apSourceVoice2[nCntSound])
		{
			// 一時停止
			g_apSourceVoice2[nCntSound]->Stop(0);
	
			// ソースボイスの破棄
			g_apSourceVoice2[nCntSound]->DestroyVoice();
			g_apSourceVoice2[nCntSound] = NULL;
	
			// オーディオデータの開放
			free(g_apDataAudio2[nCntSound]);
			g_apDataAudio2[nCntSound] = NULL;
		}
	}
	
	// マスターボイスの破棄
	g_pMasteringVoice->DestroyVoice();
	g_pMasteringVoice = NULL;
	
	if(g_pXAudio2)
	{
		// XAudio2オブジェクトの開放
		g_pXAudio2->Release();
		g_pXAudio2 = NULL;
	}
	
	// COMライブラリの終了処理
	CoUninitialize();
}
//=============================================================================
// 再生
//=============================================================================
HRESULT CSound :: Play(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_aSizeAudio[label];
	buffer.pAudioData = g_apDataAudio[label];
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	if(g_aParam[label].bLoop==true)
	{
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
		buffer.LoopBegin = 0;
		buffer.LoopLength = 0;

	}else
	{
		buffer.LoopCount  = 0;
	}

	// 状態取得
	g_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_apSourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		g_apSourceVoice[label]->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	g_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// 再生
	g_apSourceVoice[label]->Start(0);

	return S_OK;
}
//=============================================================================
// 再生
//=============================================================================
HRESULT CSound :: PlayVoice(int nType,VOICE_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_aSizeAudio2[label+(VOICE_LABEL)(nType*VOICE_LABEL_MAX)];
	buffer.pAudioData = g_apDataAudio2[label+(VOICE_LABEL)(nType*VOICE_LABEL_MAX)];
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	if(g_aParamVoice[nType][label].bLoop==true)
	{
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
		buffer.LoopBegin = 0;
		buffer.LoopLength = 0;

	}else
	{
		buffer.LoopCount  = 0;
	}

	// 状態取得
	g_apSourceVoice2[label+(VOICE_LABEL)(nType*VOICE_LABEL_MAX)]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_apSourceVoice2[label+(VOICE_LABEL)(nType*VOICE_LABEL_MAX)]->Stop(0);

		// オーディオバッファの削除
		g_apSourceVoice2[label+(VOICE_LABEL)(nType*VOICE_LABEL_MAX)]->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	g_apSourceVoice2[label+(VOICE_LABEL)(nType*VOICE_LABEL_MAX)]->SubmitSourceBuffer(&buffer);

	// 再生
	g_apSourceVoice2[label+(VOICE_LABEL)(nType*VOICE_LABEL_MAX)]->Start(0);

	return S_OK;
}
//=============================================================================
// 停止
//=============================================================================
void CSound :: Stop(void)
{
	// 一時停止
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound])
		{
			// 一時停止
			g_apSourceVoice[nCntSound]->Stop(0);
		}
	}
	// 一時停止
	for(int nCntSound = 0; nCntSound < VOICE_LABEL_MAX*CHARACTER_MAX; nCntSound++)
	{
		if(g_apSourceVoice2[nCntSound])
		{
			// 一時停止
			g_apSourceVoice2[nCntSound]->Stop(0);
		}
	}
}
//=============================================================================
// 停止
//=============================================================================
void CSound :: Stop(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	g_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_apSourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		g_apSourceVoice[label]->FlushSourceBuffers();
	}
}
//=============================================================================
// ボイス停止
//=============================================================================
void CSound :: StopVoice(int nType,VOICE_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	g_apSourceVoice2[label+(VOICE_LABEL)(nType*VOICE_LABEL_MAX)]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_apSourceVoice2[label+(VOICE_LABEL)(nType*VOICE_LABEL_MAX)]->Stop(0);

		// オーディオバッファの削除
		g_apSourceVoice2[label+(VOICE_LABEL)(nType*VOICE_LABEL_MAX)]->FlushSourceBuffers();
	}
}
//=============================================================================
// チャンクのチェック
//=============================================================================
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;
	
	if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if(dwChunkType == format)
		{
			*pChunkSize         = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if(dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}
	
	return S_OK;
}

//=============================================================================
// チャンクデータの読み込み
//=============================================================================
HRESULT CSound::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}
/////////////EOF////////////