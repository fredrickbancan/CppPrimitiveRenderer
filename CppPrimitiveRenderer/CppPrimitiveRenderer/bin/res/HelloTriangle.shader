#shader vertex
#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in float size;
layout(location = 2) in vec4 color;

out vec4 vColor;
void main()
{
	gl_Position = position;
	vColor = color;
}

#shader fragment
#version 330
in vec4 vColor;
layout(location = 0) out vec4 color;
void main()
{
	color = vColor;
}