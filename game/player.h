#pragma once
#include <iostream>

class Player
{
public:
	Player();
	Player(std::string mPlayerName, int mPlayerScore, int mPlayerHealth, int mPlayerGold);

	void setName(std::string name);
	std::string getName();
	int getScore();
	void saveScore();
	int getGold();

private:

	std::string playerName;
	int playerHealth;
	int playerScore;
	int playerGold;
};

