#version 450

/*We only need the position, and the texture coordinate for the quad*/
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTextureCoordinate;

out vec2 textureCoordinate;

void main()
{

	/*Ouput a clip space position*/
	gl_Position = vec4(inPosition.xy, -1.0f, 1.0f); // We want the quad to be visible, so we provide it a negative value, i.e. it stays in front of our field of view

	textureCoordinate = inTextureCoordinate;
}
