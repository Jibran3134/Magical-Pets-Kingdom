#include<iostream>
#include<iomanip>
#include<chrono>
#include<math.h>
#include <SFML/Graphics.hpp>
#include"graphics.h"
#include"Source.h"
using namespace std;
using namespace std::chrono;

	int main() {
		GameManager MyGame;
		MyGame.StartNewGame(); // Start a new game

		FileHandeling file;
		file.saveGame(MyGame, "Magical_Pets_Kingdom.txt"); // Save game at the starting 
		
		sf::RenderWindow window(sf::VideoMode(800, 600), "Magical Pets Kingdom");
		window.setFramerateLimit(60);
		Game game;                                        // Create a window
		game.run(window,game,file,MyGame);
		
		file.saveGame(MyGame, "Magical_Pets_Kingdom.txt");// Save game at the end
		
	}
	
	void Pet::useAbility(int , Arena* ) {
	}
	void Arena::usePowerUp(Pet* pet, string str) {
		if (str == powerups[0].getPower()) {
			cout << "\nPowerup aqquired" << endl;
			cout << "\nHealth restored" << endl;
			if (pet)
			pet->restoreHealth(pet->getMaxHealth(pet));
		}
		else if (str == powerups[1].getPower()) {
			cout << "\nPowerup aqquired" << endl;
			cout << "\nPower increased" << endl;
			if (pet)
			pet->increasePower(200);
		}
		else if (str == powerups[2].getPower()) {
			cout << "\nPowerup aqquired" << endl;
			cout << "\nDefense increased" << endl;
			if (pet)
			pet->increaseDefense(200);
		}
		else if (str == powerups[3].getPower()) {
			cout << "\nPowerup aqquired" << endl;
			cout << "\nSpeed increased" << endl;
			if(pet)
			pet->increaseSpeed(200);
		}
	}
