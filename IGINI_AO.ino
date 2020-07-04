
int conta1=0, conta2=0, ponto=0, avanco=1;
int f;


void setup(void)
{
 
  Serial.begin(9600);
pinMode(13, OUTPUT);
pinMode(12, OUTPUT);
attachInterrupt(0, rpm, FALLING);
 // inicializa timer1 
  noInterrupts();           // disabilita todas as interrupções
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 0;            // compare match register 16MHz/256/2Hz
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts


}

ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{////mudar os calculos para outros tipos de ignição e qunatidade de cilindros
conta1++; 
}

void loop(void)
{
 if (Serial.available() > 0) {
    // lê do buffer o dado recebido:
   f = Serial.read();

    // responde com o dado recebido:
    Serial.print("OK");
     if(f==97){
      avanco++;
      f="Z";
    }
    if(f==114){
      avanco--;
      f="z";
    }
    }
    if(avanco<1){
      avanco=1;
    }
    if(avanco>25){
      avanco=25;
    }
   
}
void rpm(){
ponto++;
 if(ponto==avanco){
  digitalWrite(13, HIGH);   

 }
 if(ponto==avanco+1){                      // bobina 1 e 4
  digitalWrite(13, LOW);    
 }

  if(ponto==avanco+30){
  digitalWrite(12, HIGH);  
 }
 if(ponto==avanco+31){                      // bobina 2 e 3
  digitalWrite(12, LOW);    
 }
if(conta1>conta2*2-10){                         // le Falha e renicia a contagem
conta2=0;
ponto=0;
}
conta2=conta1;
conta1=0;
 
}
