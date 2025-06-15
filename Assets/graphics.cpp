#include "graphics.h"
#include <algorithm>
#include <cmath>
static void clampToWindow(const sf::RenderWindow& window, sf::Sprite& spr) {
    float x = spr.getGlobalBounds().left;
    float y = spr.getGlobalBounds().top;
    float w = spr.getGlobalBounds().width;
    float h = spr.getGlobalBounds().height;
    float maxX = window.getSize().x - w;
    float maxY = window.getSize().y - h;
    if (x < 0)       x = 0;
    else if (x > maxX) x = maxX;
    if (y < 0)       y = 0;
    else if (y > maxY) y = maxY;
    spr.setPosition(x, y);
}

Game::Game() {
    currentState = 0;
}
Game::~Game() {}
void Game::run(sf::RenderWindow& window , Game& game ,FileHandeling&file, GameManager& MyGame) {
    trainingCamp.loadAssets(MyGame);
    leaderboard.loadAssets(MyGame);
    mainMenu.loadAssets();
    petselection.loadAssets();
    shop.loadAssets( MyGame);            // Load assets of all the classes
      inventory.loadAssets(MyGame);
  arena.loadAssets(MyGame);
  arenaMenu.loadAssets(MyGame);

    while (window.isOpen()) {
        if (MyGame.getArena()->getScore()>10)
            MyGame.getPlayer(0)->IncreaseLevel();  // Increase level based on score

        for (int i = 0; i < 4; i++) {
            if (MyGame.GetPet(i)->getHealth() > 200
                && MyGame.GetPet(i)->getPower() > 200
                && MyGame.GetPet(i)->getDefense() > 200
                && MyGame.GetPet(i)->getSpeed() > 200
                ) {                                        // Evolution of pet after reaching a threshold
                MyGame.GetPet(i)->restoreHealth(250);
                MyGame.GetPet(i)->increasePower(250);
                MyGame.GetPet(i)->increaseDefense(250);
                MyGame.GetPet(i)->increaseSpeed(250);
            }
        }
        handleEvents(window,game,file, MyGame); // handle events of all classes 
        render(window,MyGame);                // render events of all classes 
        arena.update(window,game,MyGame);
    }
   

}
void Game::handleEvents(sf::RenderWindow& window, Game& game , FileHandeling& file, GameManager& MyGame) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        switch (currentState){
        case 0:
            mainMenu.handleInput(window, currentState,file,game,MyGame);
            break;
        case 1:
            inventory.handleInput(window, currentState,game,MyGame);
           break;
        case 2:
            arenaMenu.handleInput(window, currentState, game, MyGame);
           break;
        case 3:
            shop.handleInput(window, game, MyGame);
            break;
        case 4:
            petselection.handleInput(window, game, MyGame);
                break;
        case 5:
            leaderboard.handleInput(window, currentState,game, MyGame);
            break;
        case 6:
            trainingCamp.handleInput(window, currentState, game, MyGame);
        case 7:
            arena.handleInput(window,game, currentState,MyGame);
            break;
        }
    }
}
void Game::render(sf::RenderWindow& window, GameManager& MyGame) {
    window.clear();
    switch (currentState) {
    case 0:
        mainMenu.render(window);
        break;
    case 1:
        inventory.render(window, MyGame);  
        break;
    case 2:
           arenaMenu.render(window, MyGame);     
        break;
    case 3:
        shop.render(window,  MyGame);
        break;
    case 4:
        petselection.render(window);
        break;
    case 5:
        leaderboard.render(window, MyGame);
        break;
    case 6:
        trainingCamp.render(window, MyGame);
        break;
    case 7:
          arena.render(window,MyGame);
          break;
    }
    window.display();
}
void Game::switchState(int state,int type=0) {
    currentState = state;
    battle_type = type;
    if (state == 4) {
        arena.check = true;
    }   
}


MainMenu::MainMenu() {
    for (int i = 0; i < 7; i++)
        buttons[i] = NULL;
}
MainMenu::~MainMenu() {}
void MainMenu::loadAssets() {
    // Load font and background image
    font.loadFromFile("arial.ttf");
    backgroundTexture.loadFromFile("image2.jpg");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(800.0f / backgroundTexture.getSize().x, 600.0f / backgroundTexture.getSize().y);
    backgroundMusic.openFromFile("Background audio.ogg");
    backgroundMusic.play();
    backgroundMusic.setLoop(true);

    std::string buttonLabels[8] = { "Start Game", "Load Game", "Inventory", "Shop", "Arena", "Training Campus", "LeaderBoard","Exit"};

    
  
    const sf::Color BUTTON_COLOR_DARK(30, 30, 30, 200);
    const sf::Color TEXT_COLOR_DARK(220, 220, 220, 255);

    // Button style configuration
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const int BUTTON_WIDTH = 200;
    const int BUTTON_HEIGHT = 40;
    const int BUTTON_SPACING = 20;

    // Create buttons
    for (int i = 0; i < 8; ++i) {
        // Create rectangle buttons
        buttons[i] = new sf::RectangleShape(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
        buttons[i]->setFillColor(BUTTON_COLOR_DARK);
        buttons[i]->setOutlineThickness(2);
        buttons[i]->setOutlineColor(sf::Color::Black);

        // Position calculation
        float startY = 130;
        buttons[i]->setPosition(
            (WINDOW_WIDTH - BUTTON_WIDTH) / 2,
            startY + i * (BUTTON_HEIGHT + BUTTON_SPACING)
        );

        // Set button text
        buttonText[i].setFont(font);
        buttonText[i].setString(buttonLabels[i]);
        buttonText[i].setCharacterSize(24);
        buttonText[i].setFillColor(TEXT_COLOR_DARK);
        buttonText[i].setStyle(sf::Text::Bold);

        // Center the text within the button
        sf::FloatRect textBounds = buttonText[i].getLocalBounds();
        buttonText[i].setOrigin(
            textBounds.left + textBounds.width / 2.0f,
            textBounds.top + textBounds.height / 2.0f
        );
        buttonText[i].setPosition(
            buttons[i]->getPosition().x + BUTTON_WIDTH / 2.0f,
            buttons[i]->getPosition().y + BUTTON_HEIGHT / 2.0f
        );
    }

}
void MainMenu::render(sf::RenderWindow& window) {
    
    window.clear();
    window.draw(backgroundSprite);  // Draw the background image 
    for (int i = 0; i < 8; ++i) {
        window.draw(*buttons[i]);  // Draw each button
        window.draw(buttonText[i]);  // Draw the button text
    }
   
}
void MainMenu::handleInput(sf::RenderWindow& window,int state, FileHandeling& file, Game& game,GameManager& MyGame) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        for (int i = 0; i < 8; ++i) {
            if (buttons[i]->getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {

                switch (i) {
                case 0:
                    game.switchState(4);
                case 1:
                    file.loadGame(MyGame, "Magical_Pets_Kingdom.txt");
                    break;
                case 2: 
                    game.switchState(1);
                    break;
                case 3: 
                    game.switchState(3);
                    break; 
                case 4: 
                    game.switchState(2);
                    break;
                case 5: 
                    game.switchState(6);
                    break;
                case 6: 
                    game.switchState(5);
                    break;
                case 7:
                    window.close();
                    break;
                }
            }
        }
    }
}


