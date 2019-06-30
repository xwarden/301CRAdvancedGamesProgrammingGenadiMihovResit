#include "Ball.h"
static const float scale = 30.0f;


Ball::Ball(short group, b2World* world, float X, float Y, float mysizeX, float mysizeY)
{
	//
	positionX = X;
	positionY = Y;
	World = world;
	sizeX = mysizeX / 2;
	sizeY = mysizeX / 2;
	//
	b2BodyDef bodyDefinition;
	bodyDefinition.type = b2_dynamicBody;
	bodyDefinition.position.Set(positionX / scale, positionY / scale);
	bodyDefinition.fixedRotation = true;
	body = World->CreateBody(&bodyDefinition);
	body->SetUserData(this);
	b2CircleShape sphereShape;
	sphereShape.m_p.Set(0, 0);
	sphereShape.m_radius = 2;
}

sf::Sprite Ball::drawBall(std::string TextureLoc)
{
	//
	texture.loadFromFile(TextureLoc);
	sprite.setTexture(texture);
	sprite.setOrigin(sizeX, sizeY);
	sprite.setPosition(scale * body->GetPosition().x, scale *body->GetPosition().y);
	sprite.setRotation(body->GetAngle() * 180 / b2_pi);
	return sprite;
};


void Ball::setVelocity(float velocityX, float velocityY)
{
	//
	body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, velocityY));
};

void Ball::receivePacket(float x, float y, Ball* ball)
{
	//
	ball->setPosition(x, y);
};


Ball::~Ball()
{
}
