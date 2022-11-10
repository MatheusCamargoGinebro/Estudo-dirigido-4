#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
/*
O=======================================================================O
| Estudo dirigido 4 - Sistema de Cadastro Acad�mico com Lista Encadeada |
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

//Estrutura de n� (representa item da lista).
typedef struct _node {
    Aluno aluno;        //Vari�vel (struct) do tipo "Aluno".
    struct _node *prox; //Ponteiro para o pr�ximo n�.
} Node;


//Estrutura de lista encadeada.
typedef struct _lista {
    Node *inicio; //ponteiro para o primeiro n� da lista
    Node *fim;    //ponteiro para o �ltimo n� da lista

} Lista;


//+---------------------------------+ DEFININDO FUN��ES +---------------------------------+
//Fun��o est�tica, apenas para melhorar a """Interface""".
void proxtela(){
    printf("\n");
    system("pause");
    system("cls");
}



//Fun��o para criar a lista (vazia).
Lista* cria_lista(){

    //Declarando uma lista vazia (din�micamente, com malloc).
    Lista *lista = (Lista*) malloc(sizeof(Lista));

    //Verificar se a lista foi realmente criada (caso n�o haja espa�o na mem�ria (ou haja algum outro erro), o valor de "lista" ser� NULL).
    if(lista == NULL){
         //Finalizar o programa retornando c�digo de erro 1, e uma mensagem ao usu�rio.
        printf("\nErro ao alocar mem�ria para a lista.\n");
        exit(1);
    }

    //Caso n�o haja erro, o programa inicializa os elementos da lista como NULL (pois ainda n�o h� elementos, j� que ela foi recem crianda).
    lista->inicio = NULL;
    lista->fim = NULL;

    return lista;
}

//Fun��o que verifica se uma matr�cula j� foic cadastrada.
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



//Fun��o criada para adicionar os alunos na lista (como n�).
void inserirAluno(Lista *lista, Aluno al, int resp_mat){

    //cria o node da lista
    Node *node = (Node*)malloc(sizeof(Node));

    //Verificar se o n� foi realmente criado (caso n�o tenha sido, retornar� uma mensagem de erro).
    if(node == NULL){
        printf("\nErro ao alocar mem�ria para o n� da lista\n");
        exit(1);  //finaliza o programa retornando c�digo de erro 1.
    }


    //Usar a fun��o verificarAluno para saber se a matr�cula digitada j� foi cadastrada.
    if(verificarAluno(lista, al, resp_mat)==1){ //Caso j� tenha sido cadastrada, retornar� uma mensagem avisando o usu�rio;
        printf("\nEssa matr�cula j� foi cadastrada.\n");

    }else{ //Caso a matr�cula ainda n�o tenha sido usada, o cadastro do aluno ser� efetuado.
        //Inserindo as informa��es do aluno em um n� da lista.
        strcpy(node->aluno.nome, al.nome);
        node->aluno.matricula = resp_mat;
        node->aluno.nota = al.nota;
        node->aluno.frequencia = al.frequencia;
        node->aluno.turma = al.turma;


        //Fazer o pr�ximo n� apontar para onde a lista aponta.
        node->prox = lista->inicio;

        //caso seja o primeiro elemento a ser inserido na lista, ele tamb�m ser� o �ltimo.
        if(lista->inicio == NULL){
            lista->fim = node;
        }

        //o inicio da lista passa a apontar para o n�.
        lista->inicio = node;
    }//Neste caso, estamos inserindo no inicio da lista (o �ltimo aluno inserido ser� o primeiro na lista (a menos que n�o haja uma reordena��o)).
}



//Fun��o para imprimir lista.
void imprimeLista(Lista *lista){
    if(lista == NULL){//Verifica se a lista foi criada.
        printf("A lista n�o foi criada.\n");
        return;
    }else if(lista->inicio == NULL){//Verifica se a lista est� vazia.
        printf("A lista est� vazia.\n");
        return;
    }else{
        //Declarando o Node para percorrer a lista.
        Node *node;

        //Node recebe o inicio da lista.
        node = lista->inicio;

        printf("Alunos cadastrados: \n");
        //Percorrer a lista e escrever os dados da cada n�.
        for(node = lista->inicio; node != NULL; node = node->prox){
            printf("\nNome: %sMatr�cula: %d\nNota: %.2f\nFrequ�ncia: %.2f\nTurma: %c\n", node->aluno.nome, node->aluno.matricula, node->aluno.nota, node->aluno.frequencia, node->aluno.turma);
        }
    }
}



//Fun��o para Remover o aluno da lista.
int removerAluno(Lista *lista, int num_mat, Aluno aluno){
    if(lista == NULL) {//n�o faz nada pois a lista n�o foi criada.
        return 0;
    }else if(lista->inicio == NULL){//n�o faz nada pois a lista est� vazia.
        return 0;
    } else{//Procura uma matr�cula igual � digitada pelo usu�rio.
        //Criando ponteiros pra guardar uma posi��o e uma posi��o anterior.
        Node *prev, *pos;

        //Percorrer a lista, enquando procura alguma matr�cula igual � digitada pelo usu�rio.
        for(pos = lista->inicio; pos != NULL; prev=pos, pos=pos->prox){

            if(pos->aluno.matricula == num_mat){//Encontrou algum n� com a matr�cula igual � digitada pelo usu�rio.

                if(lista->inicio == lista->fim){//Verifica se a lista possui apenas um Aluno (N�).
                    //inicializa a lista como vazia
                    lista->inicio = NULL;
                    lista->fim = NULL;

                }else{//se a lista possuir mais de um aluno (N�).

                    if(pos == lista->inicio){//se o elemento est� no in�cio da lista
                        //o segundo elemento passa a ser o in�cio da lista
                        lista->inicio = pos->prox;

                    }else if(pos == lista->fim){//se o elemento est� no fim da lista
                        lista->fim = prev; //o final da lista passa apontar para o pen�ltimo n�.
                        prev->prox = NULL;  //o pen�ltimo node passa a ser o �ltimo n�.

                    } else{//O Elemento est� no meio da lista.
                        //o proximo do n� anterior passa a ser o proximo do n� encontrado;
                        prev->prox = pos->prox;
                    }
                }
                //libera a mem�ria ocupada pelo n�.
                free(pos);
                //retorna 1 (true) indicando que encontrou e removeu o elemento da lista
                return 1;
            } // fim do if que encontrou o elemento.

        } //fim do for.

        //se chegou nesse ponto quer dizer que a lista foi inteiramente percorrida
        //e n�o foi encotrado o valor que queremos remover da lista (retorna 0 - false).
        return 0;
    }
}



//Procurar na lista algum aluno com o nome igual ao digitado pelo o usu�rio, e escreve na tela seus dados.
int pesquisarAluno(Lista *lista, Aluno aluno, char pesq_nome[]){
    Node *node;
    int verif=0;

    for(node = lista->inicio; node != NULL; node = node->prox){
        if(strcmp(node->aluno.nome, pesq_nome)==0){
            printf("\nNome: %sMatr�cula: %d\nNota: %.2f\nFrequ�ncia: %.2f\nTurma: %c\n", node->aluno.nome, node->aluno.matricula, node->aluno.nota, node->aluno.frequencia, node->aluno.turma);
            verif=1;
        }
    }
    return verif;//Caso retorne 1, significa que o aluno foi encontrado, e caso retorne 0, significa que ele n�o foi encontrado.
}



int MostraAlPorTurma(Lista *lista, Aluno aluno, char pesq_turma){

    Node *node;
    int verif=0;

    for(node = lista->inicio; node != NULL; node = node->prox){
        if(node->aluno.turma == pesq_turma){
            printf("\nNome: %sMatr�cula: %d\nNota: %.2f\nFrequ�ncia: %.2f\nTurma: %c\n", node->aluno.nome, node->aluno.matricula, node->aluno.nota, node->aluno.frequencia, node->aluno.turma);
            verif=1;
        }
    }
    return verif;//Caso retorne 1, significa que o aluno foi encontrado, e caso retorne 0, significa que ele n�o foi encontrado.

}


//Procurar na lista algum aluno com a matr�cula igual � digitada pelo usu�rio, e escreve seus dados na tela.
int pesquisarMatricula(Lista *lista, Aluno aluno, int pesq_mat){
    Node *node;
    int verif=0;

    for(node = lista->inicio; node != NULL; node = node->prox){
        if(node->aluno.matricula==pesq_mat){
            printf("\nNome: %sMatr�cula: %d\nNota: %.2f\nFrequ�ncia: %.2f\nTurma: %c\n", node->aluno.nome, node->aluno.matricula, node->aluno.nota, node->aluno.frequencia, node->aluno.turma);
            verif=1;
        }
    }
    return verif;//Caso retorne 1, significa que o aluno foi encontrado, e caso retorne 0, significa que ele n�o foi encontrado.
}



//Fun��o para Ordenar alunos.
int OrdenaAluno(Lista *lista, Aluno aluno){
    if(lista == NULL) {//n�o faz nada pois a lista n�o foi criada.
        return 0;
    }else if(lista->inicio == NULL){//n�o faz nada pois a lista est� vazia.
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



//Fun��o para procurar a maior nota e a menor, e mostrar os alunos com essas notas.
int MostraAlByNota(Lista *lista, Aluno aluno){
    if(lista == NULL) {//N�o h� lista
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
                printf("\nNome: %sMatr�cula: %d\nNota: %.2f\nFrequ�ncia: %.2f\nTurma: %c\n", node->aluno.nome, node->aluno.matricula, node->aluno.nota, node->aluno.frequencia, node->aluno.turma);
            }
        }

        //Mostrar os alunos com a maior nota.
        printf("\nA maior nota foi %.2f. Tirada por:\n", MaiorNota);
        for(node = lista->inicio; node != NULL; node = node->prox){
            if(node->aluno.nota == MaiorNota){
                printf("\nNome: %sMatr�cula: %d\nNota: %.2f\nFrequ�ncia: %.2f\nTurma: %c\n", node->aluno.nome, node->aluno.matricula, node->aluno.nota, node->aluno.frequencia, node->aluno.turma);
            }
        }
    }
    return 1;
}



//Fun��o para limpar a lista.
int LimpaLista(Lista *lista){
    if(lista == NULL) {//N�o h� lista
        return 0;
    }else if(lista->inicio == NULL){//Lista vazia.
        return 0;
    }else{
    Node *node;

    //enquanto o inicio da lista apontar para um n�
    while(lista->inicio != NULL){
            //recupera o primeiro elemento da lista
            node = lista->inicio;

            //faz com que o pr�ximo elemento seja o primeiro elemento da lista;
            lista->inicio = node->prox;

            //remove o nodo da lista
            free(node);
    }
    //libera a mem�ria da vari�vel que representa a lista
    free(lista);
    }
    return 1;
}



//+---------------------------------+ FUN��O MAIN (onde a magia acontece (ou parte dela :P)) +---------------------------------+
int main(){
    setlocale(LC_ALL, "portuguese");

    //Declarando algumas vari�veis auxiliares.
    int valor=0, num_mat, pesq_mat, resp_mat, verif;
    char pesq_nome[248], pesq_turma;

    //Declarando a lista e um n� aluno;
    Lista *lista;
    Aluno aluno;

    lista = cria_lista();


    do{
        //menu com as op��es para que o usu�rio possa escolher.
        printf("O=================================================O\n|          SISTEMA DE CADASTRO ACAD�MICO          |\nO=================================================O\n| [1] Cadastrar aluno no in�cio da lista.         |\n| [2] Remover aluno.                              |\n| [3] Pesquisar aluno por nome.                   |\n| [4] Pesquisar aluno por matr�cula.              |\n| [5] Mostrar todos os alunos de uma turma.       |\n| [6] Ordenar toda a lista de alunos pelo nome.   |\n| [7] Mostrar os alunos com a maior e menor nota. |\n| [8] Sair.                                       |\nO=================================================O\n\nDigite o que quer fazer.\nR:");
        scanf("%d", &valor);

        switch (valor){

        case 1:
            system("cls");
            printf("O=======================================================O\n| Voc� escolheu [1] Cadastrar aluno no in�cio da lista. |\nO=======================================================O\n\n");

            //Pegar o Nome do aluno.
            printf("Digite o nome: ");
            setbuf(stdin, NULL);
            fgets(aluno.nome, 248, stdin);

            //Pegar a Matr�cula do aluno (e verificar se o valor digitado est� entre 0 e 99999).
            do{
                printf("Digite a matricula: ");
                scanf("%d", &resp_mat);
                if(resp_mat>=0 && resp_mat<=99999){
                    printf("Valor v�lido. (ap�s a inser��o de todos os dados, ser� verificado se j� h� algum aluno com essa matr�cula).\n");
                    verif=0;
                }else{
                    printf("Valor inv�lido. digite um valor que esteja no intervalo 0 <= X <= 99999.\n");
                    verif=1;
                }
            }while(verif);

            //Pegar a Nota do aluno (e verificar se o valor digitado est� entre 0 e 10 (float)).
            do{
                printf("Digite a nota do aluno: ");
                scanf("%f", &aluno.nota);
                if(aluno.nota>=0.0 && aluno.nota<=10.0){
                    verif=0;
                }else{
                    printf("Valor inv�lido. digite um valor que esteja no intervalo 0 <= X <= 10.\n");
                    verif=1;
                }
            }while(verif);

            //Pegar a frequ�ncia do aluno (e verificar se o valor digitado est� entre 0 e 100 (float)).
            do{
               printf("Digite a frequ�ncia do aluno: ");
                    scanf("%f", &aluno.frequencia);
                    if(aluno.frequencia>=0.0 && aluno.frequencia<=100.0){
                    verif=0;
                }else{
                    printf("Valor inv�lido. digite um valor que esteja no intervalo 0 <= X <= 100.\n");
                    verif=1;
                }
            }while(verif);

            //Pegar turma do aluno [A/B]
            do{
                printf("Digite a turma do aluno: ");
                setbuf(stdin, NULL);
                scanf("%c", &aluno.turma);

                if(aluno.turma!= 'A' && aluno.turma!='B'){
                    printf("Turma inv�lida. Escolha entre [A/B]\n");
                    verif=1;
                }else{
                    verif=0;
                }
            }while(verif);

            //Inserindo os dados cadastrados peo usu�rio na lista.
            inserirAluno(lista, aluno, resp_mat);

            //Imprimindo a lista.
            imprimeLista(lista);

            proxtela();
            break;

        case 2:
            system("cls");
            printf("O==================================O\n| Voc� escolheu [2] Remover aluno. |\nO==================================O\n\n");

            //Pegar a matr�cula digitada para o usu�rio, para verificar sua exist�ncia, e ent�o remov�-la.
            printf("Digite o n�mero da matr�cula que voc� deseja remover: ");
            scanf("%d", &num_mat);

            //Executar fun��o de remover aluno.
            if(removerAluno(lista, num_mat, aluno)==1){
                printf("\nAluno removido com sucesso.\n");
            }
            else{
                printf("\nN�o foi poss�vel fazer a remo��o, aluno n�o encontrado.\n");
            }

            proxtela();
            break;

        case 3:
            system("cls");
            printf("O=============================================O\n| Voc� escolheu [3] Pesquisar aluno por nome. |\nO=============================================O\n\n");

            //Pegar o nome do aluno.
            printf("Digite o nome do aluno que voc� deseja pesquisar: ");
            setbuf(stdin, NULL);
            fgets(pesq_nome, 248, stdin);

            //Procurar na lista algum nome igual. (pode haver mais de 1 nome).
            if(pesquisarAluno(lista, aluno, pesq_nome)==0){
                printf("\nAluno n�o encontrado.\n");
            }

            proxtela();
            break;

        case 4:
            system("cls");
            printf("O==================================================O\n| Voc� escolheu [4] Pesquisar aluno por matr�cula. |\nO==================================================O\n\n");

            //Pegar a matr�cula do aluno.
            printf("Digite o n�mero da matr�cula que voc� deseja pesquisar: ");
            scanf("%d", &pesq_mat);

            //Procurar na lista alguma matr�cula igual (s� pode haver (no m�ximo) 1 matr�cula igual � digitada).
            if(pesquisarMatricula(lista, aluno, pesq_mat)==0){
                printf("\nAluno n�o encontrado.\n");
            }

            proxtela();
            break;

        case 5:
            do{
            system("cls");
            printf("O=========================================================O\n| Voc� escolheu [5] Mostrar todos os alunos de uma turma. |\nO=========================================================O\n\n");

            printf("Digite qual turma voc� deseja ver os alunos: ");
            setbuf(stdin, NULL);
            scanf("%c", &pesq_turma);

            if(pesq_turma=='A' || pesq_turma=='B'){
                verif=0;
            }else{
                printf("\nTurma inv�lida, escolha entre [A/B].\n");
                verif=1;
                proxtela();
            }
            }while(verif);

            if(MostraAlPorTurma(lista, aluno, pesq_turma)==0){
                printf("\nN�o h� alunos na turma %c.\n", pesq_turma);
            }

            proxtela();
            break;

        case 6:
            system("cls");
            printf("O=============================================================O\n| Voc� escolheu [6] Ordenar toda a lista de alunos pelo nome. |\nO=============================================================O\n\n");

            if(OrdenaAluno(lista, aluno)==0){
                printf("N�o h� alunos cadastrados.\n");
            }else{
                imprimeLista(lista);
            }

            proxtela();
            break;

        case 7:
            system("cls");
            printf("O===============================================================O\n| Voc� escolheu [7] Mostrar os alunos com a maior e menor nota. |\nO===============================================================O\n\n");

            if(MostraAlByNota(lista, aluno) == 0){
                printf("N�o h� alunos cadastrados.\n");
            }

            proxtela();
            break;

        case 8:
            system("cls");
            printf("O=========================O\n| Voc� escolheu [8] Sair. |\nO=========================O\n\n");


            if(LimpaLista(lista)==0){
                printf("N�o haviam elementos na lista, portanto, ela n�o precisou ser limpa.\n");
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
            printf("O valor digitado � inv�lido. Escolha algo entre 1 e 8.\n");
            proxtela();
            break;
        }
    }while(valor!=8);
    return 0;
}



//kkkkkkkkkkkkk
