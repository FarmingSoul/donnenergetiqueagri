// Paramètres du courant
int Courant_pin_P = A0;
int Courant_pin_N = A1;
int Val_I=0;
float courant_val_P=0.0;
float courant_val_N=0.0;
float courant_val=0.0;
float Val_shunt_R=220; // shunt du courant en Ohm

// Paramètres de la tension
float volt_val=0.0;

// Puissance
float Puissance_inst_mW=0.0;
float Pissance_moy_mW=0.0;

// All
const float Max_volt=5.0;
const float Max_ADC=1023; // 2^10 - 1
const unsigned char TailleMoy=4;
const unsigned char TailleTab=4;
unsigned char ValIndex=0;
float DataIn[TailleTab];

void setup()
{
        // Seria port
        Serial.begin(9600);
}
void loop() {

        // Mesure du courant
        Val_I = analogRead(Courant_pin_P);delay(10);
        courant_val_P=float(Val_I)*Max_volt/Max_ADC; // +

        Val_I = analogRead(Courant_pin_N);delay(10);
        courant_val_N=float(Val_I)*Max_volt/Max_ADC; // -

        courant_val=abs(courant_val_P-courant_val_N)/Val_shunt_R; // Valeur en Ampère

        // Mesure de la tension
        volt_val=analogRead(A2)*Max_volt/Max_ADC;
        //volt_val=5.0;

        // Calcul de la puissance instantannee
        Puissance_inst_mW=courant_val*volt_val;

        // Cacul de la puissance moyenne
        TabSet(TailleTab,  ValIndex, DataIn, Puissance_inst_mW);
        Pissance_moy_mW=Moyenne(TailleTab, TailleTab,  DataIn);

        if(courant_val!=0){
          //Affichage I/V
          Serial.print("\n Courant(A):");
          Serial.print(courant_val);
          Serial.print("\n Tension(V):");
          Serial.print(volt_val);
  
          //Affichage des puissances
          Serial.print("\n Puissance Inst :");
          Serial.print(Puissance_inst_mW);
          Serial.print("\n Puissance Moy :");
          Serial.print(Pissance_moy_mW);
          Serial.print("\n");
}
        // Mise à jour indice
        ValIndex=ValIndex+1;
        if (ValIndex==TailleTab)
        {
            ValIndex=0;
        }

        // Délai
        delay(200);
}

float Moyenne(unsigned char NumMean,unsigned char Taille,  float *DataIn)
{
        int i=0;
        float somme =0.0;
        for(i=0;i<NumMean; i++)
                somme+=DataIn[i];

        return somme/NumMean;
}

void TabSet(unsigned char Taille, unsigned char ValIndexTmp, float *DataIn, float ValPowIst)
{
  DataIn[ValIndexTmp]=ValPowIst;
}
