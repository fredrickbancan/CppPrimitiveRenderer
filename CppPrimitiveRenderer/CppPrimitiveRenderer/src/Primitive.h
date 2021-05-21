#pragma once

/*Simple struct which allows the user application to store generic primitives.*/
struct Primitive
{
	int type;
	float posX;
	float posY;
	float posZ;
	float sizeX;
	float sizeY;
	float sizeZ;
	float colorR;
	float colorG;
	float colorB;
	float colorA;
};