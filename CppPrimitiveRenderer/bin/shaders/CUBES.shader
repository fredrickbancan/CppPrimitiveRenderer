#shader vertex
#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 size;
layout(location = 2) in vec4 color;
layout(location = 3) in float faceDir;

out vec3 vPos;
out vec3 vSize;
out vec4 vColor;
out float vFaceDirIndex;
void main()
{
    vPos = position;
    vSize = size;
    vColor = color;
    vFaceDirIndex = faceDir;
}

#shader fragment
#version 330
layout(location = 0) out vec4 color;
in vec4 vColor;
void main()
{
	color = vColor;
}