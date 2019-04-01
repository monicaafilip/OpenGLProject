uniform mat4 IvModelViewProjectionMatrix;
uniform mat4 transform;

layout(location = POSITION) in vec3 position;
layout(location = TEXCOORD0) in vec2 texCoord;

out vec3 position_;
out vec2 uv;

void main()
{
    uv=texCoord;
    position_=position;
    gl_Position = IvModelViewProjectionMatrix * transform * vec4(position_,1.0);
}
