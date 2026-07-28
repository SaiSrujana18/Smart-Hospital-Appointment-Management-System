#include "hospital.h"


static int nextPatientId = 1;


/* =========================
   FIND PATIENT
   ========================= */

Patient *findPatientById(int id)
{
    Patient *current = patientHead;

    while (current != NULL)
    {
        if (current->id == id)
        {
            return current;
        }

        current = current->next;
    }

    return NULL;
}


/* =========================
   SAVE PATIENTS
   ========================= */

void savePatients(void)
{
    FILE *file;

    Patient *current;

    file = fopen(PATIENT_FILE, "wb");

    if (file == NULL)
    {
        printf("\nWarning: Unable to save patient data.\n");

        return;
    }

    current = patientHead;

    while (current != NULL)
    {
        /*
           Do not write the pointer value.
           Write only actual record fields.
        */

        fwrite(
            &current->id,
            sizeof(int),
            1,
            file
        );

        fwrite(
            current->name,
            sizeof(char),
            NAME_LEN,
            file
        );

        fwrite(
            &current->age,
            sizeof(int),
            1,
            file
        );

        fwrite(
            current->gender,
            sizeof(char),
            15,
            file
        );

        fwrite(
            current->phone,
            sizeof(char),
            PHONE_LEN,
            file
        );

        current = current->next;
    }

    fclose(file);
}


/* =========================
   LOAD PATIENTS
   ========================= */

void loadPatients(void)
{
    FILE *file;

    Patient *last = NULL;

    int maxId = 0;

    file = fopen(PATIENT_FILE, "rb");

    /*
       First run:
       file may not exist yet.

       This is normal.
    */

    if (file == NULL)
    {
        return;
    }

    while (1)
    {
        Patient *newPatient;

        newPatient =
            (Patient *)malloc(
                sizeof(Patient)
            );

        if (newPatient == NULL)
        {
            break;
        }

        if (
            fread(
                &newPatient->id,
                sizeof(int),
                1,
                file
            ) != 1
        )
        {
            free(newPatient);

            break;
        }

        if (
            fread(
                newPatient->name,
                sizeof(char),
                NAME_LEN,
                file
            ) != NAME_LEN
        )
        {
            free(newPatient);
            break;
        }

        if (
            fread(
                &newPatient->age,
                sizeof(int),
                1,
                file
            ) != 1
        )
        {
            free(newPatient);
            break;
        }

        if (
            fread(
                newPatient->gender,
                sizeof(char),
                15,
                file
            ) != 15
        )
        {
            free(newPatient);
            break;
        }

        if (
            fread(
                newPatient->phone,
                sizeof(char),
                PHONE_LEN,
                file
            ) != PHONE_LEN
        )
        {
            free(newPatient);
            break;
        }

        newPatient->next = NULL;

        if (patientHead == NULL)
        {
            patientHead = newPatient;
        }
        else
        {
            last->next = newPatient;
        }

        last = newPatient;

        if (newPatient->id > maxId)
        {
            maxId = newPatient->id;
        }
    }

    fclose(file);

    nextPatientId = maxId + 1;
}


/* =========================
   REGISTER PATIENT
   ========================= */

void registerPatient(void)
{
    Patient *newPatient;

    Patient *current;

    newPatient =
        (Patient *)malloc(
            sizeof(Patient)
        );

    if (newPatient == NULL)
    {
        printf("\nMemory allocation failed.\n");

        return;
    }

    newPatient->id =
        nextPatientId++;

    printf("\n");
    printf("========================================\n");
    printf("           REGISTER PATIENT\n");
    printf("========================================\n");

    printf("Name: ");
    scanf(
        " %59[^\n]",
        newPatient->name
    );

    printf("Age: ");
    scanf(
        "%d",
        &newPatient->age
    );

    printf("Gender: ");
    scanf(
        " %14[^\n]",
        newPatient->gender
    );

    printf("Phone: ");
    scanf(
        " %19s",
        newPatient->phone
    );

    newPatient->next = NULL;

    if (patientHead == NULL)
    {
        patientHead = newPatient;
    }
    else
    {
        current = patientHead;

        while (current->next != NULL)
        {
            current = current->next;
        }

        current->next = newPatient;
    }

    /*
       Persist immediately.
    */

    savePatients();

    printf("\nPatient registered successfully.\n");

    printf(
        "Patient ID: %d\n",
        newPatient->id
    );
}


/* =========================
   VIEW PATIENTS
   ========================= */

void viewPatients(void)
{
    Patient *current =
        patientHead;

    printf("\n");
    printf("==========================================================================\n");
    printf("                            PATIENTS\n");
    printf("==========================================================================\n");

    if (current == NULL)
    {
        printf("No patients registered.\n");

        return;
    }

    printf(
        "%-6s %-25s %-8s %-15s %-15s\n",
        "ID",
        "Name",
        "Age",
        "Gender",
        "Phone"
    );

    printf(
        "--------------------------------------------------------------------------\n"
    );

    while (current != NULL)
    {
        printf(
            "%-6d %-25s %-8d %-15s %-15s\n",
            current->id,
            current->name,
            current->age,
            current->gender,
            current->phone
        );

        current = current->next;
    }
}


/* =========================
   SEARCH PATIENT
   ========================= */

void searchPatient(void)
{
    int option;

    if (patientHead == NULL)
    {
        printf("\nNo patients registered.\n");

        return;
    }

    printf("\n");
    printf("1. Search by Patient ID\n");
    printf("2. Search by Name\n");

    printf("Choice: ");

    scanf("%d", &option);

    if (option == 1)
    {
        int id;

        Patient *patient;

        printf("Patient ID: ");

        scanf("%d", &id);

        patient =
            findPatientById(id);

        if (patient == NULL)
        {
            printf("\nPatient not found.\n");

            return;
        }

        printf("\nPatient Found\n");

        printf(
            "ID     : %d\n",
            patient->id
        );

        printf(
            "Name   : %s\n",
            patient->name
        );

        printf(
            "Age    : %d\n",
            patient->age
        );

        printf(
            "Gender : %s\n",
            patient->gender
        );

        printf(
            "Phone  : %s\n",
            patient->phone
        );
    }

    else if (option == 2)
    {
        char name[NAME_LEN];

        Patient *current =
            patientHead;

        int found = 0;

        printf("Enter patient name: ");

        scanf(
            " %59[^\n]",
            name
        );

        while (current != NULL)
        {
            if (
                strstr(
                    current->name,
                    name
                ) != NULL
            )
            {
                printf(
                    "\nID: %d | Name: %s | Age: %d | Phone: %s\n",
                    current->id,
                    current->name,
                    current->age,
                    current->phone
                );

                found = 1;
            }

            current =
                current->next;
        }

        if (!found)
        {
            printf(
                "\nNo matching patient found.\n"
            );
        }
    }

    else
    {
        printf("\nInvalid option.\n");
    }
}