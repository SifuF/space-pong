#ifndef PADDLE_H
#define PADDLE_H

#define MOVEUP 100
#define MOVEDOWN 101

class Paddle {
public:
	Scale scale;
	sf::RectangleShape shape;
	int direction;

	Paddle(bool right = false) {
		direction = 0;
		const sf::Vector2f size(scale.width, scale.height);
		shape.setSize(size);
		shape.setFillColor(sf::Color::White);
		shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
		
		if (right) {
			shape.setPosition(scale.screenWidth - shape.getSize().x/2 - scale.fromWall, scale.screenHeight / 2);
		}
		else {
			shape.setPosition(0 + shape.getSize().x/2 + scale.fromWall, scale.screenHeight / 2);
		}
	}

	void move(int dir) {
		switch (dir) {
			case 0:
				direction = 0;
				break;
			case 1:
				direction = MOVEUP;
				break;
			case -1:
				direction = MOVEDOWN;
				break;
		}
	}

	void reset() {
	
	}

	void update() {

		float delta = 0;

		if (direction == MOVEDOWN) delta = scale.moveIncrement;
		else if (direction == MOVEUP) delta = -scale.moveIncrement;

		if (shape.getPosition().y - shape.getSize().y/2 + delta > 0 && 
			shape.getPosition().y < scale.screenHeight - shape.getSize().y / 2 - delta) {
				shape.setPosition(shape.getPosition().x, shape.getPosition().y + delta);
		}
		else if (delta > 0) {
			shape.setPosition(shape.getPosition().x, shape.getPosition().y - scale.rebound);
		}
		else if (delta < 0) {
			shape.setPosition(shape.getPosition().x, shape.getPosition().y + scale.rebound);
		}
	}

	~Paddle() {

	}
};

class Puck {
public:
	Scale scale;
	sf::CircleShape shape;
	sf::Vector2f velocity;
	Paddle* paddleLeft;
	Paddle* paddleRight;
	int scoreLeft;
	int scoreRight;
	bool missed = false;
	bool startLeft = false;
	bool startRight = false;
	sf::SoundBuffer bufferLeft;
	sf::SoundBuffer bufferRight;
	sf::SoundBuffer bufferTop;
	sf::Sound soundLeft;
	sf::Sound soundRight;
	sf::Sound soundTop;

	Puck(Paddle* left, Paddle* right) {
		paddleLeft = left;
		paddleRight = right;
		
		scoreLeft = 0;
		scoreRight = 0;

		shape.setRadius(scale.radius);
		shape.setFillColor(sf::Color::White);
		shape.setOrigin(shape.getRadius(), shape.getRadius());
		shape.setPosition(scale.screenWidth/2, scale.screenHeight/2);

		velocity.x = 0.0f;
		velocity.y = 0.0f;

		if (!bufferLeft.loadFromFile("sound/left.wav")) { 
			std::cout <<"Cannot load file!" <<std::endl; 
		}
		if (!bufferRight.loadFromFile("sound/right.wav")) {
			std::cout << "Cannot load file!" << std::endl;
		}
		if (!bufferTop.loadFromFile("sound/top.wav")) {
			std::cout << "Cannot load file!" << std::endl;
		}

		soundLeft.setBuffer(bufferLeft);
		soundRight.setBuffer(bufferRight);
		soundTop.setBuffer(bufferTop);
	}

	void reset() {

		startLeft = false;
		startRight = false;

		if (scoreLeft > 99 || scoreRight > 99) {
			scoreLeft = 0;
			scoreRight = 0;
		}

		shape.setPosition(scale.screenWidth / 2, scale.screenHeight / 2);

		//float theta = (rand() % 360) * 2 * scale.PI / 360;
		//velocity.x = scale.speed*cos(theta);
		//velocity.y = scale.speed*sin(theta);

		if (rand() % 2 == 0) {
			velocity.x = scale.speed;
		}
		else {
			velocity.x = -scale.speed;
		}
		velocity.y = 0.0f;
	}

