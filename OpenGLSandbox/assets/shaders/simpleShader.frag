#version 460 core
layout(location = 0) out vec4 out_color;

in vec3 v_Normal;
in vec2 v_TexCoord;

uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D roughnessMap;
uniform sampler2D metallicMap;
uniform sampler2D ambientMap;

const vec3 color = vec3(0.8f, 0.3f, 0.2f);
const vec3 lightDirection = vec3(0.0f, -2.0f, -2.5f);

vec3 CalculateDiffuse(vec3 normal)
{
    vec3 diffuse = color;
    float diffuseLightValue = dot(-normal, normalize(lightDirection));
    float halfLambert = diffuseLightValue * 0.5 + 0.5;
    diffuse *= halfLambert;
    return diffuse;
}

void main()
{
    //vec3 finalColor = vec3(1.0);
    //
    //vec3 color = texture(albedoMap, v_TexCoord).rgb;
    //vec3 normal = texture(normalMap, v_TexCoord).rgb;
    //float roughness = texture(roughnessMap, v_TexCoord).r;
    //float metallic = texture(metallicMap, v_TexCoord).r;
    //float ambient = texture(ambientMap, v_TexCoord).r;
    //
    //finalColor = color * ambient;
    //out_color = vec4(finalColor, 1.0);

    out_color = vec4(CalculateDiffuse(normalize(v_Normal)), 1.0f);
}
