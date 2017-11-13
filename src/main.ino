#include <morse.h>
#include <Button.h>
#include <elapsedMillis.h>

#define RELAY A1
#define BUTTON 8

LEDMorseSender morseSender = LEDMorseSender(RELAY, 2.0);
Button button = Button(BUTTON, INPUT_PULLUP);

elapsedMillis timeElapsed;
unsigned int interval = 5000;
bool waiting = false;

void setup() {
	morseSender.setup();
	morseSender.setMessage(String("wd40"));
}

void loop() {
	// start sending morse code when the button goes on
	if (button.uniquePress()) {
		// first turn off the light to start a clean morse sequence
		digitalWrite(RELAY, LOW);
		// wait for 2 secs before starting morse
		delay(2000);
		morseSender.startSending();
	}
	// if the button is on, play the morse code
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
	else digitalWrite(RELAY, HIGH);
	delay(100);
}
