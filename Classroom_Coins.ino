/*
 * Board Layout in terms of numbering of LEDs:
 * 15  14  13  12  11  10  9   8   7   6   5   4   3   2   1   0
 * 16..                                                     ...31
 * 47..                                                     ...32
 * 48..                                                     ...63
 * 79..                                                     ...64
 * 80..                                                     ...95
 * 111..                                                    ...96
 * 112..                                                    ...127
 * 143..                                                    ...128
 * 144..                                                    ...159
 * 175..                                                    ...160
 * 176..                                                    ...191
 * 207..                                                    ...192
 * 208..                                                    ...223
 * 239..                                                    ...224
 * 240..                                                    ...255
 */

//Set up the LED Matrix
#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    256
CRGB leds[NUM_LEDS];

//Define the colors being used beforehand
CRGB orange = CRGB(255, 100, 0);
CRGB green = CRGB(27, 209, 37);
CRGB blue = CRGB(34, 105, 227);
CRGB purple = CRGB(195, 0, 255);

//Lightest shade
CRGB orange1 = CRGB(255, 194, 153);
CRGB green1 = CRGB(166, 237, 171);
CRGB blue1 = CRGB(168, 190, 227);
CRGB purple1 = CRGB(239, 189, 255);

//Medium-light shade
CRGB orange2 = CRGB(255, 159, 97);
CRGB green2 = CRGB(104, 227, 112);
CRGB blue2 = CRGB(109, 153, 227);
CRGB purple2 = CRGB(223, 122, 255);

//Medium shade
CRGB orange3 = CRGB(255, 120, 33);
CRGB green3 = CRGB(50, 217, 61);
CRGB blue3 = CRGB(67, 126, 230);
CRGB purple3 = CRGB(203, 41, 255);

//Pin numbers for all the inputs/outputs
int studentPin = A3;
int studentState = 0;

int coin1Pin = 2;
int coin2Pin = 3;
int coin3Pin = 4;
int coin4Pin = 5;

//Counting variables
int coinNum = 0;
int timeCount = 0;

//2D Array to make it easier to access the right LED
int cols[16][16];

void setup() {
  //Initialize the LED board
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(5);

  //Set pinMode
  pinMode(coin1Pin, INPUT);
  pinMode(coin2Pin, INPUT);
  pinMode(coin3Pin, INPUT);
  pinMode(coin4Pin, INPUT);

  Serial.begin(9600);

  //Set the LED board matrix so that the LEDs can be accessed by column + row number
  int j = 15;
  for(int i = 0; i <= 15; i++) {
    cols[0][i] = i;
    cols[2][i] = i + 32;
    cols[4][i] = i + 64;
    cols[6][i] = i + 96;
    cols[8][i] = i + 128;
    cols[10][i] = i + 160;
    cols[12][i] = i + 192;
    cols[14][i] = i + 224;

    cols[1][i] = j + 16;
    cols[3][i] = j + 48;
    cols[5][i] = j + 80;
    cols[7][i] = j + 112;
    cols[9][i] = j + 144;
    cols[11][i] = j + 176;
    cols[13][i] = j + 208;
    cols[15][i] = j + 240;
    
    j -= 1;
  }

  //Turn all the LEDs off at the start of the program
  for(int i = 0; i < 256; i++) {
    leds[i] = CRGB(0,0,0);
  }
  FastLED.show();
}

