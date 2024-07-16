//Define the LED Pin
#define PIN_OUT        12
//Define unit length in ms
#define UNIT_LENGTH    250

int numArray[10][7] = {  
  { 1,1,1,1,1,0,1 },    // 0
  { 0,0,0,0,1,0,1 },    // 1
  { 1,0,1,1,0,1,1 },    // 2
  { 1,0,0,1,1,1,1 },    // 3
  { 0,1,0,0,1,1,1 },    // 4
  { 1,1,0,1,1,1,0 },    // 5
  { 1,1,1,1,1,1,0 },    // 6
  { 1,0,0,0,1,0,1 },    // 7
  { 1,1,1,1,1,1,1 },    // 8
  { 1,1,0,1,1,1,1 }		// 9
};

//Build a struct with the morse code mapping
static const struct {const char letter, *code;} MorseMap[] =
{
	{ ' ', "     " }, //Gap between word, seven units 		
	{ '1', ".----" },
	{ '2', "..---" },
	{ '3', "...--" },
	{ '4', "....-" },
	{ '5', "....." },
	{ '6', "-...." },
	{ '7', "--..." },
	{ '8', "---.." },
	{ '9', "----." },
	{ '0', "-----" },
};

void setup()
{
  pinMode( PIN_OUT, OUTPUT );
  pinMode( 2, OUTPUT );
  pinMode( 3, OUTPUT );
  pinMode( 4, OUTPUT );
  pinMode( 5, OUTPUT );
  pinMode( 6, OUTPUT );
  pinMode( 7, OUTPUT );
  pinMode( 8, OUTPUT );
  digitalWrite( PIN_OUT, LOW );
}

void loop()
{
  String morseWord = encode( "0505 " );
  
  for(int i=0; i<=morseWord.length(); i++)
  {
    switch( morseWord[i] )
    {
      case '.': //dit
        digitalWrite( PIN_OUT, HIGH );
        delay( UNIT_LENGTH );
        digitalWrite( PIN_OUT, LOW );
        delay( UNIT_LENGTH );
          
        break;

      case '-': //dah
        digitalWrite( PIN_OUT, HIGH );
        delay( UNIT_LENGTH*3 );
        digitalWrite( PIN_OUT, LOW );
        delay( UNIT_LENGTH );
          
        break;

      case ' ': //gap
        delay( UNIT_LENGTH );
    }
  }
  
  //int readNumbers = decode(morse);
  //numWrite(readNumbers);
  
}

String encode(const char *string)
{
  size_t i, j;
  String morseWord = "";
  
  for( i = 0; string[i]; ++i )
  {
    for( j = 0; j < sizeof MorseMap / sizeof *MorseMap; ++j )
    {
      if( toupper(string[i]) == MorseMap[j].letter )
      {
        morseWord += MorseMap[j].code;
        break;
      }
    }
    morseWord += " "; //Add tailing space to seperate the chars
  }

  return morseWord;  
}

String decode(String morse)
{
  String msg = "";
  
  int lastPos = 0;
  int pos = morse.indexOf(' ');
  while( lastPos <= morse.lastIndexOf(' ') )
  {    
    for( int i = 0; i < sizeof MorseMap / sizeof *MorseMap; ++i )
    {
      if( morse.substring(lastPos, pos) == MorseMap[i].code )
      {
        msg += MorseMap[i].letter;
      }
    }

    lastPos = pos+1;
    pos = morse.indexOf(' ', lastPos);
    
    // Handle white-spaces between words (7 spaces)
    while( morse[lastPos] == ' ' && morse[pos+1] == ' ' )
    {
      pos ++;
    }
  }

  return msg;
}

void numWrite(int number) 
{
  int pin= 2;
  for (int j=0; j < 7; j++) 
  {
   digitalWrite(pin, numArray[number][j]);
   pin++;
  }
}