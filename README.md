# Raspberry Pi Button Reader
Made for the Raspberry Pi (RPi) 2. Should work with RPi 3, but not tested.

A problem that is faced when attaching a number pad or buttons to a Raspberry Pi is that it is hard to detect whenever a button is "pushed" all the while completing other programming tasks. In order to have continous code, or non-blocking functionality, no pause/sleep functions can be called.

This button reader helps eliminate this problem by implementing an exponential moving average when detecting each pin value. https://en.wikipedia.org/wiki/Moving_average#Exponential_moving_average

One of the current pitfalls is that the library doesn't take advantage of the multiple cores the RPi has to offer. One is for the sake of simplicity and time allotted to this project. Two, anyone who needs multiple threads may have the choice of utilizing the other three threads for their needs instead of being forced to run two concurrent threads. Sometime in the future users will be able to have the choice to choose.

# Real Usage
The ideology follows a flip-phone keypad, NOT a keyboard.
Pressing a button - returns 1 pin.
Holding a button  - returns 1 pin upon activation, not release.
Pushing multiple buttons - returns each pin in the order in which the RPi believes to receive the first input.

# BCM2835
Requires bcm2835 by Mike McCauley.
Pin Reader wraps around bcm2835.
Follow installation guide at: http://www.airspayce.com/mikem/bcm2835/
