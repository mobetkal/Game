#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"
#include <fstream>
#include <Windows.h>
#include <vector>

using namespace std;

using namespace sf;

Game::Game(void) :window(VideoMode(1100, 700, 32), "", Style::None)
{
	state = GameState::END;

	if ((!bg_monopoly_logo.loadFromFile("graphics/bg_monopoly_logo.png")))
		return;
	if ((!two_players.loadFromFile("graphics/two_players.png")) || (!two_players2.loadFromFile("graphics/two_players2.png")))
		return;
	if ((!three_players.loadFromFile("graphics/three_players.png")) || (!three_players2.loadFromFile("graphics/three_players2.png")))
		return;
	if ((!four_players.loadFromFile("graphics/four_players.png")) || (!four_players2.loadFromFile("graphics/four_players2.png")))
		return;

	if ((!font.loadFromFile("font/font.ttf")) || (!font_menus.loadFromFile("font/kawoszeh.ttf")))
		return;

	state = GameState::MODE_MENU;
}

void Game::setGameMode(bool result)
{
	game_mode = result;
}

bool Game::getGameMode()
{
	return game_mode;
}

void Game::setPlayers(int players)
{
	this->players = players;
}

int Game::getPlayers()
{
	return players;
}

void Game::rungame()
{
	while (state != GameState::END)
	{
		switch (state)
		{
		case GameState::MODE_MENU:
		{
				  mode_menu();
				  break;
		}
		case GameState::MAIN_MENU:
		{
				  main_menu();
				  break;
		}
		case 2:
		{
				  players_menu();
				  break;
		}
		default:
			break;
		}
	}
}

void Game::mode_menu()
{

	window.setPosition(Vector2i(100, 10));
	window.setKeyRepeatEnabled(false);
	bg.setTexture(bg_monopoly_logo);

	Text title(L"Wybierz tryb gry:", font_menus, 65);
	title.setPosition((1100 / 2 - title.getGlobalBounds().width / 2), 300);
	title.setColor(Color::Black);

	Text online(L"Gra online", font_menus, 45);
	online.setPosition((1100 / 2 - online.getGlobalBounds().width / 2), 400);

	Text offline(L"Gra offline", font_menus, 45);
	offline.setPosition((1100 / 2 - offline.getGlobalBounds().width / 2), 470);

	Text close_game(L"Wyjdź z gry", font_menus, 45);
	close_game.setPosition((1100 / 2 - close_game.getGlobalBounds().width / 2), 540);


	
	while (state == GameState::MODE_MENU)
	{
		window.clear();
		window.draw(bg);
		window.draw(title);
		window.draw(online);
		window.draw(offline);
		window.draw(close_game);
		window.display();

		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				state = GameState::END;
				break;
			}

			// close game
			if (close_game.getGlobalBounds().contains(mouse))
			{
				close_game.setStyle(Text::Bold);
				close_game.setColor(Color(197, 0, 8, 255));
				if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				{
					state = GameState::END;
					break;
				}
			}
			else
			{
				close_game.setStyle(Text::Regular);
				close_game.setColor(Color::Black);
			}

			// online game
			if (online.getGlobalBounds().contains(mouse))
			{
				online.setStyle(Text::Bold);
				online.setColor(Color(197, 0, 8, 255));
				if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				{
					setGameMode(true);
					state = GameState::MAIN_MENU;
					break;
				}
			}
			else
			{
				online.setStyle(Text::Regular);
				online.setColor(Color::Black);
			}

			// offline game
			if (offline.getGlobalBounds().contains(mouse))
			{
				offline.setStyle(Text::Bold);
				offline.setColor(Color(197, 0, 8, 255));
				if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				{
					setGameMode(false);
					state = GameState::MAIN_MENU;
					break;
				}
			}
			else
			{
				offline.setStyle(Text::Regular);
				offline.setColor(Color::Black);
			}

		}
		
	}
}


