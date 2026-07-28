#include "hospital.h"


Doctor *getDoctor(int id)
{
    for (int i = 0; i < doctorCount; i++)
    {
        if (doctors[i].id == id)
            return &doctors[i];
    }

    return NULL;
}


void addDoctor()
{
    if (doctorCount >= MAX_DOCTORS)
    {
        printf("\nDoctor database full.\n");
        return;
    }

    Doctor *d = &doctors[doctorCount];

    d->id = 501 + doctorCount;

    printf("\n=============== ADD DOCTOR ===============\n");

    printf("Doctor Name: ");
    scanf(" %[^\n]", d->name);

    printf("Specialization: ");
    scanf(" %[^\n]", d->specialization);

    printf("Working Start Time (HH:MM): ");
    scanf("%5s", d->startTime);

    printf("Working End Time (HH:MM): ");
    scanf("%5s", d->endTime);

    printf("Slot Duration (minutes): ");
    scanf("%d", &d->slotDuration);

    doctorCount++;

    printf("\nDoctor added successfully.\n");
    printf("Doctor ID: %d\n", d->id);
}


void viewDoctors()
{
    printf("\n==================== DOCTORS ====================\n");

    printf("%-6s %-25s %-20s %-13s %-8s\n",
           "ID",
           "Doctor",
           "Specialization",
           "Hours",
           "Slot");

    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < doctorCount; i++)
    {
        char hours[20];

        snprintf(
            hours,
            sizeof(hours),
            "%s-%s",
            doctors[i].startTime,
            doctors[i].endTime
        );

        printf("%-6d %-25s %-20s %-13s %d min\n",
               doctors[i].id,
               doctors[i].name,
               doctors[i].specialization,
               hours,
               doctors[i].slotDuration);
    }
}
