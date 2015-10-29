#include "FrustumCulling.h"


//	|sv|*|sv|
float Vct3LengthPow2( const VECTOR3 &sv )
{
	return( ( sv.x * sv.x ) + ( sv.y * sv.y ) + ( sv.z * sv.z ) );
}

//	|sv|
float Vct3Length( const VECTOR3 &sv )
{
	return( sqrtf( Vct3LengthPow2( sv ) ) );
}

//	1/(|sv|*|sv|)
float Vct3LengthPow2Rev( const VECTOR3 &sv )
{
	return( 1.f / Vct3LengthPow2( sv ) );
}

//	1/|sv|
float Vct3LengthRev( const VECTOR3 &sv )
{
	return( 1.f / Vct3Length( sv ) );
}

//	ov = sv * f
void Vct3MulScl( VECTOR3 &ov, const VECTOR3 &sv, const float f )
{
	ov.x = sv.x * f;
	ov.y = sv.y * f;
	ov.z = sv.z * f;
}

//	ov=正規化(sv)
void Vct3Normalize( VECTOR3 &ov, const VECTOR3 &sv )
{
	float	fr = Vct3LengthRev( sv );
	Vct3MulScl( ov, sv, fr );
}

//	ov=正規化(ov)
void Vct3Normalize( VECTOR3 &osv )
{
	Vct3Normalize( osv, osv );
}

//	内積(sv1・sv2)
float Vct3Dot( const VECTOR3 &sv1, const VECTOR3 &sv2 )
{
	return( ( sv1.x * sv2.x ) + ( sv1.y * sv2.y ) + ( sv1.z * sv2.z ) );
}

//	外積(sv1ｘsv2)
void Vct3Cross( VECTOR3 &ov, const VECTOR3 &sv1, const VECTOR3 &sv2 )
{
	ov.x = ( sv1.y * sv2.z ) - ( sv1.z * sv2.y );
	ov.y = ( sv1.z * sv2.x ) - ( sv1.x * sv2.z );
	ov.z = ( sv1.x * sv2.y ) - ( sv1.y * sv2.x );
}

//	ov = sv1 - sv2
void Vct3Sub( VECTOR3 &ov, const VECTOR3 &sv1, const VECTOR3 &sv2 )
{
	ov.x = sv1.x - sv2.x;
	ov.y = sv1.y - sv2.y;
	ov.z = sv1.z - sv2.z;
}

//	ビュー行列
void	Mtx4x4LookToLH(	MATRIX4x4 &om, const VECTOR3	&EyePosition,	const VECTOR3	&FocusPosition,	const VECTOR3	&UpDirection	)
{
	VECTOR3	EyeDirection;
	VECTOR3	vX;
	VECTOR3	vY;
	VECTOR3	vZ;
	VECTOR3	vC;
	Vct3Sub( EyeDirection, FocusPosition, EyePosition );
	Vct3Normalize( vZ, EyeDirection );	//カメラ空間のZ軸ベクトル（＝視線ベクトル＝【注視点－視点】を正規化したもの）
	Vct3Cross( vX, UpDirection, vZ );	//カメラ空間のX軸ベクトル（＝上ベクトルと視線ベクトルの外積）
	Vct3Cross( vY, vZ, vX );			//カメラ空間のY軸ベクトル（＝視線ベクトルとカメラ空間のX軸ベクトルの外積）
	vC.x = -Vct3Dot( EyePosition, vX );	//－（視点とカメラ空間のX軸ベクトルの内積）
	vC.y = -Vct3Dot( EyePosition, vY );	//－（視点とカメラ空間のY軸ベクトルの内積）
	vC.z = -Vct3Dot( EyePosition, vZ );	//－（視点とカメラ空間のZ軸ベクトルの内積）
	om._11 = vX.x;	om._12 = vY.x;	om._13 = vZ.x;	om._14 = 0.f;
	om._21 = vX.y;	om._22 = vY.y;	om._23 = vZ.y;	om._24 = 0.f;
	om._31 = vX.z;	om._32 = vY.z;	om._33 = vZ.z;	om._34 = 0.f;
	om._41 = vC.x;	om._42 = vC.y;	om._43 = vC.z;	om._44 = 1.f;
}

//３点から平面パラメータ作成
void	PlaneFromPoints(VECTOR3 *pP0 , VECTOR3 *pP1 , VECTOR3 *pP2 , PLANE *pPlane)
{
	VECTOR3 V0,V1,V2;

	V0.x = pP1->x - pP0->x;		V0.y = pP1->y - pP0->y;		V0.z= pP1->z- pP0->z;
	V1.x = pP2->x - pP0->x;		V1.y = pP2->y - pP0->y;		V1.z= pP2->z- pP0->z;
	Vct3Cross( V2, V0, V1 );
	Vct3Normalize( V2 );
	pPlane->a = V2.x;
	pPlane->b = V2.y;
	pPlane->c = V2.z;
	pPlane->d = -( V2.x * pP0->x + V2.y * pP0->y + V2.z * pP0->z );
}

