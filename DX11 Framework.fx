//--------------------------------------------------------------------------------------
// File: DX11 Framework.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register( b0 )
{
	matrix World;
}

cbuffer GlobalConstant : register( b1 )
{
    matrix View;
    matrix Projection;
    float4 DiffuseMtrl;
    float4 DiffuseLight;
    float4 AmbientMtrl;
    float4 AmbientLight;
    float4 SpecularMtrl;
    float4 SpecularLight;
    float3 EyePosW;
    float SpecularPower;
    float3 LightVecW;
    float gTime;
}

Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float3 Norm: NORMAL;
    float3 PosW: POSITION;
    float2 Tex: TEXCOORD0;
};

//--------------------------------------------------------------------------------------
// Vertex Shader - Implements Gouraud Shading using Diffuse lighting only
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( float4 Pos : POSITION, float3 NormalL: NORMAL, float2 Tex: TEXCOORD0)
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    output.Tex = Tex;

    output.Pos = mul(Pos, World);
    output.PosW = output.Pos;
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);

    //Convert from local to world space
    //W component of vector is 0 as vectors cannot be translated
    float3 normalW = mul(float4(NormalL, 0.0f), World).xyz;
    normalW = normalize(normalW);
    output.Norm = normalW;

    return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_Target
{
    float4 color;
    
    float3 toEye = normalize(EyePosW - input.PosW);

    float3 normalizedNorm = normalize(input.Norm);

    //Compute the reflection vector
    float3 r = reflect(-LightVecW, normalizedNorm);
    
    //Determine how much (if any) specular light makes it into the eye
    float specularAmount = pow(max(dot(r, toEye), 0.0f), SpecularPower);
    
    //Compute diffuse, ambient and specular components
    float3 ambient = AmbientMtrl * AmbientLight;
    float diffuseAmount = max(dot(LightVecW, normalizedNorm), 0.0f);
    float3 diffuse = diffuseAmount * (DiffuseMtrl * DiffuseLight).rgb;
    float3 specular = specularAmount * (SpecularMtrl * SpecularLight).rgb;
    
    float4 textureColor = txDiffuse.Sample(samLinear, input.Tex);

    color.rgb = (diffuse + ambient + specular) * textureColor;
    color.a = DiffuseMtrl.a;

    return color;
}