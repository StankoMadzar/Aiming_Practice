#include "Game.h"

// Private Functions
void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	videoMode.height = 600;
	videoMode.width = 800;
	this->window = new sf::RenderWindow(videoMode, "Aiming Practice", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
    enemy.setPosition(10, 10);
    enemy.setSize(sf::Vector2f(100.f, 100.f));
    enemy.setFillColor(sf::Color::Cyan);
    enemy.setOutlineColor(sf::Color::Green);
    enemy.setOutlineThickness(5.f);
}

// Constructrs and Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
    initEnemies();
}

Game::~Game()
{
	delete this->window;
}

// Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
    //Event polling
    while (this->window->pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;

        }
    }
}

// Functions
void Game::update()
{
    this->pollEvents();

    // Update mouse position relative to screen / window
    std::cout << "Mouse pos: " 
        << sf::Mouse::getPosition(*this->window).x 
        << " " << sf::Mouse::getPosition(*this->window).y 
        << std::endl;
}

void Game::render()
{
    this->window->clear();      // clear previous frame

    this->window->draw(enemy);

    this->window->display();    // tell game that you are done drawing to the frame
}
