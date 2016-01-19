#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
class Graphics
{
	sf::Texture bg_menu, bg_trade, game_board;
	sf::Texture twoPlayers, threePlayers, fourPlayers, twoPlayersHover, threePlayersHover, fourPlayersHover;
	sf::Texture frame, frame_active, frame_wrong;
	sf::Texture button_enable, button_disable, button_enable_short, button_disable_short;
	std::vector<sf::Texture> pawns, pawns_forGame, dice;

	sf::Texture CardTexure;
	sf::Texture RedCardTexure;
	std::vector<sf::Texture> MiniCard;
	sf::Texture TrainLogo;
	sf::Texture PowerStationLogo;
	sf::Texture WaterSupplyLogo;
	sf::Texture ChanceLogo;
	sf::Texture ChestLogo;

	sf::Font PalabFont;
	sf::Font MenuFont;
	sf::Font CardFont;

	bool StartGame = true;

public:
	bool StartingGame(){ return StartGame; }

	sf::Texture& bg_menuTexture(){ return bg_menu; }
	sf::Texture& bg_tradeTexture(){ return bg_trade; }
	sf::Texture& game_boardTexture(){ return game_board; }

	sf::Texture& GetTwoPlayers(){ return twoPlayers; }
	sf::Texture& GetTwoPlayersHover(){ return twoPlayersHover; }
	sf::Texture& GetThreePlayers(){ return threePlayers; }
	sf::Texture& GetThreePlayersHover(){ return threePlayersHover; }
	sf::Texture& GetFourPlayers(){ return fourPlayers; }
	sf::Texture& GetFourPlayersHover(){ return fourPlayersHover; }

	sf::Texture& GetFrameTexture(){ return frame; }
	sf::Texture& GetFrameActiveTexture(){ return frame_active; }
	sf::Texture& GetFrameWrongTexture(){ return frame_wrong; }

	std::vector<sf::Texture>& GetPawnsImg(){ return pawns; }
	std::vector<sf::Texture>& GetPawns(){ return pawns_forGame; }

	std::vector<sf::Texture>& GetDiceTexture(){ return dice; }

	sf::Texture& GetButtonEnable(){ return button_enable; }
	sf::Texture& GetButtonDisable(){ return button_disable; }
	sf::Texture& GetButtonEnableShort(){ return button_enable_short; }
	sf::Texture& GetButtonDisableShort(){ return button_disable_short; }

	sf::Texture& GetCardTexture(){ return CardTexure; }
	sf::Texture& GetRedCardTexture(){ return RedCardTexure; }
	sf::Texture& GetTrainLogoTexture(){ return TrainLogo; }
	sf::Texture& GetPowerStationLogoTexture(){ return PowerStationLogo; }
	sf::Texture& GetWaterSupplyLogoTexture(){ return WaterSupplyLogo; }
	sf::Texture& GetChestLogoTexture(){ return ChestLogo; }
	sf::Texture& GetChanceLogoTexture(){ return ChanceLogo; }
	std::vector<sf::Texture>& GetMiniCard()	{ return MiniCard; }

	sf::Font& GetPalabFont(){ return PalabFont; }
	sf::Font& GetMenuFont(){ return MenuFont; }
	sf::Font& GetCardFont(){ return CardFont; }

