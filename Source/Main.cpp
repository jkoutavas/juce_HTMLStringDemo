/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"

//==============================================================================
class HTMLStringDemoApplication  : public JUCEApplication
{
public:
    //==============================================================================
    HTMLStringDemoApplication() {}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }

    //==============================================================================
    void initialise (const String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..

        mainWindow.reset (new MainWindow (getApplicationName()));
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..

        mainWindow = nullptr; // (deletes our window)
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainComponent class.
    */
    class MainWindow    : public DocumentWindow
    {
    public:
        MainWindow (String name)  : DocumentWindow (name,
                                                    Desktop::getInstance().getDefaultLookAndFeel()
                                                                          .findColour (ResizableWindow::backgroundColourId),
                                                    DocumentWindow::allButtons)
        {
#if JUCE_WINDOWS
			upgradeWebBrowsing();
#endif

            setUsingNativeTitleBar (true);
            setContentOwned (new MainComponent(), true);

            centreWithSize (getWidth(), getHeight());
            setVisible (true);
        }

        void closeButtonPressed() override
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

#if JUCE_WINDOWS
		void upgradeWebBrowsing() {
			// want to add a key of the form
			// <binaryname>.exe  DWORD  9999
			// 9999 indicates IE9

			String keypath =
				"HKEY_CURRENT_USER\\Software\\Microsoft\\Internet "
				"Explorer\\Main\\FeatureControl\\FEATURE_BROWSER_EMULATION\\";

			// build the full path to the key
			String key = keypath + "HTMLStringDemo.exe";

			// this is the value we want
			unsigned int correctValue = 9999;
			bool ok = false;

			// lets look for it anyway
			bool v = WindowsRegistry::valueExists(key);
			if (v) {
				MemoryBlock data;
				unsigned int sz = WindowsRegistry::getBinaryValue(key, data);
				if (sz == 4)  // DWORD
				{
					unsigned int val = *(unsigned int*)data.getData();
					if (val >= correctValue) ok = true;
				}
			}

			if (!ok) {
				WindowsRegistry::setValue(key, correctValue);
			}
		}
#endif
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (HTMLStringDemoApplication)
