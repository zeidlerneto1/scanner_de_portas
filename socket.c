#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close

struct sockaddr_in destino;

int main(int argc, char *argv[]){
	if (argc != 4){
		printf("Uso: %s <IP> <Porta_Incial> <Porta_Final>\n", argv[0]);
		return 1;
	}
	char *ip = argv[1];
	int port_inicio= atoi(argv[2]);
	int port_fim= atoi(argv[3]);

	FILE *arquivo = fopen("resultado.txt", "w");
	if(arquivo == NULL){
		perror("Erro ao abrir arquivo");
		return 1;
	}

	for(int port = port_inicio; port <= port_fim; port++){
		int e_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (e_socket < 0)
		{
			perror("Erro ao criar socket");
			continue;
		}

		destino.sin_family = AF_INET;
		destino.sin_port = htons(port);
		destino.sin_addr.s_addr = inet_addr(ip);
		bzero(&(destino.sin_zero), 8);

		int conexao = connect(e_socket, (struct sockaddr *)&destino, sizeof(destino));


        if (conexao == 0) {
            printf("Porta %d aberta\n", port);
            fprintf(arquivo, "Porta %d aberta\n", port);
        }

        close(e_socket);
		}

		fclose(arquivo);
		printf("Scan finalizado. Resultados em resultado.txt\n");

return 0;
}
