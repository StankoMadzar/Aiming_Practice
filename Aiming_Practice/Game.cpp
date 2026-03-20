#include "Game.h"

// Private Functions
void Game::initVariables()
{
	this->window = nullptr;
    endGame = false;
    points = 0;
    health = 20;
    enemySpawnTimerMax = 10.f;
    enemySpawnTimer = enemySpawnTimerMax;
    maxEnemies = 7;
    mouseHeld = false;
}

void Game::initWindow()
{
	videoMode.height = 600;
	videoMode.width = 800;
	this->window = new sf::RenderWindow(videoMode, "Aiming Practice", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

int Game::initFonts()
{
    if(!font.loadFromFile("Fonts/ARIAL.TTF"));
    {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }
}

void Game::initText()
{
    uiText.setFont(font);
    uiText.setCharacterSize(24);
    uiText.setFillColor(sf::Color::White);
    uiText.setString("TEST");
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
	initVariables();
	initWindow();
    initFonts();
    initText();
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

const bool Game::getEndGame() const
{
    return endGame;
}

void Game::spawnEnemy()
{
    enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(window->getSize().x - enemy.getSize().x)), 0.f);

    int type = rand() % 5;
    switch (type)
    {
    case 0:
        enemy.setFillColor(sf::Color::Magenta);
        enemy.setSize(sf::Vector2f(25.f, 25.f));
        break;
    case 1:
        enemy.setFillColor(sf::Color::White);
        enemy.setSize(sf::Vector2f(36.f, 36.f));
        break;
    case 2:
        enemy.setFillColor(sf::Color::Red);
        enemy.setSize(sf::Vector2f(45.f, 45.f));
        break;
    case 3:
        enemy.setFillColor(sf::Color::Yellow);
        enemy.setSize(sf::Vector2f(60.f, 60.f));
        break;
    case 4:
        enemy.setFillColor(sf::Color::Green);
        enemy.setSize(sf::Vector2f(100.f, 100.f));
        break;
    default:
        enemy.setFillColor(sf::Color::Yellow);
        enemy.setSize(sf::Vector2f(60.f, 60.f));
        break;
    }

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

void Game::updateText()
{
    std::stringstream ss;
    ss << "Points: " << points << '\n' << "Health: " << health;
    uiText.setString(ss.str());
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

        enemies[i].move(0.f, 3.f);

        if (enemies[i].getPosition().y > window->getSize().y)
        {
            enemies.erase(enemies.begin() + i);
            health--;
        }
            
    }

    // Check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(mouseHeld == false)
        {
            mouseHeld = true;
            bool deleted = false;
            for (size_t i = 0; i < enemies.size() && deleted == false; i++)
            {
                if (enemies[i].getGlobalBounds().contains(mousePosView))
                {
                    //Gain points
                    if (enemies[i].getFillColor() == sf::Color::Magenta)
                        points += 12.f;
                    else if (enemies[i].getFillColor() == sf::Color::White)
                        points += 8.f;
                    else if (enemies[i].getFillColor() == sf::Color::Red)
                        points += 6.f;
                    else if (enemies[i].getFillColor() == sf::Color::Yellow)
                        points += 3.f;
                    else if (enemies[i].getFillColor() == sf::Color::Green)
                        points += 1.f;
                    else
                        points += 1.f;

                    deleted = true;
                    enemies.erase(enemies.begin() + i);
                }
            }
        }
    }
    else
    {
        mouseHeld = false;
    }
}

// Functions
void Game::update()
{
    if (!endGame)
    {
        pollEvents();
        updateMousePositions();
        updateText();
        updateEnemies();
    }
    else
        displayEndGameScreen();

    if (health <= 0)
        endGame = true;
}

void Game::renderText(sf::RenderTarget& target)
{
    target.draw(uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
    for (auto& e : enemies)
    {
        target.draw(e);
    }
}

void Game::render()
{
    window->clear();      // clear previous frame

    renderEnemies(*window);
    renderText(*window);
    window->display();    // tell game that you are done drawing to the frame
}
