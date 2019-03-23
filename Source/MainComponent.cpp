/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

class MyBrowser : public WebBrowserComponent {
    bool pageAboutToLoad(const String &newURL) override {
        if (newURL == "https://www.heynow.com/") {
            return !URL(newURL).launchInDefaultBrowser();
        } else {
            return true;
        }
    }
};

//==============================================================================
MainComponent::MainComponent() {
    _browser = std::make_unique<MyBrowser>();
    addAndMakeVisible(_browser.get());
    setSize(600, 400);

	MessageManager::callAsync([this] {
		_browser->loadHTMLString(
			"<!DOCTYPE html><html><body><p style='font:20px verdana; color:#777b88'><b>Were you expecting to find a pot of gold?</b><br><br>If so, please visit us at <a href='https://www.heynow.com'>heynow.com</a> to learn more.<p></body></html>",
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
