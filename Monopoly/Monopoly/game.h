#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>

enum class GameState { MODE_MENU, MAIN_MENU, PLAYERS_MENU, END };

class Game
{
	sf::RenderWindow window;
	GameState state;
	sf::Texture bg_monopoly_logo;
	sf::Texture two_players, three_players, four_players, two_players2, three_players2, four_players2;
	sf::Sprite bg, two_players_img, three_players_img, four_players_img;
	sf::Font font, font_menus;
	bool game_mode; // "true" when game is online
	int players; 

public:
	Game(void);
	void SetGameMode(bool result);
	bool GetGameMode() const;
	void SetPlayers(int players);
	int GetPlayers() const;

	void Rungame();
	void ModeMenu();
	void MainMenu();
	void PlayersMenu();

};