Shop_Graphics::Shop_Graphics() {}
void Shop_Graphics::loadAssets(GameManager& MyGame) {

    coinTexture.loadFromFile("coins.png");
    coinSprite.setTexture(coinTexture);
    float scale = 32.f / std::max(coinSprite.getLocalBounds().width, coinSprite.getLocalBounds().height);
    coinSprite.setScale(0.2f, 0.2f);
    coinSprite.setPosition(10.f, 10.f);

    coinText.setFont(font);
    coinText.setCharacterSize(20);
    coinText.setFillColor(sf::Color(255, 223, 0));
    coinText.setOutlineColor(sf::Color(30, 30, 30));
    coinText.setOutlineThickness(2.f);

    float x = coinSprite.getPosition().x + coinSprite.getGlobalBounds().width + 8.f;
    float y = coinSprite.getPosition().y + (coinSprite.getGlobalBounds().height - coinText.getLocalBounds().height) / 2.f;
    coinText.setPosition(x, y);

    arrowTexture.loadFromFile("tick3.png");
    arrowSprite.setTexture(arrowTexture);
    arrowSprite.setOrigin(arrowSprite.getLocalBounds().width, 0.f);
    arrowSprite.setPosition(800.f - 10.f, 10.f);
    arrowSprite.setScale(0.3f, 0.3f);
    backgroundtexture.loadFromFile("selection background.png");
    backgroundsprite.setTexture(backgroundtexture);
    font.loadFromFile("arial.ttf");

    title.setFont(font);
    title.setString("Shop");
    title.setCharacterSize(64);
    title.setStyle(sf::Text::Bold);
    title.setLetterSpacing(1.2f);
    title.setFillColor(sf::Color(233, 30, 99, 255));
    title.setOutlineColor(sf::Color(30, 40, 80));  // deep midnight-blue
    title.setOutlineThickness(3.f);


    title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
    title.setPosition(400.f, 50.f);

    // Load textures
    texture[0].loadFromFile("healingpotion.jpg");
    texture[1].loadFromFile("manapotion.jpg");
    texture[2].loadFromFile("speedpotion.jpg");
    texture[3].loadFromFile("shield.png");

    // Set textures to the sprites
    sprite[0].setTexture(texture[0]);
    sprite[0].setScale(1.0f, 1.0f);

    sprite[1].setTexture(texture[1]);
    sprite[1].setScale(2.0f, 2.0f);

    sprite[2].setTexture(texture[2]);
    sprite[2].setScale(1.5f, 1.5f);

    sprite[3].setTexture(texture[3]);
    sprite[3].setScale(1.5f, 1.5f);

    const float CARD_WIDTH = 150.f;
    const float CARD_HEIGHT = 200;
    const float CARD_SPACING = 40.f;
    const float TEXT_MARGIN = 20.f; 

    float totalWidth = 4 * CARD_WIDTH + 3 * CARD_SPACING;
    float START_X = (800.f - totalWidth) / 2.f;
    float START_Y = (600.f - CARD_HEIGHT) / 2.f+50;

    for (int i = 0; i < 4; ++i) {
       
        Frame[i].setSize({ CARD_WIDTH, CARD_HEIGHT });
        Frame[i].setPosition( START_X + i * (CARD_WIDTH + CARD_SPACING),START_Y);
        Frame[i].setOutlineThickness(3.f);
        Frame[i].setFillColor(sf::Color(20, 30, 60, 200));
        Frame[i].setOutlineColor(sf::Color(120, 200, 180, 200));

        float scaleX = CARD_WIDTH / sprite[i].getLocalBounds().width;
        float scaleY = CARD_HEIGHT / sprite[i].getLocalBounds().height;
        sprite[i].setScale(scaleX, scaleY);

        // Center origin and position it in the middle of the frame
        sprite[i].setOrigin(sprite[i].getLocalBounds().width / 2, sprite[i].getLocalBounds().height / 2);
        sprite[i].setPosition(
            Frame[i].getPosition().x + CARD_WIDTH / 2,
            Frame[i].getPosition().y + CARD_HEIGHT / 2
        );

        //  Text label below the card
        name[i].setFont(font);
        if (i == 0)
            name[i].setString("Healing Potion");
        else if (i == 1)
            name[i].setString("Mana Potion");
        else if (i == 2)
            name[i].setString("Buff Item");
        else
            name[i].setString("Shield");
      
        name[i].setCharacterSize(24);
        name[i].setOutlineThickness(2.f);
        name[i].setFillColor(sf::Color(156, 39, 176, 255));
        name[i].setOutlineColor(sf::Color(30, 10, 50, 255));
       
        name[i].setOrigin(name[i].getLocalBounds().width / 2, name[i].getLocalBounds().height / 2);
        name[i].setPosition(
            Frame[i].getPosition().x + CARD_WIDTH / 2,
            Frame[i].getPosition().y + CARD_HEIGHT + 10 + name[i].getLocalBounds().height / 2
        );
    }
   
    for (int i = 0; i < 4; ++i) {
        priceText[i].setFont(font);
        priceText[i].setCharacterSize(20);
        priceText[i].setFillColor(sf::Color(255, 223, 0));  
        priceText[i].setOutlineThickness(1.f);
        priceText[i].setOutlineColor(sf::Color::Black);
        priceText[i].setString("$ "+std::to_string(MyGame.getShop()->getPrice(i)) );
   
        priceBox[i].setSize({ Frame[i].getSize().x, 30.f });
        priceBox[i].setFillColor(sf::Color(20, 30, 60, 200));
        priceBox[i].setOutlineThickness(2.f);
        priceBox[i].setOutlineColor(sf::Color(120, 200, 180, 200));
        
        priceBox[i].setPosition(
            Frame[i].getPosition().x,
            Frame[i].getPosition().y - 30.f - 5.f
        );
        priceText[i].setOrigin(
            priceText[i].getLocalBounds().left + priceText[i].getLocalBounds().width / 2.f,
            priceText[i].getLocalBounds().top + priceText[i].getLocalBounds().height / 2.f
        );
        priceText[i].setPosition(
            Frame[i].getPosition().x + Frame[i].getSize().x / 2.f,
            Frame[i].getPosition().y - 30.f / 2.f - 5.f
        );
    }
}
void Shop_Graphics::render(sf::RenderWindow& window ,GameManager& MyGame) {
    window.draw(backgroundsprite);
    int coins = MyGame.getPlayer(0)->getCash();
    coinText.setString(std::to_string(coins));  // display the coins

    window.draw(coinSprite);
    window.draw(coinText);
    for (int i = 0; i < 4; i++) {
        window.draw(shadows[i]); 
        window.draw(Frame[i]);
        window.draw(sprite[i]);
        window.draw(name[i]);
        window.draw(priceBox[i]);
        window.draw(priceText[i]);
    }
    window.draw(arrowSprite);
    window.draw(title);
   
}
void Shop_Graphics::handleInput(sf::RenderWindow& window,Game& game, GameManager& MyGame) {         
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
       
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if (arrowSprite.getGlobalBounds().contains(mousePos)) {
                game.switchState(0); // go back to the main menu
                continue;
            }
            for (int i = 0; i < 4; ++i) {
                if (Frame[i].getGlobalBounds().contains(mousePos)) {
                    int selectedCard = i;
                            MyGame.getPlayer(0)->buyItem(selectedCard); // buy the selected item
                }
            }
        }
    }
}