/*
Istotnych zmian dokonałem tylko w tej metodzie
*/
void Game::main_menu()
{
	window.setPosition(Vector2i(100, 10));
	window.setKeyRepeatEnabled(false);
	bg.setTexture(bg_monopoly_logo);


	//Przechowuję wszystkie przyciski w wektorze zamiast po prostu dla uproszczenia
	vector<MenuButton> buttons;
	buttons.emplace_back(L"Kontynuuj grę", font_menus, 45, 350, GameState::END, !getGameMode()); //ma Pan tam zakomentowany stan CONTINUE, a musze jakis ustawic
	buttons.emplace_back(L"Nowa gra", font_menus, 45, 400, GameState::NEW_GAME);
	buttons.emplace_back(L"Powrót", font_menus, 45, 450, GameState::MODE_MENU);
	buttons.emplace_back(L"Wyjdź z gry", font_menus, 45, 500, GameState::END);

	//ten wskaźnik zapamiętuje, który przycisk jest aktualnie aktywny, jak się najedzie myszką to ten wskaźnik jest odpowiednio umieszczany (kod nizej)
	MenuButton* hoverButton = nullptr;


	std::fstream save_file;
	save_file.open("save.txt", std::ios::in);

	while (state == GameState::MAIN_MENU)
	{		
		Vector2f mouse(Mouse::getPosition(window));
		//w kazdej iteracji najpierw ustawiam ten wskaznik na nullptr bo zakladam ze zaden przycisk nie jest zaznaczony
		hoverButton = nullptr;
		//przechodze przez wszystkie przyciski i sprawdzam czy mysz jest na jakims. Jeśli tak to ustawiam mu odpowiedni styl oraz zapamiętuje sobie we wskaźniku który to był
		for(auto& button : buttons)
		if (button.GetText().getGlobalBounds().contains(mouse))
		{
			button.GetText().setStyle(Text::Bold);
			button.GetText().setColor(Color(197, 0, 8, 255));
			hoverButton = &button;
		}
		else
		{
			button.GetText().setStyle(Text::Regular);
			button.GetText().setColor(Color::Black);
		}


		Event event;
		//teraz obsługa eventów się bardzo uprościła
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				state = GameState::END;
				break;
			}

			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left && hoverButton)//tutaj tylko sobie sprawdzam, czy któryś z przycisków jest aktywny w momencie kliknięcia myszy
			{
				state = hoverButton->GetState(); //no i jesli jest to ustawiam stan na taki jaki jest zapamietany w tym przycisku
				break;
			}		
		}
		window.clear();
		window.draw(bg);
		//tutaj wyswietlam te przyciski, które powinny być widoczne
		for (auto& button : buttons)
			if(button.IsVisible())
				window.draw(button.GetText());	
		window.display();
		
	}
	save_file.close();
}

void Game::players_menu()
{
	window.setPosition(Vector2i(100, 10));
	window.setKeyRepeatEnabled(false);
	bg.setTexture(bg_monopoly_logo);

	Text title(L"Wybierz liczbę graczy:", font_menus, 65);
	title.setPosition((1100 / 2 - title.getGlobalBounds().width / 2), 300);
	title.setColor(Color::Black);

	Text back(L"Powrót", font_menus, 45);
	back.setPosition((1100 / 2 - back.getLocalBounds().width / 2), 550);

	Text close_game(L"Wyjdź z gry", font_menus, 45);
	close_game.setPosition((1100 / 2 - close_game.getLocalBounds().width / 2), 600);

	// Sprites
	two_players.setSmooth(true);
	two_players_img.setTexture(two_players);
	two_players_img.setPosition(180, 410);

	three_players.setSmooth(true);
	three_players_img.setTexture(three_players);
	three_players_img.setPosition(450, 410);

	four_players.setSmooth(true);
	four_players_img.setTexture(four_players);
	four_players_img.setPosition(740, 410);

	while (state == GameState::NEW_GAME)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				state = GameState::END;
				break;
			}

			// close game
			if (close_game.getGlobalBounds().contains(mouse))
			{
				close_game.setStyle(Text::Bold);
				close_game.setColor(Color(197, 0, 8, 255));
				if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				{
					state = GameState::END;
					break;
				}
			}
			else
			{
				close_game.setStyle(Text::Regular);
				close_game.setColor(Color::Black);
			}

			// back to main menu
			if (back.getGlobalBounds().contains(mouse))
			{
				back.setStyle(Text::Bold);
				back.setColor(Color(197, 0, 8, 255));
				if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				{
					state = GameState::MAIN_MENU;
					break;
				}
			}
			else
			{
				back.setStyle(Text::Regular);
				back.setColor(Color::Black);
			}

			// two_players
			if (two_players_img.getGlobalBounds().contains(mouse))
			{
				two_players_img.setTexture(two_players2);
				if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				{
					setPlayers(2);
					//state = START_GAME;
					break;
				}
			}
			else
			{
				two_players_img.setTexture(two_players);
			}
			
			// three_players
			if (three_players_img.getGlobalBounds().contains(mouse))
			{
				three_players_img.setTexture(three_players2);
				if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				{
					setPlayers(3);
					//state = START_GAME;
					break;
				}
			}
			else
			{
				three_players_img.setTexture(three_players);
			}

			// four_players
			if (four_players_img.getGlobalBounds().contains(mouse))
			{
				four_players_img.setTexture(four_players2);
				if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				{
					setPlayers(4);
					//state = START_GAME;
					break;
				}
			}
			else
			{
				four_players_img.setTexture(four_players);
			}
		}
		window.clear();
		window.draw(bg);
		window.draw(title);
		window.draw(two_players_img);
		window.draw(three_players_img);
		window.draw(four_players_img);
		window.draw(back);
		window.draw(close_game);
		window.display();
	}
}