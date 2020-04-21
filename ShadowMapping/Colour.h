#pragma once

/*Represents an RGB colour structure*/
struct Colour
{
	float m_redChannel;
	float m_greenChannel;
	float m_blueChannel;

	Colour();
	Colour(float r, float g, float b);
};