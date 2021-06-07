#include "color.h"

#include <sstream>

#include "base/text/character.h"
#include "base/text/funcstring.h"
#include "base/conv/parse.h"

using namespace Gfx;
using namespace Conv;

Color::operator std::string() const
{
	char res[10];
	res[0] = '#';
	Text::Character::toHex(getRedByte(), res + 1);
	Text::Character::toHex(getGreenByte(), res + 3);
	Text::Character::toHex(getBlueByte(), res + 5);
	Text::Character::toHex(getAlphaByte(), res + 7);
	res[9] = '\0';
	return res;
}

Color::Color(const std::string &string)
{
	if (string[0] == '#' && string.size() == 9)
	{
		red = (uint8_t)Text::Character::hex(&string[1]) / 255.0;
		green = (uint8_t)Text::Character::hex(&string[3]) / 255.0;
		blue = (uint8_t)Text::Character::hex(&string[5]) / 255.0;
		alpha = (uint8_t)Text::Character::hex(&string[7]) / 255.0;
	}
	else if (string[0] == '#' && string.size() == 7)
	{
		red = (uint8_t)Text::Character::hex(&string[1]) / 255.0;
		green = (uint8_t)Text::Character::hex(&string[3]) / 255.0;
		blue = (uint8_t)Text::Character::hex(&string[5]) / 255.0;
		alpha = 1.0;
	} else if (string.empty())
	{
		*this = Transparent();
	}
	else if (Text::FuncString f(string, false); !f.isEmpty())
	{
		if (f.getName() == "rgb")
		{
			auto ps = f.getParams();
			if (ps.size() != 3)
				throw std::logic_error("invalid color string");
			*this = RGBA(
				parse<uint8_t>(ps.at(0)),
				parse<uint8_t>(ps.at(1)),
				parse<uint8_t>(ps.at(2)));
		}
		else if (f.getName() == "rgba")
		{
			auto ps = f.getParams();
			if (ps.size() != 4)
				throw std::logic_error("invalid color string");
			*this = RGBA(
				parse<uint8_t>(ps.at(0)),
				parse<uint8_t>(ps.at(1)),
				parse<uint8_t>(ps.at(2)),
				parse<double>(ps.at(3)) * 255);
		}
		else throw std::logic_error("invalid color string");
	}
	else throw std::logic_error("invalid color string");
}

Color Color::RGB(uint32_t rgb)
{
	Color c;

	c.blue = (rgb & 0x000000FF) / 255.0;
	rgb >>= 8;
	c.green = (rgb & 0x000000FF) / 255.0;
	rgb >>= 8;
	c.red = (rgb & 0x000000FF) / 255.0;

	c.alpha = 1.0;

	return c;
}

Color Color::RGBA(uint32_t rgba)
{
	auto alpha = (rgba & 0x000000FF) / 255.0;
	auto rgb = rgba >> 8;
	auto c = RGB(rgb);
	c.alpha = alpha;

	return c;
}

Color Color::RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return Gfx::Color(r / 255.0, g / 255.0, b / 255.0, a / 255.0);
}
