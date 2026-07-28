#include "hospital.h"


Patient *getPatient(int id)
{
    for (int i = 0; i < patientCount; i++)
    {
        if (patients[i].id == id)
            return &patients[i];
    }

    return NULL;
}


void registerPatient()
{
    if (patientCount >= MAX_PATIENTS)
    {
        printf("\nPatient database full.\n");
        return;
    }

    Patient *p = &patients[patientCount];

    p->id = 1001 + patientCount;

    printf("\n=========== REGISTER PATIENT ===========\n");

    printf("Name: ");
    scanf(" %[^\n]", p->name);

    printf("Age: ");
    scanf("%d", &p->age);

    printf("Gender: ");
    scanf(" %14s", p->gender);

    printf("Phone: ");
    scanf(" %14s", p->phone);

    patientCount++;

    printf("\nPatient registered successfully.\n");
    printf("Patient ID: %d\n", p->id);
}


void viewPatients()
{
    printf("\n================ PATIENT DIRECTORY ================\n");

    if (patientCount == 0)
    {
        printf("No patients registered.\n");
        return;
    }

    printf("%-8s %-25s %-6s %-12s %-15s\n",
           "ID",
           "Name",
           "Age",
           "Gender",
           "Phone");

    printf("-----------------------------------------------------------------\n");

    for (int i = 0; i < patientCount; i++)
    {
        printf("%-8d %-25s %-6d %-12s %-15s\n",
               patients[i].id,
               patients[i].name,
               patients[i].age,
               patients[i].gender,
               patients[i].phone);
    }
}


void searchPatient()
{
    char search[50];

    printf("\nEnter patient name: ");
    scanf(" %[^\n]", search);

    int found = 0;

    printf("\nSearch Results\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < patientCount; i++)
    {
        if (strstr(patients[i].name, search) != NULL)
        {
            printf("ID    : %d\n", patients[i].id);
            printf("Name  : %s\n", patients[i].name);
            printf("Age   : %d\n", patients[i].age);
            printf("Phone : %s\n\n", patients[i].phone);

            found = 1;
        }
    }

    if (!found)
        printf("No patient found.\n");
}
