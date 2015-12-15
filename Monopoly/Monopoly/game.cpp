#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "buttonsprite.h"
#include "buttontext.h"
#include <fstream>
#include <Windows.h>
#include <vector>
#include "frame.h"

using namespace std;
using namespace sf;

Game::Game(void) : window(VideoMode(1100, 700, 32), "", Style::None)
{
	window.setPosition(Vector2i(100, 10));
	window.setKeyRepeatEnabled(true);
	state = GameState::END;

	if ((!bg_monopoly_logo.loadFromFile("graphics/bg_monopoly_logo.png")) || (!game_board.loadFromFile("graphics/game_board.png")))
		return;
	if ((!two_players.loadFromFile("graphics/two_players.png")) || (!two_players2.loadFromFile("graphics/two_players2.png")))
		return;
	if ((!three_players.loadFromFile("graphics/three_players.png")) || (!three_players2.loadFromFile("graphics/three_players2.png")))
		return;
	if ((!four_players.loadFromFile("graphics/four_players.png")) || (!four_players2.loadFromFile("graphics/four_players2.png")))
		return;
	if ((!frame.loadFromFile("graphics/frame.png")))
		return;

	if ((!font.loadFromFile("font/font.ttf")) || (!font_menus.loadFromFile("font/kawoszeh.ttf")))
		return;

	state = GameState::MODE_MENU;
}

void Game::SetGameMode(bool result)
{
	game_mode = result;
}

bool Game::GetGameMode() const
{
	return game_mode;
}

void Game::SetPlayers(int players)
{
	this->players = players;
}

int Game::GetPlayers() const
{
	return players;
}

void Game::Rungame()
{
	while (state != GameState::END)
	{
		switch (state)
		{
		case GameState::MODE_MENU:
		{
				  ModeMenu();
				  break;
		}
		case GameState::MAIN_MENU:
		{
				  MainMenu();
				  break;
		}
		case GameState::PLAYERS_MENU:
		{
				  PlayersMenu();
				  break;
		}
		case GameState::SET_NAMES:
		{
				  SetNames();
			      break;
		}
		case GameState::START_GAME:
		{
				  StartGame();
				  break;
		}
		default:
			break;
		}
	}
}

void Game::ModeMenu()
{
	bg.setTexture(bg_monopoly_logo);
	vector<ButtonText> buttons;
	buttons.emplace_back(L"Gra online", font_menus, 45, 400, GameState::MAIN_MENU);
	buttons.emplace_back(L"Gra offline", font_menus, 45, 470, GameState::MAIN_MENU);
	buttons.emplace_back(L"Wyjdź z gry", font_menus, 45, 540, GameState::END);

	ButtonText* hoverButton_text = nullptr;

	Text title(L"Wybierz tryb gry:", font_menus, 65);
	title.setPosition((1100 / 2 - title.getGlobalBounds().width / 2), 300);
	title.setColor(Color::Black);
		
	while (state == GameState::MODE_MENU)
	{
		Vector2f mouse(Mouse::getPosition(window));
		hoverButton_text = nullptr;
		for (auto& button : buttons)
		if (button.GetText().getGlobalBounds().contains(mouse))
		{
			button.GetText().setStyle(Text::Bold);
			button.GetText().setColor(Color(197, 0, 8, 255));
			hoverButton_text = &button;
		}
		else
		{
			button.GetText().setStyle(Text::Regular);
			button.GetText().setColor(Color::Black);
		}

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				state = GameState::END;
				break;
			}

			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left && hoverButton_text)
			{
				state = hoverButton_text->GetState(); 
				if (hoverButton_text == &buttons[0])
					SetGameMode(true);
				if (hoverButton_text == &buttons[1])
					SetGameMode(false);
				break;
			} 			
		}
		window.clear();
		window.draw(bg);
		window.draw(title);
		for (auto &button : buttons)
		{
			if (button.IsVisible())
				window.draw(button.GetText());
		}
		window.display();
	}
}


