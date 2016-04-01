#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/OpenGL.hpp"
#include <iostream>
#include <gl/GLU.h>
#include "Renderer/Model.h"

#define SCALE 6
#define SIDE 64
int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(SIDE * SCALE, SIDE * SCALE), "SFML window");
	
	sf::RenderTexture* texture = new sf::RenderTexture();

	texture->create(SIDE, SIDE, true);

	texture->setActive();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glViewport(0, 0, SIDE, SIDE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(52.0f, 1.f, 0.1f, 100.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	window.setActive();

	float angleAdd = 0;

	float xRot = 0.0f;
	float yRot = 0.0f;
	float zRot = 0.0f;

	float xMov = 0.0f;
	float yMov = 0.0f;
	float zMov = 0.0f;

	Model triangle = Model();
	triangle.position.x += 0.01f;
	triangle.addVertex(0, 0, -2);
	triangle.addVertex(0, 1, -2);
	triangle.addVertex(1, 0, -2);

	triangle.addVertex(1, 0, -2);
	triangle.addVertex(0, 0, -2);
	triangle.addVertex(1, 1, -2);

	triangle.offset = sf::Vector3f(0.5f, 0.4f, -2.f);

	// Start the game loop
	while (window.isOpen())
	{


		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window : exit
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Camera rotation:
		triangle.position.x += 0.0001f;
		triangle.rotation.y += 0.1f;
		triangle.rotation.z += 0.01f;
		triangle.rotation.x += 0.1f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			xRot -= 0.05f;
		}

		//Hello!

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			xRot += 0.05f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			yRot -= 0.05f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			yRot += 0.05f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		{
			zRot -= 0.05f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		{
			zRot += 0.05f;
		}



		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			zMov += 0.001f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			zMov -= 0.001f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			xMov -= 0.001f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			xMov += 0.001f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
		{
			yMov -= 0.001f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
		{
			yMov += 0.001f;
		}

		// Clear screen
		//window.clear();

		texture->setActive(true);

		glClear(GL_DEPTH_BUFFER_BIT); //!!!
		texture->clear(sf::Color::Black);

		//GL drawing to texture here

		//Camera translations:
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();



		glRotatef(xRot, 1, 0, 0);
		glRotatef(yRot, 0, 1, 0);
		glRotatef(zRot, 0, 0, 1);

		glTranslatef(xMov, yMov, zMov);

		

		//Model drawing


		triangle.render();

		//Front face


		/*
		glBegin(GL_POLYGON);
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(0, 0, -5.f);
			glVertex3f(1, 0, -5.f);
			glVertex3f(1, 1, -5.f);
			glVertex3f(0, 1, -5.f);
		glEnd();

		//Back face
		glBegin(GL_POLYGON);
			glColor3f(0.2f, 0.2f, 0.2f);
			glVertex3f(0, 0, -6.f);
			glVertex3f(1, 0, -6.f);
			glVertex3f(1, 1, -6.f);
			glVertex3f(0, 1, -6.f);
		glEnd();

		//Left face
		glBegin(GL_POLYGON);
			glColor3f(0.7f, 0.7f, 0.7f);
			glVertex3f(0, 0, -5.f);
			glVertex3f(0, 0, -6.f);
			glVertex3f(0, 1, -6.f);
			glVertex3f(0, 1, -5.f);
		glEnd();

		//Right face
		glBegin(GL_POLYGON);
			glColor3f(0.2f, 0.2f, 0.2f);
			glVertex3f(1, 0, -5.f);
			glVertex3f(1, 0, -6.f);
			glVertex3f(1, 1, -6.f);
			glVertex3f(1, 1, -5.f);
		glEnd();

		//Top face
		glBegin(GL_POLYGON);
			glColor3f(0.8f, 0.8f, 0.8f);
			glVertex3f(0, 1, -5.f);
			glVertex3f(1, 1, -5.f);
			glVertex3f(1, 1, -6.f);
			glVertex3f(0, 1, -6.f);
		glEnd();

		//Bottom face
		glBegin(GL_POLYGON);
			glColor3f(0.2f, 0.2f, 0.2f);
			glVertex3f(0, 0, -5.f);
			glVertex3f(1, 0, -5.f);
			glVertex3f(1, 0, -6.f);
			glVertex3f(0, 0, -6.f);
		glEnd();
		*/



		window.setActive(true);

		window.pushGLStates();

		texture->display();

		//window.setActive(true);
		// Update the window
		sf::Texture outTex = texture->getTexture();
		outTex.setSmooth(false);
		sf::Sprite s = sf::Sprite(outTex);
		s.setScale(SCALE, SCALE);
		window.draw(s);
		window.display();

		window.popGLStates();

		angleAdd += 0.01f;
	}
	return EXIT_SUCCESS;

}