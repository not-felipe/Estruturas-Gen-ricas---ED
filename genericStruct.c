#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno {
    int matricula;
    int ano;
    char nome[50];
    char curso[100];
} Aluno;

typedef struct professor {
    int matricula;
    int salario;
    char nome[50];
} Professor;

typedef struct pessoas {
    int tipo; // 1 representa aluno, 2 representa professor
    void* item;
    struct pessoas* prox;
} Pessoas;

// Funções auxiliares
Pessoas* criarNo(int tipo, void* item) {
    Pessoas* novo = (Pessoas*)malloc(sizeof(Pessoas));
    novo->tipo = tipo;
    novo->item = item;
    novo->prox = NULL;
    return novo;
}

void destruirNo(Pessoas* no) {
    if (no->tipo == 1) {
        Aluno* aluno = (Aluno*)no->item;
        free(aluno);
    } else if (no->tipo == 2) {
        Professor* professor = (Professor*)no->item;
        free(professor);
    }
    free(no);
}

void inserirPessoa(Pessoas** lista) {
    int tipo;
    printf("A pessoa que deseja inserir e um aluno ou um professor?\n[1] Aluno\n[2] Professor\n[->] ");
    scanf("%d", &tipo);
    
    if (tipo != 1 && tipo != 2) {
        printf("Tipo de pessoa invalido.\n");
        return;
    }
    
    if (tipo == 1) {
        Aluno* aluno = (Aluno*)malloc(sizeof(Aluno));
        printf("Digite a matricula do aluno: ");
        scanf("%d", &(aluno->matricula));
        printf("Digite o ano do aluno: ");
        scanf("%d", &(aluno->ano));
        printf("Digite o nome do aluno: ");
        scanf(" %[^\n]s", aluno->nome);
        printf("Digite o curso do aluno: ");
        scanf(" %[^\n]s", aluno->curso);
        
        Pessoas* novo = criarNo(tipo, aluno);
        novo->prox = *lista;
        *lista = novo;
        
        printf("Aluno inserido com sucesso.\n");
    } else if (tipo == 2) {
        Professor* professor = (Professor*)malloc(sizeof(Professor));
        printf("Digite a matricula do professor: ");
        scanf("%d", &(professor->matricula));
        printf("Digite o salario do professor: ");
        scanf("%d", &(professor->salario));
        printf("Digite o nome do professor: ");
        scanf(" %[^\n]s", professor->nome);
        
        Pessoas* novo = criarNo(tipo, professor);
        novo->prox = *lista;
        *lista = novo;
        
        printf("Professor inserido com sucesso.\n");
    }
}

void removerPessoa(Pessoas** lista, int matricula) {
    Pessoas* atual = *lista;
    Pessoas* anterior = NULL;

    while (atual != NULL) {
        if (atual->tipo == 1) {
            Aluno* aluno = (Aluno*)atual->item;
            if (aluno->matricula == matricula) {
                if (anterior == NULL) {
                    *lista = atual->prox;
                } else {
                    anterior->prox = atual->prox;
                }
                destruirNo(atual);
                printf("Aluno removido com sucesso.\n");
                return;
            }
        } else if (atual->tipo == 2) {
            Professor* professor = (Professor*)atual->item;
            if (professor->matricula == matricula) {
                if (anterior == NULL) {
                    *lista = atual->prox;
                } else {
                    anterior->prox = atual->prox;
                }
                destruirNo(atual);
                printf("Professor removido com sucesso.\n");
                return;
            }
        }
        anterior = atual;
        atual = atual->prox;
    }

    printf("Pessoa com matricula %d nao encontrada.\n", matricula);
}

void buscarPessoa(Pessoas* lista, int matricula) {
    Pessoas* atual = lista;

    while (atual != NULL) {
        if (atual->tipo == 1) {
            Aluno* aluno = (Aluno*)atual->item;
            if (aluno->matricula == matricula) {
                printf("Aluno encontrado:\n");
                printf("Matricula: %d\n", aluno->matricula);
                printf("Ano: %d\n", aluno->ano);
                printf("Nome: %s\n", aluno->nome);
                printf("Curso: %s\n", aluno->curso);
                return;
            }
        } else if (atual->tipo == 2) {
            Professor* professor = (Professor*)atual->item;
            if (professor->matricula == matricula) {
                printf("Professor encontrado:\n");
                printf("Matricula: %d\n", professor->matricula);
                printf("Salario: %d\n", professor->salario);
                printf("Nome: %s\n", professor->nome);
                return;
            }
        }
        atual = atual->prox;
    }

    printf("Pessoa com matricula %d nao encontrada.\n", matricula);
}

int contarAlunosCurso(Pessoas* lista, const char* curso) {
    int contador = 0;
    Pessoas* atual = lista;

    while (atual != NULL) {
        if (atual->tipo == 1) {
            Aluno* aluno = (Aluno*)atual->item;
            if (strcmp(aluno->curso, curso) == 0) {
                contador++;
            }
        }
        atual = atual->prox;
    }

    return contador;
}

void imprimirProfessoresSalario(Pessoas* lista, int salarioMinimo) {
    printf("Professores com salario maior que %d:\n", salarioMinimo);
    Pessoas* atual = lista;

    while (atual != NULL) {
        if (atual->tipo == 2) {
            Professor* professor = (Professor*)atual->item;
            if (professor->salario > salarioMinimo) {
                printf("Matricula: %d\n", professor->matricula);
                printf("Salario: %d\n", professor->salario);
                printf("Nome: %s\n", professor->nome);
            }
        }
        atual = atual->prox;
        printf("\n");
    }
}

void destruirLista(Pessoas** lista) {
    Pessoas* atual = *lista;
    Pessoas* proximo;

    while (atual != NULL) {
        proximo = atual->prox;
        destruirNo(atual);
        atual = proximo;
    }

    *lista = NULL;
}

void exibirMenu() {
    printf("----- Menu -----\n");
    printf("[1] Inserir pessoa\n");
    printf("[2] Remover pessoa\n");
    printf("[3] Buscar pessoa\n");
    printf("[4] Contar numero de alunos em um curso\n");
    printf("[5] Imprimir professores com salario maior que um valor\n");
    printf("[6] Sair\n");
    printf("[->] ");
}

int main() {
    Pessoas* lista = NULL;
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirPessoa(&lista);
                break;
            case 2: {
                int matricula;
                printf("Digite a matricula da pessoa a ser removida: ");
                scanf("%d", &matricula);
                removerPessoa(&lista, matricula);
                break;
            }
            case 3: {
                int matricula;
                printf("Digite a matricula da pessoa a ser buscada: ");
                scanf("%d", &matricula);
                buscarPessoa(lista, matricula);
                break;
            }
            case 4: {
                char curso[100];
                printf("Digite o nome do curso: ");
                scanf(" %[^\n]s", curso);
                int contador = contarAlunosCurso(lista, curso);
                printf("Quantidade de pessoas no curso de %s: %d\n", curso, contador);
                break;
            }
            case 5: {
                int salarioMinimo;
                printf("Digite o salario mínimo: ");
                scanf("%d", &salarioMinimo);
                imprimirProfessoresSalario(lista, salarioMinimo);
                break;
            }
            case 6:
                destruirLista(&lista);
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opção invalida.\n");
        }
    } while (opcao != 6);

    return 0;
}
