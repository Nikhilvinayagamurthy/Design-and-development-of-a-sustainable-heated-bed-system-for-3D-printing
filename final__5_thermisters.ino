const int thermistorPin1 = A2;   // Thermistor 1 voltage divider connected to A2
const int thermistorPin2 = A3;   // Thermistor 2 voltage divider connected to A3
const int thermistorPin3 = A4;   // Thermistor 3 voltage divider connected to A4
const int thermistorPin4 = A5;   // Thermistor 4 voltage divider connected to A5
const int thermistorPin5 = A6;   // Thermistor 5 voltage divider connected to A6
const float seriesResistor = 4700.0;  // External 4.7kΩ resistor
const float B = 3950.0;         // Beta value for the thermistor
const float R0 = 100000.0;      // Resistance at 25°C (100kΩ)
const float T0 = 298.15;        // Reference temperature in Kelvin (25°C)

void setup() {
  Serial.begin(9600);  // Start Serial communication
}

void loop() {
  // Read ADC values for all five thermistors
  int rawADC1 = analogRead(thermistorPin1);
  int rawADC2 = analogRead(thermistorPin2);
  int rawADC3 = analogRead(thermistorPin3);
  int rawADC4 = analogRead(thermistorPin4);
  int rawADC5 = analogRead(thermistorPin5);

  // Convert ADC values to voltage
  float voltage1 = (rawADC1 / 1023.0) * 5.0;
  float voltage2 = (rawADC2 / 1023.0) * 5.0;
  float voltage3 = (rawADC3 / 1023.0) * 5.0;
  float voltage4 = (rawADC4 / 1023.0) * 5.0;
  float voltage5 = (rawADC5 / 1023.0) * 5.0;

  // Calculate thermistor resistances
  float thermistorResistance1 = (seriesResistor * (5.0 - voltage1)) / voltage1;
  float thermistorResistance2 = (seriesResistor * (5.0 - voltage2)) / voltage2;
  float thermistorResistance3 = (seriesResistor * (5.0 - voltage3)) / voltage3;
  float thermistorResistance4 = (seriesResistor * (5.0 - voltage4)) / voltage4;
  float thermistorResistance5 = (seriesResistor * (5.0 - voltage5)) / voltage5;

  // Calculate temperatures using Beta parameter formula
  float temperature1 = 1.0 / (1.0/T0 + (1.0/B) * log(thermistorResistance1 / R0));
  float temperature2 = 1.0 / (1.0/T0 + (1.0/B) * log(thermistorResistance2 / R0));
  float temperature3 = 1.0 / (1.0/T0 + (1.0/B) * log(thermistorResistance3 / R0));
  float temperature4 = 1.0 / (1.0/T0 + (1.0/B) * log(thermistorResistance4 / R0));
  float temperature5 = 1.0 / (1.0/T0 + (1.0/B) * log(thermistorResistance5 / R0));

  // Convert Kelvin to Celsius
  temperature1 -= 273.15;
  temperature2 -= 273.15;
  temperature3 -= 273.15;
  temperature4 -= 273.15;
  temperature5 -= 273.15;

  // Print temperature values in the desired format
  Serial.print("Temperature 1: ");
  Serial.print(temperature1);
  Serial.print(", Temperature 2: ");
  Serial.print(temperature2);
  Serial.print(", Temperature 3: ");
  Serial.print(temperature3);
  Serial.print(", Temperature 4: ");
  Serial.print(temperature4);
  Serial.print(", Room Temperature: ");
  Serial.println(temperature5);

  delay(3000); // Read temperature every 3 seconds
}