uniform mat4 IvModelViewProjectionMatrix;

layout(location = COLOR) in vec4 inColor;
layout(location = POSITION) in vec4 position;
layout(location = TEXCOORD0) in vec2 texCoord0;

void main()
{
    gl_Position = IvModelViewProjectionMatrix * position;
}
