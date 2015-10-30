
#include "exten_common.h"

#include <random>
#include <vector>
#include <iostream>
#include <map>

std::random_device rnd;     // �񌈒�I�ȗ���������𐶐�
std::mt19937 mt(rnd());     //  �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h�l

float mersenne_twister_f32(float low, float high){
	std::uniform_real_distribution<> rand_(low, high);
	return static_cast<float>(rand_(mt));
}

int mersenne_twister_u16(int low, int high)
{
	std::uniform_int_distribution<> rand_(low, high);
	return static_cast<int>(rand_(mt));
}

float Rotation_Normalizer(float rot)
{
	if (rot > D3DX_PI)
	{
		rot -= D3DX_PI * 2.0f;
	}
	if (rot < -D3DX_PI)
	{
		rot += D3DX_PI * 2.0f;
	}
	return rot;
}
//
//
//
bool Create_PS(char* hlsl, char* name, LPDIRECT3DPIXELSHADER9* shader, LPD3DXCONSTANTTABLE* table, LPDIRECT3DDEVICE9 pDevice)
{
	HRESULT hr;
	LPD3DXBUFFER err;
	LPD3DXBUFFER code;
	// hlsl�ǂݍ���
	hr = D3DXCompileShaderFromFile(hlsl, NULL, NULL, name, "ps_3_0", 0, &code, &err, table);
	if (FAILED(hr)){
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), name, MB_OK);
		err->Release();
		return false;
	}
	// �s�N�Z���V�F�[�_�쐬 
	hr = pDevice->CreatePixelShader((DWORD*)code->GetBufferPointer(), shader);
	if (FAILED(hr)){
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), name, MB_OK);
		return false;
	}
	return true;
}
//
//
//
bool Create_VS(char* hlsl, char* name, LPDIRECT3DVERTEXSHADER9* shader, LPD3DXCONSTANTTABLE* table, LPDIRECT3DDEVICE9 pDevice)
{
	HRESULT hr;
	LPD3DXBUFFER err;
	LPD3DXBUFFER code;
	// hlsl�ǂݍ���
	hr = D3DXCompileShaderFromFile(hlsl, NULL, NULL, name, "vs_3_0", 0, &code, &err, table);
	if (FAILED(hr)){
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), name, MB_OK);
		err->Release();
		return false;
	}
	// �s�N�Z���V�F�[�_�쐬 
	hr = pDevice->CreateVertexShader((DWORD*)code->GetBufferPointer(), shader);
	if (FAILED(hr)){
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), name, MB_OK);
		return false;
	}
	return true;
}