#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
class Label
{
public:

	std::vector<sf::Sprite> glyphs = std::vector<sf::Sprite>();

	void draw(sf::RenderTarget* target)
	{
		for (int i = 0; i < glyphs.size(); i++)
		{
			target->draw(glyphs.at(i));
		}
	}

	Label();
	~Label();
};

