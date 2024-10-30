#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define MAX_APPOINTMENTS 100
#define MAX 256


typedef struct {
    char id[MAX];
    char password[MAX];
} Doctor_pass;
typedef struct {
    char id[MAX];
    char username[MAX];
    char doctor[MAX];
    char date[MAX];
    char time[MAX];
}Appointment;
struct Patient {
    char name[50];
    char disease[50];
    char cure[50];
    char appointments[100][10];
    char bill[50];
    int appointment_count;
};

void Schedule(char *doctor_name);
void displaySchedule(char* doctor_name);
void DeleteSlot(char *doctor_name, char *patient_name, char *appointment_id);
void makeAppointment(char *doctor_name);


// Connection with main function
int doctor_functions() {
    const char filename[] = "doctor_folder\\ehr.txt";

    char username[MAX], password[MAX];

    while (1) {
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        FILE *file = fopen("doctor_folder\\doctor_pass.txt", "r");
        if (file == NULL) {
            printf("Error: Unable to open doctors' file.\n");
            return 0;
        }
        char file_username[MAX], file_password[MAX];
        char doctor_name[MAX]="Dr.";
        int found = 0;
        char line[100];
        while (fscanf(file, "%s %s", file_username, file_password) == 2) {
            if (strcmp(file_username, username) == 0 && strcmp(file_password, password) == 0) {

                    printf("Login successful!\n");
                    strcat(doctor_name, username);
                    printf("Welcome, %s\n", doctor_name);
                    printf("\n1. Schedule\n2. Health records\n3. Generate a report\n4. Reporting and Analytics\n5. Exit\n");
                    int choice;
                    scanf("%d",&choice);
                    switch(choice){
                        case 1:
                            Schedule(doctor_name);
                            break;
                        case 2:
                            display_HeathRecords();
                            break;
                        case 3:
                            Generate_report(filename);
                            break;
                        case 4:
                            display_ReportHistory();
                            break;
                        case 5:
                            return 0;
                    }
                    found = 1;
                    break;
                }
         }
        if (found) {
            fclose(file);
            return 0;
        } else {
            printf("Login failed. Invalid username or password.\n");
            exit(0);}

    }
}

void Schedule(char *doctor_name) {
        int option;
        while(1){
            printf("\n#############################################\n");
            printf("#           What shall you choose?          #\n");
            printf("#############################################\n");
            printf("\n1.Display existing Appointments\n2.Make an appointment\n3.Delete slot\n4.Exit\nEnter the option you need(from 1 to 4): ");

            scanf("%d",&option);
            switch(option){
                case(1):
                    displaySchedule(doctor_name);
                    break;
                case (2):
                    makeAppointment(doctor_name);
                    break;
                case (3):
                    displaySchedule(doctor_name);
                    char appointment_id[MAX],patient_name[MAX];
                    printf("Enter Patient Username: ");
                    scanf("%s",patient_name);

                    printf("Enter Appointment ID: ");
                    scanf("%s",appointment_id);

                    DeleteSlot(doctor_name, patient_name, appointment_id);
                    break;
                case(4):
                    return;
            }
        }
}

void displaySchedule(char* doctor_name) {
    printf("\nCurrent Schedule:\n");
    FILE *file = fopen("patient_folder\\appointments-patient.txt", "r");
    if (file == NULL) {
        printf("Unable to open file\n");
        return;
    }

    char line[MAX];

    Appointment appointment;




    while (fgets(line, sizeof(line), file)) {
        if (strstr(line,doctor_name)!=0) {

            line[strcspn(line, "\n")] = '\0';


            sscanf(line, "%s %s %s %s %s",
                appointment.username,
                appointment.id,
                appointment.date,
                appointment.time,
                appointment.doctor);


            printf("-ScheduleID: %s\n", appointment.id);
            printf("-Patient username: %s\n", appointment.username);
            printf("-Date: %s\n", appointment.date);
            printf("-Time: %s\n", appointment.time);
            printf("\n");
        }
    }

    fclose(file);
}

