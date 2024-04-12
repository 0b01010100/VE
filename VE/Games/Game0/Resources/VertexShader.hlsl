//vs_5_0

struct VS_INPUT
{
    float4 position : POSITION;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT)0;
	
    output.position = input.position;

    return output;
}