void loop() {
  //Read to see if any of the color-determining buttons have been pressed
  //If so - determine which color, then run the selectCol function with that color
   if(digitalRead(coin1Pin) == HIGH){
     coinNum = 1;
     selectCol(1);
     timeCount = 0;
   }
   else if(digitalRead(coin2Pin) == HIGH){
     coinNum = 2;
     selectCol(2);
     timeCount = 0;
   }
   else if(digitalRead(coin3Pin) == HIGH){
     coinNum = 3;
     selectCol(3);
     timeCount = 0;
   }
   else if(digitalRead(coin4Pin) == HIGH){
     coinNum = 4;
     selectCol(4);
     timeCount = 0;
   }

  //If no button is pressed, keep listening
  if(coinNum == 0) {
    delay(1);
  }
  else{
    //Now, read the inputs from the 16 student-column buttons
    studentState = analogRead(studentPin);
    //Serial.println(studentState);

    //If the reading is less than 20, no button has been pressed yet
    if(studentState < 20){
      delay(1);
      //Continue playing the selectCol function
      selectCol(coinNum);
      //Add 1 to the time count
      timeCount += 1; 
      //If it has been 25 cycles without the selection of a student pin, reset
      if(timeCount >= 25) {
        coinNum = 0;
      }
    }

    //Determine which column the button press corresponds to, 
    //then run lightCol on that combination of column and color
    else if(studentState < 35){
      lightCol(0, coinNum);
      coinNum = 0;
    }

    else if(studentState < 54){
      lightCol(1, coinNum);
      coinNum = 0;
    }

    else if(studentState < 62) {
      lightCol(2, coinNum);
      coinNum = 0;
    }

    else if(studentState < 69) {
      lightCol(3, coinNum);
      coinNum = 0;
    }

    else if(studentState < 78) {
      lightCol(4, coinNum);
      coinNum = 0;
    }
  
    else if(studentState < 85) {
      lightCol(5, coinNum);
      coinNum = 0;
    }

    else if(studentState < 96) {
      lightCol(6, coinNum);
      coinNum = 0;
    }

    else if(studentState < 110) {
      lightCol(7, coinNum);
      coinNum = 0;
    }

    else if(studentState < 125) {
      lightCol(8, coinNum);
      coinNum = 0;
    }

    else if(studentState < 145) {
      lightCol(9, coinNum);
      coinNum = 0;
    }

    else if(studentState < 170) {
      lightCol(10, coinNum);
      coinNum = 0;
    }

    else if(studentState < 220) {
      lightCol(11, coinNum);
      coinNum = 0;
    }

    else if(studentState < 290) {
      lightCol(12, coinNum);
      coinNum = 0;
    }

    else if(studentState < 400) {
      lightCol(13, coinNum);
      coinNum = 0;
    }

    else if(studentState < 600) {
      lightCol(14, coinNum);
      coinNum = 0;
    }
  
    else{
      lightCol(15, coinNum);
      coinNum = 0;
    }
  }
  
  delay(1);
}

/*
 * lightCol function: lights an LED in the specified column with the specified color
 * 
 * Inputs: - An int representing the column number to light the LED in
 *         - An int that signifies what color the LED should be lit
 *         
 * No outputs
 * 
 * Post condition: The next unlit LED in the column is lit up with the color given
 */
void lightCol(int colNum, int lightNum){
  //Initialize the variables needed
  int numLights = 0;
  CRGB c;
  CRGB color = leds[cols[colNum][numLights]];

  //Determine which color the LED will be
  if(lightNum == 1) {
    //Orange
    c = orange;
  }
  else if(lightNum == 2) {
    //Green
    c = green;
  }
  else if(lightNum == 3) {
    //Blue
    c = blue;
  }
  else if(lightNum == 4 ){
    //Purple
    c = purple;
  }

  //Cycle through the LEDs in the column until the first unlit LED is found, 
  //or the end of the column has been reached
  while((color != CRGB(0, 0, 0)) && (numLights < 16)) {
    //If the light is already on, go on to the next one
    numLights += 1;
    //If the end of the column has been reached, break out of the while loop
    if(numLights == 16){
      break;
    }
    //Access the next LED's color
    color = leds[cols[colNum][numLights]];
  }

  //If the column has already been filled out:
  if(numLights >= 16) {
    //Turn off all the LEDs 
    for(int i = 0; i < 16; i++) {
      leds[cols[colNum][i]] = CRGB(0, 0, 0);
    }
    FastLED.show();
    delay(300);
    //Reset to the beginning
    numLights = 0;
  }

   //Light the next unlit LED (which was found earlier)
   leds[cols[colNum][numLights]] = c;
   FastLED.show();
   delay(300);

  //Call sortCol to sort the column
  sortCol(colNum, numLights + 1);

  //If, on this iteration, the column was just filled out
  //Play the fullCol animation to signify the completion of a column
  if(numLights == 15) {
    fullCol(colNum);
  }
}

