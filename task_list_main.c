#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task_list.h"

int main() {

    int choice;
    list *task_list;
    init_list(task_list);

    while(1) {

        printf("\nMenu de Opções:\n");
        printf("1. Adicionar tarefa \n");
        printf("2. Visualizar tarefas \n");
        printf("3. Concluir tarefas \n");
        printf("4. Excluir tarefas \n");
        printf("5. Sair \n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            char *description[300];
            int time;

            printf("Digite a descrição da tarefa a ser adicionada.");
            scanf("%s", description);
            printf("Digite o tempo (em horas) para realizar esta tarefa.");
            scanf("%d", &time);
            addTask(task_list, description,time);
            break;

        case 2:
            int visualization;
            while (1) {
                printf("Você deseja visualizar: \n");
                printf("1.Todas as tarefas \n");
                printf("2. Tarefas ativas \n");
                printf("3. Tarefas concluidas \n");
                printf("Digite a opção escolhida: ");
                scanf("%d", visualization);

                switch (choice) {
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    default:
                         printf("Opção inválida! Tente novamente.\n");
                }
            }
            break;
        case 3:
            int id;
            printf("Digite o ID da tarefa que você deseja concluir. \n");
            scanf("%d", &id);
            concludeTask(task_list, id);
            break;
        case 4:
            int id;
            printf("Digite o ID da tarefa que você deseja excluir. \n");
            scanf("%d", &id);
            excludeTask(task_list, id);
            break;
        case 5:
            printf("Saindo do programa...\n");
            exit(0);
        default:
            printf("Opção inválida! Tente novamente.\n");
        }
    }
}