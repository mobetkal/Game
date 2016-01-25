#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <vector>
#include "graphics.h"
#include "card.h"
#include "dice.h"
#include "drawcard.h"
class Field;

enum class GameState { MODE_MENU, MAIN_MENU, PLAYERS_MENU, SET_NAMES, START_GAME, TRADE, END };
#include "buttonsprite.h"
#include "buttontext.h"
#include "DetectMemoryLeaks.h"

class Game
{
	sf::RenderWindow window;
	GameState state;
	sf::Sprite bg, tradeBG;
	std::vector<sf::String> names;
	std::vector<DrawCard*> chanceList, communityList;
	std::list<Field*> fields;
	Graphics graphics;

	std::vector<Pawn> pawns;
	std::vector<Player> player;
	std::vector<ButtonText> textButtons;
	std::vector<ButtonSprite> imgButtons;

	bool game_mode; // "true" when game is online
	int players; 
	
public:
	Game();
	~Game();

	//Short Methods
	void SetGameMode(bool result);
	bool GetGameMode() const;
	void SetPlayers(int players);
	int GetPlayers() const;

	//Game Methods
	void Rungame();
	void ModeMenu();
	void MainMenu();
	void PlayersMenu();
	void SetNames();
	void StartGame();

	//Creating Methods
	void CreatePlayersAndPawns();
	void CreateGameTextButtons();
	std::list<Field*> CreateList_ptrField(Graphics& graphics);
	void CreateChanceList(std::vector<DrawCard*>& chanceCard);
	void CreateCommunityList(std::vector<DrawCard*>& communityCard);
	void CreateTrade(Player* activePlayer, Player* secondPlayer);

	//Methods of checking
	MiniCard* CheckHoverStatusCard();
	Player* CheckActivePlayer();
	ButtonText* CheckHoverTextButtonInMenu(std::vector<ButtonText>& textButtons);
	ButtonSprite* CheckHoverSpriteButtonInMenu(std::vector<ButtonSprite>& imgButtons);
	ButtonSprite* Game::CheckHoverSpriteInGame(
		Player* activePlayer,
		Field*& FindedCard,
		Field* ShowBigCard,
		ButtonSprite& rollDiceButton,
		ButtonSprite& nextPlayerButton,
		ButtonSprite& bidButton,
		ButtonSprite& buyButton,
		ButtonSprite& buildButton,
		ButtonSprite& depositButton,
		ButtonSprite& tradeButton
		);

	//Methods of finding
	Field* FindField(std::list<Field*> list, const int ID);

	//Response Methods
	void DrawButtonOnWindow(sf::RenderTarget& target, std::pair<ButtonSprite, ButtonText>& button);
	void DrawFindedCardAndSetAlerts(
		Field*& FindedCard, 
		Player*& activePlayer, 
		sf::Text& textButton, 
		std::pair<ButtonSprite, ButtonText>& buyButton,
		std::pair<ButtonSprite, ButtonText>& bidButton,
		bool& ShownCard
		);
	void GoToNextPlayer(Player* activePlayer, ButtonText& button);
	bool RollDiceAfterThrowingDoublet(Player* activePlayer, Dice& firstDice, Dice& secondDice, ButtonText& button, bool ShownCard);
	bool RollDiceBeforeThrowingDoublet(Player* activePlayer, Dice& firstDice, Dice& secondDice, ButtonText& button, bool ShownCard);

	//Activating Methods
	void ActivateRollAndSkipPlayerButtons(Player* activePlayer, ButtonSprite& RollDiceButton, ButtonSprite& SkipPlayerButton);
	void ActivateTradeButton(ButtonSprite& button, Player* activePlayer);

};