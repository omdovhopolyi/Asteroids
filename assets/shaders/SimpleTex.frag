#version 330 core
out vec4 FragColor;

in vec2 uv;
in vec4 clr;

uniform sampler2D tex;
uniform sampler2D mask;

void main()
{
    FragColor = texture(tex, uv) * clr;
    FragColor += vec4(0.1);
}
