#include "Ball.h"
#include "Player.h"
static const float scale = 30.0f;


Ball::Ball(short group, b2World* world, float X, float Y, float mysizeX, float mysizeY)
{
	//body parameters
	positionX = X;
	positionY = Y;
	World = world;
	sizeX = mysizeX / 2;
	sizeY = mysizeY / 2;
	//create the body
	b2BodyDef bodyDefinition;
	bodyDefinition.type = b2_dynamicBody;
	bodyDefinition.position.Set(positionX / scale, positionY / scale);
	bodyDefinition.fixedRotation = true;
	body = World->CreateBody(&bodyDefinition);
	body->SetUserData(this);
	b2CircleShape sphereShape;
	sphereShape.m_p.Set(0, 0);
	sphereShape.m_radius = sizeX / scale;
	//defining the fixture for the body
	b2FixtureDef fixtureDefinition;
	fixtureDefinition.shape = &sphereShape;
	fixtureDefinition.density = 1.0f;
	fixtureDefinition.friction = 0.0f;
	fixtureDefinition.restitution = 1.0f;
	body->CreateFixture(&fixtureDefinition);
}

sf::Sprite Ball::drawBall(std::string TextureLoc)
{
	//texture the player using a sprite
	texture.loadFromFile(TextureLoc);
	sprite.setTexture(texture);
	sprite.setOrigin(sizeX, sizeY);
	sprite.setPosition(scale * body->GetPosition().x, scale *body->GetPosition().y);
	sprite.setRotation(body->GetAngle() * 180 / b2_pi);
	return sprite;
};



void Ball::setVelocity(float velocityX, float velocityY)
{
	//set body velocity on Y
	body->SetLinearVelocity(b2Vec2(velocityX, velocityY));
};

bool Ball::startContact(Collidable* col)
{
		Player* collider = dynamic_cast<Player*>(col);
		if (collider)
		{
			b2Vec2 currentPosition = body->GetPosition();
			b2Vec2 playerPosition = collider->getBody()->GetPosition();
			b2Vec2 dir = (currentPosition - playerPosition);
			dir.Normalize();
			dir *= body->GetLinearVelocity().Length() + 0.1f;
			body->SetLinearVelocity(dir);
		}

	return true;
};

void Ball::receivePacket(float x, float y, Ball* ball)
{
	ball->setPosition(x, y);
};


Ball::~Ball()
{
}
