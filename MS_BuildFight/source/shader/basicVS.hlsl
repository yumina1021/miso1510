
float4x4 gWvp;
float4x4 oldWvp;
float4x4 world;
float4x4 worldInvTranspose;

float3 LightDir;
float4 LightDiffuse;
float4 LightDiffuse2;
float4 LightAmbient;
float4 MatDiffuse;
float4 MatAmbient;
float3 CameraVec;
float3 PlayerPos;
float3 Pos;

////////////////////////////////////////
//ノーマル
////////////////////////////////////////
void VS(in float3 inPos : POSITION0,
	in float3 inNormal : NORMAL0,
	in float2 inUV : TEXCOORD0,
	out float4 outPos : POSITION,
	out float4 outColor : COLOR0,
	out float2 outUV : TEXCOORD0,
	out float fog : FOG)
{
	float4 PosH = mul(float4(inPos, 1.0f), gWvp);
	outPos = PosH;

	outColor = MatDiffuse;
	outUV = inUV;

	float d = distance(Pos, inPos);	//カメラから
	fog = 1.0f / exp(d*0.00027f);	//指数フォグ
}

////////////////////////////////////////
//シャドウ（テクスチャ）
////////////////////////////////////////
void VS_TEXTURE(in float3 inPos : POSITION0,
	in float3 inNormal : NORMAL0,
	in float2 inUV : TEXCOORD0,
	out float4 outPos : POSITION,
	out float4 outColor : COLOR0,
	out float2 outUV : TEXCOORD0)
{
	float4 PosH = mul(float4(inPos, 1.0f), gWvp);
	outPos = PosH;
	float light = dot(inNormal, -LightDir)*0.5f + 0.5;
	outColor = MatDiffuse;
	outColor = float4(0.0f, 0.0f, 0.0f, 0.0f);
	outColor.a = 1.0f;
	outUV = inUV;
}

////////////////////////////////////////
//モーションブラー
////////////////////////////////////////
void VS_BLUR(in float3 inPos : POSITION0,
	in float3 inNormal : NORMAL0,
	out float4 outPos : POSITION,
	out float4 outColor : COLOR0,
	out float2 outUV : TEXCOORD0,
	out float2 velocity : TEXCOORD1)
{
	float4 oldPosH = mul(float4(inPos, 1.0f), oldWvp);
	float4 newPosH = mul(float4(inPos, 1.0f), gWvp);
	float2 spdVec = newPosH.xy / newPosH.w - oldPosH.xy / oldPosH.w;

	velocity.x = spdVec.x *0.5f;
	velocity.y = spdVec.y *-0.5f;

	float4 normal = float4(inNormal,0.0f);
	normal = mul(normal, gWvp);

	float result = dot(normal.xy, spdVec);
	if (result <= 0.0f){ 
		outPos = oldPosH;
	}
	else{
		outPos = newPosH;
	}

	float light = dot(inNormal, -LightDir)*0.5f + 0.5;

	outColor = MatDiffuse*light;

	outUV = newPosH.xy / newPosH.w *0.5f + 0.5f;
	outUV.y = 1.0f - outUV.y;
}
////////////////////////////////////////
//トゥーン
////////////////////////////////////////
void VS_THUN(in float3 inPos : POSITION0,
	in float3 inNormal : NORMAL0,
	out float4 outPos : POSITION,
	out float4 outColor : COLOR0,
	out float4 outColor2 : COLOR1,
	out float2 outUV : TEXCOORD0)
{
	outPos = mul(float4(inPos, 1.0f), gWvp);

	float light = -dot(inNormal.xyz, LightDir);

	float4 PosH = mul(float4(inPos, 1.0f), gWvp);
	outPos = PosH;

	float3 normalH = normalize(mul(float4(inNormal, 1.0f), world).xyz);

	//深度値カラー
	outColor.r = normalH.x;
	outColor.g = normalH.y;
	outColor.b = normalH.z;
	outColor.a = PosH.z / PosH.w;

	//トゥーンカラー
	outColor2 = MatDiffuse * LightDiffuse;
	outColor2.a = 1.0f;

	outUV.x = light*0.5 + 0.5;
	outUV.y = 0.5f;

}
////////////////////////////////////////
//シャドウバッファ
////////////////////////////////////////
void VS_SHADOW(in float3 inPos : POSITION0,
	in float3 inNormal : NORMAL0,
	in float2 inUV : TEXCOORD0,
	out float4 outPos : POSITION,
	out float4 outColor : COLOR0,
	out float2 outUV : TEXCOORD0,
	out float4 outUVX : TEXCOORD1)
{
	float4 PosH = mul(float4(inPos, 1.0f), gWvp);
		outPos = PosH;

	float light = dot(inNormal, -LightDir) + 0.5;

	outColor = light;
	outColor.a = 1.0f;

	outUV.x = (PlayerPos.x - inPos.x)*0.02f + 0.25f;
	outUV.y = (PlayerPos.z - inPos.z)*0.02f + 0.5f;
}
////////////////////////////////////////
//シャドウバッファ
////////////////////////////////////////
void VS_GOAL(in float3 inPos : POSITION0,
			out float4 outPos : POSITION,
			out float4 outColor : COLOR0)
{
	float4 PosH = mul(float4(inPos, 1.0f), gWvp);
	outPos = PosH;

	outColor = MatDiffuse;
	outColor.a = 0.5f;
}
////////////////////////////////////////
//シャドウバッファ
////////////////////////////////////////
void VS_GOAL_LING(in float3 inPos : POSITION0,
	in float3 inNormal : NORMAL0,
	out float4 outPos : POSITION,
	out float4 outColor : COLOR0,
	out float3 outNormal : TEXCOORD1,
	out float3 outWorldPos : TEXCOORD2)
{
	float4 PosH = mul(float4(inPos, 1.0f), gWvp);

	outPos = PosH;

	outWorldPos = mul(float4(inPos, 1.0f), world);

	outNormal = mul(inNormal, (float3x3)worldInvTranspose);

	outColor = MatDiffuse;
}
