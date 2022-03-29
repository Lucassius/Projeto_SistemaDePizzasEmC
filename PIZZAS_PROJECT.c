 //O PROJETO É SEMELHANTE A UM SISTEMA DE RESTAURANTE, PERMITINDO O USUARIO PEDIR PIZZAS COM RECEITAS PRONTAS, ADICIONAR PIZZAS COM NOVAS RECEITAS E REALOCAR //
 //OS INGREDIENTES SALVANDO ELES EM ARQUIVOS BINARIOS//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define SUCESS 1
#define FAIL 1
#define TAMANHO_MAXIMO_DESCRICAO_PIZZA 50
#define QUANTIDADE_MAXIMA_INGREDIENTES 20
#define TAMANHO_MAXIMO_PIZZA 4
#define ING_NOT_FOUND 1
#define REC_NOT_FOUND 1
#define MAXIMO_INGREDIENTES 15
#define VARIAVEL_ORIG 10
#define REC_FAIL  1
#define REC_ACEPT 0
#define LEITURA_NUM_INGREDIENTES 1
#define LEITURA_NUM_RECEITAS 2
#define NOME 25
#define LISTAR_INGREDIENTES 20
#define CADASTRAR_INGREDIENTES 30

typedef struct INGREDIENTES {
      int num;
      char name[TAMANHO_MAXIMO_DESCRICAO_PIZZA];
 }pizza;

            

 typedef struct NOMEDAPIZZA {
     char nome_pizza_descript[TAMANHO_MAXIMO_DESCRICAO_PIZZA];
     pizza* ingred;
     float* quantidade;
     int num_ing;
 }nomepizza;


typedef struct ingredientes{

    char nome[NOME];
    int codigo_ingrediente;

}Ingredientes;

typedef struct controle{

    int Total_de_ingredientes;
    int Total_de_receitas;
    int Total_de_pedidos;

}Controle_programa;

typedef struct receitas{

    char nome_receita[NOME];
    int codigo_receita;
    int Numero_de_ingredientes;
    int codigo_ingredientes[MAXIMO_INGREDIENTES];
    float quantidade_dos_ingredientes[MAXIMO_INGREDIENTES];

}Receitas;

