
typedef enum {
    ATIVA,
    CONCLUIDA
} Estado;

struct task {
    int id;
    char *description[300];
    int time;
    Estado status;  
    struct task *prev;
    struct task *next;
    
};
typedef struct task task;

struct list {
    struct task *head;
    struct task *tail;
};
typedef struct list list;

void init_list(list *list);

void addTask (list *list, char *description, int time);

task* findById(list *list, int id);

void showTasks(list *list);

void concludeTask(list *list, int id);

void excludeTask(list *list, int id);