	void resetGame() {
		scoreLeft = 0;
		scoreRight = 0;
		
		reset();
	}

	void impact(bool right = false) {
		float unit = scale.height / 8.0f;
		float delta;
		int reverse;
		
		if (right) {
			reverse = -1;
			delta = paddleRight->shape.getPosition().y - shape.getPosition().y;
		}
		else {
			reverse = 1;
			delta = paddleLeft->shape.getPosition().y - shape.getPosition().y;
		}
		
		if (delta <= 0) {	//puck below centre
			delta = -delta;
			if (delta < 1 * unit) {
				velocity.x = -velocity.x;
				velocity.y = 0;
			}
			else if (delta < 2 * unit) {
				velocity.x = scale.speed * cos(scale.PI / 12.0f) * reverse;
				velocity.y = scale.speed * sin(scale.PI / 12.0f);
			}
			else if (delta < 3 * unit) {
				velocity.x = scale.speed * cos(scale.PI / 6.0f) * reverse;
				velocity.y = scale.speed * sin(scale.PI / 6.0f);
			}
			else {
				velocity.x = scale.speed * cos(scale.PI / 4.0f) * reverse;
				velocity.y = scale.speed * sin(scale.PI / 4.0f);
			}
		}
		else {	//puck above centre
			if (delta < 1 * unit) {
				velocity.x = -velocity.x;
				velocity.y = 0;
			}
			else if (delta < 2 * unit) {
				velocity.x = scale.speed * cos(scale.PI / 12.0f) * reverse;
				velocity.y = -scale.speed * sin(scale.PI / 12.0f);
			}
			else if (delta < 3 * unit) {
				velocity.x = scale.speed * cos(scale.PI / 6.0f) * reverse;
				velocity.y = -scale.speed * sin(scale.PI / 6.0f);
			}
			else {
				velocity.x = scale.speed * cos(scale.PI / 4.0f) * reverse;
				velocity.y = -scale.speed * sin(scale.PI / 4.0f);
			}
		}		
	}

	void update() {

		float x = shape.getPosition().x + velocity.x;
		float y = shape.getPosition().y + velocity.y;
		shape.setPosition(x,y);

		//ceiling and floor check
		if (shape.getPosition().y - shape.getRadius() < 0 || shape.getPosition().y + shape.getRadius() > scale.screenHeight) {
			velocity.y = -velocity.y;
			soundTop.play();
		}

		//left paddle check
		if (shape.getPosition().x - shape.getRadius() < 0 + scale.width/2 + scale.fromWall) {
			if (shape.getPosition().y + shape.getRadius() > paddleLeft->shape.getPosition().y - scale.height / 2 &&
				shape.getPosition().y - shape.getRadius() < paddleLeft->shape.getPosition().y + scale.height / 2 &&
				!missed) {
					impact();
					soundLeft.play();
					
					startLeft = true;
					startRight = false;
			}
			else {
				missed = true;
			}

			if (shape.getPosition().x + shape.getRadius() < 0 - scale.offScreen) {
				scoreRight++;
				reset();
			}
		}

		//right paddle check
		if (shape.getPosition().x + shape.getRadius() > scale.screenWidth - scale.width/2 - scale.fromWall) {
			if (shape.getPosition().y + shape.getRadius() > paddleRight->shape.getPosition().y - scale.height / 2 &&
				shape.getPosition().y - shape.getRadius() < paddleRight->shape.getPosition().y + scale.height / 2 &&
				!missed) {
					impact(true);
					soundRight.play();
					
					startRight = true;
					startLeft = false;
			}
			else {
				missed = true;
			}

			if (shape.getPosition().x - shape.getRadius() > scale.screenWidth + scale.offScreen) {
				scoreLeft++;
				reset();
			}
		}

		//reset missed condition
		float center = 1.0;
		if (shape.getPosition().x > scale.screenWidth / 2 - center && shape.getPosition().x < scale.screenWidth / 2 + center) {
			missed = false;
		}
	}

	~Puck() {
	
	}
};

#endif
