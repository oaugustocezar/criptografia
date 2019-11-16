#include <rsa_local.h>

#include <SoftwareSerial.h>
SoftwareSerial s(5,6);
void setup() {
  // put your setup code here, to run once:
  s.begin(9600);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  char data = 'x';
  if(s.available()>0)
  {
    s.write(data);
  }

}
