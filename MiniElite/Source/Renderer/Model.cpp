#include "Model.h"

Error Model::render()
{
	bool doColor = true;
	if (colors.size() <= 0)
	{
		doColor = false;
	}

	if (vertices.size() <= 0)
	{
		return Error::NO_VERTICES;
	}
	else
	{
		if (vertices.size() % 3 != 0)
		{
			return Error::VERTICES_NO_TRIPLET;
		}
		
		if (doColor && colors.size() % 3 != 0)
		{
			return Error::COLORS_NO_TRIPLET;
		}

		//Translation, scale and rotation:
		/*
		glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		glTranslatef(location.x, location.y, location.z);
		glRotatef(rotation.x, 1, 0, 0);
		glRotatef(rotation.y, 0, 1, 0);
		glRotatef(rotation.z, 0, 0, 1);
		glScalef(scale.x, scale.y, scale.z);*/
		//Do actual rendering!


		glPushMatrix();
		glTranslatef(offset.x, offset.y, offset.z);
		glTranslatef(location.x, location.y, location.z);

		glRotatef(rotation.x, 1, 0, 0);
		glRotatef(rotation.y, 0, 1, 0);
		glRotatef(rotation.z, 0, 0, 1);

		glTranslatef(-offset.x, -offset.y, -offset.z);
		glBegin(GL_TRIANGLES);
		for (unsigned int i = 0; i < vertices.size(); i++)
		{
			glColor3f(1.f, 1.f, 1.f);
			glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		}
		glEnd();


		glBegin(GL_POINTS);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(offset.x, offset.y, offset.z);
		glEnd();

		glPopMatrix();
		//Done!
		return Error::SUCCESS;
	}
}


void Model::addVertex(float x, float y, float z)
{
	sf::Vector3f v = sf::Vector3f(x, y, z);
	vertices.push_back(v);
}
void Model::addVertex(sf::Vector3f v)
{
	vertices.push_back(v);
}

void Model::move(float x, float y, float z)
{
	position += sf::Vector3f(x, y, z);
}

void Model::rotate(float x, float y, float z)
{
	rotation += sf::Vector3f(x, y, z);
}

void Model::move(sf::Vector3f t)
{
	position += t;
}

void Model::rotate(sf::Vector3f t)
{
	rotation += t;
}

void Model::setPosition(float x, float y, float z)
{
	position = sf::Vector3f(x, y, z);
}

void Model::setRotation(float x, float y, float z)
{
	rotation = sf::Vector3f(x, y, z);
}

void Model::setScale(float x, float y, float z)
{
	scale = sf::Vector3f(x, y, z);
}


void Model::setPosition(sf::Vector3f t)
{
	position = t;
}

void Model::setRotation(sf::Vector3f t)
{
	rotation = t;
}

void Model::setScale(sf::Vector3f t)
{
	scale = t;
}


Model::Model()
{
}


Model::~Model()
{
}
