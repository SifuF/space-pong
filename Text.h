#ifndef TEXT_H
#define TEXT_H

#include<iostream>

class Digit {
public:
	Scale scale;
	int numShapes;
	sf::RectangleShape *shape;
	sf::Vector2f position;
	sf::RenderWindow *win;
	int n;

	Digit() {
	}

	void create(int num, sf::Vector2f p, sf::RenderWindow *wind) {
		n = num;
		win = wind;
		position.x = p.x;
		position.y = p.y;
		const sf::Vector2f size(scale.textSize, scale.textSize);
		
		if(n==0) numShapes = 12;
		else if (n == 1) numShapes = 5;
		else if (n == 2) numShapes = 11;
		else if (n == 3) numShapes = 11;
		else if (n == 4) numShapes = 9;
		else if (n == 5) numShapes = 11;
		else if (n == 6) numShapes = 12;
		else if (n == 7) numShapes = 7;
		else if (n == 8) numShapes = 13;
		else if (n == 9) numShapes = 10;

		shape = new sf::RectangleShape[numShapes];

		for (int i = 0; i < numShapes; i++) {
			shape[i].setSize(size);
			shape[i].setFillColor(sf::Color::Yellow);
		}
		
		update();
	}

	void update() {
		int k = 0;

		if (n == 2 || n == 3 || n == 4 || n == 5 || n == 6 || n == 7 || n == 8 || n == 9 || n == 0 )					//////		//////		//////
			{shape[k].setPosition(position.x, position.y); k++;}														//////		//////		//////
		if (n == 2 || n == 3 || n == 5 || n == 6 || n == 7 || n == 8 || n == 9 || n == 0)								//////		//////		//////
			{shape[k].setPosition(position.x + scale.textSize, position.y); k++;}										//////		//////		//////
		if (n == 1 || n == 2 || n == 3 || n == 4 || n == 5 || n == 6 || n == 7 || n == 8 || n == 9 || n == 0)			//////		//////		//////
			{shape[k].setPosition(position.x + 2* scale.textSize, position.y); k++;}									//////		//////		//////
		////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (n == 4 || n == 5 || n == 6 || n == 8 || n == 9 || n == 0)													//////					//////
			{shape[k].setPosition(position.x, position.y + scale.textSize); k++;}										//////					//////
																														//////					//////
																														//////					//////
		if (n == 1 || n == 2 || n == 3 || n == 4 || n == 7 || n == 8 || n == 9 || n == 0)								//////					//////
			{shape[k].setPosition(position.x + 2 * scale.textSize, position.y + scale.textSize); k++;}					//////					//////
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		if (n == 2 || n == 3 || n == 4 || n == 5 || n == 6 || n == 8 || n == 9 || n == 0)								//////		//////		//////
			{shape[k].setPosition(position.x, position.y + 2 * scale.textSize); k++;}									//////		//////		//////
		if (n == 2 || n == 3 || n == 4 || n == 5 || n == 6 || n == 8 || n == 9)											//////		//////		//////
			{shape[k].setPosition(position.x + scale.textSize, position.y + 2 * scale.textSize); k++;}					//////		//////		//////
		if (n == 1 || n == 2 || n == 3 || n == 4 || n == 5 || n == 6 || n == 7 || n == 8 || n == 9 || n == 0)			//////		//////		//////
			{shape[k].setPosition(position.x + 2 * scale.textSize, position.y + 2 * scale.textSize); k++;}				//////		//////		//////
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		if (n == 2 || n == 6 || n == 8 || n == 0)																		//////					//////
			{shape[k].setPosition(position.x, position.y + 3 * scale.textSize); k++;}									//////					//////
																														//////					//////
																														//////					//////
		if (n == 1 || n == 3 || n == 4 || n == 5 || n == 6 || n == 7 || n == 8 || n == 9 || n == 0)						//////					//////
			{shape[k].setPosition(position.x + 2 * scale.textSize, position.y + 3 * scale.textSize); k++;}				//////					//////
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		if (n == 2 || n == 3 || n == 5 || n == 6 || n == 8 || n == 0)													//////		//////		//////
			{shape[k].setPosition(position.x, position.y + 4 * scale.textSize); k++;}									//////		//////		//////
		if (n == 2 || n == 3 || n == 5 || n == 6 || n == 8 || n == 0)													//////		//////		//////
			{shape[k].setPosition(position.x + scale.textSize, position.y + 4 * scale.textSize); k++;}					//////		//////		//////
		if (n == 1 || n == 2 || n == 3 || n == 4 || n == 5 || n == 6 || n == 7 || n == 8 || n == 9 || n == 0)			//////		//////		//////
			{shape[k].setPosition(position.x + 2 * scale.textSize, position.y + 4 * scale.textSize); k++;}				//////		//////		//////
	}