void listar_e_cadastrar_ingredientes(int controle_de_cadastro){
    FILE* F_ingredientes;
    int escolha;
    int num_ingredientes = ler_num_ingredientes_receitas(LEITURA_NUM_INGREDIENTES);
    Ingredientes * Lista_ingredientes = (Ingredientes*)malloc(sizeof(Ingredientes)* num_ingredientes);
    Ingredientes aux;


    switch (controle_de_cadastro)
    {
    case LISTAR_INGREDIENTES:
         F_ingredientes = fopen("ingredientes.bin", "rb");
         fread(Lista_ingredientes, sizeof(Ingredientes), num_ingredientes, F_ingredientes);
         fclose(F_ingredientes);
         printf("\n...Deseja listar os ingrendientes...\n");
         printf("\n...Criacao [1]...\n");
         printf("\n...Codigo [2]...\n");
         printf("\n...Alfabetica [3]...\n");
         scanf("%d%*c", &escolha);
         switch (escolha)
         {
         case 1:
            for(int i = 0; i < num_ingredientes; i++){
                printf("[%d] || %s\n", Lista_ingredientes[i].codigo_ingrediente, Lista_ingredientes[i].nome);
            }
            break;
        case 2:
            for(int i = 0; i < (num_ingredientes-1); i++){
                for(int j = 0; j < (num_ingredientes-1); j++){
                    if(Lista_ingredientes[j].codigo_ingrediente > Lista_ingredientes[j+1].codigo_ingrediente){
                        aux = Lista_ingredientes[j];
                        Lista_ingredientes[j] = Lista_ingredientes[j+1];
                        Lista_ingredientes[j+1] = aux;
                    }
                }
            }
            for(int i = 0; i < num_ingredientes; i++){
                printf("[%d] || %s\n", Lista_ingredientes[i].codigo_ingrediente, Lista_ingredientes[i].nome);
            }
            break;

        case 3:
            for(int i = 0; i < (num_ingredientes-1); i++){
                for(int j = 0; j < (num_ingredientes-1); j++){
                    if(strcmp(Lista_ingredientes[j].nome, Lista_ingredientes[j+1].nome) > 0){
                        aux = Lista_ingredientes[j];
                        Lista_ingredientes[j] = Lista_ingredientes[j+1];
                        Lista_ingredientes[j+1] = aux;
                    }
                }
            }
            for(int i = 0; i < num_ingredientes; i++){
                printf("[%d] || %s\n", Lista_ingredientes[i].codigo_ingrediente, Lista_ingredientes[i].nome);
            }
         
         default:
             break;
         }

        break;
    case CADASTRAR_INGREDIENTES:
        F_ingredientes = fopen("ingredientes.bin", "rb");
        fread(Lista_ingredientes, sizeof(Ingredientes), num_ingredientes, F_ingredientes);
        fclose(F_ingredientes);
        Lista_ingredientes = (Ingredientes*)realloc(Lista_ingredientes, sizeof(Ingredientes)*(num_ingredientes + 1));
        printf("\nInsira o codigo do ingrediente...:\n");
        scanf("%d%*c", &Lista_ingredientes[num_ingredientes].codigo_ingrediente);
        printf("\n...Digite o nome do ingrediente...\n");
        fgets(Lista_ingredientes[num_ingredientes].nome, NOME, stdin);
        Lista_ingredientes[num_ingredientes].nome[strlen(Lista_ingredientes[num_ingredientes].nome)- 1] = '\0';
        num_ingredientes++;
        F_ingredientes = fopen("ingredientes.bin", "wb");
        fwrite(Lista_ingredientes, sizeof(Ingredientes), num_ingredientes, F_ingredientes);
        fclose(F_ingredientes);
        break;
    default:
    perror("\tERROR...\n");
        break;
    }

    

}


