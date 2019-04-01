#version 150
uniform vec3 constColor;

out vec4 fragColor;

void main()
{
    fragColor=vec4(constColor,1.);
}
