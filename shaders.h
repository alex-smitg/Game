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

in vec4 fragPosLightSpace;

uniform bool use_diffuse;
uniform bool emit;

uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 diffuse_color;

uniform float shine;
uniform float spec_factor;

uniform vec2 uv_scale;

uniform bool color_mode;
uniform vec3 color_color;

uniform sampler2D oText;

vec3 calculateDiffuse(vec3 lightColor, vec2 uv, vec3 norm) {
    vec3 diffuse;


    
    if (use_diffuse) {
        diffuse = texture(oText, vec2(uv.x, 1.0 - uv.y)).rgb * lightColor * diffuse_color;
    } else {
        diffuse = lightColor * diffuse_color;
    }
    
    return diffuse;
}

vec3 calculateSpecular(vec3 lightColor, vec3 norm, vec3 lightDir, vec3 viewDir, vec2 uv) {
    float nDot = dot(norm, lightDir);

    float spec;

    vec3 reflectDir = reflect(lightDir, norm);
    spec = pow(max(dot(viewDir, -reflectDir), 0.0), shine);
	
    vec3 specular = vec3(0.0, 0.0, 0.0);

    if (nDot > 0) {
        specular = spec * lightColor * spec_factor * lightColor * nDot;
    }

    return specular;
}







void main()
{
    if(color_mode == true) {
        FragColor = vec4(color_color, 1.0);
        return;
    }
    vec2 new_TexCoord = uv_scale * TexCoord;

    vec3 viewDir = normalize(viewPos - FragPos);
	vec3 norm = Normal;
	
    vec3 result = vec3(0.0, 0.0, 0.0);
    vec3 ambient = lightColor;

    if (use_diffuse) {
        ambient  = ambient * texture(oText, vec2(new_TexCoord.x, 1.0 - new_TexCoord.y)).rgb;
    }



    result = ambient + result + calculateDiffuse(lightColor, new_TexCoord, norm);

    if (emit) {
        result = vec3(diffuse_color);
    }

	result = texture(oText, vec2(new_TexCoord.x, 1.0 - new_TexCoord.y)).rgb;
    FragColor = vec4(result, 1.0);
	
	
}
)"},{"standart.vertex",R"(#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{

    FragPos = vec3(model * vec4(position, 1.0));
    Normal = aNormal;
	
    gl_Position = projection * view * vec4(FragPos, 1.0);

    TexCoord = aTexCoord;
})"},};