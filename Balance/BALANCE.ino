void setup() {

  // initialize both serial ports:

  Serial.begin(9600);

  Serial1.begin(115200);
}

void loop() {

if(Serial1.available()>0)
{
  Serial.println(Serial1.available());
  Serial.println(Serial1.readString());
}
}