	Graphics()
	{
		// Loading Background Menu
		if (!bg_menu.loadFromFile("graphics/bg_monopoly_logo.png"))
			StartGame = false;

		// Loading Background Trade
		if (!bg_trade.loadFromFile("graphics/bg_trade.png"))
			StartGame = false;

		// Loading Monopoly Game Board
		if (!game_board.loadFromFile("graphics/game_board.png"))
			StartGame = false;

		// Loading Numbers of Players
		if ((!twoPlayers.loadFromFile("graphics/pawn/two_players.png")) || (!twoPlayersHover.loadFromFile("graphics/pawn/two_players_hover.png")))
			StartGame = false;
		if ((!threePlayers.loadFromFile("graphics/pawn/three_players.png")) || (!threePlayersHover.loadFromFile("graphics/pawn/three_players_hover.png")))
			StartGame = false;
		if ((!fourPlayers.loadFromFile("graphics/pawn/four_players.png")) || (!fourPlayersHover.loadFromFile("graphics/pawn/four_players_hover.png")))
			StartGame = false;

		// Loading Frames
		if (!frame.loadFromFile("graphics/frame.png"))
			StartGame = false;
		if (!frame_active.loadFromFile("graphics/frame_active.png"))
			StartGame = false;
		if (!frame_wrong.loadFromFile("graphics/frame_wrong.png"))
			StartGame = false;

		// Loading Pawns Texture
		std::vector<sf::Texture> pawn(4);
		int Size = pawn.size();
		if ((!pawn[1].loadFromFile("graphics/pawn/yellow.png")) || (!pawn[2].loadFromFile("graphics/pawn/green.png")))
			StartGame = false;
		if ((!pawn[3].loadFromFile("graphics/pawn/red.png")) || (!pawn[0].loadFromFile("graphics/pawn/blue.png")))
			StartGame = false;
		for (int i = 0; i < Size; ++i)
		{
			pawn[i].setSmooth(true);
			Graphics::pawns.emplace_back(pawn[i]);
		}

		// Loading Pawn For Game
		if ((!pawn[1].loadFromFile("graphics/pawn/yellow_pawn.png")) || (!pawn[2].loadFromFile("graphics/pawn/green_pawn.png")))
			StartGame = false;
		if ((!pawn[3].loadFromFile("graphics/pawn/red_pawn.png")) || (!pawn[0].loadFromFile("graphics/pawn/blue_pawn.png")))
			StartGame = false;
		for (int i = 0; i < Size; ++i)
		{
			pawn[i].setSmooth(true);
			Graphics::pawns_forGame.emplace_back(pawn[i]);
		}

		// Loading Dice Texture
		std::vector<sf::Texture> dice(6);
		Size = dice.size();
		if ((!dice[0].loadFromFile("graphics/dice/meshNumber_1.png")) || (!dice[1].loadFromFile("graphics/dice/meshNumber_2.png")))
			StartGame = false;
		if ((!dice[2].loadFromFile("graphics/dice/meshNumber_3.png")) || (!dice[3].loadFromFile("graphics/dice/meshNumber_4.png")))
			StartGame = false;
		if ((!dice[4].loadFromFile("graphics/dice/meshNumber_5.png")) || (!dice[5].loadFromFile("graphics/dice/meshNumber_6.png")))
			StartGame = false;
		for (int i = 0; i < Size; ++i)
		{
			dice[i].setSmooth(true);
			Graphics::dice.emplace_back(dice[i]);
		}

		// Loading Buttons Texture
		if (!button_enable.loadFromFile("graphics/button_enable.png"))
			StartGame = false;
		if (!button_disable.loadFromFile("graphics/button_disable.png"))
			StartGame = false;
		if (!button_enable_short.loadFromFile("graphics/button_enable_short.png"))
			StartGame = false;
		if (!button_disable_short.loadFromFile("graphics/button_disable_short.png"))
			StartGame = false;

		// Loading Card Texture
		if (!CardTexure.loadFromFile("graphics/card.png"))
			StartGame = false;
		if (!RedCardTexure.loadFromFile("graphics/RedCard.png"))
			StartGame = false;
		if (!TrainLogo.loadFromFile("graphics/TrainLogo.png"))
			StartGame = false;
		if (!PowerStationLogo.loadFromFile("graphics/PowerStationLogo.png"))
			StartGame = false;
		if (!WaterSupplyLogo.loadFromFile("graphics/WaterSupplyLogo.png"))
			StartGame = false;
		if (!ChestLogo.loadFromFile("graphics/chest.png"))
			StartGame = false;
		if (!ChanceLogo.loadFromFile("graphics/chance.png"))
			StartGame = false;

		//Loading Mini Cards Texture
		std::vector<sf::Texture> MiniCards(11);
		Size = MiniCards.size();
		if (!MiniCards[0].loadFromFile("graphics/miniCards/jailCard.png"))
			StartGame = false;
		if (!MiniCards[1].loadFromFile("graphics/miniCards/BlackMiniCard.png"))
			StartGame = false;
		if (!MiniCards[2].loadFromFile("graphics/miniCards/SpecialMiniCard.png"))
			StartGame = false;
		if (!MiniCards[3].loadFromFile("graphics/miniCards/PurpleMiniCard.png"))
			StartGame = false;
		if (!MiniCards[4].loadFromFile("graphics/miniCards/LightBlueMiniCard.png"))
			StartGame = false;
		if (!MiniCards[5].loadFromFile("graphics/miniCards/PinkMiniCard.png"))
			StartGame = false;
		if (!MiniCards[6].loadFromFile("graphics/miniCards/OrangeMiniCard.png"))
			StartGame = false;
		if (!MiniCards[7].loadFromFile("graphics/miniCards/RedMiniCard.png"))
			StartGame = false;
		if (!MiniCards[8].loadFromFile("graphics/miniCards/YellowMiniCard.png"))
			StartGame = false;
		if (!MiniCards[9].loadFromFile("graphics/miniCards/GreenMiniCard.png"))
			StartGame = false;
		if (!MiniCards[10].loadFromFile("graphics/miniCards/BlueMiniCard.png"))
			StartGame = false;

		for (int i = 0; i < Size; ++i)
		{
			MiniCards[i].setSmooth(true);
			Graphics::MiniCard.emplace_back(MiniCards[i]);
		}

		// Loading Fonts
		if (!PalabFont.loadFromFile("font/palab.ttf"))
			StartGame = false;
		if (!MenuFont.loadFromFile("font/kawoszeh.ttf"))
			StartGame = false;
		if (!CardFont.loadFromFile("font/Maritime_Tropical_Neue.ttf"))
			StartGame = false;
	}
};
