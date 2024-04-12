//vs_5_0

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
    VS_OUTPUT output = (VS_OUTPUT)0;
	
    output.position = input.position;

    output.color = float3(1,1,1);
    return output;
}