Inventory_Graphics::Inventory_Graphics() {}
void Inventory_Graphics::loadAssets(GameManager& MyGame) {
    arrowTexture.loadFromFile("tick3.png");
    arrowSprite.setTexture(arrowTexture);
    arrowSprite.setOrigin(arrowSprite.getLocalBounds().width, 0.f);
    arrowSprite.setPosition(800.f - 10.f, 10.f);
    arrowSprite.setScale(0.3f, 0.3f);
    backgroundtexture.loadFromFile("selection background.png");
    backgroundsprite.setTexture(backgroundtexture);
    font.loadFromFile("arial.ttf");

    title.setFont(font);
    title.setString("Inventory");
    title.setCharacterSize(64);
    title.setStyle(sf::Text::Bold);
    title.setLetterSpacing(1.2f);
    title.setFillColor(sf::Color(233, 30, 99, 255));
    title.setOutlineColor(sf::Color(30, 40, 80));  
    title.setOutlineThickness(3.f);

    title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
    title.setPosition(400.f, 50.f);

    texture[0].loadFromFile("healingpotion.jpg");
    texture[1].loadFromFile("manapotion.jpg");
    texture[2].loadFromFile("speedpotion.jpg");
    texture[3].loadFromFile("shield.png");

    sprite[0].setTexture(texture[0]);
    sprite[0].setScale(1.0f, 1.0f);

    sprite[1].setTexture(texture[1]);
    sprite[1].setScale(2.0f, 2.0f);

    sprite[2].setTexture(texture[2]);
    sprite[2].setScale(1.5f, 1.5f);

    sprite[3].setTexture(texture[3]);
    sprite[3].setScale(1.5f, 1.5f);

    string name[4] = { "Healing Potion","Mana Potion","Buff item","Shield" };
    for (int i = 0; i < 4; ++i) {

        float s = 64.f / std::max(sprite[i].getLocalBounds().width, sprite[i].getLocalBounds().height);
        sprite[i].setScale(0.07, 0.07);

        names[i].setFont(font);
        names[i].setString(name[i]);
        names[i].setCharacterSize(24);
        names[i].setFillColor(sf::Color::White);


    btnRemove[i].setSize({28.f, 28.f});
    btnRemove[i].setFillColor(sf::Color(200, 50, 50, 220)); 
    btnRemove[i].setOutlineThickness(2.f);
    btnRemove[i].setOutlineColor(sf::Color::White);
    btnRemove[i].setPosition(700.f, 100.f + (i + 1) * 60.f + 16.f);
 
    txtRemove[i].setFont(font);
    txtRemove[i].setString("_");
    txtRemove[i].setCharacterSize(24);
    txtRemove[i].setFillColor(sf::Color::White);
    }
        addButton.setSize({ 150.f, 40.f });
        addButton.setFillColor(sf::Color(50, 200, 50, 220));
        addButton.setOutlineThickness(2.f);
        addButton.setOutlineColor(sf::Color::White);
        addButton.setPosition((800.f - 150.f) / 2, 160.f + 4 * 60.f + 20.f);

        txtAddButton.setFont(font);
        txtAddButton.setString("+ Add Item");
        txtAddButton.setCharacterSize(20);
        txtAddButton.setFillColor(sf::Color::White);
        for (int i = 0; i < 4; ++i) {
            float btnY = 160.f + (i + 1) * 60.f  
                + (60.f - 28.f) / 2.f;   
            btnRemove[i].setPosition(750.f, btnY);
            auto tb = txtRemove[i].getLocalBounds();
            txtRemove[i].setOrigin(txtRemove[i].getLocalBounds().left + txtRemove[i].getLocalBounds().width / 2.f, txtRemove[i].getLocalBounds().top + txtRemove[i].getLocalBounds().height / 2.f);
            txtRemove[i].setPosition(750.f + 28.f / 2.f,  btnY + 28.f / 2.f );
        }
            addButton.setPosition(800.f - 150.f - 20.f, 600.f - 40.f - 20.f);
            txtAddButton.setOrigin(txtAddButton.getLocalBounds().left + txtAddButton.getLocalBounds().width / 2.f,
                txtAddButton.getLocalBounds().top + txtAddButton.getLocalBounds().height / 2.f);
            txtAddButton.setPosition(800.f - 150.f - 20.f + 150.f / 2.f, 600.f - 40.f - 20.f + 40.f / 2.f);
   
            for (int i = 0; i < 4; ++i) {
    countText[i].setFont(font);
    countText[i].setCharacterSize(20);
    countText[i].setFillColor(sf::Color(255,223,0));
    countText[i].setOutlineThickness(1.f);
    countText[i].setOutlineColor(sf::Color::Black);

    countText[i].setOrigin(
        countText[i].getLocalBounds().left + countText[i].getLocalBounds().width/2.f,
        countText[i].getLocalBounds().top  + countText[i].getLocalBounds().height/2.f+15
    );
    countText[i].setPosition(600.f, 160.f + (i + 1) * 60.f + 30.f);
}
    sprite[3].setScale(0.2, 0.2);
    for (int i = 0; i < 5; ++i) {
        rowBg[i].setSize({ 800.f, 60.f });
        rowBg[i].setPosition(0.f, 160.f + i * 60.f);
        rowBg[i].setFillColor(i % 2? sf::Color(30, 30, 30, 220): sf::Color(40, 40, 40, 220));
    }
    {
        for (int i = 0; i < 4; i++) {
            header[i].setFont(font);
            description[i].setFont(font);
            header[i].setCharacterSize(20);
            description[i].setCharacterSize(20);
            header[i].setFillColor(sf::Color::White);
        }
      
        header[0].setString("Item");
        header[1].setString("Description");
        header[2].setString("Count");
        header[3].setString("Remove");

        header[0].setPosition(90.f, 160.f + 10.f);
        header[1].setPosition(300.f, 160.f + 10.f);
        header[2].setPosition(600.f, 160.f + 10.f);
        header[3].setPosition(780.f, 160.f + 10.f);
      
    }
    for (int i = 0; i < 4 ; ++i) {
        float y = 160.f + (i + 1) * 60.f + 8.f;
        sprite[i].setPosition(10.f, y);
        names[i].setPosition(90.f, y);
        description[0].setString("Heals us");
        description[1].setString("Increases our ability");
        description[2].setString("provides temporary buffer");
        description[3].setString("Protects us from attack");
        description[i].setPosition(300.f, y + 4.f);
    } 
}
void Inventory_Graphics::render(sf::RenderWindow& window , GameManager& MyGame) {
   
    window.draw(backgroundsprite);
    window.draw(arrowSprite);
    window.draw(title);
    for (int i = 0; i < 5; ++i)
        window.draw(rowBg[i]);
    for (int i = 0; i < 4; ++i)
        window.draw(header[i]);
    for (int i = 0; i < 4; ++i) {
        int count = MyGame.getPlayer(0)->Getinventory()->getCount(i + 1);
        countText[i].setString(std::to_string(count)); // output the quantity
        window.draw(sprite[i]);
        window.draw(names[i]);
        window.draw(description[i]);
        window.draw(countText[i]);
       window.draw(btnRemove[i]);
        window.draw(txtRemove[i]);
    }
    window.draw(addButton);
    window.draw(txtAddButton);
}
void Inventory_Graphics::handleInput(sf::RenderWindow& window, int state, Game& game,GameManager& MyGame) {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if (arrowSprite.getGlobalBounds().contains(mousePos)) {
                game.switchState(0);// go to the main menu
                continue;
            }
            if (addButton.getGlobalBounds().contains(mousePos)) {
                game.switchState(3); // go to shop
                    continue;
            }
            for (int i = 0; i < 4; ++i) {
                if (btnRemove[i].getGlobalBounds().contains(mousePos)) {

                    if (MyGame.getPlayer(0)->Getinventory()->getCount(i + 1)==0) { // check the quantity of item
                        std::cout << "\nNo more items left\n";
                        return;
                    }
                    string name[4] = { "Healing Potion","Mana Potion","Buff item","Shield" };
                    cout << name[i] << " has been removed" << endl;
                    MyGame.getPlayer(0)->Getinventory()->removeItem(i + 1); // remove the item
                   
                    
                }
            }
        }
    }

}


