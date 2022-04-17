#ifndef AI_H
#define AI_H

#define STRAT_STAY 1000
#define STRAT_RESET 1001
#define STRAT_FOLLOW 1002
#define STRAT_EASY 1005

class AI {
public:
	Scale scale;
	Paddle *paddle;
	Puck *puck;
	sf::RenderWindow* win;
	sf::VertexArray lines;
	sf::VertexArray targetLineLeft;
	sf::VertexArray targetLineRight;
	bool initFromLeft = false;
	bool initFromRight = false;
	float targetR;
	float targetL;
	bool right;
	int strat;

	AI(Paddle *pad, Puck *pp, bool r = false) {
		right = r;
		paddle = pad;
		puck = pp;
		strat = STRAT_STAY;
	}

	void init(sf::RenderWindow* w) {
		win = w;
		lines.setPrimitiveType(sf::LinesStrip);
		
		targetLineLeft.setPrimitiveType(sf::Lines);
		targetLineLeft.append(sf::Vector2f(scale.fromWall + scale.width / 2.0, 0));
		targetLineLeft.append(sf::Vector2f(scale.fromWall + scale.width / 2.0, scale.screenHeight));
		targetLineLeft[0].color = sf::Color::White;
		targetLineLeft[1].color = sf::Color::White;

		targetLineRight.setPrimitiveType(sf::Lines);
		targetLineRight.append(sf::Vector2f(scale.screenWidth - scale.fromWall - scale.width / 2.0, 0));
		targetLineRight.append(sf::Vector2f(scale.screenWidth - scale.fromWall - scale.width / 2.0, scale.screenHeight));
		targetLineRight[0].color = sf::Color::White;
		targetLineRight[1].color = sf::Color::White;

		targetL = scale.screenHeight / 2.0f;
		targetR = scale.screenHeight / 2.0f;
	}

	void update() {

		if (strat == STRAT_EASY) {
			if (puck->shape.getPosition().y > paddle->shape.getPosition().y) {
				paddle->move(-1);
			}
			else {
				paddle->move(1);
			}
		}
		else {
			if (right) {
				if (paddle->shape.getPosition().y < targetR) {
					paddle->move(-1);
				}
				else {
					paddle->move(1);
				}
			}
			else {
				if (paddle->shape.getPosition().y < targetL) {
					paddle->move(-1);
				}
				else {
					paddle->move(1);
				}
			}
		}

		drawLine();
	}

	float vary() {
		float d = scale.height / 2.0f;
		float r = -scale.varyUnit/2 + rand() % scale.varyUnit;
		return r;
	}

