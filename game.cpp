#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <time.h>
#include "game.h"
#include "cell.h"


game::game(int W, int H):W(W), H(H) {
	//creating a cell grid
	cells = new cell* [H];
	for (int i = 0; i < H; ++i) {
		cells[i] = new cell[W];
	}
	
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++){
			cells[i][j]=cell(sf::Vector2f(j*22,i*22));
		}
	}
	//seting up some shit
	startingPos();
	font.loadFromFile("Rubik.ttf");
	t.setFont(font);
	t.setFillColor(sf::Color::White);
	t.setCharacterSize(50);
	t.setOutlineColor(sf::Color::Black);
	t.setOutlineThickness(3);
	
}

void game::startingPos(){
	head = sf::Vector2i(W / 2, H / 2);
	dir = sf::Vector2i(1, 0);
	snake.clear();
	snake.push_back(sf::Vector2i(head.x - 3, head.y));
	snake.push_back(sf::Vector2i(head.x - 2, head.y));
	snake.push_back(sf::Vector2i(head.x - 1, head.y));
	snake.push_back(head);

	setFruit();
}

void game::setFruit() {
	srand(time(0));
	int notSet;
	do {
		notSet = 0;
		fruit.x = rand() % W;
		fruit.y = rand() % H;
		for (int i = 0; i < snake.size(); i++) {
			if (fruit == snake[i]) notSet = 1;
		}
	} while (notSet);
}

void game::update(sf::RenderWindow& win, sf::Sprite& whiteS, sf::Sprite& redS, sf::Sprite& greenS) {
	//once per tick
	if (tick(0.3) && !pause) {
		direction();
		head += dir;
		//walls
		if (head.x < 0) head.x = W - 1;
		if (head.x > W-1) head.x = 0;
		if (head.y < 0) head.y = H - 1;
		if (head.y > H - 1) head.y = 0;

		//colision with body
		for (int i = 0; i < snake.size(); i++) {
			if (snake[i]==head) {
				startingPos();
				dir == sf::Vector2i(1, 0);
				t.setString("YOU LOSE");
				t.setPosition(sf::Vector2f((W * 22) / 2 - 130, (H * 22) / 2 - 70));
				win.draw(t);
				win.display();
				Sleep(2000);
				break;
			}
		}

		//updating snake shape
		snake.push_back(head);
		if (head != fruit) {
			snake.erase(snake.begin());
		}
		else setFruit();
	}
	
	cells[fruit.y][fruit.x].active = 2;

	//seting all cells of snake active
	for (int i = 0; i < snake.size(); i++){
		cells[snake[i].y][snake[i].x].active = 1;
	}


	//drawing
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {

			if (cells[i][j].active == 1) {
				redS.setPosition(cells[i][j].position);
				win.draw(redS);
			}
			else if (cells[i][j].active == 2) {
				greenS.setPosition(cells[i][j].position);
				win.draw(greenS);
			}
			else {
				whiteS.setPosition(cells[i][j].position);
				win.draw(whiteS);
			}
			cells[i][j].active = 0;

			
		}
	}
	
	//pause
	if (!pause && GetAsyncKeyState(VK_SPACE)) {
		pause = true;
		t.setString("PAUSE");
		t.setPosition(sf::Vector2f((W * 22) / 2 - 80, (H * 22) / 2 - 60));
	}
	if (pause && GetAsyncKeyState(VK_RETURN)) {
		pause = false;
	}
	if (pause) {
		win.draw(t);
	}
}

bool game::tick(float lim) {
	if (clk.getElapsedTime().asSeconds() > lim) {
		clk.restart();
		return true;
	}
	else return false;
}

void game::direction() {
	sf::Vector2i copyDir = dir;

	if (GetAsyncKeyState('W')) dir = sf::Vector2i(0, -1);
	if (GetAsyncKeyState('D')) dir = sf::Vector2i(1, 0);
	if (GetAsyncKeyState('S')) dir = sf::Vector2i(0, 1);
	if (GetAsyncKeyState('A')) dir = sf::Vector2i(-1, 0);

	if (GetAsyncKeyState(VK_UP)) dir = sf::Vector2i(0, -1);
	if (GetAsyncKeyState(VK_RIGHT)) dir = sf::Vector2i(1, 0);
	if (GetAsyncKeyState(VK_DOWN)) dir = sf::Vector2i(0, 1);
	if (GetAsyncKeyState(VK_LEFT)) dir = sf::Vector2i(-1, 0);

	if(dir== sf::Vector2i((-1)*copyDir.x, (-1) * copyDir.y)) dir = copyDir;
}