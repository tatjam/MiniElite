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
		glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		glTranslatef(location[0], location[1], location[2]);
		glRotatef(rotation[0], 1, 0, 0);
		glRotatef(rotation[1], 0, 1, 0);
		glRotatef(rotation[2], 0, 0, 1);
		glScalef(scale[0], scale[1], scale[2]);
		//Do actual rendering!
		glBegin(GL_TRIANGLES);
		for (unsigned int i = 0; i < vertices.size(); i++)
		{
			glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		}
		glEnd();
		glPopMatrix();
		//Done!
		return Error::SUCCESS;
	}
}


Model::Model()
{
}


Model::~Model()
{
}
