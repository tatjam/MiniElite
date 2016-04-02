#include "Model.h"
#include <iostream>


#define DISABLE_COUT true

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
		glTranslatef(position.x, position.y, position.z);

		glRotatef(rotation.x, 1, 0, 0);
		glRotatef(rotation.y, 0, 1, 0);
		glRotatef(rotation.z, 0, 0, 1);

		glTranslatef(-offset.x, -offset.y, -offset.z);
		glBegin(GL_TRIANGLES);
		for (unsigned int i = 0; i < vertices.size(); i++)
		{
			if (doColor)
			{
				glColor3f(colors[i].x, colors[i].y, colors[i].z);
			}
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

Error Model::loadFile(std::string objPath, std::string mtlPath)
{

	if (DISABLE_COUT)
	{
		std::cout.setstate(std::ios_base::failbit);
	}

	std::ifstream t(objPath);
	if (!t.good())
	{
		return Error::FILE_NOT_FOUND;
	}
	std::stringstream buffer;
	buffer << t.rdbuf();

	std::ifstream g(mtlPath);
	if (!g.good())
	{
		return Error::FILE_NOT_FOUND;
	}
	std::stringstream buffer2;
	buffer2 << g.rdbuf();

	//buffer now contains our file

	std::string obj = buffer.str();

	std::string mtl = buffer2.str();

	//.Obj file parser starts here
	//----------------------------------------------
	// Supported:
	//		- Vertex
	//		- Color (Material)
	//		- Normal
	// Other data is ignored!

	std::map<std::string, sf::Vector3f> materials = std::map<std::string, sf::Vector3f>();


	bool comment = false;

	std::string materialName = "";

	bool colorParsing = false;



	bool newMtlIn = false;
	bool matNameIn = false;
	bool inMat = false;
	bool inColor = false;

	int matNum = 0;

	std::string matNum1 = "";
	std::string matNum2 = "";
	std::string matNum3 = "";
	std::string matBuffer = "";

	int picPoint = 0;

	//First parse materialss:
	for (int i = 0; i < mtl.size(); i++)
	{
		std::cout << mtl.at(i) << std::endl;
		if (comment == true)
		{
			std::cout << "IN COMMENT!" << std::endl;
			//Wait until line break
			if (mtl.at(i) == '\n')
			{
				comment = false;
				continue;
			}



			continue;
		}
		else
		{

			//We will skip the newMtlIn until the space
			//and once we are there we will get the 
			//material name
			if (newMtlIn == true)
			{
				std::cout << "Going through newMtl..." << std::endl;
				if (mtl.at(i) == ' ')
				{
					std::cout << "Finally got to name!" << std::endl;
					newMtlIn = false;
					matNameIn = true;
					materialName = "";
					continue;
				}
				continue;
			}

			//We will store every char until the '\n' (will will not be stored)
			if (matNameIn == true)
			{
				std::cout << "Obtaining name!" << std::endl;
				if (mtl.at(i) == '\n')
				{
					matNameIn = false;
					inMat = true;
					std::cout << "Finished getting name: " << materialName << std::endl;
					continue;
				}
				materialName.push_back(mtl.at(i));
				continue;
			}

			//We will keep going until we find 'Kd'
			//then we will parse it and push the
			//color!
			if (inMat)
			{
				std::cout << "InMat, searching for Kd" << std::endl;
				if (mtl.at(i) == 'K' && mtl.at(i + 1) == 'd')
				{
					std::cout << "Found the color!" << std::endl;
					inColor = true;
					inMat = false;
					i += 2; //Place cursor at start of numbers
					std::cout << "I NOW: " << mtl.at(i) << std::endl;
					continue;
				}

				continue;
			}

			//We are already in the numbers, just get each one
			//into a string and then convert
			if (inColor)
			{

				std::cout << "In Color!" << std::endl;
				if (mtl.at(i) == ' ')
				{
					std::cout << "Found color separation!" << std::endl;
					std::cout << "MN: " << matNum << std::endl;
					std::cout << "MB: " << matBuffer << std::endl;
					matNum++;
					//Push the number

					if (matNum == 1)
					{
						matNum1 = matBuffer;
					}
					else if (matNum == 2)
					{
						matNum2 = matBuffer;
					}
					else
					{
						matNum3 = matBuffer;
					}

					matBuffer = "";

					continue;
				}

				if (mtl.at(i) == '\n')
				{
					std::cout << "Found color separation! (END)" << std::endl;
					std::cout << "MN: " << matNum << std::endl;
					std::cout << "MB: " << matBuffer << std::endl;
					matNum++;
					//Push the number

					if (matNum == 1)
					{
						matNum1 = matBuffer;
					}
					else if (matNum == 2)
					{
						matNum2 = matBuffer;
					}
					else
					{
						matNum3 = matBuffer;
					}

					matBuffer = "";

					std::cout << "Finishing new color!" << std::endl;
					//Create the material:
					float r, g, b;

					std::cout << "PR: " << matNum1 << " PG: " << matNum2 <<
						" PB: " << matNum3 << std::endl;

					try
					{
						r = std::stof(matNum1);
						g = std::stof(matNum2);
						b = std::stof(matNum3);
					}
					catch (const int exception)
					{
						throw(exception);
						return Error::FATAL_ERROR;
					}
					//Clear them:

					std::cout << "Clearing old data!" << std::endl;

					matNum1 = "";
					matNum2 = "";
					matNum3 = "";

					//Create new material:

					std::cout << "Pushing material!" << std::endl;

					materials[materialName] = sf::Vector3f(r, g, b);

					//Clear other stuff

					std::cout << "Finishing clearing" << std::endl;

					materialName = "";

					std::cout << "Finished material thing" << std::endl;

					std::cout << "R: " << r << ", G: " << g << " B: " << b << std::endl;

					//Set it to find another material:
					inMat = false;

					inColor = false;

					matNum = 0;

					continue;
				}

				std::cout << "Adding to buffer: " << mtl.at(i) << std::endl;

				matBuffer += mtl.at(i);


			}

			if (mtl.at(i) == '#')
			{
				comment = true;
				continue;
			}

			if (mtl.at(i) == 'n')
			{
				std::cout << "Starting new material!" << std::endl;
				newMtlIn = true;
				continue;
			}

			continue;
		}
	}

	//Now actually parse the .obj file
	//This is simpler!



	std::vector<sf::Vector3f> verticesIndex = std::vector<sf::Vector3f>();

	std::vector<sf::Vector3f> outVertices = std::vector<sf::Vector3f>();

	std::vector<sf::Vector3f> outNormals = std::vector<sf::Vector3f>();

	//.obj identifier (v, ...)
	std::string identifier = "NONE";

	comment = false;

	bool defining = false;

	std::string activeMaterial = "";

	sf::Vector3f vertexBuffer;
	std::string sBuffer = "";

	int point = 0;

	//The actual A/B/C (starts at 0)
	int faceIP = 0;

	int faceLength = 0;

	int faceSubP = 0;

	for (int i = 0; i < obj.size(); i++)
	{
		std::cout << obj.at(i);
		if (comment)
		{
			std::cout << "IN COMMENT!" << std::endl;

			if (obj.at(i) == '\n')
			{
				std::cout << "Ending comment" << std::endl;
				comment = false;
				continue;
			}
		}
		else
		{
			if (obj.at(i) == '#')
			{
				std::cout << "Starting comment!" << std::endl;
				comment = true;
				continue;
			}

			if (!defining)
			{
				//Find a new (valid) identifier and start definind
				if (obj.at(i) == 'v')
				{
					if (obj.at(i + 1) == 'n')
					{
						std::cout << "Starting normal" << std::endl;
						//New vertex normal
						//Skip to first number
						i += 2;
						defining = true;
						identifier = "vn";
						continue;
					}
					else
					{
						if (obj.at(i + 1) == ' ')
						{
							std::cout << "Starting vertex" << std::endl;
							//New vertex 
							//Skip to first number
							i++;
							defining = true;
							identifier = "v";
							continue;
						}
					}
				}
				else if (obj.at(i) == 'f')
				{
					if (obj.at(i + 1) == ' ')
					{
						std::cout << "Starting face" << std::endl;
						//New (complex) face:

						//Skip to first number
						i++;
						defining = true;
						identifier = "f";
						continue;
					}
				}
				else if (obj.at(i) == 'u')
				{
					if (obj.at(i + 1) == 's')
					{
						if (obj.at(i + 2) == 'e')
						{
							if (obj.at(i + 3) == 'm')
							{
								if (obj.at(i + 4) == 't')
								{
									if (obj.at(i + 5) == 'l')
									{
										materialName = "";
										//usemtl!
										std::cout << "Starting mtl" << std::endl;
										//Skip to material name:
										i += 6;
										defining = true;
										identifier = "usemtl";
										continue;
									}
								}

							}
						}
					}

				}
			}
			else
			{
				if (identifier == "usemtl")
				{
					std::cout << "useMtlDoing" << std::endl;
					//Find activeMaterial, and stop defining
					//We just need to travel until we find a [\n]

					if (obj.at(i) == '\n')
					{
						std::cout << "FINAL NAME: " << materialName << std::endl;
						defining = false;
						continue;
					}

					materialName += obj.at(i);
					continue;
				}
				else if (identifier == "v")
				{
					if (obj.at(i) == ' ')
					{
						if (point == 0)
						{
							vertexBuffer.x = stof(sBuffer);
						}
						else if (point == 1)
						{
							vertexBuffer.y = stof(sBuffer);
						}

						sBuffer = "";

						point++;
						continue;
					}
					else if (obj.at(i) == '\n')
					{
						vertexBuffer.z = stof(sBuffer);

						outVertices.push_back(vertexBuffer);

						std::cout << "Finished vertex: " << std::endl;
						std::cout << "X: " << vertexBuffer.x << " Y: " <<
							vertexBuffer.y << " Z: " << vertexBuffer.z << std::endl;
						std::cout << "outVertices is now size: " << outVertices.size();

						vertexBuffer = sf::Vector3f();
						sBuffer = "";
						point = 0;
						defining = false;
						continue;
					}

					sBuffer += obj.at(i);

					continue;

				}
				else if (identifier == "vn")
				{
					if (obj.at(i) == ' ')
					{
						if (point == 0)
						{
							vertexBuffer.x = stof(sBuffer);
						}
						else if (point == 1)
						{
							vertexBuffer.y = stof(sBuffer);
						}

						sBuffer = "";

						point++;
						continue;
					}
					else if (obj.at(i) == '\n')
					{
						vertexBuffer.z = stof(sBuffer);

						outNormals.push_back(vertexBuffer);

						std::cout << "Finished normal: " << std::endl;
						std::cout << "X: " << vertexBuffer.x << " Y: " <<
							vertexBuffer.y << " Z: " << vertexBuffer.z << std::endl;
						std::cout << "outNormals is now size: " << outNormals.size();

						vertexBuffer = sf::Vector3f();
						sBuffer = "";
						point = 0;
						defining = false;
						continue;
					}

					sBuffer += obj.at(i);

					continue;
				}
				else if (identifier == "f")
				{
					std::cout << "VERTEX SIZE: " << outVertices.size() << std::endl;
					std::cout << "NORMAL SIZE: " << outNormals.size() << std::endl;
					std::cout << "DOING FACE!" << std::endl;

					if (obj.at(i) == ' ')
					{
						std::cout << "Doing normal of either first or second triplet!" << std::endl;
						//Finish one of the triplets
						//and push the data

						//normal (faceIP = 2)

						std::cout << "Inserting normal, normal ID: " << std::stoi(sBuffer) - 1 << std::endl;

						normals.push_back(outNormals[std::stoi(sBuffer) - 1]);


						faceIP = 0;
						//i++;
						sBuffer = "";
						continue;
					}

					if (obj.at(i) == '\n')
					{
						std::cout << "Finishing face group!" << std::endl;
						//normal (faceIP = 2)
						//Do last triplet and flush

						normals.push_back(outNormals[std::stoi(sBuffer) - 1]);

						defining = false;
						identifier = "";

						faceIP = 0;
						sBuffer = "";

						//Push the color three times to make all
						//added vertices the mtlcolor used!

						colors.push_back(materials[materialName]);
						colors.push_back(materials[materialName]);
						colors.push_back(materials[materialName]);
						continue;

					}

					if (obj.at(i) == '/')
					{

						std::cout << "Doing vertex or UV!" << std::endl;
						if (sBuffer == "")
						{
							sBuffer = "1";
						}


						if (faceIP == 0)
						{
							std::cout << "Inserting vertex, vertex ID: " << std::stoi(sBuffer) - 1 << std::endl;
							if (std::stoi(sBuffer) - 1 >= outVertices.size())
							{
								std::cout << std::stoi(sBuffer) - 1 << " is >= " << outVertices.size()
									<< std::endl;
								continue;
							}
							vertices.push_back(outVertices[std::stoi(sBuffer) - 1]);

							std::cout << "Inserted vertex: " << std::endl;
							std::cout << "X: " << outVertices[std::stoi(sBuffer) - 1].x <<
								" Y: " << outVertices[std::stoi(sBuffer) - 1].y << " Z: " <<
								outVertices[std::stoi(sBuffer) - 1].z << std::endl;

							//vertex
						}
						else if (faceIP == 1)
						{
							std::cout << "UV DOING NOTHING!" << std::endl;
							//Uvs do nothing for now
							//uv
						}

						std::cout << "Done!" << std::endl;
						sBuffer = "";
						faceIP++;
						continue;

					}
					std::cout << "BEFORE sBuffer: " << sBuffer << std::endl;


					sBuffer += obj.at(i);

					std::cout << "AFTER sBuffer: " << sBuffer << std::endl;

					continue;

				}
			}


		}
	}



	std::cout << "--------------------------------------" << std::endl;
	std::cout << " File: " << objPath << " was loaded!" << std::endl;
	std::cout << "--------------------------------------" << std::endl;


	if (DISABLE_COUT)
	{
		std::cout.setstate(std::ios_base::goodbit);
	}

}


Model::Model()
{
}


Model::~Model()
{
}
