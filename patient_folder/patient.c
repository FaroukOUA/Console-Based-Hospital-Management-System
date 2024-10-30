#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define MAX 256
typedef struct{
    char username[MAX];
    char med_history[MAX];
    char prescription[MAX];
    char appointment_history[MAX];
    char billing_info[MAX];
}EHR;
typedef struct{
    char username[MAX];
    char id[MAX];
    char amount[MAX];
    char status[MAX];
    char insurance_id[MAX];
    char claim_date[MAX];
    char claim_status[MAX];
}Billing;
typedef struct {
    char id[MAX];
    char username[MAX];
    char doctor[MAX];
    char date[MAX];
    char time[MAX];
}Appointment_patient;
typedef struct {
    char id[MAX];
    char password[MAX];
} Patient;

int login_patient(char *id, char *password);
void logout_patient();
void viewAppointments(char *patient_name);
void rescheduleAppointment(char *patient_name, char *appointment_id);
void cancelAppointment(char *patient_name, char *appointment_id);
void viewEHR(char *patient_name);
void viewBillingDetails(char *patient_name);//billing
void searchBillingInfo(char *patient_name, char *criteria);//billing
void displayMenu(char *patient_name);

int patientfunction() {
    printf("*******************************\n*    %-12s    *\n*******************************\n","Welcome back patient!");

    char patient_name[MAX];
    char password[MAX];

    printf("Enter your Username: ");
    scanf("%s", patient_name);
    printf("Enter Password: ");
    scanf("%s", password);

    if (login_patient(patient_name, password)) {
        printf("login_patient Successful\n");
        displayMenu(patient_name);
        logout_patient();
    } else {
        printf("Invalid Username or Password\n");
    }
    
    return 0;
}

