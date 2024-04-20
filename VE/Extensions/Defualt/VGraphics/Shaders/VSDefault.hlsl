//vs_5_0
cbuffer constant : register(b0)
{
    float4 posOffset;
}
struct VS_INPUT
{
    float3 position : POSITION;
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
    
    output.position = float4(input.position, 1.F) + posOffset;
    output.color = input.color;
    
    return output;
}