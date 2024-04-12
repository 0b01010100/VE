//ps_5_0

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
};
float4 psmain(VS_OUTPUT input) : SV_Target
{
    return float4(1,1,1,1);

}