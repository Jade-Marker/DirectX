//--------------------------------------------------------------------------------------
// File: DX11 Framework.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include <ConstantBuffers.fx>

struct Light 
{
    float4 DiffuseLight;
    float4 AmbientLight;
    float4 SpecularLight;
    float4 LightPosW;
    float4 LightDir;
    float SpecularPower;
    float DiffuseStrength;
    float AmbientStrength;
    float SpecularStrength;
};

StructuredBuffer<Light> lightsBuffer : register(t1);

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

struct VS_INPUT
{
    float4 Pos : POSITION;
    float3 NormalL : NORMAL;
    float2 Tex : TEXCOORD0;
};

//--------------------------------------------------------------------------------------
// Vertex Shader - Implements Gouraud Shading using Diffuse lighting only
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    output.Tex = input.Tex;

    output.Pos = mul(input.Pos, World);
    output.PosW = output.Pos;
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);

    //Convert from local to world space
    //W component of vector is 0 as vectors cannot be translated
    float3 normalW = mul(float4(input.NormalL, 0.0f), World).xyz;
    normalW = normalize(normalW);
    output.Norm = normalW;

    return output;
}

float3 CalculateColor(VS_OUTPUT input, Light light)
{
    float3 toEye = normalize(EyePosW - input.PosW);

    float3 normalizedNorm = normalize(input.Norm);

    float distanceScale;
    float3 lightDirection;

    if (light.LightPosW.w == 1.0f)
    {
        distanceScale = 1.0f / distance(input.PosW, light.LightPosW);
        lightDirection = normalize(light.LightPosW - input.PosW);
    }
    else
    {
        distanceScale = 1.0f;
        lightDirection = light.LightDir;
    }

    //Compute the reflection vector
    float3 r = reflect(-lightDirection, normalizedNorm);

    //Determine how much (if any) specular light makes it into the eye
    float specularAmount = pow(max(dot(r, toEye), 0.0f), light.SpecularPower) * distanceScale * light.SpecularStrength;

    //Compute diffuse, ambient and specular components
    float3 ambient = AmbientMtrl * light.AmbientLight * distanceScale * light.AmbientStrength;
    float diffuseAmount = max(dot(lightDirection, normalizedNorm), 0.0f) * distanceScale * light.DiffuseStrength;
    float3 diffuse = diffuseAmount * (DiffuseMtrl * light.DiffuseLight).rgb;
    float3 specular = specularAmount * (SpecularMtrl * light.SpecularLight).rgb;

    return (diffuse + ambient + specular);
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_Target
{
    float4 color;
    
    float3 sumOfLights = (0,0,0);
    for (uint i = 0; i < numLights; i++)
    {
        sumOfLights += CalculateColor(input, lightsBuffer[i]);
    }

    float4 textureColor = txDiffuse.Sample(samLinear, input.Tex);

    color.rgb = sumOfLights * textureColor;
    color.a = DiffuseMtrl.a;

    return color;
}