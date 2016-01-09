#pragma once
#include <SFML/Graphics.hpp>
#include "graphics.h"

enum class GameState { MODE_MENU, MAIN_MENU, PLAYERS_MENU, SET_NAMES, START_GAME, END };


class Game
{
	sf::RenderWindow window;
	GameState state;
	sf::Sprite bg;
	std::vector<sf::String> names;
	Graphics graphics;

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
	void SetNames();
	void StartGame();
};