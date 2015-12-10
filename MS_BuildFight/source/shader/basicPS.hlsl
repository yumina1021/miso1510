
sampler texSampler;
sampler texSampler2;
sampler shadowSampler;
sampler texSamplerCube;

float3 LightDir;
float4 MatDiffuse;
float3 CameraVec;
float2 ScreenResolution;

float4 gColor;
float gValue;
float g_ballalpha;
float g_goalhit;

float4 cubeMap(sampler cubemap, float3 toEye, float3 normalW);

/////////////////////////////////////////////////////////
// 通常（テクスチャー）
/////////////////////////////////////////////////////////
float4 PS(float4 diffuse : COLOR0, float2 uv : TEXCOORD0) : COLOR0
{
	return tex2D(texSampler, uv);
}

/////////////////////////////////////////////////////////
// 通常(色のみ)
/////////////////////////////////////////////////////////
float4 PS_DIFFUSE(float4 diffuse : COLOR0, float2 uv : TEXCOORD0) : COLOR0
{
	return diffuse;
}

/////////////////////////////////////////////////////////
// トゥーン輪郭
/////////////////////////////////////////////////////////
float4 PS_THUN_OUTLINE(float2 uv : TEXCOORD0) : COLOR0
{
	float2 pixel_offset = 1 / ScreenResolution;

	float4 n1 = tex2D(texSampler, float2(uv.x - pixel_offset.x, uv.y - pixel_offset.y));
	float4 n2 = tex2D(texSampler, float2(uv.x + pixel_offset.x, uv.y + pixel_offset.y));
	float4 n3 = tex2D(texSampler, float2(uv.x - pixel_offset.x, uv.y + pixel_offset.y));
	float4 n4 = tex2D(texSampler, float2(uv.x + pixel_offset.x, uv.y - pixel_offset.y));

	float4 diagonalDelta = abs(n1 - n2) + abs(n3 - n4);
	float depthDelta = diagonalDelta.a;
	depthDelta = saturate((depthDelta - 0.1f)*1.0f);

	float edgeAmount = saturate(depthDelta)*1.0f;

	float4 DepthMap = float4((float3)(1 - edgeAmount), 1.0f);
	
	float normalDelta = dot(diagonalDelta.rgb, 1);//r+g+bの早くなる書き方
	normalDelta = saturate(normalDelta - 0.5)*10.0f;

	float4 NormalMap = float4((float3)(1 - normalDelta), 1.0f);

	return DepthMap*NormalMap*tex2D(texSampler2, uv);
}
/////////////////////////////////////////////////////////
// モーションブラー用
/////////////////////////////////////////////////////////
void PS_BLUR(in float4 diffuse : COLOR0,
	in float2 inUV : TEXCOORD0,
	in float2 velocity : TEXCOORD1,
	out float4 outColor : COLOR0)
{
	outColor = 0.0f;

	for (int i = 0; i < 10; i++){
		outColor += tex2D(texSampler, inUV + velocity*i*-0.1f)*0.1f;
	}

	outColor *= diffuse;
	outColor.a = 1.0f;
}

/////////////////////////////////////////////////////////
// トゥーンカラー
/////////////////////////////////////////////////////////
void PS_THUN(in float2 inUV : TEXCOORD0,
	in float4 inColor : TEXCOORD1,
	out float4 outColor : COLOR0,
	out float4 outBuffer : COLOR1)
{
	outBuffer = inColor;
	outColor = gColor*tex2D(texSampler, inUV);
}

/////////////////////////////////////////////////////////
// 地面にテクスチャ貼る用PS
/////////////////////////////////////////////////////////
float4 PS_SHADOW(float4 diffuse : COLOR0, float2 uv : TEXCOORD0, float4 uvx : TEXCOORD1) : COLOR0
{
	return tex2D(shadowSampler, uv);
}
/////////////////////////////////////////////////////////
// エフェクト用
/////////////////////////////////////////////////////////
float4 PS_EFFECT(float4 diffuse : COLOR0, float2 uv : TEXCOORD0) : COLOR0
{
	return diffuse;
}
/////////////////////////////////////////////////////////
// ローザボールカラー
/////////////////////////////////////////////////////////
float4 PS_BALL_ROSA(float4 diffuse : COLOR0, float2 uv : TEXCOORD0) : COLOR0
{
	float4 color = float4(1.0f, 0.0f, 1.0f, g_ballalpha);
	return tex2D(texSampler, uv)*color;
}
/////////////////////////////////////////////////////////
// リーラボールカラー
/////////////////////////////////////////////////////////
float4 PS_BALL_LIRA(float4 diffuse : COLOR0, float2 uv : TEXCOORD0) : COLOR0
{
	float4 color = float4(0.2f, 0.6f, 1.0f, g_ballalpha);
	return tex2D(texSampler, uv)*color;
}
/////////////////////////////////////////////////////////
// テーメボールカラー
/////////////////////////////////////////////////////////
float4 PS_BALL_THEME(float4 diffuse : COLOR0, float2 uv : TEXCOORD0) : COLOR0
{
	float4 color = float4(1.0f, 1.0f, 0.0f, g_ballalpha);
	return tex2D(texSampler, uv)*color;
}
/////////////////////////////////////////////////////////
// 禿爺ボールカラー
/////////////////////////////////////////////////////////
float4 PS_BALL_HAGE(float4 diffuse : COLOR0, float2 uv : TEXCOORD0) : COLOR0
{
	float4 color = float4(1.0f, 1.0f, 1.0f, g_ballalpha);
	return tex2D(texSampler, uv)*color;
}
/////////////////////////////////////////////////////////
// ゴール用
/////////////////////////////////////////////////////////
float4 PS_GOAL(float4 diffuse : COLOR0) : COLOR0
{
	diffuse.r *= g_goalhit;
	return float4(diffuse.rgb, 0.5f);
}
/////////////////////////////////////////////////////////
// ゴールリング用
/////////////////////////////////////////////////////////
float4 PS_GOAL_LING(float4 diffuse : COLOR0, float3 normal : TEXCOORD1, float3 worldPos : TEXCOORD2) : COLOR0
{

	float3 toEye;

	normal = normalize(normal);

	toEye = normalize(CameraVec - worldPos);

	float4 cubeColor = cubeMap(texSamplerCube, toEye, normal);

	float4 color = cubeColor*0.4 + MatDiffuse*0.6;

	return float4(color.xyz, 1.0f);

}

//キューブマップ
float4 cubeMap(sampler cubemap, float3 toEye, float3 normalW)
{
	float3 envVec = reflect(-toEye, normalW);

	float4 envColor = texCUBE(cubemap, envVec);

	return envColor;
}