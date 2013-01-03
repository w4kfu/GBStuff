byte GB_CLK = B00000100;
byte GB_IN = B00001000;
byte GB_OUT = B00010000;

const int led = 13;

byte result;

void setup()
{
  DDRC |= GB_OUT | GB_CLK;
  DDRC &= ~GB_IN;
  PORTC |= GB_CLK;
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void Send(byte data)
{
  for (int currentBit = 0; currentBit < 8; currentBit++)
  {
    if (data & B10000000)
    {
      PORTC &= ~GB_CLK;
      PORTC |= GB_CLK | GB_OUT;
    }
    else
    {
      PORTC &= ~(GB_CLK | GB_OUT);
      PORTC |= GB_CLK;
    }
    data <<= 1;
  }
}

byte Read(void)
{
  byte data = 0;

  for (int currentBit = 0; currentBit < 8; currentBit++)
  {
    data <<= 1;
    PORTC &= ~GB_CLK;
    delay(0.01);
    if (PINC & GB_IN)
    {
      data |= B00000001;
    }
    PORTC |= GB_CLK;
  }
  return data;
}

void loop()
{
  digitalWrite(led, LOW);

  while (1)
  {
    Send(0x02);
    delay(3);
    result = Read();
    //Serial.println(result);
    if (result == 0x60)
      break;
  }
  
  digitalWrite(led, HIGH);

  // launch
  delay(1000);
  Send(0x60);
  delay(1000);
  
  // select multi
  Send(0xD0);
  delay(10);
  Send(0xD7);
  delay(10);
  Send(0xD8);
  delay(10);  
  Send(0x00);
  
  
  while (1) 
  {
    //delay(100);
    //Send(0x00);
  }
}
