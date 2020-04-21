#version 450

in vec2 texCoord;

out vec4 outputColour;

uniform sampler2D depthTexture;

void main()
{

		float test = texture(depthTexture, texCoord).r;
		outputColour = vec4(test, test, test, 1.0f);

}