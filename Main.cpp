#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Game.h"
using namespace std;

//Screen size variables
int screenSizeX;
int screenSizeY;
//Recomended size 50:30

Game game;
string defaultFrame; //Empty screen pictures

//Print all objects on screen
string PrintObjects(string frame) {
	for (int i = 0; i < game.lastObjectNumber; i++) {
		int posX = game.allObjects[i].positionX; //Object position x
		int posY = game.allObjects[i].positionY; //Object position y

		if (posX < 0 || posX >= screenSizeX || posY < 0 || posY >= screenSizeY) continue; //If object not in screen
		string pixelChar = "#"; //Pixel picture in frame
		if (game.allObjects[i].objectName == "PlatformLeft") pixelChar = ">";
		if (game.allObjects[i].objectName == "PlatformRight") pixelChar = "<";
		if (game.allObjects[i].objectName == "Ball") pixelChar = "+";

		int pixelNumber; //Pixel number in frame
		pixelNumber = posX + posY * (screenSizeX + 1); //Set pixel number

		frame.replace(pixelNumber, 1, pixelChar); //Print game object
	}

	return frame; //Return frame
}

int main() {
	cout << "Enter your screen size" << "\n";
	cout << "X: "; cin >> screenSizeX; //Set screen size x
	cout << "Y: "; cin >> screenSizeY; //Set screen size y
	screenSizeX -= 1;
	screenSizeY -= 1;
	//Set screen size in game class
	game.screenSizeX = screenSizeX;
	game.screenSizeY = screenSizeY;
	if (screenSizeX < 10 || screenSizeY < 10) cout << "Error: minimum screen size: 10" << "\n"; //If screen size very small

	//Set default screen
	for (int i = 0; i < screenSizeY; i++) {
		for (int j = 0; j < screenSizeX; j++) defaultFrame += "_"; //Set one line
		defaultFrame += "\n"; //Set end line
	}

	game.Start(); //Start function

	//Output screen
	while (true) {
		//Get pressed key
		if (_kbhit()) {
			char key = _getch(); //Get pressed key
			switch (key) {
			case 'd': //Move right
				game.MovePlatfrom(true);
				break;
			case 'a': //Move left
				game.MovePlatfrom(false);
				break;
			}
		}

		if (!game.Update()) break; //Start update function
		string newFrame = PrintObjects (defaultFrame); //Create new frame
		cout << "\n\n" << newFrame; //Output new frame
		Sleep(100); //Sleep on 0.1 seconds
	}

	return 0;
}
