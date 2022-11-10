#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
/*
O=======================================================================O
| Estudo dirigido 4 - Sistema de Cadastro Acadêmico com Lista Encadeada |
|    Nomes:                                                             |
|        Matheus Camargo Ginebro CP3016153                              |
|        Lucas Haiter Leoni CP3017362                                   |
O=======================================================================O
*/

//+---------------------------------+ DEFININDO ESTRUTURAS +---------------------------------+

//Estrutura de aluno.
typedef struct _aluno{
    char nome[248];
    char turma;
    float nota;
    float frequencia;
    int matricula;
} Aluno;

//Estrutura de nó (representa item da lista).
typedef struct _node {
    Aluno aluno;        //Variável (struct) do tipo "Aluno".
    struct _node *prox; //Ponteiro para o próximo nó.
} Node;


//Estrutura de lista encadeada.
typedef struct _lista {
    Node *inicio; //ponteiro para o primeiro nó da lista
    Node *fim;    //ponteiro para o último nó da lista

} Lista;


//+---------------------------------+ DEFININDO FUNÇÕES +---------------------------------+
//Função estética, apenas para melhorar a """Interface""".
void proxtela(){
    printf("\n");
    system("pause");
    system("cls");
}



//Função para criar a lista (vazia).
Lista* cria_lista(){

    //Declarando uma lista vazia (dinâmicamente, com malloc).
    Lista *lista = (Lista*) malloc(sizeof(Lista));

    //Verificar se a lista foi realmente criada (caso não haja espaço na memória (ou haja algum outro erro), o valor de "lista" será NULL).
    if(lista == NULL){
         //Finalizar o programa retornando código de erro 1, e uma mensagem ao usuário.
        printf("\nErro ao alocar memória para a lista.\n");
        exit(1);
    }

    //Caso não haja erro, o programa inicializa os elementos da lista como NULL (pois ainda não há elementos, já que ela foi recem crianda).
    lista->inicio = NULL;
    lista->fim = NULL;

    return lista;
}

//Função que verifica se uma matrícula já foic cadastrada.
int verificarAluno(Lista *lista, Aluno aluno, int resp_mat){
    Node *node;

    for(node = lista->inicio; node != NULL; node = node->prox){
        if(resp_mat==node->aluno.matricula){
            return 1;
        }
        else if(node->prox==NULL){
            return 0;
        }
    }
}



//Função criada para adicionar os alunos na lista (como nó).
void inserirAluno(Lista *lista, Aluno al, int resp_mat){

    //cria o node da lista
    Node *node = (Node*)malloc(sizeof(Node));

    //Verificar se o nó foi realmente criado (caso não tenha sido, retornará uma mensagem de erro).
    if(node == NULL){
        printf("\nErro ao alocar memória para o nó da lista\n");
        exit(1);  //finaliza o programa retornando código de erro 1.
    }


    //Usar a função verificarAluno para saber se a matrícula digitada já foi cadastrada.
    if(verificarAluno(lista, al, resp_mat)==1){ //Caso já tenha sido cadastrada, retornará uma mensagem avisando o usuário;
        printf("\nEssa matrícula já foi cadastrada.\n");

    }else{ //Caso a matrícula ainda não tenha sido usada, o cadastro do aluno será efetuado.
        //Inserindo as informações do aluno em um nó da lista.
        strcpy(node->aluno.nome, al.nome);
        node->aluno.matricula = resp_mat;
        node->aluno.nota = al.nota;
        node->aluno.frequencia = al.frequencia;
        node->aluno.turma = al.turma;


        //Fazer o próximo nó apontar para onde a lista aponta.
        node->prox = lista->inicio;

        //caso seja o primeiro elemento a ser inserido na lista, ele também será o último.
        if(lista->inicio == NULL){
            lista->fim = node;
        }

        //o inicio da lista passa a apontar para o nó.
        lista->inicio = node;
    }//Neste caso, estamos inserindo no inicio da lista (o último aluno inserido será o primeiro na lista (a menos que não haja uma reordenação)).
}



