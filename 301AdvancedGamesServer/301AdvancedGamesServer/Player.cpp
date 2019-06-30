#include "Player.h"
static const float scale = 30.0f;


Player::Player(short group, b2World* world, float X, float Y, float mysizeX, float mysizeY)
{
	//
	positionX = X;
	positionY = Y;
	World = world;
	sizeX = mysizeX / 2;
	sizeY = mysizeY / 2;
	//
	b2BodyDef bodyDefenition;
	bodyDefenition.type = b2_kinematicBody;
	bodyDefenition.position.Set(positionX / scale, positionY / scale);
	bodyDefenition.fixedRotation = true;
	body = World->CreateBody(&bodyDefenition);
	body->SetUserData(this);
	b2PolygonShape boxShape;
	boxShape.SetAsBox(sizeX / scale, sizeY / scale);
	//
	b2FixtureDef fixtureDefenition;
	fixtureDefenition.filter.groupIndex = group;
	fixtureDefenition.shape = &boxShape;
	fixtureDefenition.density = 1.0f;
	fixtureDefenition.friction = 0.0f;
	body->CreateFixture(&fixtureDefenition);
}

sf::Sprite Player::drawPlayer(std::string TextureLoc)
{
	
	//
	texture.loadFromFile(TextureLoc);
	sprite.setTexture(texture);
	sprite.setOrigin(sizeX, sizeY);
	sprite.setPosition(scale * body->GetPosition().x, scale *body->GetPosition().y);
	sprite.setRotation(body->GetAngle() * 180 / b2_pi);
	return sprite;
};


void Player::setVelocity(float velocityX, float velocityY)
{
	//
	body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, velocityY));
};

void Player::setPosition(float x, float y) 
{
	//
	body->SetTransform(b2Vec2(x / scale, y / scale), body->GetAngle()); 
};

float Player::fetchPositionX() 
{ 
	//
	return body->GetPosition().x * scale;
};
float Player::fetchPositionY()
{ 
	//
	return body->GetPosition().y * scale; 
};


void Player::receivePacket(float x, float y, Player* player)
{
	//
	player->setPosition(x, y);
};


Player::~Player()
{
}
