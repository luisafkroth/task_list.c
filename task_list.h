#ifndef TASK_LIST_H
#define TASK_LIST_H

struct taskNode {
    int id;
    char description[300];
    int time;
    int status;  
    struct taskNode *left;
    struct taskNode *right;
    
};
typedef struct taskNode taskNode;


void initializeRandom();

int generateId();

int idExists( taskNode *root, int id);

taskNode* findById(taskNode *root, int id);

taskNode* createTask(taskNode *root, char *description, int time);

taskNode* addTask(taskNode *root, taskNode *newTask);

taskNode* addTaskTime(taskNode *root, taskNode *newTask);

void printTask(taskNode *task);

void showAllTasks(taskNode *root);

void showActiveTasks(taskNode *root);

void showCompletedTasks(taskNode *root);

void concludeTask(taskNode *root, int id);

taskNode* findMin(taskNode *root);

taskNode* excludeTask(taskNode *root, int id);
#endif