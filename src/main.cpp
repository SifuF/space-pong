//Pong by SifuF
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Scale.h"
#include "Paddle.h"
#include "AI.h"
#include "Text.h"

Scale scale;

Paddle paddleL;
Paddle paddleR(true);
Puck puck(&paddleL, &paddleR);

AI aiL(&paddleL, &puck);
AI aiR(&paddleR, &puck, true);

Number number;

void instructions() {
    std::cout << "Left paddle:" << std::endl;
    std::cout << "  Up/Down: Q/A" << std::endl;
    std::cout << "  CPU On/Off : W/S" << std::endl << std::endl;

    std::cout << "Right paddle:" << std::endl;
    std::cout << "  Up/Down: Up arrow/Down arrow" << std::endl;
    std::cout << "  CPU On/Off : O/L" << std::endl << std::endl;

    std::cout << "Difficulty:" << std::endl;
    std::cout << "  Easy: V" << std::endl;
    std::cout << "  Hard - Stay : B" << std::endl;
    std::cout << "  Hard - Reset: N" << std::endl;
    std::cout << "  Hard - Follow: M" << std::endl << std::endl;

    std::cout << "Game speed Up/Down : T/G" << std::endl;
    std::cout << "Reset game: R" << std::endl;
    std::cout << "Debug On/Off : E/D" << std::endl;
}

void checkKeys() {
    //clear keys required for human players only
    if (!scale.AI_left) { paddleL.move(0); }
    if (!scale.AI_right) { paddleR.move(0); }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        paddleR.move(1);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        paddleR.move(-1);
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        paddleL.move(1);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        paddleL.move(-1);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        puck.resetGame();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        aiL.scale.debug = true;
        aiR.scale.debug = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        aiL.scale.debug = false;
        aiR.scale.debug = false;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        scale.AI_left = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        scale.AI_left = false;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
        scale.AI_right = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
        scale.AI_right = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
        scale.delay += scale.delayIncrement;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
       scale.delay -= scale.delayIncrement;
       if (scale.delay < 0) {
           scale.delay=0;
       }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
        aiL.strat = STRAT_EASY;
        aiR.strat = STRAT_EASY;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
        aiL.strat = STRAT_STAY;
        aiR.strat = STRAT_STAY;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
        aiL.strat = STRAT_RESET;
        aiR.strat = STRAT_RESET;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
        aiL.strat = STRAT_FOLLOW;
        aiR.strat = STRAT_FOLLOW;
    }
}

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(scale.screenWidth, scale.screenHeight), "SifuF Pong");
    
    instructions();

    paddleL.reset();
    paddleR.reset();
    puck.reset();

    paddleL.shape.setFillColor(sf::Color::Red);
    paddleR.shape.setFillColor(sf::Color::Blue);
    puck.shape.setFillColor(sf::Color::Green);
    
    number.create(&window);

    aiL.init(&window);
    aiR.init(&window);

    sf::Music music;
    if (!music.openFromFile("sound/music.ogg"))
        return -1; // error
    music.setLoop(true);
    music.play();

    sf::Clock clock;
    sf::Time timePrevious = clock.getElapsedTime();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        
        checkKeys();

        sf::Time timeCurrent = clock.getElapsedTime();
        sf::Time frameTime = timeCurrent - timePrevious;
        while (frameTime.asSeconds() < scale.delay) {
            frameTime = clock.getElapsedTime() - timePrevious;
        }
        timePrevious = timeCurrent;
        
        paddleL.update();
        paddleR.update();
        puck.update();

        if (scale.AI_left) { aiL.update(); }
        if (scale.AI_right) { aiR.update(); }
   
        window.draw(puck.shape);
        window.draw(paddleL.shape);
        window.draw(paddleR.shape);

        number.draw(puck.scoreLeft, { scale.screenWidth/8.0f, scale.screenHeight/20.0f });
        number.draw(puck.scoreRight, { scale.screenWidth - 8*scale.textSize - scale.screenWidth / 8.0f, scale.screenHeight / 20.0f });
      
        window.display();
    }

    return 0;
}