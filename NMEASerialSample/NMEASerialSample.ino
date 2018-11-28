void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("$GPRMC,085120.307,A,3541.1493,N,13945.3994,E,000.0,240.3,181211,,,A*6A");
  Serial.println("$GPGGA,175120.307,3541.1493,N,13945.3994,E,1,08,1.0,6.9,M,35.9,M,,0000*5E");
  delay(1000);
}