/*
 * selectCol function: flashes the last row of LEDs in the color specified to 
 *                     indicate that a student button can now be selected
 * 
 * Inputs: - An int corresponding to the color that was just selected
 * 
 * No outputs
 * 
 * Post condition: The final row of LEDs on the matrix will flash once in 
 *                 the color specified
 */
void selectCol(int lightNum){
  CRGB c;

  //Determine which color button has just been picked
  if(lightNum == 1) {
    //Orange
    c = orange;
  }
  else if(lightNum == 2) {
    //Green
    c = green;
  }
  else if(lightNum == 3) {
    //Blue
    c = blue;
  }
  else if(lightNum == 4 ){
    //Purple
    c = purple;
  }


  //Store the current colors of the final row of LEDs
  CRGB lights[16];
  for(int i = 0; i < 16; i++) {
    lights[i] = leds[cols[i][15]];
  }

  //Light up the final row of LEDs with the specified color
  for(int i = 0; i < 16; i++) {
    leds[cols[i][15]] = c;
  }
  FastLED.show();
  delay(300);

  //Turn off all the LEDs in the final row
  for(int i = 0; i < 16; i++){
    leds[cols[i][15]] = CRGB(0, 0, 0);
  }
  FastLED.show();
  delay(300);

  //Restore the initial colors that were in the final row
  for(int i = 0; i < 16; i++) {
    leds[cols[i][15]] = lights[i];
  }
  FastLED.show();
}

/*
 * sortCol function: sorts the LEDs in a column by color in order of 
 *                   orange --> green --> blue --> purple
 * 
 * Inputs: - An int for the column number that is to be sorted
 *         - An int for how many LEDs in that column are lit up
 * 
 * No outputs
 * 
 * Post Condition: LEDs in the column are sorted by color
 */
void sortCol(int colNum, int lightNum){
  //Initialize the variables to count the LEDs of each color
  int oCount = 0;
  int gCount = 0;
  int bCount = 0;
  int pCount = 0;

  //Create an array of CRGB objects with length of however many LEDs are lit in the column
  CRGB lights[lightNum];

  //Loop through the LEDs and determine how many of each color there are
  for(int i = 0; i < lightNum; i++) {
    CRGB color = leds[cols[colNum][i]];
    lights[i] = color;
    if(color == orange) {
      oCount += 1;
    }
    if(color == green) {
      gCount += 1;
    }
    if(color == blue){
      bCount += 1;
    }
    if(color == purple) {
      pCount += 1;
    }
  }

  //Blink the LEDs in the column 3 times:  
  for(int i = 0; i < lightNum; i++){
    leds[cols[colNum][i]] = CRGB(0, 0, 0);
  }
  FastLED.show();
  delay(300);
  
  for(int i = 0; i < lightNum; i++) {
    leds[cols[colNum][i]] = lights[i];
  }
  FastLED.show();
  delay(300);

  for(int i = 0; i < lightNum; i++) {
    leds[cols[colNum][i]] = CRGB(0, 0, 0);
  }
  FastLED.show();
  delay(300);

  for(int i = 0; i < lightNum; i++) {
    leds[cols[colNum][i]] = lights[i];
  }
  FastLED.show();
  delay(300);

  for(int i = 0; i < lightNum; i++) {
    leds[cols[colNum][i]] = CRGB(0, 0, 0);
  }
  FastLED.show();
  delay(300);

  //Light up all the orange LEDs first
  for(int i = 0; i < oCount; i++) {
    leds[cols[colNum][i]] = orange;
    FastLED.show();
    delay(200);
  }

  //Then light up the green LEDs
  for(int i = oCount; i < oCount + gCount; i++) {
    leds[cols[colNum][i]] = green;
    FastLED.show();
    delay(200);
  }

  //Afterwards, light up the blue LEDs
  for(int i = oCount+gCount; i < oCount+gCount+bCount; i++){
    leds[cols[colNum][i]] = blue;
    FastLED.show();
    delay(200);
  }

  //Finally light up all the purple LEDs
  for(int i = oCount + gCount + bCount; i < oCount + gCount + bCount + pCount; i++) {
    leds[cols[colNum][i]] = purple;
    FastLED.show();
    delay(200);
  }

}