void displayMenu(char *patient_name) {
    int choice;
    char appointment_id[MAX], criteria[MAX];

    while (1) {
        printf("\n***************************************\n*            %-25s*\n***************************************","Patient Menu");
        printf("\n*    %-33s*","1. Appointment Management");
        printf("\n*    %-33s*","2. EHR Access");
        printf("\n*    %-33s*","3. Billing Management");
        printf("\n*    %-33s*","4. Exit");
        printf("\n***************************************\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        putchar('\n');

        switch (choice) {
            case 1:
                while (1) {
                    printf("\n***************************************\n*            %-25s*\n***************************************","Appointment Management");
                    printf("\n*    %-33s*","1. View appointments");
                    printf("\n*    %-33s*","2. Reschedule appointments");
                    printf("\n*    %-33s*","3. Cancel appointments");
                    printf("\n*    %-33s*","4. Go back to main menu");
                    printf("\n*    %-33s*","5. Exit");
                    printf("\n***************************************\n");
                    printf("\nEnter your choice: ");
                    scanf("%d", &choice);
                    putchar('\n');

                    switch (choice) {
                        case 1:
                            viewAppointments(patient_name);
                            break;
                        case 2:
                            viewAppointments(patient_name);
                            //asking for new date to be replaced
                            printf("Enter Appointment ID to Reschedule: ");
                            scanf("%s", appointment_id);
            
                            rescheduleAppointment(patient_name, appointment_id);
                            break;
                        case 3:
                            printf("Enter Appointment ID to Cancel: ");
                            scanf("%s", appointment_id);
                            cancelAppointment(patient_name, appointment_id);
                            break;
                        case 4:
                            displayMenu(patient_name);
                            return;
                        case 5:
                            printf("Bye! See you next time ;)\n");
                            return;
                        default:
                            printf("Invalid choice, please try again.\n");
                    }
                }
                
                break;
            case 2://EHR
                viewEHR(patient_name);
                
                break;
            case 3://Billing
                while (1) {
                    printf("\n***************************************\n*            %-25s*\n***************************************","Billing Management");
                    printf("\n*    %-33s*","1. View Billing Details");
                    printf("\n*    %-33s*","2. Search Billing Details");
                    printf("\n*    %-33s*","3. Go back to Main Menu");
                    printf("\n*    %-33s*","4. Exit");
                    printf("\n***************************************\n");
                    printf("\nEnter your choice: ");
                    scanf("%d", &choice);
                    putchar('\n');

                    switch (choice) {
                        case 1://view
                            viewBillingDetails(patient_name);
                            break;
                        case 2://search
                            while(1){
                                printf("Choose one criteria:\n1. Billing ID\n2. Bill Status(paid/pending)\n3. Insurance Claim ID\n4. Insurance Status(Approved/Pending/Rejected)\n5. Go back to Main Menu\n6. Exit\nChoice: ");
                                scanf("%d",&choice);
                                switch (choice)
                                {
                                case 1:
                                    printf("Enter Billing ID: ");
                                    scanf("%s",criteria);
                                    searchBillingInfo(patient_name, criteria);
                                    break;
                                case 2:
                                    printf("Enter Billing Status(paid/pending): ");
                                    scanf("%s",criteria);
                                    searchBillingInfo(patient_name, criteria);
                                    break;
                                case 3:
                                    printf("Enter Insurance Claim ID(example: Claim_001): ");
                                    scanf("%s",criteria);
                                    searchBillingInfo(patient_name, criteria);
                                    break;
                                case 4:
                                    printf("Enter Insurance Status(Approved/Pending/Rejected): ");
                                    scanf("%s",&criteria);
                                    searchBillingInfo(patient_name, criteria);
                                    break;
                                case 5:
                                    displayMenu(patient_name);
                                    return;
                                case 6:
                                    printf("Bye! See you next time ;)\n");
                                    return;
                        
                                default:
                                    printf("Invalid choice, please try again.\n");
                                }
                            }
                            break;
                        case 3:
                            displayMenu(patient_name);
                            return;
                        case 4:
                            printf("Bye! See you next time ;)\n");
                            return;
                        default:
                            printf("Invalid choice, please try again.\n");
                    }
                }


                break;    
            case 4:
                printf("Bye! See you next time ;)\n");
                return;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
}

int login_patient(char *id, char *password) {
    FILE *file = fopen("patient_folder\\patientpass.txt", "r");
    if (file == NULL) {
        printf("Unable to open file\n");
        return 0;
    }

    Patient patient;
    while (fscanf(file, "%s %s", patient.id, patient.password) != EOF) {
        if (strcmp(id, patient.id) == 0 && strcmp(password, patient.password) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void logout_patient() {
    printf("Logged out successfully\n");
}

void viewAppointments(char *patient_name) {
    FILE *file = fopen("patient_folder\\appointments-patient.txt", "r");
    if (file == NULL) {
        printf("Unable to open file\n");
        return;
    }

    char line[MAX];
    char temp_line[MAX];
    
    Appointment_patient appointment;
    
    
    long pos;
    printf("Appointments:\n\n");
    while (fgets(line, sizeof(line), file)) {
        strcpy(temp_line,line);
        char* token = strtok(temp_line, " ");
        if (strcmp(token,patient_name)==0) {
            // Remove the newline character at the end of the line if present
            line[strcspn(line, "\n")] = '\0';

            // Parse the line and assign values to the struct
            sscanf(line, "%s %s %s %s %s",
                appointment.username,
                appointment.id,
                appointment.date,
                appointment.time,
                appointment.doctor);

            // Print the parsed values 
            printf("-ID: %s\n", appointment.id);
            printf("-Username: %s\n", appointment.username);
            printf("-Doctor: %s\n", appointment.doctor);
            printf("-Date: %s\n", appointment.date);
            printf("-Time: %s\n", appointment.time);
            printf("\n");
        }
    } 
    
    fclose(file);
}

void rescheduleAppointment(char *patient_name, char *appointment_id) {
    char new_date[MAX];
    char new_time[MAX];
    char temp_line[MAX];
    //asking the user for new date
    printf("Enter New Date (YYYY-MM-DD): ");
    scanf("%s", new_date);
    printf("Enter New Time (example --> 10:30): ");
    scanf("%s", new_time);

    FILE *inputFile = fopen("patient_folder\\appointments-patient.txt", "r");
    FILE *tempFile = fopen("patient_folder\\temp.txt", "w");
    if (inputFile == NULL || tempFile == NULL) {
        perror("Error opening file");
        return;
    }    

    char line[MAX];

    Appointment_patient appointment;
    while (fgets(line, sizeof(line), inputFile)) {
        strcpy(temp_line,line);
        char* token = strtok(temp_line, " ");
        // Remove the newline character at the end of the line if present
        line[strcspn(line, "\n")] = '\0';

        // Parse the line and assign values to the struct
        sscanf(line, "%s %s %s %s %s",
            appointment.username,
            appointment.id,
            appointment.date,
            appointment.time,
            appointment.doctor);
               
        //wrong date(error handling)
        if ((strcmp(appointment.date, new_date)==0) && (strcmp(appointment.time, new_time)==0)){
            printf("This date is already taken. Please try again\n");
            rescheduleAppointment(patient_name, appointment_id);
        }
        if ((strcmp(token,patient_name)==0) && strstr(line, appointment_id)) {
            
            break;
        }
            
    }
    

    rewind(inputFile);
    
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        char* token = strtok(temp_line, " ");

        char oldDateTime[MAX];
        oldDateTime[0] = '\0';
        strcat(oldDateTime, appointment.date);
        strcat(oldDateTime, " ");
        strcat(oldDateTime, appointment.time);   
        char *pos = strstr(line, oldDateTime);
        if ((strcmp(token,patient_name)==0) && strstr(line, appointment_id)) {
            if (pos != NULL ) {
                // Create a buffer for the modified line
                char modifiedLine[MAX];
                // Calculate the position of oldData in the line
                int index = pos - line;
                // Copy the part of the line before oldData
                strncpy(modifiedLine, line, index);
                modifiedLine[index] = '\0'; // Null-terminate the string
                // Concatenate newData and the part of the line after oldData
                strcat(modifiedLine, new_date);
                strcat(modifiedLine," ");
                strcat(modifiedLine,new_time);
                strcat(modifiedLine, pos + strlen(oldDateTime));
                // Copy the modified line back to line for writing
                strcpy(line, modifiedLine);
            }
        }
        fputs(line, tempFile);
        
    }
    //closing the files
    fclose(inputFile);
    fclose(tempFile);
    
    // Replacing the original file with the temporary file
    if (remove("patient_folder\\appointments-patient.txt") != 0) {
        perror("Error deleting the original file");
        return;
    }
    if (rename("patient_folder\\temp.txt", "patient_folder\\appointments-patient.txt") != 0) {
        perror("Error renaming the temporary file");
        return;
    }
    printf("\nAppointment rescheduled successfully!\n");    
}

void cancelAppointment(char *patient_name, char *appointment_id) {
    FILE *file = fopen("patient_folder\\appointments-patient.txt", "r");
    FILE *temp = fopen("patient_folder\\temp.txt", "w");
    if (file == NULL || temp == NULL) {
        printf("Unable to open file\n");
        return;
    }
    int found=0;
    char line[MAX];
    while (fgets(line, sizeof(line), file)) {
        if (!(strstr(line, patient_name) && strstr(line, appointment_id))) {
            fputs(line, temp);

        }else{
            found=1;
        }
    }
    if (!found){
        printf("There's no such Apointment ID");
        return;
    }
    fclose(file);
    fclose(temp);
    // Replace the original file with the temporary file
    if (remove("patient_folder\\appointments-patient.txt") != 0) {
        perror("Error deleting the original file");
        return;
    }
    if (rename("patient_folder\\temp.txt", "patient_folder\\appointments-patient.txt") != 0) {
        perror("Error renaming the temporary file");
        return;
    }
    printf("Appointment canceled!\n");
}

void viewEHR(char *patient_name){
    FILE *file = fopen("patient_folder\\ehr.txt", "r");
    if (file == NULL) {
        printf("Unable to open file\n");
        return;
    }

    char line[MAX];
    char temp_line[MAX];
    
    EHR ehr;
    
    long pos;
    printf("Electronic Health Records :\n\n");
    while (fgets(line, sizeof(line), file)) {
        strcpy(temp_line,line);
        char* token = strtok(temp_line, " ");
        if (strcmp(token,patient_name)==0) {
            // Remove the newline character at the end of the line if present
            line[strcspn(line, "\n")] = '\0';
            
            // Parse the line and assign values to the struct
            sscanf(line, "%s %s %s %s %s",
                ehr.username,
                ehr.med_history,
                ehr.prescription,
                ehr.appointment_history,
                ehr.billing_info);

            // Print the parsed values 
            printf("-Patient Name: %s\n", ehr.username);
            printf("-Medical History: %s\n", ehr.med_history);
            printf("-Prescription: %s\n", ehr.prescription);
            printf("-Appointments IDs: %s\n", ehr.appointment_history);
            printf("-Billing ID: %s\n\n", ehr.billing_info);
        }
    } 
    
    fclose(file);
}

void viewBillingDetails(char *patient_name) {
    FILE *file = fopen("patient_folder\\billing.txt", "r");
    if (file == NULL) {
        printf("Unable to open file\n");
        return;
    }

    char line[MAX];
    char temp_line[MAX];
    
    Billing billing;
    
    long pos;
    printf("\nBilling Details :\n\n");
    while (fgets(line, sizeof(line), file)) {
        strcpy(temp_line,line);
        char* token = strtok(temp_line, ",");
        if (strcmp(token,patient_name)==0) {
            // Remove the newline character at the end of the line if present
            line[strcspn(line, "\n")] = '\0';
            
            // Parse the line and assign values to the struct
            sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]",
                billing.username,
                billing.id,
                billing.amount,
                billing.status,
                billing.insurance_id,
                billing.claim_date,
                billing.claim_status);

            // Print the parsed values 
            printf("-Patient Name: %s\n", billing.username);
            printf("-Bill ID: %s\n", billing.id);
            printf("-Amount : %s\n", billing.amount);
            printf("-Status: %s\n", billing.status);
            printf("-Insurance Claim ID: %s\n", billing.insurance_id);
            printf("-Claim date: %s\n", billing.claim_date);
            printf("-Claim Status: %s\n\n", billing.claim_status);
        }
    } 
    
    fclose(file);
}

void searchBillingInfo(char *patient_name, char *criteria) {

    FILE *file = fopen("patient_folder\\billing.txt", "r");
    if (file == NULL) {
        printf("Unable to open file\n");
        return;
    }

    char line[MAX];
    char temp_line[MAX];
    
    Billing billing;
    
    long pos;
    printf("\nBilling Details :\n\n");
    while (fgets(line, sizeof(line), file)) {
        strcpy(temp_line,line);
        char* token = strtok(temp_line, ",");
        if (strcmp(token,patient_name)==0) {
            // Remove the newline character at the end of the line if present
            line[strcspn(line, "\n")] = '\0';
            
            // Parse the line and assign values to the struct
            sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]",
                billing.username,
                billing.id,
                billing.amount,
                billing.status,
                billing.insurance_id,
                billing.claim_date,
                billing.claim_status);
            if (strcmp(criteria,billing.id)==0 || strcmp(criteria,billing.status)==0 || strcmp(criteria,billing.insurance_id)==0 || strcmp(criteria,billing.claim_status)==0){
                // Print the parsed values
                printf("-Patient Name: %s\n", billing.username);
                printf("-Bill ID: %s\n", billing.id);
                printf("-Amount : %s\n", billing.amount);
                printf("-Status: %s\n", billing.status);
                printf("-Insurance Claim ID: %s\n", billing.insurance_id);
                printf("-Claim date: %s\n", billing.claim_date);
                printf("-Claim Status: %s\n\n", billing.claim_status);
            }
        }
    } 
    
    fclose(file);
}
