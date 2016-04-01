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
	sf::Vector3f location;
	sf::Vector3f rotation;
	sf::Vector3f scale;
	sf::Vector3f offset;
	//Vertex list!
	//Stored as triplets, to represent glVertex3f
	std::vector<sf::Vector3f> vertices = std::vector<sf::Vector3f>();

	//Color list!
	//Stored as triplets, to represent glColor3f
	std::vector<sf::Vector3f> colors = std::vector<sf::Vector3f>();


	void addVertex(float x, float y, float z);
	void addVertex(sf::Vector3f vertex);

	Error render();

	Model();
	~Model();
};

