#version 450

/*We care only for the position for the Quad and the texture coordinates at the 4 vertices*/
layout(location = 0) in vec3 inPosition;
layout(location = 3) in vec2 inTexCoord;

/*We pass the texture coordinate to the fragment shader as that is where sampling happens*/
out vec2 texCoord;

void main()
{
	/*Notes: Z-position is set to -1 as we want it to be visible and staying in front of the camera*/
	gl_Position = vec4(inPosition.xy, -1.0f, 1.0f);

	texCoord = inTexCoord;
}