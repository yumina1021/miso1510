#include <stdio.h>
#include <math.h>
#ifdef	_WIN32
#include <windows.h>
#endif//_WIN32

#ifndef	_WIN32
typedef	unsigned	int	BOOL;
#define	TRUE			1
#define	FALSE			0
#endif//_WIN32


#define	VIEW_ANGLE		(D3DX_PI * 0.25f/*D3DXToRadian(45.0f)*/)							// ビュー平面の視野角
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z		(1.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z		(10000.0f)										// ビュー平面のFarZ値

typedef struct _VECTOR3
{
	float x;
	float y;
	float z;
}VECTOR3;	//ベクトル

typedef struct _PLANE
{
	float a;
	float b;
	float c;
	float d;
}PLANE;		//平面

typedef struct _FRUSTUM
{
	PLANE	LeftPlane;
	PLANE	RightPlane;
	PLANE	TopPlane;
	PLANE	BottomPlane;
	float	NearClip;
	float	FarClip;
}FRUSTUM;	//視錐台

typedef struct _MATRIX4x4
{
	float _11;
	float _12;
	float _13;
	float _14;
	float _21;
	float _22;
	float _23;
	float _24;
	float _31;
	float _32;
	float _33;
	float _34;
	float _41;
	float _42;
	float _43;
	float _44;
}MATRIX4x4;	//4X4行列

float Vct3LengthPow2( const VECTOR3 &sv );

//	|sv|
float Vct3Length( const VECTOR3 &sv );

//	1/(|sv|*|sv|)
float Vct3LengthPow2Rev( const VECTOR3 &sv );

//	1/|sv|
float Vct3LengthRev( const VECTOR3 &sv );

//	ov = sv * f
void Vct3MulScl( VECTOR3 &ov, const VECTOR3 &sv, const float f );

//	ov=正規化(sv)
void Vct3Normalize( VECTOR3 &ov, const VECTOR3 &sv );

//	ov=正規化(ov)
void Vct3Normalize( VECTOR3 &osv );

//	内積(sv1・sv2)
float Vct3Dot( const VECTOR3 &sv1, const VECTOR3 &sv2 );

//	外積(sv1ｘsv2)
void Vct3Cross( VECTOR3 &ov, const VECTOR3 &sv1, const VECTOR3 &sv2 );

//	ov = sv1 - sv2
void Vct3Sub( VECTOR3 &ov, const VECTOR3 &sv1, const VECTOR3 &sv2 );

//	ビュー行列
void	Mtx4x4LookToLH(	MATRIX4x4 &om, const VECTOR3	&EyePosition,	const VECTOR3	&FocusPosition,	const VECTOR3	&UpDirection	);

//３点から平面パラメータ作成
void	PlaneFromPoints(VECTOR3 *pP0 , VECTOR3 *pP1 , VECTOR3 *pP2 , PLANE *pPlane);

//視野パラメータから視錐台用平面作成
void	SetupFOVClipPlanes( float Angle , float Aspect , float NearClip , float FarClip, FRUSTUM &Frustum );

//視錐台判定
BOOL	MeshFOVCheck(VECTOR3 *pBSpherePos , float BSphereRadius,FRUSTUM &Frustum,MATRIX4x4	&mView);


