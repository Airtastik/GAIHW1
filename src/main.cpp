#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
void moveAndRotateSprite(sf::Sprite& sprite,int orentation, float move)
{
    // Get the deltaTime for this specific sprite (time since last update)

    
    if (orentation == 0)
    {
        sprite.move({move, 0.f});
     
    }
    else if (orentation == 1)  // After 2 seconds, start rotation
    {
        sprite.setRotation(sf::degrees(90));
        sprite.move({0.f, move});
  
    }
    else if (orentation == 2)
    {
        sprite.setRotation(sf::degrees(180));
        sprite.move({-move, 0.f});
   
    }
    else
    {
        sprite.setRotation(sf::degrees(270));
        sprite.move({0.f, -move});

    }

}

int main()
{
    sf::RenderWindow window(sf::VideoMode({640, 480}), "Homework 1");
    sf::Texture texture;
    
    if (!texture.loadFromFile("boid-sm.png")) // Ensure the texture loads properly
        return -1;

    sf::Sprite sprite(texture); // Start from the left side, center vertically

    sf::Clock clock;
    float duration = 2.0f; // Move across the screen in 1 second
    float speed = 640.0f / duration; // Pixels per second
    float speed2 = 480.0f / duration;
    
    sf::Time elapsedTime = sf::Time::Zero; // Track time

    std::vector<sf::Sprite> sprites;
    sprites.push_back(sprite); // Add initial sprite

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds(); // Get frame time
        elapsedTime += sf::seconds(deltaTime); // Update elapsed time
        float movex = speed * deltaTime;
        float movey = speed2 * deltaTime;
        
       if (elapsedTime.asSeconds() < 2) // sprite 1
        {
            moveAndRotateSprite(sprites[0],0,movex);
        }
        else if(elapsedTime.asSeconds() < 4)  // After 2 seconds start next sprite  sprite 1 2
        {
            moveAndRotateSprite(sprites[0],1,movey);
            sf::Sprite newSprite(texture);
            sprites.push_back(newSprite);
            moveAndRotateSprite(sprites[1],0,movex);
            
        }
        else if(elapsedTime.asSeconds() < 6) { // sprite 1,2,3
            moveAndRotateSprite(sprites[0],2,movex);
            moveAndRotateSprite(sprites[1],1,movey);
            sf::Sprite newSprite(texture);
            sprites.push_back(newSprite);
            moveAndRotateSprite(sprites[2],0,movex);
        }
        else if(elapsedTime.asSeconds() < 8) { // sprite 1,2,3,4
            moveAndRotateSprite(sprites[0],3,movey);
            moveAndRotateSprite(sprites[1],2,movex);
            moveAndRotateSprite(sprites[2],1,movey);
            sf::Sprite newSprite(texture);
            moveAndRotateSprite(sprites[3],0,movex);
        }
        else if(elapsedTime.asSeconds() < 10) { // sprite 2,3,4

            moveAndRotateSprite(sprites[1],3,movey);
            moveAndRotateSprite(sprites[2],2,movex);
            moveAndRotateSprite(sprites[3],1,movey);
        }
        else if(elapsedTime.asSeconds() < 12) { // sprite 3,4
            moveAndRotateSprite(sprites[2],3,movey);
            moveAndRotateSprite(sprites[3],2,movex);
        }
          else if(elapsedTime.asSeconds() < 14) { // sprite 4
              moveAndRotateSprite(sprites[3],3,movey);
        }
        else{ // sprite 4
            if(sprites.size() > 0){
                sprites.erase(sprites.begin()) ;
                sf::Sprite newSprite(texture);
                newSprite.setPosition({0.0f,0.0f});
                sprites.push_back(newSprite);
                elapsedTime = sf::seconds(0);
            }
          
        }
       
        
        window.clear(sf::Color::Green);
        for (const auto& s : sprites) {
            window.draw(s);
        }
        window.display();
    }

}