void makeAppointment(char *doctor_name){
    char line[MAX], newline[MAX]="\n", patient_name[MAX], appointment_id[MAX], date[MAX], time[MAX];
    printf("\nEnter Patient Username: ");
    scanf("%s",patient_name);
    strcat(newline,patient_name);
    strcat(newline," ");
    printf("\nEnter AppointmentID(For example A001): ");
    scanf("%s",appointment_id);
    strcat(newline,appointment_id);
    strcat(newline," ");

    printf("\nEnter Date(YYYY-MM-DD): ");
    scanf("%s",date);
    strcat(newline,date);
    strcat(newline," ");

    printf("\nEnter Time(HH:MM): ");
    scanf("%s",time);
    strcat(newline,time);
    strcat(newline," ");
    strcat(newline, doctor_name);
    FILE *file = fopen("patient_folder\\appointments-patient.txt", "a");
    if (file == NULL) {
        printf("Error: Unable to open doctors file.\n");
        return;
    }
    int available=1;
    Appointment appointment;
    while (fgets(line, sizeof(line), file)) {


        sscanf(line, "%s %s %s %s %s",
            appointment.username,
            appointment.id,
            appointment.date,
            appointment.time,
            appointment.doctor);

        if (strcmp(appointment.doctor, doctor_name)==0 && strcmp(appointment.date, date)==0 && strcmp(appointment.time, time)==0) {
            available = 0;
        }
    }
    if (available){
        fprintf(file, "%s", newline);
        fclose(file);
        printf("\nAppointment was added successfully!");
        return;
    }else{
            printf("\nYou already have an appointment at this time.");
            fclose(file);
            return;
        }


}

void DeleteSlot(char *doctor_name, char *patient_name, char *appointment_id) {
    FILE *file = fopen("patient_folder\\appointments-patient.txt", "r");
    FILE *temp = fopen("patient_folder\\temp.txt", "w");
    if (file == NULL || temp == NULL) {
        printf("Unable to open file\n");
        return;
    }
    int found=0;
    Appointment appointment;
    char line[MAX];
    while (fgets(line, sizeof(line), file)) {


        sscanf(line, "%s %s %s %s %s",
            appointment.username,
            appointment.id,
            appointment.date,
            appointment.time,
            appointment.doctor);

        if (!(strcmp(appointment.doctor, doctor_name)==0 && strcmp(appointment.username, patient_name)==0 && strcmp(appointment.id, appointment_id)==0)) {
            fputs(line, temp);

        }else{
            found = 1;
        }

    }
    if (!found){
        printf("No appointment found for the specified day and time.\n");
        return ;
    }
    fclose(file);
    fclose(temp);

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

void display_HeathRecords(){
    char line[50];
    FILE*file=fopen("doctor_folder\\EHR.txt","r");
    while(fgets(line,sizeof(line),file)){
        printf("%s", line);
    }
    fclose(file);
    return;
}

void Generate_report(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    FILE*report_file=fopen("ReportHist.txt", "a");

    char searchName[50];
    printf("Enter the patient's name to search: ");
    if (scanf("%s", searchName) != 1) {
        fprintf(stderr, "Error reading input.\n");
        fclose(file);
        return;
    }

    char line[MAX_LINE_LENGTH];
    struct Patient patient;
    int found = 0;
    int reportNumber = 0;

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %s %s %[^\n]", patient.name, patient.disease, patient.cure, line);


        if (strcmp(patient.name, searchName) == 0) {
            patient.appointment_count = 0;
            char *token = strtok(line, ",");
            while (token != NULL && patient.appointment_count < MAX_APPOINTMENTS) {
                strcpy(patient.appointments[patient.appointment_count], token);
                patient.appointment_count++;
                token = strtok(NULL, ",");
            }

            found = 1;
            strcpy(patient.bill, patient.appointments[patient.appointment_count - 1]);
            patient.appointment_count--;


            printf("Name = %s, Disease = %s, Cure = %s, Appointments: ", patient.name, patient.disease, patient.cure);
            for (int i = 0; i < patient.appointment_count; ++i) {
                if (i > 0) printf(",");
                printf("%s", patient.appointments[i]);
            }
            printf(", Bill = %s\n", patient.bill);

            break;
            reportNumber++;

            fprintf(report_file, "Report %d, Name = %s, Disease = %s, Cure = %s, Appointments: ", reportNumber, patient.name, patient.disease, patient.cure);
            for (int i = 0; i < patient.appointment_count; ++i) {
                if (i > 0) fprintf(report_file, ",");
                fprintf(report_file, "%s", patient.appointments[i]);
            }
            fprintf(report_file, ", Bill = %s\n", patient.bill);
        }
        return;
    }

    if (!found) {
        printf("Patient with name '%s' not found in the file.\n", searchName);
    }

    fclose(file);
    fclose(report_file);
    return;
}

void display_ReportHistory(){
    char line[MAX];
    FILE*file=fopen("doctor_folder\\ReportHist.txt","r");
    while(fgets(line, sizeof(line), file)){
        printf("%s", line);
    }
    fclose(file);
    return;
}



