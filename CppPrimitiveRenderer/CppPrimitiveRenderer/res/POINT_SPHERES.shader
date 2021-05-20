#shader vertex
#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in float size;
layout(location = 2) in vec4 color;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform vec2 viewPortSize;
uniform float lerpFactor;
out vec4 vColor;
void main()
{
	gl_Position = projMatrix * viewMatrix * position;
	gl_PointSize = viewPortSize.y * projMatrix[1][1] * size / gl_Position.w;
	vColor = color;
}

#shader fragment
#version 330
in vec4 vColor;
layout(location = 0) out vec4 color;

void makeSphere()
{
	//clamps fragments to circle shape. 
	vec2 centerVec = gl_PointCoord - vec2(0.5F);//get a vector from center of square to coord
	float coordLength = length(centerVec);

	if (coordLength >= 0.5F)
	{//discard if the vectors length is more than 0.5
		discard;
	}
}

void main()
{
	makeSphere();
	color = vColor;
}