	void draw() {
		update();
		for (int i = 0; i < numShapes; i++) {
			win->draw(shape[i]);
		}
	}

	~Digit() {
		delete[] shape;
	}
};

class Number {
public:
	Scale scale;
	Digit digit0;
	Digit digit1;
	Digit digit2;
	Digit digit3;
	Digit digit4;
	Digit digit5;
	Digit digit6;
	Digit digit7;
	Digit digit8;
	Digit digit9;
	sf::RenderWindow* win;

	Number() {}

	void create(sf::RenderWindow* win) {

		sf::Vector2f pos(0.0f, 0.0f);

		//digit0.create(0, { pos.x , pos.y}, win);
		//digit1.create(1, { pos.x + 4 * textSize, pos.y }, win);
		//digit2.create(2, { pos.x + 4 * 2 * textSize, pos.y }, win);
		//digit3.create(3, { pos.x + 4 * 3 * textSize, pos.y }, win);
		//digit4.create(4, { pos.x + 4 * 4 * textSize, pos.y }, win);
		//digit5.create(5, { pos.x + 4 * 5 * textSize, pos.y }, win);
		//digit6.create(6, { pos.x + 4 * 6 * textSize, pos.y }, win);
		//digit7.create(7, { pos.x + 4 * 7 * textSize, pos.y }, win);
		//digit8.create(8, { pos.x + 4 * 8 * textSize, pos.y }, win);
		//digit9.create(9, { pos.x + 4 * 9 * textSize, pos.y }, win);

		digit0.create(0, { pos.x , pos.y }, win);
		digit1.create(1, { pos.x , pos.y }, win);
		digit2.create(2, { pos.x , pos.y }, win);
		digit3.create(3, { pos.x , pos.y }, win);
		digit4.create(4, { pos.x , pos.y }, win);
		digit5.create(5, { pos.x , pos.y }, win);
		digit6.create(6, { pos.x , pos.y }, win);
		digit7.create(7, { pos.x , pos.y }, win);
		digit8.create(8, { pos.x , pos.y }, win);
		digit9.create(9, { pos.x , pos.y }, win);
		
	}

	void update(int n) {
		
	}

	void drawSingle(int n, sf::Vector2f p) {
		if(n==0) { 
			digit0.position = p;
			digit0.draw(); 
		}
		else if (n == 1) {
			digit1.position = p;
			digit1.draw();
		}
		else if (n == 2) {
			digit2.position = p;
			digit2.draw();
		}
		else if (n == 3) {
			digit3.position = p;
			digit3.draw();
		}
		else if (n == 4) {
			digit4.position = p;
			digit4.draw();
		}
		else if (n == 5) {
			digit5.position = p;
			digit5.draw();
		}
		else if (n == 6) {
			digit6.position = p;
			digit6.draw();
		}
		else if (n == 7) {
			digit7.position = p;
			digit7.draw();
		}
		else if (n == 8) {
			digit8.position = p;
			digit8.draw();
		}
		else if (n == 9) {
			digit9.position = p;
			digit9.draw();
		}
			
	}

	void draw(int n, sf::Vector2f v) {

		int num1 = n % 10;
		int num10 = (n / 10);

		drawSingle(num10, v);
		drawSingle(num1, { v.x + 4 * scale.textSize, v.y });
	}

	~Number() {
	
	}
};

#endif
