/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() {
    _browser = std::make_unique<WebBrowserComponent>();
    addAndMakeVisible(_browser.get());
    setSize(600, 400);

	MessageManager::callAsync([this] {
		_browser->loadHTMLString(
			"<!DOCTYPE html><html><body><h1>My First Heading</h1><p>My first "
			"paragraph.</p></body></html>",
			"");
	});
}

MainComponent::~MainComponent() {}

//==============================================================================
void MainComponent::paint(Graphics& g) {
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

    g.setFont(Font(16.0f));
    g.setColour(Colours::white);
    g.drawText("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainComponent::resized() {
    _browser->setBounds(getLocalBounds());
}
