/*#############################################################################################################################################################################################*/
#shader tesscont
#version 410
layout(vertices = 4) out;
const vec3[] cornerOffsets = vec3[]
(
    //posX face
    vec3(1, 1, -1)* 0.5F,
    vec3(1, 1, 1)* 0.5F,
    vec3(1, -1, -1)* 0.5F,
    vec3(1, -1, 1)* 0.5F,

    //posY face
    vec3(1, 1, 1)* 0.5F,
    vec3(1, 1, -1)* 0.5F,
    vec3(-1, 1, 1)* 0.5F,
    vec3(-1, 1, -1)* 0.5F,

    //posZ face
    vec3(1, 1, 1)* 0.5F,
    vec3(-1, 1, 1)* 0.5F,
    vec3(1, -1, 1)* 0.5F,
    vec3(-1, -1, 1)* 0.5F,

    //negX face
    vec3(-1, 1, 1)* 0.5F,
    vec3(-1, 1, -1)* 0.5F,
    vec3(-1, -1, 1)* 0.5F,
    vec3(-1, -1, -1)* 0.5F,

    //negY face
    vec3(-1, -1, 1)* 0.5F,
    vec3(-1, -1, -1)* 0.5F,
    vec3(1, -1, 1)* 0.5F,
    vec3(1, -1, -1)* 0.5F,

    //negZ face
    vec3(-1, 1, -1)* 0.5F,
    vec3(1, 1, -1)* 0.5F,
    vec3(-1, -1, -1)* 0.5F,
    vec3(1, -1, -1)* 0.5F
    );
const float[] faceBrightnesses = float[]
(
    0.8F,
    1.0F,
    0.7F,
    0.8F,
    0.5F,
    0.7F
);
in vec3 vPos[];
in vec3 vSize[];
in vec4 vColor[];
in float vFaceDirIndex[];
out Tess
{
    vec3 pos;
    vec4 color;
} Out[];

void main(void)
{
    if (gl_InvocationID == 0)
    {
        gl_TessLevelInner[0] = 0;
        gl_TessLevelInner[1] = 0;
        gl_TessLevelOuter[0] = 1;
        gl_TessLevelOuter[1] = 1;
        gl_TessLevelOuter[2] = 1;
        gl_TessLevelOuter[3] = 1;
    }
    int faceDirIndex = int(round(vFaceDirIndex[0]));
    Out[gl_InvocationID].pos = vPos[0] + (cornerOffsets[faceDirIndex * 4 + gl_InvocationID] * vSize[0]);
    Out[gl_InvocationID].color = vec4(vColor[0].rgb * faceBrightnesses[faceDirIndex], vColor[0].a);
}

/*#############################################################################################################################################################################################*/
#shader tesseval
#version 410
layout(quads) in;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
out vec4 vColor;
in Tess
{
    vec3 pos;
    vec4 color;
} In[];

void main(void)
{
    gl_Position = projMatrix * viewMatrix * vec4(In[int(gl_TessCoord.x) + int(gl_TessCoord.y) * 2].pos, 1.0F);
    vColor = In[0].color;
}
