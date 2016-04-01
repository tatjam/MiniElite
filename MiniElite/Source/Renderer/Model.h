#pragma once
#include "SFML/OpenGL.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
//A not so simple class for handling models!
//To be expanded to support shaders!

enum Error
{
	SUCCESS,            //When nothing went wrong
	NO_VERTICES,         //When no vertices are stored
	VERTICES_NO_TRIPLET, //When vertices % 3 != 0
	COLORS_NO_TRIPLET,   //When color % 3 != 0
};

class Model
{
public:
	
	//Do not dare to modify these without use of the helper
	//functions (Feel free actually)
	sf::Vector3f position = sf::Vector3f(0, 0, 0);
	sf::Vector3f rotation = sf::Vector3f(0, 0, 0);
	sf::Vector3f scale = sf::Vector3f(0, 0, 0);
	sf::Vector3f offset = sf::Vector3f(0, 0, 0);
	//Vertex list!
	//Stored as triplets, to represent glVertex3f
	std::vector<sf::Vector3f> vertices = std::vector<sf::Vector3f>();

	//Color list!
	//Stored as triplets, to represent glColor3f
	std::vector<sf::Vector3f> colors = std::vector<sf::Vector3f>();


	void addVertex(float x, float y, float z);
	void addVertex(sf::Vector3f vertex);

	void move(float x, float y, float z);
	void rotate(float x, float y, float z);

	void move(sf::Vector3f t);
	void rotate(sf::Vector3f t);


	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setScale(float x, float y, float z);

	void setPosition(sf::Vector3f t);
	void setRotation(sf::Vector3f t);
	void setScale(sf::Vector3f t);


	Error render();

	Model();
	~Model();
};

