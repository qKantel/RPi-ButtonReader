# Raspberry Pi Button Reader
Made for the Raspberry Pi (RPi) 2. Should work with RPi 3, but not tested.

A problem that is faced when attaching a number pad or buttons to a Raspberry Pi is that it is hard to detect whenever a button is "pushed" all the while completing other programming tasks. In order to have continous code, or non-blocking functionality, no pause/sleep functions can be called.

This button reader helps eliminate this problem by implementing an exponential moving average when detecting each pin value. https://en.wikipedia.org/wiki/Moving_average#Exponential_moving_average

# Real Usage
The ideology follows a flip-phone keypad, NOT a keyboard.

Pressing a button - returns 1 pin.

Holding a button  - returns 1 pin upon activation, not release.

Pushing multiple buttons - returns each pin in the order in which the RPi believes to receive the first input.

# BCM2835
Requires bcm2835 by Mike McCauley.
Pin Reader wraps around bcm2835.
Follow installation guide at: http://www.airspayce.com/mikem/bcm2835/

# Problems (In order of highest priority)
#### 1. The algorithm is based soley on the program running as fast as possible.
Workaround: Develop the remaining part of your project. Test the program and find a suitable alpha.

#### 2. No choice to spawn a thread in parallel to the main thread.
Features: A start function to allow the reader to run separately. Client will create necessary thread-safe function callbacks.
Note: Implementing this will radically change the current client interface as well.

# Versions
#### 1.0 (June 9, 2016)
-Stable working build for the original project.
