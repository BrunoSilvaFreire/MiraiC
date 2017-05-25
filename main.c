#include <stdio.h>
#include <conio.h>
#include "commands.c"

#define BUZZ_SIZE 2048

char *readFace();

void debug(char string[98]);

/**
 *
 * @return Uma string com
 */
char *getAvailableCommands() {
    return "hello.";
}

int main() {
    //Ler arquivo da face da Mirai
    char *miraiFace = readFace();
    printf(miraiFace);
    printf("\n");

    //Introdução
    printf("Ola, eu sou a mirai! Eu sou um robo feito para facilitar a sua vida :D\n");
    printf("Eu venho com varios comandos de utilidade que voce pode utilizar, entre eles:\n");
    char *comandosDisponiveis = getAvailableCommands();
    printf(comandosDisponiveis);
    return 0;
}

/**
 * Procura por um arquivo que se chame
 * @return
 */
char *readFace() {
    char buff[BUZZ_SIZE];
    FILE *f = fopen("mirai.txt", "r");
    if (f == NULL) {
        debug("Nao foi possivel encontrar um arquivo com a face de Mirai! Usando face padrao nada interessante.\n");
        return ":D";
    }
    printf(f->_base);
    fgets(buff, BUZZ_SIZE, f);
    return buff;
}

void debug(char *string) {
    printf("[DEBUG] ");
    printf(string);
}
