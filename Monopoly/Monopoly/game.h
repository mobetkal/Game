#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <vector>
#include "graphics.h"
#include "card.h"
class Field;

enum class GameState { MODE_MENU, MAIN_MENU, PLAYERS_MENU, SET_NAMES, START_GAME, END };

class Game
{
	sf::RenderWindow window;
	GameState state;
	sf::Sprite bg;
	std::vector<sf::String> names;
	std::vector<DrawCard> chanceList, communityList;
	Graphics graphics;

	bool game_mode; // "true" when game is online
	int players; 
	
public:
	Game();
	//~Game();
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
	std::list<Field*> CreateList_ptrField(Graphics& graphics);
	Field* FindField(std::list<Field*> list, const int ID);
	void CreateChanceList(std::vector<DrawCard>& chanceCard);
	void CreateCommunityList(std::vector<DrawCard>& communityCard);
};