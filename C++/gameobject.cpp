#include "gameobject.h"
#include  "game.h"

GameObject::GameObject(const Game & mygame)
//epeidh ftiaksame refrence se game, opws kais ta const prepei na arxikopoiountai mesa sth lista arxikopoihshs
	: game(mygame)
{
}