//視野パラメータから視錐台用平面作成
void	SetupFOVClipPlanes( float Angle , float Aspect , float NearClip , float FarClip, FRUSTUM &Frustum )
{
	VECTOR3	P0 , P1 , P2;

	float	fTan = tan( Angle * 0.5f );

	//	左平面
	P0.x = 0.0f;
	P0.y = 0.0f;
	P0.z = 0.0f;
	P1.x = -FarClip * ( fTan / Aspect );
	P1.y = -FarClip * ( fTan );
	P1.z = FarClip;
	P2.x = P1.x;
	P2.y = -P1.y;
	P2.z = P1.z;
	PlaneFromPoints( &P0, &P1 , &P2 , &Frustum.LeftPlane );

	//	右平面
	P0.x = 0.0f;
	P0.y = 0.0f;
	P0.z = 0.0f;
	P1.x = FarClip * ( fTan / Aspect);
	P1.y = FarClip * ( fTan );
	P1.z = FarClip;
	P2.x = P1.x;
	P2.y = -P1.y;
	P2.z = P1.z;
	PlaneFromPoints( &P0, &P1 , &P2 , &Frustum.RightPlane );

	//	上平面
	P0.x = 0.0f;
	P0.y = 0.0f;
	P0.z = 0.0f;
	P1.x = -FarClip * ( fTan / Aspect);
	P1.y = FarClip * ( fTan );
	P1.z = FarClip;
	P2.x = -P1.x;
	P2.y = P1.y;
	P2.z = P1.z;
	PlaneFromPoints( &P0, &P1 , &P2 , &Frustum.TopPlane );

	//	下平面
	P0.x = 0.0f;
	P0.y = 0.0f;
	P0.z = 0.0f;
	P1.x = FarClip * ( fTan / Aspect);
	P1.y = -FarClip * ( fTan );
	P1.z = FarClip;
	P2.x = -P1.x;
	P2.y = P1.y;
	P2.z = P1.z;
	PlaneFromPoints( &P0, &P1 , &P2 , &Frustum.BottomPlane );

	Frustum.NearClip = NearClip;
	Frustum.FarClip = FarClip;
}

//視錐台判定
BOOL	MeshFOVCheck(VECTOR3 *pBSpherePos , float BSphereRadius,FRUSTUM &Frustum,MATRIX4x4	&mView)
{
	float	Dist;
	VECTOR3	vViewPos;
	//	ビュー空間Ｚ変換
	vViewPos.z =	mView._13 * pBSpherePos->x +
					mView._23 * pBSpherePos->y +
					mView._33 * pBSpherePos->z + mView._43;
	//	ニアクリップ平面より手前か
	if( ( vViewPos.z + BSphereRadius ) < Frustum.NearClip )
	{
		return FALSE;
	}
	//	ファークリップ平面より奥か
	if( ( vViewPos.z - BSphereRadius ) > Frustum.FarClip )
	{
		return FALSE;
	}
	//	ビュー空間Ｘ変換
	vViewPos.x =	mView._11 * pBSpherePos->x +
					mView._21 * pBSpherePos->y +
					mView._31 * pBSpherePos->z + mView._41;
	//	左側面より左側か
	Dist = ( vViewPos.x * Frustum.LeftPlane.a ) + ( vViewPos.z * Frustum.LeftPlane.c );
	if( Dist > BSphereRadius )
	{
		return FALSE;
	}
	//	右側面より右側か
	Dist = ( vViewPos.x * Frustum.RightPlane.a ) + ( vViewPos.z * Frustum.RightPlane.c );
	if( Dist > BSphereRadius )
	{
		return FALSE;
	}
	//	ビュー空間Ｙ変換
	vViewPos.y =	mView._12 * pBSpherePos->x +
					mView._22 * pBSpherePos->y +
					mView._32 * pBSpherePos->z + mView._42;
	//	上側面より上側か
	Dist = ( vViewPos.y * Frustum.TopPlane.b ) + ( vViewPos.z * Frustum.TopPlane.c );
	if( Dist > BSphereRadius )
	{
		return FALSE;
	}
	//	下側面より下側か
	Dist = ( vViewPos.y * Frustum.BottomPlane.b ) + ( vViewPos.z * Frustum.BottomPlane.c);
	if( Dist > BSphereRadius )
	{
		return FALSE;
	}
	return TRUE;
}
/*
void main( void )
{
	VECTOR3	EyePosition = {0.f,0.f,-100.f};
	VECTOR3	FocusPosition = {0.f,0.f,200.f};
	VECTOR3	UpDirection = {0.f,1.f,0.f};
	MATRIX4x4	mView;
	Mtx4x4LookToLH(	mView, EyePosition,	FocusPosition,	UpDirection	);

	FRUSTUM	sFrustum;
	SetupFOVClipPlanes( 45.0f, 800/600, 1.0f, 10000.0f, sFrustum );

	VECTOR3	BSpherePos		=	{ 0.f, 0.f, 50.f };
	float	BSphereRadius	=	100.f;
	if( MeshFOVCheck(&BSpherePos , BSphereRadius,sFrustum,mView) )
	{
		printf("draw\n");
	}
	else
	{
		printf("culling\n");
	}

	rewind(stdin);
	getchar();
}
*/

