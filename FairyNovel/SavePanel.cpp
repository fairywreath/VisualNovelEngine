#include "SavePanel.hpp"
#include "Utility.hpp"

GUI::SavePanel::SavePanel(State::Context context) :
	Button(context),
	nWindow(*context.window),
	nFadableOuterRect(nOuterRect),
	nChapterTitleLabel("CHAPTER", context.fonts->get("ttcommons")),
	nDateTitleLabel("DATE", context.fonts->get("ttcommons")),
	nChapterLabel("chapter here", context.fonts->get("ttcommons")),
	nDateLabel("date here", context.fonts->get("ttcommons")),
	nNumberLabel("NO.00", context.fonts->get("ttcommons")),
	nDialogueLabel("dialogue here", context.fonts->get("ttcommons")),
	nSprite(context.textures->get("BG1")),
	nFadableSrpite(nSprite),
	nNumber(0),
	nFadableDB(nDialogueBox)
{
	nOuterRect.setSize(sf::Vector2f(500.f, 100.f));
	nOuterRect.setOutlineColor(sf::Color(249, 169, 178));
	nOuterRect.setFillColor(sf::Color(249, 169, 178, 0));
	nOuterRect.setOutlineThickness(0.75);
	nOuterRect.setPosition(0.f, 0.f);
	nFadableOuterRect.setObjectColor(sf::Color(249, 169, 178));
	nFadableOuterRect.setOutlineOnly(true);

	nDialogueBox.setSize(sf::Vector2f(310.f, 25.f));
	nDialogueBox.setOutlineColor(sf::Color(249, 169, 178));
	nDialogueBox.setFillColor(sf::Color(249, 169, 178, 0));
	nDialogueBox.setOutlineThickness(0.75);
	nFadableDB.setObjectColor(sf::Color(249, 169, 178));
	nFadableDB.setOutlineOnly(true);

	nSprite.setScale(0.12f, 0.12f);

	setLabel(nChapterLabel);
	setLabel(nChapterTitleLabel);
	setLabel(nDateLabel);
	setLabel(nDateTitleLabel);
	setLabel(nNumberLabel);
	setLabel(nDialogueLabel);

	const auto titleX = 250.f;
	nChapterTitleLabel.setOriginRight();
	nChapterTitleLabel.setOriginBottom();
	nChapterTitleLabel.setPosition(titleX, 25.f);

	nDateTitleLabel.setOriginRight();
	nDateTitleLabel.setOriginBottom();
	nDateTitleLabel.setPosition(titleX, 55.f);

	nChapterLabel.setOriginLeft();
	nChapterLabel.setOriginBottom();
	nChapterLabel.setPosition(titleX + 20.f, 25.f);

	nDateLabel.setOriginLeft();
	nDateLabel.setOriginBottom();
	nDateLabel.setPosition(titleX + 20.f, 55.f);

	nDialogueLabel.setOriginBottom();
	nDialogueLabel.setOriginLeft();
	nDialogueLabel.setPosition(190.f, 85.f);
	nDialogueLabel.setSize(20);

	nDialogueBox.setPosition(180.f, 65.f);

	nNumberLabel.setSize(16);
	nNumberLabel.setOriginLeft();
	nNumberLabel.setOriginBottom();
	nNumberLabel.setPosition(5.f, 99.f);
}

void GUI::SavePanel::intialize(State::Context context)
{
}

void GUI::SavePanel::handleEvent(const sf::Event& event)
{
	if (checkMouseLocation() && !isSelected())
	{
		select();
	}
	else if (isSelected())
	{
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			activate();		// deactivates instantly if toggle is default(which is the default status)
		}
		else if (!checkMouseLocation())
		{
			deselect();
		}
		else
		{
			// empty
		}
	}
}

void GUI::SavePanel::update(sf::Time dt)
{
	nFadableOuterRect.update(dt);
	nFadableSrpite.update(dt);
	nFadableDB.update(dt);

	for (const auto& cmp : nComponents)
	{
		cmp->update(dt);
	}
}

void GUI::SavePanel::fade(float time, int targetAlpha, int startAlpha)
{
	if (isSelected())
	{
		updateApperance(ButtonState::Normal);
	}

	nFadableOuterRect.fade(time, targetAlpha, startAlpha);


	nFadableSrpite.fade(time, targetAlpha, startAlpha);
	nFadableDB.fade(time, targetAlpha, startAlpha);

	for (const auto& cmp : nComponents)
	{
		cmp->fade(time, targetAlpha, startAlpha);
	}
}

void GUI::SavePanel::setNumber(int num)
{
	nNumber = num;
	if (num > 9)
	{
		nNumberLabel.setText("NO." + std::to_string(num));
	}
	else
	{
		nNumberLabel.setText("NO.0" + std::to_string(num));
	}
}

int GUI::SavePanel::getNumber() const
{
	return nNumber;
}

void GUI::SavePanel::setChapter(const std::string& str)
{
	nChapterLabel.setText(str);
}

void GUI::SavePanel::setDate(const std::string& str)
{
	nDateLabel.setText(str);
}

void GUI::SavePanel::setDialogue(const std::string& str)
{
	// need use glyphs here
}

void GUI::SavePanel::setSprite(const sf::Texture& texture)
{
	nSprite.setTexture(texture);
}

void GUI::SavePanel::setOriginLeft()
{
	setOrigin(0, 0);
}

void GUI::SavePanel::setOriginRight()
{
	setOrigin(nOuterRect.getGlobalBounds().left + nOuterRect.getGlobalBounds().width, 0);
}

void GUI::SavePanel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(nOuterRect, states);
	target.draw(nSprite, states);
	target.draw(nDialogueBox, states);

	for (const auto& cmp : nComponents)
	{
		target.draw(*cmp, states);
	}
}


void GUI::SavePanel::updateApperance(ButtonState state)
{
	switch (state)
	{
	case ButtonState::Hover:
		nOuterRect.setFillColor(sf::Color(249, 169, 178, 75));
		break;
	case ButtonState::Normal:
		nOuterRect.setFillColor(sf::Color(249, 169, 178, 0));
		break;
	case ButtonState::Pressed:
		nOuterRect.setFillColor(sf::Color(249, 169, 178, 0));
		break;
	default:
		break;
	}
}

bool GUI::SavePanel::checkMouseLocation() const
{
	return getTransform().transformRect(nOuterRect.getGlobalBounds()).
		contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(nWindow)));
}

void GUI::SavePanel::setLabel(GUI::Label& label)
{
	label.setColor(sf::Color(249, 169, 178));
	label.setSize(21);
	nComponents.push_back(&label);
}
