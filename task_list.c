#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task_list.h"

void init_list(list *list)
{
	list->head=NULL;
	list->tail=NULL;
}

void addTask (list *list, char *description, int time)
{
    task *aux;
    aux = (task *)malloc(sizeof(task));
    strcpy(aux->description, description);
    aux->time = time;   
    aux->status = ATIVA;
    aux->next = NULL;
    if (list->head==NULL) {
        aux->id = 1;
        aux->prev = NULL;
        list->head = aux;
        list->tail = aux;
        return;
    }
    aux->id = list->tail->id+1;
    aux->prev = list->tail;
    list->tail->next = aux;
    list->tail = aux;
    return;
}

task* findById(list *list, int id) {
    task *aux;
    if (list == NULL || list->head == NULL) {
        printf("A lista está vazia!\n");
        return NULL;
    }
    for (aux=list->head; aux->next!=NULL; aux=aux->next) {
        if (aux->id==id) {
            return aux;
        }
    }
    printf("ID %d não encontrado! \n", id);
    return NULL;
}

void showTasks(list *list) {

}
void concludeTask(list *list, int id) {
    task *aux = findById(list, id);
    aux->status = CONCLUIDA;
}

void excludeTask(list *list, int id) {
    task *aux = findById(list, id);
    if (aux==list->head) {
        list->head = list->head->next;
        list->head->prev = NULL;
    } if (aux==list->tail) {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    } else {
        aux->prev->next = aux->next;
        aux->next->prev = aux->prev;
    }
    free(aux);
}