#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Source.h"
class Game;

class Training_Camp {
    sf::Texture arrowTexture;
    sf::Sprite  arrowSprite;
    sf::Texture backgroundtexture;
    sf::Sprite backgroundsprite;
    sf::Font font;
    sf::Text title;
    sf::RectangleShape* buttons[4];
    sf::Text buttonText[4];
    sf::Texture texture[4];
    sf::Sprite sprite[4];
public:
    void loadAssets(GameManager& MyGame);
    void render(sf::RenderWindow& window, GameManager& MyGame);
    void handleInput(sf::RenderWindow& window, int state, Game& game, GameManager& MyGame);

};
class LeaderBoard {
    sf::Texture arrowTexture;
    sf::Sprite  arrowSprite;
    sf::Texture backgroundtexture;
    sf::Sprite backgroundsprite;
    sf::Font font;
    sf::Text title;
    sf::Text      entry;
    sf::RectangleShape card;
    sf::RectangleShape cardShadow;

public:
    void loadAssets(GameManager& MyGame);
    void render(sf::RenderWindow& window, GameManager& MyGame);
    void handleInput(sf::RenderWindow& window, int state, Game& game, GameManager& MyGame);
};
class Arena_Menu {
    sf::Texture arrowTexture;
    sf::Sprite  arrowSprite;
    sf::Texture backgroundtexture;
    sf::Sprite backgroundsprite;
    sf::Texture optionsTexture[3];
    sf::Sprite optionsSprite[3];
    sf::Font font;
    sf::Text title;
public:
    Arena_Menu();
    void loadAssets(GameManager& MyGame);
    void render(sf::RenderWindow& window, GameManager& MyGame);
    void handleInput(sf::RenderWindow& window, int state, Game& game, GameManager& MyGame);
};
class Shop_Graphics {
    sf::RectangleShape priceBox[4];
    sf::Text priceText[4];
    sf::Texture coinTexture;
    sf::Sprite  coinSprite;
    sf::Text    coinText;
    sf::Texture arrowTexture;
    sf::Sprite  arrowSprite;
    sf::Texture backgroundtexture;
    sf::Sprite backgroundsprite;
    sf::RectangleShape Frame[4];
    sf::RectangleShape shadows[4];
    sf::Texture texture[4];
    sf::Sprite sprite[4];
    sf::Font font;
    sf::Text name[4];
    sf::Text title;
public:
    Shop_Graphics();
    void loadAssets(GameManager& MyGame);
    void render(sf::RenderWindow& window, GameManager& MyGame);
    void handleInput(sf::RenderWindow& window, Game& game, GameManager& MyGame);
};
class PetSelection {
    sf::Texture arrowTexture;
    sf::Sprite  arrowSprite;
    sf::Texture backgroundtexture;
    sf::Sprite backgroundsprite;
    sf::RectangleShape Frame[4];
    sf::RectangleShape shadows[4];
    sf::Texture texture[4];
    sf::Sprite sprite[4];
    sf::Font font;
    sf::Text name[4];
    sf::Text title;
    bool selected[4];
    bool selected_pets[4];
public:
    PetSelection();
    void loadAssets();
    void render(sf::RenderWindow& window);
    void handleInput(sf::RenderWindow& window, Game& game, GameManager& MyGame);
    void reset();
};
class MainMenu {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Music backgroundMusic;
    sf::RectangleShape* buttons[8];
    sf::Font font;
    sf::Text buttonText[8];

public:
    MainMenu();
    ~MainMenu();
    void loadAssets();
    void render(sf::RenderWindow& window);
    void handleInput(sf::RenderWindow& window, int state, FileHandeling& file, Game&,GameManager& );
};
class Inventory_Graphics {
private:
    sf::Font font;
    sf::Text title;
    sf::Texture backgroundtexture;
    sf::Sprite backgroundsprite;
    sf::Texture arrowTexture;
    sf::Sprite  arrowSprite;
    sf::Texture        texture[4];
    sf::Sprite         sprite[4];
    sf::Text           names[4];
    sf::Text           countText[4];
    sf::RectangleShape btnRemove[4];
    sf::RectangleShape addButton;
    sf::Text           txtRemove[4];
    sf::Text           txtAddButton;
    sf::Text description[4];
    sf::Text header[4];
    sf::RectangleShape rowBg[5];

public:

