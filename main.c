#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "C:\Users\PRO\OneDrive\Bureau\assignment_of_c\c-assignment\patient_folder\patient.c"
#include "C:\Users\PRO\OneDrive\Bureau\assignment_of_c\c-assignment\doctor_folder\doctor.c"
#include "C:\Users\PRO\OneDrive\Bureau\assignment_of_c\c-assignment\nurse_folder\Nurse.c"
#define MAX_ADMINS 3
#define MAX_USERS 100
#define MAX_INVENTORY_OF_ITEMS 100

#define INVENTORY_FILE "inventory.txt"
#define APPOINTMENTS_FILE "appointments.txt"
#define PATIENTS_FILE "patients.txt"
#define DOCTORS_FILE "doctors.txt"
#define NURSES_FILE "nurses.txt"
#define ADMINS_FILE "admins.txt"

typedef struct Admin {
    char username[20];
    char password[20];
} Admin;

typedef struct User {
    char role[10];
    char first_name[20];
    char last_name[20];
    char dob[11];  // dd/mm/yyyy format
    char gender[10];
} User;

typedef struct InventoryItem {
    char name[30];
    int quantity;
} InventoryItem;

Admin admins[MAX_ADMINS];
int num_admins = 0;

User users[MAX_USERS];
int num_users = 0;

InventoryItem inventory[MAX_INVENTORY_OF_ITEMS];
int num_inventory_items = 0;

Admin *current_user = NULL;

void superadmin_functions();
void hospital_admin_functions();
void register_user();
void view_inventory();
void search_inventory();
void identify_peak_appointment_times();
void login();
void logout();
void add_inventory_item();

int main() {
    printf("\n");
    printf("********************************************\n");
    printf("*                                          *\n");
    printf("*      Welcome to the Hospital System      *\n");
    printf("*                                          *\n");
    printf("********************************************\n");

    char input[10];
    int choice;

    while (1) {
        printf("\n1. Superadmin\n2. Hospital administrator\n3. Staff\n4. Doctor\n5. Patient\n6. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                superadmin_functions();
                break;
            case 2:
                hospital_admin_functions();
                break;
            case 3:
                // Call staff functions here
                nursefunction();
                break;
            case 4:
                // Call doctor functions here
                doctor_functions();
                break;
            case 5:
                // Call patient functions here
                patientfunction();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid option.\n");
        }
    }

    return 0;
}

void superadmin_functions() {
    char input[10];
    int choice;

    while (1) {
        printf("\n********************************************\n");
        printf("*          Superadmin Functions            *\n");
        printf("********************************************\n");
        printf("\n1. Create new admin\n2. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (num_admins >= MAX_ADMINS) {
                    printf("Maximum number of admins reached.\n");
                    break;
                }

                printf("Enter username: ");
                scanf("%s",admins[num_admins].username);
                printf("Enter password: ");
                scanf("%s",admins[num_admins].password);
                num_admins++;

                FILE *file = fopen(ADMINS_FILE, "a");
                if (file != NULL) {
                    fprintf(file, "%s %s\n", admins[num_admins-1].username, admins[num_admins-1].password);
                    fclose(file);
                    printf("Admin created successfully.\n");
                } else {
                    printf("Error: Unable to open admins file.\n");
                }
                break;
            case 2:
                return;
            default:
                printf("Invalid option.\n");
        }
    }
}

void hospital_admin_functions() {
    login();

    char input[10];
    int choice;

    while (current_user != NULL) {
        printf("\n********************************************\n");
        printf("*     Hospital Administrator Functions     *\n");
        printf("********************************************\n");
        printf("\n1. Register User\n2. View inventory\n3. Search inventory\n4. Add to inventory\n5. Appointment Trends\n6. Logout\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                register_user();
                break;
            case 2:
                view_inventory();
                break;
            case 3:
                search_inventory();
                break;
            case 4:
                add_inventory_item();
                break;
            case 5:
                identify_peak_appointment_times();
                break;
            case 6:
                logout();
                return;
            default:
                printf("Invalid option.\n");
        }
    }
}

void login() {
    char username[20], password[20];

    while (1) {
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        FILE *file = fopen(ADMINS_FILE, "r");
        if (file == NULL) {
            printf("Error: Unable to open admins file.\n");
            return;
        }

        int found = 0;
        char admin_username[20], admin_password[20];
        while (fscanf(file, "%s %s", admin_username, admin_password) == 2) {
            if (strcmp(admin_username, username) == 0 && strcmp(admin_password, password) == 0) {
                found = 1;
                break;
            }
        }

        fclose(file);

        if (found) {
            printf("Login successful!\n");
            current_user = malloc(sizeof(Admin));
            strcpy(current_user->username, username);
            strcpy(current_user->password, password);
            break;
        } else {
            printf("Login failed. Invalid username or password.\n");
        }
    }
}

void logout() {
    free(current_user);
    current_user = NULL;
    printf("Logout successful.\n");
}

