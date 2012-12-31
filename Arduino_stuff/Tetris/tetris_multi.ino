byte GB_CLK = B00000100;
byte GB_IN = B00001000;
byte GB_OUT = B00010000;
int led = 13;
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

void init_game()
{
    Send(0x29);
    delay(1000);  
}

void music_choice()
{
  // FOR FUN CHOOSE ALL CHOICE
  for (int i = 0x1C; i < 0x20; i++)
  {
    Send(i);
    delay(1000);  
  }  
  
  Send(0x1C);
  delay(1000);
  // CHOICE MUSIC OK
  Send(0x50);
  delay(1000);  
}

void line_choice()
{
  // FOR FUN CHOOSE ALL CHOICE
  for (int i = 0; i < 6; i++)
  {
    // LINES CHOOSE
    Send(i);
    delay(1000);
  }
  Send(0x00);
  delay(1000);  
}

int map_tetris[] = {  0x2F, 0x82, 0x2F, 0x2F, 0x2F, 0x82, 0x82, 0x2F, 0x2F, 0x2F,
                      0x2F, 0x2F, 0x82, 0x2F, 0x82, 0x82, 0x82, 0x2F, 0x2F, 0x2F,
                      0x2F, 0x2F, 0x82, 0x2F, 0x82, 0x2F, 0x82, 0x2F, 0x82, 0x2F,
                      0x2F, 0x2F, 0x2F, 0x82, 0x2F, 0x2F, 0x2F, 0x82, 0x82, 0x2F,
                      0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x82, 0x2F,
                      0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F,
                      0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F,
                      0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F,
                      0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F,
                      0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F};

void send_map()
{
  for (int i = 0; i < 0xA; i++)
  {
    for (int j = 0; j < 0xA; j++)
    {  
      Send(map_tetris[i * j]);
      delay(10);
    }
  } 
}

void send_obj()
{
  for (int i = 0; i < 0xFF; i++)
  {
      Send(0x01);
      delay(10);
  }  
}

void start_map()
{
  Send(0x00);
  delay(100);
  Send(0x29);
  delay(100);  
            
  send_map();
  Send(0x29);
  delay(1000);
  
  send_obj();
        
  // Wiat until other gb finish
  for (int i = 0; i < 10; i++)
  {
    Send(0x30);
    delay(10);
  }    
  digitalWrite(led, HIGH);
  delay(100);
  Send(0x00);	
  delay(100);
  Send(0x02);
  delay(100);
  Send(0x02);
  delay(100);
  Send(0x20);  
}

void finish_lines()
{
  delay(5000);
  Send(0x77);
  delay(100);
  Send(0x02);   
  delay(100);
  Send(0x43);  
}

void victory()
{
  delay(5000);
  Send(0x60);
  delay(100);
  Send(0x02);
  delay(100);
  Send(0x02);     
   delay(100);
  Send(0x02);
   delay(100);
  Send(0x79);  
}

void loop()
{
  delay(3000);
  digitalWrite(led, LOW);
  init_game();
  music_choice();  
  line_choice();

  // START THE GAME
  Send(0x60);
  
  for (int i = 0; i < 4; i++)
  {
    delay(1000);          
    start_map();
    finish_lines();
    victory();
  }
  
   while (1) 
   {
     
   }
}
