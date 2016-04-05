#include <GL/glew.h>
#include <iostream>
#include "Renderer/Model.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Renderer/GLShader.h"
#include "Renderer/GLProgram.h"

#define SCALE 10
#define SIDE 64
int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(SIDE * SCALE, SIDE * SCALE), "SFML window");
	
	sf::RenderTexture* texture = new sf::RenderTexture();

	window.setFramerateLimit(60);

	sf::Sprite s = sf::Sprite();
	s.setScale(SCALE, SCALE);

	texture->create(SIDE, SIDE, true);

	texture->setActive();

	//ENABLING HAS TO GO HERE
	//-------------------------------------------------
	
	glEnable(GL_LIGHTING);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	GLfloat light0Position[] = { 1, 1, 1, 0}; // Position
	glLightfv(GL_LIGHT0, GL_POSITION, light0Position);

	glEnable(GL_LIGHT0);
	glShadeModel(GL_FLAT);

	//Sometimes after everything is ready glEnable does nothing

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glViewport(0, 0, SIDE, SIDE);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(53.0f, 1.f, 0.1f, 100.f);
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
	/*triangle.position.x += 0.01f;
	triangle.addVertex(0, 0, -2);
	triangle.addVertex(0, 1, -2);
	triangle.addVertex(1, 0, -2);

	triangle.addVertex(1, 0, -2);
	triangle.addVertex(0, 0, -2);
	triangle.addVertex(1, 1, -2);*/
	
	triangle.offset = sf::Vector3f(0.f, 0.f, 0.f);

	triangle.loadFile("res/ships/viper.obj", "res/ships/viper.mtl");
	
	
	
	Model test = Model();

	test.loadFile("res/objects/asteroid2.obj", "res/objects/asteroid2.mtl");
	

	Model a = Model();

	//a.loadFile("res/ships/viper.obj", "res/ships/viper.mtl");

	
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW is not willing to work, the program will now quit." << std::endl;
		std::cin.get();
		return 1;
	}


	
	//HUD
	sf::Texture hudUnderlayTex = sf::Texture();
	hudUnderlayTex.loadFromFile("res/textures/hud.png");

	sf::Sprite hudUnderlay = sf::Sprite(hudUnderlayTex);
	
	// Start the game loop
	while (window.isOpen())
	{
		//triangle.doLight(lightPosition, 1.0f, MixMode::ADD);

		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window : exit
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Camera rotation:
		//triangle.position.x += 0.001f;
		//triangle.position.y += 0.001f;
		//triangle.rotation.y += 0.02f;
		//triangle.rotation.z += 0.01f;
		//triangle.rotation.x += 0.1f;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			xRot -= 0.35f;
		}

		//Hello!

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			xRot += 0.35f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			yRot -= 0.35f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			yRot += 0.35f;
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
			{
				zMov += 0.035f;
			}
			else
			{
				zMov += 0.005f;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
			{
				zMov -= 0.035f;
			}
			else
			{
				zMov -= 0.005f;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
			{
				xMov -= 0.035f;
			}
			else
			{
				xMov -= 0.005f;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
			{
				xMov += 0.03f;
			}
			else
			{
				xMov += 0.005f;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
			{
				yMov -= 0.035f;
			}
			else
			{
				yMov -= 0.005f;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
			{
				yMov += 0.035f;
			}
			else
			{
				yMov += 0.005f;
			}
		}

		// Clear screen
		//window.clear();

		texture->setActive(true);

		//We have to reposition the light each frame, as it "moves with the camera"

		glLightfv(GL_LIGHT0, GL_POSITION, light0Position);

		glClear(GL_DEPTH_BUFFER_BIT); //!!!
		texture->clear(sf::Color(10, 8, 35));

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

		test.render();

		window.setActive(true);

		window.pushGLStates();
		texture->pushGLStates();
		texture->draw(hudUnderlay);

		texture->display();

		//window.setActive(true);
		// Update the window
		sf::Texture outTex = texture->getTexture();
		outTex.setSmooth(false);
		s.setTexture(outTex);
		window.draw(s);
		window.display();

		window.popGLStates();
		texture->popGLStates();
		angleAdd += 0.01f;

		

	}
	return EXIT_SUCCESS;

}