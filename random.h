#ifndef GAME_RANDOM
#define GAME_RANDOM


#include <string>
#include <vector>
#include <random>

class Random {
public:
	std::vector<std::string> s = {
		"a", "i", "u", "e", "o",
		"ka", "ki", "ku", "ke", "ko",
		"sa", "shi", "su", "se", "so",
		"ta", "chi", "tsu", "te", "to",
		"na", "ni", "nu", "ne", "no",
		"ha", "hi", "hu", "he", "ho",
		"ma", "mi", "mu", "me", "mo",
		"ya", "yu", "yo", "wa", "wo",
		"ra", "ri", "ru", "re", "ro",
		"n", "kim"
	};

	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<int> distX;
	std::uniform_int_distribution<int> distY;
	std::uniform_int_distribution<int> distZ;


	Random() : distX(1, 46), distY(0, 3), distZ(0, 100000), gen(std::random_device{}())
	{}

	float randfloat() {
		return distZ(gen) / 100000.0f;
	}


	std::string generate_random_name() {
		std::string out = "";

		


		int len = distY(gen) + 2;

		for (int i = 0; i < len ; i++) {
			

			int a = distX(gen);

			out += s[a];
		}
		return out;
	}
};


#endif