void pizza_comum()
{
     char lixo;
     int quant_pizza;
     int i, j;
     int unit_ing, type_ing;
     nomepizza* receitas;

    FILE* arquivo_pizza_20_ingredientes;

    arquivo_pizza_20_ingredientes = fopen("ArquivoPizza.bin", "wb");
    if(arquivo_pizza_20_ingredientes == NULL){
        printf("\n...ARQUIVO NAO ENCONTRADO...\n");
        return FAIL;
    }

     pizza ingredientes_pizza[QUANTIDADE_MAXIMA_INGREDIENTES] = {
            {0, "Tomate"},
            {1, "Queijo"},
            {2, "Farinha"},
            {3, "Fermento"},
            {4, "Molho de tomate"},
            {5, "Oregano"},
            {6, "Calabresa"},
            {7, "Queijo cheddar"},
            {8, "Cebola"},
            {9, "Milho"},
            {10, "Azeitona"},
            {11, "Frango"},
            {12, "Presunto"},
            {13, "Bacon"},
            {14, "Pimentao"},
            {15, "Sal"},
            {16, "Champignon"},
            {17, "Salame"},
            {18, "Queijo frescal"},
            {19, "Linguica"},
        };

        printf("\n...LISTA DOS INGREDIENTES...\n");
        for (i = 0; i < QUANTIDADE_MAXIMA_INGREDIENTES; i++) {
            printf("[%d]%s\n", ingredientes_pizza[i].num, ingredientes_pizza[i].name);
            fwrite(&ingredientes_pizza[i], sizeof(pizza), 1, arquivo_pizza_20_ingredientes);         
        }
        fclose(arquivo_pizza_20_ingredientes);
    
        arquivo_pizza_20_ingredientes = fopen("ArquivoPizza.bin", "rb");
        printf("\nAgora vamos comecar a montar a(s) pizza(s) :\n");
        printf("\nQuantidade de pizza(s):\n");
        scanf("%d%c", &quant_pizza, &lixo);
     
        

        receitas = (nomepizza*)malloc(quant_pizza * sizeof(nomepizza));
        for (i = 0; i < quant_pizza; i++) {
            printf("\nAgora insira o nome da pizza:\n");
            fgets(receitas[i].nome_pizza_descript, TAMANHO_MAXIMO_DESCRICAO_PIZZA, stdin);
            receitas[i].nome_pizza_descript[strlen(receitas[i].nome_pizza_descript) - 1] = '\0';
           

            printf("\nInsira a quantidade de ingredientes (Max.20) :\n");
            scanf("%d%c", &unit_ing, &lixo);
            receitas[i].num_ing = unit_ing;

            receitas[i].ingred = (pizza*)malloc(unit_ing * sizeof(pizza));
            receitas[i].quantidade = (float*)malloc(unit_ing * sizeof(float));
            for (int j = 0; j < unit_ing; j++) {
                printf("\nInsira o numero dos ingredientes de acordo com a lista:\n");
                scanf("%d%c", &type_ing, &lixo);
                type_ing -= 1;
                receitas[i].ingred[j] = ingredientes_pizza[type_ing];

                printf("\nInsira a quantidade de cada ingrediente em gramas:\n");
                scanf("%f%c", &receitas[i].quantidade[j], &lixo);


            }

        }
                fwrite(receitas, sizeof(nomepizza), quant_pizza, arquivo_pizza_20_ingredientes);
                fclose(arquivo_pizza_20_ingredientes);
                
            
        for (i = 0; i < quant_pizza; i++) {
            printf("\nA receita da(s) pizza(s) e:\n");
            printf("\nNome da pizza %s\n", receitas[i].nome_pizza_descript);
            printf("\nAbaixo os ingredientes das pizzas.\n");

            for (j = 0; j < (receitas[i].num_ing); j++) {
                printf("%d-%s/quantidade=%.2f\n", receitas[i].ingred[j].num, receitas[i].ingred[j].name, receitas[i].quantidade[j]);

               
            }


        }   

    }

