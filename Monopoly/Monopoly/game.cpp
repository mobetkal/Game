#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"
#include <fstream>

using namespace sf;

Game::Game(void) :monopoly_game(VideoMode(1100, 700, 32), "", Style::None)
{
	state = END;

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

	state = MODE_MENU;
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
	while (state != END)
	{
		switch (state)
		{
		case 0:
		{
				  mode_menu();
				  break;
		}
		case 1:
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

	monopoly_game.setPosition(Vector2i(100, 10));
	monopoly_game.setKeyRepeatEnabled(false);
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

	while (state == MODE_MENU)
	{
		Vector2f mouse(Mouse::getPosition(monopoly_game));
		Event event;
		while (monopoly_game.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				state = END;
				break;
			}

			// close game
			if (close_game.getGlobalBounds().contains(mouse))
			{
				close_game.setStyle(Text::Bold);
				close_game.setColor(Color(197, 0, 8, 255));
				if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				{
					state = END;
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
					state = MAIN_MENU;
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
					state = MAIN_MENU;
					break;
				}
			}
			else
			{
				offline.setStyle(Text::Regular);
				offline.setColor(Color::Black);
			}

		}
		monopoly_game.clear();
		monopoly_game.draw(bg);
		monopoly_game.draw(title);
		monopoly_game.draw(online);
		monopoly_game.draw(offline);
		monopoly_game.draw(close_game);
		monopoly_game.display();
	}
}

void Game::main_menu()
{
	monopoly_game.setPosition(Vector2i(100, 10));
	monopoly_game.setKeyRepeatEnabled(false);
	bg.setTexture(bg_monopoly_logo);

	Text continue_game(L"Kontynuuj grę", font_menus, 45);
	continue_game.setPosition((1100 / 2 - continue_game.getGlobalBounds().width / 2), 350);
	
	Text new_game(L"Nowa gra", font_menus, 45);
	new_game.setPosition((1100 / 2 - new_game.getGlobalBounds().width / 2), 400);

	Text back(L"Powrót", font_menus, 45);
	back.setPosition((1100 / 2 - back.getGlobalBounds().width / 2), 450);

	Text close_game(L"Wyjdź z gry", font_menus, 45);
	close_game.setPosition((1100 / 2 - close_game.getGlobalBounds().width / 2), 500);

	std::fstream save_file;
	save_file.open("save.txt", std::ios::in);

	while (state == MAIN_MENU)
	{
		Vector2f mouse(Mouse::getPosition(monopoly_game));
		Event event;
		while (monopoly_game.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				state = END;
				break;
			}

			// close game
			if (close_game.getGlobalBounds().contains(mouse))
			{
				close_game.setStyle(Text::Bold);
				close_game.setColor(Color(197, 0, 8, 255));
				if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				{
					state = END;
					break;
				}
			}
			else
			{
				close_game.setStyle(Text::Regular);
				close_game.setColor(Color::Black);
			}

			// continue game
			
			if (continue_game.getGlobalBounds().contains(mouse))
			{
				if (save_file.good()) // file exists "save.txt"
				{
					continue_game.setStyle(Text::Bold);
					continue_game.setColor(Color(197, 0, 8, 255));
					if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
					{
						//state = CONTINUE;
						break;
					}
				}
			}
			else
			{
				continue_game.setStyle(Text::Regular);
				if (save_file.good()) // file exists "save.txt"
				{
					continue_game.setColor(Color::Black);
				}
				else
				{
					continue_game.setColor(Color(145, 145, 145, 255));
				}
			}

			// new game
			if (new_game.getGlobalBounds().contains(mouse))
			{
				new_game.setStyle(Text::Bold);
				new_game.setColor(Color(197, 0, 8, 255));
				if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				{
					state = NEW_GAME;
					break;
				}
			}
			else
			{
				new_game.setStyle(Text::Regular);
				new_game.setColor(Color::Black);
			}

			// back to main menu
			if (back.getGlobalBounds().contains(mouse))
			{
				back.setStyle(Text::Bold);
				back.setColor(Color(197, 0, 8, 255));
				if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				{
					state = MODE_MENU;
					break;
				}
			}
			else
			{
				back.setStyle(Text::Regular);
				back.setColor(Color::Black);
			}
		}
		monopoly_game.clear();
		monopoly_game.draw(bg);
		monopoly_game.draw(close_game);
		if (!getGameMode())							// Block "continue" when game is online
			monopoly_game.draw(continue_game);
		monopoly_game.draw(back); // przeczytac o maszynie stanów
		monopoly_game.draw(new_game);
		monopoly_game.display();
	}
	save_file.close();
}

void Game::players_menu()
{
	monopoly_game.setPosition(Vector2i(100, 10));
	monopoly_game.setKeyRepeatEnabled(false);
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

	while (state == NEW_GAME)
	{
		Vector2f mouse(Mouse::getPosition(monopoly_game));
		Event event;
		while (monopoly_game.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				state = END;
				break;
			}

			// close game
			if (close_game.getGlobalBounds().contains(mouse))
			{
				close_game.setStyle(Text::Bold);
				close_game.setColor(Color(197, 0, 8, 255));
				if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				{
					state = END;
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
					state = MAIN_MENU;
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
		monopoly_game.clear();
		monopoly_game.draw(bg);
		monopoly_game.draw(title);
		monopoly_game.draw(two_players_img);
		monopoly_game.draw(three_players_img);
		monopoly_game.draw(four_players_img);
		monopoly_game.draw(back);
		monopoly_game.draw(close_game);
		monopoly_game.display();
	}
}