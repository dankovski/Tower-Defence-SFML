#include "Player.h"


Player::Player() {
	playerName = "noname";
	playerScore = 0;
}
Player::Player(std::string mPlayerName, int mPlayerScore, int mPlayerHealth, int mPlayerGold) {
	playerName = mPlayerName;
	playerScore = mPlayerScore;
	playerHealth = mPlayerHealth;
	playerGold = mPlayerGold;
}

int Player::getGold() {
	return playerGold;
}

void Player::addScore(int mScore)
{
	playerScore += mScore;
}

void Player::addGold(int mGold)
{
	playerGold += mGold;
}

int Player::getHealth()
{
	return playerHealth;
}

void Player::removeHealth(int mHealth)
{
	playerHealth -= mHealth;
}

void Player::setName(std::string name) {
	playerName = name;

}

std::string Player::getName() {

	return playerName;
}

int Player::getScore() {

	return playerScore;
}

void saveScore() {

	//todo add saving score to file

}