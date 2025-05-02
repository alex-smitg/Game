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
	std::string b = "0123456789";
	std::string c = """.,-+=*/\"'<>()[]!?""";

	glm::vec3 color = glm::vec3(1.0, 1.0, 1.0);

	Font(Shader* shader, Texture* texture) {
		int x = 0;
		for (char ch : a) {
			FontCharacter* fc = new FontCharacter(shader);
			fc->char_pos.x = x;
			fc->texture = texture;
			characters[ch] = fc;
			x += 1;
		}
		x = 0;
		int y = 1;
		for (char ch : b) {
			FontCharacter* fc = new FontCharacter(shader);
			fc->char_pos.x = x;
			fc->char_pos.y = y;
			fc->texture = texture;
			characters[ch] = fc;
			x += 1;
		}




		x = 0;
		y = 2;
		for (char ch : c) {
			FontCharacter* fc = new FontCharacter(shader);
			fc->char_pos.x = x;
			fc->char_pos.y = y;
			fc->texture = texture;
			characters[ch] = fc;
			x += 1;
		}
	}

	void draw(std::string text, glm::vec2 pos){
		float start_x = pos.x;

		for (char ch : text) {
			if (ch == '\n') {
				pos.y -= 2.2;
				pos.x = start_x;
				continue;
			}


			FontCharacter* fc = characters[ch];
			fc->color = color;
			fc->position = pos;
			pos.x += 2.0;
			fc->draw();

			
		}
	}

};

#endif