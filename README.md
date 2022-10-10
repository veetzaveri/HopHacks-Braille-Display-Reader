# HopHacks-Braille-Display-Reader



Inspiration
The expensive Braille Displays on the market, which only a small percent of the community can afford. It motivated us to create a device that offers the same functionality at an affordable rate.

What it does
When a sentence of ASCII characters is entered, the Braille Display will display the Braille dots that represent each character of the sentence and can display the next character by moving the display to the right.

How we built it
We used an Arduino Uno to control an LED matrix to display the braille characters. We also used an Arduino Mega to collect raw accelerometer data using MPU6050 and sent this data to a python program running on our laptop. This Python program calculated when to change the characters on the display based on a certain threshold over the acceleration.

Challenges we ran into
One challenge we ran into was creating a low pass filter to help reduce the noise of the graph since the slow movement of the Braille Display would lead to graphs with high noise. Another challenge we had was IMU double integration because with device rotation we would need to measure acceleration, subtract gravity, integrate residual acceleration to get velocities, and then integrate again to get the positions.

Accomplishments that we're proud of
We are proud of how the Braille Display converts the sentence of characters into Braille dots and displays those characters on the LED matrix. Also, we are proud of how the Braille Display can show the next character as it is moved over to the right in a similar fashion to how a sentence from a book is read.

What we learned
We learned how the Arduino Uno takes in text and how it should be converted to display on the LED matrix. Also, how Python can be used to indicate the direction for a frame moved and how an accelerometer can take in raw acceleration data to send to an Arduino Mega.

What's next for Economic Braille Display Reader
This Braille Display can be taken further by being implemented with a glove containing technology similar to tactile stimuli that allow users to hover the glove in the direction to read the next characters of a sentence.
