enum V_INPUT_LAYOUT_FORMAT : unsigned int
{
	//Represents a vector format with four 32-bit floating-point components.
	V_INPUT_LAYOUT_FORMAT_R32G32B32A32_FLOAT = 2,
	//Represents a vector format with four 32 - bit unsigned integer components.
	V_INPUT_LAYOUT_FORMAT_R32G32B32A32_UINT = 3,
	//Represents a vector format with four 32-bit signed integer components.
	V_INPUT_LAYOUT_FORMAT_R32G32B32A32_SINT = 4,

	//Represents a vector format with three 32-bit floating-point components.
	V_INPUT_LAYOUT_FORMAT_R32G32B32_FLOAT = 6,
	//Represents a vector format with three 32-bit unsigned integer components.
	V_INPUT_LAYOUT_FORMAT_R32G32B32_UINT = 7,
	//Represents a vector format with three 32 - bit signed integer components.
	V_INPUT_LAYOUT_FORMAT_R32G32B32_SINT = 8,

	//Represents a vector format with three 32-bit floating-point components.
	V_INPUT_LAYOUT_FORMAT_R32G32_FLOAT = 16,
	//Represents a vector format with three 32-bit unsigned integer components.
	V_INPUT_LAYOUT_FORMAT_R32G32_UINT = 17,
	//Represents a vector format with three 32 - bit signed integer components.
	V_INPUT_LAYOUT_FORMAT_R32G32_SINT = 18
};

static bool operator>=(enum V_INPUT_LAYOUT_FORMAT ls, unsigned int rs)
{
	return (static_cast<unsigned int>(ls) >= rs);
}
static bool operator<=(enum V_INPUT_LAYOUT_FORMAT ls, unsigned int rs)
{
	return (static_cast<unsigned int>(ls) <= rs);
}
struct V_VertexShaderInfo
{
	//Shader code and Size
	void* vsCode;
	//Vertex Mesh
	void* vtm;
	//vertex data size
	unsigned int size_vertex;
	//vertex count
	unsigned int len_list;
	//vertex shader Uniform or Constant Buffer
	void* cb;
	//size of vertex shader Uniform or Constant Buffer
	unsigned cbSize;
	//input layout
	enum V_INPUT_LAYOUT_FORMAT* inputLayouts;
	//number of user defined samatics
	unsigned int inputLayoutsElementCount;
	//Name of user defined samatics
	const char** inputLayoutElementNames;
};
