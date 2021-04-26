#include <PID_v1.h>

const int LM35 = A0; // Define o pino que lera a saída do LM35
const int cooler = A1;
float temperatura; // Variável que armazenará a temperatura medida
double Setpoint = 15, Input, Output;
double TSetpoint = Setpoint * 0.01;
float tensao;
float leitura;
double erro;

double Kp = 3, Ki = 3, Kd = 1;

PID pid(&Input, &Output, &Setpoint, Kp, Ki, Kd, REVERSE);

void setup() {
  Serial.begin(9600); // inicializa a comunicação serial
  pid.SetMode(AUTOMATIC);
  pid.SetTunings(Kp, Ki, Kd);

}

//Função que será executada continuamente
void loop(){

  leitura = analogRead(LM35);
  tensao = (float(leitura) * 5 / (1023));
  temperatura = tensao / 0.01;
  
  erro =  double(temperatura) - Setpoint;

  Input = map(leitura , 0, 1024, 0, 255);
  pid.Compute();

  analogWrite(cooler , Output);

  Serial.print("Temperatura: ");
  Serial.println(temperatura);
  Serial.print("Tensao: ");
  Serial.println(tensao);
  Serial.print("PID: ");
  Serial.println(Output);
  delay(500);
}
