#version 130

in vec2 vertexPosition;
in vec4 vertextColor;
in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

uniform mat4 mvp;

void main() {
	gl_Position.xy = (mvp * vec4(vertexPosition, 0.0, 1.0)).xy;
	gl_Position.z = 0.0;
	gl_Position.w = 1.0;
	
	fragmentPosition = vertexPosition;
	fragmentColor = vertextColor;
	fragmentUV = vertexUV;
}