#version 150
uniform sampler2D Texture;

in vec2 uv;
out vec4 fragColor;

void main()
{
    fragColor = texture(Texture,uv);
}
