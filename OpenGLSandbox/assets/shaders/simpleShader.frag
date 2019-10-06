#version 460 core
layout(location = 0) out vec4 color;

in vec3 v_Normal;
in vec2 v_TexCoord;

uniform sampler2D albedo;
uniform sampler2D roughness;

void main()
{
    vec3 finalColor = vec3(1.0);

    vec3 albedoColor = texture(albedo, v_TexCoord).rgb;
    
    finalColor = albedoColor;
    color = vec4(finalColor, 1.0);
}
