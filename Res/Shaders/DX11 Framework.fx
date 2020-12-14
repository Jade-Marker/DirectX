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

StructuredBuffer<Light> lightsBuffer : register(t3);

Texture2D txDiffuse : register(t0);
Texture2D txAmbient : register(t1);
Texture2D txSpecular : register(t2);
SamplerState samDiffuse : register(s0);
SamplerState samAmbient : register(s1);
SamplerState samSpecular : register(s2);

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

float GetDistanceScale(VS_OUTPUT input, Light light)
{
    float distanceScale;

    if (light.LightPosW.w == 1.0f)
    {
        distanceScale = 1.0f / distance(input.PosW, light.LightPosW);
    }
    else
    {
        distanceScale = 1.0f;
    }

    return distanceScale;
}

float3 GetLightDirection(VS_OUTPUT input, Light light)
{
    float3 lightDirection;

    if (light.LightPosW.w == 1.0f)
    {
        lightDirection = normalize(light.LightPosW - input.PosW);
    }
    else
    {
        lightDirection = light.LightDir;
    }

    return lightDirection;
}

float3 CalculateDiffuse(VS_OUTPUT input, Light light)
{
    float distanceScale = GetDistanceScale(input, light);
    float3 lightDirection = GetLightDirection(input, light);

    float diffuseAmount = max(dot(lightDirection, input.Norm), 0.0f) * distanceScale * light.DiffuseStrength;
    float3 diffuse = diffuseAmount * (DiffuseMtrl * light.DiffuseLight).rgb;

    return diffuse;
}

float3 CalculateAmbient(VS_OUTPUT input, Light light)
{
    float distanceScale = GetDistanceScale(input, light);
    float3 ambient = AmbientMtrl * light.AmbientLight * distanceScale * light.AmbientStrength;

    return ambient;
}

float3 CalculateSpecular(VS_OUTPUT input, Light light)
{
    float3 toEye = normalize(EyePosW - input.PosW);

    float distanceScale = GetDistanceScale(input, light);
    float3 lightDirection = GetLightDirection(input, light);

    //Compute the reflection vector
    float3 r = reflect(-lightDirection, input.Norm);

    //Determine how much (if any) specular light makes it into the eye
    float specularAmount = pow(max(dot(r, toEye), 0.0f), light.SpecularPower) * distanceScale * light.SpecularStrength;
    float3 specular = specularAmount * (SpecularMtrl * light.SpecularLight).rgb;

    return specular;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_Target
{
    float4 color;
    
    input.Norm = normalize(input.Norm);

    float3 sumOfDiffuse = (0,0,0);
    float3 sumOfAmbient = (0,0,0);
    float3 sumOfSpecular = (0,0,0);
    for (uint i = 0; i < numLights; i++)
    {
        sumOfDiffuse += CalculateDiffuse(input, lightsBuffer[i]);
        sumOfAmbient += CalculateAmbient(input, lightsBuffer[i]);
        sumOfSpecular += CalculateSpecular(input, lightsBuffer[i]);
    }

    float4 diffuseColor = txDiffuse.Sample(samDiffuse, input.Tex);
    float4 ambientColor = txAmbient.Sample(samAmbient, input.Tex);
    float4 specularColor = txSpecular.Sample(samSpecular, input.Tex);

    color.rgb = sumOfDiffuse * diffuseColor + (sumOfAmbient * ambientColor) * diffuseColor + sumOfSpecular * specularColor;
    color.a = diffuseColor.a;

    return color;
}