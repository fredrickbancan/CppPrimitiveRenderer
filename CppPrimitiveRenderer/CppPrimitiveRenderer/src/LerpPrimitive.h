#pragma once

/*Simple struct which allows the user application to store generic linearly interpolated primitives.*/
struct LerpPrimitive
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
	float prevPosX;
	float prevPosY;
	float prevPosZ;
	float prevSizeX;
	float prevSizeY;
	float prevSizeZ;
	float prevColorR;
	float prevColorG;
	float prevColorB;
	float prevcolorA;
};