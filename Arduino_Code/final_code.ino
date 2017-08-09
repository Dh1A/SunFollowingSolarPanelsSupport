 



// LDR pin connections
//  name  = analogpin;
int ldrlt = 0; //LDR top left - BOTTOM LEFT    <--- BDG
int ldrrt = 1; //LDR top rigt - BOTTOM RIGHT 
int ldrld = 3; //LDR down left - TOP LEFT
int ldrrd = 2; //ldr down rigt - TOP RIGHT
#define relais1 8
#define relais2 9
#define relais3 10
#define relais4 11
#define Ils0A     3
#define Ils1A     2


void verin_1_sens1 ()
{
 digitalWrite(relais1,HIGH);
  digitalWrite(relais2,LOW);
}
void verin_1_sens2 ()
{ 
  digitalWrite(relais1,LOW);
  digitalWrite(relais2,HIGH);
}
void verin_2_sens2 ()
{
 digitalWrite(relais4,HIGH);
 digitalWrite(relais3,LOW);
}
void verin_2_sens1 ()
{ 
  digitalWrite(relais3,HIGH);
  digitalWrite(relais4,LOW);
}
void verin_1_stop ()
{ 
  digitalWrite(relais1,HIGH);
  digitalWrite(relais2,HIGH);
}
void verin_2_stop ()
{
 digitalWrite(relais4,HIGH);
 digitalWrite(relais3,HIGH);
}




void setup()
{
 pinMode(Ils0A, INPUT);  
 pinMode(Ils1A, INPUT);  
 pinMode(relais1,OUTPUT);
  pinMode(relais2,OUTPUT);
 pinMode(relais3,OUTPUT);
  pinMode(relais4,OUTPUT);

  
  Serial.begin(9600);
     
}

void loop() 
{
  
  int lt = analogRead(ldrlt); // top left
  int rt = analogRead(ldrrt); // top right
  int ld = analogRead(ldrld); // down left
  int rd = analogRead(ldrrd); // down rigt
  
  
  int dtime = 10;
  int tol = 50;
  
  int avt = (lt + rt) / 2; // average value top
  int avd = (ld + rd) / 2; // average value down
  int avl = (lt + ld) / 2; // average value left
  int avr = (rt + rd) / 2; // average value right

  int dvert = avt - avd; // check the diffirence of up and down
  int dhoriz = avl - avr;// check the diffirence og left and rigt
  
  
  Serial.print(avt);
  Serial.print(" ");
   Serial.println("TOP ");
  Serial.print(avd);
  Serial.print(" ");
  Serial.print("down ");
  Serial.print(" ");
  Serial.print(avl);
  Serial.print(" ");Serial.print(" left");Serial.print(" ");
  Serial.print(avr);
  Serial.print("   ");Serial.print(" right  ");Serial.print("   ");
  Serial.print(dtime);
  Serial.print("   ");
  Serial.print(tol);
  Serial.println(" ");
  
    
  if (-1*tol > dvert || dvert > tol)
  {
  if (avt > avd)
  {
    verin_1_sens1 ();
    Serial.print("m_haut"); Serial.println(" ");
     }
 
  if (avt < avd)
  {
   verin_1_sens2 ();
   Serial.print("m_bas"); Serial.println(" ");
  }

  }







  
  if (-1*tol > dhoriz || dhoriz > tol)
  {
  if (avl > avr)
  {
    
    
    
    if (digitalRead(Ils1A) == 1)
{
  
  verin_2_stop ();
  }
  else if (avl > avr)
  { 
    verin_2_sens2 ();
    Serial.print("m_left"); Serial.println(" ");
  } 
  }





  
  if (avl < avr)
  {
    if (digitalRead(Ils1A) == 0)
{
  
  verin_2_stop ();
  }
  else if (avl < avr)
  {
    verin_2_sens1 ();
    Serial.print("m_right"); Serial.println(" ");
     }
  }
  }
 
else
{ 
verin_1_stop ();
verin_2_stop ();
}
}