void register_user() {
    char role[10];
    char first_name[20], last_name[20], dob[11], gender[10];
    char full_name[50];

    printf("Enter role (patient, doctor, or nurse): ");
    scanf("%s",role);

    printf("Enter first name: ");
    scanf("%s",first_name);

    printf("Enter last name: ");
    scanf("%s",last_name);

    printf("Enter date of birth (dd/mm/yyyy): ");
    scanf("%s",dob);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Enter gender (male or female): ");
    scanf("%s",gender);

    if (strcmp(role, "doctor") == 0) {
        snprintf(full_name, sizeof(full_name), "Dr. %s %s", first_name, last_name);
    } else if (strcmp(role, "nurse") == 0) {
        snprintf(full_name, sizeof(full_name), "N. %s %s", first_name, last_name);
    } else if (strcmp(role, "patient") == 0) {
        if (strcmp(gender, "male") == 0) {
            snprintf(full_name, sizeof(full_name), "Mr. %s %s", first_name, last_name);
        } else if (strcmp(gender, "female") == 0) {
            snprintf(full_name, sizeof(full_name), "Ms. %s %s", first_name, last_name);
        } else {
            snprintf(full_name, sizeof(full_name), "%s %s", first_name, last_name);
        }
    } else {
        printf("Invalid role.\n");
        return;
    }

    if (num_users >= MAX_USERS) {
        printf("Maximum number of users reached.\n");
        return;
    }

    strcpy(users[num_users].first_name, first_name);
    strcpy(users[num_users].last_name, last_name);
    strcpy(users[num_users].dob, dob);
    strcpy(users[num_users].gender, gender);
    strcpy(users[num_users].role, role);
    num_users++;

    FILE *file;
    if (strcmp(role, "patient") == 0) {
        file = fopen(PATIENTS_FILE, "a");
    } else if (strcmp(role, "doctor") == 0) {
        file = fopen(DOCTORS_FILE, "a");
    } else if (strcmp(role, "nurse") == 0) {
        file = fopen(NURSES_FILE, "a");
    } else {
        printf("Invalid role.\n");
        return;
    }

    fprintf(file, "%s %s %s %s\n", full_name, dob, gender, role);
    fclose(file);

    printf("User registered successfully.\n");
}

void view_inventory() {
    FILE *file = fopen(INVENTORY_FILE, "r");
    if (file == NULL) {
        printf("Error: Unable to open inventory file.\n");
        return;
    }

    char item_name[30];
    int quantity;
    printf("\nInventory:\n");
    printf("Item Name\t\tQuantity\n");
    printf("----------------------------\n");
    while (fscanf(file, "%29s %d", item_name, &quantity) != EOF) {
        printf("%-20s\t%d\n", item_name, quantity);
    }

    fclose(file);
}

void search_inventory() {
    char search_item[30];
    printf("Enter item name to search: ");
    scanf("%s",search_item);

    FILE *file = fopen(INVENTORY_FILE, "r");
    if (file == NULL) {
        printf("Error: Unable to open inventory file.\n");
        return;
    }

    char item_name[30];
    int quantity;
    int found = 0;
    while (fscanf(file, "%s %d", item_name, &quantity) == 2) {
        if (strcmp(item_name, search_item) == 0) {
            printf("Item: %s, Quantity: %d\n", item_name, quantity);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Item not found in inventory.\n");
    }
}

void add_inventory_item() {
    char item_name[30];
    int quantity;

    printf("Enter item name: ");
    scanf("%s",item_name);

    printf("Enter quantity: ");
    scanf("%d", &quantity);
    getchar();

    FILE *file = fopen(INVENTORY_FILE, "a");
    if (file == NULL) {
        printf("Error: Unable to open inventory file.\n");
        return;
    }

    fprintf(file, "%s %d\n", item_name, quantity);
    fclose(file);

    printf("Inventory item added successfully.\n");
}

void identify_peak_appointment_times() {
    FILE *file = fopen(APPOINTMENTS_FILE, "r");
    if (file == NULL) {
        printf("Error: Unable to open appointments file.\n");
        return;
    }

    char patient_name[30], appointment_id[10], date[11], time[6], doctor_name[30];
    int hour, counts[24] = {0};

    printf("Reading appointments from file...\n");

    while (fscanf(file, "%s %s %s %s %s", patient_name, appointment_id, date, time, doctor_name) == 5) {
        printf("Read appointment: %s %s %s %s %s\n", patient_name, appointment_id, date, time, doctor_name);
        sscanf(time, "%2d:", &hour);

        if (hour >= 0 && hour < 24) {
            counts[hour]++;
        } else {
            printf("Warning: Invalid hour detected: %d\n", hour);
        }
    }

    fclose(file);

    int peak_hour = 0;
    for (int i = 1; i < 24; i++) {
        if (counts[i] > counts[peak_hour]) {
            peak_hour = i;
        }
    }

    printf("Peak appointment hour: %02d:00 with %d appointments.\n", peak_hour, counts[peak_hour]);
}
