#include <stdio.h>
#include <stdlib.h>

int testados[363000];
int resolucao[1000];
unsigned int nm_testes = 0;
int max_niveis;
int max_tentativas;

void mostraresultado(){
    printf("Solucao\n\n");
    for (int i=0;i<=max_niveis;i++){
        printf("Passo %d:\n",i);
        int valor = resolucao[i];
        if(valor >0){
            for (int j=0;j<3;j++){
                for (int k=0;k<3;k++) {
                    printf("%2d ",valor % 10); ;
                    valor = valor/10;
                }
                printf("\n");
            }
        }

    }
}

int achaLinha(int tab[3][3]){
    int i,j;
    for (i=0;i<3;i++){
        for (j=0;j<3;j++)
            if(tab[i][j] == 0){
            return i;
        }
    }
}

int achaColuna(int tab[3][3]){
    int i,j;
    for (i=0;i<3;i++){
        for (j=0;j<3;j++)
            if(tab[i][j] == 0){
                return j;
            }
    }
}

int final(int tabela[3][3]){
    if(tabela[0][1]==1 && tabela[0][2]==2 && tabela[1][0]==3 && tabela[1][1]==4 && tabela[1][2]==5 && tabela[2][0]==6 && tabela[2][1]==7 && tabela[2][2]==8)
        return 1;

    return 0;

}

unsigned int montavalor (int tab[3][3]){
    unsigned int valor =0;
    for(int i=2;i>=0;i--){
        for(int j=2;j>=0;j--){
            valor = valor*10+tab[i][j];
        }
    }
    return valor;
}

void gravajogada(int tab[3][3]){
    testados[nm_testes]=  montavalor(tab);
    nm_testes++;
}

void gravaresulado(int tab[3][3],int nivel){
    resolucao[nivel] = montavalor(tab);
}

int testajogada(int tab[3][3]){
    unsigned int valor = montavalor(tab);
    for(int i=0;i<=nm_testes;i++){
        if(valor == testados[i])return 1;
    }
    return 0;
}

int validatab(int tab[9]){
    for(int i=0;i<8;i++) {
        int val = tab[i];
        for(int j=i+1;j<9;j++){
            if(val == tab[j]){
                return -1;
            }
        }
    }
}

int back(int tabela[3][3],int nivel, int linha_origem, int coluna_origem, int linha_troca,int coluna_troca) {
    int tab[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tab[i][j] = tabela[i][j];
        }
    }
    if (linha_origem < 0 || linha_origem > 2 ||
        linha_troca < 0 || linha_troca > 2 ||
        coluna_origem < 0 || coluna_origem > 2 ||
        coluna_troca < 0 || coluna_troca > 2) return 0;
    if (tab[linha_origem][coluna_origem] != 0) return 0;
    if (nivel > max_tentativas) return 0;

    int aux = tab[linha_origem][coluna_origem];
    tab[linha_origem][coluna_origem] = tab[linha_troca][coluna_troca];
    tab[linha_troca][coluna_troca] = aux;

    if(testajogada(tab) == 1)return 0;
    gravajogada(tab);

    if (final(tab) == 1) {
        max_niveis = nivel;
        gravaresulado(tab,nivel);
        return 1;
    }

       if(back(tab, nivel + 1, linha_troca, coluna_troca, linha_troca, coluna_troca - 1) == 1){
           gravaresulado(tab,nivel);
           return 1;
       }
       if(back(tab, nivel + 1, linha_troca, coluna_troca, linha_troca, coluna_troca + 1)== 1){
           gravaresulado(tab,nivel);
            return 1;
        }
       if(back(tab, nivel + 1, linha_troca, coluna_troca, linha_troca + 1, coluna_troca)== 1){
           gravaresulado(tab,nivel);
           return 1;
       }
       if(back(tab, nivel + 1, linha_troca, coluna_troca, linha_troca - 1, coluna_troca)== 1){
           gravaresulado(tab,nivel);
           return 1;
       }

     return 0;
    }



int main()
{
    int entrada;
    int tabela[3][3]={{0,0,0},{0,0,0},{0,0,0}};
    int tab[9]={0,0,0,0,0,0,0,0,0};

    printf("Digite os valores iniciais da tabela:");
    scanf("%d", &entrada);

    if(entrada >9999999 && entrada < 1000000000){
        for (int i=0;i<9;i++){
                tab[8-i]= entrada % 10 ;
                entrada = entrada/10;
            }
        if(validatab(tab)==-1){
            printf("Valores iniciais invalidos!");
            exit(1);
        }else{
            for(int i=0;i<9;i++){
                tabela[i/3][i%3]=tab[i];
            }
        }
    }else{
        printf("Valores iniciais invalidos!");
        exit(1);
    }
    printf("Digite o numero maximo de tentativas: ");
    scanf("%d", &max_tentativas);

    int i = achaLinha(tabela);
    int j = achaColuna(tabela);

    if(back(tabela,0,i,j,i,j) == 0){
        printf("Nao foi possivel concluir em %d movimentos \n",max_tentativas);
    }else{
        mostraresultado();
        printf("Completou em %d niveis \n", max_niveis);
    }
    system("pause");
}