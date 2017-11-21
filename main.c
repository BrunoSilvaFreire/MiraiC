#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_COMMANDS 10
#define COMMAND_LIST_HEADER "--------------------------------\n"
#define QUIT_COMMAND "quit"
#define HELP_COMMAND "help"
#define HELLO_COMMAND "hello"
#define SQUARE_AREA_COMMAND "areaDeQuadrado"
#define SQUARE_VOL_COMMAND "volDeQuadrado"
#define PRICE_OF_FILLING_AREA_COMMAND "precoPreenchimentoMaterialArea"
#define PRICE_OF_FILLING_VOLUME_COMMAND "precoPreenchimentoMaterialVolume"
#define CHILL_COMMAND "desestressar"
#define SHOW_ACTION_COMMAND "log"
#define SHOW_ALL_COMMAND "logAll"
#define LOG_FILE_NAME "log.mirai"

char *AVAILABLE_COMMANDS[TOTAL_COMMANDS] = {
        QUIT_COMMAND,
        HELP_COMMAND,
        HELLO_COMMAND,
        SQUARE_AREA_COMMAND,
        SQUARE_VOL_COMMAND,
        PRICE_OF_FILLING_AREA_COMMAND,
        PRICE_OF_FILLING_VOLUME_COMMAND,
        CHILL_COMMAND,
        SHOW_ACTION_COMMAND,
        SHOW_ALL_COMMAND
};
char *COMMANDS_DESCRIPTIONS[TOTAL_COMMANDS] = {
        "Termina a execucao de Mirai",
        "Mostra esta lista de comandos",
        "Diz ola!",
        "Calcula a area de um quadrado",
        "Calcula o volume de um quadrado",
        "Calcula o preco para preencher uma area com um material",
        "Calcula o preco para preencher um espaco com um material",
        "Abre uma porta secreta para o paraiso",
        "Mostra as ultimas acoes do usuario",
		"Mostra todas as ultimas acoes do usuario"
};
struct actionArgument {
	char * chars;
	int length;
} typedef ActionArgument;

struct action {
	long long start;
	long long end;
	int command;
} typedef Action;

Action currentAction;
Action * lastActions;
int totalActions;

Action getAction(int index) {
	return lastActions[index + 1];
}
void printAction(Action a) {
	printf("Comando executado: %d(%s)\n",a.command, AVAILABLE_COMMANDS[a.command]);
	//printf("Iniciado em: %d\n", a.start);
	//printf("Terminado em: %d\n", a.end);
}
void writeLastActions() {
	FILE * logFile = fopen(LOG_FILE_NAME, "rt+");
	if (logFile == NULL) {
		logFile = fopen(LOG_FILE_NAME, "wb");
	}
	fwrite(lastActions, sizeof(Action), totalActions, logFile);
	fclose(logFile);
}

void readLastActions() {
	FILE * logFile = fopen(LOG_FILE_NAME, "rt+");
	if (logFile == NULL) {
		printf("Couldn't find file '%s', skipping load.\n", LOG_FILE_NAME);
		logFile = fopen(LOG_FILE_NAME, "wb");
		return;
	}
	printf("Loading actions from file '%s'\n", LOG_FILE_NAME);
	int count;
	while(fgetc(logFile) != EOF) {
		count++;
	}
	rewind(logFile);
	int size = sizeof(Action);
	totalActions = count / size;
	lastActions = (Action *) malloc(sizeof(Action) * totalActions);
	fread(lastActions, size, totalActions, logFile);
	fclose(logFile);
	printf("Loaded %d actions.\n", totalActions);
}
long long getCurrentTimestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // caculate milliseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}

Action createNewAction(int id) {
	Action action = *((Action *) malloc(sizeof(Action)));
	action.start = getCurrentTimestamp();
	action.command = id;
	return action;
}

void startNewAction(int name) {
	currentAction = createNewAction(name);
}

void addToLog(Action action) {
	int newSize = totalActions +1;
	int bytes = sizeof(Action) * newSize;
	lastActions = realloc(lastActions, bytes);
	int index = newSize-1;
	lastActions[index] = action;
}
void finishAction() {
	totalActions++;
	currentAction.end = getCurrentTimestamp();
	addToLog(currentAction);
	writeLastActions();
}

void addFloatArgument(float i) {
}
void addIntArgument(int i) {
}
int readInteger() {
    int i;
    scanf("%d", &i);
    //addIntArgument(i);
    return i;
}

