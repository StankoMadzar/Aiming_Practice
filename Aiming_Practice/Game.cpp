#include "Game.h"

// Private Functions
void Game::initVariables()
{
	this->window = nullptr;
    points = 0;
    enemySpawnTimerMax = 10.f;
    enemySpawnTimer = enemySpawnTimerMax;
    maxEnemies = 10;
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
    //enemy.setOutlineColor(sf::Color::Green);
    //enemy.setOutlineThickness(5.f);
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
	return window->isOpen();
}

void Game::spawnEnemy()
{
    enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(window->getSize().x - enemy.getSize().x)), 0.f);

    enemy.setFillColor(sf::Color::Yellow);
    enemies.push_back(enemy);
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

void Game::updateMousePositions()
{
    mousePosWindow = sf::Mouse::getPosition(*this->window);
    mousePosView = window->mapPixelToCoords(mousePosWindow);
}

void Game::updateEnemies()
{
    if (enemies.size() < maxEnemies)
    {
        if (enemySpawnTimer >= enemySpawnTimerMax)
        {
            // spawn enemy and reset timer
            spawnEnemy();
            enemySpawnTimer = 0.f;
        }
        else
            enemySpawnTimer += 1.f;
    }
    
    // Move and update enemies
    for (size_t i = 0; i < enemies.size(); i++)
    {
        bool deleted = false;

        enemies[i].move(0.f, 4.f);

        // Check if clicked upon
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (enemies[i].getGlobalBounds().contains(mousePosView))
            {
                deleted = true;

                //Gain points
                points += 10.f;
            }
        }

        if (enemies[i].getPosition().y > window->getSize().y)
        {
            deleted = true;
        }

        if (deleted)
            enemies.erase(enemies.begin() + i);
    }
}

// Functions
void Game::update()
{
    pollEvents();
    updateMousePositions();
    updateEnemies();
}

void Game::renderEnemies()
{
    for (auto& e : enemies)
    {
        window->draw(e);
    }
}

void Game::render()
{
    window->clear();      // clear previous frame

    renderEnemies();
    window->display();    // tell game that you are done drawing to the frame
}
