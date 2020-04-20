#version 450

in vec2 textureCoordinate;

out vec3 outColour;

/*Sampler object which we use for sampling a texture*/
uniform sampler2D depthTexture;

void main()
{

	/*Sample the shadow map for the depth value located and xy*/
	/* .r gives us whatever we have in the Red channel. Since we have a single depth channel being sampled, this value will be stored in the Red channel*/
	const float depthValue = texture(depthTexture, textureCoordinate).r; 

	/*Setting the channels using the same value would give us a depth map similar to greyscale image*/
	outColour = vec3(depthValue, depthValue, depthValue);
}