//Função para imprimir lista.
void imprimeLista(Lista *lista){
    if(lista == NULL){//Verifica se a lista foi criada.
        printf("A lista não foi criada.\n");
        return;
    }else if(lista->inicio == NULL){//Verifica se a lista está vazia.
        printf("A lista está vazia.\n");
        return;
    }else{
        //Declarando o Node para percorrer a lista.
        Node *node;

        //Node recebe o inicio da lista.
        node = lista->inicio;

        printf("Alunos cadastrados: \n");
        //Percorrer a lista e escrever os dados da cada nó.
        for(node = lista->inicio; node != NULL; node = node->prox){
            printf("\nNome: %sMatrícula: %d\nNota: %.2f\nFrequência: %.2f\nTurma: %c\n", node->aluno.nome, node->aluno.matricula, node->aluno.nota, node->aluno.frequencia, node->aluno.turma);
        }
    }
}



//Função para Remover o aluno da lista.
int removerAluno(Lista *lista, int num_mat, Aluno aluno){
    if(lista == NULL) {//não faz nada pois a lista não foi criada.
        return 0;
    }else if(lista->inicio == NULL){//não faz nada pois a lista está vazia.
        return 0;
    } else{//Procura uma matrícula igual à digitada pelo usuário.
        //Criando ponteiros pra guardar uma posição e uma posição anterior.
        Node *prev, *pos;

        //Percorrer a lista, enquando procura alguma matrícula igual à digitada pelo usuário.
        for(pos = lista->inicio; pos != NULL; prev=pos, pos=pos->prox){

            if(pos->aluno.matricula == num_mat){//Encontrou algum nó com a matrícula igual à digitada pelo usuário.

                if(lista->inicio == lista->fim){//Verifica se a lista possui apenas um Aluno (Nó).
                    //inicializa a lista como vazia
                    lista->inicio = NULL;
                    lista->fim = NULL;

                }else{//se a lista possuir mais de um aluno (Nó).

                    if(pos == lista->inicio){//se o elemento está no início da lista
                        //o segundo elemento passa a ser o início da lista
                        lista->inicio = pos->prox;

                    }else if(pos == lista->fim){//se o elemento está no fim da lista
                        lista->fim = prev; //o final da lista passa apontar para o penúltimo nó.
                        prev->prox = NULL;  //o penúltimo node passa a ser o último nó.

                    } else{//O Elemento está no meio da lista.
                        //o proximo do nó anterior passa a ser o proximo do nó encontrado;
                        prev->prox = pos->prox;
                    }
                }
                //libera a memória ocupada pelo nó.
                free(pos);
                //retorna 1 (true) indicando que encontrou e removeu o elemento da lista
                return 1;
            } // fim do if que encontrou o elemento.

        } //fim do for.

        //se chegou nesse ponto quer dizer que a lista foi inteiramente percorrida
        //e não foi encotrado o valor que queremos remover da lista (retorna 0 - false).
        return 0;
    }
}



//Procurar na lista algum aluno com o nome igual ao digitado pelo o usuário, e escreve na tela seus dados.
int pesquisarAluno(Lista *lista, Aluno aluno, char pesq_nome[]){
    Node *node;
    int verif=0;

    for(node = lista->inicio; node != NULL; node = node->prox){
        if(strcmp(node->aluno.nome, pesq_nome)==0){
            printf("\nNome: %sMatrícula: %d\nNota: %.2f\nFrequência: %.2f\nTurma: %c\n", node->aluno.nome, node->aluno.matricula, node->aluno.nota, node->aluno.frequencia, node->aluno.turma);
            verif=1;
        }
    }
    return verif;//Caso retorne 1, significa que o aluno foi encontrado, e caso retorne 0, significa que ele não foi encontrado.
}