    Inventory_Graphics();
    void loadAssets(GameManager& MyGame);
    void render(sf::RenderWindow& window, GameManager& MyGame);
    void handleInput(sf::RenderWindow& window, int state, Game& game, GameManager& MyGame);
};
struct Bullet {
    sf::Sprite sprite;
    bool       active = false;
};
class Arena_Graphics {
private:
    sf::Sprite arrowSprite;
    sf::Texture arrowTexture;
    sf::Font font;
    sf::Text text;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Sprite playerSprites[4];
    sf::Sprite aiSprites[4];
    sf::Texture ArenaTexture[4];
    sf::RectangleShape playerHealthBars[4];
 sf::RectangleShape aiHealthBars[4];

 sf::Texture dragonabilityTexture;
 sf::Sprite dragonabilitySprite;
 sf::Texture phoenixabilityTexture;
 sf::Sprite phoenixabilitySprite;
 sf::Texture griffinabilityTexture;
 sf::Sprite griffinabilitySprite;

 sf::Texture powerupTexture;
 sf::Sprite powerupSprite[4];
 Bullet bullets[500];
 int nextBullet = 0;

 sf::Texture AIBulletTexture;
 Bullet AIbullet[500];
 int nextaibullet=0;
 bool spaceWasDown = false;

 sf::Texture BulletTexture[4];
 sf::Clock fireclock[4];
 int bulletFrame[4];
 int spawnedpowerup = 0;


    sf::Clock clock[4];
    int currentFrame[4];
    int selectedPet;
    
public:
    sf::Clock pclock;
    bool check = true;
    void shootBullet( GameManager& MyGame);
    void shootAIBullet(GameManager& MyGame);
   void checkCollisions(GameManager& MyGame);
    ~Arena_Graphics();
    Arena_Graphics();
    void loadAssets(GameManager& MyGame);
    void render(sf::RenderWindow& window,  GameManager& MyGame);
    void handleInput(sf::RenderWindow& window, Game& game, int state, GameManager& MyGame);
    void update(float deltaTime);
    void updateAnimation(sf::RenderWindow& window);
    void update(sf::RenderWindow& window,Game& , GameManager& MyGame);
    void updateHealthBars(Arena& arena);
   bool  checkGameStatus( GameManager& MyGame);
   void deployPowerUps(sf::RenderWindow& window,GameManager& MyGame);
};
class Game {
private:
    sf::RenderWindow window;
    int currentState; // 0 main_menu 1 inventory 2 arena 3 shop
    MainMenu mainMenu;
    Inventory_Graphics inventory;
    Arena_Graphics arena;
    PetSelection petselection;
    Shop_Graphics shop;
    Arena_Menu arenaMenu;
    LeaderBoard leaderboard;
    Training_Camp trainingCamp;
    int battle_type;
public:
    Game();
    ~Game();

    void run(sf::RenderWindow& window , Game& game , FileHandeling&file, GameManager& MyGame);                    // Main game loop
    void handleEvents(sf::RenderWindow& window, Game& game , FileHandeling& file, GameManager& MyGame);          // General event handler
    void handleInput(sf::RenderWindow& window, int state, Game& game);
    void render(sf::RenderWindow& window, GameManager& MyGame);                // General renderer
    void switchState(int,int);  // Switch between screens
    Arena_Graphics getArenaGraphics() {
        return arena;
    }
    int get_battleType() {
        return battle_type;
    }
    void set_battleType(int value) {
        battle_type = value;
    }
    PetSelection* getPetSelection() {
        return &petselection;
    }
};