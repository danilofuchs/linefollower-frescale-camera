
//########## PINOS - NÃO ALTERAR ##########
#define CAM_CLK 3
#define CAM_SI 4
#define CAM_AOUT A5
#define MOTOR_A 5
#define MOTOR_B 6
#define BUZZER A4
#define BLUETOOTH_EN 2
#define BOTAO 7
#define LED 13


//########## PARÂMETROS FIXOS - NÃO ALTERAR ##########
#define PIXEL_ARRAY_SIZE 128
#define CAM_CLK_DELAY_US  500

#define MOTOR_A_ADJUST  100
#define MOTOR_B_ADJUST  100

//########## PARÂMETROS AJUSTÁVEIS - ALTERAR À VONTADE ##########
#define COLOR_LOGIC 0
#define CAM_LIGHT_THRESHOLD 200
#define CAM_SIDE_TRIM_PIXELS 15
#define IGNORED_PIXEL_VALUE 0
#define DELAY_BETWEEN_ITERATIONS_MS 500
#define CENTER_DEAD_ZONE_PIXELS 30

//########## VARIÁVEIS DE PROCESSO - ALTERAR À VONTADE ##########
int somaEsquerda = 0, somaDireita = 0;

//########## VARIÁVEIS NECESSÁRIAS - NÃO ALTERAR ##########
int pixelArray[PIXEL_ARRAY_SIZE];
unsigned short motorACurrentSpeed = 0, motorBCurrentSpeed = 0, globalSpeed = 100;

void setup()
{
  pinMode(CAM_CLK, OUTPUT);
  pinMode(CAM_SI, OUTPUT);
  pinMode(CAM_AOUT, INPUT);
  pinMode(MOTOR_A , OUTPUT);
  pinMode(MOTOR_B , OUTPUT);
  pinMode(BUZZER , OUTPUT);
  pinMode(BLUETOOTH_EN , OUTPUT);
  pinMode(BOTAO , INPUT);
  pinMode(LED, OUTPUT);

  Serial.begin(115200); //######DEBUG ONLY######
}

void mainLogic() //AQUI VIVE A FUNÇÃO ONDE VAMOS TRABALHAR TODA A LÓGICA DO ROBÔ
{
  somaEsquerda = 0; somaDireita = 0;
  for (int i = 0; i < PIXEL_ARRAY_SIZE / 2; i++)
  {
    somaEsquerda += pixelArray[i];
  }
  for (int i = PIXEL_ARRAY_SIZE - 1; i > PIXEL_ARRAY_SIZE / 2; i--)
  {
    somaDireita += pixelArray[i];
  }
  Serial.print("Soma Esquerda: "); Serial.print(somaEsquerda); Serial.print("\t"); Serial.print("Soma Direita: "); Serial.print(somaDireita); Serial.print("\n"); //######DEBUG ONLY######

  if (somaDireita < somaEsquerda - CENTER_DEAD_ZONE_PIXELS / 2)
  {
    motorACurrentSpeed = 0;
    motorBCurrentSpeed = 100;
  }

  else if (somaDireita > somaEsquerda + CENTER_DEAD_ZONE_PIXELS / 2)
  {
    motorACurrentSpeed = 100;
    motorBCurrentSpeed = 0;
  }

  else
  {
    motorACurrentSpeed = 100;
    motorBCurrentSpeed = 100;
  }

  //  motorACurrentSpeed = map(somaEsquerda,0, somaEsquerda,0,100);
  //  motorBCurrentSpeed = map(somaDireita,0, somaDireita,0,100);
}


void loop()
{
  readCamera(); //lê valores crus da câmera
  filterCamera(); //filtra valores lidos
  mainLogic(); //toma as decisões necessárias e atualiza as velocidades dos motores
  moveMotors(motorACurrentSpeed * globalSpeed / 100, motorBCurrentSpeed * globalSpeed / 100); //envia os valores atualizados aos motores
  delay(DELAY_BETWEEN_ITERATIONS_MS);
}

void filterCamera() //CHAMAR ESTA FUNÇÃO QUANDO DESEJAR FILTRAR O SINAL DA CÂMERA
{
  for (int i = 0; i <= CAM_SIDE_TRIM_PIXELS; i++) pixelArray[i] = IGNORED_PIXEL_VALUE; //joga valores do lado esquerdo da câmera para o valor intermediario definido
  for (int i = PIXEL_ARRAY_SIZE - 1; i >= PIXEL_ARRAY_SIZE - CAM_SIDE_TRIM_PIXELS - 1; i--) pixelArray[i] = IGNORED_PIXEL_VALUE; //joga valores do lado direito da câmera para o valor intermediario definido

  for (int i = 0; i < PIXEL_ARRAY_SIZE; i++)
  {
    if (pixelArray[i] > CAM_LIGHT_THRESHOLD) pixelArray[i] = !COLOR_LOGIC;
    else pixelArray[i] = COLOR_LOGIC;
  }

  //ADICIONAR MAIS TÉCNICAS DE FILTRAGEM AQUI


  //  for (int i = 0; i < PIXEL_ARRAY_SIZE; i += 6)                 //######DEBUG ONLY###### //mostra na serial o valor da câmera a cada 6 pixels (pra caber na tela)
  //  { //######DEBUG ONLY######
  //
  //    Serial.print(pixelArray[i]);                                //######DEBUG ONLY######
  //    Serial.print(" ");                                          //######DEBUG ONLY######
  //  }                                                             //######DEBUG ONLY######
  //  Serial.print("\n");                                         //######DEBUG ONLY######
}

void readCamera() //CHAMAR ESTA FUNÇÃO QUANDO QUISER VALROES ATUALIZADOS DA CÂMERA
{
  // while(digitalRead(BOTAO) != HIGH) {} //######DEBUG ONLY###### só lê a câmera uma vez quando apertamos o botão

  digitalWrite(CAM_SI, HIGH);
  delayMicroseconds(CAM_CLK_DELAY_US / 2);

  for (int i = 0; i < PIXEL_ARRAY_SIZE; i++)
  {
    digitalWrite(CAM_CLK, HIGH);
    delayMicroseconds(CAM_CLK_DELAY_US / 2);
    digitalWrite(CAM_SI, LOW);
    delayMicroseconds(CAM_CLK_DELAY_US / 2);
    digitalWrite(CAM_CLK, LOW);
    delayMicroseconds(CAM_CLK_DELAY_US / 2);
    pixelArray[i] = analogRead(CAM_AOUT);
    delayMicroseconds(CAM_CLK_DELAY_US / 2);
  }

  //  for(int i=0;i<PIXEL_ARRAY_SIZE;i+=6)                          //######DEBUG ONLY###### //mostra na serial o valor da câmera a cada 6 pixels (pra caber na tela)
  //  {                                                             //######DEBUG ONLY######
  //
  //    Serial.print(pixelArray[i]);                                //######DEBUG ONLY######
  //    Serial.print(" ");                                          //######DEBUG ONLY######
  //  }                                                             //######DEBUG ONLY######
  //    Serial.print("\n");                                         //######DEBUG ONLY######
}

void moveMotors(byte speedA, byte speedB)
{
  float speedAConverted = map(((speedA * MOTOR_A_ADJUST) / 100), 0, 100, 0, 255);
  float speedBConverted = map(((speedB * MOTOR_B_ADJUST) / 100), 0, 100, 0, 255);

  analogWrite(MOTOR_A, (unsigned byte)speedAConverted);
  analogWrite(MOTOR_B, (unsigned byte)speedBConverted);
}
