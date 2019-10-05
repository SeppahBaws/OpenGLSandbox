#version 460 core
layout(location = 0) out vec4 color;

in vec3 v_Normal;
in vec2 v_TexCoord;

uniform sampler2D albedo;

void main()
{
    color = texture(albedo, v_TexCoord);
    // color = vec4(1.0);
}
