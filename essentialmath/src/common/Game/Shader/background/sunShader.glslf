#version 150
uniform sampler2D Texture;

in vec3 position_;
in vec2 uv;
out vec4 fragColor;

void main()
{
    vec3 p1=vec3(0.3,0,1.);
    vec3 p2=position_;
    p2.y=0;
    float dist=length(p1-p2);
    float at=1/dist;
    fragColor=vec4(at,at,at,1)*texture(Texture,uv);
}

