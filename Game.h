#ifndef GAME
#define GAME
#include <iostream>
using namespace std;

class Game {
public:
	//Game object class
	class GameObject {
	public:
		int positionX; //Object position x
		int positionY; //Object position y
		string objectName; //Object name
	};

	int screenSizeX; //Screen size x
	int screenSizeY; //Screen size y
	int maxObjectsCount; //Max count objects in allObjects list
	int lastObjectNumber = 0; //Game objects count in allObjects list
	GameObject* allObjects; //All game objects list
	int snakeWay = 0; //Where is the snake moving

	//This function start with program
	void Start() {
		srand(time(0)); //Random setting
		maxObjectsCount = screenSizeX * screenSizeY + 1; //Set max count number
		allObjects = new GameObject[maxObjectsCount]; //Create allObject list

		for (int i = 0; i < 8; i++) {
			string platformPositionName = "PlatformUp"; //Ricochet up
			if (i <= 3) platformPositionName = "PlatformRight"; //Ricochet right
			if (i >= 4) platformPositionName = "PlatformLeft"; //Ricochet left
			platform[i] = Create(screenSizeX / 2 + 3 - i, screenSizeY - 1, platformPositionName); //Create player platform
			enemyPlatform[i] = Create(screenSizeX / 2 + 3 - i, 0, "Platform"); //Create enemy platform
		}

		ball = Create(screenSizeX / 2, screenSizeY / 2, "Ball"); //Create ball

		//Set random ball vectors
		vectorBallX = 1 - rand() % 3;
		vectorBallY = 1 - rand() % 2 * 2;
	}

	//This function start every frame
	bool Update() {
		//Move ball
		ball->positionX += vectorBallX; //X
		ball->positionY += vectorBallY; //Y

		//Ball ricochet
		GameObject* returnTouchBall = ReturnTouch(ball); //Object that was touched ball
		if (returnTouchBall->positionX <= 0 || returnTouchBall->positionX >= screenSizeX - 1) vectorBallX *= -1; //Wall ricochet
		if (returnTouchBall->objectName == "Platform") {
			//Platform random ricochet
			vectorBallY *= -1;
			vectorBallX = 1 - rand() % 2 * 2;
		}
		if (returnTouchBall->objectName == "PlatformLeft") {
			//Platform ricochet left
			vectorBallY *= -1;
			vectorBallX = -1;
		}
		if (returnTouchBall->objectName == "PlatformRight") {
			//Platform ricochet right
			vectorBallY *= -1;
			vectorBallX = 1;
		}

		//Move enemy platform
		if (ball->positionX > enemyPlatform[3]->positionX) {
			for (int i = 0; i < 8; i++) enemyPlatform[i]->positionX++; //Move right
		}
		else if (ball->positionX < enemyPlatform[3]->positionX) {
			for (int i = 0; i < 8; i++) enemyPlatform[i]->positionX--; //Move left
		}

		//Restart game
		if (ball->positionY < 0 || ball->positionY >= screenSizeY) {
			for (int i = 0; i < 8; i++) {
				platform[i]->positionX = screenSizeX / 2 + 3 - i; //Move player platform to default position
				enemyPlatform[i]->positionX = screenSizeX / 2 + 3 - i; //Move enemy platform to default position
			}

			//Move ball to default position
			ball->positionX = screenSizeX / 2;
			ball->positionY = screenSizeY / 2;

			//Set random ball vectors
			vectorBallX = 1 - rand() % 2 * 2;
			vectorBallY = 1 - rand() % 2 * 2;
		}

		return true; //Continue
	}

	//Game public functions
	void MovePlatfrom(bool isRight) {
		int posX = platform[3]->positionX; //Platform position x
		int vector = 0; //Move vector
		if (isRight && posX < screenSizeX - 3) vector = 3; //Move right
		if (!isRight && posX >= 3) vector = -3; //Move left
		for (int i = 0; i < 8; i++) platform[i]->positionX += vector; //Move platform
	}
private:
	//Game variables
	GameObject* platform[8]; //Player platform
	GameObject* enemyPlatform[8]; //Enemy platform
	GameObject* ball; //Ball
	//Ball move vectors
	int vectorBallX;
	int vectorBallY;

	//Create new game object
	GameObject* Create(int positionX = 0, int positionY = 0, string objectName = "NoName") {
		GameObject gameObject; //Create new game object

		//Set game object variables
		gameObject.positionX = positionX;
		gameObject.positionY = positionY;
		gameObject.objectName = objectName;
		
		lastObjectNumber++; //Increase the number of objects
		allObjects[lastObjectNumber - 1] = gameObject; //Set new object in allObjects list
		return &allObjects[lastObjectNumber - 1]; //Return link on new object
	}

	//Return object that was touched
	GameObject* ReturnTouch(GameObject* gameObject) {
		for (int i = 0; i < lastObjectNumber; i++) {
			if (gameObject->objectName != allObjects[i].objectName) { //If object have different name
				//If object position equals target object position
				if (gameObject->positionX == allObjects[i].positionX && gameObject->positionY == allObjects[i].positionY) return &allObjects[i];
			}
		}
		return gameObject; //If object is not touched
	}
};

#endif
