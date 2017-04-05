#include <stdio.h>
#include <math.h>

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
	for (int j = 0; j < SIZE; j++) {
		flag = 0x0000;
		for (int i = 0; i < SIZE; i++) {
			flag |= 1 << (grid[i][j] - 1);
		}
		if (flag != 0x01FF) {
			printf("Erro na coluna %d\n",j + 1);
		}
	}
}

void check_quadrants(int grid[][SIZE])
{
	int flag, si, sj, i, j;
	int quadrant_size = (int) sqrt(SIZE);
	for (si = 0; si < quadrant_size; si++) {
		for (sj = 0; sj < quadrant_size; sj++) {
			flag = 0x0000;
			for (i = 0; i < quadrant_size; i++) {
				for (j = 0; j < sqrt(SIZE); j++) {
					flag |= 1 << (grid[si * quadrant_size + i][sj * quadrant_size + j] - 1);
				}
			}
			if (flag != 0x01FF) {
				printf("Erro no quadrante %d, %d\n", si * quadrant_size + i - 1, sj * quadrant_size + j - 1);			
			}
		}
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
		check_collumns(grid);
		check_quadrants(grid);
		printf("\n");
	}

	return 0;
}
