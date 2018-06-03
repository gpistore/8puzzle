#include <stdio.h>
#include <stdlib.h>
int cont=0;
int tab[3][3]={{8,0,6},
               {5,4,7},
               {2,3,1}};
void mostra()
{
    int i,j;
    printf("Solução %d:\n\n",++cont);
    for (i=0;i<3;i++){
        for (j=0;j<3;j++)
            printf("%2d ",tab[i][j]);
        printf("\n\n");
    }
    printf("\n\n");
}

void back(int nivel, int lin, int col)
{
    if (lin<0 || lin>2 || col<0 || col>2) return;
    if (tab[lin][col]!=0) return;
    tab[lin][col]=nivel;
    if (nivel==9)
    {
        mostra();
        tab[lin][col]=0;
        return;
    }
    back(nivel+1,lin-1,col-1);
    back(nivel+1,lin-2,col+1);
    back(nivel+1,lin-1,col-2);
    back(nivel+1,lin-1,col+2);
    back(nivel+1,lin+1,col-2);
    back(nivel+1,lin+1,col+2);
    back(nivel+1,lin+2,col-1);
    back(nivel+1,lin+2,col+1);
    tab[lin][col]=0;
}
int main()
{
    back(1,0,0);
    system("pause");
}