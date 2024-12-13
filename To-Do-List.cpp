#include <bits/stdc++.h>
using namespace std;


struct Task {
    string description;
    string priority;
    Task* next; // pointer for the next node
};

// ## Add Task ##
void add_task(Task*& head, string desc, string prior) {
    Task* newTask = new Task(); // create new node
    newTask->description = desc; // store description task
    newTask->priority = prior; // store priority of task
    newTask->next = head; // connect the new node with our list
    head = newTask; // update head of list to point for new node
}

// ## Show Tasks ##
void display_tasks(Task* head) {
    cout << "To-Do List: " << endl;
    while(head != NULL) {
        cout << "- " << head->description << " [" << head->priority << "]" << endl; // print description task
        head = head->next; // traverse to next node
    }
}

// ## Delete any task ##
void delete_task(Task*& head, string desc) {
    Task* temp = head; // the current node
    Task* prev = NULL; // the previous node

    if(temp != NULL && temp->description == desc) { // if the first task
        head = temp->next; // update head of list
        delete temp;
        return;
    }

    while(temp != NULL && temp->description != desc) { // search of node
        prev = temp;
        temp  = temp->next;
    }

    // if task is not exist
    if(temp == NULL) return;

    prev->next = temp->next;
    delete temp;
}

// ## Mark task as a done ##
void markAsDone(Task*& head, string desc) {
    Task* temp = head;
    while(temp != NULL) {
        if(temp->description == desc) {
            temp->description += " (Done)"; // Adding a mark that the task is complete
            return;
        }
        temp = temp->next;
    }
    cout << "Task not found !" << endl;
}

// ## Show tasks is completed ##
void displayCompletedTasks(Task* head) {
    cout << "Completed Tasks:" << endl;
    while(head != NULL) {
        if(head->description.find("(Done)") != string::npos) {
            cout << "-> " << head->description << endl;
        }
        head = head->next;
    }
}

// ## Save the tasks to external file named "tasks.txt" ##
void saveToFile(Task* head) {
    ofstream file("tasks.txt"); // open file text for writing
    while(head != NULL) {
        file << head->description << "," << head->priority << endl;
        head = head->next; // traverse to the next node
    }
    file.close(); // close the file
    cout << "Tasks saved to file !" << endl;
}

// ## Load the tasks from file -> tasks.txt ##
void loadFromFile(Task*& head) {
    ifstream file("tasks.txt"); // open file on read mode
    string line, desc, priority;

    while(getline(file, line)) { // read all line from file
        size_t commaPos = line.find(","); // find the position of comma ,
        desc = line.substr(0, commaPos); // description of task before comma
        priority = line.substr(commaPos + 1); // priority of task after comma
        add_task(head, desc, priority); // add task to list
    }

    file.close();
    cout << "Tasks loaded from file !" << endl;
}


int main()
{
    Task* head = NULL;

    add_task(head, "Complete Project", "High");
    add_task(head, "Go To The GYM", "Medium");
    add_task(head, "Study For Exams", "Low");

    display_tasks(head);

    markAsDone(head, "Complete Project");
    cout << endl;
    cout << "After marking 'Complete Project' as Done" << endl;
    display_tasks(head);

    displayCompletedTasks(head);

    saveToFile(head);

    head = NULL; // clear list

    loadFromFile(head);
    cout << endl;
    cout << "After loading from file" << endl;
    display_tasks(head);


    return 0;
}
