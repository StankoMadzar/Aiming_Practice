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
}

// Constructrs and Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
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
}

void Game::render()
{
    this->window->clear(sf::Color::Red);
    this->window->display();
}