void imprime_receitas(int Num_max_rec, int Num_max_ing){



    FILE* arquivo_ingredientes;
    FILE* arquivo_receitas;

    Ingredientes * Dados_ingredientes;
    Receitas * Dados_receitas;

    int i,j,k,choise;
    int Codigo_receita;
    int alternate_lp = 0;
    char * check_use = {"lixo"};
    int rec_non_locate = 1;
   

    Dados_ingredientes = (Ingredientes*)malloc(Num_max_ing * sizeof(Ingredientes));
    Dados_receitas = (Receitas*)malloc(Num_max_rec * sizeof(Receitas));

    arquivo_ingredientes = fopen("ingredientes.bin","rb");
    if(arquivo_ingredientes == NULL){
       perror("\n...ARQUIVO NAO ENCONTRADO...\n");    
    }
    
    arquivo_receitas = fopen("receitas.bin","rb");
   if(arquivo_ingredientes == NULL){
       perror("\n...ARQUIVO NAO ENCONTRADO...\n");    
    }

  
    if(arquivo_ingredientes == NULL || arquivo_receitas == NULL){
        perror("\n...ARQUIVO NAO ENCONTRADO...\n");
        
    }

    for(i = 0;i < Num_max_ing;i++){
        
        fread(&Dados_ingredientes[i],sizeof(Ingredientes),1,arquivo_ingredientes);

    }
    for(i = 0;i < Num_max_rec;i++){
        fread(&Dados_receitas[i],sizeof(Receitas),1,arquivo_receitas);
    }
    
    printf("\n...IMPLEMENTANDO RECEITAS...\n");

    while(alternate_lp!=1){

        rec_non_locate = 1;
        
        printf("Voce deseja listar todas as receitas ou alguma especifica: \n");
        printf("[0] Somente uma em especifico.\n");
        printf("[1] Todas as receitas.\n");
        printf("Escolha: ");
        scanf("%d", &choise);
        printf("\n");

        switch(choise){

            case 0:
                printf("Digite o codigo da receita: ");
                scanf("%d", &Codigo_receita);

                for(i = 0;i < Num_max_rec;i++){
                    if(Codigo_receita == Dados_receitas[i].codigo_receita && strcmp(Dados_receitas[i].nome_receita, check_use)!=0){
                        printf("Nome: %s\n", Dados_receitas[i].nome_receita);
                        printf("Numero de ingredientes: %d\n", Dados_receitas[i].Numero_de_ingredientes);
                        printf("Codigo: %.4d\n\n", Dados_receitas[i].codigo_receita);

                        printf("\tIngredientes da receita: \n");
                        printf("Nome                  Codigo  Quantidade \n");
                        for(j = 0;j < Dados_receitas[i].Numero_de_ingredientes;j++){
                            for(k = 0;k < Num_max_ing;k++){
                                if(Dados_ingredientes[k].codigo_ingrediente == Dados_receitas[i].codigo_ingredientes[j]){
                                    printf("%-20s   %.4d     %.2f\n", Dados_ingredientes[k].nome,Dados_receitas[i].codigo_ingredientes[j], Dados_receitas[i].quantidade_dos_ingredientes[j]);
                                }
                            }
                            
                        }
                        rec_non_locate = 0;
                    }
                }

                if(rec_non_locate == 1){
                    printf("\n...Nao foi possivel localizar a receita...\n");
                }

                    printf("\n");

            break;
            case 1:
                for(i = 0;i < Num_max_rec;i++){
                    if(strcmp(Dados_receitas[i].nome_receita, check_use)!=0){
                        printf("Nome: %s\n", Dados_receitas[i].nome_receita);
                        printf("Numero de ingredientes: %d\n", Dados_receitas[i].Numero_de_ingredientes);
                        printf("Codigo: %.4d\n\n", Dados_receitas[i].codigo_receita);

                        printf("\tIngredientes da receita: \n");
                        printf("Nome                  Codigo  Quantidade \n");
                        for(j = 0;j < Dados_receitas[i].Numero_de_ingredientes;j++){
                            for(k = 0;k < Num_max_ing;k++){
                                if(Dados_ingredientes[k].codigo_ingrediente==Dados_receitas[i].codigo_ingredientes[j]){
                                    printf("%-20s   %.4d     %.2f\n", Dados_ingredientes[k].nome,Dados_receitas[i].codigo_ingredientes[j], Dados_receitas[i].quantidade_dos_ingredientes[j]);
                                }
                            }
                            
                        }
                    }
                    printf("\n");
                }
            break;
            default:
                printf("\n...ESCOLHA UMA OPCAO VALIDA...\n");
            break;

        }

        printf("Deseja visualizar mais alguma receita: \n");
        printf("[0] Sim.\n");
        printf("[1] Nao.\n");
        printf("Opcao: ");
        scanf("%d", &alternate_lp);
        printf("\n");
    }

    free(Dados_ingredientes);
    free(Dados_receitas);
    fclose(arquivo_ingredientes);
    fclose(arquivo_receitas);
}

