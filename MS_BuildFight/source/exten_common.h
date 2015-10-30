//=============================================================================
//
// ã§í åvéZèàóù [math_common.h]
// Author : Tomoki Ohashi
//
//=============================================================================
#ifndef _EXTEN_COMMON_H_
#define _EXTEN_COMMON_H_


#include "common.h"

float mersenne_twister_f32(float low, float high);
int mersenne_twister_u16(int low, int high);
float Rotation_Normalizer(float rot);
bool Create_PS(char* hlsl, char* name, LPDIRECT3DPIXELSHADER9* shader, LPD3DXCONSTANTTABLE* table,LPDIRECT3DDEVICE9 pDevice);
bool Create_VS(char* hlsl, char* name, LPDIRECT3DVERTEXSHADER9* shader, LPD3DXCONSTANTTABLE* table, LPDIRECT3DDEVICE9 pDevice);



#endif _COMMON_H_


// EOF
