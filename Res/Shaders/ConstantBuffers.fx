cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    float4 DiffuseMtrl;
    float4 AmbientMtrl;
    float4 SpecularMtrl;
}

cbuffer GlobalConstant : register(b1)
{
    matrix View;
    matrix Projection;
    float3 EyePosW;
    float gTime;
    int numLights;
}