float readFloat() {
    float i;
    scanf("%f", &i);
    //addFloatArgument(i);
    return i;
}


float areaOfSquare(float height, float width) {
    return height * width;
}

float volumeOfSquare(float height, float width, float length) {
    return areaOfSquare(height, width) * length;
}

void printAvailableCommands() {
    printf(COMMAND_LIST_HEADER);
    int i;
    for (i = 0; i < TOTAL_COMMANDS; ++i) {
        char *command = AVAILABLE_COMMANDS[i];
        char *description = COMMANDS_DESCRIPTIONS[i];
        printf("%d - %s: %s\n", i, command, description);
    }
    printf(COMMAND_LIST_HEADER);
}


void helloCommand() {
    printf("Ola! ^_^\n");
}

void areaOfSquareCommand() {
    printf("Informe a largura do quadrado.\n");
    float width = readFloat();
    printf("Informe o comprimento do quadrado.\n");
    float length = readFloat();
    float area = areaOfSquare(width, length);
    printf("A area do quadrado e de %f u.a.\n", area);
}

void volumeOfSquareCommand() {
    printf("Informe a largura do quadrado.\n");
    float width = readFloat();
    printf("Informe o comprimento do quadrado.\n");
    float length = readFloat();
    printf("Informe a altura do quadrado.\n");
    float height = readFloat();
    float area = volumeOfSquare(height, width, length);
    printf("O volume do quadrado e de %f u.v.\n", area);
}

void priceOfSquareAreaCommand() {
    printf("Informe a largura do quadrado.\n");
    float width = readFloat();
    printf("Informe o comprimento do quadrado.\n");
    float length = readFloat();
    printf("Informe o preco por metro quadrado do material.\n");
    float price = readFloat();
    float finalPrice = areaOfSquare(width, length) * price;
    printf("O preco final sera de %f$", finalPrice);
}

void priceOfSquareVolumeCommand() {
    printf("Informe a largura do cubo.\n");
    float width = readFloat();
    printf("Informe o comprimento do cubo.\n");
    float length = readFloat();
    printf("Informe a altura do cubo.\n");
    float height = readFloat();
    printf("Informe o preco por metro cubico do material.\n");
    float price = readFloat();
    float finalPrice = volumeOfSquare(height, width, length) * price;
    printf("O preco final ssera de %f$\n", finalPrice);
}

void chillCommand() {
    printf("https://www.google.com.br/search?q=cute_kittens&tbm=isch\n");
    printf("Que a paz esteja com vc :)\n");
}
void logCommand() {
	printf("Informe o indice da acao. (Total = %d)", totalActions);
	int index = readInteger();
	if (index >= totalActions) {
		printf("Nao foi possivel encontrar uma acao com esse indice, use um numero entre 0 -> %d", totalActions - 1);
		return;
	}
	Action a = getAction(index);
	printAction(a);
}
void logAllCommand() {
	int i;
	for(i = 0; i < totalActions ; i++){
		printf("Action %d/%d\n", i+1, totalActions);
		printAction(getAction(i));
		printf("\n");
	}
}
void executeCommand(int cmd) {
    switch (cmd) {
        case 1:
            printAvailableCommands();
            break;
        case 2:
            helloCommand();
            break;
        case 3:
            areaOfSquareCommand();
            break;
        case 4:
            volumeOfSquareCommand();
            break;
        case 5:
            priceOfSquareAreaCommand();
            break;
        case 6:
            priceOfSquareVolumeCommand();
            break;
        case 7:
            chillCommand();
            break;
        case 8:
            logCommand();
            break;
        case 9:
            logAllCommand();
            break;
        default:
            printf("Eu nao conheco esse comando :/ tente um dos commando disponiveis:\n");
            printAvailableCommands();
    }
}

int main() {
	readLastActions();
    printf("Ola, eu sou a mirai! Eu sou um robo feito para facilitar a sua vida :D\n");
    printf("Eu venho com varios comandos de utilidade que voce pode utilizar, entre eles:\n");
    printf("Digite o numero de um comando para a execucao! :)\n");
    while (true) {
        printAvailableCommands();
        int cmd;
        scanf("%d", &cmd);
        if (cmd == 0) {
            break;
        }
        startNewAction(cmd);
        executeCommand(cmd);
        finishAction();
    }
    writeLastActions();
    printf("Sayounara ^_^\n");
    return 0;
}