/*
 * fullCol function: plays the full column animations upon filling up a column
 * 
 * Inputs: - An int for the column number that has been filled up
 * 
 * No Outputs
 * 
 * Post Condition: A small light animation is played
 */
void fullCol(int colNum) {
  //Initialize variables needed
  CRGB lights[16];
  CRGB lights1[16];
  CRGB lights2[16];
  CRGB lights3[16];

  //Determine how many of each color LED there are in the column
  //Then create 3 corresponding arrays of CRGB variables that have the corresponding shades of the color
  for(int i = 0; i < 16; i++) {
    lights[i] = leds[cols[colNum][i]];
    if(lights[i].r == 255) {
      lights1[i] = orange1;
      lights2[i] = orange2;
      lights3[i] = orange3;
    }
    else if(lights[i].r == 27){
      lights1[i] = green1;
      lights2[i] = green2;
      lights3[i] = green3;
    }
    else if(lights[i].r == 34) {
      lights1[i] = blue1;
      lights2[i] = blue2;
      lights3[i] = blue3;
    }
    else if(lights[i].r == 195) {
      lights1[i] = purple1;
      lights2[i] = purple2;
      lights3[i] = purple3;
    }

    //Turn all the LEDs off
    leds[cols[colNum][i]] = CRGB(0, 0, 0);
  }
  FastLED.show();
  delay(300);

  //Blink the LEDs twice
  for(int i = 0; i < 2; i++ ){
    for(int j = 0; j < 16; j++) {
      leds[cols[colNum][j]] = lights[j];
    }
    FastLED.show();
    delay(300);
    for(int j = 0; j < 16; j++) {
      leds[cols[colNum][j]] = CRGB(0, 0, 0);
    }
    FastLED.show();
    delay(300);
  }

  //Light up the LEDs all white, cascading
  for(int i = 0; i < 1; i++) {
    for(int j = 0; j < 16; j++) {
      leds[cols[colNum][j]] = CRGB(255, 255, 255);
      FastLED.show();
      delay(10);
    }
    delay(100);
    //Turn them all off, cascading
    for(int j = 0; j < 16; j++) {
      leds[cols[colNum][j]] = CRGB(0, 0, 0);
      FastLED.show();
      delay(10);
    }
    delay(100);
  }

  //Light up the LEDs the lightest shade of the colors, cascading
  for(int i = 0; i < 16; i++) {
    leds[cols[colNum][i]] = lights1[i];
    FastLED.show();
    delay(10);
  }
  delay(100);
  //Turn them all off, cascading
  for(int i = 0; i < 16; i++){
    leds[cols[colNum][i]] = CRGB(0, 0, 0);
    FastLED.show();
    delay(10);
  }
  delay(100);

  //Light up the LEDs in the second shade of the colors, cascading
  for(int i = 0; i < 16; i++) {
    leds[cols[colNum][i]] = lights2[i];
    FastLED.show();
    delay(10);
  }
  delay(100);
  //Turn them all off, cascading
  for(int i = 0; i < 16; i++){
    leds[cols[colNum][i]] = CRGB(0, 0, 0);
    FastLED.show();
    delay(10);
  }

  //Light up all the LEDs in the third shade of the colors, cascading
  for(int i = 0; i < 16; i++) {
    leds[cols[colNum][i]] = lights3[i];
    FastLED.show();
    delay(10);
  }
  delay(100);
  //Turn them all off, cascading
  for(int i = 0; i < 16; i++){
    leds[cols[colNum][i]] = CRGB(0, 0, 0);
    FastLED.show();
    delay(10);
  }
  delay(100);

  //Light up the LEDs in the original colors, cascading
  for(int j = 0; j < 16; j++) {
    leds[cols[colNum][j]] = lights[j];
    FastLED.show();
    delay(10);
  }
}
