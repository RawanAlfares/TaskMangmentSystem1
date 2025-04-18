//Rawan Fares Abo Alrous  1231043  section:4
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define a Date data type.
typedef struct {  
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
};
typedef Task List;

//return if the linked list is empty or not 
bool isEmpty(List head) {
    return  (head->next == NULL);
}
//function finds the last node of the list
List findTail(List list) {
    List tail = list;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    return tail;
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
void loadTasks(List head) {
    FILE* in = fopen("tasks.txt", "r");
    char taskSize[200]; //maximum length of line (task)
	if (in == NULL) {
		printf("file is not exist!\n");
		return;
	}
    if (head == NULL) { // if the linked list has not been created
        head = creatList();
        return;
    }
    while(fgets(taskSize,sizeof(taskSize), in)!=NULL){ //read file line by line and store each data in Task linkelist
        Task newTask = (Task)malloc(sizeof(struct task)); //creat a new Task + store the value inside it + let it points to null 
        if (newTask == NULL) {
            printf("Memory allocation failed!\n");
            fclose(in);
            return;
        }
        //extract ID
        char* token = strtok(taskSize, "#");
        if (token == NULL)
            continue;
        strcpy(newTask->ID , token); 

        //extract name
        token = strtok(NULL, "#");
        if (token == NULL)
            continue;
        strcpy(newTask->name , token); // copy the name
        
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

        newTask->next = NULL;

        //If the list is empty then add the first task after head
        if (head->next == NULL) { 
            head->next = newTask;
        }

        // if the list was'nt empty add tasks to the end of the list
        else { 
            Task tail = findTail(head);
            tail->next = newTask;
        }
    }
    printf("Tasks have been loaded Successfully:)\n\n");
    fclose(in);
}
//function that search for the task using id or name
bool searchTask(Task head) {
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

        //search by id
        if (choice==0) { 
            printf("Enter Task ID:\n");
            scanf("%s", id);
        }

        //search by name
        else if (choice==1) { 
            printf("Enter Task Name:\n");  

            //dealing for reading multiwords strings correctly
            fgets(taskName, sizeof(taskName), stdin);
            int len = strlen(taskName);
            //to remove the \n from the end of the string
            if (taskName[len - 1] == '\n') { 
                taskName[len - 1] = '\0'; //every string end with this char '\0'
            }
        }
        else {
            printf("Choose only 0 or 1 !!!\n\n");
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
void addTask(Task head) {
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
    printf("Enter Task Name:\n");
    scanf(" %[^\n]", newTask->name);

    //get the date of task (day,month,year)
    printf("Enter Task date(day, month, year) respectivly:\n");
    scanf("%s %s %s", (newTask->date.day), (newTask->date.month), (newTask->date.year));
        
    //get the duration of the task
    printf("Enter Task Duration in hours:\n");
    scanf("%s", (newTask->duration));

    newTask->next = NULL;
    //If the node is empty then the head will points to the first node
    if (head->next == NULL) { 
          head->next = newTask;
    }
    // if the list was'nt empty 
    else { 
        Task tail = findTail(head);
          tail->next = newTask;
    }
    printf("task has been added successfully:)\n\n");
}
//function that delete a specific task using its id
void deleteTask(Task head) {
    
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
//overloaded function that delete a specific task from list. this function only used in (perform a task function)
Task deleteTask(List head,char id[8]) {
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
void performTask(List head, List perform) {
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
            Task tail = findTail(perform);
            tail->next = performTask;
            performTask->next = NULL;
        }
    }
}
//function that prints  tasks 
void printTasks(Task head) {
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
//function that undo the last perform task and add it to the end of the unperformed task and to the undone list
void undo(List head, List perform,List undoneList) {
    if (head == NULL || head->next == NULL || perform == NULL || perform->next == NULL) {
        printf("the list is empty or not found!\n");
        return;
    }

    //get last task for each linked list
    List currPerform = findTail(perform);
    List currHead = findTail(head);

    List prevPerform = perform;
    //points to the previous node of tail
    while (prevPerform->next->next != NULL) {
        prevPerform = prevPerform->next;
    }
    prevPerform->next = NULL;

    //If the node is empty then the head will points to the first node
    if (head->next == NULL) { 
        head->next = currPerform;
    }
    else { // if the list was'nt empty 
        currHead->next = currPerform;
    }
   
    //creat a new node for undone list
    List newUndone = (List)malloc(sizeof(struct task));
    if (newUndone == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newUndone->next = NULL;

    //copy task information
    strcpy(newUndone->ID, currPerform->ID);
    strcpy(newUndone->name, currPerform->name);
    strcpy(newUndone->date.day, currPerform->date.day);
    strcpy(newUndone->date.month, currPerform->date.month);
    strcpy(newUndone->date.year, currPerform->date.year);
    strcpy(newUndone->duration, currPerform->duration);

    //add to undone list
    if (undoneList->next == NULL) {
        undoneList->next = newUndone;
    }
    else {
        Task tail2 = findTail(undoneList);
            tail2->next = newUndone;
    }
    printf("undo the last task successfully:)\n");
}
//fumction to exit from the task managment system
void Exit() {
    printf("BEST OF LUCK:)\n");
}
// function that write tasks to report file
void GenerateSummaryReport(List mainList,List performed,List undoneList) {
    FILE* Report = fopen("Report.txt", "w");
    if (Report == NULL) {
        printf("Error openeing file!\n");
        return;
    }
    if (performed == NULL || performed->next == NULL) {
        fprintf(Report, "No tasks in performed list.\n");
        return;
    }
    if (mainList == NULL || mainList->next == NULL) {
        fprintf(Report, "No tasks in unperformed or undone list.\n");
        return;
    }
    List temp = performed->next;
    fprintf(Report, "Performed tasks:\n============================\n");
    while (temp != NULL) {
        fprintf(Report, "\n%s\t", temp->ID);
        fprintf(Report, "%s\t", temp->name);
        fprintf(Report, "%s", temp->date.day);
        fprintf(Report, "/%s", temp->date.month);
        fprintf(Report, "/%s\t", temp->date.year);
        fprintf(Report, "%s", temp->duration);

        temp = temp->next;
    }

    fprintf(Report, "\n\nunPerformed tasks:\n============================\n");
    List temp2 = mainList->next;
    while (temp2 != NULL) {
        fprintf(Report, "\n%s\t", temp2->ID);
        fprintf(Report, "%s\t", temp2->name);
        fprintf(Report, "%s", temp2->date.day);
        fprintf(Report, "/%s", temp2->date.month);
        fprintf(Report ,"/%s\t", temp2->date.year);
        fprintf(Report, "%s", temp2->duration);

        temp2 = temp2->next;
    }
    fprintf(Report, "\n\nundone tasks:\n============================\n");
    List temp3 = undoneList->next;
    while (temp3 != NULL) {
        fprintf(Report, "\n%s\t", temp3->ID);
        fprintf(Report, "%s\t", temp3->name);
        fprintf(Report, "%s", temp3->date.day);
        fprintf(Report, "/%s", temp3->date.month);
        fprintf(Report, "/%s\t", temp3->date.year);
        fprintf(Report, "%s", temp3->duration);

        temp3 = temp3->next;
    }
    
    fclose(Report);
    printf("Tasks written to \"Report.txt\" successfully:)\n\n");
}
int main()
{
    int choice ,id;
    List mainList = creatList();
    List perfomedList = creatList();
	List undoneList = creatList();
    //List unperformedList = creatList();
    do {
        printf("1. Load Tasks File\n");
        printf("2. Add a New Task\n");
        printf("3. Delete a Task\n");
        printf("4. Search for a Task\n");
        printf("5. View Unperformed Tasks\n");
        printf("6. Perform a Task\n");
        printf("7. Undo Last Performed Task\n");
        printf("8. View Performed Tasks\n");
        printf("9. Generate Summary Report\n");
        printf("10. Exit\n");
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
            printf("mainlist:\n");
            printTasks(mainList);
            printf("performed list\n");
            printTasks(perfomedList);
			break;
        case 7:
            undo(mainList, perfomedList,undoneList);
            printf("unperformed:\n==========================\n");
            printTasks(mainList);
            printf("performed list\n==========================\n");
            printTasks(perfomedList);
            printf("undone list\n==========================\n");
            printTasks(undoneList);
            break;
        case 8:
			printTasks(perfomedList);
			break;
        case 9:
            GenerateSummaryReport(mainList, perfomedList,undoneList);
            break;
        case 10:
            Exit();
            break;
        }
    } while (choice != 10);

        return 0;
}
