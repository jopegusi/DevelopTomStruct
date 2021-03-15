#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
//JPS comentei isto porque é para MS DOS
//#include <conio.h>

//JPS adicionei esta biblioteca para funcao getch() para linux
//#include <curses.h>
//para copia de strings
#include <string.h>

    //Guardar a quantidade
    //int IDGLOBAL=1;
    //Nome do ficheiro de inventário para guardar os produtos
    char fileInventario[] = "Inventario_De_Oficina.dat";

    void CreateNewProduct();
    void ProductCharacteristics();
    int VariableInitializing();
    int readProductsFromFile();
    int writeProductToFile();
    // funcoes de conversao para p.ID (identificador (único) do produto)
    void int2string ( int i , char *idstring );
    int  string2int ( char *idstring );

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


   //long unsigned  vv = sizeof(struct Produtos);
   //printf ( "tamanho da estrutura Produtos é = %lu" ,vv );
   //printf ( "%s %.30s %c %ld %.2f\n",    p->ID, p->Nome, p->CAT, p->Qtd,  p->Valor );
//--------------------------------------------------------------------------------------
// Converte um numero inteiro numa string com zeros à esquerda
void int2string ( int i , char *idstring )
{
    sprintf(idstring, "%09d", i);
}
//--------------------------------------------------------------------------------------
// Converte uma string com zeros à esquerda para numero inteiro
int string2int ( char *idstring )
{
    int num = atoi( idstring );
    return num;
}

//--------------------------------------------------------------------------------------
// Imprime uma ficha Completa do produto
void produto_Print( struct Produtos *p )
{
  printf ( "p.ID      = %s\n",    p->ID);     //identificador (único) do produto
  printf ( "p.Nome    = %s\n",    p->Nome );  // - Nome do produto
  printf ( "p.CAT     = %c\n",    p->CAT);    // Categoria da Peça (i.e., M - Motor, T - Sistema de Travagem, E - Sistema Elétrico, O - Outras)
  printf ( "p.AF      = %.10s\n", p->AF);     //Ano de Fabricação (Data no formato dd/mm/aaaa)
  printf ( "p.DC      = %.10s\n", p->DC);     //Ano de Fabricação (Data no formato dd/mm/aaaa)
  printf ( "p.DE      = %.10s\n", p->DE);     //Data da última receção desse tipo de produto (Data no formato dd/mm/aaaa)
  printf ( "p.Qtd     = %ld\n",   p->Qtd);    //Quantidade (atualmente) no armazém
  printf ( "p.Unidade = %c\n",    p->Unidade); //Unidade de medida (i.e., U - Unidade, L - Litros, P - Packages)
  printf ( "p.Valor   = %.2f\n",  p->Valor);  //Valor / preço (unitário) do produto
  printf ( "p.DS      = %.10s\n", p->DS);     //Data de saída (Data no formato dd/mm/aaaa)
  printf ( "p.CT      = %s\n",    p->CT );    //Características Técnicas (“string” com indicação do caminho (no formato: pasta + nome do ficheiro de texto) onde se podem ler as CT especificas do producto / peça
  printf ( "p.TA      = %u\n",    p->TA );    //Total de acessos/saídas do armazém
  printf ( "\n");
}

//--------------------------------------------------------------------------------------
// Imprime uma linha REsumo do produto
void produto_Print_Sumario( struct Produtos *p )
{
  // selecciona os primeiros campos para mostrar numa linha
  // servirá para listagem resumidas ,ou mostrar progresso de leitura de conteudo de linhas do ficheiro dos dados
  printf ( "%s %.30s %c %ld %.2f\n",    p->ID, p->Nome, p->CAT, p->Qtd,  p->Valor );
}

//--------------------------------------------------------------------------------------
// para testes , permite criar rapidamente conteudos para uma instancia de produto.
void preenche_uma_struct_produto_constante( int id, struct Produtos *p )
{
  //converte numero para string com leading zeros
  int2string ( id , p->ID );
  //p.ID=id;       //identificador (único) do produto
  sprintf ( p->Nome, "Caixa de Velocidades");  // - Nome do produto
  p->CAT='M';          // Categoria da Peça (i.e., M - Motor, T - Sistema de Travagem, E - Sistema Elétrico, O - Outras)
  sprintf (p->AF , "01/01/2021");    //Ano de Fabricação (Data no formato dd/mm/aaaa)
  sprintf (p->DC , "01/01/2021");    //Ano de Fabricação (Data no formato dd/mm/aaaa)
  sprintf (p->DE , "01/01/2021");    //Data da última receção desse tipo de produto (Data no formato dd/mm/aaaa)
  p->Qtd=11;       //Quantidade (atualmente) no armazém
  p->Unidade='U';   //Unidade de medida (i.e., U - Unidade, L - Litros, P - Packages)
  p->Valor=58.45;    //Valor / preço (unitário) do produto
  sprintf (p->DS , "01/01/2021");    //Data de saída (Data no formato dd/mm/aaaa)
  //prepara nome de ficheiro com numero de ID no nome
  sprintf ( p->CT ,  "caracteristicasTecProd_%s.txt", p->ID );
  //p.CT="caracteristicas.ID.txt";   //Características Técnicas (“string” com indicação do caminho (no formato: pasta + nome do ficheiro de texto) onde se podem ler as CT especificas do producto / peça
  p->TA=0;        //Total de acessos/saídas do armazém

}




