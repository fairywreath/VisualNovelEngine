#include "SaveState.hpp"

SaveState::SaveState(StateStack& stack, Context context) :
	State(stack, context),
	nSectionLabel("SAVE", context.fonts->get("sinkins")),
	nInfoLabel("save story progress", context.fonts->get("ttcommons")),
	nExitBtn(context, "EXIT"),
	nBackground(context.textures->get("statebg")),
	nFadableBg(nBackground),
	nComponents(),
	nSaves(),
	nPageNum(0)
{
	nSectionLabel.setSize(100);
	nSectionLabel.setColor(sf::Color(249, 169, 178));
	nSectionLabel.setOriginRight();
	nSectionLabel.setPosition(TitleLabelX, TitleLabelY);
	packComponent(&nSectionLabel);

	nInfoLabel.setSize(24);
	nInfoLabel.setColor(sf::Color(249, 169, 178));
	nInfoLabel.centerOriginX();
	nInfoLabel.setPosition(InfoLabelX, TitleLabelY);
	packComponent(&nInfoLabel);

	nExitBtn.setFont(context.fonts->get("huxleyv"));
	nExitBtn.setSize(55);
	nExitBtn.setPosition(80.f, TitleLabelY);
	nExitBtn.setCallback([this]() {
		requestStackPop();
		});
	packComponent(&nExitBtn);

	setUpdateState(UpdateState::OnTop);

	/*
		@setup the save buttons
	*/
	const auto centerX = (float)context.window->getSize().x / 2;
	const auto distX = 30.f;
	const auto distY = 110.f;
	const auto startY = 20.f;
	const auto numCols = 2.f;
	nSaves.reserve(NumPerPage);
	for (int i = 0; i < NumPerPage; i++) {
		nSaves.push_back(std::make_unique<GUI::SavePanel>(context));
		if (i >= NumPerPage / numCols)
		{
			nSaves[i]->setOriginLeft();
			nSaves[i]->setPosition(centerX + distX, startY + (( i - (NumPerPage / numCols)) * distY));
		}
		else
		{
			nSaves[i]->setOriginRight();
			nSaves[i]->setPosition(centerX - distX, startY + (i * distY));
		}
		nSaves[i]->setNumber(i + 1);
		nComponents.push_back(nSaves[i].get());
	}
}

void SaveState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(nBackground);

	for (const auto& cmp : nComponents)
	{
		window.draw(*cmp);
	}

}

bool SaveState::update(sf::Time dt)
{
	for (const auto& cmp : nComponents)
	{
		cmp->update(dt);
	}

	nFadableBg.update(dt);

	return false;
}

bool SaveState::handleEvent(const sf::Event& event)
{
	for (const auto& cmp : nComponents)
	{
		cmp->handleEvent(event);
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		requestStackPop();
	}
	return false;
}

void SaveState::setUpdateState(UpdateState state)
{
	State::setUpdateState(state);

	if (state == UpdateState::OnTop)
	{
		for (const auto& cmp : nComponents)
		{
			cmp->fade(1.f, 255, 0);
		}
		nFadableBg.fade(1.f, 255, 0);
	}
	else if (state == UpdateState::InRemovalAnimation)
	{
		for (const auto& cmp : nComponents)
		{
			cmp->fade(1.f, 0, 255);
		}
		nFadableBg.fade(1.f, 0, 255);
	}
	else
	{

	}
}

void SaveState::packComponent(GUI::Component* cmpt)
{
	nComponents.push_back(cmpt);
}
