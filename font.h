#ifndef GAME_FONT
#define GAME_FONT


#include "font_character.h"
#include "texture.h"
#include <string>
#include <map>

class Font {
public:
	


	std::map<char, FontCharacter*> characters;

	std::string a = "abcdefghijklmnopqrstuvwxyz ";

	Font(Shader* shader, Texture* texture) {
		int x = 0;
		for (char ch : a) {
			FontCharacter* fc = new FontCharacter(shader);
			fc->char_pos.x = x;
			fc->texture = texture;
			characters[ch] = fc;
			x += 1;
		}
	}

	void draw(std::string text, glm::vec2 pos){
		
		for (char ch : text) {
			FontCharacter* fc = characters[ch];
			fc->position = pos;
			pos.x += 2.0;
			fc->draw();
		}
	}

};

#endif