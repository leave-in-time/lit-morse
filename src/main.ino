#include <morse.h>
#include <Button.h>
#include <elapsedMillis.h>

#define RELAY A1
#define BUTTON 8

LEDMorseSender morseSender = LEDMorseSender(RELAY, 7.0);
Button button = Button(BUTTON, INPUT_PULLUP);

elapsedMillis timeElapsed;
unsigned int interval = 1000;
bool waiting = false;

void setup() {
	morseSender.setup();
	morseSender.setMessage(String("sos"));
}

void loop() {
	// start sending morse code when the button goes on
	if (button.uniquePress()) {
		morseSender.startSending();
	}
	// if the button is on play the morse code
	if (button.isPressed()) {
		// if morse message is ended, restart sending it after the interval
		if (!morseSender.continueSending()) {
			if (!waiting) {
				timeElapsed = 0;
				waiting = true;
			}
			if (timeElapsed > interval) {
				morseSender.startSending();
				waiting = false;
			}
		}
	}
	// else turn on the relay/light
	else {
		digitalWrite(RELAY, HIGH);
	}
}
