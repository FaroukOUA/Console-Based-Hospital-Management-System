#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_DOCTORS 10  // Increased to allow adding more doctors
#define MAX_INVENTORY_ITEMS 10
#define MAX_REPORTS 10
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    char schedule[100];
} Doctor;

typedef struct {
    char itemName[MAX_NAME_LENGTH];
    int quantity;
} InventoryItem_nurse;

typedef struct {
    char patientName[MAX_NAME_LENGTH];
    char reportDetails[200];
} Report;

Doctor doctors[MAX_DOCTORS];
InventoryItem_nurse inventory_nurse[MAX_INVENTORY_ITEMS];
Report reports[MAX_REPORTS];

bool loggedIn = false;

void loadDoctors() {
    FILE *file = fopen("nurse_folder\\doctorschedules.txt", "r");
    if (file == NULL) {
        printf("Error opening doctorschedules.txt\n");
        return;
    }
    for (int i = 0; i < MAX_DOCTORS; i++) {
        if (fscanf(file, "%[^,], %[^\n]\n", doctors[i].name, doctors[i].schedule) == EOF) {
            break;
        }
    }
    fclose(file);
}

void saveDoctors() {
    FILE *file = fopen("nurse_folder\\doctorschedules.txt", "w");
    if (file == NULL) {
        printf("Error opening doctorschedules.txt\n");
        return;
    }
    for (int i = 0; i < MAX_DOCTORS; i++) {
        if (strlen(doctors[i].name) > 0) {
            fprintf(file, "%s, %s\n", doctors[i].name, doctors[i].schedule);
        }
    }
    fclose(file);
}

void loadInventory() {
    FILE *file = fopen("nurse_folder\\inventory.txt", "r");
    if (file == NULL) {
        printf("Error opening inventory.txt\n");
        return;
    }
    for (int i = 0; i < MAX_INVENTORY_ITEMS; i++) {
        if (fscanf(file, "%[^,], %d\n", inventory_nurse[i].itemName, &inventory_nurse[i].quantity) == EOF) {
            break;
        }
    }
    fclose(file);
}

void saveInventory() {
    FILE *file = fopen("nurse_folder\\inventory.txt", "w");
    if (file == NULL) {
        printf("Error opening inventory.txt\n");
        return;
    }
    for (int i = 0; i < MAX_INVENTORY_ITEMS; i++) {
        if (inventory_nurse[i].quantity > 0) {
            fprintf(file, "%s, %d\n", inventory_nurse[i].itemName, inventory_nurse[i].quantity);
        }
    }
    fclose(file);
}

void loadReports() {
    FILE *file = fopen("nurse_folder\\reports.txt", "r");
    if (file == NULL) {
        printf("Error opening reports.txt\n");
        return;
    }
    for (int i = 0; i < MAX_REPORTS; i++) {
        if (fscanf(file, "%[^,], %[^\n]\n", reports[i].patientName, reports[i].reportDetails) == EOF) {
            break;
        }
    }
    fclose(file);
}

bool checkCredentials(const char* username, const char* password) {
    FILE *file = fopen("nurse_folder\\logincredentials.txt", "r");
    if (file == NULL) {
        printf("Error opening logincredentials.txt\n");
        return false;
    }

    char storedUsername[MAX_NAME_LENGTH];
    char storedPassword[MAX_NAME_LENGTH];
    bool valid = false;

    while (fscanf(file, "%[^,], %[^\n]\n", storedUsername, storedPassword) != EOF) {
        if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
            valid = true;
            break;
        }
    }

    fclose(file);
    return valid;
}

void saveReports() {
    FILE *file = fopen("nurse_folder\\reports.txt", "w");
    if (file == NULL) {
        printf("Error opening reports.txt\n");
        return;
    }
    for (int i = 0; i < MAX_REPORTS; i++) {
        if (strlen(reports[i].patientName) > 0) {
            fprintf(file, "%s, %s\n", reports[i].patientName, reports[i].reportDetails);
        }
    }
    fclose(file);
}

