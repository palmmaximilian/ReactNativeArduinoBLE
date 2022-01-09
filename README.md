# React Native Arduino BLE Example

An example project on how to communicate between an esp32 and a React Native app over Bluetooth low energy
A video showing the app can be found [here](https://www.youtube.com/watch?v=erWibryA_tE)

## What is the purpose of this project?

This is a very simple example of how you can communicate over BLE (Bluetooth Low Energy) between an ESP32 (programmed using Arduino) and a React Native App

---

## What does this project do?

It establishes a BLE connection, retrieves the initial Values of two characteristics and monitors them.
Then the app has one checkbox to update a value on the ESP side.

It is only compiled for Android at this point but I see no problem with it working for iOS.

---

## Prequesits

1. You need everything needed for a regular ReactNative App, so NodeJS and a JAVA SDK. Try with the most basic ReactNative Example to make sure your enviroment is working

2. I am using Visual Studio Code with PlatformIO for the Arduino Programming
   Android Studio to run the App on a real device since emulators dont have Bluetooth.

   ***

## Installation

1. Place the contents of the repository somewhere on your system (manualy or with git) and open the folder in VSCode

2. run the following command to install all needed libraries

`npm install --save`

3. update the Android Studio SDK location in ./android/local.properties

4. run the following command to launch the app on your connected android phone (make sure it has debugging enabled)

`npx react-native run-android`

5. In a seperate VSCode Window open the "Arduino" folder and upload the Code to an ESP32 using PlatformIO

---

## Use

The App should have one button "Connect".
Upon hitting that button it should connect to the ESP32 and continously update the Message.
When you use the checkbox the Arduino should report that over the Serial Port.

---

## Useful Links

- [BLX library documentation](https://dotintent.github.io/react-native-ble-plx/#introduction)
- [Arduino BLE library documentation](https://github.com/nkolban/esp32-snippets/blob/master/Documentation/BLE%20C%2B%2B%20Guide.pdf)
- [Another Example Tutorial](https://blog.bam.tech/developer-news/make-your-first-iot-react-native-application-with-the-bluetooth-low-energy)
- [BLX Demo](https://github.com/priyanka-Sadh/react-native-ble-plx-demo)
