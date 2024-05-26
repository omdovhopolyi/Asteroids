#version 330 core
out vec4 FragColor;

in vec4 fragWorldPos;

uniform float lineWidth = 0.01f;
uniform float cameraDistance = 1.f;


void main()
{
    vec4 pos = fragWorldPos - floor(fragWorldPos);

    float width = lineWidth * cameraDistance;

    if (pos.x > -width && pos.x < width || pos.y > -width && pos.y < width)
    {
        if (fragWorldPos.x > 0.f && fragWorldPos.x < width)
        {
            FragColor = vec4(0.f, 1.f, 0.f, 1.f);
        }
        else if (fragWorldPos.y > 0.f && fragWorldPos.y < width)
        {
            FragColor = vec4(1.f, 0.f, 0.f, 1.f);
        }
        else
        {
            FragColor = vec4(0.5f, 0.5f, 0.5f, 0.5f);
        }
    }
    else
    {
        discard;
    }
}