void login_nurse() {
    char username[MAX_NAME_LENGTH];
    char password[MAX_NAME_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (checkCredentials(username, password)) {
        loggedIn = true;
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
    }
}

void logout_nurse() {
    loggedIn = false;
    printf("Logged out successfully.\n");
}

void registerNewUser() {
    if (!loggedIn) {
        printf("Please log in first.\n");
        return;
    }else{printf("okokokok");}

    char username[MAX_NAME_LENGTH];
    char password[MAX_NAME_LENGTH];

    FILE *file = fopen("nurse_folder\\logincredentials.txt", "a");
    if (file == NULL) {
        printf("Error opening logincredentials.txt\n");
        return;
    }

    printf("Enter new username: ");
    scanf("%s", username);
    printf("Enter new password: ");
    scanf("%s", password);

    fprintf(file, "%s, %s\n", username, password);
    fclose(file);

    printf("Account Registered Successfully\n");
}

void viewDoctorSchedules() {
    if (!loggedIn) {
        printf("Please log in first.\n");
        return;
    }
    printf("Doctor Schedules:\n");
    for (int i = 0; i < MAX_DOCTORS; i++) {
        if (strlen(doctors[i].name) > 0) {
            printf("%s: %s\n", doctors[i].name, doctors[i].schedule);
        }
    }
}

void updateDoctorSchedule() {
    if (!loggedIn) {
        printf("Please log in first.\n");
        return;
    }

    char doctorName[MAX_NAME_LENGTH];
    char newSchedule[100];

    printf("Enter doctor's name to update: ");
    fgets(doctorName, sizeof(doctorName), stdin);
    doctorName[strcspn(doctorName, "\n")] = 0; // Remove newline character

    printf("Enter new schedule: ");
    fgets(newSchedule, sizeof(newSchedule), stdin);
    newSchedule[strcspn(newSchedule, "\n")] = 0; // Remove newline character

    bool doctorFound = false;
    for (int i = 0; i < MAX_DOCTORS; i++) {
        if (strcmp(doctors[i].name, doctorName) == 0) {
            strcpy(doctors[i].schedule, newSchedule);
            doctorFound = true;
            printf("Schedule updated successfully for %s.\n", doctorName);
            saveDoctors(); // Save the updated schedule
            break;
        }
    }

    if (!doctorFound) {
        printf("Doctor not found.\n");
    }
}

void addDoctor() {
    if (!loggedIn) {
        printf("Please log in first.\n");
        return;
    }

    char doctorName[MAX_NAME_LENGTH];
    char doctorSchedule[100];

    printf("Enter new doctor's name: ");
    fgets(doctorName, sizeof(doctorName), stdin);
    doctorName[strcspn(doctorName, "\n")] = 0; // Remove newline character

    printf("Enter new doctor's schedule: ");
    fgets(doctorSchedule, sizeof(doctorSchedule), stdin);
    doctorSchedule[strcspn(doctorSchedule, "\n")] = 0; // Remove newline character

    bool doctorAdded = false;
    for (int i = 0; i < MAX_DOCTORS; i++) {
        if (strlen(doctors[i].name) == 0) {
            strcpy(doctors[i].name, doctorName);
            strcpy(doctors[i].schedule, doctorSchedule);
            doctorAdded = true;
            printf("Doctor %s added successfully.\n", doctorName);
            saveDoctors(); // Save the new doctor
            break;
        }
    }

    if (!doctorAdded) {
        printf("No space to add a new doctor.\n");
    }
}

void manageInventory() {
    if (!loggedIn) {
        printf("Please log in first.\n");
        return;
    }

    int choice;
    do {
        printf("\nInventory Management:\n");
        for (int i = 0; i < MAX_INVENTORY_ITEMS; i++) {
            if (inventory_nurse[i].quantity > 0) {
                printf("%s: %d\n", inventory_nurse[i].itemName, inventory_nurse[i].quantity);
            }
        }

        printf("Enter 1 to add item, 2 to update quantity, 0 to exit: ");
        scanf("%d", &choice);
        getchar(); // To consume the newline character left in the buffer by scanf

        if (choice == 0) return;

        char itemName[MAX_NAME_LENGTH];
        int quantity;

        if (choice == 1) {
            printf("Enter item name: ");
            fgets(itemName, sizeof(itemName), stdin);
            itemName[strcspn(itemName, "\n")] = 0; // Remove the newline character

            printf("Enter quantity: ");
            scanf("%d", &quantity);
            getchar(); // To consume the newline character left in the buffer by scanf

            bool itemAdded = false;
            for (int i = 0; i < MAX_INVENTORY_ITEMS; i++) {
                if (inventory_nurse[i].quantity == 0) {
                    strcpy(inventory_nurse[i].itemName, itemName);
                    inventory_nurse[i].quantity = quantity;
                    itemAdded = true;
                    printf("Item added successfully.\n");
                    saveInventory(); // Save after adding the item
                    break;
                }
            }
            if (!itemAdded) {
                printf("Inventory is full. Cannot add more items.\n");
            }
        } else if (choice == 2) {
            printf("Enter item name to update: ");
            fgets(itemName, sizeof(itemName), stdin);
            itemName[strcspn(itemName, "\n")] = 0; // Remove the newline character

            printf("Enter new quantity: ");
            scanf("%d", &quantity);
            getchar(); // To consume the newline character left in the buffer by scanf

            bool itemFound = false;
            for (int i = 0; i < MAX_INVENTORY_ITEMS; i++) {
                if (strcmp(inventory_nurse[i].itemName, itemName) == 0) {
                    inventory_nurse[i].quantity = quantity;
                    itemFound = true;
                    printf("Item quantity updated successfully.\n");
                    saveInventory(); // Save after updating the item
                    break;
                }
            }

            if (!itemFound) {
                printf("Item not found.\n");
            }
        }
    } while (choice != 0);
}

void generateReport() {
    if (!loggedIn) {
        printf("Please log in first.\n");
        return;
    }

    char patientName[MAX_NAME_LENGTH];
    char reportDetails[200];

    printf("Enter patient name: ");
    fgets(patientName, sizeof(patientName), stdin);
    patientName[strcspn(patientName, "\n")] = 0; // Remove the newline character

    printf("Enter report details: ");
    fgets(reportDetails, sizeof(reportDetails), stdin);
    reportDetails[strcspn(reportDetails, "\n")] = 0; // Remove the newline character

    bool reportAdded = false;
    for (int i = 0; i < MAX_REPORTS; i++) {
        if (strlen(reports[i].patientName) == 0) {
            strcpy(reports[i].patientName, patientName);
            strcpy(reports[i].reportDetails, reportDetails);
            reportAdded = true;
            printf("Report for %s added successfully.\n", patientName);
            saveReports(); // Save the new report
            break;
        }
    }

    if (!reportAdded) {
        printf("No space to add a new report.\n");
    }
}

void viewReports() {
    if (!loggedIn) {
        printf("Please log in first.\n");
        return;
    }

    printf("Reports:\n");
    for (int i = 0; i < MAX_REPORTS; i++) {
        if (strlen(reports[i].patientName) > 0) {
            printf("Patient: %s\nReport: %s\n", reports[i].patientName, reports[i].reportDetails);
        }
    }
}

void menu() {
    int choice;

    while (1) {
        printf("\n");
        printf("********************************************\n");
        printf("*                Nurse Menu                *\n");
        printf("********************************************\n");
        printf("1. Login\n");
        printf("2. Logout\n");
        printf("3. Register New User\n");
        printf("4. View Doctor Schedules\n");
        printf("5. Update Doctor Schedule\n");
        printf("6. Add New Doctor\n");
        printf("7. Manage Inventory\n");
        printf("8. Generate Report\n");
        printf("9. View Reports\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // To consume the newline character left in the buffer by scanf

        switch (choice) {
            case 1:
                login_nurse();
                break;
            case 2:
                logout_nurse();
                break;
            case 3:
                registerNewUser();
                break;
            case 4:
                viewDoctorSchedules();
                break;
            case 5:
                updateDoctorSchedule();
                break;
            case 6:
                addDoctor();
                break;
            case 7:
                manageInventory();
                break;
            case 8:
                generateReport();
                break;
            case 9:
                viewReports();
                break;
            case 0:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

int nursefunction() {
    loadDoctors();
    loadInventory();
    loadReports();
    menu();
    return 0;
}
