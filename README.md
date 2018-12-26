# Arduino NeoPixel Mariah Carey Christmas Tree Lightshow
Code for [RedBearLab's Blend V1.0 Arduino](https://www.seeedstudio.com/Blend-V1-0-a-single-board-integrated-with-Arduino-and-BLE-p-1918.html) to control 150 LED [Adafruit NeoPixel Digital RGBW LED Strip](https://www.adafruit.com/product/2824?length=5) - Black PCB 30 LED/m PRODUCT ID: 2824 5 meters. The code creates a lightshow for a christmas tree in-sync with the household favorite [Mariah Carey - All I Want For Christmas Is You](https://www.youtube.com/watch?v=yXQViqx6GMY).

#### Link to view code in action:
  * https://drive.google.com/open?id=19AwKpEQrmBMTanNbOpcWqGv3utOPJUrr

#### Language and Modules:
* Arduino 1.8.7
* Arduino Time Library by Micheal Margolis V 1.5.0
* Arduino RBL_nRF8001 Library by Cheong V 1.0.0
* Arduino BLEPeripheral Library by Sandeep Mistry V 0.4.0
* Arduino BLE SDK for Arduino by RedBearLab V 1.0.1
* Arduino AdaFruit NeoPixel by Adafruit Version 1.1.7

#### Usage:
* Simply use the Arduino IDE to upload to a Blend Arduino. Then connet to the board via bluetooth with the iOS app LightBlue. Once connected send the digit 1 to the Arduino. This will trigger the lightshow. Start the song at the exact same time. 
* I also tried triggering the lightshow with the Time library at a specific time sent to the arduino via my computer using the processing app. This work randomnly and was not very exact.
* Use to make a holiday party a bit more lit or emphasize to your girl you are a complete nerd.

#### License:
All files in this Github repository are available under the MIT license. See [LICENSE](LICENSE.txt) for more information.
