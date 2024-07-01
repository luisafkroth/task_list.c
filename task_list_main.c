#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "task_list.h"

int main() {

     initializeRandom();
    
    taskNode *taskTree = NULL;  //Árvore principal
    taskNode *taskTreeTime = NULL; //Árvore criada com base no tempo

    while(1) {

        int choice;
        printf("\nMenu de Opcoes:\n\n");
        printf("1. Adicionar tarefa \n");
        printf("2. Visualizar tarefas \n");
        printf("3. Concluir tarefas \n");
        printf("4. Excluir tarefas \n");
        printf("5. Sair \n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
            {
                char description[300];
                int time;

                printf("\nDigite a descricao da tarefa a ser adicionada: ");
                scanf(" %[^\t\n]s", description);
                printf("Digite o tempo (em horas) para realizar esta tarefa: ");
                scanf("%d", &time);
                taskNode *newTask = createTask(taskTree, description, time);
                taskNode *newTask2 = (taskNode *)malloc(sizeof(taskNode));
                memcpy(newTask2, newTask, sizeof *newTask);
                taskTree = addTask(taskTree, newTask);  //Adiciona na árvore principal
                taskTreeTime = addTaskTime(taskTreeTime, newTask2);  //Adiciona na árvore baseada no tempo
                break;
            }
            case 2: 
            {
                int visualization;
                printf("\nVoce deseja visualizar: \n\n");
                printf("1.Todas as tarefas \n");
                printf("2. Tarefas ativas \n");
                printf("3. Tarefas concluidas \n");
                printf("\nDigite a opcao escolhida: ");
                scanf("%d", &visualization);

                if (visualization == 1) {
                    showActiveTasks(taskTreeTime);        ///Imprime primeiro todas as tarefas ativas
                    showCompletedTasks(taskTreeTime);     ///Depois imprime as concluídas
                    break;
                } else if (visualization == 2) {
                    showActiveTasks(taskTreeTime);
                    break;
                } else if (visualization == 3) {
                    showCompletedTasks(taskTreeTime);
                    break;
                } else {
                    printf("Opcao invalida! Tente novamente.\n");
                }
                break;
            }
            case 3:
            {
                int id;
                printf("Digite o ID da tarefa que voce deseja concluir. \n");
                scanf("%d", &id);
                if (idExists(taskTree, id) == 1) {
                    concludeTask(taskTree, id);       //Conclui a tarefa na árvore principal
                    concludeTask(taskTreeTime, id);   //Conclui a tarefa na árvore baseada no tempo
                    printf("Tarefa de ID %d concluida. \n", id);
                } else {
                    printf("Nao existe nenhuma tarefa com o ID %d \n", id);
                }
                break;
            }
            case 4:
            {
                int id;
                printf("Digite o ID da tarefa que voce deseja excluir. \n");
                scanf("%d", &id);
                if (idExists(taskTree, id)) {
                    taskTree = excludeTask(taskTree, id);      //Exclui a tarefa da árvore principal
                    taskTreeTime = excludeTask(taskTreeTime, id);  //Exclui a tarefa da árvore baseada no tempo
                    printf("Tarefa de ID %d excluida. \n", id);
                } else {
                    printf("Nao existe nenhuma tarefa com o ID %d \n", id);
                }
                break;
            }
            case 5:
            {
                printf("Saindo do programa...\n");
                exit(0);
            }
            default:
            {
                printf("Opcao invalida! Tente novamente.\n");
            }
        }
    }
}