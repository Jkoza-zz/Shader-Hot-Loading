#include <GLSLProgram.h>
#include <SDL\SDL.h>
#include <GL/glew.h>
#include <iostream>
SDL_Window* _window;
GLSLProgram _Program;
GLuint _vboID = 0;
bool exiting = false;
void initShaders() {
	_Program.compileShaders("Shaders/vertex.glsl", "Shaders/fragment.glsl");
	_Program.addAttribute("vertexPosition");
	_Program.linkShaders();
}
void draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glGenBuffers(1, &_vboID);
	float vertexData[12];
	float height = 1.0f;
	float width = 1.0f;
	float x = -1.0f;
	float y = -1.0f;
	//First Triangle
	vertexData[0] = x + width;
	vertexData[1] = y + height;

	vertexData[2] = x;
	vertexData[3] = y + height;

	vertexData[4] = x;
	vertexData[5] = y;

	//Second Triangle
	vertexData[6] = x;
	vertexData[7] = y;

	vertexData[8] = x + width;
	vertexData[9] = y;

	vertexData[10] = x + width;
	vertexData[11] = y + height;
	_Program.use();

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	_Program.unuse();
	SDL_GL_SwapWindow(_window);
}
void processInput() {
	SDL_Event evnt;
	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			exiting = true;
			break;
		case SDL_QUIT:
			exiting = true;
			break;
		}
	}
}
void initSystems() {
	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_OPENGL);
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	GLenum err = glewInit();
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	initShaders();
}
int main(int argc, char** argv) 
{
	initSystems();
	draw();
	while(!exiting){
		processInput();
	}
	return 0;
}
