#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <list>
#include "game.h"
#include "buttonsprite.h"
#include "buttontext.h"
#include "frame.h"
#include "pawn.h"
#include "dice.h"
#include "icon.c"
#include "player.h"
#include "field.h"
#include "graphics.h"
//#include "functions.h"

using namespace std;
using namespace sf;

std::list<Field*> CreateList_ptrField(Graphics& graphics);
Field* FindField(std::list<Field*> list, const unsigned int ID);
//list<Chance> CreateChanceList();
void CreateChanceList(vector<Chance>& chanceCard);

Game::Game(void) : window(VideoMode(1100, 700, 32), "", Style::None), graphics(Graphics())
{
	window.setPosition(Vector2i(100, 10));
	window.setKeyRepeatEnabled(true);
	window.setIcon(MonopolyIcon.width, MonopolyIcon.height, MonopolyIcon.pixel_data);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	if (graphics.StartingGame())
		state = GameState::MODE_MENU;
	else
		state = GameState::END;
}

void Game::SetGameMode(bool result) { game_mode = result; }
bool Game::GetGameMode() const { return game_mode; }
void Game::SetPlayers(int players) { this->players = players; }
int Game::GetPlayers() const { return players; }

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
	bg.setTexture(graphics.bg_menuTexture());
	vector<ButtonText> text_buttons;
	text_buttons.emplace_back(L"Wybierz tryb gry:", graphics.GetMenuFont(), 65, 300.0f, false);
	text_buttons.emplace_back(L"Gra online", graphics.GetMenuFont(), 45, 400.0f, GameState::MAIN_MENU);
	text_buttons.emplace_back(L"Gra offline", graphics.GetMenuFont(), 45, 470.0f, GameState::MAIN_MENU);
	text_buttons.emplace_back(L"Wyjdź z gry", graphics.GetMenuFont(), 45, 540.0f, GameState::END);
	text_buttons.emplace_back(L"MARCIN OBETKAŁ©", graphics.GetPalabFont(), 13, 789.0f, 283.0f, false);

	ButtonText* hoverButton_text = nullptr;
		
	while (state == GameState::MODE_MENU)
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
				if (hoverButton_text == &text_buttons[1])
					SetGameMode(true);
				if (hoverButton_text == &text_buttons[2])
					SetGameMode(false);
				break;
			} 			
		}
		window.clear();
		window.draw(bg);
		for (auto &button : text_buttons)
			window.draw(button.GetText());
		window.display();
	}
}


