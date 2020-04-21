#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 3) in vec2 inTexCoord;

out vec2 texCoord;

void main()
{
	gl_Position = vec4(inPosition.xy, -1.0f, 1.0f);
	texCoord = inTexCoord;
}