#pragma once
#include <map>
#include <string>
std::map<std::string, std::string> shaders = {
{"font.fragment",R"(#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D tex;

uniform vec2 char_pos;
uniform vec3 color;

void main() {
	vec2 uv = TexCoord / 32.0 + (1.0/32.0)*char_pos;
	
	vec4 o = texture(tex, uv);

	o.a = o.r * o.g * o.b;

	FragColor = o * vec4(color, 1.0);
})"},{"font.vertex",R"(#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform vec2 position;

uniform bool in_world;
uniform mat4 view;
uniform mat4 model;

uniform float scale;
uniform mat4 projection;

void main() {
	if (in_world==false) {
	gl_Position = projection * vec4((aPos.x+position.x), (aPos.y+position.y), 0.0, 1.0); 
	} else {



	 gl_Position = projection * view * model * vec4((aPos.x+position.x), (aPos.y+position.y), 0.0, 1.0);
	}

	TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
})"},{"standart.fragment",R"(#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in mat3 TBN;

in vec4 fragPosLightSpace;

uniform bool use_diffuse;
uniform bool emit;

uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 diffuse_color;

uniform float shine;
uniform float reflection;
uniform float spec_factor;
uniform float ref_ratio;
uniform float normal_bump;
uniform float dif;


uniform vec2 uv_scale;

uniform float sky_val;



uniform bool color_mode;
uniform vec3 color_color;


uniform sampler2D oText;
uniform sampler2D sText;
uniform sampler2D nText;
uniform samplerCube skybox;
uniform sampler2D shadowMap;

struct PointLight {    
    vec3 position;
    vec3 color;

    float strength;
    float constant;
    float radius;
};


uniform int light_number;

#define NR_POINT_LIGHTS 64
uniform PointLight pointLights[NR_POINT_LIGHTS];




vec3 calculateDiffuse(vec3 lightColor, vec2 uv, vec3 norm, vec3 lightDir) {
    vec3 diffuse;
    float diff = max(dot(norm, lightDir), 0.0);

    
    if (use_diffuse) {
        diffuse = diff * texture(oText, vec2(uv.x, 1.0 - uv.y)).rgb * lightColor * dif * diffuse_color;
    } else {
        diffuse = diff * lightColor * dif * diffuse_color;
    }
    
    return diffuse;
}

vec3 calculateSpecular(vec3 lightColor, vec3 norm, vec3 lightDir, vec3 viewDir, vec2 uv) {
    float nDot = dot(norm, lightDir);

    float spec;

    if (use_blinn) {
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(norm, halfwayDir), 0.0), shine);
    } else {
         vec3 reflectDir = reflect(lightDir, norm);
        spec = pow(max(dot(viewDir, -reflectDir), 0.0), shine);
    }

    
 
    vec3 specular = vec3(0.0, 0.0, 0.0);

    if (nDot > 0) {
        if(use_specular) {
            specular = spec * lightColor * vec3(texture(sText, vec2(uv.x, 1.0 - uv.y))).r * spec_factor * lightColor * nDot;
        } else {
            specular = spec * lightColor * spec_factor * lightColor * nDot;
        }
        
    }

    return specular;
}




vec4 calculatePointLight(PointLight light, vec3 norm, vec3 FragPos, vec3 viewDir, vec2 uv) 
{
    float distance = length(light.position - FragPos);
    float attenuation = smoothstep(light.radius, 0, distance);

    vec3 lightDir = normalize(light.position - FragPos);

    vec3 diffuse = calculateDiffuse(light.color, uv, norm, lightDir);
    vec3 specular = calculateSpecular(light.color, norm, lightDir, viewDir, uv);

    diffuse *= light.strength * attenuation;
    specular *= light.strength * attenuation;
    vec3 result = (diffuse + specular);
    return vec4(result, 1.0) ;
}






void main()
{
    if(color_mode == true) {
        FragColor = vec4(color_color, 1.0);
        return;
    }
    vec2 new_TexCoord = uv_scale * TexCoord;
    vec3 norm = texture(nText, vec2(new_TexCoord.x, 1.0 - new_TexCoord.y)).rgb ;
    norm = norm * 2.0 - 1.0;
    norm.xy *= normal_bump;
    norm = normalize(TBN * norm);

    if(normal_bump < 0.01 || use_normal == false) {
        norm = normalize(Normal);
    }

    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0, 0.0, 0.0);

    vec3 ambient = lightColor;

    if (use_diffuse) {
        ambient  = ambient * texture(oText, vec2(new_TexCoord.x, 1.0 - new_TexCoord.y)).rgb;
    }
    for(int i = 0; i < light_number; i++) {
        result += calculatePointLight(pointLights[i], norm, FragPos, viewDir, new_TexCoord).rgb;
    }

    vec3 R = refract(-viewDir, normalize(-norm), ref_ratio);
    //vec3 refl = texture(skybox, R).rgb;
    //result += refl * reflection;

    result = ambient + result;


    if (emit) {
        result = vec3(diffuse_color);
    }


    FragColor = vec4(result, 1.0);
}
)"},{"standart.vertex",R"(#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

out vec3 ourColor;
out vec2 TexCoord;

out vec3 FragPos;
out vec3 Normal;
out mat3 TBN;
out vec4 fragPosLightSpace;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

void main()
{

    mat3 modelVector = mat3(transpose(inverse(model)));

    vec3 T = normalize(vec3(model * vec4(tangent, 0.0)));
    vec3 B = normalize(vec3(model * vec4(bitangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(aNormal, 0.0)));
    TBN = mat3(T, B, N);


    FragPos = vec3(model * vec4(position, 1.0));
    Normal = modelVector * aNormal;


    fragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);

    gl_Position = projection * view * vec4(FragPos, 1.0);

    TexCoord = aTexCoord;
})"},};