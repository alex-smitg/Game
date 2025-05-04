#ifndef GAME_ASSET_MANAGER
#define GAME_ASSET_MANAGER

#include <map>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#include "mesh.h"
#include "material.h"
#include "shader.h"
#include "texture.h"

#include "models.h"
#include "shaders.h"


#define R_TEX1 2
#define R_TEX2 3
#define R_TEX3 4
#define R_TEX4 5
#define R_TEX5 6

class AssetManager {
public:


	Texture* createTexture(int texture) {
		unsigned char* image_data = nullptr;
		int width, height, channels;

		HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(texture), RT_RCDATA);
		HGLOBAL hData = LoadResource(NULL, hRes);
		DWORD image_size = SizeofResource(NULL, hRes);
		void* pRawData = LockResource(hData);


		image_data = stbi_load_from_memory(
			reinterpret_cast<stbi_uc*>(pRawData),
			image_size,
			&width, &height, &channels,
			STBI_rgb_alpha
		);
		Texture* tex = new Texture();

		glGenTextures(1, &tex->id);
		glBindTexture(GL_TEXTURE_2D, tex->id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);


		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

		stbi_image_free(image_data);

		return tex;
	}
	

	AssetManager() {
		for (auto const& [name, vertices] : models) {
			Mesh* mesh = new Mesh(vertices);
			meshes[name] = mesh;
		}

		
		_textures["terrain.png"] = createTexture(R_TEX1);
		_textures["test.png"] = createTexture(R_TEX2);
		_textures["font.png"] = createTexture(R_TEX3);
		_textures["redhoodhelicopter.png"] = createTexture(R_TEX4);
		_textures["bullet.png"] = createTexture(R_TEX5);

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
