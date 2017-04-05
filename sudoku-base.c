#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <stdlib.h>

/* grid size = 9x9 */
#define SIZE 9

int puzzle[SIZE][SIZE];

typedef struct {
	size_t start, end;
	pthread_t tid;
} work;

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


void check_rows(void * arg) 
{
	work * current_thread = (work *) arg;
	int flag;
	printf("Thread %lu: Verificando linhas %u à %u\n",pthread_self(), current_thread->start, current_thread->end);
	for (int i = current_thread->start; i < current_thread -> end; i++) {
		flag = 0x0000; // Máscara binária para controle dos digitos da linha
					   // Se todos os digitos estiverem presentes, flag = 0x01FF
		for (int j = 0; j < SIZE; j++) {
			flag |= 1 << (puzzle[i][j] - 1);
		}
		if (flag != 0x01FF) {
			printf("Thread %lu: Erro na linha %d\n",pthread_self(), i + 1);
		}
	}
}

void check_collumns(void * arg)
{

	work * current_thread = (work *) arg;
	printf("Thread %lu: Verificando colunas %u à %u\n",pthread_self(), current_thread->start, current_thread->end);
	int flag;
	for (int j = current_thread->start; j < current_thread -> end; j++) {
		flag = 0x0000;
		for (int i = 0; i < SIZE; i++) {
			flag |= 1 << (puzzle[i][j] - 1);
		}
		if (flag != 0x01FF) {
			printf("Thread %lu: Erro na coluna %d\n",pthread_self(), j + 1);
		}
	}
}

// TODO: distribuir quadrados entre as threads
// void check_quadrants(void * arg)
// {
// 	work * current_thread = (work *) arg;
// 	int start = current_thread -> start;
// 	int end = current_thread -> end;
// 	printf ("Thread %lu: Start: %u, end: %u\n",pthread_self(), start, end);
// 	int flag, si, sj, i, j;
// 	int quadrant_size = (int) sqrt(SIZE);	
// 	for (si = start; si < quadrant_size; si++) {
// 		for (sj = start; sj < quadrant_size; sj++) {
// 			flag = 0x0000;
// 			for (i = 0; i < quadrant_size; i++) {
// 				for (j = 0; j < quadrant_size; j++) {
// 					flag |= 1 << (puzzle[si * quadrant_size + i][sj * quadrant_size + j] - 1);
// 				}
// 			}
// 			if (flag != 0x01FF) {
// 				// printf("Thread %lu: Erro no quadrante %d, %d\n", pthread_self(), si + 1 , sj + 1);			
// 			}
// 		}
// 	}
// }


void * verify_puzzle(void * arg) {
	
	work * current_thread = (work *) arg;
	check_rows(arg);
	check_collumns(arg);
	//check_quadrants(arg);
}


int main(int argc, char *argv[]) 
{

	if(argc != 3) {
		printf("Erro: informe o arquivo de entrada, e o numero de threads!\nUso: %s <arquivo de entrada> <numero de threads>\n\n", argv[0]);
		return 1;
	}
	if(!atoi(argv[2])) {
		printf("Erro: informe o arquivo de entrada, e o numero de threads!\nUso: %s <arquivo de entrada> <numero de threads>\n\n", argv[0]);
		return 1;
	}
	int nthreads = atoi(argv[2]);
	work threads[nthreads];
	size_t index_start, index_end, index_n = SIZE / nthreads + SIZE % nthreads;
	index_start = 0;
	index_end = index_start + index_n;
	if(load_grid(puzzle, argv[1])) {
		printf("Quebra-cabecas fornecido:\n");
		for(int i = 0; i < SIZE; i++) {
			for(int j = 0; j < SIZE; j++)
				printf("%d ", puzzle[i][j]);
			printf("\n");
		}
		for (size_t i = 0; i < nthreads; i++) {
			// printf("Index start: %d, index_end: %d, index_n: %d\n", index_start, index_end, index_n);

			threads[i].start = index_start;
			threads[i].end = index_end;

			pthread_create(&threads[i].tid, NULL, verify_puzzle, (void*)&threads[i]);
			index_start = index_end;
			index_end =  (index_end + index_n < SIZE ? index_end + index_n : SIZE);
		}
		for (size_t i = 0; i < nthreads; i++) {
			pthread_join(threads[i].tid, NULL);
		}
		printf("\n");
	}

	return 0;
}
