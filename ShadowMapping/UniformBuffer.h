#pragma once

#include<QMatrix4x4>
#include<QVector3D>

/*The struct contains data for our OpenGL uniform Buffer*/
struct UniformBuffer
{	
	/*The first two variables are the model and the result of combining the matrices for the view and projection*/
	float model[16];
	float viewProjection[16];

	/*This matrix takes the fragment from world space to light space. I.e. as seen from the light's view point*/
	float lightSpaceMatrix[16];

	/*A vector representing the direction towards the light source. We only have one light source, hence we only need one direction*/
	float toLightDirection[4]; 
};

/*
Helper functions which will copy the data into the Uniform Buffer structure. The reason I did this is for the compiler to warn me, when 
attempting to do silly things, such as add less data, or more data than I should.
*/

void copyMatrix4x4ToFloatArray(const QMatrix4x4& source, float destination[16]);
void copyVector4ToFloatArray(const QVector4D& source, float destination[4]);