/*
Istotnych zmian dokonałem tylko w tej metodzie
*/
void Game::MainMenu()
{
	bg.setTexture(bg_monopoly_logo);

	//Przechowuję wszystkie przyciski w wektorze zamiast po prostu dla uproszczenia
	vector<ButtonText> text_buttons;
	text_buttons.emplace_back(L"Kontynuuj grę", font_menus, 45, 350, GameState::END, !GetGameMode()); //ma Pan tam zakomentowany stan CONTINUE, a musze jakis ustawic
	text_buttons.emplace_back(L"Nowa gra", font_menus, 45, 400, GameState::PLAYERS_MENU);
	text_buttons.emplace_back(L"Powrót", font_menus, 45, 450, GameState::MODE_MENU);
	text_buttons.emplace_back(L"Wyjdź z gry", font_menus, 45, 500, GameState::END);

	//ten wskaźnik zapamiętuje, który przycisk jest aktualnie aktywny, jak się najedzie myszką to ten wskaźnik jest odpowiednio umieszczany (kod nizej)
	ButtonText* hoverButton_text = nullptr;

	fstream save_file;
	save_file.open("save.txt", ios::in);

	while (state == GameState::MAIN_MENU)
	{		
		Vector2f mouse(Mouse::getPosition(window));
		//w kazdej iteracji najpierw ustawiam ten wskaznik na nullptr bo zakladam ze zaden przycisk nie jest zaznaczony
		hoverButton_text = nullptr;
		//przechodze przez wszystkie przyciski i sprawdzam czy mysz jest na jakims. Jeśli tak to ustawiam mu odpowiedni styl oraz zapamiętuje sobie we wskaźniku który to był
		for (auto& button : text_buttons)
		if (button.GetText().getGlobalBounds().contains(mouse))
		{
			button.GetText().setStyle(Text::Bold);
			button.GetText().setColor(Color(197, 0, 8, 255));
			hoverButton_text = &button;
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

			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left && hoverButton_text)//tutaj tylko sobie sprawdzam, czy któryś z przycisków jest aktywny w momencie kliknięcia myszy
			{
				state = hoverButton_text->GetState(); //no i jesli jest to ustawiam stan na taki jaki jest zapamietany w tym przycisku
				break;
			}		
		}
		window.clear();
		window.draw(bg);
		//tutaj wyswietlam te przyciski, które powinny być widoczne
		for (auto& button : text_buttons)
			if(button.IsVisible())
				window.draw(button.GetText());	
		window.display();
		
	}
	save_file.close();
}

void Game::PlayersMenu()
{
	bg.setTexture(bg_monopoly_logo);

	Text title(L"Wybierz liczbę graczy:", font_menus, 65);
	title.setPosition((1100 / 2 - title.getGlobalBounds().width / 2), 300);
	title.setColor(Color::Black);

	vector<ButtonText> text_buttons;
	text_buttons.emplace_back(L"Powrót", font_menus, 45, 550, GameState::MAIN_MENU);
	text_buttons.emplace_back(L"Wyjdź z gry", font_menus, 45, 600, GameState::END);

	ButtonText* hoverButton_text = nullptr;

	vector<ButtonSprite> img_buttons;
	img_buttons.emplace_back(make_pair(two_players, two_players2), 180, 410, GameState::SET_NAMES);
	img_buttons.emplace_back(make_pair(three_players, three_players2), 450, 410, GameState::SET_NAMES);
	img_buttons.emplace_back(make_pair(four_players, four_players2), 740, 410, GameState::SET_NAMES);
	
	ButtonSprite* hoverButton_img = nullptr;

	while (state == GameState::PLAYERS_MENU)
	{
		Vector2f mouse(Mouse::getPosition(window));
		hoverButton_text = nullptr;
		hoverButton_img = nullptr;
		for (auto& button : text_buttons)
		if (button.GetText().getGlobalBounds().contains(mouse))
		{
			button.GetText().setStyle(Text::Bold);
			button.GetText().setColor(Color(197, 0, 8, 255));
			hoverButton_text = &button;
		}
		else
		{
			button.GetText().setStyle(Text::Regular);
			button.GetText().setColor(Color::Black);
		}
		for (auto& button : img_buttons)
		if (button.GetSprite().getGlobalBounds().contains(mouse))
		{
			button.GetSprite().setTexture(button.GetTexture().second);
			hoverButton_img = &button;
		}
		else
		{
			button.GetSprite().setTexture(button.GetTexture().first);
		}
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				state = GameState::END;
				break;
			}

			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				if (hoverButton_text)
				{
					state = hoverButton_text->GetState();
				}
				if (hoverButton_img)
				{
					state = hoverButton_img->GetState();
					if (hoverButton_img == &img_buttons[0])
						SetPlayers(2);
					if (hoverButton_img == &img_buttons[1])
						SetPlayers(3);
					if (hoverButton_img == &img_buttons[2])
						SetPlayers(4);
				}
				break;
			}
		}
		window.clear();
		window.draw(bg);
		window.draw(title);
		for (auto& button : text_buttons)
		{
			if (button.IsVisible())
				window.draw(button.GetText());
		}
		for (auto& button : img_buttons)
		{
			if (button.IsVisible())
				window.draw(button.GetSprite());
		}
		window.display();
	}
}