Arena_Graphics::Arena_Graphics() {
    selectedPet = 0;
    srand(time(0));
}
Arena_Graphics::~Arena_Graphics() {}
void Arena_Graphics::loadAssets(GameManager& MyGame) {
    pclock.restart();
    arrowTexture.loadFromFile("tick3.png");
    arrowSprite.setTexture(arrowTexture);
    arrowSprite.setOrigin(arrowSprite.getLocalBounds().width, arrowSprite.getLocalBounds().height);
    arrowSprite.setRotation(180.f);
    arrowSprite.setPosition(0.f, 0.f);
    arrowSprite.setScale(0.3f, 0.3f);

    dragonabilityTexture.loadFromFile("dragonspecialability.png");
    dragonabilitySprite.setTexture(dragonabilityTexture);
    phoenixabilityTexture.loadFromFile("phoenixspecialability.png");
    phoenixabilitySprite.setTexture(phoenixabilityTexture);
    griffinabilityTexture.loadFromFile("griffinspecialability.png");
    griffinabilitySprite.setTexture(griffinabilityTexture);

    dragonabilitySprite.setTextureRect(sf::IntRect(0, 116, 146, 116));
    phoenixabilitySprite.setTextureRect(sf::IntRect(0, 116, 146, 116));
    griffinabilitySprite.setTextureRect(sf::IntRect(0, 116, 146, 116));

    dragonabilityTexture.setSmooth(true);
    phoenixabilityTexture.setSmooth(true);
    griffinabilityTexture.setSmooth(true);

    powerupTexture.loadFromFile("powerups.png");
    for (int i = 0; i < 4; i++) {
        powerupSprite[i].setTexture(powerupTexture);
        powerupSprite[i].setScale(2.f, 2.f);
    }

    font.loadFromFile("arial.ttf");
    text.setFont(font);
    text.setCharacterSize(72);
    text.setStyle(sf::Text::Bold);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(4.f);

    // Arenas with different textures and increased difficulty
    int type = rand() % 4;
    if (type == 0) {
        backgroundTexture.loadFromFile("arenabackground.jpg");
    }
    else if (type == 1) {
        backgroundTexture.loadFromFile("arenabackground1.jpg");
        for (int i = 0; i < 4; i++) {
            MyGame.GetAI(i)->restoreHealth(MyGame.GetAI(i)->getMaxHealth(MyGame.GetAI(i)) + 20);
            MyGame.GetAI(i)->increasePower(MyGame.GetAI(i)->getMaxPower(MyGame.GetAI(i)) + 20);
            MyGame.GetAI(i)->increaseDefense(MyGame.GetAI(i)->getMaxDefense(MyGame.GetAI(i)) + 20);
            MyGame.GetAI(i)->increaseSpeed(MyGame.GetAI(i)->getMaxSpeed(MyGame.GetAI(i)) + 20);
        }
    }
    else if (type == 2) {
        backgroundTexture.loadFromFile("arenabackground2.png");
        for (int i = 0; i < 4; i++) {
            MyGame.GetAI(i)->restoreHealth(MyGame.GetAI(i)->getMaxHealth(MyGame.GetAI(i)) + 40);
            MyGame.GetAI(i)->increasePower(MyGame.GetAI(i)->getMaxPower(MyGame.GetAI(i)) + 40);
            MyGame.GetAI(i)->increaseDefense(MyGame.GetAI(i)->getMaxDefense(MyGame.GetAI(i)) + 40);
            MyGame.GetAI(i)->increaseSpeed(MyGame.GetAI(i)->getMaxSpeed(MyGame.GetAI(i)) + 40);
        }
    } 
    else {
        backgroundTexture.loadFromFile("arenabackground3.png");
        for (int i = 0; i < 4; i++) {
            MyGame.GetAI(i)->restoreHealth(MyGame.GetAI(i)->getMaxHealth(MyGame.GetAI(i)) + 60);
            MyGame.GetAI(i)->increasePower(MyGame.GetAI(i)->getMaxPower(MyGame.GetAI(i)) + 60);
            MyGame.GetAI(i)->increaseDefense(MyGame.GetAI(i)->getMaxDefense(MyGame.GetAI(i)) + 60);
            MyGame.GetAI(i)->increaseSpeed(MyGame.GetAI(i)->getMaxSpeed(MyGame.GetAI(i)) + 60);
        }
    }  

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(800.0f / backgroundTexture.getSize().x, 600.0f / backgroundTexture.getSize().y);

    BulletTexture[0].loadFromFile("dragonfire.png");  
    BulletTexture[1].loadFromFile("lazer1.png");
    BulletTexture[2].loadFromFile("unicornfire.png");  
    BulletTexture[3].loadFromFile("griffinfire.png");
    AIBulletTexture.loadFromFile("aishoot.png");

    for (int i = 0; i < 500; ++i)
        bullets[i].active = false;

    ArenaTexture[0].loadFromFile("Dragon.png");
    ArenaTexture[1].loadFromFile("Phoenix.png");
    ArenaTexture[2].loadFromFile("Unicorn.png");
    ArenaTexture[3].loadFromFile("Griffin.png");
    for (int i = 0; i < 4; i++) {
        playerSprites[i].setTexture(ArenaTexture[i]);
        playerSprites[i].setPosition(100, 100 + i * 120);  // Set initial position

        aiSprites[i].setTexture(ArenaTexture[i]);
        aiSprites[i].setPosition(600, 100 + i * 120); // Right side positions
        aiSprites[i].setScale(-1.f, 1.f); // to flip the direction
    
        currentFrame[i] = 0;  // Start from the first frame in the animation
        clock[i].restart();   // Start the clock for frame animation control
        bulletFrame[i] = 0;
        fireclock[i].restart();

        playerHealthBars[i].setSize({ 60.f, 6.f });
        playerHealthBars[i].setFillColor(sf::Color::Green);
        playerHealthBars[i].setOrigin(30.f, 3.f);

        aiHealthBars[i].setSize({ 60.f, 6.f });
        aiHealthBars[i].setFillColor(sf::Color::Green);
        aiHealthBars[i].setOrigin(30.f, 3.f);
    }

    playerSprites[0].setTextureRect(sf::IntRect(0, 116, 146, 116)); // Start with the first frame
    playerSprites[1].setTextureRect(sf::IntRect(0, 0, 32, 32));
    playerSprites[2].setTextureRect(sf::IntRect(0, 0, 85, 95));
    playerSprites[3].setTextureRect(sf::IntRect(0, 0, 86, 86));

    aiSprites[0].setTextureRect(sf::IntRect(0, 100, 130, 130)); // Start with the first frame
    aiSprites[1].setTextureRect(sf::IntRect(0, 0, 32, 32));
    aiSprites[2].setTextureRect(sf::IntRect(0, 0, 85, 95));
    aiSprites[3].setTextureRect(sf::IntRect(0, 0, 86, 86));


    for (int i = 0; i < 4; i++) {
        ArenaTexture[i].setSmooth(true); // Prevent pixelation
        ArenaTexture[i].setRepeated(false); // Critical for animations
        BulletTexture[i].setSmooth(true);
    }
    AIBulletTexture.setSmooth(true);
    playerSprites[1].setScale(2.f, 2.f);
    aiSprites[1].setScale(-2.f,2.f);
    
}
void Arena_Graphics::render(sf::RenderWindow& window, GameManager& MyGame) {
    window.draw(backgroundSprite);

    for (int i = 0; i < MyGame.getArena()->getpetCount("Player"); i++) {

        Pet* pet = MyGame.getArena()->getPet(i, "Player");
        if (pet && MyGame.getArena()->getState("Player", i)) {

            if (pet->getName() == "Dragon") {
                window.draw(playerSprites[0]);
                window.draw(playerHealthBars[0]);
            }
            else if (pet->getName() == "Phoenix") {
                window.draw(playerSprites[1]);
                window.draw(playerHealthBars[1]);
            }                                          // render all selected pets of the player
            else if (pet->getName() == "Unicorn") {
                window.draw(playerSprites[2]);
                window.draw(playerHealthBars[2]);
            }
            else if (pet->getName() == "Griffin") {
                window.draw(playerSprites[3]);
                window.draw(playerHealthBars[3]);
            }
        }
    }

    for (int i = 0; i < MyGame.getArena()->getpetCount("AI"); i++) {
        Pet* pet = MyGame.getArena()->getPet(i, "AI");
        if (pet && MyGame.getArena()->getState("AI", i)) {

            if (pet->getName() == "Dragon") {
                window.draw(aiSprites[0]);
                window.draw(aiHealthBars[0]);
            }
            else if (pet->getName() == "Phoenix") {
                window.draw(aiSprites[1]);
                window.draw(aiHealthBars[1]);
            }                                          // render all selected pets of the AI
            else if (pet->getName() == "Unicorn") {
                window.draw(aiSprites[2]);
                window.draw(aiHealthBars[2]);
            }
            else if (pet->getName() == "Griffin") {
                window.draw(aiSprites[3]);
                window.draw(aiHealthBars[3]);
            }
        }
    }
    for (int i = 0; i < 500; ++i) {
        if (bullets[i].active)            // draw player's bullets
            window.draw(bullets[i].sprite);
    }
    for (int i = 0; i < 500; ++i) {
        if (AIbullet[i].active) {            // draw AI's bullets
            window.draw(AIbullet[i].sprite);
        }
    }
    if (checkGameStatus(MyGame)) {
        window.draw(text);          // display win or loose
    }
    for (int i = 0; i < 4; ++i) {
        if (MyGame.getArena()->getPstate(i))
            window.draw(powerupSprite[i]);    // display the powerups
    }
    window.draw(arrowSprite);
}
void Arena_Graphics::handleInput(sf::RenderWindow& window,Game& game, int state,  GameManager& MyGame) { 
    
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) selectedPet = 0; // Dragon
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) selectedPet = 1; // Phoenix
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) selectedPet = 2; // Unicorn
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) selectedPet = 3; // Griffin
       
        int speed = MyGame.GetPet(selectedPet)->getSpeed() / 10;
    // Handle input for arena (e.g., move the dragon)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        playerSprites[selectedPet].move(-speed, 0);  // Move dragon left
        clampToWindow(window, playerSprites[selectedPet]);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        playerSprites[selectedPet].move(speed, 0);  // Move dragon right
        clampToWindow(window, playerSprites[selectedPet]);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        playerSprites[selectedPet].move(0, -speed);  // Move dragon up
        clampToWindow(window, playerSprites[selectedPet]);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        playerSprites[selectedPet].move(0, speed);  // Move dragon down
        clampToWindow(window, playerSprites[selectedPet]);
    }
    bool spaceIsDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    if (spaceIsDown && !spaceWasDown) {
        shootBullet( MyGame);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (arrowSprite.getGlobalBounds().contains(mousePos)) {
            game.switchState(0);
        }
    }
    spaceWasDown = spaceIsDown;
    static bool ability1 = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {  // use First ability
        if (!ability1 &&! MyGame.getArena()->getPet(selectedPet, "Player")->getActiveAbility(1)) {
            MyGame.getArena()->getPet(selectedPet, "Player")->useAbility(1,MyGame.getArena());
            ability1 = true;
        }
    }
    else {
        ability1 = false;
    }
    static bool ability2 = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { // use Second ability
        if (!ability2 && !MyGame.getArena()->getPet(selectedPet, "Player")->getActiveAbility(2)) {
            MyGame.getArena()->getPet(selectedPet, "Player")->useAbility(2, MyGame.getArena());
            ability2 = true;
        }
    }
    else {
        ability2 = false;
    } 
    static bool rebirth = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) { // Revive the phoenix after its death
        if (!rebirth && !MyGame.getArena()->getPet(2, "Player")->getActiveAbility(2)) {
            MyGame.getArena()->getPet(1, "Player")->useAbility(2, MyGame.getArena());

            rebirth = true;
        }
    }
    else {
        rebirth = false;
    }
    ///////// Use items 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
        Pet* pet = MyGame.getArena()->getPet(selectedPet,"Player");
        for (int i = 0; i < MyGame.getPlayer(0)->Getinventory()->getItemCount(); i++) {
            if (MyGame.getPlayer(0)->Getinventory()->getItem(i)->getName() == "Healing_Potion")
            {
                MyGame.getPlayer(0)->Getinventory()->useItem(MyGame.getPlayer(0)->Getinventory()->getItem(i), *pet);
                break;
            }
        }

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) {
        Pet* pet = MyGame.getArena()->getPet(selectedPet, "Player");
        for (int i = 0; i < MyGame.getPlayer(0)->Getinventory()->getItemCount(); i++) {
            if (MyGame.getPlayer(0)->Getinventory()->getItem(i)->getName() == "Mana_Potion")
            {
                MyGame.getPlayer(0)->Getinventory()->useItem(MyGame.getPlayer(0)->Getinventory()->getItem(i), *pet);
                break;
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) {
        Pet* pet = MyGame.getArena()->getPet(selectedPet, "Player");
        for (int i = 0; i < MyGame.getPlayer(0)->Getinventory()->getItemCount(); i++) {
            if (MyGame.getPlayer(0)->Getinventory()->getItem(i)->getName() == "Buff_Item")
            {
                MyGame.getPlayer(0)->Getinventory()->useItem(MyGame.getPlayer(0)->Getinventory()->getItem(i), *pet);
                break;
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) {
        Pet* pet = MyGame.getArena()->getPet(selectedPet, "Player");
        for (int i = 0; i < MyGame.getPlayer(0)->Getinventory()->getItemCount(); i++) {
            if (MyGame.getPlayer(0)->Getinventory()->getItem(i)->getName() == "Shield")
            {
                MyGame.getPlayer(0)->Getinventory()->useItem(MyGame.getPlayer(0)->Getinventory()->getItem(i), *pet);
                break;
            }
        }

    }
}
void Arena_Graphics::updateAnimation(sf::RenderWindow& window) {
    
    // update animations for making the players and bullets move across the screen
        if (clock[0].getElapsedTime().asSeconds() > 0.1f) { 
            currentFrame[0]++;
            if (currentFrame[0] >= 3) 
                currentFrame[0] = 0;  

            playerSprites[0].setTextureRect(sf::IntRect(currentFrame[0] * 146, 116, 146, 116));  // Update texture
            aiSprites[0].setTextureRect(sf::IntRect(currentFrame[0] * 146, 116, 146, 116));
            clock[0].restart();  // Restart the clock after changing the frame
        }

        if (clock[1].getElapsedTime().asSeconds() > 0.1f) {
            currentFrame[1]++;
            if (currentFrame[1] >= 6)
                currentFrame[1] = 0;

            playerSprites[1].setTextureRect(sf::IntRect(currentFrame[1] * 32, 0, 32, 32));  // Update texture
            aiSprites[1].setTextureRect(sf::IntRect(currentFrame[1] * 32, 0, 32, 32));
            clock[1].restart();  // Restart the clock after changing the frame
        }

        if (clock[2].getElapsedTime().asSeconds() > 0.1f) {
            currentFrame[2]++;
            if (currentFrame[2] >= 3)
                currentFrame[2] = 0;

            int left =  currentFrame[2] * 85; // 77px per frame
            playerSprites[2].setTextureRect(sf::IntRect(left, 0, 85, 95));
            aiSprites[2].setTextureRect(sf::IntRect(left, 0, 85, 95));
            clock[2].restart();  // Restart the clock after changing the frame
        }

        if (clock[3].getElapsedTime().asSeconds() > 0.1f) {
            currentFrame[3]++;
            if (currentFrame[3] >= 2)
                currentFrame[3] = 0;
            
            int left, top;
            if (currentFrame[3] == 0) {
                left = 15;  
                top = 0;
            }
            else if (currentFrame[3] == 1) {
                left = 100; 
                top = 0;
            }
          
            playerSprites[3].setTextureRect(sf::IntRect(left, top, 86, 86));
            aiSprites[3].setTextureRect(sf::IntRect(left, top, 86, 86));
            clock[3].restart();  // Restart the clock after changing the frame
        }
        for (int i = 0; i < 500; ++i) {
            if (bullets[i].active)
                bullets[i].sprite.move(5, 0);                  // fly right
            if (bullets[i].sprite.getPosition().x > 800)  // off-screen?
                bullets[i].active = false;               // deactivate
        }
        for (int i = 0; i < 500; ++i) {
            if (AIbullet[i].active) {
                AIbullet[i].sprite.move(-5, 0); // Move left
                if (AIbullet[i].sprite.getPosition().x < -50) { // Off left screen
                    AIbullet[i].active = false;
                }
            }
        }
}


void Arena_Graphics::updateHealthBars(Arena& arena)
{
    // Update player health bars
    for (int i = 0; i < arena.getpetCount("Player"); i++) {
        Pet* pet = arena.getPet(i, "Player");
        if (!pet || !arena.getState("Player", i)) continue;

        float maxHealth = pet->getMaxHealth(pet);
        float currentHealth = pet->getHealth();
        float healthPercent = currentHealth / maxHealth;

        // Determine which sprite/health bar to update based on pet type
        int spriteIndex = -1;
        if (pet->getName() == "Dragon")
            spriteIndex = 0;
        else if (pet->getName() == "Phoenix")
            spriteIndex = 1;
        else if (pet->getName() == "Unicorn")
            spriteIndex = 2;
        else if (pet->getName() == "Griffin")
            spriteIndex = 3;

        if (spriteIndex >= 0) {
            // Update health bar size
            playerHealthBars[spriteIndex].setSize({
                std::max(60.f * healthPercent, 5.0f),
                6.f
                });
            // Update health bar color
            if (healthPercent > 0.6f) {
                playerHealthBars[spriteIndex].setFillColor(sf::Color::Green);
            }
            else if (healthPercent > 0.3f) {
                playerHealthBars[spriteIndex].setFillColor(sf::Color::Yellow);
            }
            else {
                playerHealthBars[spriteIndex].setFillColor(sf::Color::Red);
            }

            // Position health bar above pet
            playerHealthBars[spriteIndex].setPosition(
                playerSprites[spriteIndex].getPosition().x,
                playerSprites[spriteIndex].getPosition().y - 20
            );
        }
    }
    // Update AI health bars (same logic as above)
    for (int i = 0; i < arena.getpetCount("AI"); i++) {
        Pet* pet = arena.getPet(i, "AI");
        if (!pet || !arena.getState("AI", i)) continue;

        float maxHealth = pet->getMaxAIHealth(pet);
        float currentHealth = pet->getHealth();
        float healthPercent = currentHealth / maxHealth;

        int spriteIndex = -1;
        if (pet->getName() == "Dragon")
            spriteIndex = 0;
        else if (pet->getName() == "Phoenix")
            spriteIndex = 1;
        else if (pet->getName() == "Unicorn")
            spriteIndex = 2;
        else if (pet->getName() == "Griffin")
            spriteIndex = 3;

        if (spriteIndex >= 0) {
            aiHealthBars[spriteIndex].setSize({
                std::max(15.f * healthPercent, 5.0f),
                6.f
                });

            if (healthPercent > 0.6f) {
                aiHealthBars[spriteIndex].setFillColor(sf::Color::Green);
            }
            else if (healthPercent > 0.3f) {
                aiHealthBars[spriteIndex].setFillColor(sf::Color::Yellow);
            }
            else {
                aiHealthBars[spriteIndex].setFillColor(sf::Color::Red);
            }

            aiHealthBars[spriteIndex].setPosition(
                aiSprites[spriteIndex].getPosition().x,
                aiSprites[spriteIndex].getPosition().y - 20
            );
        }
    }
}
void Arena_Graphics::update(sf::RenderWindow& window,Game& game , GameManager& MyGame) {
    // Update the animation continuously
    updateAnimation(window);
    for (int i = 0; i < 4; i++) {
        MyGame.GetPet(i)->AbilityTimeout((MyGame.getArena()));
    }
    deployPowerUps(window, MyGame);
    shootAIBullet(MyGame);
    checkCollisions(MyGame);
    handleInput(window,game, 0, MyGame);
    updateHealthBars(*(MyGame.getArena()));
   
}
void Arena_Graphics::checkCollisions(GameManager& MyGame) {
    Arena* arena = MyGame.getArena();

    for (int b = 0; b < 500; ++b) {
        if (!bullets[b].active) continue;

        for (int j = 0; j < arena->getpetCount("AI"); ++j) {
            Pet* aiPet = arena->getPet(j, "AI");
            if (!aiPet || !arena->getState("AI", j)) continue;

            int spriteIndex = -1;
            if (aiPet->getName() == "Dragon")
                spriteIndex = 0;
            else if (aiPet->getName() == "Phoenix")
                spriteIndex = 1;
            else if (aiPet->getName() == "Unicorn")
                spriteIndex = 2;
            else if (aiPet->getName() == "Griffin")
                spriteIndex = 3;

            if (spriteIndex >= 0 &&
                bullets[b].sprite.getGlobalBounds().intersects( // if bullet hits the AI pet
                    aiSprites[spriteIndex].getGlobalBounds()))
            {
                Pet* playerPet = arena->getPet(selectedPet, "Player");
                if (playerPet) {
                    
                   if(MyGame.getArena()->getPet(selectedPet, "Player")->getName() == "Dragon" &&MyGame.getArena()->getPet(selectedPet, "Player")->getActiveAbility(1))
                       aiPet->Damage(40); // if fireball ability of dragon is being used
                   else
                       aiPet->Damage(abs(playerPet->getPower() / 2 - playerPet->getDefense()/2));
                    if (aiPet->getHealth() <= 0) {
                        arena->setState("AI", j, false);
                    }
                }
                bullets[b].active = false;
                break;
            }
        }
    }
    for (int b = 0; b < 500; ++b) {
        if (!AIbullet[b].active) continue;

        for (int j = 0; j < arena->getpetCount("Player"); ++j) {
            Pet* playerPet = arena->getPet(j, "Player");
            if (!playerPet || !arena->getState("Player", j)) continue;

            int spriteIndex = -1;
            if (playerPet->getName() == "Dragon")
                spriteIndex = 0;
            else if (playerPet->getName() == "Phoenix")
                spriteIndex = 1;
            else if (playerPet->getName() == "Unicorn") 
                spriteIndex = 2;
            else if (playerPet->getName() == "Griffin")
                spriteIndex = 3;

            if (spriteIndex >= 0 &&
                AIbullet[b].sprite.getGlobalBounds().intersects( // check if bullet hits the player's pet
                    playerSprites[spriteIndex].getGlobalBounds()))
            {
                playerPet->Damage(20);
                if (playerPet->getHealth() <= 0) {
                    arena->setState("Player", j, false);
                }
                AIbullet[b].active = false;
                break;
            }
        }
    }
    
    for (int i = 0; i < 4; i++) {
        if (playerSprites[selectedPet].getGlobalBounds().intersects(powerupSprite[i].getGlobalBounds())&& MyGame.getArena()->getPstate(i) )
        {
            int num = rand() % 5;
            if (num == 1)
                MyGame.getArena()->usePowerUp(MyGame.getArena()->getPet(selectedPet, "Player"), "Health");
            else if (num == 2)
                MyGame.getArena()->usePowerUp(MyGame.getArena()->getPet(selectedPet, "Player"), "Power");
            else if (num == 3)
                MyGame.getArena()->usePowerUp(MyGame.getArena()->getPet(selectedPet, "Player"), "Defense");
            else if (num == 4)
                MyGame.getArena()->usePowerUp(MyGame.getArena()->getPet(selectedPet, "Player"), "Speed");
           
            MyGame.getArena()->setPstate(i, false);
        }
    }
}
void Arena_Graphics::shootBullet( GameManager& MyGame) {

    bool ability1 = MyGame.getArena()->getPet(selectedPet, "Player")->getActiveAbility(1);
    bullets[nextBullet].active = true;
    if (MyGame.getArena()->getPet(selectedPet, "Player")->getName() == "Dragon" && ability1) {
        bullets[nextBullet].sprite.setTexture(dragonabilityTexture);
        bullets[nextBullet].sprite.setTextureRect(sf::IntRect(0, 0, 86, 86));
    }
    else {
        bullets[nextBullet].sprite.setTexture(BulletTexture[selectedPet]);
        bullets[nextBullet].sprite.setTextureRect(sf::IntRect(0, 0, 86, 86));
    }
        
        bullets[nextBullet].sprite.setPosition(playerSprites[selectedPet].getPosition().x + 50, playerSprites[selectedPet].getPosition().y + 20);
        nextBullet += 1;


}
void Arena_Graphics::shootAIBullet(GameManager& MyGame) {
    static sf::Clock shootClock;
    const float shootInterval = 1.0f; // Seconds between shots

    if (shootClock.getElapsedTime().asSeconds() < shootInterval)
        return;
    shootClock.restart();

    int bulletIndex = -1;
    for (int i = 0; i < 500; ++i) {
        if (!AIbullet[i].active) {
            bulletIndex = i;
            break;
        }
    }
    if (bulletIndex == -1) return; // No available bullets

    // Shoot from random active AI pet
    int activeCount = MyGame.getArena()->getpetCount("AI");
    if (activeCount == 0) return;

    int randomPet = rand() % activeCount;
    AIbullet[bulletIndex].active = true;
    AIbullet[bulletIndex].sprite.setTexture(AIBulletTexture);
    AIbullet[bulletIndex].sprite.setTextureRect(sf::IntRect(0, 0, 86, 86));

    auto pos = aiSprites[randomPet].getPosition();
    AIbullet[bulletIndex].sprite.setPosition(pos.x +50, pos.y + 20); // Adjusted for left movement
  


}
bool Arena_Graphics::checkGameStatus(GameManager& MyGame) {
    
    int player = 4;
    int ai = 4;
    for (int i = 0; i < 4; i++) {
        if (!MyGame.getArena()->getState("Player", i))
            player--;
        if(!MyGame.getArena()->getState("AI", i))
            ai--;
    }
    if (ai == 0 ) {
         text.setString("You Won");
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width * 0.5f,
            bounds.top + bounds.height * 0.5f);
        text.setPosition(800 * 0.5f,
            600 * 0.5f);
        text.setFillColor(sf::Color::Green);
        if (check) {
            MyGame.getArena()->increaseScore();
            MyGame.getPlayer(0)->increaseGamesWon();
            MyGame.getArena()->setpetCount(0, "Player");
        }
        check = false;
        return true;
    }
    else if (player == 0 && check) {
        text.setString("Game Over");
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.left + bounds.width * 0.5f,
            bounds.top + bounds.height * 0.5f);
        text.setPosition(800 * 0.5f,
            600 * 0.5f);
        text.setFillColor(sf::Color::Red);
        check = false;
        return true;
    }
    
   
}
void Arena_Graphics::deployPowerUps(sf::RenderWindow& window,GameManager& MyGame)
{
    if (pclock.getElapsedTime().asSeconds() >= 20.f) {
        int x = rand() % 801; // random locations on the screen
        int y = rand() % 601;
        powerupSprite[spawnedpowerup].setPosition(static_cast<float>(x), static_cast<float>(y));
        pclock.restart();
        MyGame.getArena()->setPstate(spawnedpowerup, true);
        spawnedpowerup = (spawnedpowerup + 1) % 4;

    }
    for (int i = 0; i < 4; ++i) {
        if (MyGame.getArena()->getPstate(i))
            window.draw(powerupSprite[i]);
    }
}


 PetSelection::PetSelection() {
    
}
 void PetSelection::reset()
 {
     for (int i = 0; i < 4; i++){
         selected[i] = false;
     selected_pets[i] = false;
 }
 }
 void PetSelection::loadAssets()
 {
     arrowTexture.loadFromFile("tick3.png");
     arrowSprite.setTexture(arrowTexture);
     arrowSprite.setOrigin(arrowSprite.getLocalBounds().width, 0.f);
     arrowSprite.setPosition(800.f - 10.f, 10.f);
     arrowSprite.setScale(0.3f, 0.3f);
     backgroundtexture.loadFromFile("selection background.png");
     backgroundsprite.setTexture(backgroundtexture);
     font.loadFromFile("arial.ttf");

     title.setFont(font);
     title.setString("Choose Your Pet");
     title.setCharacterSize(64);
     title.setStyle(sf::Text::Bold);
     title.setLetterSpacing(1.2f);   
   title.setFillColor(sf::Color(233, 30, 99, 255));
     title.setOutlineColor(sf::Color(30, 40, 80));  
     title.setOutlineThickness(3.f);

         title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
         title.setPosition(400.f, 50.f);
     
     const float CARD_WIDTH = 300.f;
     const float CARD_HEIGHT = 200.f;
     const float CARD_SPACING = 40.f;

     // Calculate grid positioning
     const float START_X = (800.f - (2 * CARD_WIDTH + CARD_SPACING)) / 2;
     const float START_Y = 60+(600.f - (2 * CARD_HEIGHT + CARD_SPACING)) / 2;

     // Load textures 
     texture[0].loadFromFile("Dragon.png");
     texture[1].loadFromFile("Phoenix.png");
     texture[2].loadFromFile("Unicorn.png");
     texture[3].loadFromFile("Griffin.png");

     // Add textures to the sprites
     sprite[0].setTexture(texture[0]);
     sprite[0].setTextureRect(sf::IntRect(0, 116, 146, 116));
     sprite[0].setScale(1.0f, 1.0f);

     sprite[1].setTexture(texture[1]);
     sprite[1].setTextureRect(sf::IntRect(0, 0, 32, 32));
     sprite[1].setScale(2.0f, 2.0f);

     sprite[2].setTexture(texture[2]);
     sprite[2].setTextureRect(sf::IntRect(0, 0, 85, 95));
     sprite[2].setScale(1.5f, 1.5f);

     sprite[3].setTexture(texture[3]);
     sprite[3].setTextureRect(sf::IntRect(0, 0, 86, 86));
     sprite[3].setScale(1.5f, 1.5f);

     // Create cards in 2x2 grid
     for (int i = 0; i < 4; i++) {
         // Calculate grid position
         int row = i / 2;
         int col = i % 2;

         Frame[i].setSize({ CARD_WIDTH, CARD_HEIGHT });
         Frame[i].setPosition(
             START_X + col * (CARD_WIDTH + CARD_SPACING),
             START_Y + row * (CARD_HEIGHT + CARD_SPACING)
         );

         Frame[i].setFillColor(sf::Color(20, 30, 60, 200)); 
         Frame[i].setOutlineThickness(3.f);
         Frame[i].setOutlineColor(sf::Color(120, 200, 180, 200));

         sf::FloatRect spriteBounds = sprite[i].getLocalBounds();
         sprite[i].setOrigin(spriteBounds.width / 2, spriteBounds.height / 2);
         sprite[i].setPosition(
             Frame[i].getPosition().x + CARD_WIDTH / 2,
             Frame[i].getPosition().y + CARD_HEIGHT / 2 - 20
         );

         name[i].setFont(font);
         name[i].setString((i == 0 ? "Dragon" : i == 1 ? "Phoenix" : i == 2 ? "Unicorn" : "Griffin"));
         name[i].setCharacterSize(28);
         name[i].setFillColor(sf::Color::White);
         name[i].setOutlineThickness(2.f);
         name[i].setOutlineColor(sf::Color::Black);
         
             name[i].setOrigin(name[i].getLocalBounds().width / 2, name[i].getLocalBounds().height / 2);
             name[i].setPosition(
                 Frame[i].getPosition().x + CARD_WIDTH / 2,
                 Frame[i].getPosition().y + CARD_HEIGHT - 50.f
             );
         shadows[i].setSize({ CARD_WIDTH - 10, CARD_HEIGHT - 10 });
         shadows[i].setFillColor(sf::Color(98, 214, 162, 40));
         shadows[i].setPosition(
             Frame[i].getPosition().x + 5,
             Frame[i].getPosition().y + 5
         );
     }
 }
 void PetSelection::render(sf::RenderWindow& window) {
     window.draw(backgroundsprite);
     for (int i = 0; i < 4; i++) {
         window.draw(shadows[i]); // Draw shadow first
         window.draw(Frame[i]);
         window.draw(sprite[i]);
         window.draw(name[i]);
     }
     window.draw(arrowSprite);
     window.draw(title);
 }
 void PetSelection::handleInput(sf::RenderWindow& window,Game& game, GameManager& MyGame) {

     bool selection = true;
     sf::Event event;
    
     while (window.pollEvent(event)) {
         if (event.type == sf::Event::Closed) {
             window.close();
         }

         if (event.type == sf::Event::MouseButtonPressed &&
             event.mouseButton.button == sf::Mouse::Left) {
             sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
             if (arrowSprite.getGlobalBounds().contains(mousePos)) {
                 if (game.get_battleType() == 0)
                     game.switchState(0);
                 else if(game.get_battleType() == 1 || game.get_battleType()==3) {
                     for (int i = 0; i < 4; i++)
                         if (selected_pets[i])
                             selection = false;
                     if (!selection) {
                         if (game.get_battleType() == 3) {
                              bool role[4] = { false,false,false,false };
                             for (int j = 0; j < MyGame.getArena()->getpetCount("Player"); j++) {                               
                                 bool done = false;
                                 int op;
                                 do {
                                     cout << "Enter the role for " << MyGame.getArena()->getPet(j, "Player")->getName() << endl;
                                     cout << "1.Tank" << endl;
                                     cout << "2.Healer" << endl;
                                     cout << "3.Damage Dealer" << endl;
                                     cout << "4.Flash" << endl;
                                     cin >> op;
                                     switch (op) {
                                     case 1: {
                                         if (!role[0]) {
                                             MyGame.getGuild()->assignRole(j, 0);
                                             cout << "\nTank has been assigned to " << MyGame.GetPet(j)->getName() << endl;
                                             role[0] = true;
                                             done = true;
                                         }
                                         else
                                             cout << "\nRole is already assigned" << endl;
                                         break;
                                     }
                                     case 2: {
                                         if (!role[1]) {
                                             MyGame.getGuild()->assignRole(j, 2);
                                             cout << "\nHealer has been assigned to " << MyGame.GetPet(j)->getName() << endl;
                                             role[1] = true;
                                             done = true;
                                         }
                                         else
                                             cout << "\nRole is already assigned" << endl;
                                         break;
                                     }
                                     case 3: {
                                         if (!role[2]) {
                                             MyGame.getGuild()->assignRole(j, 3);
                                             cout << "\nDamage Dealer has been assigned to " << MyGame.GetPet(j)->getName() << endl;
                                             role[2] = true;
                                             done = true;
                                         }
                                         else
                                             cout << "\nRole is already assigned" << endl;
                                         break;
                                     }
                                     case 4: {
                                         if (!role[3]) {
                                             MyGame.getGuild()->assignRole(j, 4);
                                             cout << "\nFlash has been assigned to " << MyGame.GetPet(j)->getName() << endl;
                                             role[3] = true;
                                             done = true;
                                         }
                                         else
                                             cout << "\nRole is already assigned" << endl;
                                         break;
                                     }
                                     }
                                 } while (!done);                                
                             }
                             cout << "\n......Continuing to the game......" << endl;
                         }
                      
                         game.switchState(7); // if 1v1,2v2 or guild than change to arena
                     }
                     else
                         cout << "\nYou must choose a pet" << endl;
                 }
                 else if (game.get_battleType() == 2) {
                     int count = 0;
                     for (int i = 0; i < 4; i++) {
                         if (selected_pets[i])
                             count++;
                     }
                     if (count == 0) {
                         cout << "\nYou must choose a pet" << endl;
                         break;
                     }                      
                     else if (count == 1) {
                         cout << "\nChoose another pet" << endl;
                     }
                     else
                         game.switchState(7);
                 }

                 continue;
             }

             if (game.get_battleType() == 0 || game.get_battleType() == 3) {
                 for (int i = 0; i < 4; ++i) {
                     if (Frame[i].getGlobalBounds().contains(mousePos)) {
                         int selectedCard = i;

                         if (MyGame.getPlayer(0)->get_petCount() >= 4) {
                             std::cout << "\nMaximum pet capacity reached\n";
                             return;
                         }
                         if (selected_pets[selectedCard]) {
                             std::cout << "\nPet is already selected\n";    // ...........Guild Vs Guild.............
                             return;
                         }
                         MyGame.getPlayer(0)->addPet(*MyGame.GetPet(selectedCard));
                         MyGame.getArena()->addPet(MyGame.GetPet(i), "Player");
                         selected_pets[selectedCard] = true;
                     }
                 }
             }
             
             if (game.get_battleType() == 1) {
                 for (int i = 0; i < 4; ++i) {
                     if (Frame[i].getGlobalBounds().contains(mousePos)) {
                         int selectedCard = i;
                         bool alreadySelected = false;
                         for (int j = 0; j < 4; j++) {
                             if (selected_pets[j]) {
                                 alreadySelected = true;
                                 break;                           // ...........1 Vs 1.............
                             }
                         }
                         if (!alreadySelected) {
                             MyGame.getArena()->addPet(MyGame.GetPet(i), "Player");
                             selected_pets[i] = true; // Mark this pet as selected
                             cout << "Selected pet: " << MyGame.GetPet(i)->getName() << endl;
                         }
                         else {
                             cout << "\nYou have already selected a pet" << endl;
                         }
                     }
                 }
             }
             if (game.get_battleType() == 2) {
                 for (int i = 0; i < 4; ++i) {
                     if (Frame[i].getGlobalBounds().contains(mousePos)) {
                         int selectedCard = i;
                         int petcount = 0;
                         for (int j = 0; j < 4; j++) {
                             if (selected_pets[j])
                                 petcount++;
                         }
                         if (petcount >= 2) {
                             cout << "\nCannot select more pets" << endl; // ...........2 Vs 2.............
                             break;
                         }
                         else
                         {
                             MyGame.getArena()->addPet(MyGame.GetPet(i), "Player");
                             selected_pets[i] = true; 
                             cout << "Selected pet: " << MyGame.GetPet(i)->getName() << endl;
                         }

                     }
                 }
             }
         }
     
     }
     static bool ai_pets_added = false;
     if (!ai_pets_added && MyGame.getArena()) {
         if (game.get_battleType() == 0 || game.get_battleType() == 3) {
             // Guild vs Guild - add all 4 AI pets
             for (int i = 0; i < 4; i++) {
                 Pet* ai_pet = MyGame.GetAI(i);
                 if (ai_pet) {
                     MyGame.getArena()->addPet(ai_pet, "AI");
                 }
             }
         }
         else if (game.get_battleType() == 1) {
             // 1v1 - add one random AI pet
             int num = rand() % 4;
             Pet* ai_pet = MyGame.GetAI(num);
             if (ai_pet) {
                 MyGame.getArena()->addPet(ai_pet, "AI");
             }
         }
         else if (game.get_battleType() == 2) {
             // 2v2 - add two random AI pets
             int added = 0;
             while (added < 2) {
                 int num = rand() % 4;
                 Pet* ai_pet = MyGame.GetAI(num);
                 if (ai_pet && !MyGame.getArena()->getPet(added, "AI")) {
                     MyGame.getArena()->addPet(ai_pet, "AI");
                     added++;
                 }
             }
         }
         ai_pets_added = true;
     }

 }


 Arena_Menu::Arena_Menu()
 {
 }
 void Arena_Menu::loadAssets(GameManager& MyGame)
 {
     arrowTexture.loadFromFile("tick3.png");
     arrowSprite.setTexture(arrowTexture);
     arrowSprite.setOrigin(arrowSprite.getLocalBounds().width, arrowSprite.getLocalBounds().height);
     arrowSprite.setRotation(180.f);
     arrowSprite.setPosition(0.f, 0.f);
     arrowSprite.setScale(0.3f, 0.3f);
     backgroundtexture.loadFromFile("arenamenubackground.jpg");
     backgroundsprite.setTexture(backgroundtexture);
     backgroundsprite.setScale(2.f, 2.f);
     font.loadFromFile("arial.ttf");

     title.setFont(font);
     title.setString("Arena");
     title.setCharacterSize(64);
     title.setStyle(sf::Text::Bold);
     title.setLetterSpacing(1.2f);
     title.setFillColor(sf::Color(233, 30, 99, 255));
     title.setOutlineColor(sf::Color(30, 40, 80));  // deep midnight-blue
     title.setOutlineThickness(3.f);

     title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
     title.setPosition(400.f, 50.f);

     optionsTexture[0].loadFromFile("1v1 new.png");
     optionsTexture[1].loadFromFile("2v2 new.png");
     optionsTexture[2].loadFromFile("guild new.png");

     for(int i=0 ; i<3 ; i++)
     optionsSprite[i].setTexture(optionsTexture[i]);

     float gap = 20;
     float x = (800 - (optionsSprite[0].getGlobalBounds().width + optionsSprite[1].getGlobalBounds().width + optionsSprite[2].getGlobalBounds().width + gap * 2)) / 2;
     optionsSprite[0].setPosition(x, 220);
     optionsSprite[1].setPosition(x + optionsSprite[0].getGlobalBounds().width + gap, 220);
     optionsSprite[2].setPosition(x + optionsSprite[0].getGlobalBounds().width + gap + optionsSprite[1].getGlobalBounds().width + gap, 220);
 }
 void Arena_Menu::render(sf::RenderWindow& window, GameManager& MyGame)
 {
     window.draw(backgroundsprite);
     window.draw(arrowSprite);
     window.draw(title);
     for (int i = 0; i < 3; i++) {
         window.draw(optionsSprite[i]);
     }
 }
 void Arena_Menu::handleInput(sf::RenderWindow& window, int state, Game& game, GameManager& MyGame)
 {
     sf::Event event;

     while (window.pollEvent(event)) {
         if (event.type == sf::Event::Closed) {
             window.close();
         }

         if (event.type == sf::Event::MouseButtonPressed &&
             event.mouseButton.button == sf::Mouse::Left) {
             sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
             if (arrowSprite.getGlobalBounds().contains(mousePos)) {
                 game.switchState(0);
                 continue;
             }
             if (optionsSprite[0].getGlobalBounds().contains(mousePos)) {
                 // 1v1 
                  game.switchState(4,1);
             }
             if (optionsSprite[1].getGlobalBounds().contains(mousePos)) {
                 //  2v2 
                 game.switchState(4, 2);
             }
             if (optionsSprite[2].getGlobalBounds().contains(mousePos)) {
                 // guild vs guild 
                 game.switchState(4, 3);
             }
         }
     }
 }
 

 void LeaderBoard::loadAssets(GameManager& MyGame)
 {
     arrowTexture.loadFromFile("tick3.png");
     arrowSprite.setTexture(arrowTexture);
     arrowSprite.setOrigin(arrowSprite.getLocalBounds().width, arrowSprite.getLocalBounds().height);
     arrowSprite.setRotation(180.f);
     arrowSprite.setPosition(0.f, 0.f);
     arrowSprite.setScale(0.3f, 0.3f);
     backgroundtexture.loadFromFile("arenamenubackground.jpg");
     backgroundsprite.setTexture(backgroundtexture);
     backgroundsprite.setScale(2.f, 2.f);
     font.loadFromFile("arial.ttf");

     title.setFont(font);
     title.setString("LeaderBoard");
     title.setCharacterSize(64);
     title.setStyle(sf::Text::Bold);
     title.setLetterSpacing(1.2f);
     title.setFillColor(sf::Color(233, 30, 99, 255));
     title.setOutlineColor(sf::Color(30, 40, 80)); 
     title.setOutlineThickness(3.f);

     title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
     title.setPosition(400.f, 50.f);
    
    }
 void LeaderBoard::render(sf::RenderWindow& window, GameManager& MyGame)
 {
     Player& p = *MyGame.getPlayer(0);
     string stats =
         "Player Name: " + p.getName() +
         "\nTotal Wins: " + std::to_string(p.getGamesWon()) +
         "\nLevel:      " + std::to_string(p.getLevel());

     entry.setFont(font);
     entry.setString(stats);
     entry.setCharacterSize(48);
     entry.setFillColor({ 250, 245, 240 });   
     entry.setOutlineColor({ 80, 20, 20 });
     entry.setOutlineThickness(1.f);

     // Card dimensions
     const float CARD_W = 500.f;
     const float CARD_H = 300.f;
     const float WINDOW_W = 800.f;
     const float WINDOW_H = 600.f;

     float cardX = (WINDOW_W - CARD_W) / 2.f;     // position
     float cardY = (WINDOW_H - CARD_H) / 2.f + 20.f;

     cardShadow.setSize({ CARD_W, CARD_H });
     cardShadow.setFillColor(sf::Color(98, 214, 162, 40));
     cardShadow.setPosition(cardX + 8.f, cardY + 8.f);
     cardShadow.setOutlineThickness(0);

     card.setSize({ CARD_W, CARD_H });
     card.setFillColor({ 128, 32, 32 });
     card.setOutlineColor(sf::Color(200, 200, 200));
     card.setOutlineThickness(4.f);
     card.setPosition(cardX, cardY);

     const float PADDING = 30.f;
     entry.setPosition(cardX + PADDING, cardY + PADDING + 20.f);

     window.draw(backgroundsprite);
     window.draw(arrowSprite);
     window.draw(cardShadow);
     window.draw(card);
     window.draw(title);
     window.draw(entry);
 }
 void LeaderBoard::handleInput(sf::RenderWindow& window, int state, Game& game, GameManager& MyGame)
 {
     sf::Event event;

     while (window.pollEvent(event)) {
         if (event.type == sf::Event::Closed) {
             window.close();
         }

         if (event.type == sf::Event::MouseButtonPressed &&
             event.mouseButton.button == sf::Mouse::Left) {
             sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
             if (arrowSprite.getGlobalBounds().contains(mousePos))
                 game.switchState(0);
         }
     }
 }

 void Training_Camp::loadAssets(GameManager& MyGame)
 {
     arrowTexture.loadFromFile("tick3.png");
     arrowSprite.setTexture(arrowTexture);
     arrowSprite.setOrigin(arrowSprite.getLocalBounds().width, arrowSprite.getLocalBounds().height);
     arrowSprite.setRotation(180.f);
     arrowSprite.setPosition(0.f, 0.f);
     arrowSprite.setScale(0.3f, 0.3f);
     backgroundtexture.loadFromFile("arenamenubackground.jpg");
     backgroundsprite.setTexture(backgroundtexture);
     backgroundsprite.setScale(2.f, 2.f);
     font.loadFromFile("arial.ttf");

     title.setFont(font);
     title.setString("Training Camp");
     title.setCharacterSize(64);
     title.setStyle(sf::Text::Bold);
     title.setLetterSpacing(1.2f);
     title.setFillColor(sf::Color(233, 30, 99, 255));
     title.setOutlineColor(sf::Color(30, 40, 80));  
     title.setOutlineThickness(3.f);

     title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
     title.setPosition(400.f, 50.f);

     std::string buttonLabels[4] = { "Train Dragon", "Train Phoenix", "Train unicorn", "Train griffin" };

     const int WINDOW_WIDTH = 800;
     const int WINDOW_HEIGHT = 600;

     const sf::Color BUTTON_COLOR_DARK(30, 30, 30, 200);
     const sf::Color TEXT_COLOR_DARK(220, 220, 220, 255);
     const sf::Color BUTTON_COLOR_NEON(0, 0, 0, 200);
     const sf::Color TEXT_COLOR_NEON(57, 255, 20, 255);

     const int BUTTON_WIDTH = 250;
     const int BUTTON_HEIGHT = 60;
     const int BUTTON_SPACING = 25;
     // Create buttons
     for (int i = 0; i < 4; ++i) {
        
         buttons[i] = new sf::RectangleShape(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
         buttons[i]->setFillColor(BUTTON_COLOR_NEON);
         buttons[i]->setOutlineThickness(2);
         buttons[i]->setOutlineColor(sf::Color::Black);

         float startY = 190;
         buttons[i]->setPosition(
             (WINDOW_WIDTH - BUTTON_WIDTH) / 2,
             startY + i * (BUTTON_HEIGHT + BUTTON_SPACING)
         );

         // Set button text
         buttonText[i].setFont(font);
         buttonText[i].setString(buttonLabels[i]);
         buttonText[i].setCharacterSize(24);
         buttonText[i].setFillColor(TEXT_COLOR_NEON);
         buttonText[i].setStyle(sf::Text::Bold);

         sf::FloatRect textBounds = buttonText[i].getLocalBounds();
         buttonText[i].setOrigin(
             textBounds.left + textBounds.width / 2.0f,
             textBounds.top + textBounds.height / 2.0f
         );
         buttonText[i].setPosition(
             buttons[i]->getPosition().x + BUTTON_WIDTH / 2.0f,
             buttons[i]->getPosition().y + BUTTON_HEIGHT / 2.0f
         );
     }
 }
 void Training_Camp::render(sf::RenderWindow& window, GameManager& MyGame)
 {
     window.draw(backgroundsprite);
     window.draw(arrowSprite);
     window.draw(title);
     for (int i = 0; i < 4; ++i) {
         window.draw(*buttons[i]);  // Draw each button
         window.draw(buttonText[i]);  // Draw the button text
     }
 }
 void Training_Camp::handleInput(sf::RenderWindow& window, int state, Game& game, GameManager& MyGame)
 {
     sf::Event event;

     while (window.pollEvent(event)) {
         if (event.type == sf::Event::Closed) {
             window.close();
         }
         if (event.type == sf::Event::MouseButtonPressed &&
             event.mouseButton.button == sf::Mouse::Left) {
             sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
             if (arrowSprite.getGlobalBounds().contains(mousePos))
                 game.switchState(0);
             for(int i=0 ; i<4 ; i++)
             if (buttons[i]->getGlobalBounds().contains(mousePos))
                 MyGame.get_training_Complex()->Train(*MyGame.GetPet(i));
         }
     }
 }
