#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


int main() {
   const char *filename = "exemplo.txt";
   const char text[35] = "Ola, este eh um texto de exemplo.\n";
   int fd;
   ssize_t bytes_written;


   // Cria o arquivo com permissões rw-r--r--
   fd = creat(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
   if (fd < 0) {
       perror("Erro ao criar o arquivo");
       exit(EXIT_FAILURE);
   }


   // Escreve texto no arquivo
   bytes_written = write(fd, text, sizeof(text) - 1);
   if (bytes_written < 0) {
       perror("Erro ao escrever no arquivo");
       close(fd);
       exit(EXIT_FAILURE);
   }
   printf("Foram escritos '%i' bytes!\n", bytes_written);


   // Fecha o arquivo
   if (close(fd) < 0) {
       perror("Erro ao fechar o arquerivo");
       exit(EXIT_FAILURE);
   }


   printf("Arquivo '%s' criado e texto adicionado com sucesso!\n", filename);


   return 0;
}
