#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>


class TextNode : public sf::Drawable, public sf::Transformable
{
	public:
		explicit			TextNode(sf::Font& font, const std::string& text);

		void				setString(const std::string& text);

		virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
		sf::Text			mText;
};

