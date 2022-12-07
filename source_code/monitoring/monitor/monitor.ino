#define echopin 0
#define trigpin 2
#define alert 14
#define mq4 4

//declaring variables
long duration;
int distance;
int sensor_mq4;
int threshold = 400;
int count = 0;

// initializing pins
void setup(){
	Serial.begin(9600);
	pinMode(trigpin, OUTPUT);  //declaring trigger pin of hc-sr04
	pinMode(echopin, INPUT);  //declaring echo pin of hc=sr04
	pinMode(mq4, INPUT);     //declaring analog for input 
	pinMode(alert, OUTPUT); //declaring pin for buzzer
	delay(20000);          //delay to heat up the has module
}

// main loop
void loop(){
	while(count <=10)
	{
		digitalWrite(trigPin, LOW); //clearing trigger pin
		delayMicroseconds(2); 
		digitalWrite(trigPin, HIGH); // triggering signal
		delayMicroseconds(10);      // delay 10 microseconds
		digitalWrite(trigpin, LOW);// making trigger pin low
		duration = pulseIn(echopin, HIGH); // receiving input
		distance = duration * 0.034 / 2; // converting to cm 
		Serial.print(distance); 

		if ( distance <= 45 ) //loop to set distance
		{
			while( distance <= 20 ) // loop to protect sensors
			{
				digitalWrite(alert, HIGH);
			}

			digitalWrite(alert, LOW);
			delay(1000);
			count++;
		}
	}

	delay(30000); // delay to set as sensor
	sensor_mq4 = analogRead(mq4); // defining analog read
	if(sensor_mq4 > threshold)
	{
		Serial.print("ppm: "); 
		Serial.println(sensor_mq4); 
	}
	return 0;
}

