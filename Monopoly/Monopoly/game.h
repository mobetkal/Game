#pragma once
#include <SFML/Graphics.hpp>
#include "frame.h"

enum class GameState { MODE_MENU, MAIN_MENU, PLAYERS_MENU, SET_NAMES, START_GAME, END };

class Game
{
	sf::RenderWindow window;
	GameState state;
	sf::Texture bg_monopoly_logo, game_board;
	sf::Texture two_players, three_players, four_players, two_players2, three_players2, four_players2;
	sf::Texture frame, frame_active, frame_wrong, button_orange;
	std::vector<sf::Texture> pawns, pawns_forGame, dice;
	std::vector<std::string> names;
	sf::Sprite bg;
	sf::Font font, font_menus;
	bool game_mode; // "true" when game is online
	int players; 
public:
	Game(void);
	void SetGameMode(bool result);
	bool GetGameMode() const;
	void SetPlayers(int players);
	int GetPlayers() const;
	/*std::pair<Frame, Frame> ErrorCheck(std::vector<Frame> frame)
	{
		int frameSize = frame.size();
		for (int i = 0; i < frameSize; ++i)
		{
			for (int j = i + 1; j < frameSize; ++j)
			if (frame[i].GetString() == frame[j].GetString())
				return std::make_pair(frame[i], frame[i]);
		}
		return;
	}*/

	void Rungame();
	void ModeMenu();
	void MainMenu();
	void PlayersMenu();
	void SetNames();
	void StartGame();
};