void Game::MainMenu()
{
	bg.setTexture(graphics.bg_menuTexture());

	vector<ButtonText> text_buttons;
	if (!GetGameMode())
		text_buttons.emplace_back(L"Kontynuuj grę", graphics.GetMenuFont(), 45, 350.0f, GameState::END); // Dorobić CONTINUE
	text_buttons.emplace_back(L"Nowa gra", graphics.GetMenuFont(), 45, 410.0f, GameState::PLAYERS_MENU);
	text_buttons.emplace_back(L"Powrót", graphics.GetMenuFont(), 45, 470.0f, GameState::MODE_MENU);
	text_buttons.emplace_back(L"Wyjdź z gry", graphics.GetMenuFont(), 45, 530.0f, GameState::END);
	text_buttons.emplace_back(L"MARCIN OBETKAŁ©", graphics.GetPalabFont(), 13, 789.0f, 283.0f, false);

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
	bg.setTexture(graphics.bg_menuTexture());

	vector<ButtonText> text_buttons;
	text_buttons.emplace_back(L"Wybierz liczbę graczy:", graphics.GetMenuFont(), 65, 300.0f, false);
	text_buttons.emplace_back(L"Powrót", graphics.GetMenuFont(), 45, 550.0f, GameState::MAIN_MENU);
	text_buttons.emplace_back(L"Wyjdź z gry", graphics.GetMenuFont(), 45, 600.0f, GameState::END);
	text_buttons.emplace_back(L"MARCIN OBETKAŁ©", graphics.GetPalabFont(), 13, 789.0f, 283.0f, false);

	ButtonText* hoverButton_text = nullptr;

	vector<ButtonSprite> img_buttons;
	img_buttons.emplace_back(graphics.GetTwoPlayers(), graphics.GetTwoPlayersHover(), 180.0f, 410.0f, GameState::SET_NAMES);
	img_buttons.emplace_back(graphics.GetThreePlayers(), graphics.GetThreePlayersHover(), 450.0f, 410.0f, GameState::SET_NAMES);
	img_buttons.emplace_back(graphics.GetFourPlayers(), graphics.GetFourPlayersHover(), 740.0f, 410.0f, GameState::SET_NAMES);
	
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
	bg.setTexture(graphics.bg_menuTexture());
	
	vector<Text> players;
	vector<Frame> frames;
	vector<Sprite> pawn;
	for (int i = 1; i <= GetPlayers(); ++i)
	{
		players.emplace_back(L"Gracz " + to_string(i) + ":", graphics.GetMenuFont(), 40);
		players[i - 1].setPosition(290.0f, (float)(380 + (i - 1) * 55));
		players[i - 1].setColor(Color::Black);
		frames.emplace_back(make_pair(graphics.GetFrameTexture(), graphics.GetFrameActiveTexture()), 445.0f, (float)(380 + (i - 1) * 55), "", graphics.GetMenuFont(), 30);
		pawn.emplace_back();
		pawn[i - 1].setTexture(graphics.GetPawnsImg()[i - 1]);
		pawn[i - 1].setPosition(250.0f, (float)(380 + (i - 1) * 55));
	}
	for (auto& frame : frames)
		frame.GetSprite().setTexture(frame.GetTexture().first);
	vector<ButtonText> text_buttons;
	text_buttons.emplace_back(L"Wpisz nicki graczy:", graphics.GetMenuFont(), 65, 290.0f, false);
	text_buttons.emplace_back(L"Powrót", graphics.GetMenuFont(), 45, 590.0f, GameState::PLAYERS_MENU);
	text_buttons.emplace_back(L"Wyjdź z gry", graphics.GetMenuFont(), 45, 635.0f, GameState::END);
	text_buttons.emplace_back(L"GRAJ", graphics.GetMenuFont(), 50, 920, 565.0f, GameState::START_GAME);
	text_buttons.emplace_back(L"MARCIN OBETKAŁ©", graphics.GetPalabFont(), 13, 789.0f, 283.0f, false);

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
							frames[i].GetSprite().setTexture(graphics.GetFrameWrongTexture());
							frames[j].GetSprite().setTexture(graphics.GetFrameWrongTexture());
							state = GameState::SET_NAMES;
							wrong = true;
						}
					}
					for (auto& frame : frames)
					{
						if (frame.GetString() == "" || frame.GetString() == " ")
						{
							frame.GetSprite().setTexture(graphics.GetFrameWrongTexture());
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
						else if (event.text.unicode > 31 && event.text.unicode < 123 && frame.GetString().size() < 14)
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
	bg.setTexture(graphics.game_boardTexture());
	Dice LeftDice(graphics.GetDiceTexture(), 810.0f, 50.0f);
	Dice RightDice(graphics.GetDiceTexture(), 865.0f, 50.0f);
	Dice ChoosePlayer(1, GetPlayers());

	vector<Pawn> pawns;
	for (int i = 1; i <= GetPlayers(); ++i)
	{
		pawns.emplace_back(graphics.GetPawns()[i - 1], i, 0);
	}
		
	vector<Player> player;
	for (int i = 1; i <= GetPlayers(); ++i)
		player.emplace_back(Text(names[i - 1], graphics.GetMenuFont(), 20), pawns[i - 1], i - 1, graphics);
	int firstPlayer = ChoosePlayer.RollDice() - 1;
	player[firstPlayer].SetActive(true);
	player[firstPlayer].SetActiveMovement(true);
	//player[firstPlayer].SetJailCard(true);
	//player[firstPlayer].SetBlock(2);

	list<Field*> fields = CreateList_ptrField(graphics);
	bool ShownCard = false;
	bool CloseCard = false;

	vector<ButtonSprite> imgButtons;
	imgButtons.emplace_back(graphics.GetButtonEnable(), graphics.GetButtonDisable(), 936.0f, 55.0f);
	imgButtons.emplace_back(graphics.GetButtonEnable(), graphics.GetButtonDisable(), 936.0f, 540.0f);
	pair<ButtonSprite, ButtonText> buy = make_pair(ButtonSprite(graphics.GetButtonEnableShort(), graphics.GetButtonDisableShort(), 225.0f, 515.0f), ButtonText(L"KUP", graphics.GetMenuFont(), 20, 268.0f, 522.0f, false));
	pair<ButtonSprite, ButtonText> bid = make_pair(ButtonSprite(graphics.GetButtonEnableShort(), graphics.GetButtonDisableShort(), 355.0f, 515.0f, false), ButtonText(L"LICYTUJ", graphics.GetMenuFont(), 20, 381.0f, 522.0f, false)); // Brak opcji

	vector<ButtonText> textButtons;
	textButtons.emplace_back(L"Aktywny Gracz", graphics.GetMenuFont(), 28, 840.0f, 5.0f, false);
	textButtons.emplace_back(L"Brak...", graphics.GetMenuFont(), 21, 705.0f, 606.0f, false);
	textButtons.emplace_back(L"99999", graphics.GetMenuFont(), 24, 835.0f, 103.0f, false);
	textButtons.emplace_back(L"Powiadomienia dodatkowe:", graphics.GetMenuFont(), 21, 705.0f, 580.0f, false);
	textButtons.emplace_back(L"Twój ruch:", graphics.GetMenuFont(), 28, 705.0f, 5.0f, false);
	textButtons.emplace_back(L"Stan konta:", graphics.GetMenuFont(), 24, 705.0f, 103.0f, false);
	textButtons.emplace_back(L"Rzuć kostkami!", graphics.GetMenuFont(), 17, 953.0f, 63.0f, false);
	textButtons.emplace_back(L"----------------------------------------------------------------", graphics.GetMenuFont(), 21, 705.0f, 93.0f, false);
	textButtons.emplace_back(L"----------------------------", graphics.GetMenuFont(), 21, 924.0f, 568.0f, false);
	textButtons.emplace_back(L"-----------------------------------------------------------------", graphics.GetMenuFont(), 21, 702.0f, 593.0f, false);
	textButtons.emplace_back(L"Następny gracz!", graphics.GetMenuFont(), 17, 945.0f, 548.0f, false);
	textButtons.emplace_back(L"Copyright © 2016 by MARCIN OBETKAŁ PolSl Project", graphics.GetPalabFont(), 10, 327.0f, 591.0f, false);

	ButtonSprite* hoverImgButton = nullptr;
	ButtonText* hoverTextButton = nullptr;

	Player* activePlayer = nullptr;
	Field* FindedCard = nullptr;

	while (state == GameState::START_GAME)
	{
		Vector2f mouse(Mouse::getPosition(window));
		hoverImgButton = nullptr;
		hoverTextButton = nullptr;
		activePlayer = nullptr;

		for (auto& active : player)
		{
			if (active.IsActive())
			{
				activePlayer = &active;
				textButtons[0].GetText().setString(activePlayer->GetString());
				textButtons[2].GetText().setString(to_string(activePlayer->AccoundStatus()) + L" zł");
			}
			active.GetMoneyStatus().setString(L"Stan konta: " + to_string(active.AccoundStatus()));
		}
		

		if (activePlayer->IsActiveField())
		{
			FindedCard = FindField(fields, activePlayer->GetPawn().GetArea()); //
			if (!FindedCard)
				activePlayer->SetActiveField(false);
		}
		else
		{
			FindedCard = nullptr;
			activePlayer->SetActiveField(false);
		}

		for (auto& button : textButtons)
		if (button.GetText().getGlobalBounds().contains(mouse) && button.MakeStyle())
		{
			hoverTextButton = &button;
			button.GetText().setStyle(Text::Underlined);
		}
		else
		{
			button.GetText().setStyle(Text::Regular);
		}

		for (auto& button : imgButtons)
		if (button.GetSprite().getGlobalBounds().contains(mouse))
		{
			hoverImgButton = &button;
		}
		if (dynamic_cast<ChanceField*>(FindedCard) && FindedCard->ShowGraphics().begin()->GetSprite().getGlobalBounds().contains(mouse))
		{
			hoverImgButton = &(FindedCard->ShowGraphics()[0]);
		}
		if (activePlayer->IsActiveField())
		{
			if (buy.first.GetSprite().getGlobalBounds().contains(mouse))
				hoverImgButton = &buy.first;
			else if (bid.first.GetSprite().getGlobalBounds().contains(mouse))
				hoverImgButton = &bid.first;
		}
		
		if (activePlayer->IsActiveMovement())
		{
			if (!activePlayer->IsActiveField())// || !ShownCard)
				imgButtons[0].activeButton(true);
			else 
				imgButtons[0].activeButton(false);
			imgButtons[1].activeButton(false);
		}
		else
		{
			imgButtons[0].activeButton(false);
			if (!activePlayer->IsActiveField())// || !ShownCard)
				imgButtons[1].activeButton(true);
			else
				imgButtons[0].activeButton(false);
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
				if (hoverImgButton == &buy.first && ShownCard && buy.first.IsActive())
				{
					FindedCard->Action(*activePlayer);
					ShownCard = false;
					activePlayer->SetActiveField(false);
				}

				if (activePlayer->GetJailCard().getGlobalBounds().contains(mouse) && activePlayer->ExistJailCard() && activePlayer->IsBlocked() && activePlayer->IsActiveMovement() && !activePlayer->IsActiveField())
				{
					activePlayer->SetJailCard(false);
					activePlayer->SetBlock(0);
					activePlayer->SetActiveMovement(false);
				}

				if (ShownCard && !bid.first.IsActive() && !buy.first.IsActive()) // Kiedy karty nie da się kupić, bo jest kogoś :P
				{

					if (!dynamic_cast<ChanceField*>(FindedCard)) // && !dynamic_cast<CommunityField*>(FindedCard)
					{
						Player* owner = nullptr;
						unsigned int price = 0;
						if (DeedField* card = dynamic_cast<DeedField*>(FindedCard))
						{
							owner = card->GetCard().GetOwner();
							price = card->GetCard().Get_rents().Get_withoutHouse();
						}
						else if (TrainField* card = dynamic_cast<TrainField*>(FindedCard))
						{
							owner = card->GetCard().GetOwner();
							price = card->GetCard().Get_Rent();
						}
						else if (SpecialField* card = dynamic_cast<SpecialField*>(FindedCard))
						{
							owner = card->GetCard().GetOwner();
							price = activePlayer->GetPawn().GetLastRollDice() * 4;
						}

						if (owner != nullptr && owner != activePlayer)
						{
							owner->AddMoney(price);
							activePlayer->SpendMoney(price);
						}
						CloseCard = true;
						ShownCard = false;
						imgButtons[1].activeButton(true);
					}
					else
					{
						if (ChanceField* card = dynamic_cast<ChanceField*>(FindedCard))
						{
							if (hoverImgButton == &(FindedCard->ShowGraphics()[0]) && !card->isVisible())
							{
								card->ShowDescription();
								card->SetVisibility(true);
								CloseCard = false;
							}
							else if (card->isVisible())
							{
								CloseCard = true;
								ShownCard = false;
								imgButtons[1].activeButton(true);
								card->SetVisibility(false);
								card->AfterShowDescription();
								//Dodać zmianę karty :)
							}
						}
						//else if (CommunityField* card = dynamic_cast<CommunityField*>(FindedCard))
					}
				}

				if (hoverImgButton == &imgButtons[0] && !activePlayer->ThrewDoublet() && imgButtons[0].IsActive())
				{
					int firstRollDice = LeftDice.RollDice();
					int secondRollDice = RightDice.RollDice();
					if (!activePlayer->IsBlocked())
					{
						if (activePlayer->GetPawn().move(firstRollDice + secondRollDice))
							activePlayer->AddMoney(200);
						//ZARZĄDZANIE POLEM
						activePlayer->SetActiveField(true);
						ShownCard = false;

						if (firstRollDice == secondRollDice)
						{
							activePlayer->SetDoublet(true);
							textButtons[1].GetText().setString(L"Wyrzuciłeś dublet!\nRzuć kostkami jeszcze raz!");
						}
						else
							activePlayer->SetActiveMovement(false);
					}
					else
					{
						if (firstRollDice == secondRollDice)
						{
							activePlayer->SetDoublet(true);
							textButtons[1].GetText().setString(L"Wyrzuciłeś dublet!\nRzuć kostkami jeszcze raz!");
						}
						else
						{
							textButtons[1].GetText().setString(L"Nie udało się wyrzucić dubletu!\nOddaj ruch kolejnemu graczowi!");
							activePlayer->SetActiveMovement(false);
						}
						--(*activePlayer);
					}
					hoverImgButton = nullptr;
				}

				if (hoverImgButton == &imgButtons[0] && activePlayer->ThrewDoublet() && (!activePlayer->IsActiveField() || !ShownCard))
				{
					int firstRollDice = LeftDice.RollDice();
					int secondRollDice = RightDice.RollDice();
					if (!activePlayer->IsBlocked())
					{
						if (firstRollDice != secondRollDice)
						{
							textButtons[1].GetText().setString(L"Brak...");
							if (activePlayer->GetPawn().move(firstRollDice + secondRollDice))
								activePlayer->AddMoney(200);
							//ZARZĄDZANIE POLEM
							activePlayer->SetActiveField(true);
							ShownCard = false;
						}
						else
						{
							activePlayer->SetBlock(2, true);
							//activePlayer->GetPawn().GoJail(activePlayer);
							textButtons[1].GetText().setString(L"Wyrzuciłeś drugi dublet!\nTrafiasz do więzienia!");
						}
					}
					else
					{
						if (firstRollDice == secondRollDice)
						{
							textButtons[1].GetText().setString(L"Wyrzuciłeś drugi dublet!\nWychodzisz z więzienia!");
							activePlayer->GetPawn().SetArea(10);
							if (activePlayer->GetPawn().move(firstRollDice + secondRollDice))
								activePlayer->AddMoney(200);
							activePlayer->SetBlock(0);
							//ZARZĄDZANIE POLEM
							activePlayer->SetActiveField(true);
							ShownCard = false;
						}
					}
					activePlayer->SetDoublet(false);
					activePlayer->SetActiveMovement(false);
				}

				if (hoverImgButton == &imgButtons[1] && hoverImgButton->IsActive())
				{
					activePlayer->SetActive(false);
					textButtons[1].GetText().setString(L"Brak...");
					if (activePlayer != &player[GetPlayers() - 1])
					{
						(activePlayer + 1)->SetActive(true);
						(activePlayer + 1)->SetActiveMovement(true);
					}
					else
					{
						player[0].SetActive(true);
						player[0].SetActiveMovement(true);
					}
					for (auto& active : player)
					if (active.IsActive() && active.IsBlocked())
						textButtons[1].GetText().setString(L"Jesteś zablokowany, rzuć kostkami!\nDwa dublety wypuszczą Cię z więzienia!");
				}

			}			
		}
		window.clear();
		window.draw(bg);
		for (auto& thisPlayer : player)
		{
			window.draw(thisPlayer.GetPawn().GetSprite());
			window.draw(thisPlayer);
		}
		window.draw(LeftDice.GetSprite());
		window.draw(RightDice.GetSprite());
		for (auto& button : imgButtons)
			window.draw(button.GetSprite());
		for (auto& button : textButtons)
			window.draw(button.GetText());
		if (FindedCard != nullptr && activePlayer->IsActiveField() && !CloseCard)
		{
			window.draw(*FindedCard);
			Player* owner = nullptr;
			unsigned int price = 0;
			if (DeedField* card = dynamic_cast<DeedField*>(FindedCard))
			{
				owner = card->GetCard().GetOwner();
				price = card->GetCard().Get_rents().Get_withoutHouse();
			}
			else if (TrainField* card = dynamic_cast<TrainField*>(FindedCard))
			{
				owner = card->GetCard().GetOwner();
				price = card->GetCard().Get_Rent();
			}
			else if (SpecialField* card = dynamic_cast<SpecialField*>(FindedCard))
			{
				owner = card->GetCard().GetOwner();
				price = activePlayer->GetPawn().GetLastRollDice() * 4;
			}

			if (owner != nullptr)
			{
				buy.first.activeButton(false);
				//bid.first.activeButton(false);
				if (owner != activePlayer)
					textButtons[1].GetText().setString(L"Karta jest własnością " + owner->GetString() + "\nPobrano czynsz " + to_string(price) + L" zł");
				else
					textButtons[1].GetText().setString(L"Karta jest Twoją własnością!");
			}
			else
				buy.first.activeButton(true);

			bid.first.activeButton(false); // Brak możliwości licytowania
			
			if (FindedCard->ShowButtonsOnCard()) // Dodać wyjątek dla kart społecznych
			{
				window.draw(buy.first.GetSprite());
				window.draw(buy.second.GetText());
				window.draw(bid.first.GetSprite());
				window.draw(bid.second.GetText());
			}
			else
			{
				bid.first.activeButton(false);
				buy.first.activeButton(false);
			}
			ShownCard = true;
		}
		else if (CloseCard)
		{
			CloseCard = false;
			activePlayer->SetActiveField(false);
		}	
		if (activePlayer->ExistJailCard())
		{
			window.draw(activePlayer->GetJailCard());
			window.draw(activePlayer->GetJailCardTitle());
		}
		window.display();
	}
}

