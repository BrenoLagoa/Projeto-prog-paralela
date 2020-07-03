#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int TAM = 10000;     //determina o tamanho do vetor
int main(){

    int i,j,temp;  //cria as variaveirs auxiliares
    int numeros[TAM];       //cria o vetor de tamanho TAM
    
   for(int k=0; k<10; k++){  //loop para realizar as 10 execuções

        for(int i= 0; i<TAM; i++){    //loop para preencher o vetor com valores aleatorios
               numeros[i] = rand()%TAM;
        }


        double start_time;  //cria a variavel que marca o tempo inicial
        start_time = omp_get_wtime();   //atribui valor a varivale marcadora de inicio

           
        for(i=0;i<TAM;i++){   //loop para percorrer o vetor 
            if(i%2==0){     //confere se o número é par
                #pragma omp parallel for private(temp,j) shared(numeros)  //cria uma fila compartilhando o vetor 'numeros' e criando os temporarios 'temp' e 'j'
                for(j=0;j<TAM-1;j+=2){        //loop que percorre o vetor de dois em dois a fim de criar a possibilidade de um pipeline
                    if(numeros[j]> numeros[j+1]){       //compara se o termo numeros[j] é maior que o seu seguinte caso verdadeiro se realiza a troca
                        temp = numeros[j];        //passa numeros[j] para um temporario
                        numeros[j] = numeros[j+1];      //passa numeros[j+1] para numeros[j]
                        numeros[j+1] = temp;      //passa o valor do temporario para numeros[j+1] 
                    }
                }
            }else{      //caso seja ímpar
                #pragma omp parallel for private(temp,j) shared(numeros)  //cria uma fila compartilhando o vetor 'numeros' e criando os temporarios 'temp' e 'j' 
                for(j=1;j<TAM-1;j+=2){        //loop que percorre o vetor de dois em dois a fim de criar a possibilidade de um pipeline
                    if(numeros[j]> numeros[j+1]) {      //compara se o termo numeros[j] é maior que o seu seguinte caso verdadeiro se realiza a troca
                        temp = numeros[j];        //passa numeros[j] para um temporario
                        numeros[j] = numeros[j+1];      //passa numeros[j+1] para numeros[j]
                        numeros[j+1] = temp;      //passa o valor do temporario para numeros[j+1]
                    }
                }
            }
               
        }

        printf("Execution %d, time = %lf seconds\n", k+1 ,omp_get_wtime() - start_time);  //imprime o número da execução e quanto tempo levou para ordenar o vetor
    }

}
