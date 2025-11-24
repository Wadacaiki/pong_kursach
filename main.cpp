#include "game.h"
#include <SFML/Audio.hpp>

using namespace sf;

int main()
{
	sf::Music music;
	music.openFromFile("music.ogg");
	music.setLoop(true);
	music.setVolume(100);
	music.play();


	Game game;
	game.play();
	return 0;
}