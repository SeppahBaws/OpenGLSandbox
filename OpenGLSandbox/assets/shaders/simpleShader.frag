#version 460 core
layout(location = 0) out vec4 color;

in vec3 v_Color;
in vec2 v_TexCoord;

uniform sampler2D tilesTexture;

void main()
{
    // color = vec4(v_Color, 1.0);
    color = texture(tilesTexture, v_TexCoord);
}
