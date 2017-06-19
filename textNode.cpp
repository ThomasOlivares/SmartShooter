#include "textNode.hpp"
#include "utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

    
TextNode::TextNode(sf::Font& font, const std::string& text)
{
	mText.setFont(font);
	mText.setCharacterSize(20);
	setString(text);
}

void TextNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mText, states.transform*getTransform());
}

void TextNode::setString(const std::string& text)
{
	mText.setString(text);
	centerOrigin(mText);
}