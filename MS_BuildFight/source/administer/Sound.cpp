//=============================================================================
//
// MS_BuildFight [CSound.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "Sound.h"

// �e���f�ނ̃p�����[�^
PARAM g_aParam[SOUND_LABEL_MAX] =
{
	{ "data/BGM/BGM_TITLE.wav"		,true},
	{ "data/BGM/BGM_SELECT.wav"		,true},
	{ "data/BGM/BGM_GAME.wav"		,true},
	{ "data/BGM/BGM_RESULT.wav"		,true},
	{ "data/BGM/INFINITE_SKY.wav"	,true},
	{ "data/SE/cursor.wav"			,false},
	{ "data/SE/button.wav"			,false },
	{ "data/SE/prayer1.wav"			,false },
	{ "data/SE/sceneswitch1.wav"	,false },
	{ "data/SE/shine1.wav"			,false },
	{ "data/SE/trumpet1.wav"		,false },


};

PARAM g_aParamVoice[CHARACTER_MAX][VOICE_LABEL_MAX] =
{
};
//=============================================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//=============================================================================
CSound :: ~CSound(void)
{
}
//=============================================================================
// ������
//=============================================================================
HRESULT CSound :: Init(HWND hWnd)
{
	HRESULT hr;

	// COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&g_pXAudio2, 0);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// COM���C�u�����̏I������
		CoUninitialize();
		return E_FAIL;
	}
	
	// �}�X�^�[�{�C�X�̐���
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�}�X�^�[�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);

		if(g_pXAudio2)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			g_pXAudio2->Release();
			g_pXAudio2 = NULL;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}
	if (g_aParam[0].pFilename != NULL)
	{
		// �T�E���h�f�[�^�̏�����
		for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
		{
			HANDLE hFile;
			DWORD dwChunkSize = 0;
			DWORD dwChunkPosition = 0;
			DWORD dwFiletype;
			WAVEFORMATEXTENSIBLE wfx;
			XAUDIO2_BUFFER buffer;

			// �o�b�t�@�̃N���A
			memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
			memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

			// �T�E���h�f�[�^�t�@�C���̐���
			hFile = CreateFile(g_aParam[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
			if (hFile == INVALID_HANDLE_VALUE)
			{
				MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
				return HRESULT_FROM_WIN32(GetLastError());
			}
			if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^��擪�Ɉړ�
				MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
				return HRESULT_FROM_WIN32(GetLastError());
			}

			// WAVE�t�@�C���̃`�F�b�N
			hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
			if (FAILED(hr))
			{
				MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
				return S_FALSE;
			}
			hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
			if (FAILED(hr))
			{
				MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
				return S_FALSE;
			}
			if (dwFiletype != 'EVAW')
			{
				MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)", "�x���I", MB_ICONWARNING);
				return S_FALSE;
			}

			// �t�H�[�}�b�g�`�F�b�N
			hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
			if (FAILED(hr))
			{
				MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
				return S_FALSE;
			}
			hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
			if (FAILED(hr))
			{
				MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
				return S_FALSE;
			}

			// �I�[�f�B�I�f�[�^�ǂݍ���
			hr = CheckChunk(hFile, 'atad', &g_aSizeAudio[nCntSound], &dwChunkPosition);
			if (FAILED(hr))
			{
				MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
				return S_FALSE;
			}
			g_apDataAudio[nCntSound] = (BYTE*)malloc(g_aSizeAudio[nCntSound]);
			hr = ReadChunkData(hFile, g_apDataAudio[nCntSound], g_aSizeAudio[nCntSound], dwChunkPosition);
			if (FAILED(hr))
			{
				MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
				return S_FALSE;
			}

			// �\�[�X�{�C�X�̐���
			hr = g_pXAudio2->CreateSourceVoice(&g_apSourceVoice[nCntSound], &(wfx.Format));
			if (FAILED(hr))
			{
				MessageBox(hWnd, "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);
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

			// �I�[�f�B�I�o�b�t�@�̓o�^
			g_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);
		}
	}

	int nCntNum=0;

	if (g_aParamVoice[0][0].pFilename != NULL)
	{
		// �T�E���h�f�[�^�̏�����
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

				// �o�b�t�@�̃N���A
				memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
				memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

				// �T�E���h�f�[�^�t�@�C���̐���
				hFile = CreateFile(g_aParamVoice[nCntChara][nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
				if (hFile == INVALID_HANDLE_VALUE)
				{
					MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
					return HRESULT_FROM_WIN32(GetLastError());
				}
				if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
				{// �t�@�C���|�C���^��擪�Ɉړ�
					MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
					return HRESULT_FROM_WIN32(GetLastError());
				}

				// WAVE�t�@�C���̃`�F�b�N
				hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
				if (FAILED(hr))
				{
					MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
					return S_FALSE;
				}
				hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
				if (FAILED(hr))
				{
					MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
					return S_FALSE;
				}
				if (dwFiletype != 'EVAW')
				{
					MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)", "�x���I", MB_ICONWARNING);
					return S_FALSE;
				}

				// �t�H�[�}�b�g�`�F�b�N
				hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
				if (FAILED(hr))
				{
					MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
					return S_FALSE;
				}
				hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
				if (FAILED(hr))
				{
					MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
					return S_FALSE;
				}

				// �I�[�f�B�I�f�[�^�ǂݍ���
				hr = CheckChunk(hFile, 'atad', &g_aSizeAudio2[nCntNum], &dwChunkPosition);
				if (FAILED(hr))
				{
					MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
					return S_FALSE;
				}

				g_apDataAudio2[nCntNum] = (BYTE*)malloc(g_aSizeAudio2[nCntNum]);
				hr = ReadChunkData(hFile, g_apDataAudio2[nCntNum], g_aSizeAudio2[nCntNum], dwChunkPosition);
				if (FAILED(hr))
				{
					MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
					return S_FALSE;
				}

				// �\�[�X�{�C�X�̐���
				hr = g_pXAudio2->CreateSourceVoice(&g_apSourceVoice2[nCntNum], &(wfx.Format));
				if (FAILED(hr))
				{
					MessageBox(hWnd, "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);
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

				// �I�[�f�B�I�o�b�t�@�̓o�^
				g_apSourceVoice2[nCntNum]->SubmitSourceBuffer(&buffer);

				nCntNum++;
			}
		}
	}

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CSound :: Uninit(void)
{
	// �ꎞ��~
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound])
		{
			// �ꎞ��~
			g_apSourceVoice[nCntSound]->Stop(0);
	
			// �\�[�X�{�C�X�̔j��
			g_apSourceVoice[nCntSound]->DestroyVoice();
			g_apSourceVoice[nCntSound] = NULL;
	
			// �I�[�f�B�I�f�[�^�̊J��
			free(g_apDataAudio[nCntSound]);
			g_apDataAudio[nCntSound] = NULL;
		}
	}

	for(int nCntSound = 0; nCntSound < VOICE_LABEL_MAX*CHARACTER_MAX; nCntSound++)
	{
		if(g_apSourceVoice2[nCntSound])
		{
			// �ꎞ��~
			g_apSourceVoice2[nCntSound]->Stop(0);
	
			// �\�[�X�{�C�X�̔j��
			g_apSourceVoice2[nCntSound]->DestroyVoice();
			g_apSourceVoice2[nCntSound] = NULL;
	
			// �I�[�f�B�I�f�[�^�̊J��
			free(g_apDataAudio2[nCntSound]);
			g_apDataAudio2[nCntSound] = NULL;
		}
	}
	
	// �}�X�^�[�{�C�X�̔j��
	g_pMasteringVoice->DestroyVoice();
	g_pMasteringVoice = NULL;
	
	if(g_pXAudio2)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		g_pXAudio2->Release();
		g_pXAudio2 = NULL;
	}
	
	// COM���C�u�����̏I������
	CoUninitialize();
}
//=============================================================================
// �Đ�
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

	// ��Ԏ擾
	g_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_apSourceVoice[label]->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	g_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// �Đ�
	g_apSourceVoice[label]->Start(0);

	return S_OK;
}
//=============================================================================
// �Đ�
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

	// ��Ԏ擾
	g_apSourceVoice2[label+(VOICE_LABEL)(nType*VOICE_LABEL_MAX)]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_apSourceVoice2[label+(VOICE_LABEL)(nType*VOICE_LABEL_MAX)]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_apSourceVoice2[label+(VOICE_LABEL)(nType*VOICE_LABEL_MAX)]->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	g_apSourceVoice2[label+(VOICE_LABEL)(nType*VOICE_LABEL_MAX)]->SubmitSourceBuffer(&buffer);

	// �Đ�
	g_apSourceVoice2[label+(VOICE_LABEL)(nType*VOICE_LABEL_MAX)]->Start(0);

	return S_OK;
}
//=============================================================================
// ��~
//=============================================================================
void CSound :: Stop(void)
{
	// �ꎞ��~
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound])
		{
			// �ꎞ��~
			g_apSourceVoice[nCntSound]->Stop(0);
		}
	}
	// �ꎞ��~
	for(int nCntSound = 0; nCntSound < VOICE_LABEL_MAX*CHARACTER_MAX; nCntSound++)
	{
		if(g_apSourceVoice2[nCntSound])
		{
			// �ꎞ��~
			g_apSourceVoice2[nCntSound]->Stop(0);
		}
	}
}
//=============================================================================
// ��~
//=============================================================================
void CSound :: Stop(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	g_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_apSourceVoice[label]->FlushSourceBuffers();
	}
}
//=============================================================================
// �{�C�X��~
//=============================================================================
void CSound :: StopVoice(int nType,VOICE_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	g_apSourceVoice2[label+(VOICE_LABEL)(nType*VOICE_LABEL_MAX)]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_apSourceVoice2[label+(VOICE_LABEL)(nType*VOICE_LABEL_MAX)]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_apSourceVoice2[label+(VOICE_LABEL)(nType*VOICE_LABEL_MAX)]->FlushSourceBuffers();
	}
}
//=============================================================================
// �`�����N�̃`�F�b�N
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
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
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
// �`�����N�f�[�^�̓ǂݍ���
//=============================================================================
HRESULT CSound::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}
/////////////EOF////////////