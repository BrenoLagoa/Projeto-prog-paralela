#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void swap(); //declara a função de troca

int main () {
	int TAM =10000;	//determina o tamanho do vetor
	int numeros[TAM];		//cria o vetor
	
	for(int k=0; k<10; k++){	//loop para executar a ordenação 10 vezes

		for(int i= 0; i<TAM; i++){	// loop para inserir valores aleatorios no vetor 
		    numeros[i] = rand()%TAM;
		}

		int i=0, j=0; //declara as variaveis para os laços
		int first;	//declara a variavel que determina por qual item o segundo laço irá começar

		double start,end;	//cria a varavel double de marcação de tempo
		start=omp_get_wtime(); //insere o tempo inicial na variavel

		for( i = 0; i < TAM-1; i++ ){ 	// loop que percorre todo o vetor

			first = i % 2; //insere o valor de onde o segundo laço deve começar, através da divisão inteira de i por 2, logo sempre proximo da metade de i
			#pragma omp parallel for default(none),shared(numeros,first,TAM) 	//marca no codigo a fim de demonstrar ao compilador onde pode ser paralelizado
			
			for( j = first; j < TAM-1; j += 1 ){	//loop que se inicia a partir da variável first, a fim de evitar passagens por posições já ordenadas

				if( numeros[ j ] > numeros[ j+1 ] ){ 	//condição caso o item seguinte seja maior que o anterior

					swap( &numeros[ j ], &numeros[ j+1 ] );	//função para a troca dos valores
				
				}
			}
		}


		printf("Time Parallel(exec %d)= %f \n", k+1, (omp_get_wtime()-start)); //imprime qual execução está o codigo e o tempo levado

    }
}

void swap(int *num1, int *num2){	//função de troca de posições dos valores

	int temp = *num1;	//cria um temporario que recebe o valor da posição i
	*num1 =  *num2;		//passa o valor da posição i+1 para a posição i
	*num2 = temp;		//passa o valor salvo no temporario para a posição i+1
}