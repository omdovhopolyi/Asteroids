#version 330 core
layout (location = 0) in vec3 pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 fragWorldPos;

void main()
{
    fragWorldPos = model * vec4(pos, 1.0);
    gl_Position = projection * view * model * vec4(pos, 1.0);
}
