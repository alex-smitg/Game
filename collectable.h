#ifndef GAME_COLLECTABLE
#define GAME_COLLECTABLE


#include "actor.h"


enum Type {BEER, KIMCHI};

class Collectable : public Actor {
public:

	int livetime = 0;

	Type type = BEER;
};

#endif


