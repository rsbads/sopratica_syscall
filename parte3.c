#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    const char *filename = "exemplo.txt";
    const char new_text[38] = "Tentativa de modificar o arquivo.\n";
    int fd;
    ssize_t bytes_written;

    // Tenta abrir o arquivo em modo de escrita
    fd = open(filename, O_WRONLY);
    if (fd < 0) {
        perror("Erro ao abrir o arquivo para escrita");
        printf("Não é possível modificar o arquivo '%s' porque ele está em modo somente leitura.\n", filename);
        exit(EXIT_FAILURE);
    }

    // Tenta escrever no arquivo
    bytes_written = write(fd, new_text, sizeof(new_text) - 1);
    if (bytes_written < 0) {
        perror("Erro ao escrever no arquivo");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Fecha o arquivo
    if (close(fd) < 0) {
        perror("Erro ao fechar o arquivo");
        exit(EXIT_FAILURE);
    }

    printf("Texto foi escrito no arquivo '%s' com sucesso (não deveria ter sido possível)!\n", filename);

    return 0;
}
