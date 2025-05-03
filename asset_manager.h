#ifndef GAME_ASSET_MANAGER
#define GAME_ASSET_MANAGER

#include <map>

#include "mesh.h"
#include "material.h"
#include "shader.h"
#include "texture.h"

#include "models.h"
#include "shaders.h"
#include "textures.h"

class AssetManager {
public:
	

	AssetManager() {
		for (auto const& [name, vertices] : models) {
			Mesh* mesh = new Mesh(vertices);
			meshes[name] = mesh;
		}

		for (auto const& [name, data] : textures) {
			Texture* texture = new Texture();

			int width = data.width;
			int height = data.height;
			int channels = data.channels;

			glGenTextures(1, &texture->id);
			glBindTexture(GL_TEXTURE_2D, texture->id);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data.data());


			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			
			_textures[name] = texture;
		}



		Shader* standart = new Shader(shaders["standart.vertex"], shaders["standart.fragment"]);
		standart->use();
		glUniform1i(glGetUniformLocation(standart->ID, "oText"), 0);

		Shader* font = new Shader(shaders["font.vertex"], shaders["font.fragment"]);
		font->use();
		glUniform1i(glGetUniformLocation(font->ID, "tex"), 0);

		_shaders["standart"] = standart;
		_shaders["font"] = font;



	}

	Texture* getTexture(std::string name) {
		return _textures[name];
	}

	Mesh* getMesh(std::string name) {
		return meshes[name];
	}

	Shader* getShader(std::string name)  {
		return _shaders[name];
	}

	Material* createMaterial(std::string name) {
		Material* material = new Material();
		_materials[name] = material;
		return material;
	}
	Material* getMaterial(std::string name) {
		return _materials[name];
	}


private:
	std::map<std::string, Mesh*> meshes;
	std::map<std::string, Shader*> _shaders;
	std::map<std::string, Material*> _materials;
	std::map<std::string, Texture*> _textures;

};



#endif
