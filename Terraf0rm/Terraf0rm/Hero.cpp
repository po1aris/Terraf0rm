#include "Hero.h"

Hero::Hero()
{

}
void Hero::InitHero(ALLEGRO_BITMAP *image, int Height, int Width)
{
	setHealth(50);
	setMana(100);

	Hero::image = image;

	GameObject::init((Width/2),(Height/2), 5, 5, 0, 0, 10, 10);

	setID(PLAYER);
	setSuitID(NonSuit);

	setAlive(true);

	setDirection(DOWN);

	mLives = 3;
	maxFrame = 3;
	curFrame = 0;
	frameWidth = 30;
	frameHeight = 33;
	animationColumns = 3;
	animationRow = 4;

	if (image != NULL)
		Hero::image = image;

}
void Hero::Update()
{
	CharacterSprite::Update();
}
void Hero::Render(int heroType)
{
	CharacterSprite::Render();
	int fx = (curFrame % animationColumns * frameWidth);
	int fy = animationRow * frameHeight;

	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);
}
void Hero::Destroy()
{
	GameObject::Destroy();
}
void Hero::Collide(int objectID)
{
	if(objectID == BULLET)
		loseHealth();
	else if (objectID == ENEMY)
		loseHealth();
}
void Hero::moveUp()
{
	animationRow = 0;
	dirY = -1;
}
void Hero::moveDown()
{
	animationRow = 3;
	dirY = 1;
}
void Hero::moveLeft()
{
	animationRow = 1;
	dirX = -1;
}
void Hero::moveRight()
{
	animationRow = 2;
	dirX = 1;
}
Hero::~Hero()
{

}