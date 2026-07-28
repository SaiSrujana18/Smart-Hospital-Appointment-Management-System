#include "hospital.h"


static int nextDoctorId = 1;


/* =========================
   FIND DOCTOR
   ========================= */

Doctor *findDoctorById(int id)
{
    Doctor *current =
        doctorHead;

    while (current != NULL)
    {
        if (current->id == id)
        {
            return current;
        }

        current =
            current->next;
    }

    return NULL;
}


/* =========================
   SAVE DOCTORS
   ========================= */

void saveDoctors(void)
{
    FILE *file;

    Doctor *current;

    file =
        fopen(
            DOCTOR_FILE,
            "wb"
        );

    if (file == NULL)
    {
        printf(
            "\nWarning: Unable to save doctor data.\n"
        );

        return;
    }

    current =
        doctorHead;

    while (current != NULL)
    {
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
            current->specialization,
            sizeof(char),
            SPEC_LEN,
            file
        );

        fwrite(
            current->startTime,
            sizeof(char),
            TIME_LEN,
            file
        );

        fwrite(
            current->endTime,
            sizeof(char),
            TIME_LEN,
            file
        );

        current =
            current->next;
    }

    fclose(file);
}


/* =========================
   LOAD DOCTORS
   ========================= */

void loadDoctors(void)
{
    FILE *file;

    Doctor *last = NULL;

    int maxId = 0;

    file =
        fopen(
            DOCTOR_FILE,
            "rb"
        );

    if (file == NULL)
    {
        return;
    }

    while (1)
    {
        Doctor *newDoctor;

        newDoctor =
            (Doctor *)malloc(
                sizeof(Doctor)
            );

        if (newDoctor == NULL)
        {
            break;
        }

        if (
            fread(
                &newDoctor->id,
                sizeof(int),
                1,
                file
            ) != 1
        )
        {
            free(newDoctor);
            break;
        }

        if (
            fread(
                newDoctor->name,
                sizeof(char),
                NAME_LEN,
                file
            ) != NAME_LEN
        )
        {
            free(newDoctor);
            break;
        }

        if (
            fread(
                newDoctor->specialization,
                sizeof(char),
                SPEC_LEN,
                file
            ) != SPEC_LEN
        )
        {
            free(newDoctor);
            break;
        }

        if (
            fread(
                newDoctor->startTime,
                sizeof(char),
                TIME_LEN,
                file
            ) != TIME_LEN
        )
        {
            free(newDoctor);
            break;
        }

        if (
            fread(
                newDoctor->endTime,
                sizeof(char),
                TIME_LEN,
                file
            ) != TIME_LEN
        )
        {
            free(newDoctor);
            break;
        }

        newDoctor->next = NULL;

        if (doctorHead == NULL)
        {
            doctorHead =
                newDoctor;
        }
        else
        {
            last->next =
                newDoctor;
        }

        last =
            newDoctor;

        if (newDoctor->id > maxId)
        {
            maxId =
                newDoctor->id;
        }
    }

    fclose(file);

    nextDoctorId =
        maxId + 1;
}


/* =========================
   ADD DOCTOR
   ========================= */

void addDoctor(void)
{
    Doctor *newDoctor;

    Doctor *current;

    newDoctor =
        (Doctor *)malloc(
            sizeof(Doctor)
        );

    if (newDoctor == NULL)
    {
        printf(
            "\nMemory allocation failed.\n"
        );

        return;
    }

    newDoctor->id =
        nextDoctorId++;

    printf("\n");
    printf("========================================\n");
    printf("              ADD DOCTOR\n");
    printf("========================================\n");

    printf("Doctor Name: ");

    scanf(
        " %59[^\n]",
        newDoctor->name
    );

    printf("Specialization: ");

    scanf(
        " %59[^\n]",
        newDoctor->specialization
    );

    printf(
        "Working Start Time (HH:MM): "
    );

    scanf(
        "%5s",
        newDoctor->startTime
    );

    printf(
        "Working End Time (HH:MM): "
    );

    scanf(
        "%5s",
        newDoctor->endTime
    );

    newDoctor->next = NULL;

    if (doctorHead == NULL)
    {
        doctorHead =
            newDoctor;
    }
    else
    {
        current =
            doctorHead;

        while (
            current->next != NULL
        )
        {
            current =
                current->next;
        }

        current->next =
            newDoctor;
    }

    saveDoctors();

    printf(
        "\nDoctor added successfully.\n"
    );

    printf(
        "Doctor ID: %d\n",
        newDoctor->id
    );
}


/* =========================
   VIEW DOCTORS
   ========================= */

void viewDoctors(void)
{
    Doctor *current =
        doctorHead;

    printf("\n");

    printf(
        "================================================================================\n"
    );

    printf(
        "                                  DOCTORS\n"
    );

    printf(
        "================================================================================\n"
    );

    if (current == NULL)
    {
        printf(
            "No doctors available.\n"
        );

        return;
    }

    printf(
        "%-6s %-25s %-25s %-10s %-10s\n",
        "ID",
        "Doctor",
        "Specialization",
        "From",
        "Until"
    );

    printf(
        "--------------------------------------------------------------------------------\n"
    );

    while (current != NULL)
    {
        printf(
            "%-6d %-25s %-25s %-10s %-10s\n",
            current->id,
            current->name,
            current->specialization,
            current->startTime,
            current->endTime
        );

        current =
            current->next;
    }
}