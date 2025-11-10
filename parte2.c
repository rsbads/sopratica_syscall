#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

int main() {
    const char *filename = "exemplo.txt";
    int fd;
    ssize_t bytes_read;
    char buffer[BUFFER_SIZE];

    // Modifica as permissões do arquivo para somente leitura
    if (chmod(filename, S_IRUSR | S_IRGRP | S_IROTH) < 0) {
        perror("Erro ao modificar permissões do arquivo");
        exit(EXIT_FAILURE);
    }

    // Abre o arquivo somente para leitura
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // Lê o conteúdo do arquivo
    bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read < 0) {
        perror("Erro ao ler o arquivo");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Adiciona um caractere nulo ao final da string lida
    buffer[bytes_read] = '\0';

    // Fecha o arquivo
    if (close(fd) < 0) {
        perror("Erro ao fechar o arquivo");
        exit(EXIT_FAILURE);
    }

    // Exibe o conteúdo do arquivo
    printf("Conteúdo do arquivo '%s':\n%s", filename, buffer);

    return 0;
}
