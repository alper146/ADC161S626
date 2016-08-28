/*
Configuration of ADC16S626.
Uses bigbang method.
enable pin=D8=PB0-output
SCLK=D9=PB1-output
MISO=D10=PB2-input
*/
#define adc_clk 1
#define adc_miso 2
#define adc_enable 0
unsigned int data;

void setup() {
 DDRB|=(1<<adc_clk)|(1<<adc_enable);
 DDRB&=~(1<<adc_miso);
digitalWrite(8,HIGH);//disable 
Serial.begin(115200);
}

void loop() {
  data=ADC161();
 Serial.println(data);
  delay(10);
}

unsigned int ADC161(void){
 unsigned int result=0;
  PORTB|=(1<<adc_enable);//disable
  PORTB|=(1<<adc_clk); //clock polarity=1;
  delay(1);
  PORTB&=~(1<<adc_enable); //enable
  for (char i=0;i<7;i++){
    __asm__("nop\n\t"); // slow down the frequency approx. to 2 MHz
    } 
clk();
clk();
for(char i=0; i<16; i++){
  result=result<<1;
  clk();
  if(PINB&(1<<adc_miso)){
     result|=0x01;}
  }
  PORTB|=(1<<adc_enable); //disable
  return result;
  }
  
void clk(void){
  PORTB&=~(1<<adc_clk);
  for (char i=0;i<7;i++){
    __asm__("nop\n\t"); // slow down the frequency approx. to 2 MHz
    }
  PORTB|=(1<<adc_clk);
    for (char i=0;i<7;i++){
    __asm__("nop\n\t"); 
    } 
  }
  
