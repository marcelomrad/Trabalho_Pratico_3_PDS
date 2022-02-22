#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TMAX 16

typedef struct 
{
    int posicao_x;
    int posicao_y;
    int movimentos;

}Vetor;

void LerTabuleiro(int tamanho_tab, char tabuleiro[TMAX][TMAX]) //FUNÇAO PARA LER TABULEIRO
{
    for (int i = 0; i < tamanho_tab; i++)
    {
        fgets(tabuleiro[i], TMAX, stdin);
    }
}

void CopiaTabuleiro(int tamanho_tab, char recebe[TMAX][TMAX], char copia[TMAX][TMAX]) //FUNÇÃO PARA PASSAR PRO TABULEIRO A SUA COPIA
{
    for(int i = 0; i < tamanho_tab; i++)
    {
        for(int j = 0; j < tamanho_tab; j++)
        {
          recebe[i][j] = copia[i][j];  
        }   
    }
}

int MelhorJogada(char tabuleiro[TMAX][TMAX], int x, int y, int *contador, int *contador_max) //FUNÇAO PARA IMPLEMENTAR MELHOR JOGADA
{   
    //comer pra baixo/esquerda
    if(tabuleiro[x+1][y-1] == 'p' && tabuleiro[x+2][y-2] == 'o')
    {
        //casa com peça preta recebe valor vazio
        tabuleiro[x+1][y-1] = 'o'; 

        //casa que sai a peça branca recebe valor vazio
        tabuleiro[x][y] = 'o';

        //casa vazia recebe peça branca
        tabuleiro[x+2][y-2] = 'b';

        (*contador)++;
        
        
        //chamada da função de recursão
        MelhorJogada(tabuleiro, x+2, y-2, contador, contador_max);

        //tirando contador na hora de voltar o caminho da recursão 
        (*contador)--;
            
        //evitando erro na bifurcação de teste de qual melhor caminho a seguir
        tabuleiro[x+1][y-1] = 'p';
    }
    //comer pra cima/esquerda
    if(tabuleiro[x-1][y-1] == 'p' && tabuleiro[x-2][y-2] == 'o') 
    {
        //casa com peça preta recebe valor vazio
        tabuleiro[x-1][y-1] = 'o'; 

        //casa que sai a peça branca recebe valor vazio
        tabuleiro[x][y] = 'o';

        //casa vazia recebe peça branca
        tabuleiro[x-2][y-2] = 'b';  

        (*contador)++;
        
        
        //chamada da função de recursão
        MelhorJogada(tabuleiro, x-2, y-2, contador, contador_max);

        //tirando contador na hora de voltar o caminho da recursão 
        (*contador)--;
        
        //evitando erro na bifurcação de teste de qual melhor caminho a seguir
        tabuleiro[x-1][y-1] = 'p';
    }
    //comer pra baixo/direita
    if(tabuleiro[x+1][y+1] == 'p' && tabuleiro[x+2][y+2] == 'o') 
    {  
        //casa com peça preta recebe valor vazio
        tabuleiro[x+1][y+1] = 'o'; 

        //casa que sai a peça branca recebe valor vazio
        tabuleiro[x][y] = 'o';

        //casa vazia recebe peça branca
        tabuleiro[x+2][y+2] = 'b'; 

        (*contador)++;
        
       

        //chamada da função de recursão
        MelhorJogada(tabuleiro, x+2, y+2, contador, contador_max);
        
        //tirando contador na hora de voltar o caminho da recursão 
        (*contador)--;
            
        //evitando erro na bifurcação de teste de qual melhor caminho a seguir
        tabuleiro[x+1][y+1] = 'p';
    }
    //comer pra cima/direita
    if(tabuleiro[x-1][y+1] == 'p' && tabuleiro[x-2][y+2] == 'o') 
    {
        //casa com peça preta recebe valor vazio
        tabuleiro[x-1][y+1] = 'o'; 

        //casa que sai a peça branca recebe valor vazio
        tabuleiro[x][y] = 'o';

        //casa vazia recebe peça branca
        tabuleiro[x-2][y+2] = 'b';  

        (*contador)++;
        
        
    
        //chamada da função de recursão
        MelhorJogada(tabuleiro, x-2, y+2, contador, contador_max);

        //tirando contador na hora de voltar o caminho da recursão 
        (*contador)--;

        //evitando erro na bifurcação de teste de qual melhor caminho a seguir
        tabuleiro[x-1][y+1] = 'p';
    }
    
    //comparando os caminhos da recursão e separando o contador do caminho que tiver comido mais peças
    if(*contador > *contador_max)
        *contador_max = *contador;

    //evitando problema na hora da peça voltar o caminho da bifurcação
    tabuleiro[x][y] = 'o';
    
    return 0;
}

