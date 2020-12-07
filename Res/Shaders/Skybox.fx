//--------------------------------------------------------------------------------------
// File: DX11 Framework.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include <ConstantBuffers.fx>

TextureCube skyBoxTexture : register(t0);
SamplerState skyboxSampler : register(s0);

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float3 Norm: NORMAL;
    float3 PosW: POSITION;
    float3 Tex: TEXCOORD0;
};

struct VS_INPUT
{
    float4 Pos : POSITION;
    float3 NormalL : NORMAL;
    float2 Tex : TEXCOORD0;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT)0;

    matrix viewNoTranslation = {
        View[0][0], View[0][1], View[0][2], 0,
        View[1][0], View[1][1], View[1][2], 0,
        View[2][0], View[2][1], View[2][2], 0,
        0,          0,          0,          1
    };

    output.Pos = mul(input.Pos, viewNoTranslation);
    output.Pos = mul(output.Pos, Projection);
    output.Pos = output.Pos.xyww;

    output.Tex = input.Pos.xyz;

    return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_Target
{
    return skyBoxTexture.Sample(skyboxSampler, input.Tex);
}