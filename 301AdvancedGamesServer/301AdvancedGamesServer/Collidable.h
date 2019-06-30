#pragma once
class Collidable
{
public:
	virtual bool startContact(Collidable* col);
	virtual bool endContact(Collidable* col);
protected:
	bool isColliding;
};