Field* FindField(std::list<Field*> list, const unsigned int ID)
{
	auto elem = list.begin();
	auto end = list.end();
	while (elem != end)
	{
		if ((*elem)->GetArea() == ID)
			return *elem;
		++elem;
	}
	return nullptr;
}

std::list<Field*> CreateList_ptrField(Graphics& graphics)
{
	Font& CardFont = graphics.GetCardFont();
	Texture CardTexture = graphics.GetCardTexture();
	vector<Chance> chanceList; 
	CreateChanceList(chanceList);

	std::list<Field*> fields;
	fields.emplace_back(new DeedField(
		DeedCard(L"ULICA KONOPACKA", CardFont, Rent(2, 10, 30, 90, 160), 60, 50, 50, 30), graphics, Color(78, 61, 113), 1
		));
	//// kasa społeczna 2

	fields.emplace_back(new DeedField(
		DeedCard(L"ULICA STALOWA", CardFont, Rent(4, 20, 60, 180, 320), 60, 50, 50, 30), graphics, Color(78, 61, 113), 3
		));
	////fields.emplace_back(4); -200ZŁ 4
	fields.emplace_back(new TrainField(
		TrainCard("DWORZEC ZACHODNI", CardFont, 200, 25, 100), graphics, 5
		));
	fields.emplace_back(new DeedField(
		DeedCard(L"ULICA RADZYMIŃSKA", CardFont, Rent(6, 30, 90, 270, 400), 100, 50, 50, 50), graphics, Color(178, 194, 228), 6
		));

	//// karta szansy 7
	fields.emplace_back(new ChanceField(
		chanceList, graphics, 7
		));


	fields.emplace_back(new DeedField(
		DeedCard(L"ULICA JAGIELLOŃSKA", CardFont, Rent(6, 30, 90, 270, 400), 100, 50, 50, 50), graphics, Color(178, 194, 228), 8
		));
	fields.emplace_back(new DeedField(
		DeedCard(L"ULICA TARGOWA", CardFont, Rent(8, 40, 100, 300, 450), 120, 50, 50, 60), graphics, Color(178, 194, 228), 9
		));
	// 10 NIC
	fields.emplace_back(new DeedField(
		DeedCard(L"ULICA PŁOWIECKA", CardFont, Rent(10, 50, 150, 450, 625), 140, 100, 100, 70), graphics, Color(177, 50, 95), 11
		));
	fields.emplace_back(new SpecialField(
		SpecialCard(L"ELEKTROWNIA", CardFont, 150, 75), graphics, graphics.GetPowerStationLogoTexture(), 12
		));
	fields.emplace_back(new DeedField(
		DeedCard(L"ULICA MARSA", CardFont, Rent(10, 50, 150, 450, 625), 140, 100, 100, 70), graphics, Color(177, 50, 95), 13
		));
	fields.emplace_back(new DeedField(
		DeedCard(L"ULICA GROCHOWSKA", CardFont, Rent(12, 60, 180, 500, 700), 160, 100, 100, 80), graphics, Color(177, 50, 95), 14
		));
	fields.emplace_back(new TrainField(
		TrainCard(L"DWORZEC GDAŃSKI", CardFont, 200, 25, 100), graphics, 15
		));
	fields.emplace_back(new DeedField(
		DeedCard(L"ULICA OBOZOWA", CardFont, Rent(14, 70, 200, 550, 750), 180, 100, 100, 90), graphics, Color(243, 141, 77), 16
		));
	//KASA SPOŁECZNA 17
	fields.emplace_back(new DeedField(
		DeedCard(L"ULICA GÓRCZEWSKA", CardFont, Rent(14, 70, 200, 550, 750), 180, 100, 100, 90), graphics, Color(243, 141, 77), 18
		));
	fields.emplace_back(new DeedField(
		DeedCard(L"ULICA WOLSKA", CardFont, Rent(16, 80, 220, 600, 800), 200, 100, 100, 100), graphics, Color(243, 141, 77), 19
		));
	//20 NIC
	fields.emplace_back(new DeedField(
		DeedCard(L"ULICA MICKIEWICZA", CardFont, Rent(18, 90, 250, 700, 875), 220, 150, 150, 110), graphics, Color(239, 59, 58), 21
		));
	//KARTA SZANSY 22
	fields.emplace_back(new DeedField(
		DeedCard(L"ULICA SŁOWACKIEGO", CardFont, Rent(18, 90, 250, 700, 875), 220, 150, 150, 110), graphics, Color(239, 59, 58), 23
		));
	fields.emplace_back(new DeedField(
		DeedCard(L"ULICA WILSONA", CardFont, Rent(20, 100, 300, 750, 925), 240, 150, 150, 120), graphics, Color(239, 59, 58), 24
		));
	fields.emplace_back(new TrainField(
		TrainCard("DWORZEC WSCHODNI", CardFont, 200, 25, 100), graphics, 25
		));
	fields.emplace_back(new DeedField(
		DeedCard(L"ULICA ŚWIĘTOKRZYSKA", CardFont, Rent(22, 110, 330, 800, 975), 260, 150, 150, 130), graphics, Color(237, 247, 140), 26
		));
	fields.emplace_back(new DeedField(
		DeedCard(L"KRAKOWSKIE PRZEDMIEŚCIE", CardFont, Rent(22, 110, 330, 800, 975), 260, 150, 150, 130), graphics, Color(237, 247, 140), 27
		));
	fields.emplace_back(new SpecialField(
		SpecialCard(L"WODOCIĄGI", CardFont, 150, 75), graphics, graphics.GetWaterSupplyLogoTexture(), 28
		));
	fields.emplace_back(new DeedField(
		DeedCard(L"NOWY ŚWIAT", CardFont, Rent(24, 120, 360, 850, 1025), 280, 150, 150, 140), graphics, Color(237, 247, 140), 29
		));
	//GO TO JAIL! 30
	fields.emplace_back(new DeedField(
		DeedCard(L"PLAC TRZECH KRZYŻY", CardFont, Rent(26, 130, 390, 900, 1100), 300, 200, 200, 150), graphics, Color(83, 148, 114), 31
		));
	fields.emplace_back(new DeedField(
		DeedCard(L"ULICA MARSZAŁKOWSKA", CardFont, Rent(26, 130, 390, 900, 1100), 300, 200, 200, 150), graphics, Color(83, 148, 114), 32
		));
	//KASA SPOŁECZNA 33
	fields.emplace_back(new DeedField(
		DeedCard(L"ALEJE JEROZOLIMSKIE", CardFont, Rent(28, 150, 450, 1000, 1200), 320, 200, 200, 160), graphics, Color(83, 148, 114), 34
		));
	fields.emplace_back(new TrainField(
		TrainCard("DWORZEC CENTRALNY", CardFont, 200, 25, 100), graphics, 35
		));
	//SZANSA 36

	fields.emplace_back(new ChanceField(
		chanceList, graphics, 36
		));

	fields.emplace_back(new DeedField(
		DeedCard(L"BELWEDERSKA", CardFont, Rent(35, 175, 500, 1100, 1300), 350, 200, 200, 175), graphics, Color(56, 79, 146), 37
		));
	//PODATEK -100ZŁ 38
	fields.emplace_back(new DeedField(
		DeedCard(L"ALEJE UJAZDOWSKIE", CardFont, Rent(50, 200, 600, 1400, 1700), 400, 200, 200, 200), graphics, Color(56, 79, 146), 39
		));
	return fields;
}

void CreateChanceList(vector<Chance>& chanceCard)
{
	chanceCard.emplace_back(L"Teścik1 kochani moi");
	chanceCard.emplace_back(L"Teścik2 kochani moi");
	chanceCard.emplace_back(L"Teścik3 kochani moi");
	//chanceCard.emplace_back(L"Teścik4 kochani moi");
	//chanceCard.emplace_back(L"Teścik5 kochani moi");

}