//--------------------------------------------------------------------------------------
int VariableInitializing( struct Produtos *p , int itemsAtuais, int itemsACriar  )
{

  int a ;
  /* for loop execution */
  for( a = itemsAtuais ; a < (itemsAtuais+itemsACriar) ; a= a + 1 ){
      preenche_uma_struct_produto_constante(  ++a , p );
      //produto_Print( p );
      writeProductToFile ( fileInventario , p );

  }
  return a;
}

//--------------------------------------------------------------------------------------
void CreateNewProduct()
{
}

//--------------------------------------------------------------------------------------
void ProductCharacteristics(){
    //system("@cls||clear");

}

//--------------------------------------------------------------------------------------
// conta a quantidade de Produtos no ficheiro de
// retorna a quantidade de itens
// https://www.geeksforgeeks.org/readwrite-structure-file-c/
int readProductsFromFile ( char *filename )
{
    FILE *infile;
    struct Produtos item;
    int QtItems = 0;

    // Open person.dat for reading
    infile = fopen ( filename, "r");
    if (infile == NULL)
    {
        fprintf(stderr, "\n-----------------------------------------------------\n");
        fprintf(stderr, "\n !!! Erro !!! a abrir o ficheiro de Produtos  %s\n", filename);
        fprintf(stderr, "\n-----------------------------------------------------\n");
        fprintf(stderr, "\na) Se é a primeira vez que o programa corre então  \n");
        fprintf(stderr, "\n   está bem. O programa irá criar o ficheiro com a   \n");
        fprintf(stderr, "\n   inserção do primeiro produto   \n");

        fprintf(stderr, "\nb) Se nao for o caso termine o programa   \n");
        fprintf(stderr, "\n   e reponha o ficheiro %s \n", filename );
        fprintf(stderr, "\n   na pasta certa \n");
        fprintf(stderr, "\n-----------------------------------------------------\n");
        printf("Press ENTER Key to Continue\n");
        getchar();
        return QtItems;
    }

    // read file contents till end of file
    while( fread(&item, sizeof(struct Produtos), 1, infile)  )  {
        ++QtItems;
        //printf ("id = %d name = %s %s\n", input.id, input.fname, input.lname);
        printf ("--\n");
        //printf ( "p.ID      = %s\n",      item.ID);     //identificador (único) do produto
        //printf ( "p.Nome    = %s\n",    item.Nome );  // - Nome do produto
        //printf ( "p.CAT     = %c\n",    item.CAT);    // Categoria da Peça (i.e., M - Motor, T - Sistema de Travagem, E - Sistema Elétrico, O - Outras)
        //printf ( "p.AF      = %.10s\n", item.AF);

        //produto_Print( &item );
        produto_Print_Sumario( &item );
      }


    // close file
    fclose (infile);
    return QtItems;
}


//--------------------------------------------------------------------------------------
// escreve 1 ITEM no ficheiro de produtos
// https://www.geeksforgeeks.org/readwrite-structure-file-c/
int writeProductToFile ( char *filename , struct Produtos *item )
{
    FILE *outfile;
    outfile = fopen ( filename, "a");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        return 1;
    }


    // write struct to file
    fwrite(item, sizeof(struct Produtos), 1, outfile);
    //fwrite(p, sizeof(struct Produtos), 1, outfile);

    if (fwrite != 0)
    {
            printf("contents to file written successfully !\n");
            produto_Print_Sumario( item );
    }    else
    {
            printf("error writing file !\n");
    }
    // close file
    fclose (outfile);
    return 0;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


int main()
{
  int items;            // quantidade total de tipo de produtos existentes

  struct Produtos Product, *pProduct, vProduct[5000] ;

  pProduct = &Product;

  // Vai ver se existe ficheiro de dados com o inventario e devolve o numero  de produtos nesse ficheiro

  items = readProductsFromFile ( fileInventario );

  printf ("Quantidade de items na DB é : %d \n", items );



  printf ("-- Vamos escrever um item na DB ---------------\n");

  //
  items = VariableInitializing( pProduct, items, 1 );

  //printf ("-- Vamos escrever um item na DB ---------------\n");

  //writeProductToFile ( fileInventario , pProduct );

  printf ("-- Vamos ler quantos items estao na DB -------\n");

  printf ("Quantidade de items na DB é : %d \n", items );



  //preenche_uma_struct_produto_constante(  3 , pProduct );
  //produto_Print( pProduct );

  setlocale(LC_ALL, "Portuguese");

  int op1, op2, op3, op4, op5, op6;

  char choice;

  while (op1!=6)
      {
          //system("@cls");
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
          printf("Escolha a opção que de deseja: \n");
          scanf(" %d",&op1);
          //system("@cls");

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
          //system("@cls||clear");
          printf("A op��o que escolheu � inv�lida, para voltar ao menu pressione uma tecla.");
      }
      //getch();
      scanf(" %c", &choice);
  }
}
