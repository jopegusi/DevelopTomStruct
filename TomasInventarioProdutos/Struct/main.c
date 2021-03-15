#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
//JPS comentei isto porque é para MS DOS
//#include <conio.h>

//JPS adicionei esta biblioteca para funcao getch() para linux
#include <curses.h>


    char choice;

    void CreateNewProduct();
    void ProductCharacteristics();
    void VariableInitializing();

    struct Produtos {
        char ID[10];
        char Nome[50];
        char CAT;
        char AF[10];
        char DC[10];
        char DE[10];
        long Qtd;
        char Unidade;
        float Valor ;
        char DS[10];
        char CT[256];
        unsigned int TA;
    };

    int IDGLOBAL=1;

    struct Produtos myProduct;


int main()
{
    //VariableInitializing();

    setlocale(LC_ALL, "Portuguese");

    int op1, op2, op3, op4, op5, op6;


    while (op1!=6)
        {
            system("@cls");
            printf("============================ MENU ============================\n");
            printf("=   1. Criar /adicionar um novo produto                      =\n");
            printf("=   2. Introduzir as caracter�sticas t�cnicas de um produto  =\n");
            printf("=   3. Rececionar novos lotes de um producto no armaz�m      =\n");
            printf("=   4. Dar sa�da de um produto no armaz�m                    =\n");
            printf("=   5. Alertas baixa disponibilidade de uma pe�a/produto     =\n");
            printf("=   6. Estat�sticas                                          =\n");
            printf("=   7. Finalizar                                             =\n");
            printf("==============================================================\n");
            printf("\n");
            printf("Escolha a op��o que de deseja: \n");
            scanf("%d",&op1);
            system("@cls");

        switch(op1)
        {
        case 1:

            printf("Voce pretende adicionar um novo produto? (s/n)");
    scanf("%s", &choice);
    printf("\n");

    if("choice == 's'")
    {

    CreateNewProduct();
    }
    else
    {
        return 1;
    }
            break;


        case 2:
               ProductCharacteristics();

            break;

        case 3:

            break;

        case 4:

            break;

        case 5:

            break;

        case 6:

            break;

        case 7:
            printf("\n\nPressione uma tecla para sair do programa.\n\n");
            exit(0);
            break;

        default:
            system("@cls||clear");
            printf("A op��o que escolheu � inv�lida, para voltar ao menu pressione uma tecla.");
        }
        getch();
    }
}

void VariableInitializing()
{
   FILE * fP;
   int a;
    fP = fopen("id.text","r");
    fscanf( "%d", &a);
    fseek(fP, -1, SEEK_CUR);
    if(a=1)
    {
       struct Produtos = {1};
    }
    else{

    }

    fclose(VariableInitializing);
}

void CreateNewProduct()
{
      FILE* fPointer;
         system("@cls||clear");
     printf("É o primeiro produto introduzido?");
     char choice[40];
     scanf("%s", choice);

    if(choice='s')
    {
         VariableInitializing();
         //fprintf("")
    }
    else
    {
         VariableInitializing();
         myProduct.ID++;
         fprintf(fPointer, "%d", &myProduct.ID);
    }



    fPointer=fopen("Produtos.txt", "w"); //create's a txt file if the don't exist

    printf("Introduza o nome do produto: ");
    scanf("%s", &myProduct.Nome);

    printf("Introduza a Categoria da Pe�a (M - Motor, T - Sistema de Travagem, E - Sistema El�trico, O - Outras: ");
    scanf("%s", &myProduct.CAT);


    fprintf(fPointer, "%s\n", &myProduct.Nome);
    fprintf(fPointer, "%s\n\n", &myProduct.CAT);

    printf("%s", myProduct.Nome);


/*
  char line[255];
    FILE * fPointer1;
    fPointer1 = fopen("Produtos.txt","r");//read a ID
    fgets(line, 255, fPointer1);
    fgets(line, 255, fPointer1);
    fseek(fPointer1, -1, SEEK_CUR);
    scanf("%s", line);
*/

    fclose(fPointer);

  system("@cls||clear");

    printf("Deseja ver o ficheiro?");
    scanf("%s", &choice);
     if("choice == 's'")

    {
          system("@cls||clear");

            FILE *fPointer;
        fPointer = fopen("Produtos.txt", "r"); //Read de file
        char singleLine[150];



        while(fgets(singleLine,50,fPointer)!=NULL){
                puts(singleLine);
    }

        fclose(fPointer);

    }
    else
    {
        return 1;
    }


}

void ProductCharacteristics(){
    system("@cls||clear");





}