void Game::SetNames()
{
	bg.setTexture(bg_monopoly_logo);

	Text title(L"Wpisz nicki graczy:", font_menus, 65);
	title.setPosition((float)(1100 / 2 - title.getGlobalBounds().width / 2), 290.0f);
	title.setColor(Color::Black);
	vector<Text> players;
	vector<Frame> frames;
	for (int i = 1; i <= GetPlayers(); ++i)
	{
		players.emplace_back(L"Player " + to_string(i) + ":", font_menus, 40);
		players[i - 1].setPosition((float)((1100 / 2 - title.getGlobalBounds().width / 2) + 20), (float)(380 + (i - 1) * 55));
		players[i - 1].setColor(Color::Black);
		frames.emplace_back(frame, 450, 380 + (i - 1) * 55, "", font_menus, 30);
	}
	vector<ButtonText> text_buttons;
	text_buttons.emplace_back(L"Powrót", font_menus, 45, 590, GameState::PLAYERS_MENU);
	text_buttons.emplace_back(L"Wyjdź z gry", font_menus, 45, 635, GameState::END);
	text_buttons.emplace_back(L"GRAJ", font_menus, 50, 920, 565, GameState::END);

	ButtonText* hoverButton_text = nullptr;
	Frame* onFrame = nullptr;

	while (state == GameState::SET_NAMES)
	{
		Vector2f mouse(Mouse::getPosition(window));
		hoverButton_text = nullptr;
		onFrame = nullptr;
		for (auto& button : text_buttons)
		if (button.GetText().getGlobalBounds().contains(mouse))
		{
			button.GetText().setStyle(Text::Bold);
			button.GetText().setColor(Color(197, 0, 8, 255));
			hoverButton_text = &button;
		}
		else
		{
			button.GetText().setStyle(Text::Regular);
			button.GetText().setColor(Color::Black);
		}
		
		Event event;
		while (window.pollEvent(event))
		{
			/*if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				state = GameState::END;
				break;
			}*/
			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left && hoverButton_text)
			{
				state = hoverButton_text->GetState();
				break;
			}
			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				for (auto& frame : frames)
				{
					if (frame.GetSprite().getGlobalBounds().contains(mouse))
						frame.TurnActive(true);
					else
						frame.TurnActive(false);
				}
			}
			if (event.type == Event::TextEntered)
			{
				for (auto& frame : frames)
				{
					if (frame.IsActive())
					{
						if (event.text.unicode == 8 && frame.GetString().size() != 0) // Backspace
						{
							frame.GetString().pop_back();
							frame.SetText(frame.GetString());
						}
						else if (event.text.unicode == 13) // Enter
						{
							frame.TurnActive(false);
						}
						else if (event.text.unicode > 31 && event.text.unicode < 128 && frame.GetString().size() < 14)
						{
							frame.GetString().push_back((char)event.text.unicode);
							frame.SetText(frame.GetString());
						}
					}
				}
			}
		}
		window.clear();
		window.draw(bg);
		window.draw(title);
		for (auto& player : players)
		{
			window.draw(player);
		}
		for (auto& button : text_buttons)
		{
			if (button.IsVisible())
				window.draw(button.GetText());
		}
		for (auto& frame : frames)
		{
			window.draw(frame.GetSprite());
			window.draw(frame.GetText());
		}
		window.display();
	}
}

void Game::StartGame()
{
	bg.setTexture(game_board);


	while (state == GameState::START_GAME)
	{

		window.clear();
		window.draw(bg);
		window.display();
	}
}