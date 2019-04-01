#version 150
uniform sampler2D Texture;
uniform vec4 transparencyColor;

in vec2 uv;
out vec4 fragColor;

void main()
{
    fragColor=texture(Texture,uv) *transparencyColor;
}