int ler_num_ingredientes_receitas(int recebe_funcao){

    FILE* arquivo_ingredientes;
    FILE* arquivo_receitas;
    int num_itens = 0;
    Ingredientes ing;
    Receitas recipe;
    Ingredientes ingr = {{"tomato"}, 43};
    Receitas recipeeee = {{"receita"}, 10, 1, {ingr.codigo_ingrediente}, {2}};

    switch (recebe_funcao){
        case LEITURA_NUM_INGREDIENTES:
            arquivo_ingredientes = fopen("ingredientes.bin", "rb");
            if(arquivo_ingredientes == NULL){
                fclose(arquivo_ingredientes);   
                arquivo_ingredientes = fopen("ingredientes.bin", "wb");
                fwrite(&ingr, sizeof(Ingredientes), 1, arquivo_ingredientes);
                fclose(arquivo_ingredientes);
                arquivo_ingredientes = fopen("ingredientes.bin", "rb");
            }
            
            while(!feof(arquivo_ingredientes)){
                fread(&ing, sizeof(Ingredientes), 1, arquivo_ingredientes);
                if(feof(arquivo_ingredientes)){
                    break;
                }
                
                num_itens++;
            }
            fclose(arquivo_ingredientes);
            break;

        case LEITURA_NUM_RECEITAS:
            arquivo_receitas = fopen("receitas.bin", "rb");
            if(arquivo_receitas == NULL){
                fclose(arquivo_receitas);   
                arquivo_receitas = fopen("receitas.bin", "wb");
                fwrite(&recipeeee, sizeof(Receitas), 1, arquivo_receitas);
                fclose(arquivo_receitas);
                arquivo_receitas = fopen("receitas.bin", "rb");
            }
    
            
            while(!feof(arquivo_receitas)){
                fread(&recipe, sizeof(Receitas), 1, arquivo_receitas);
                if(feof(arquivo_receitas)){
                    break;
                }
                num_itens++;
            }
            fclose(arquivo_receitas);
            break;

        default:
            break;
    }
    
    return num_itens;
}



void adiciona_remove_receitas(int Total_de_receitas, int Total_de_ingredientes){

       
    FILE * arquivo_ingredientes;
    FILE * arquivo_controle;
    FILE * arquivo_receitas;

    Ingredientes * data_ing;
    Receitas * data_rec;
    Receitas help_receitas;
    Controle_programa Controler;

    int i,j,k;
    int alternate_lp = 0;
    int choise;
    int control = 0;
    char * check_use = {"lixo"};
    

    data_ing=(Ingredientes*)malloc(Total_de_ingredientes * sizeof(Ingredientes));
    data_rec=(Receitas*)malloc(Total_de_receitas * sizeof(Receitas));
    arquivo_ingredientes = fopen("ingredientes.bin","rb");
    arquivo_receitas = fopen("receitas.bin", "rb");
 


    if((arquivo_ingredientes==NULL) || (arquivo_receitas==NULL)){
        perror("\n...ARQUIVO NAO ENCONTRADO...\n");
    }


    fread(data_ing, sizeof(Ingredientes), Total_de_ingredientes, arquivo_ingredientes);
    fread(data_rec, sizeof(Receitas), Total_de_receitas, arquivo_receitas);
    fclose(arquivo_ingredientes);
    fclose(arquivo_receitas);


    printf("\n...MONTAGEM DE RECEITAS...\n");
    while(alternate_lp==0){

        control=0;

        printf("Voce deseja adicionar uma receita?\n");
        printf("Digite [1] para adicionar uma receita:\n");
        scanf("%d%*c", &choise);
        printf("\n");

        switch(choise){

            case 1:
                arquivo_receitas = fopen("ingredientes.bin", "rb");
                fread(data_rec, sizeof(Receitas), Total_de_receitas, arquivo_receitas);
                data_rec = (Receitas*)realloc(data_rec, sizeof(Receitas)* (Total_de_receitas + 1));


                
                i = Total_de_receitas;
                printf("Digite o nome da receita:");
                fgets(data_rec[i].nome_receita, NOME, stdin);
                data_rec[i].nome_receita[strlen(data_rec[i].nome_receita)- 1] = '\0';
                control = 1;

                printf("Digite o numero de ingredientes(MAX. 15): ");
                scanf("%d%*c", &data_rec[i].Numero_de_ingredientes);
                printf("Codigo da nova receita:");
                scanf("%d%*c", &data_rec[i].codigo_receita);
                        

                printf("Digite o codigo dos ingredientes da pizza de %s:\n",data_rec[i].nome_receita);
                for(j = 0;j < data_rec[i].Numero_de_ingredientes;j++){
                    printf("Ingrediente[%d]:",j);
                    scanf("%d%*c", &data_rec[i].codigo_ingredientes[j]);
                }
                printf("Digite a quantidade de cada ingrediente: \n");
                for(j = 0;j < (data_rec[i].Numero_de_ingredientes);j++){
                    for(k = 0;k < Total_de_ingredientes;k++){
                        if(data_ing[k].codigo_ingrediente == data_rec[i].codigo_ingredientes[j]){
                            printf("%s: ",data_ing[k].nome);
                            scanf("%f%*c", &data_rec[i].quantidade_dos_ingredientes[j]);
                        }
                    }
                }

                fclose(arquivo_receitas);

                arquivo_receitas = fopen("receitas.bin","wb");
                Total_de_receitas++;
                fwrite(data_rec, sizeof(Receitas), Total_de_receitas, arquivo_receitas);
                fclose(arquivo_receitas);
              

            break;
           
            default:
                alternate_lp = 1;
            break;
        }
     
       
    }
     free(data_ing);
     free(data_rec);
     fclose(arquivo_ingredientes);
     fclose(arquivo_receitas);
    
   

 
    

}


