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
#include "icon.c"
#include "player.h"
#include "field.h"
#include "graphics.h"

using namespace std;
using namespace sf;

Game::Game() : window(VideoMode(1100, 700, 32), "", Style::None), graphics(Graphics())
{
	window.setPosition(Vector2i(100, 10));
	window.setKeyRepeatEnabled(true);
	window.setIcon(MonopolyIcon.width, MonopolyIcon.height, MonopolyIcon.pixel_data);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	if (graphics.StartingGame())
		state = GameState::MODE_MENU;
	else
	{
		MessageBox(0, "Monopoly::ERROR!\n\nBrak plików!\nZainstaluj ponownie.", "Monopoly::ERROR", MB_OK);
		state = GameState::END;
	}
		
}
Game::~Game()
{
	for (auto& field : fields)
		delete field;
}

//Short Methods
void Game::SetGameMode(bool result) { game_mode = result; }
bool Game::GetGameMode() const { return game_mode; }
void Game::SetPlayers(int players) { this->players = players; }
int Game::GetPlayers() const { return players; }

//Game Methods
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

	textButtons.emplace_back(L"Wybierz tryb gry:", graphics.GetMenuFont(), 65, 300.0f, false);
	textButtons.emplace_back(L"Gra online", graphics.GetMenuFont(), 45, 400.0f, GameState::MAIN_MENU);
	textButtons.emplace_back(L"Gra offline", graphics.GetMenuFont(), 45, 470.0f, GameState::MAIN_MENU);
	textButtons.emplace_back(L"Wyjdź z gry", graphics.GetMenuFont(), 45, 540.0f, GameState::END);
	textButtons.emplace_back(L"MARCIN OBETKAŁ©", graphics.GetPalabFont(), 13, 789.0f, 283.0f, false);

	ButtonText* hoverButtonText = nullptr;
		
	while (state == GameState::MODE_MENU)
	{
		Vector2f mouse(Mouse::getPosition(window));
		hoverButtonText = CheckHoverTextButtonInMenu(textButtons);

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				state = GameState::END;
				break;
			}

			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left && hoverButtonText)
			{
				state = hoverButtonText->GetState(); 
				if (hoverButtonText == &textButtons[1])
					SetGameMode(true);
				if (hoverButtonText == &textButtons[2])
					SetGameMode(false);
				break;
			} 			
		}
		window.clear();
		window.draw(bg);
		for (auto &button : textButtons)
			window.draw(button.GetText());
		window.display();
	}
	textButtons.clear();
}
void Game::MainMenu()
{
	bg.setTexture(graphics.bg_menuTexture());

	if (!GetGameMode())
		textButtons.emplace_back(L"Kontynuuj grę", graphics.GetMenuFont(), 45, 350.0f, GameState::END); // Dorobić CONTINUE
	textButtons.emplace_back(L"Nowa gra", graphics.GetMenuFont(), 45, 410.0f, GameState::PLAYERS_MENU);
	textButtons.emplace_back(L"Powrót", graphics.GetMenuFont(), 45, 470.0f, GameState::MODE_MENU);
	textButtons.emplace_back(L"Wyjdź z gry", graphics.GetMenuFont(), 45, 530.0f, GameState::END);
	textButtons.emplace_back(L"MARCIN OBETKAŁ©", graphics.GetPalabFont(), 13, 789.0f, 283.0f, false);

	ButtonText* hoverButtonText = nullptr;

	//fstream save_file;
	//save_file.open("save.txt", ios::in);

	while (state == GameState::MAIN_MENU)
	{		
		Vector2f mouse(Mouse::getPosition(window));
		hoverButtonText = CheckHoverTextButtonInMenu(textButtons);

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				state = GameState::END;
				break;
			}

			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left && hoverButtonText)
			{
				state = hoverButtonText->GetState();
				break;
			}		
		}
		window.clear();
		window.draw(bg);
		for (auto& button : textButtons)
			window.draw(button.GetText());	
		window.display();
		
	}
	//save_file.close();
	textButtons.clear();
}
void Game::PlayersMenu()
{
	bg.setTexture(graphics.bg_menuTexture());

	textButtons.emplace_back(L"Wybierz liczbę graczy:", graphics.GetMenuFont(), 65, 300.0f, false);
	textButtons.emplace_back(L"Powrót", graphics.GetMenuFont(), 45, 550.0f, GameState::MAIN_MENU);
	textButtons.emplace_back(L"Wyjdź z gry", graphics.GetMenuFont(), 45, 600.0f, GameState::END);
	textButtons.emplace_back(L"MARCIN OBETKAŁ©", graphics.GetPalabFont(), 13, 789.0f, 283.0f, false);

	imgButtons.emplace_back(graphics.GetTwoPlayers(), graphics.GetTwoPlayersHover(), 180.0f, 410.0f, GameState::SET_NAMES);
	imgButtons.emplace_back(graphics.GetThreePlayers(), graphics.GetThreePlayersHover(), 450.0f, 410.0f, GameState::SET_NAMES);
	imgButtons.emplace_back(graphics.GetFourPlayers(), graphics.GetFourPlayersHover(), 740.0f, 410.0f, GameState::SET_NAMES);
	
	ButtonSprite* hoverImgButton = nullptr;
	ButtonText* hoverButtonText = nullptr;

	while (state == GameState::PLAYERS_MENU)
	{
		hoverButtonText = CheckHoverTextButtonInMenu(textButtons);
		hoverImgButton = CheckHoverSpriteButtonInMenu(imgButtons);
		
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
				if (hoverButtonText)
					state = hoverButtonText->GetState();
				if (hoverImgButton)
				{
					state = hoverImgButton->GetState();
					if (hoverImgButton == &imgButtons[0])
						SetPlayers(2);
					if (hoverImgButton == &imgButtons[1])
						SetPlayers(3);
					if (hoverImgButton == &imgButtons[2])
						SetPlayers(4);
				}
				break;
			}
		}
		window.clear();
		window.draw(bg);
		for (auto& button : textButtons)
			window.draw(button.GetText());
		for (auto& button : imgButtons)
			window.draw(button.GetSprite());
		window.display();
	}
	textButtons.clear();
	imgButtons.clear();
}
void Game::SetNames()
{
	bg.setTexture(graphics.bg_menuTexture());
	
	vector<Frame> frames;
	for (int i = 1; i <= players; ++i)
	{
		textButtons.emplace_back(L"Gracz " + to_string(i) + ":", graphics.GetMenuFont(), 40, 290.0f, (float)(380 + (i - 1) * 55), false);
		frames.emplace_back(graphics.GetFrameTexture(), graphics.GetFrameActiveTexture(), graphics.GetFrameWrongTexture(), 445.0f, (float)(380 + (i - 1) * 55), "", graphics.GetMenuFont(), 30);
		imgButtons.emplace_back(graphics.GetPawnsImg()[i - 1], 250.0f, (float)(380 + (i - 1) * 55));
	}
	textButtons.emplace_back(L"Wpisz nicki graczy:", graphics.GetMenuFont(), 65, 290.0f, false);
	textButtons.emplace_back(L"Powrót", graphics.GetMenuFont(), 45, 590.0f, GameState::PLAYERS_MENU);
	textButtons.emplace_back(L"Wyjdź z gry", graphics.GetMenuFont(), 45, 635.0f, GameState::END);
	textButtons.emplace_back(L"GRAJ", graphics.GetMenuFont(), 50, 920, 565.0f, GameState::START_GAME);
	textButtons.emplace_back(L"MARCIN OBETKAŁ©", graphics.GetPalabFont(), 13, 789.0f, 283.0f, false);

	ButtonText* hoverButtonText = nullptr;

	while (state == GameState::SET_NAMES)
	{
		Vector2f mouse(Mouse::getPosition(window));
		hoverButtonText = CheckHoverTextButtonInMenu(textButtons);
		
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
				if (hoverButtonText)
				{
					state = hoverButtonText->GetState();
					if (state == GameState::START_GAME)
					{
						bool wrong = false;
						for (int i = 0; i < players; ++i)
						{
							for (int j = i + 1; j < players; ++j)
							if (frames[i].GetString() == frames[j].GetString())
							{
								frames[i].TurnWrong();
								frames[j].TurnWrong();
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
				else
				{
					for (auto& frame : frames)
					{
						if (frame.GetSprite().getGlobalBounds().contains(mouse))
							frame.TurnActive(true);
						else
							frame.TurnActive(false);
					}
				}
			}

			if (event.type == Event::TextEntered)
			{
				for (auto& frame : frames)
				if (frame.IsActive())
					frame.EnterTextIntoFrame(event.text.unicode);
			}
		}
		window.clear();
		window.draw(bg);

		for (auto& button : imgButtons)
			window.draw(button.GetSprite());

		for (auto& button : textButtons)
			window.draw(button.GetText());
		for (auto& frame : frames)
		{
			window.draw(frame.GetSprite());
			window.draw(frame.GetText());
		}
		window.display();
	}
	textButtons.clear();
	imgButtons.clear();
}
void Game::StartGame()
{
	bg.setTexture(graphics.game_boardTexture());
	Dice LeftDice(graphics.GetDiceTexture(), 810.0f, 50.0f);
	Dice RightDice(graphics.GetDiceTexture(), 865.0f, 50.0f);

	CreatePlayersAndPawns();
	fields = CreateList_ptrField(graphics);
	CreateGameTextButtons();
	bool ShownCard = false;
	bool CloseCard = false;
	bool LetDrawStatusCard = false;

	pair<ButtonSprite, ButtonText> rollDiceButton = make_pair(ButtonSprite(graphics.GetButtonEnable(), graphics.GetButtonDisable(), 936.0f, 55.0f), ButtonText(L"Rzuć kostkami!", graphics.GetMenuFont(), 17, 953.0f, 63.0f, false));
	pair<ButtonSprite, ButtonText> nextPlayerButton = make_pair(ButtonSprite(graphics.GetButtonEnable(), graphics.GetButtonDisable(), 936.0f, 540.0f), ButtonText(L"Następny gracz!", graphics.GetMenuFont(), 17, 945.0f, 548.0f, false));
	pair<ButtonSprite, ButtonText> buyButton = make_pair(ButtonSprite(graphics.GetButtonEnableShort(), graphics.GetButtonDisableShort(), 225.0f, 515.0f), ButtonText(L"KUP", graphics.GetMenuFont(), 20, 268.0f, 522.0f, false));
	pair<ButtonSprite, ButtonText> bidButton = make_pair(ButtonSprite(graphics.GetButtonEnableShort(), graphics.GetButtonDisableShort(), 355.0f, 515.0f, false), ButtonText(L"LICYTUJ", graphics.GetMenuFont(), 20, 381.0f, 522.0f, false)); // Brak opcji
	pair<ButtonSprite, ButtonText> buildButton = make_pair(ButtonSprite(graphics.GetButtonEnableShort(), graphics.GetButtonDisableShort(), 225.0f, 515.0f, false), ButtonText(L"ZBUDUJ", graphics.GetCardFont(), 19, 252.0f, 522.0f, false));
	pair<ButtonSprite, ButtonText> depositButton = make_pair(ButtonSprite(graphics.GetButtonEnableShort(), graphics.GetButtonDisableShort(), 355.0f, 515.0f, false), ButtonText(L"HIPOTEKA", graphics.GetCardFont(), 19, 375.0f, 522.0f, false));
	pair<ButtonSprite, ButtonText> tradeButton = make_pair(ButtonSprite(graphics.GetButtonEnable(), graphics.GetButtonDisable(), 720.0f, 540.0f, false), ButtonText(L"Oferta Wymiany", graphics.GetMenuFont(), 17, 730.0f, 548.0f, false));

	ButtonSprite* hoverImgButton = nullptr;
	MiniCard* hoverStatusCard = nullptr;
	Field* ShowBigCard = nullptr;

	Player* activePlayer = nullptr;
	Field* FindedCard = nullptr;

	while (state == GameState::START_GAME)
	{
		Vector2f mouse(Mouse::getPosition(window));
		hoverImgButton = nullptr;
		activePlayer = CheckActivePlayer();
		hoverStatusCard = CheckHoverStatusCard();

		ActivateTradeButton(tradeButton.first, activePlayer);

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

		if (rollDiceButton.first.GetSprite().getGlobalBounds().contains(mouse))
			hoverImgButton = &rollDiceButton.first;
		else if (nextPlayerButton.first.GetSprite().getGlobalBounds().contains(mouse))
			hoverImgButton = &nextPlayerButton.first;
		else if (dynamic_cast<DrawCardField*>(FindedCard) && FindedCard->ShowGraphics().begin()->GetSprite().getGlobalBounds().contains(mouse))
			hoverImgButton = &(FindedCard->ShowGraphics()[0]);

		if (activePlayer->IsActiveField())
		{
			if (buyButton.first.GetSprite().getGlobalBounds().contains(mouse))
				hoverImgButton = &buyButton.first;
			else if (bidButton.first.GetSprite().getGlobalBounds().contains(mouse))
				hoverImgButton = &bidButton.first;
		}
		if (!activePlayer->IsActiveField())
		{
			if (ShowBigCard)
			{
				if (buildButton.first.GetSprite().getGlobalBounds().contains(mouse))
					hoverImgButton = &buildButton.first;
				else if (depositButton.first.GetSprite().getGlobalBounds().contains(mouse))
					hoverImgButton = &depositButton.first;
			}
			else if (tradeButton.first.GetSprite().getGlobalBounds().contains(mouse))
			{
				hoverImgButton = &tradeButton.first;
			}
		}
		ActivateRollAndSkipPlayerButtons(activePlayer, rollDiceButton.first, nextPlayerButton.first);

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
				if (hoverImgButton == &tradeButton.first && tradeButton.first.IsActive())
					//CreateTrade(activePlayer, activePlayer+1);

				if (hoverStatusCard && !activePlayer->IsActiveField())
				{
					ShowBigCard = FindField(fields, hoverStatusCard->GetMiniCardArea());
					if (hoverStatusCard->GetMiniCardOwner() == activePlayer)
						depositButton.first.activeButton(true);
					else
						depositButton.first.activeButton(false);
				}
				else if (ShowBigCard && !(ShowBigCard->ShowGraphics().begin()->GetSprite().getGlobalBounds().contains(mouse)))
					ShowBigCard = nullptr;

				if (hoverImgButton == &buyButton.first && ShownCard && buyButton.first.IsActive())
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

				if (ShownCard && !bidButton.first.IsActive() && !buyButton.first.IsActive()) // Kiedy karty nie da się kupić, bo jest kogoś :P
				{
					if (DrawCardField* card = dynamic_cast<DrawCardField*>(FindedCard))
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
							nextPlayerButton.first.activeButton(true);
							card->SetVisibility(false);
							card->AfterShowDescription();
						}
					}
					else
					{
						Player* owner = nullptr;
						unsigned int price = 0;
						FindedCard->GetOwnerAndPrice(owner, price, activePlayer);

						if (owner != nullptr && owner != activePlayer)
						{
							owner->AddMoney(price);
							activePlayer->SpendMoney(price);
						}
						CloseCard = true;
						ShownCard = false;
						nextPlayerButton.first.activeButton(true);
					}
				}

				if (hoverImgButton == &rollDiceButton.first && !activePlayer->ThrewDoublet() && rollDiceButton.first.IsActive())
				{
					ShownCard = RollDiceBeforeThrowingDoublet(activePlayer, LeftDice, RightDice, textButtons[1], ShownCard);
					hoverImgButton = nullptr;
				}

				if (hoverImgButton == &rollDiceButton.first && activePlayer->ThrewDoublet() && (!activePlayer->IsActiveField() || !ShownCard))
					ShownCard = RollDiceAfterThrowingDoublet(activePlayer, LeftDice, RightDice, textButtons[1], ShownCard);

				if (hoverImgButton == &nextPlayerButton.first && hoverImgButton->IsActive())
				{
					tradeButton.first.activeButton(false);
					GoToNextPlayer(activePlayer, textButtons[1]);
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
		DrawButtonOnWindow(window, nextPlayerButton);
		DrawButtonOnWindow(window, rollDiceButton);
		for (auto& button : textButtons)
			window.draw(button.GetText());
		if (FindedCard != nullptr && activePlayer->IsActiveField() && !CloseCard)
		{
			window.draw(*FindedCard);
			Player* owner = nullptr;
			unsigned int price = 0;
			FindedCard->GetOwnerAndPrice(owner, price, activePlayer);
			if (owner != nullptr)
			{
				buyButton.first.activeButton(false);
				//bid.first.activeButton(false);
				if (owner != activePlayer)
					textButtons[1].GetText().setString(L"Karta jest własnością " + owner->GetString() + "\nPobrano czynsz " + to_string(price) + L" zł");
				else
					textButtons[1].GetText().setString(L"Karta jest Twoją własnością!");
			}
			else
				buyButton.first.activeButton(true);

			bidButton.first.activeButton(false); // Brak możliwości licytowania

			if (FindedCard->ShowButtonsOnCard())
			{
				DrawButtonOnWindow(window, buyButton);
				DrawButtonOnWindow(window, bidButton);
			}
			else
			{
				bidButton.first.activeButton(false);
				buyButton.first.activeButton(false);
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
		if (ShowBigCard)
		{
			window.draw(*ShowBigCard);
			DrawButtonOnWindow(window, buildButton);
			DrawButtonOnWindow(window, depositButton);
		}
		DrawButtonOnWindow(window, tradeButton);
		window.display();
	}
}

//Creating Methods
void Game::CreatePlayersAndPawns()
{
	Dice ChoosePlayer(1, players);
	for (int i = 1; i <= players; ++i)
		pawns.emplace_back(graphics.GetPawns()[i - 1], i, 0);

	for (int i = 1; i <= players; ++i)
		player.emplace_back(Text(names[i - 1], graphics.GetMenuFont(), 20), pawns[i - 1], i - 1, graphics);
	int firstPlayer = ChoosePlayer.RollDice() - 1;
	player[firstPlayer].SetActive(true);
	player[firstPlayer].SetActiveMovement(true);
}
void Game::CreateGameTextButtons()
{
	textButtons.emplace_back(L"Aktywny Gracz", graphics.GetMenuFont(), 28, 840.0f, 5.0f, false);
	textButtons.emplace_back(L"Brak...", graphics.GetMenuFont(), 21, 705.0f, 606.0f, false);
	textButtons.emplace_back(L"99999", graphics.GetMenuFont(), 24, 835.0f, 103.0f, false);
	textButtons.emplace_back(L"Powiadomienia dodatkowe:", graphics.GetMenuFont(), 21, 705.0f, 580.0f, false);
	textButtons.emplace_back(L"Twój ruch:", graphics.GetMenuFont(), 28, 705.0f, 5.0f, false);
	textButtons.emplace_back(L"Stan konta:", graphics.GetMenuFont(), 24, 705.0f, 103.0f, false);
	textButtons.emplace_back(L"----------------------------------------------------------------", graphics.GetMenuFont(), 21, 705.0f, 93.0f, false);
	textButtons.emplace_back(L"----------------------------", graphics.GetMenuFont(), 21, 924.0f, 568.0f, false);
	textButtons.emplace_back(L"-----------------------------------------------------------------", graphics.GetMenuFont(), 21, 702.0f, 593.0f, false);
	textButtons.emplace_back(L"Copyright © 2016 by MARCIN OBETKAŁ PolSl Project", graphics.GetPalabFont(), 10, 327.0f, 591.0f, false);
}
std::list<Field*> Game::CreateList_ptrField(Graphics& graphics)
{
	Font& CardFont = graphics.GetCardFont();
	Texture CardTexture = graphics.GetCardTexture();

	CreateChanceList(chanceList);
	CreateCommunityList(communityList);

	std::list<Field*> fields;
	fields.emplace_back(new DeedField(
		DeedCard(L"ULICA KONOPACKA", CardFont, Rent(2, 10, 30, 90, 160), 60, 50, 50, 30), graphics, Color(78, 61, 113), 1
		));

	fields.emplace_back(new DrawCardField(								// KARTA KASY SPOŁECZNEJ POLE 2 (NR 1)
		communityList, graphics, graphics.GetChestLogoTexture(), 2
		));

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

	fields.emplace_back(new DrawCardField(								// KARTA SZANSY POLE 7 (NR 1)
		chanceList, graphics, graphics.GetChanceLogoTexture(), 7
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

	fields.emplace_back(new DrawCardField(								// KARTA KASY SPOŁECZNEJ POLE 17 (NR 2)
		communityList, graphics, graphics.GetChestLogoTexture(), 17
		));

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

	fields.emplace_back(new DrawCardField(								// KARTA SZANSY POLE 22 (NR 2)
		chanceList, graphics, graphics.GetChanceLogoTexture(), 22
		));

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

	fields.emplace_back(new DrawCardField(								// KARTA KASY SPOŁECZNEJ POLE 33 (NR 3)
		communityList, graphics, graphics.GetChestLogoTexture(), 33
		));

	fields.emplace_back(new DeedField(
		DeedCard(L"ALEJE JEROZOLIMSKIE", CardFont, Rent(28, 150, 450, 1000, 1200), 320, 200, 200, 160), graphics, Color(83, 148, 114), 34
		));
	fields.emplace_back(new TrainField(
		TrainCard("DWORZEC CENTRALNY", CardFont, 200, 25, 100), graphics, 35
		));

	fields.emplace_back(new DrawCardField(								// KARTA SZANSY POLE 36 (NR 3)
		chanceList, graphics, graphics.GetChanceLogoTexture(), 36
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
void Game::CreateChanceList(vector<DrawCard>& chanceCard)
{
	chanceCard.emplace_back(L"Teścik1 kochani moi");
	chanceCard.emplace_back(L"Teścik2 kochani moi");
	chanceCard.emplace_back(L"Teścik3 kochani moi");
	//chanceCard.emplace_back(L"Teścik4 kochani moi");
	//chanceCard.emplace_back(L"Teścik5 kochani moi");

}
void Game::CreateCommunityList(vector<DrawCard>& communityCard)
{
	communityCard.emplace_back(L"Teścik1 skrzynki kochani moi");
	communityCard.emplace_back(L"Teścik2 skrzunki kochani moi");
	communityCard.emplace_back(L"Teścik3 skrzynki kochani moi");

}
void Game::CreateTrade(Player* activePlayer, Player* secondPlayer)
{
	tradeBG.setTexture(graphics.bg_tradeTexture());
	state = GameState::TRADE;
	MiniCard* hoverStatusCard;
	Field* ShowBigCard = nullptr;

	while (state == GameState::TRADE)
	{
		Vector2f mouse(Mouse::getPosition(window));
		hoverStatusCard = nullptr;

		for (auto& sector : activePlayer->GetCardsStatus())
		{
			for (auto& card : sector->GetVectorCards())
			{
				if (card.GetVertCard().getBounds().contains(mouse))
				{
					hoverStatusCard = &card;
				}
			}
		}
		for (auto& sector : secondPlayer->GetCardsStatus())
		{
			for (auto& card : sector->GetVectorCards())
			{
				if (card.GetVertCard().getBounds().contains(mouse))
				{
					hoverStatusCard = &card;
				}
			}
		}

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				state = GameState::START_GAME;
				break;
			}

			if (hoverStatusCard)
			{
				ShowBigCard = FindField(fields, hoverStatusCard->GetMiniCardArea());
			}
			else if (ShowBigCard && !(ShowBigCard->ShowGraphics().begin()->GetSprite().getGlobalBounds().contains(mouse)))
			{
				ShowBigCard = nullptr;
			}

		}
		window.clear();
		window.draw(tradeBG);
		window.draw(*activePlayer);
		window.draw(*secondPlayer);
		if (ShowBigCard)
			window.draw(*ShowBigCard);
		window.display();
	}
}

//Methods of checking
MiniCard* Game::CheckHoverStatusCard()
{
	Vector2f mouse(Mouse::getPosition(window));
	for (auto& active : player)
	{
		for (auto& sector : active.GetCardsStatus())
		{
			for (auto& card : sector->GetVectorCards())
			{
				if (card.GetVertCard().getBounds().contains(mouse))
					return &card;
			}
		}
	}
	return nullptr;
}
Player* Game::CheckActivePlayer()
{
	for (auto& active : player)
	{
		active.GetMoneyStatus().setString(L"Stan konta: " + to_string(active.AccoundStatus()));
		if (active.IsActive())
		{
			textButtons[0].GetText().setString(active.GetString());
			textButtons[2].GetText().setString(to_string(active.AccoundStatus()) + L" zł");
			return &active;
		}
	}
	return nullptr;
}
ButtonText* Game::CheckHoverTextButtonInMenu(std::vector<ButtonText>& textButtons)
{
	Vector2f mouse(Mouse::getPosition(window));
	for (auto& button : textButtons)
	if (button.GetText().getGlobalBounds().contains(mouse) && button.MakeStyle())
	{
		button.GetText().setStyle(Text::Bold);
		button.GetText().setColor(Color(197, 0, 8, 255));
		return &button;
	}
	else
	{
		button.GetText().setStyle(Text::Regular);
		button.GetText().setColor(Color::Black);
	}
	return nullptr;
}
ButtonSprite* Game::CheckHoverSpriteButtonInMenu(std::vector<ButtonSprite>& imgButtons)
{
	Vector2f mouse(Mouse::getPosition(window));
	for (auto& button : imgButtons)
	if (button.GetSprite().getGlobalBounds().contains(mouse))
	{
		button.activeButton(false);
		return &button;
	}
	else
		button.activeButton(true);
	return nullptr;
}

//Methods of finding
Field* Game::FindField(list<Field*> list, const int ID)
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

//Response Methods
void Game::DrawButtonOnWindow(sf::RenderTarget& target, pair<ButtonSprite, ButtonText>& button)
{
	target.draw(button.first.GetSprite());
	target.draw(button.second.GetText());
}
void Game::GoToNextPlayer(Player* activePlayer, ButtonText& button)
{
	activePlayer->SetActive(false);
	button.GetText().setString(L"Brak...");
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
		button.GetText().setString(L"Jesteś zablokowany, rzuć kostkami!\nDwa dublety wypuszczą Cię z więzienia!");

}
bool Game::RollDiceAfterThrowingDoublet(Player* activePlayer, Dice& firstDice, Dice& secondDice, ButtonText& button, bool ShownCard)
{
	int firstRollDice = firstDice.RollDice();
	int secondRollDice = secondDice.RollDice();
	if (!activePlayer->IsBlocked())
	{
		if (firstRollDice != secondRollDice)
		{
			textButtons[1].GetText().setString(L"Brak...");
			if (activePlayer->GetPawn().move(firstRollDice + secondRollDice))
				activePlayer->AddMoney(200);
			activePlayer->SetActiveField(true);
			ShownCard = false;
		}
		else
		{
			activePlayer->SetBlock(2, true);
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
			activePlayer->SetActiveField(true);
			ShownCard = false;
		}
	}
	activePlayer->SetDoublet(false);
	activePlayer->SetActiveMovement(false);
	return ShownCard;
}
bool Game::RollDiceBeforeThrowingDoublet(Player* activePlayer, Dice& firstDice, Dice& secondDice, ButtonText& button, bool ShownCard)
{
	int firstRollDice = firstDice.RollDice();
	int secondRollDice = secondDice.RollDice();
	if (!activePlayer->IsBlocked())
	{
		if (activePlayer->GetPawn().move(firstRollDice + secondRollDice))
			activePlayer->AddMoney(200);
		activePlayer->SetActiveField(true);
		ShownCard = false;

		if (firstRollDice == secondRollDice)
		{
			activePlayer->SetDoublet(true);
			button.GetText().setString(L"Wyrzuciłeś dublet!\nRzuć kostkami jeszcze raz!");
		}
		else
			activePlayer->SetActiveMovement(false);
	}
	else
	{
		if (firstRollDice == secondRollDice)
		{
			activePlayer->SetDoublet(true);
			button.GetText().setString(L"Wyrzuciłeś dublet!\nRzuć kostkami jeszcze raz!");
		}
		else
		{
			button.GetText().setString(L"Nie udało się wyrzucić dubletu!\nOddaj ruch kolejnemu graczowi!");
			activePlayer->SetActiveMovement(false);
		}
		--(*activePlayer);
	}
	return ShownCard;
}

//Activating Methods
void Game::ActivateRollAndSkipPlayerButtons(Player* activePlayer, ButtonSprite& RollDiceButton, ButtonSprite& SkipPlayerButton)
{
	if (activePlayer->IsActiveMovement())
	{
		if (!activePlayer->IsActiveField())
			RollDiceButton.activeButton(true);
		else
			RollDiceButton.activeButton(false);
		SkipPlayerButton.activeButton(false);
	}
	else
	{
		RollDiceButton.activeButton(false);
		if (!activePlayer->IsActiveField())
			SkipPlayerButton.activeButton(true);
		else
			RollDiceButton.activeButton(false);
	}
}
void Game::ActivateTradeButton(ButtonSprite& button, Player* activePlayer)
{
	for (auto& sector : activePlayer->GetCardsStatus())
	{
		for (auto& card : sector->GetVectorCards())
		{
			if (card.GetMiniCardOwner() == activePlayer)
			{
				button.activeButton(true);
				return;
			}
		}
	}
}

