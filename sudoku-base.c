#include <stdio.h>

/* grid size = 9x9 */
#define SIZE 9

/* Funcao que le um grid do arquivo "filename" e o armazena em uma matriz */
int load_grid(int grid[][SIZE], char *filename) 
{
	FILE *input_file = fopen(filename, "r");

	if (input_file != NULL) {
		for(int i = 0; i < SIZE; i++)
			for(int j = 0; j < SIZE; j++)
				fscanf(input_file, "%d", &grid[i][j]);
		fclose(input_file);
		return 1;
	}

	return 0;
}

void check_rows(int grid[][SIZE]) 
{
	int flag;
	for (int i = 0; i < SIZE; i++) {
		flag = 0x0000; // Máscara binária para controle dos digitos da linha
					   // Se todos os digitos estiverem presentes, flag = 0x01FF
		for (int j = 0; j < SIZE; j++) {
			flag |= 1 << (grid[i][j] - 1);
		}
		if (flag != 0x01FF) {
			printf("Erro na linha %d\n", i + 1);
		}
	}
}

void check_collumns(int grid[][SIZE])
{
	int flag;
	for (int i = 0; i < SIZE; i++) {
		flag = 0x0000;
	}
}

int main(int argc, char *argv[]) 
{

	if(argc != 2) {
		printf("Erro: informe o arquivo de entrada!\nUso: %s <arquivo de entrada>\n\n", argv[0]);
		return 1;
	}

	/* Le o grid do arquivo, armazena na matriz grid e imprime */
	int grid[9][9];
	if(load_grid(grid, argv[1])) {
		printf("Quebra-cabecas fornecido:\n");
		for(int i = 0; i < 9; i++) {
			for(int j = 0; j < 9; j++)
				printf("%d ", grid[i][j]);
			printf("\n");
		}
		check_rows(grid);
		printf("\n");
	}

	return 0;
}
