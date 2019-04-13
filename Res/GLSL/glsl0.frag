#version 330 core

in vec4 outColor;
in vec2 outTexCoord;

uniform sampler2D ourTexture;

void main()
{
	//gl_FragColor = texture(ourTexture,outTexCoord);
	gl_FragColor = outColor;
}