	void drawLine() {

		float err = 0.00001;
		
		if (!puck->startLeft && !puck->startRight) {	//clear path after a miss
			lines.clear();
			initFromLeft = false;
			initFromRight = false;
			targetL = scale.screenHeight / 2.0f;
			targetR = scale.screenHeight / 2.0f;
		}
		
		if (puck->startLeft) {		//left paddle impacted
			initFromRight= false;
			if (!initFromLeft) {
				initFromLeft = true;
				lines.clear();
				lines.append(puck->shape.getPosition());

				if (abs(puck->velocity.y) < err) {	
					sf::Vector2f position(puck->shape.getPosition().x + 10000 * puck->velocity.x, puck->shape.getPosition().y);
					lines.append(position);
					lines[0].color = sf::Color::White;

					float t = ((scale.screenWidth - (scale.fromWall + scale.width / 2.0)) - lines[0].position.x) / (lines[1].position.x - lines[0].position.x);
					float posX = lines[0].position.x + t * (lines[1].position.x - lines[0].position.x);
					targetR = lines[0].position.y + t * (lines[1].position.y - lines[0].position.y) + vary();

					if (strat == STRAT_RESET) {
						targetL = scale.screenHeight / 2.0f + vary();
					}
				}
				else {
					if (puck->velocity.y < 0) {		
						float s;
						float t;

						t = puck->shape.getPosition().y / puck->velocity.y;
						s = abs(t) - scale.radius;
						sf::Vector2f position(puck->shape.getPosition().x + s * puck->velocity.x, puck->shape.getPosition().y + s * puck->velocity.y);
						lines.append(position);

						t = -scale.screenHeight / puck->velocity.y;
						s = t - scale.radius * 2;
						sf::Vector2f position2(position.x + s * puck->velocity.x, +position.y - s * puck->velocity.y);
						lines.append(position2);

						t = 10000;
						s = t;
						sf::Vector2f position3(position2.x + s * puck->velocity.x, +position2.y + s * puck->velocity.y);
						lines.append(position3);

						int bounces = 0;
						if (position.x > scale.screenWidth - scale.fromWall + scale.width / 2.0) {
							bounces = 0;
							float t = ((scale.screenWidth - (scale.fromWall + scale.width / 2.0)) - lines[0].position.x) / (lines[1].position.x - lines[0].position.x);
							float posX = lines[0].position.x + t * (lines[1].position.x - lines[0].position.x);
							targetR = lines[0].position.y + t * (lines[1].position.y - lines[0].position.y) + vary();
						}
						else if (position2.x > scale.screenWidth - scale.fromWall + scale.width / 2.0) {
							bounces = 1;
							float t = ((scale.screenWidth - (scale.fromWall + scale.width / 2.0)) - lines[1].position.x) / (lines[2].position.x - lines[1].position.x);
							float posX = lines[1].position.x + t * (lines[2].position.x - lines[1].position.x);
							targetR = lines[1].position.y + t * (lines[2].position.y - lines[1].position.y) + vary();
						}
						else if (position3.x > scale.screenWidth - scale.fromWall + scale.width / 2.0) {
							bounces = 2;
							float t = ((scale.screenWidth - (scale.fromWall + scale.width / 2.0)) - lines[2].position.x) / (lines[3].position.x - lines[2].position.x);
							float posX = lines[2].position.x + t * (lines[3].position.x - lines[2].position.x);
							targetR = lines[2].position.y + t * (lines[3].position.y - lines[2].position.y) + vary();
						}
						else {
							//std::cout << "error!" << std::endl;
						}
						//std::cout << "bounces= " << bounces << std::endl;
					}
					else {							
						float s;
						float t;

						t = (scale.screenHeight - puck->shape.getPosition().y) / puck->velocity.y;
						s = t - scale.radius;
						sf::Vector2f position(puck->shape.getPosition().x + s * puck->velocity.x, puck->shape.getPosition().y + s * puck->velocity.y);
						lines.append(position);

						if (position.x)

							t = scale.screenHeight / puck->velocity.y;
						s = t - scale.radius * 2;
						sf::Vector2f position2(position.x + s * puck->velocity.x, +position.y - s * puck->velocity.y);
						lines.append(position2);

						t = 10000;
						s = t;
						sf::Vector2f position3(position2.x + s * puck->velocity.x, +position2.y + s * puck->velocity.y);
						lines.append(position3);

						int bounces = 0;
						if (position.x > scale.screenWidth - scale.fromWall + scale.width / 2.0) {
							bounces = 0;
							float t = ((scale.screenWidth - (scale.fromWall + scale.width / 2.0)) - lines[0].position.x) / (lines[1].position.x - lines[0].position.x);
							float posX = lines[0].position.x + t * (lines[1].position.x - lines[0].position.x);
							targetR = lines[0].position.y + t * (lines[1].position.y - lines[0].position.y) + vary();
						}
						else if (position2.x > scale.screenWidth - scale.fromWall + scale.width / 2.0) {
							bounces = 1;
							float t = ((scale.screenWidth - (scale.fromWall + scale.width / 2.0)) - lines[1].position.x) / (lines[2].position.x - lines[1].position.x);
							float posX = lines[1].position.x + t * (lines[2].position.x - lines[1].position.x);
							targetR = lines[1].position.y + t * (lines[2].position.y - lines[1].position.y) + vary();
						}
						else if (position3.x > scale.screenWidth - scale.fromWall + scale.width / 2.0) {
							bounces = 2;
							float t = ((scale.screenWidth - (scale.fromWall + scale.width / 2.0)) - lines[2].position.x) / (lines[3].position.x - lines[2].position.x);
							float posX = lines[2].position.x + t * (lines[3].position.x - lines[2].position.x);
							targetR = lines[2].position.y + t * (lines[3].position.y - lines[2].position.y) + vary();
						}
						else {
							//std::cout << "error!" << std::endl;
						}
						//std::cout << "bounces= " << bounces << std::endl;
					}
					lines[0].color = sf::Color::White;	
					lines[1].color = sf::Color::White;
					lines[2].color = sf::Color::White;
					
					if (strat == STRAT_RESET) {
						targetL = scale.screenHeight / 2.0f + vary();
					}
					else if (strat == STRAT_FOLLOW) {
						targetL = targetR;
					}

				}
			}
			if (scale.debug) {
				win->draw(lines);
				win->draw(targetLineRight);
			}
		}
		else if (puck->startRight) {	//right paddle impacted
			initFromLeft = false;
			if (!initFromRight) {
				initFromRight = true;
				lines.clear();
				lines.append(puck->shape.getPosition());

				if (abs(puck->velocity.y) < err) {	
					sf::Vector2f position(puck->shape.getPosition().x + 10000 * puck->velocity.x, puck->shape.getPosition().y);
					lines.append(position);
					lines[0].color = sf::Color::White;

					float t = ((scale.fromWall + scale.width / 2.0) - lines[0].position.x) / (lines[1].position.x - lines[0].position.x);
					float posX = lines[0].position.x + t * (lines[1].position.x - lines[0].position.x);
					targetL = lines[0].position.y + t * (lines[1].position.y - lines[0].position.y) + vary();

					if (strat == STRAT_RESET) {
						targetR = scale.screenHeight / 2.0f + vary();
					}
				}
				else {
					if (puck->velocity.y < 0) {			
						
						float s;
						float t;

						t = puck->shape.getPosition().y / puck->velocity.y;
						s = abs(t) - scale.radius;
						sf::Vector2f position(puck->shape.getPosition().x + s * puck->velocity.x, puck->shape.getPosition().y + s * puck->velocity.y);
						lines.append(position);
						

						t = -scale.screenHeight / puck->velocity.y;
						s = t - scale.radius * 2;
						sf::Vector2f position2(position.x + s * puck->velocity.x, +position.y - s * puck->velocity.y);
						lines.append(position2);

						t = 10000;
						s = t;
						sf::Vector2f position3(position2.x + s * puck->velocity.x, +position2.y + s * puck->velocity.y);
						lines.append(position3);

						int bounces = 0;
						if (position.x < scale.fromWall + scale.width / 2.0) {
							bounces = 0;
							float t = ((scale.fromWall + scale.width / 2.0) - lines[0].position.x) / (lines[1].position.x - lines[0].position.x);
							float posX = lines[0].position.x + t * (lines[1].position.x - lines[0].position.x);
							targetL = lines[0].position.y + t * (lines[1].position.y - lines[0].position.y) + vary();
						}
						else if (position2.x < scale.fromWall + scale.width / 2.0) {
							bounces = 1;
							float t = ((scale.fromWall + scale.width / 2.0) - lines[1].position.x) / (lines[2].position.x - lines[1].position.x);
							float posX = lines[1].position.x + t * (lines[2].position.x - lines[1].position.x);
							targetL = lines[1].position.y + t * (lines[2].position.y - lines[1].position.y) + vary();
						}
						else if (position3.x < scale.fromWall + scale.width / 2.0) {
							bounces = 2;
							float t = ((scale.fromWall + scale.width / 2.0) - lines[2].position.x) / (lines[3].position.x - lines[2].position.x);
							float posX = lines[2].position.x + t * (lines[3].position.x - lines[2].position.x);
							targetL = lines[2].position.y + t * (lines[3].position.y - lines[2].position.y) + vary();
						}
						else {
							//std::cout << "error!" << std::endl;
						}
						//std::cout << "bounces= " << bounces << std::endl;

					}
					else {							
						float s;
						float t;

						t = (scale.screenHeight - puck->shape.getPosition().y) / puck->velocity.y;
						s = t - scale.radius;
						sf::Vector2f position(puck->shape.getPosition().x + s * puck->velocity.x, puck->shape.getPosition().y + s * puck->velocity.y);
						lines.append(position);

						if (position.x)

							t = scale.screenHeight / puck->velocity.y;
						s = t - scale.radius * 2;
						sf::Vector2f position2(position.x + s * puck->velocity.x, +position.y - s * puck->velocity.y);
						lines.append(position2);

						t = 10000;
						s = t;
						sf::Vector2f position3(position2.x + s * puck->velocity.x, +position2.y + s * puck->velocity.y);
						lines.append(position3);

						int bounces = 0;
						if (position.x < scale.fromWall + scale.width / 2.0) {
							bounces = 0;
							float t = ((scale.fromWall + scale.width / 2.0) - lines[0].position.x) / (lines[1].position.x - lines[0].position.x);
							float posX = lines[0].position.x + t * (lines[1].position.x - lines[0].position.x);
							targetL = lines[0].position.y + t * (lines[1].position.y - lines[0].position.y) + vary();
						}
						else if (position2.x < scale.fromWall + scale.width / 2.0) {
							bounces = 1;
							float t = ((scale.fromWall + scale.width / 2.0) - lines[1].position.x) / (lines[2].position.x - lines[1].position.x);
							float posX = lines[1].position.x + t * (lines[2].position.x - lines[1].position.x);
							targetL = lines[1].position.y + t * (lines[2].position.y - lines[1].position.y) + vary();
						}
						else if (position3.x < scale.fromWall + scale.width / 2.0) {
							bounces = 2;
							float t = ((scale.fromWall + scale.width / 2.0) - lines[2].position.x) / (lines[3].position.x - lines[2].position.x);
							float posX = lines[2].position.x + t * (lines[3].position.x - lines[2].position.x);
							targetL = lines[2].position.y + t * (lines[3].position.y - lines[2].position.y) + vary();
						}
						else {
							//std::cout << "error!" << std::endl;
						}
						//std::cout << "bounces= " << bounces << std::endl;
					}
					lines[0].color = sf::Color::White;
					lines[1].color = sf::Color::White;
					lines[2].color = sf::Color::White;

					if (strat == STRAT_RESET) {
						targetR = scale.screenHeight / 2.0f + vary();
					}
					else if (strat == STRAT_FOLLOW) {
						targetR = targetL;
					}
				}	
			}
			if (scale.debug) {
				win->draw(lines);
				win->draw(targetLineLeft);
			}
		}
	}
};

#endif
