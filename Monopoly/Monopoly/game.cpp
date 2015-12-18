#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"
#include "buttonsprite.h"
#include "buttontext.h"
#include <fstream>
#include <Windows.h>
#include <vector>
#include "frame.h"
#include "pawn.h"
#include "dice.h"
#include "icon.c"
#include "player.h"

using namespace std;
using namespace sf;

Game::Game(void) : window(VideoMode(1100, 700, 32), "", Style::None)
{
	window.setPosition(Vector2i(100, 10));
	window.setKeyRepeatEnabled(true);
	window.setIcon(MonopolyIcon.width, MonopolyIcon.height, MonopolyIcon.pixel_data);

	state = GameState::END;

	if ((!bg_monopoly_logo.loadFromFile("graphics/bg_monopoly_logo.png")) || (!game_board.loadFromFile("graphics/game_board.png")))
		return;
	if ((!two_players.loadFromFile("graphics/two_players.png")) || (!two_players2.loadFromFile("graphics/two_players2.png")))
		return;
	if ((!three_players.loadFromFile("graphics/three_players.png")) || (!three_players2.loadFromFile("graphics/three_players2.png")))
		return;
	if ((!four_players.loadFromFile("graphics/four_players.png")) || (!four_players2.loadFromFile("graphics/four_players2.png")))
		return;
	if ((!frame.loadFromFile("graphics/frame.png")) || (!frame_active.loadFromFile("graphics/frame_active.png")) || (!frame_wrong.loadFromFile("graphics/frame_wrong.png")))
		return;
	vector<Texture> pawn(4);
	int pawnSize = pawn.size();
	if ((!pawn[1].loadFromFile("graphics/pawn/yellow.png")) || (!pawn[2].loadFromFile("graphics/pawn/green.png")))
		return;
	if ((!pawn[3].loadFromFile("graphics/pawn/red.png")) || (!pawn[0].loadFromFile("graphics/pawn/blue.png")))
		return;
	for (int i = 0; i < pawnSize; ++i)
	{
		pawn[i].setSmooth(true);
		Game::pawns.emplace_back(pawn[i]);
	}
	if ((!pawn[1].loadFromFile("graphics/pawn/yellow_pawn.png")) || (!pawn[2].loadFromFile("graphics/pawn/green_pawn.png")))
		return;
	if ((!pawn[3].loadFromFile("graphics/pawn/red_pawn.png")) || (!pawn[0].loadFromFile("graphics/pawn/blue_pawn.png")))
		return;
	for (int i = 0; i < pawnSize; ++i)
	{
		pawn[i].setSmooth(true);
		Game::pawns_forGame.emplace_back(pawn[i]);
	}
	vector<Texture> dice(6);
	int diceSize = dice.size();
	if ((!dice[0].loadFromFile("graphics/dice/meshNumber_1.png")) || (!dice[1].loadFromFile("graphics/dice/meshNumber_2.png")))
		return;
	if ((!dice[2].loadFromFile("graphics/dice/meshNumber_3.png")) || (!dice[3].loadFromFile("graphics/dice/meshNumber_4.png")))
		return;
	if ((!dice[4].loadFromFile("graphics/dice/meshNumber_5.png")) || (!dice[5].loadFromFile("graphics/dice/meshNumber_6.png")))
		return;
	for (int i = 0; i < diceSize; ++i)
	{
		dice[i].setSmooth(true);
		Game::dice.emplace_back(dice[i]);
	}
	if ((!button_orange.loadFromFile("graphics/button_orange.png")))
		return;

	// Fonts
	if ((!font.loadFromFile("font/font.ttf")) || (!font_menus.loadFromFile("font/kawoszeh.ttf")))
		return;
	
	state = GameState::MODE_MENU;
	//state = GameState::START_GAME;
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
	buttons.emplace_back(L"Wybierz tryb gry:", font_menus, 65, 300.0f, false);
	buttons.emplace_back(L"Gra online", font_menus, 45, 400.0f, GameState::MAIN_MENU);
	buttons.emplace_back(L"Gra offline", font_menus, 45, 470.0f, GameState::MAIN_MENU);
	buttons.emplace_back(L"Wyjdź z gry", font_menus, 45, 540.0f, GameState::END);

	ButtonText* hoverButton_text = nullptr;
		
	while (state == GameState::MODE_MENU)
	{
		Vector2f mouse(Mouse::getPosition(window));
		hoverButton_text = nullptr;
		for (auto& button : buttons)
		if (button.GetText().getGlobalBounds().contains(mouse) && button.MakeStyle())
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
		for (auto &button : buttons)
			window.draw(button.GetText());
		window.display();
	}
}


