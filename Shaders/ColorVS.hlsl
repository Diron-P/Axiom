cbuffer MatrixBuffer
{
    matrix world;
    matrix view;
    matrix projection;
};

struct VertexInput
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

PixelInput main(VertexInput input)
{
    PixelInput output;
    
    // Set the vector's w coordinate to 1.0f for 4x4 matrix calculations.
    input.position.w = 1.0;
    
    // Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, world);
    output.position = mul(output.position, view);
    output.position = mul(output.position, projection);
    
    // Set the input color for the pixel shader.
    output.color = input.color;
    
	return output;
}
