#include "CharacterTestScene.h"
#include "GLHeaders.h"
#include "SpriteRendererManager.h"
#include "Shader.h"
#include "SharedConstants.h"
#include <iostream>
#include "Camera.h"
#include "MovingSquare.h"
#include "MiscSquare.h"
#include <vector>
#include "SpawnManager.h"
#include <memory>
#include <WoodenLongbow.h>
#include "AudioManager.h"
#include "GameManager.h"

CharacterTestScene::CharacterTestScene()
{
}

void CharacterTestScene::onStart()
{
	AudioManager::getInstance()->playMusic();
	Camera::getActiveCamera()->addComponent<CameraFollow>(Camera::getActiveCamera().get());

	const int size = 10;
	const int scale = 5;

	for (int x = -size; x < size; x++)
	{
		for (int y = -size; y < size; y++)
		{
			SpawnManager::getInstance()->generateMiscSquare(x * scale, y * scale, scale);
		}
	}

	SpawnManager::getInstance()->generateWall(50, 0, 10);

	//GameManager::getInstance()->createGameObject<SimpleSprite>(false, "LandingPage.png", 0, 0, 0, 42);

	SpawnManager::getInstance()->generateWorldItem(-5, -5, std::make_shared<WoodenLongbow>());

	SpawnManager::getInstance()->generateDummyCharacter(15, 15);

	setCameraFollow(SpawnManager::getInstance()->generatePlayerCharacter(0, 0));
}

void CharacterTestScene::setCameraFollow(std::shared_ptr<GameObject> toFollow)
{
	Camera::getActiveCamera()->getComponent<CameraFollow>()->setToFollow(toFollow);
}

void CharacterTestScene::onPause()
{
}

void CharacterTestScene::onEnd()
{

}

void CharacterTestScene::onUpdate(int ticks)
{
}