int MostraAlPorTurma(Lista *lista, Aluno aluno, char pesq_turma){

    Node *node;
    int verif=0;

    for(node = lista->inicio; node != NULL; node = node->prox){
        if(node->aluno.turma == pesq_turma){
            printf("\nNome: %sMatrícula: %d\nNota: %.2f\nFrequência: %.2f\nTurma: %c\n", node->aluno.nome, node->aluno.matricula, node->aluno.nota, node->aluno.frequencia, node->aluno.turma);
            verif=1;
        }
    }
    return verif;//Caso retorne 1, significa que o aluno foi encontrado, e caso retorne 0, significa que ele não foi encontrado.

}


//Procurar na lista algum aluno com a matrícula igual à digitada pelo usuário, e escreve seus dados na tela.
int pesquisarMatricula(Lista *lista, Aluno aluno, int pesq_mat){
    Node *node;
    int verif=0;

    for(node = lista->inicio; node != NULL; node = node->prox){
        if(node->aluno.matricula==pesq_mat){
            printf("\nNome: %sMatrícula: %d\nNota: %.2f\nFrequência: %.2f\nTurma: %c\n", node->aluno.nome, node->aluno.matricula, node->aluno.nota, node->aluno.frequencia, node->aluno.turma);
            verif=1;
        }
    }
    return verif;//Caso retorne 1, significa que o aluno foi encontrado, e caso retorne 0, significa que ele não foi encontrado.
}



//Função para Ordenar alunos.
int OrdenaAluno(Lista *lista, Aluno aluno){
    if(lista == NULL) {//não faz nada pois a lista não foi criada.
        return 0;
    }else if(lista->inicio == NULL){//não faz nada pois a lista está vazia.
        return 0;
    }else{//Ordena a lista.
        Node *pi, *pj, *pend=NULL;

        for(pi = lista->inicio; pi->prox!=NULL; pi = pi->prox){
            for(pj = lista->inicio; pj->prox!= pend; pj = pj->prox){
                if(strcmp(pj->aluno.nome, pj->prox->aluno.nome)>0){
                    Aluno aux = pj->aluno;
                    pj->aluno = pj->prox->aluno;
                    pj->prox->aluno = aux;
                }
            }
        }
    }
    return 1;
}



//Função para procurar a maior nota e a menor, e mostrar os alunos com essas notas.
int MostraAlByNota(Lista *lista, Aluno aluno){
    if(lista == NULL) {//Não há lista
        return 0;
    }else if(lista->inicio == NULL){//Lista vazia.
        return 0;
    }else{
        Node *node;

        //Pegar as tais notas.
        float MenorNota, MaiorNota;
        for(node = lista->inicio; node != NULL; node = node->prox){
            if (node == lista->inicio){
                MenorNota = node->aluno.nota;
                MaiorNota = node->aluno.nota;
            }else{
                if(MenorNota>node->aluno.nota){
                    MenorNota = node->aluno.nota;
                }
                if(MaiorNota<node->aluno.nota){
                    MaiorNota = node->aluno.nota;
                }
            }
        }

        //Mostrar os alunos com a menor nota.
        printf("A menor nota foi %.2f. Tirada por:\n", MenorNota);
        for(node = lista->inicio; node != NULL; node = node->prox){
            if(node->aluno.nota == MenorNota){
                printf("\nNome: %sMatrícula: %d\nNota: %.2f\nFrequência: %.2f\nTurma: %c\n", node->aluno.nome, node->aluno.matricula, node->aluno.nota, node->aluno.frequencia, node->aluno.turma);
            }
        }

        //Mostrar os alunos com a maior nota.
        printf("\nA maior nota foi %.2f. Tirada por:\n", MaiorNota);
        for(node = lista->inicio; node != NULL; node = node->prox){
            if(node->aluno.nota == MaiorNota){
                printf("\nNome: %sMatrícula: %d\nNota: %.2f\nFrequência: %.2f\nTurma: %c\n", node->aluno.nome, node->aluno.matricula, node->aluno.nota, node->aluno.frequencia, node->aluno.turma);
            }
        }
    }
    return 1;
}



