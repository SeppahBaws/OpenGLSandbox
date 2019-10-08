#version 460 core
layout(location = 0) out vec4 out_color;

in vec3 v_Pos;
in vec3 v_Normal;
in vec2 v_TexCoord;

uniform sampler2D u_AlbedoMap;
uniform sampler2D u_NormalMap;
uniform sampler2D u_RoughnessMap;
uniform sampler2D u_MetallicMap;
uniform sampler2D u_AOMap;

uniform vec3 u_ViewPos;

float ambientStrength = 0.2;
vec3 lightPosition = vec3(2.0, 2.0, 2.0);
vec3 lightColor = vec3(1.0);
float specularStrength = 0.5;

void main()
{
    vec3 finalColor = vec3(1.0);

    vec3 color = texture(u_AlbedoMap, v_TexCoord).rgb;
    vec3 normal = texture(u_NormalMap, v_TexCoord).rgb;
    float roughness = texture(u_RoughnessMap, v_TexCoord).r;
    float metallic = texture(u_MetallicMap, v_TexCoord).r;
    float ao = texture(u_AOMap, v_TexCoord).r;

    // Diffuse Calculation
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(lightPosition - v_Pos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    diffuse *= ao;

    finalColor = (ambientStrength + diffuse) * color;
    out_color = vec4(finalColor, 1.0);
}
