// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

#include "Shader.h"
#include "Vertice.h"
#include "Carro.h"

#include "Modelo.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

using namespace std;

Shader *shader;
GLuint posicionID;
GLuint colorID;
GLuint transformacionesID;
GLuint vistaID;
GLuint modeloID;
GLuint proyeccionID;


Carro *carro;

//Declaramos apuntador de ventana
GLFWwindow *window;
GLfloat ancho = 1024.0f;
GLfloat alto = 768.0f;


void establecerVista() {
	vista = lookAt(
		vec3(0.0f, 20.0f, 10.0f), //Posición de la camara
		vec3(0.0f, 0.0f, 0.0f), //Posición del objetivo
		vec3(0.0f, 1.0f, 0.0f) //Vector hacia arriba
	);
}

void establecerProyeccion() {
	proyeccion = perspective(
		90.0f, //Campo de vision (FoV)
		ancho / alto, //relacion de aspecto (Aspecto Ratio)
		0.1f, //Near Clipping (Desde donde renderea)
		150.0f //Far clipping (Hasta donde renderea)
	);
}

void dibujar() {
	carro->(GL_QUADS);
}

void actualizar() {

}

int main()
{


	//Si no se pudo iniciar glfw
	//terminamos ejcución
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	//Si se pudo iniciar GLFW
	//entonces inicializamos la ventana
	window =
		glfwCreateWindow(1024, 768, "Ventana",
			NULL, NULL);
	//Si no podemos iniciar la ventana
	//Entonces terminamos ejecucion
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//Establecemos el contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido  el contexto
	//Activamos funciones modernas
	glewExperimental = true;
	GLenum errorGlew = glewInit();
	if (errorGlew != GLEW_OK) {
		cout <<
			glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL =
		glGetString(GL_VERSION);
	cout << "Version OpenGL: "
		<< versionGL;


	const char *rutaVertex =
		"VertexShader.shader";
	const char *rutaFragment =
		"FragmentShader.shader";

	shader = new Shader(rutaVertex, rutaFragment);

	//Mapeo de atributos
	posicionID =
		glGetAttribLocation(shader->getID(), "posicion");
	colorID =
		glGetAttribLocation(shader->getID(), "color");
	modeloID =
		glGetUniformLocation(shader->getID(), "modelo");
	vistaID =
		glGetUniformLocation(shader->getID(), "vista");
	proyeccionID =
		glGetUniformLocation(shader->getID(), "proyeccion");

	//Desenlazar el shader
	shader->desenlazar();
	establecerVista();
	establecerProyeccion();

	//Inicializar modelo y Establecer shader
	carro = new Carro();
	carro->vista = vista;
	carro->proyeccion = proyeccion;
	carro->shader = shader;
	carro->inicializarVertexArray(posicionID, colorID, modeloID, vistaID, proyeccionID);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);


	//Inicializar vertex array
	triangulo->inicializarVertexArray(posicionID,
		colorID, transformacionesID);

	cuadrado->shader = shader;
	cuadrado->inicializarVertexArray(posicionID,
		colorID, transformacionesID);

	//Ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Esablecer region de dibujo
		glViewport(0, 0, 1024, 768);
		//Establece el color de borrado
		glClearColor(1, 0.2, 0.5, 1);
		//Borramos
		glClear(
			GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		dibujar();
		actualizar();

		//Cambiar los buffers
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

