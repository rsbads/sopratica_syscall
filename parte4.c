#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


int main() {
   const char *filename = "exemplo.txt";
   const char new_text[38] = "O arquivo foi modificado com sucesso!\n";
   int fd;
   ssize_t bytes_written;


   // Modifica as permissões do arquivo para leitura e escrita
   if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0) {
       perror("Erro ao modificar permissões do arquivo");
       exit(EXIT_FAILURE);
   }


   // Abre o arquivo em modo de escrita
   fd = open(filename, O_WRONLY | O_APPEND);
   if (fd < 0) {
       perror("Erro ao abrir o arquivo para escrita");
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


   printf("Texto foi escrito no arquivo '%s' com sucesso!\n", filename);


   return 0;
}
