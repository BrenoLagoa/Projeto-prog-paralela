#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define TAM 100000  //tamanho do vetor

int main(){


int aux, troca, numero[TAM];	//declaração das variáveis e do vetor
   

	
	for(int r =0; r<10; r++){  //loop para executar 10 vezes o algoritmo
		

		for(int i= 0; i<TAM; i++){		//insere valores aleatórios no vetor 
		    numero[i] = rand()%TAM;
		}
		troca = 1;

		double start_time;	//cria uma variável double para demarcar o tempo inicial
		start_time = omp_get_wtime();	//salva o tempo que se iniciou

	    while (troca == 1){		//loop que acaba quando a flag assumir valor 0, mostrando que não há mais trocas necessárias
	        troca = 0; //muda o valor da flag

	        for (int i = 0; i < TAM; i++){	//loop que percorre o vetor

	            if (numero[i] > numero[i + 1]){	//confere se o a posiçaõ seguinte é menor que o valor da posição i

	                troca = 1;	//muda o valor da flag se entrar nessa condição
	                aux = numero[i];	//passa o valor para a auxiliar
	                numero[i] = numero[i + 1];	//passa o valor da posição i+1 para a posição i
	                numero[i + 1] = aux;	//passa o valor da auxiliar para a posição i+1
	            }
	        }
	    }

	    
	    printf(" Execution(%d) time = %lf seconds\n" , r+1, omp_get_wtime() - start_time);	//imprime o numero da execução e o tempo que levou
	    
 	}
}
