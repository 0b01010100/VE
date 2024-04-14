//vs_5_0
cbuffer constant : register(b0)
{
    float3 posOffset;
}
struct VS_INPUT
{
    float4 position : POSITION;
    float3 color : COLOR;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    output.position = input.position + float4(posOffset, 0);
    output.color = input.color;
    
    return output;
}