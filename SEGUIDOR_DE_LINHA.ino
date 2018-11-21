//Definições de Hardware
#define PINO_MOTOR_ESQUERDA  0
#define PINO_MOTOR_DIREITA  0
#define PINO_SENSOR_DADOS 0
#define PINO_SENSOR_CLOCK 0

//Parâmetros Motor (%)
#define MIN_SPEED_ESQUERDA  0
#define MIN_SPEED_DIREITA   0

#define MAX_SPEED_ESQUERDA  0
#define MAX_SPEED_DIREITA   0

//Parâmetros Sensor (%)
#define MIN_SENSOR_VALID  0
#define MAX_SENSOR_VALID  0


//Parâmetros PID
#define KP  0
#define KD  0
#define KI  0

unsigned char speedEsquerda = 0, speedDireita = 0;



void leSensor(void); //Lê array da câmera ****EVERTON->DANILO: Vai ter que usar um ponteiro aqui pra apontar pro array que vai ser retornado, certo?
void movimenta(unsigned char esquerda, unsigned char direita); //recebe potência/velocidade (%) para os motores da esquerda e da direita

void setup() 
{
//Configura pinos como saidas ou entradas
pinMode(PINO_MOTOR_ESQUERDA,OUTPUT);
pinMode(PINO_MOTOR_DIREITA,OUTPUT);
pinMode(PINO_SENSOR_DADOS,INPUT);
pinMode(PINO_SENSOR_CLOCK,OUTPUT);

//Serial.begin(38400); //Inicializa Serial na frequência do módulo bluetooth //SEMPRE COMENTAR SERIAL ANTES DE TOMADA DE TEMPO!
}

void loop() 
{
  
//RECEBE INFORMAÇÃO DA CÂMERA  
leSensor();


//##################################LOGICA PRINCIPAL VAI AQUI##########################


//MOVIMENTA O ROBÔ DE FATO
movimenta(speedEsquerda,speedDireita);
//Serial.print(speedEsquerda);Serial.print("\t");Serial.print(speedDireita);Serial.print("\n"); //SEMPRE COMENTAR SERIAL ANTES DE TOMADA DE TEMPO!

}

void leSensor(void)
{
  
}

void movimenta(unsigned char velocEsquerda, unsigned char velocDireita)
{

//Filtra os valores máximos e mínimos das velocidades
if (velocEsquerda < MIN_SPEED_ESQUERDA) velocEsquerda = MIN_SPEED_ESQUERDA;
else if (velocEsquerda > MAX_SPEED_ESQUERDA) velocEsquerda = MAX_SPEED_ESQUERDA;
if (velocDireita < MIN_SPEED_DIREITA) velocDireita = MIN_SPEED_DIREITA;
else if (velocDireita > MAX_SPEED_DIREITA) velocDireita = MAX_SPEED_DIREITA;

//converte de porcentagem para "Analogico255"
map(velocEsquerda,0,100,0,255); 
map(velocDireita,0,100,0,255);


//##################################COMANDOS PARA MOVIMENTAR O ROBÔ INSERIDOS AQUI #################################
  
}
