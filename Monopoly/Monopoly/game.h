#pragma once
#include <SFML/Graphics.hpp>

class Game
{
	sf::RenderWindow monopoly_game;
	enum GameState { MODE_MENU, MAIN_MENU, NEW_GAME, END };
	GameState state;
	sf::Texture bg_monopoly_logo;
	sf::Texture two_players, three_players, four_players, two_players2, three_players2, four_players2;
	sf::Sprite bg, two_players_img, three_players_img, four_players_img;
	sf::Font font, font_menus;
	bool game_mode; // "true" when game is online
	int players; 

public:
	Game(void);
	void setGameMode(bool result);
	bool getGameMode();
	void setPlayers(int players);
	int getPlayers();

	void rungame();
	void mode_menu();
	void main_menu();
	void players_menu();

};