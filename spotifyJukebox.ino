#include <Wire.h>
#include "rgb_lcd.h"
#define ROTARY_ANGLE_SENSOR A0
#define LED 13  //the Grove - LED is connected to PWM pin D3 of Arduino
#define ADC_REF 5 //reference voltage of ADC is 5v.If the Vcc switch on the seeeduino
                    //board switches to 3V3, the ADC_REF should be 3.3
#define GROVE_VCC 5 //VCC of the grove interface is normally 5v
#define FULL_ANGLE 300 //full value of the rotary angle is 300 degrees

//////
const int buzzerPin = 5;  // Replace with the actual pin number for your buzzer
int previousGroup = -1;   // Initialize previousGroup to an out-of-range value
//////
const int buttonPin = 2;  // Replace with the actual pin number where your button is connected
const int bufferSize = 64;  // Maximum size of the input buffer
char inputBuffer[bufferSize];  // Buffer to store incoming characters
String receivedString = "";  // String to store the received message
boolean newData = false;
rgb_lcd lcd;
const int numRows = 6;  // Number of rows
const int numCols = 2;  // Number of columns
int rotateNum;
//String inputString = "The Box, Roddy Ricch, Box Fan Rest Sound, Fan Sounds,Box Fan Sound,Tmsoft’s White Noise Sleep Sounds,10 Hour Box Fan (No Distractions),Big Fan,Box of Rain - 2013 Remaster,Grateful Dead,Box #10,Jim Croce";  // Replace this with your comma-separated string
String inputString = "";
String myArray[numRows][numCols];
 int doThis= 1;
void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600); // start the serial port at 9600 baud
  pinMode(buttonPin, INPUT_PULLUP);  // Set the button pin as an input with internal pull-up resistor

    pinMode(ROTARY_ANGLE_SENSOR, INPUT);
      pinMode(LED,OUTPUT);   

     pinMode(buzzerPin, OUTPUT);

}



void loop() { 

//get text 

if (doThis == 1) {
   if (Serial.available()) {
     inputString = Serial.readString();

        doThis=2;
    parseCSV(inputString); 
   // Serial.println(inputString);
    }
}
   
if (doThis==2 ){

   //Serial.println(doThis);
  
   //String input = Serial.read();
  //songText = input;

rotateNum = rotat(rotateNum);
      // Define the text to be scrolled in the first row
//  String songText = "Now Playing: list";
  //String artistText = "Artist: You ;) ";

 String songText = myArray[rotateNum-1][0];
String artistText = myArray[rotateNum-1][1];
  
//songText += "    Now playing: ";
songText= "    Play: " + songText;
//


artistText = "By " + artistText;
  

  
  // Calculate the length of the longer text (either songText or artistText)
  int maxTextLength = max(songText.length(), artistText.length());

  // Loop to scroll both texts from right to left
  for (int i = 0; i <= maxTextLength + 16; i++) {
    lcd.clear();


rotateNum = rotat(rotateNum);
 
  if (digitalRead(buttonPin) == HIGH) {
 //   Serial.println("boop"); 
    Serial.println(rotateNum);  // Send "1" to the serial console
    delay(100);  // Add a delay to debounce the button (adjust as needed)
  }

    // Display the first row (songText)
    lcd.setCursor(0, 0);
    for (int j = 0; j < 16; j++) {
      int charIndex = i + j;
      if (charIndex >= 0 && charIndex < songText.length()) {
        lcd.print(songText[charIndex]);
      } else {
        lcd.print(" ");
      }
    }
   
    // Display the second row (artistText)
    lcd.setCursor(0, 1);
    for (int j = 0; j < 16; j++) {
      int charIndex = i + j;
      if (charIndex >= 0 && charIndex < artistText.length()) {
        lcd.print(artistText[charIndex]);
      } else {
        lcd.print(" ");
      }
    }

    // Delay to control the scrolling speed
    delay(200);
  }
}

}

void parseCSV(String csvString) {
  int row = 0;
  int col = 0;

  // Split the input string into tokens using the comma as the delimiter
  char *token = strtok(const_cast<char*>(csvString.c_str()), ",");

  while (token != NULL && row < numRows) {
    // Store the token in the 2D array
    myArray[row][col] = String(token);

    // Move to the next column
    col++;

    // If we have reached the end of a row, move to the next row and reset the column counter
    if (col == numCols) {
      col = 0;
      row++;
    }

    // Get the next token
    token = strtok(NULL, ",");
  }

  // Print the 2D array to verify the values
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
     // Serial.print(myArray[i][j]);
     // Serial.print('\t');  // Add a tab for formatting
    }
  //  Serial.println();  // Move to the next line for the next row
  }
}

int rotat(int previousGroup) {

    
 float voltage;
    int sensor_value = analogRead(ROTARY_ANGLE_SENSOR);
    voltage = (float)sensor_value*ADC_REF/1023;
    float degrees = (voltage*FULL_ANGLE)/GROVE_VCC;
  //  Serial.println("The angle between the mark and the starting position:");
  int currentGroup = -1;  

 
if (degrees >= 0 && degrees <= 50) {
 // Serial.println("Group 1");
  currentGroup = 0;
  //return 1;
} else if (degrees > 50 && degrees <= 100) {
//  Serial.println("Group 2");
  currentGroup = 1;
  //return 2;
} else if (degrees > 100 && degrees <= 150) {
//  Serial.println("Group 3");
  currentGroup = 2;
  //return 3;
} else if (degrees > 150 && degrees <= 200) {
 // Serial.println("Group 4");
  currentGroup = 3;
  //return 4;
} else if (degrees > 200 && degrees <= 250) {
  //Serial.println("Group 5");
  currentGroup = 4;
  //return 5;
} else if (degrees > 250 && degrees <= 300) {
 // Serial.println("Group 6");
  currentGroup = 5;
  //return 6;
} else {
 
  Serial.println("Degrees out of range");
}
//  Serial.println("oppp");
  if (currentGroup != previousGroup) {
    // Buzzer buzzes when the group changes
  //  Serial.println("ahh");
    buzzBuzzer();
    
   // Print the corresponding group to Serial
    // Serial.print("Group ");
     // Serial.println(currentGroup);
    
    // Update previousGroup
    previousGroup = currentGroup;
  return currentGroup;
  
  }

    int brightness;
    
  }


void buzzBuzzer() {
  digitalWrite(buzzerPin, HIGH);
  delay(100);  // Adjust this delay to control the buzzer duration
  digitalWrite(buzzerPin, LOW);
}