void PrintarMaior(int tamanho_vetor, Vetor *vetor) //FUNÇAO PARA PRINTAR A PEÇA QUE MAIS COME
{
    int aux_maior = 0;
    for (int i = 0; i < tamanho_vetor; i++)
    {
        if(vetor[i].movimentos > aux_maior)
            aux_maior = vetor[i].movimentos;
    }

    for (int i = 0; i < tamanho_vetor; i++)
    {
        if(vetor[i].movimentos == aux_maior)
        {
            printf("%d %d %d\n",vetor[i].posicao_x,vetor[i].posicao_y, vetor[i].movimentos);
            break;
        }
    }
             
}

void PrintarPecas(int tamanho_vetor, Vetor *vetor) //FUNÇÃO PARA PRINTAR AS PEÇAS QUE COMEM PELO MENOS UMA
{
    for (int i = 0; i < tamanho_vetor; i++)
    {   
         printf("%d %d %d\n",vetor[i].posicao_x,vetor[i].posicao_y, vetor[i].movimentos);
    }
}

int main(){

    //receber variaveis para leitura tabuleiro
    int tamanho_tab;
    char entrada[TMAX];
    fgets(entrada, TMAX, stdin);
    sscanf(entrada, "%d" , &tamanho_tab);
    char tabuleiro[TMAX][TMAX];

    //variaveis para auxiliar a contagem de movimentos, maior numero de movimentos e posição da struct
    int contador = 0;
    int contador_max = 0;
    int cont_vetor = 0;

    //struct para receber posição e numero de movimentos
    Vetor vetor[100];

    //variavel para auxiliar na copia do tabuleiro
    char aux[TMAX][TMAX];

    LerTabuleiro(tamanho_tab, tabuleiro);

    //fazer uma copia do tabuleiro para o auxiliar
    CopiaTabuleiro(tamanho_tab, aux, tabuleiro);
    

  //Testando as peças do tabuleiro para ver se é branca, caso seja executa o algoritmo para definir numero de peças capturadas
   for(int i = 0; i < tamanho_tab; i++)
    {   
        //ordenar de acordo com os testes
        if(i % 2 == 0) 
        {
            for(int j = 0; j < tamanho_tab; j++)
            {
                //passando a copia do tabuleiro
                CopiaTabuleiro(tamanho_tab,tabuleiro,aux);

                if(tabuleiro[i][j] == 'b')
                {   

                    //chamando função para executar os movimentos
                    MelhorJogada(tabuleiro,i,j, &contador, &contador_max);

                    //recebendo as coordenadas e o numero de movimentos
                    if(contador_max >= 1)
                    {
                        vetor[cont_vetor].posicao_x = i;
                        vetor[cont_vetor].posicao_y = j;
                        vetor[cont_vetor].movimentos = contador_max;
                        cont_vetor++;
                    }
                   
                    //zerando o contador para a proxima peça
                    contador_max = 0;
                } 
            }   

        }else{
            for(int j = tamanho_tab-1; j >= 0; j--)
            {
                //passando copia tabuleiro
                CopiaTabuleiro(tamanho_tab,tabuleiro,aux);

                if(tabuleiro[i][j] == 'b')
                {   
                   
                    //chamando função para executar os movimentos
                    MelhorJogada(tabuleiro,i,j, &contador, &contador_max);

                    //recebendo as coordenadas e o numero de movimentos
                    if(contador_max >= 1)
                    {
                        vetor[cont_vetor].posicao_x = i;
                        vetor[cont_vetor].posicao_y = j;
                        vetor[cont_vetor].movimentos = contador_max;
                        cont_vetor++;
                    }

                    //zerando o contador para a proxima peça
                    contador_max = 0;  
                }  
            }   
        }   
    } 
    
    //printar o as coordenadas e os movimentos da peça que mais come
    PrintarMaior(cont_vetor, vetor);

    //printar os resultados
    PrintarPecas(cont_vetor, vetor);
    
    EXIT_SUCCESS; 
} 
