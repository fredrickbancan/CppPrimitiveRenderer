#shader vertex
#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in float radius;
layout(location = 2) in vec4 color;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform vec2 viewPortSize;
uniform float lerpFactor;
out vec4 vColor;
out vec4 worldPos;
out float rad;
void main()
{
	gl_Position = projMatrix * viewMatrix * position;
	gl_PointSize = viewPortSize.y * projMatrix[1][1] * radius / gl_Position.w;
	vColor = color;
	rad = radius;
    worldPos = position;
}

#shader fragment
#version 330
layout(location = 0) out vec4 color;
in vec4 vColor;
in float rad;
in vec4 worldPos;
uniform mat4 projMatrix;
uniform mat4 viewMatrix;
float aoc;

void makeSphere()
{
    //clamps fragments to circle shape. 
    vec2 mapping = gl_PointCoord * 2.0F - 1.0F;
    float d = dot(mapping, mapping);

    if (d >= 1.0F)
    {//discard if the vectors length is more than 0.5
        discard;
    }
    float z = sqrt(1.0F - d);
    vec3 normal = vec3(mapping, z);
    normal = mat3(transpose(viewMatrix)) * normal;
    vec3 cameraPos = worldPos.xyz + rad * normal;
    
    ////Set the depth based on the new cameraPos.
    vec4 clipPos = projMatrix * viewMatrix * vec4(cameraPos, 1.0);
    float ndcDepth = clipPos.z / clipPos.w;
    gl_FragDepth = ((gl_DepthRange.diff * ndcDepth) + gl_DepthRange.near + gl_DepthRange.far) / 2.0;
    if (gl_FragDepth < 0.0001)discard;
    //calc ambient occlusion for circle
    aoc = sqrt(1.0F - d / 2);
}

void main()
{
	makeSphere();
	color = vColor;
	color.r *= aoc;
	color.g *= aoc;
	color.b *= aoc;
}