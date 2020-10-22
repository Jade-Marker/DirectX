//--------------------------------------------------------------------------------------
// File: DX11 Framework.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register(b0)
{
    matrix World;
}

cbuffer GlobalConstant : register(b1)
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

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR0;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( float4 Pos : POSITION, float4 Color : COLOR )
{
    float freq = 5.0f;
    float amp = 1.0f;

    Pos.z += sin(Pos.x + gTime * freq) * amp;

    VS_OUTPUT output = (VS_OUTPUT)0;
    output.Pos = mul( Pos, World );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );
    output.Color = float4(0.0f, 0.0625f, 0.5f, 0.2f) * abs(sin(Pos.x + gTime * 2)) + float4(0.0f, 0.0f, 0.5f, 0.2f);
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_Target
{
    return input.Color;
}
