#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uvCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 color = vec4(1.0);

out vec2 uv;
out vec4 clr;

void main()
{
    gl_Position = projection * view * model * vec4(pos, 1.0);
    uv = uvCoords;
    clr = color;
}
