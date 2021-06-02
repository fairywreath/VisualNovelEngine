#include "GalleryState.hpp"

GalleryState::GalleryState(StateStack& stack, Context context) :
	State(stack, context),
	nSectionLabel("GALLERY", context.fonts->get("sinkins")),
	nInfoLabel("view memories", context.fonts->get("ttcommons")),
	nExitBtn(context, "EXIT"),
	nBackground(context.textures->get("statebg")),
	nFadableBg(nBackground),
	nComponents()
{
	nSectionLabel.setSize(70);
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
}

void GalleryState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(nBackground);

	for (const auto& cmp : nComponents)
	{
		window.draw(*cmp);
	}

}

bool GalleryState::update(sf::Time dt)
{
	for (const auto& cmp : nComponents)
	{
		cmp->update(dt);
	}

	nFadableBg.update(dt);

	return false;
}

bool GalleryState::handleEvent(const sf::Event& event)
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

void GalleryState::setUpdateState(UpdateState state)
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

void GalleryState::packComponent(GUI::Component* cmpt)
{
	nComponents.push_back(cmpt);
}
