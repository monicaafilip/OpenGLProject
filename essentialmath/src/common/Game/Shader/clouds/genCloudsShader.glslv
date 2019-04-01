uniform mat4 IvModelViewProjectionMatrix;
uniform mat4 transform;

layout(location = COLOR) in vec4 inColor;
layout(location = POSITION) in vec3 position;
layout(location = TEXCOORD0) in vec2 texCoord0;

void main()
{
    gl_Position = IvModelViewProjectionMatrix *transform* vec4(position,1.0);
}

