void stim(int j) {
    for ( int i=0; i<16; i++ ) {
      digitalWrite(CLK, LOW);
      delayMicroseconds(1);
      if (input[j][i] == 1) digitalWrite(DIN, HIGH);
      else digitalWrite(DIN, LOW);
      delayMicroseconds(1);
      digitalWrite(CLK, HIGH);
      delayMicroseconds(1);
    }
    digitalWrite(LE, LOW);
    delayMicroseconds(5);
    digitalWrite(DIN, LOW);
    delayMicroseconds(5);
    digitalWrite(CLK, LOW);
    delayMicroseconds(10);

    curStrength[j-1] = strength[j-1];
    
//    digitalWrite(DA_CS, LOW);     //enable clock
//    SPI.transfer16(char(curStrength[j-1]) << 6);
//    digitalWrite(DA_CS, HIGH);

    analogWrite(A0, curStrength[j-1]);
    
    delayMicroseconds(pulseWidth);
    
//    digitalWrite(DA_CS, LOW);     //enable clock
//    SPI.transfer16(0 << 6);
//    digitalWrite(DA_CS, HIGH);

    analogWrite(A0, 0);
    
    delayMicroseconds(10);
    digitalWrite(LE, HIGH);
    //delayMicroseconds(20);
}
