//Rawan Fares Abo Alrous  1231043  section:4
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct {  // define a Date data type.
    char day[10];
    char month[10];
    char year[10];
}Date;
struct task;
typedef struct task* Task;
struct task {
    char ID[8];
    char name[30];
    Task next;
    Date date;
    char duration [20];
    //char status[50];
};
int size = 0;
typedef Task List;
//return if the linked list is empty or not 
bool isEmpty(List head) {
    return  (head->next == NULL);
}
//returning the size of the linked list
int getSize(List head) {
    int size = 0;
    Task ptr = head;
    if (isEmpty(head)) {
        return 0;
    }
    else if (head == NULL) {
        printf("list is not found!");
        return 0;
    }
    while (ptr->next != NULL) {
        size++;
        ptr = ptr->next;
    }
    return size;
}
//function that creat the list 
List creatList() {
    List head;
    head = (List)malloc(sizeof(struct task));
    if (head == NULL) {
        printf("Memory allocation failed!,List not Created!\n");
        return NULL;
    }
    head->next = NULL;
    return head;
}
//function that load tasks from file 
/*done*/ void loadTasks(List head) {
    FILE* open = fopen("tasks.txt", "r");
    char taskSize[200]; //maximum length of line (task)
	if (open == NULL) {
		printf("file is not exist!\n");
		return;
	}
    if (head == NULL) { // if the linked list has been not created
        head = creatList();
        return;
    }
    while(fgets(taskSize,sizeof(taskSize),open)!=NULL){ //read file line by line and store each data in Task linkelist
        Task newTask = (Task)malloc(sizeof(struct task)); //creat a new Task + store the value inside it + let it points to null 
        if (newTask == NULL) {
            printf("Memory allocation failed!\n");
            fclose(open);
            return;
        }
        char* token = strtok(taskSize, "#");
        if (token == NULL)
            continue;
        strcpy(newTask->ID , token); 

        //extract name
        token = strtok(NULL, "#");
        if (token == NULL)
            continue;
        strcpy(newTask->name , token); //to copy the name
        
        //extract day
        token = strtok(NULL, "/");
        if (token == NULL)
            continue;
        strcpy(newTask->date.day,token);

        // extract month
        token = strtok(NULL, "/");
        if (token == NULL)
            continue;
        strcpy(newTask->date.month, token);

        // extract year
        token = strtok(NULL, "#");
        if (token == NULL)
            continue;
        strcpy(newTask->date.year, token);

        // extract duration
        token = strtok(NULL, "#");
        if (token == NULL)
            continue;
        strcpy(newTask->duration ,token); 

        //extract status
        /*
        token = strtok(NULL, "#");
        if (token == NULL)
            continue;
        strcpy(newTask->status ,token);
        */
        newTask->next = NULL;
        if (head->next == NULL) { //If the list is empty then add the first task after head
            head->next = newTask;
        }
        else { // if the list was'nt empty add tasks to the end of the list
            Task tail = head;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = newTask;
            tail = newTask;
        }
    }
    printf("Tasks have been loaded Successfully:)\n\n");
    fclose(open);
}
//function that search for tha task using id
/*done*/bool searchTask(Task head) {
    if (head == NULL) {
        printf("Linked List Not Found..\n");
        return false;
    }
    else if (isEmpty(head)) {
        printf("the list is empty!!");
        return false;
    }
    else {
        printf("Do you want to search for a task by Task ID or Task Name? Enter '0' for ID and '1' for Name:\n");
        int choice;
        char id[8] ;
        char taskName[50];
        scanf("%d", &choice);
        getchar();
        if (choice==0) { //search by id
            printf("Enter Task ID:\n");
            scanf("%s", id);
        }
        else if (choice==1) { //search by name
            printf("Enter Task Name:\n");  

            //dealing for reading multiwords strings correctly
            fgets(taskName, sizeof(taskName), stdin);
            int len = strlen(taskName);
            //to remove the \n from the end of the string
            if (taskName[len - 1] == '\n') { 
                taskName[len - 1] = '\0'; //every string end with this char
            }
        }
        else {
            printf("Choose only 0 or 1 !!!\n");
            return false;
        }
        Task target = head->next;
        while (target != NULL) {
            if (strcmp(target->ID , id)==0 || strcmp(target->name, taskName)==0) {
                printf("task you search for is found:)\n");
                return true;
            }
            target = target->next;
        }
    }
    printf("task you're searching for is not found:(\n");
    return false;
}
//function that add task to the system
/*done*/void addTask(Task head) {
    //creat a new task + store the value inside it + let it points to null 
    Task newTask = (Task)malloc(sizeof(struct task)); 
    if (newTask == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    //get the id of the task
    printf("Enter Task ID:\n");
    scanf("%s", (newTask->ID));
    Task target = head->next;

    //check if the id of the task is unique 
    while (target != NULL) {
        if (strcmp(target->ID, newTask->ID) == 0) {
            printf("ID you want to add is already existed:)\n");
            return;
        }
        target = target->next;
    }
    //get the name of the task
    printf("Enter Task Name: \" only one word:) \" \n");
    scanf("%s", newTask->name);

    //get the date of task (day,month,year)
    printf("Enter Task date(day, month, year) respectivly:\n");
    scanf("%s %s %s", (newTask->date.day), (newTask->date.month), (newTask->date.year));
        
    //get the duration of the task
    printf("Enter Task Duration in hours:\n");
    scanf("%s", (newTask->duration));

    /*
    printf("Enter Task Status:\n");
	scanf("%s", newTask->status);
    */
    newTask->next = NULL;
    if (head->next == NULL) { //If the node is empty then the head will points to the first node
          head->next = newTask;
    }
    else { // if the list was'nt empty 
        Task tail = head;

         while (tail->next != NULL) {
             tail = tail->next;
         }
          tail->next = newTask;
    }
    printf("task has been added successfully:)\n\n");
}
//function that delete a specific task using its id
/*done*/void deleteTask(Task head) {
    
    if (!isEmpty(head)) {  
        printf("Enter task ID to delete:\n");
        char id[8];
        scanf("%s", id);
        Task target1 = head->next;
        bool flag1 = false;
        //make sure if task id is existed or not
        while (target1 != NULL) {
            flag1 = false;
            if (strcmp(target1->ID, id) == 0) {
                flag1 = true;
                break;
            }
            target1 = target1->next;
        }
        if (!flag1) {
            printf("Task ID %s is not existed\n", id);
            return;
        }

        Task target = head->next;
        Task p = head;
        bool flag = false;
        if (strcmp(target->ID, id)==0) { //if the task ID that will be deleted  was in the first node
            head->next = target->next;
			target->next = NULL;
            free(target);
            flag = true;
            printf("Task %s has been deleted Successfully:)\n\n", id);
            return;
        }
        if (strcmp(target->ID, id) == 0 && target->next == NULL) { //if the list was only one task
            head->next = NULL;
            flag = true;
            target->next = NULL;
            free(target);
            printf("Task %s has been deleted Successfully:)\n\n", id);
            return;
        }
        while (target != NULL) { 
            if (strcmp(target->ID, id) == 0 && target->next == NULL) { //if the task that want to be deleted was the last
                p->next = NULL;
            }
            else if (strcmp(target->ID, id) == 0) {
                p->next = target->next;
                target->next = NULL;
            }
            p = target;
            target = target->next;
        } 
        free(target);
        printf("Task %s has been deleted Successfully:)\n\n", id);
        return;
    }
    else {
        printf("the list is empty\n");
        return;
    }
       
}
//overloaded function that delete a specific task from list and add it to perfom list
/*done*/Task deleteTask(List head,char id[8]) {
    if (!isEmpty(head)) {
        Task target1 = head->next;
        bool flag1 = false;
        //make sure if task id is existed or not
        while (target1 != NULL) {
            flag1 = false;
            if (strcmp(target1->ID, id) == 0) {
                flag1 = true;
                break;
            }
            target1 = target1->next;
        }
        if (!flag1) {
            printf("Task ID %s is not existed\n", id);
            return NULL;
        }

        Task target = head->next;
        Task p = head;
        bool flag = false;
        if (strcmp(target->ID, id) == 0) { //if the task ID that will be deleted  was in the first node
            head->next = target->next;
            target->next = NULL;
            flag = true;
            printf("Task %s has been deleted Successfully:)\n\n", id);
            return target;
        }
        if (strcmp(target->ID, id) == 0 && target->next == NULL) { //if the list was only one task
            head->next = NULL;
            flag = true;
            target->next = NULL;
            printf("Task %s has been deleted Successfully:)\n\n", id);
            return target;
        }
        while (target != NULL) {
            if (strcmp(target->ID, id) == 0 && target->next == NULL) { //if the task that want to be deleted was the last
                p->next = NULL;
                break;
            }
            else if (strcmp(target->ID, id) == 0) {
                p->next = target->next;
                target->next = NULL;
                break;
            }
            p = target;
            target = target->next;
        }
        
        printf("Task %s has been performed Successfully:)\n\n", id);
        return target;
    }
    else {
        printf("the list is empty\n");
        return NULL;
    }

}
//function that perform a task
/*done*/void performTask(List head, List perform) {
    printf("Enter task ID to perform:\n");
    char id[8];
    scanf("%s", id);
    Task performTask = deleteTask(head, id);
    if (performTask != NULL) {
        //strcpy(performTask->status, "performed");
        if (perform->next == NULL) { //the first task was performed
            perform->next = performTask;
        }
        else {
            Task tail = perform;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = performTask;
            performTask->next = NULL;
        }
    }
}
void unperformedTask(List head) {
    printf("Enter task id to unperform:\n");
    char id [8];
    scanf("%s", id);
    bool flag = false;
    if (head != NULL) {
        Task unperformTask = head->next;
        while (unperformTask != NULL) {
            flag = false;
            if (strcmp(unperformTask->ID , id)==0) {
               // strcpy(unperformTask->status, "unperformed");
                flag = true;
                return;
            }
			unperformTask = unperformTask->next;
        }
    }
	
   if(!flag){
        printf("the task you're trying to perform is not exists\n");
    }
}
//function that print the unperformed tasks
void printUnperformed(Task head) {
    if (head == NULL || head->next == NULL) {
        printf("Linked List Not Found..\n");
        return;
    }
    if (isEmpty(head)) {
        printf("the list is empty");
        return;
    }
    Task ptr = head->next;
    while (ptr != NULL) {
        /*
        if (strcmp(ptr->status , "unperformed")==0) {
            printf("ID: %d, Name: %s, Date: %d/%d/%d, Duration:%.2lf hours\n", ptr->ID, ptr->name, ptr->date.day, ptr->date.month, ptr->date.year, ptr->duration);
        }*/
        ptr = ptr->next;
    }
    printf("\n============================\n");
}
//function that prints the tasks 
/*done*/void printTasks(Task head) {
    if (head == NULL || head->next==NULL) {
        printf("Linked List Not Found..\n");
        return;
    }
    if (isEmpty(head)) {
        printf("the list is empty");
        return;
    }
    Task ptr = head->next;
    while (ptr != NULL) {
        printf("ID: %s | Name: %s | Date: % s/% s/% s | Duration:%s\n", ptr->ID,ptr->name,ptr->date.day, ptr->date.month, ptr->date.year,ptr->duration);
        ptr = ptr->next;
    }
    printf("\n============================\n");
}
void Exit() {
    printf("Good Bye:)\n");
}
int main()
{
    int choice ,id;
    List mainList = creatList();
    List perfomedList = creatList();
	List unperfomedList = creatList();
    do {
        printf("1.Load Tasks File\n");
        printf("2. Add a New Task\n");
        printf("3. Delete a Task\n");
        printf("4. Search for a Task\n");
        printf("5. View Unperformed Tasks\n");
        printf("6. Perform a Task\n");
        printf("7. Undo Last Performed Task\n");
        printf("8. View Performed Tasks\n");
        printf("9. Generate Summary Report\n10. Exit\n");
        printf("Enter your choice:\n");
        scanf("%d", &choice); //read user's choice
        switch(choice) {
        case 1:loadTasks(mainList);
            break;
        case 2:
            addTask(mainList);
            printTasks(mainList);
            break;
        case 3:
            deleteTask(mainList);
            printTasks(mainList);
            break;
        case 4:
            searchTask(mainList);
            break;
        case 5:
            printTasks(mainList);
			break;
		case 6:
			performTask(mainList, perfomedList);
			break;
        case 8:
			printTasks(perfomedList);
			break;
        case 10:
            Exit();
            break;
        }
    } while (choice != 10);

        return 0;
}
