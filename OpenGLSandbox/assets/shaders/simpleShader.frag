#version 460 core
layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D tilesTexture;

void main()
{
    color = texture(tilesTexture, v_TexCoord);
}