void Game::MainMenu()
{
	bg.setTexture(bg_monopoly_logo);

	vector<ButtonText> text_buttons;
	if (!game_mode)
		text_buttons.emplace_back(L"Kontynuuj grę", font_menus, 45, 350.0f, GameState::END); // Dorobić CONTINUE
	text_buttons.emplace_back(L"Nowa gra", font_menus, 45, 410.0f, GameState::PLAYERS_MENU);
	text_buttons.emplace_back(L"Powrót", font_menus, 45, 470.0f, GameState::MODE_MENU);
	text_buttons.emplace_back(L"Wyjdź z gry", font_menus, 45, 530.0f, GameState::END);

	ButtonText* hoverButton_text = nullptr;

	fstream save_file;
	save_file.open("save.txt", ios::in);

	while (state == GameState::MAIN_MENU)
	{		
		Vector2f mouse(Mouse::getPosition(window));
		hoverButton_text = nullptr;
		for (auto& button : text_buttons)
		if (button.GetText().getGlobalBounds().contains(mouse) && button.MakeStyle())
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
				break;
			}		
		}
		window.clear();
		window.draw(bg);
		for (auto& button : text_buttons)
			window.draw(button.GetText());	
		window.display();
		
	}
	save_file.close();
}

void Game::PlayersMenu()
{
	bg.setTexture(bg_monopoly_logo);

	vector<ButtonText> text_buttons;
	text_buttons.emplace_back(L"Wybierz liczbę graczy:", font_menus, 65, 300.0f, false);
	text_buttons.emplace_back(L"Powrót", font_menus, 45, 550.0f, GameState::MAIN_MENU);
	text_buttons.emplace_back(L"Wyjdź z gry", font_menus, 45, 600.0f, GameState::END);

	ButtonText* hoverButton_text = nullptr;

	vector<ButtonSprite> img_buttons;
	img_buttons.emplace_back(make_pair(two_players, two_players2), 180.0f, 410.0f, GameState::SET_NAMES);
	img_buttons.emplace_back(make_pair(three_players, three_players2), 450.0f, 410.0f, GameState::SET_NAMES);
	img_buttons.emplace_back(make_pair(four_players, four_players2), 740.0f, 410.0f, GameState::SET_NAMES);
	
	ButtonSprite* hoverButton_img = nullptr;

	while (state == GameState::PLAYERS_MENU)
	{
		Vector2f mouse(Mouse::getPosition(window));
		hoverButton_text = nullptr;
		hoverButton_img = nullptr;
		for (auto& button : text_buttons)
		if (button.GetText().getGlobalBounds().contains(mouse) && button.MakeStyle())
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
		for (auto& button : text_buttons)
			window.draw(button.GetText());
		for (auto& button : img_buttons)
			window.draw(button.GetSprite());
		window.display();
	}
}