//Função para limpar a lista.
int LimpaLista(Lista *lista){
    if(lista == NULL) {//Não há lista
        return 0;
    }else if(lista->inicio == NULL){//Lista vazia.
        return 0;
    }else{
    Node *node;

    //enquanto o inicio da lista apontar para um nó
    while(lista->inicio != NULL){
            //recupera o primeiro elemento da lista
            node = lista->inicio;

            //faz com que o próximo elemento seja o primeiro elemento da lista;
            lista->inicio = node->prox;

            //remove o nodo da lista
            free(node);
    }
    //libera a memória da variável que representa a lista
    free(lista);
    }
    return 1;
}



//+---------------------------------+ FUNÇÃO MAIN (onde a magia acontece (ou parte dela :P)) +---------------------------------+
int main(){
    setlocale(LC_ALL, "portuguese");

    //Declarando algumas variáveis auxiliares.
    int valor=0, num_mat, pesq_mat, resp_mat, verif;
    char pesq_nome[248], pesq_turma;

    //Declarando a lista e um nó aluno;
    Lista *lista;
    Aluno aluno;

    lista = cria_lista();


    do{
        //menu com as opções para que o usuário possa escolher.
        printf("O=================================================O\n|          SISTEMA DE CADASTRO ACADÊMICO          |\nO=================================================O\n| [1] Cadastrar aluno no início da lista.         |\n| [2] Remover aluno.                              |\n| [3] Pesquisar aluno por nome.                   |\n| [4] Pesquisar aluno por matrícula.              |\n| [5] Mostrar todos os alunos de uma turma.       |\n| [6] Ordenar toda a lista de alunos pelo nome.   |\n| [7] Mostrar os alunos com a maior e menor nota. |\n| [8] Sair.                                       |\nO=================================================O\n\nDigite o que quer fazer.\nR:");
        scanf("%d", &valor);

        switch (valor){

        case 1:
            system("cls");
            printf("O=======================================================O\n| Você escolheu [1] Cadastrar aluno no início da lista. |\nO=======================================================O\n\n");

            //Pegar o Nome do aluno.
            printf("Digite o nome: ");
            setbuf(stdin, NULL);
            fgets(aluno.nome, 248, stdin);

            //Pegar a Matrícula do aluno (e verificar se o valor digitado está entre 0 e 99999).
            do{
                printf("Digite a matricula: ");
                scanf("%d", &resp_mat);
                if(resp_mat>=0 && resp_mat<=99999){
                    printf("Valor válido. (após a inserção de todos os dados, será verificado se já há algum aluno com essa matrícula).\n");
                    verif=0;
                }else{
                    printf("Valor inválido. digite um valor que esteja no intervalo 0 <= X <= 99999.\n");
                    verif=1;
                }
            }while(verif);

            //Pegar a Nota do aluno (e verificar se o valor digitado está entre 0 e 10 (float)).
            do{
                printf("Digite a nota do aluno: ");
                scanf("%f", &aluno.nota);
                if(aluno.nota>=0.0 && aluno.nota<=10.0){
                    verif=0;
                }else{
                    printf("Valor inválido. digite um valor que esteja no intervalo 0 <= X <= 10.\n");
                    verif=1;
                }
            }while(verif);

            //Pegar a frequência do aluno (e verificar se o valor digitado está entre 0 e 100 (float)).
            do{
               printf("Digite a frequência do aluno: ");
                    scanf("%f", &aluno.frequencia);
                    if(aluno.frequencia>=0.0 && aluno.frequencia<=100.0){
                    verif=0;
                }else{
                    printf("Valor inválido. digite um valor que esteja no intervalo 0 <= X <= 100.\n");
                    verif=1;
                }
            }while(verif);

            //Pegar turma do aluno [A/B]
            do{
                printf("Digite a turma do aluno: ");
                setbuf(stdin, NULL);
                scanf("%c", &aluno.turma);

                if(aluno.turma!= 'A' && aluno.turma!='B'){
                    printf("Turma inválida. Escolha entre [A/B]\n");
                    verif=1;
                }else{
                    verif=0;
                }
            }while(verif);

            //Inserindo os dados cadastrados peo usuário na lista.
            inserirAluno(lista, aluno, resp_mat);

            //Imprimindo a lista.
            imprimeLista(lista);

            proxtela();
            break;

        case 2:
            system("cls");
            printf("O==================================O\n| Você escolheu [2] Remover aluno. |\nO==================================O\n\n");

            //Pegar a matrícula digitada para o usuário, para verificar sua existência, e então removê-la.
            printf("Digite o número da matrícula que você deseja remover: ");
            scanf("%d", &num_mat);

            //Executar função de remover aluno.
            if(removerAluno(lista, num_mat, aluno)==1){
                printf("\nAluno removido com sucesso.\n");
            }
            else{
                printf("\nNão foi possível fazer a remoção, aluno não encontrado.\n");
            }

            proxtela();
            break;

        case 3:
            system("cls");
            printf("O=============================================O\n| Você escolheu [3] Pesquisar aluno por nome. |\nO=============================================O\n\n");

            //Pegar o nome do aluno.
            printf("Digite o nome do aluno que você deseja pesquisar: ");
            setbuf(stdin, NULL);
            fgets(pesq_nome, 248, stdin);

            //Procurar na lista algum nome igual. (pode haver mais de 1 nome).
            if(pesquisarAluno(lista, aluno, pesq_nome)==0){
                printf("\nAluno não encontrado.\n");
            }

            proxtela();
            break;

        case 4:
            system("cls");
            printf("O==================================================O\n| Você escolheu [4] Pesquisar aluno por matrícula. |\nO==================================================O\n\n");

            //Pegar a matrícula do aluno.
            printf("Digite o número da matrícula que você deseja pesquisar: ");
            scanf("%d", &pesq_mat);

            //Procurar na lista alguma matrícula igual (só pode haver (no máximo) 1 matrícula igual à digitada).
            if(pesquisarMatricula(lista, aluno, pesq_mat)==0){
                printf("\nAluno não encontrado.\n");
            }

            proxtela();
            break;

        case 5:
            do{
            system("cls");
            printf("O=========================================================O\n| Você escolheu [5] Mostrar todos os alunos de uma turma. |\nO=========================================================O\n\n");

            printf("Digite qual turma você deseja ver os alunos: ");
            setbuf(stdin, NULL);
            scanf("%c", &pesq_turma);

            if(pesq_turma=='A' || pesq_turma=='B'){
                verif=0;
            }else{
                printf("\nTurma inválida, escolha entre [A/B].\n");
                verif=1;
                proxtela();
            }
            }while(verif);

            if(MostraAlPorTurma(lista, aluno, pesq_turma)==0){
                printf("\nNão há alunos na turma %c.\n", pesq_turma);
            }

            proxtela();
            break;

        case 6:
            system("cls");
            printf("O=============================================================O\n| Você escolheu [6] Ordenar toda a lista de alunos pelo nome. |\nO=============================================================O\n\n");

            if(OrdenaAluno(lista, aluno)==0){
                printf("Não há alunos cadastrados.\n");
            }else{
                imprimeLista(lista);
            }

            proxtela();
            break;

        case 7:
            system("cls");
            printf("O===============================================================O\n| Você escolheu [7] Mostrar os alunos com a maior e menor nota. |\nO===============================================================O\n\n");

            if(MostraAlByNota(lista, aluno) == 0){
                printf("Não há alunos cadastrados.\n");
            }

            proxtela();
            break;

        case 8:
            system("cls");
            printf("O=========================O\n| Você escolheu [8] Sair. |\nO=========================O\n\n");


            if(LimpaLista(lista)==0){
                printf("Não haviam elementos na lista, portanto, ela não precisou ser limpa.\n");
            }else{
                printf("A lista foi limpa.\n");
            }

            break;

        case 69://DEBUG :D
        printf("\n");
            imprimeLista(lista);
            proxtela();
            break;

        default:
            printf("O valor digitado é inválido. Escolha algo entre 1 e 8.\n");
            proxtela();
            break;
        }
    }while(valor!=8);
    return 0;
}
