#version 460 core
layout(location = 0) out vec4 out_color;

in vec3 v_Normal;
in vec2 v_TexCoord;

// uniform sampler2D albedoMap;
// uniform sampler2D normalMap;
// uniform sampler2D roughnessMap;
// uniform sampler2D metallicMap;
// uniform sampler2D ambientMap;

// uniform vec3 u_TintColor = vec3(1.0, 0.0, 1.0);
uniform vec3 u_Color;
uniform float u_Ambient;

void main()
{
    vec3 finalColor = vec3(1.0);

    // vec3 color = texture(albedoMap, v_TexCoord).rgb;
    // vec3 normal = texture(normalMap, v_TexCoord).rgb;
    // float roughness = texture(roughnessMap, v_TexCoord).r;
    // float metallic = texture(metallicMap, v_TexCoord).r;
    // float ambient = texture(ambientMap, v_TexCoord).r;
    
    // finalColor = color * ambient;
    finalColor = u_Color * u_Ambient;
    out_color = vec4(finalColor, 1.0);
}