void Game::SetNames()
{
	bg.setTexture(bg_monopoly_logo);

	vector<Text> players;
	vector<Frame> frames;
	vector<Sprite> pawn;
	for (int i = 1; i <= GetPlayers(); ++i)
	{
		players.emplace_back(L"Player " + to_string(i) + ":", font_menus, 40);
		players[i - 1].setPosition(290.0f, (float)(380 + (i - 1) * 55));
		players[i - 1].setColor(Color::Black);
		frames.emplace_back(make_pair(frame, frame_active), 445.0f, (float)(380 + (i - 1) * 55), "", font_menus, 30);
		pawn.emplace_back();
		pawn[i - 1].setTexture(pawns[i-1]);
		pawn[i - 1].setPosition(250.0f, (float)(380 + (i - 1) * 55));
	}
	for (auto& frame : frames)
		frame.GetSprite().setTexture(frame.GetTexture().first);
	vector<ButtonText> text_buttons;
	text_buttons.emplace_back(L"Wpisz nicki graczy:", font_menus, 65, 290.0f, false);
	text_buttons.emplace_back(L"Powrót", font_menus, 45, 590.0f, GameState::PLAYERS_MENU);
	text_buttons.emplace_back(L"Wyjdź z gry", font_menus, 45, 635.0f, GameState::END);
	text_buttons.emplace_back(L"GRAJ", font_menus, 50, 920, 565.0f, GameState::START_GAME);

	ButtonText* hoverButton_text = nullptr;

	while (state == GameState::SET_NAMES)
	{
		Vector2f mouse(Mouse::getPosition(window));
		hoverButton_text = nullptr;
		for (auto& button : text_buttons)
		if (button.GetText().getGlobalBounds().contains(mouse) && button.MakeStyle())
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
				if (state == GameState::START_GAME)
				{
					bool wrong = false;
					int frameSize = frames.size();
					for (int i = 0; i < frameSize; ++i)
					{
						for (int j = i + 1; j < frameSize; ++j)
						if (frames[i].GetString() == frames[j].GetString())
						{
							frames[i].GetSprite().setTexture(frame_wrong);
							frames[j].GetSprite().setTexture(frame_wrong);
							state = GameState::SET_NAMES;
							wrong = true;
						}
					}
					for (auto& frame : frames)
					{
						if (frame.GetString() == "" || frame.GetString() == " ")
						{
							frame.GetSprite().setTexture(frame_wrong);
							state = GameState::SET_NAMES;
						}
						else if (!wrong)
							names.emplace_back(frame.GetString());
					}
				}
				break;
			}
			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				for (auto& frame : frames)
				{
					if (frame.GetSprite().getGlobalBounds().contains(mouse))
					{
						frame.TurnActive(true);
						frame.GetSprite().setTexture(frame.GetTexture().second);
					}
					else
					{
						frame.TurnActive(false);
						frame.GetSprite().setTexture(frame.GetTexture().first);
					}
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
							frame.GetSprite().setTexture(frame.GetTexture().first);
						}
						else if (event.text.unicode > 31 && event.text.unicode < 123 && frame.GetString().size() < 15)
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
		for (auto& player : players)
			window.draw(player);

		for (auto& elem : pawn)
			window.draw(elem);

		for (auto& button : text_buttons)
			window.draw(button.GetText());
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
	Dice LeftDice(dice, 800.0f, 100.0f);
	Dice RightDice(dice, 850.0f, 100.0f);
	vector<Pawn> pawns;
	for (int i = 1; i <= GetPlayers(); ++i)
		pawns.emplace_back(pawns_forGame[i - 1], 0);
	vector<Player> player;
	for (int i = 1; i <= GetPlayers(); ++i)
	{
		player.emplace_back(names[i - 1], pawns[i - 1], GetPlayers() );
	}

	vector<ButtonSprite> imgButtons;
	imgButtons.emplace_back(button_orange, 910.0f, 105.0f);

	vector<ButtonText> textButtons;
	textButtons.emplace_back(L"Rzuć kostkami!", font_menus, 17, 927.0f, 113.0f);

	ButtonSprite* hoverImgButton = nullptr;
	ButtonText* hoverTextButton = nullptr;

	while (state == GameState::START_GAME)
	{
		Vector2f mouse(Mouse::getPosition(window));
		hoverImgButton = nullptr;
		hoverTextButton = nullptr;

		for (auto& button : imgButtons)
		if (button.GetSprite().getGlobalBounds().contains(mouse))
		{
			hoverImgButton = &button;
		}
		for (auto& button : textButtons)
		if (button.GetText().getGlobalBounds().contains(mouse))
		{
			hoverTextButton = &button;
			button.GetText().setStyle(Text::Underlined);
		}
		else
		{
			button.GetText().setStyle(Text::Regular);
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
				if (hoverImgButton == &imgButtons[0])
				{
					int SumMesh = LeftDice.RollDice() + RightDice.RollDice();
					if (SumMesh != 12)
						player[0].GetPawn().move(SumMesh);
					//else
						//red.GoJail();
				}
				//break;
			}
		}


		window.clear();
		window.draw(bg);
		for (auto& pawn : player)
			window.draw(pawn.GetPawn().GetSprite());
		window.draw(LeftDice.GetSprite());
		window.draw(RightDice.GetSprite());
		window.draw(imgButtons[0].GetSprite());
		for (auto& button : textButtons)
			window.draw(button.GetText());
		window.display();
	}
}