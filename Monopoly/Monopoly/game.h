#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include <utility>

//wyjąłem to z klasy Game, bo jest mi potrzebne też w klasie MenuButton, którą utworzyłem
//przerobiłem też na enum class bo to jest bezpieczniejsza wersja enuma
enum class GameState { MODE_MENU, MAIN_MENU, PLAYERS_MENU, END };

//Utworzyłem tą klasę aby uprościć konstrukcję w obsłudze poszczególnych menu
//Można w razie potrzeby sobie rozbudować to
class Button_Text
{
	sf::Text button_text;
	GameState state;
	bool visible;
public:
	Button_Text(const sf::String& text, const sf::Font& font, unsigned int characterSize, float y, GameState state, bool visibility = true)
		:
		button_text(text, font, characterSize),
		state(state),
		visible(visibility)
	{
		button_text.setPosition((1100 / 2 - button_text.getGlobalBounds().width / 2), y);
	}
	sf::Text& GetText()
	{
		return button_text;
	}
	GameState GetState() const
	{
		return state;
	}
	bool IsVisible() const
	{
		return visible;
	}
};

class Button_Sprite
{
	sf::Sprite button_sprite;
	GameState state;
	bool visible;
	std::pair<sf::Texture, sf::Texture> texture;
public:
	Button_Sprite(std::pair<sf::Texture, sf::Texture> texture, float x, float y, GameState state, bool visibility = true)
		:
		state(state),
		visible(visibility)
	{
		texture.first.setSmooth(true);
		texture.second.setSmooth(true);
		this->texture.first = texture.first;
		this->texture.second = texture.second;
		button_sprite.setPosition(x, y);
	}
	std::pair<sf::Texture, sf::Texture>& GetTexture()
	{
		return texture;
	}
	sf::Sprite& GetSprite()
	{
		return button_sprite;
	}
	GameState GetState() const
	{
		return state;
	}
	bool IsVisible() const
	{
		return visible;
	}
};

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