#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "task_list.h"

void initializeRandom() { /// Função para iniciar o gerador de números aleatórios
    srand(time(NULL));
}

int generateId() {  /// Função para gerar um ID aleatório
    int id = (rand() % 100);
    return id;
}

int idExists( taskNode *root, int id) {  /// Função para checar se um ID existe
    if (root == NULL) {
        return 0; // False
    }
    if (root->id == id) {
        return 1; // True
    } else if (id < root->id) {
        return idExists(root->left, id);
    } else {
        return idExists(root->right, id);
    }
}


taskNode* findById(taskNode *root, int id) {
    if (root == NULL) {
        return NULL;
    }
    if (id == root->id) {
        return root;
    } else if (id < root->id) {
        return findById(root->left, id);
    } else {
        return findById(root->right, id);
    }
}

taskNode* createTask(taskNode *root, char *description, int time) {  ///Função para criar uma tarefa
    taskNode *newTask = (taskNode *)malloc(sizeof(taskNode));
    int id = generateId();
    while (idExists(root, id)) {             /// Loop para conferir se um ID existe, e, se sim, criar um novo ID
        id = generateId();
    }
    newTask->id = id;
    strncpy(newTask->description, description, sizeof(newTask->description) - 1);
    newTask->description[sizeof(newTask->description) - 1] = '\0'; 
    newTask->time = time;
    newTask->status = 1;         ///Tarefa ativa = 1 e concluída = 0
    newTask->left = NULL;
    newTask->right = NULL;
    return newTask;
}

taskNode* addTask(taskNode *root, taskNode *newTask)  /// Função para adicionar uma tarefa
{
    if (root==NULL) {
        return newTask;
    }
    printf("%p\n", root);
    if (newTask->id < root->id) {
        root->left = addTask(root->left, newTask);
    } else {
        root->right = addTask(root->right, newTask);
    }
    return root; 
}

taskNode* addTaskTime(taskNode *root, taskNode *newTask)  /// Função para adicionar uma tarefa na árvore baseada no tempo
{
    if (root==NULL) {
        return newTask;
    }
    if (newTask->time < root->time) {
        root->left = addTaskTime(root->left, newTask);
    } else {
        root->right = addTaskTime(root->right, newTask);
    }
    return root; 
}

void printTask(taskNode *task) {     /// Função para padronizar impressão de tarefas
    printf("-------------------------------------\n");
    printf("ID: %d \n", task->id);
    printf("Descricao: %s \n", task->description);
    printf("Tempo: %d horas \n", task->time);
     if (task->status == 1) {
        printf("Status: ATIVA\n");
    } else {
        printf("Status: CONCLUIDA\n"); 
    }
    printf("-------------------------------------\n");
}

void showActiveTasks(taskNode *root) {    ///Função para imprimir apenas as tarefas ativas
    if (root==NULL) return;
    showActiveTasks(root->left);
    if (root->status == 1) {
        printTask(root);
    }
    showActiveTasks(root->right);
}

void showCompletedTasks(taskNode *root) {    ///Função para imprimir apenas as tarefas concluídas
    if (root==NULL) return;
    showCompletedTasks(root->left);
    if (root->status == 0) {
        printTask(root);
    }
    showCompletedTasks(root->right);
}

void concludeTask(taskNode *root, int id) {        ///Função para concluir uma tarefa
    taskNode *task = findById(root, id);
    if (task != NULL) {
        task->status = 0;
    }
}

taskNode* findMin(taskNode *root)          /// Função para encontrar o nó com menor valor na subárvore direita
{
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

taskNode* excludeTask(taskNode *root, int id)  /// Função para excluir uma tarefa
{
    if (root == NULL) return root;
    if (id < root->id) {
        root->left = excludeTask(root->left, id);
    } else if (id > root->id) {
        root->right = excludeTask(root->right, id);
    } else {
        if (root->left == NULL) {
            taskNode *temp = root->right;
            free(root);
            return temp;        
        } else if (root->right == NULL) {
            taskNode *temp = root->left;
            free(root);
            return temp;
        }
        taskNode *temp = findMin(root->right);
        root->id = temp->id;
        strncpy(root->description, temp->description, sizeof(root->description) - 1);
        root->description[sizeof(root->description) - 1] = '\0';
        root->time = temp->time;
        root->status = temp->status;
        root->right = excludeTask(root->right, temp->id);
    }
    return root;
}