int main(void){

    int choise_user;



    printf("\n|||...Bem vindo a Pizzaria Freddy Fazbear...|||\n");
    printf("|||...PAGINA DE MONTAGEM DA PIZZA...........|||\n");
    printf("|||...INGREDIENTES E RECEITAS.............|||\n");
    printf("\n...SE DESEJAR ADICIONAR INGREDIENTES OU RECEITAS...\n ");
    printf("\n...DIGITE [0]\n");
    printf("\n...SE DESEJAR VISUALIZAR SUA RECEITA...\n");
    printf("\n...DIGITE [1]...\n");
    printf("\n...SE DESEJAR MONTAR PIZZAS SEM CRIAR SEUS PROPRIOS INGREDIENTES...\n ");
    printf("\n...DIGITE [2]\n");
    printf("\n...SE DESEJAR LISTAR OS INGREDIENTES...\n");
    printf("\n...DIGITE [3]...\n");
    printf("\n...SE DESEJAR CADASTRAR INGREDIENTES...\n");
    printf("\n...DIGITE [4]...\n");
    printf("\n|||...SE DESEJAR FECHAR O SISTEMA DE PIZZAS...|||\n");
    printf("\n...DIGITE [5]\n");
    scanf("%d%*c", &choise_user);

    switch(choise_user){

        case 0: adiciona_remove_receitas(ler_num_ingredientes_receitas(LEITURA_NUM_RECEITAS), ler_num_ingredientes_receitas(LEITURA_NUM_INGREDIENTES));
                
        break;
        
        case 1: imprime_receitas(ler_num_ingredientes_receitas(LEITURA_NUM_RECEITAS), ler_num_ingredientes_receitas(LEITURA_NUM_INGREDIENTES));
        break;
        
        case 2: pizza_comum();
        break;
        
        case 3:listar_e_cadastrar_ingredientes(LISTAR_INGREDIENTES);

        break;

        case 4:listar_e_cadastrar_ingredientes(CADASTRAR_INGREDIENTES);

        break;
        case 5:
        printf("\n... O PROGRAMA VAI ENCERRAR EM...\n");
        _sleep(1000);
        printf("\n...3...\n");
        _sleep(1000);
        printf("\n...2...\n");
        _sleep(1000);
        printf("\n...1...");

        break;
        default:
        perror("\n... OPCAO INVALIDA...\n");
        break;


    }
   
   return SUCESS; 


}
