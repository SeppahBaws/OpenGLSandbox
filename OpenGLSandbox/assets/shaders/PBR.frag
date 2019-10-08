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

vec3 fresnel(vec3 normal, vec3 viewDirection, float fresnelPower, float fresnelMultiplier);

void main()
{
    vec3 albedo = texture(u_AlbedoMap, v_TexCoord).rgb;
    float ao = texture(u_AOMap, v_TexCoord).r;

    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(lightPosition - v_Pos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    diffuse *= ao;

    vec3 viewDir = normalize(u_ViewPos - v_Pos);
    vec3 fresnel = fresnel(norm, viewDir, 2, 3);

    vec3 finalColor = (ambientStrength + diffuse) * albedo + fresnel;
    out_color = vec4(finalColor, 1.0);
}


vec3 fresnel(vec3 normal, vec3 viewDirection, float fresnelPower, float fresnelMultiplier)
{
    float fresnel = pow((1 - abs(dot(normal, viewDirection))), fresnelPower) * fresnelMultiplier;

    return vec3(fresnel);
}