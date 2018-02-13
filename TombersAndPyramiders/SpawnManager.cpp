#include "SpawnManager.h"
#include <vector>
#include "GameManager.h"
#include "Inventory.h"
#include "WoodenShortsword.h"
#include "WoodenLongbow.h"
#include "PlayerPilot.h"
#include "Receiver.h"
#include "Sender.h"
#include "NetworkingManager.h"
#include "NetworkedGameScene.h"

std::shared_ptr<SpawnManager> SpawnManager::s_instance;

void callback(std::map<std::string, void*> payload)
{
	SpawnManager* self = (SpawnManager*)payload["this"];

	float p1x = std::stof(*(std::string*)payload["playerSpawnX0"]);
	float p1y = std::stof(*(std::string*)payload["playerSpawnY0"]);
	float p2x = std::stof(*(std::string*)payload["playerSpawnX1"]);
	float p2y = std::stof(*(std::string*)payload["playerSpawnY1"]);

	SceneManager::getInstance ()->pushScene (new NetworkedGameScene (p1x, p1y, p2x, p2y));
}

void SpawnManager::sendStartPacket ()
{
	std::map<std::string, std::string> payload;

	float p1x = -2;
	float p1y = -2;
	float p2x = 2;
	float p2y = 2;


	payload["playerSpawnX0"] = std::to_string (p1x);
	payload["playerSpawnY0"] = std::to_string (p1y);

	payload["playerSpawnX1"] = std::to_string (p2x);
	payload["playerSpawnY1"] = std::to_string (p2y);

	NetworkingManager::getInstance ()->prepareMessageForSending ("STARTGAME", payload);
	SceneManager::getInstance ()->pushScene (new NetworkedGameScene (p1x, p1y, p2x, p2y));
}

std::shared_ptr<SpawnManager> SpawnManager::getInstance()
{
	if (s_instance == nullptr)
		s_instance = GameManager::getInstance()->createGameObject<SpawnManager> (true);
	return s_instance;
}

SpawnManager::SpawnManager() : GameObject()
{
	auto receiver = addComponent<Receiver>(this, std::to_string(getId()));
	MessageManager::subscribe ("STARTGAME", callback, this);
	auto sender = addComponent<Sender>(this, std::to_string(getId()));
}

SpawnManager::~SpawnManager()
{

}

std::shared_ptr<MiscSquare> SpawnManager::generateMiscSquare(float x, float y, float scale)
{
	std::shared_ptr<MiscSquare> miscSquare = GameManager::getInstance()->createGameObject<MiscSquare>(false);
	miscSquare->getTransform()->setPosition(x, y);
	miscSquare->getTransform()->setScale(scale);
	return miscSquare;
}

std	::shared_ptr<MovingSquare> SpawnManager::generateMovingSquare(float x, float y)
{
	std::shared_ptr<MovingSquare> movingSquare = GameManager::getInstance()->createGameObject<MovingSquare>(false);
	movingSquare->getTransform()->setPosition(x, y);
	return movingSquare;
}

std::shared_ptr<Character> SpawnManager::generatePlayerCharacter(float x, float y)
{
	std::shared_ptr<Character> simpleCharacter = GameManager::getInstance()->createGameObject<Character>(false, new PlayerPilot());
	simpleCharacter->getComponent<Inventory>()->addItem(new WoodenLongbow());
	simpleCharacter->getTransform()->setPosition(x, y);

	return simpleCharacter;
}

std::shared_ptr<Character> SpawnManager::generateNetworkCharacter(float x, float y)
{
	IPaddress ip = NetworkingManager::getInstance()->getIP();
	int id = ip.host + rand();
	std::shared_ptr<Character> simpleCharacter = GameManager::getInstance()->createGameObjectWithId<Character>(false, id, new PlayerPilot());
	simpleCharacter->getComponent<Inventory>()->addItem(new WoodenLongbow());
	simpleCharacter->getTransform()->setPosition(x, y);
	return simpleCharacter;
}
/*
//Networking test
std::shared_ptr<NetworkCharacter> SpawnManager::generateNetworkCharacter(float x, float y)
{
	std::shared_ptr<NetworkCharacter> networkCharacter = std::shared_ptr<NetworkCharacter>(new NetworkCharacter());
	networkCharacter->getTransform()->setPosition(x, y);
	networkCharacters.push_back(networkCharacter);
	return networkCharacter;
}
*/