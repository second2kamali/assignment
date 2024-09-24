#include <iostream>
#include <string>
using namespace std;

// Node structure for representing a task
struct Task {
    int id;             // Unique task ID
    string description; // Task description
    int priority;       // Task priority (higher value means higher priority)
    Task* next;         // Pointer to the next node
};

// Singly Linked List class to manage tasks
class TaskList {
private:
    Task* head;

public:
    TaskList() : head(nullptr) {}

    // Function to add a new task based on priority
    void addTask(int id, const string& description, int priority) {
        Task* newTask = new Task{id, description, priority, nullptr};

        if (!head || head->priority < priority) {
            newTask->next = head;
            head = newTask;
        } else {
            Task* current = head;
            while (current->next && current->next->priority >= priority) {
                current = current->next;
            }
            newTask->next = current->next;
            current->next = newTask;
        }

        cout << "Task added successfully.\n";
    }

    // Function to remove the task with the highest priority
    void removeHighestPriorityTask() {
        if (!head) {
            cout << "Task list is empty.\n";
            return;
        }

        Task* temp = head;
        head = head->next;
        cout << "Removed task with ID: " << temp->id << " (Highest priority)\n";
        delete temp;
    }

    // Function to remove a task by its ID
    void removeTaskById(int id) {
        if (!head) {
            cout << "Task list is empty.\n";
            return;
        }

        if (head->id == id) {
            Task* temp = head;
            head = head->next;
            delete temp;
            cout << "Removed task with ID: " << id << "\n";
            return;
        }

        Task* current = head;
        while (current->next && current->next->id != id) {
            current = current->next;
        }

        if (!current->next) {
            cout << "Task with ID: " << id << " not found.\n";
            return;
        }

        Task* temp = current->next;
        current->next = current->next->next;
        delete temp;
        cout << "Removed task with ID: " << id << "\n";
    }

    // Function to view all tasks
    void viewTasks() const {
        if (!head) {
            cout << "Task list is empty.\n";
            return;
        }

        Task* current = head;
        while (current) {
            cout << "ID: " << current->id << ", Description: " << current->description
                 << ", Priority: " << current->priority << "\n";
            current = current->next;
        }
    }

    // Destructor to free allocated memory
    ~TaskList() {
        while (head) {
            Task* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Menu for user interaction
void menu() {
    TaskList taskList;
    int choice;

    do {
        cout << "\nTask Management System\n";
        cout << "1. Add a new task\n";
        cout << "2. View all tasks\n";
        cout << "3. Remove the highest priority task\n";
        cout << "4. Remove a task by ID\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, priority;
                string description;
                cout << "Enter task ID: ";
                cin >> id;
                cout << "Enter task description: ";
                cin.ignore(); // To consume newline from previous input
                getline(cin, description);
                cout << "Enter task priority: ";
                cin >> priority;
                taskList.addTask(id, description, priority);
                break;
            }
            case 2:
                taskList.viewTasks();
                break;
            case 3:
                taskList.removeHighestPriorityTask();
                break;
            case 4: {
                int id;
                cout << "Enter task ID to remove: ";
                cin >> id;
                taskList.removeTaskById(id);
                break;
            }
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}

int main() {
    menu();
    return 0;
}
