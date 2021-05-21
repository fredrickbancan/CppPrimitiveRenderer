#pragma once
struct CubeFace
{
	static const int sizeBytes = 44;
	float posX, posY, posZ;
	float sizeX, sizeY, sizeZ;
	float colorR, colorG, colorB, colorA;
	float faceDir;
};