float etatv = 0;
int pin = 2;
float pri = 0;

void setup(){
  Serial.begin(9600);       // Initialisation de la COM série pour afficher directement le résultat sur le PC.
  pinMode(pin, INPUT_PULLUP);
  pinMode(A3, INPUT);
  
}

void loop(){
  etatv = (analogRead(3)*5.0/1023);  // Lit l'état de la broche 2.
  if (etatv!=0.00){
    Serial.println(etatv);  // Affiche l'état dans le moniteur série sur le PC.
  }
  delay(30);
  // Un délais court pour nous laisser le temps de lire l'état dans le moniteur série.
  
}
