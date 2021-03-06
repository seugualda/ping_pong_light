// Light up ping pong ball w/ ATiny85

// Reference: http://blog.makezine.com/2011/10/10/how-to-shrinkify-your-arduino-projects/



const int redPin = 4;                  // IC leg 6 (PB1), output to red channel
const int greenPin = 0;                // IC leg 5 (PB0), output to green channel
const int bluePin = 1;                 // IC leg 3 (PB4), output to blue channel
const int buttonPin = 2;               // IC leg 7 (PB2), input from button

int delay_int = 50;

double mode = 0;
double mode_adjust = 0.2;


int button_state = 0;
int button_pushed = 0; // This is the indicator that the button was pushed and released
int button_press_initiate[1];     // storage for button press function
int button_press_completed[1];    // storage for button press function

unsigned long currentTime;
double second_timer[1] = {0}; // This is use dto keep track of the timer used to tick for each second
int ticked = 0;

int color = 0;

void setup() {                
  // initialize the digital pin as an output.
  pinMode(redPin, OUTPUT);   
  pinMode(greenPin, OUTPUT);     
  pinMode(bluePin, OUTPUT);
  pinMode(buttonPin, INPUT);       
}

void loop() {
  
  button_state = digitalRead(buttonPin);
  button_pushed = button_press (button_state, button_press_initiate, button_press_completed);    // This function looks for a complete button press of press and release
  if (button_pushed == 1){                // Change mode whenever a button press is detected
    mode += mode_adjust;
  }
 
 if (mode >= 0 && mode < 1){              // This is color changing mode. As the button is pressed, the colors change more slowly
 mode_adjust = 0.2;                       // Modes 1.2, 1.4 etc are sub-modes with different color change speeds
  if (tick(delay_int*(mode),second_timer) == 1){
        color = color + 1;
  }
  if (color > 6){ color = 0; }            // Reset back to red
  display_color(color);  
 }
 
 if (mode >= 1){
mode_adjust = 1;

if (tick(delay_int,second_timer) == 1){ // This flashes a specific color depending on the mode. There are 6 different colors
 if( ticked == 1){ ticked = 0; }
 else if (ticked == 0){ ticked = 1; }
 }
if (ticked == 0) { display_color(mode); }
else if (ticked == 1) { display_color(7); }  // Color 7 is no color (no LEDs lit)
 }
 
 if (mode > 7) {mode = 0;} // The modes cycle through as the button is pressed
          
}

int button_press (int button_indicator, int button_press_initiated[1], int button_press_complete[1]){
	if (button_indicator == 0 && button_press_initiated[0] == 1) {
	button_press_complete[0] = 1;
	button_press_initiated[0] = 0;
	}
	else if (button_indicator == 1){
	button_press_initiated[0] = 1;
	button_press_complete[0] = 0;
	}
	else {button_press_complete[0] = 0;}
return button_press_complete[0];
}

int tick(int delay, double timekeeper[1]){
currentTime = millis();
if(currentTime >= (timekeeper[0] + delay)){
	timekeeper[0] = currentTime;
	return 1;
  }
else {return 0;}
}

void display_color(int color){ // This function creates colors by combining colors together. No PWM, just digital.
if (color == 0){  
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}  
if (color == 1){    
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
}
if (color == 2){  
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
}
if (color == 3){  
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
}
if (color == 4){  
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, LOW);
}
if (color == 5){  
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, HIGH);
}
if (color == 6){  
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);  
}
if (color == 7){  
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);  
}
}
