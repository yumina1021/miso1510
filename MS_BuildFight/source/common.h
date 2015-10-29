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
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"				
//�`�揈���ɕK�v
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
// ���C�u�����̃����N
//*****************************************************************************
#pragma comment (lib,"d3d9.lib")	//�`�揈���ɕK�v
#pragma comment (lib,"d3dx9.lib")	//��̊g�����C�u����
#pragma comment (lib,"dxguid.lib")	//DirectX�R���|�[�l���g�Ɏg�p
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "winmm.lib")
//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �Q�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// �R�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@�� / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define SCREEN_WIDTH	(1300)
#define SCREEN_HEIGHT	(750)

#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr) = NULL; } }


#define	GRAVITY					(4.80f)		// �d��
#define	REGIST_MOVE				(0.55f)		// ��R�l
#define	REGIST_MOVE_AIR			(0.95f)		// ��R�l(��)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3	vtx;	//���_���W
	float		hrw;	//�i���g��1.0f�j
	D3DCOLOR	diffuse;//���ˌ�
	D3DXVECTOR2	tex;	//�e�N�X�`�����W
}VERTEX_2D;
// ��L�R�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3	vtx;		// ���_���W
	D3DXVECTOR3	nor;		// �@���x�N�g��
	D3DCOLOR	diffuse;	// ���ˌ�
	D3DXVECTOR2	tex;		// �e�N�X�`�����W
} VERTEX_3D;

typedef struct
{
	LPDIRECT3DPIXELSHADER9 ps;			//�s�N�Z���V�F�[�_�[
	LPD3DXCONSTANTTABLE    psc;		//�s�N�Z���V�F�[�_�[�p�R���X�^���g�e�[�u��
	LPDIRECT3DVERTEXSHADER9 vs;		//�o�[�e�b�N�X�V�F�[�_�[
	LPD3DXCONSTANTTABLE    vsc;		//�o�[�e�b�N�X�V�F�[�_�[�p�R���X�^���g�e�[�u��
}SHADER_SET;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//�J�b�R�C�C�ISafeRelease�֐�!! #define�}�N���Ȃ�Ă����Â�
//�g�����F�������ĂˁB
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