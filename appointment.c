#include "hospital.h"


static int nextAppointmentId = 1;


/* =========================
   FIND APPOINTMENT
   ========================= */

Appointment *findAppointmentById(int id)
{
    Appointment *current =
        appointmentHead;

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
   SAVE APPOINTMENTS
   ========================= */

void saveAppointments(void)
{
    FILE *file;

    Appointment *current;

    file =
        fopen(
            APPOINTMENT_FILE,
            "wb"
        );

    if (file == NULL)
    {
        printf(
            "\nWarning: Unable to save appointment data.\n"
        );

        return;
    }

    current =
        appointmentHead;

    while (current != NULL)
    {
        fwrite(
            &current->id,
            sizeof(int),
            1,
            file
        );

        fwrite(
            &current->patientId,
            sizeof(int),
            1,
            file
        );

        fwrite(
            &current->doctorId,
            sizeof(int),
            1,
            file
        );

        fwrite(
            current->date,
            sizeof(char),
            DATE_LEN,
            file
        );

        fwrite(
            current->time,
            sizeof(char),
            TIME_LEN,
            file
        );

        fwrite(
            current->status,
            sizeof(char),
            25,
            file
        );

        current =
            current->next;
    }

    fclose(file);
}


/* =========================
   LOAD APPOINTMENTS
   ========================= */

void loadAppointments(void)
{
    FILE *file;

    Appointment *last = NULL;

    int maxId = 0;

    file =
        fopen(
            APPOINTMENT_FILE,
            "rb"
        );

    if (file == NULL)
    {
        return;
    }

    while (1)
    {
        Appointment *newAppointment;

        newAppointment =
            (Appointment *)malloc(
                sizeof(Appointment)
            );

        if (newAppointment == NULL)
        {
            break;
        }

        if (
            fread(
                &newAppointment->id,
                sizeof(int),
                1,
                file
            ) != 1
        )
        {
            free(newAppointment);
            break;
        }

        if (
            fread(
                &newAppointment->patientId,
                sizeof(int),
                1,
                file
            ) != 1
        )
        {
            free(newAppointment);
            break;
        }

        if (
            fread(
                &newAppointment->doctorId,
                sizeof(int),
                1,
                file
            ) != 1
        )
        {
            free(newAppointment);
            break;
        }

        if (
            fread(
                newAppointment->date,
                sizeof(char),
                DATE_LEN,
                file
            ) != DATE_LEN
        )
        {
            free(newAppointment);
            break;
        }

        if (
            fread(
                newAppointment->time,
                sizeof(char),
                TIME_LEN,
                file
            ) != TIME_LEN
        )
        {
            free(newAppointment);
            break;
        }

        if (
            fread(
                newAppointment->status,
                sizeof(char),
                25,
                file
            ) != 25
        )
        {
            free(newAppointment);
            break;
        }

        newAppointment->next =
            NULL;

        if (appointmentHead == NULL)
        {
            appointmentHead =
                newAppointment;
        }
        else
        {
            last->next =
                newAppointment;
        }

        last =
            newAppointment;

        if (
            newAppointment->id >
            maxId
        )
        {
            maxId =
                newAppointment->id;
        }
    }

    fclose(file);

    nextAppointmentId =
        maxId + 1;
}


/* =========================
   SLOT AVAILABILITY
   ========================= */

int isSlotAvailable(
    int doctorId,
    const char *date,
    const char *time
)
{
    Appointment *current =
        appointmentHead;

    while (current != NULL)
    {
        if (
            current->doctorId == doctorId &&
            strcmp(
                current->date,
                date
            ) == 0 &&
            strcmp(
                current->time,
                time
            ) == 0 &&
            strcmp(
                current->status,
                "CANCELLED"
            ) != 0 &&
            strcmp(
                current->status,
                "COMPLETED"
            ) != 0
        )
        {
            return 0;
        }

        current =
            current->next;
    }

    return 1;
}


/* =========================
   CREATE APPOINTMENT
   ========================= */

static Appointment *createAppointment(
    int patientId,
    int doctorId,
    const char *date,
    const char *time
)
{
    Appointment *newAppointment;

    Appointment *current;

    newAppointment =
        (Appointment *)malloc(
            sizeof(Appointment)
        );

    if (newAppointment == NULL)
    {
        return NULL;
    }

    newAppointment->id =
        nextAppointmentId++;

    newAppointment->patientId =
        patientId;

    newAppointment->doctorId =
        doctorId;

    strcpy(
        newAppointment->date,
        date
    );

    strcpy(
        newAppointment->time,
        time
    );

    strcpy(
        newAppointment->status,
        "BOOKED"
    );

    newAppointment->next =
        NULL;

    if (appointmentHead == NULL)
    {
        appointmentHead =
            newAppointment;
    }
    else
    {
        current =
            appointmentHead;

        while (
            current->next != NULL
        )
        {
            current =
                current->next;
        }

        current->next =
            newAppointment;
    }

    saveAppointments();

    return newAppointment;
}


/* =========================
   BOOK APPOINTMENT
   ========================= */

void bookAppointment(void)
{
    int patientId;
    int doctorId;

    char date[DATE_LEN];
    char time[TIME_LEN];

    Patient *patient;
    Doctor *doctor;
    Appointment *appointment;

    if (patientHead == NULL)
    {
        printf(
            "\nRegister a patient first.\n"
        );

        return;
    }

    if (doctorHead == NULL)
    {
        printf(
            "\nAdd a doctor first.\n"
        );

        return;
    }

    printf("\n");
    printf("========================================\n");
    printf("           BOOK APPOINTMENT\n");
    printf("========================================\n");

    printf("Patient ID: ");
    scanf(
        "%d",
        &patientId
    );

    patient =
        findPatientById(
            patientId
        );

    if (patient == NULL)
    {
        printf(
            "\nPatient not found.\n"
        );

        return;
    }

    printf("Doctor ID: ");
    scanf(
        "%d",
        &doctorId
    );

    doctor =
        findDoctorById(
            doctorId
        );

    if (doctor == NULL)
    {
        printf(
            "\nDoctor not found.\n"
        );

        return;
    }

    printf(
        "Date (YYYY-MM-DD): "
    );

    scanf(
        "%10s",
        date
    );

    printf(
        "Time (HH:MM): "
    );

    scanf(
        "%5s",
        time
    );

    if (
        timeToMinutes(time) <
        timeToMinutes(
            doctor->startTime
        ) ||

        timeToMinutes(time) >=
        timeToMinutes(
            doctor->endTime
        )
    )
    {
        printf(
            "\nDoctor is not available at this time.\n"
        );

        printf(
            "Working Hours: %s - %s\n",
            doctor->startTime,
            doctor->endTime
        );

        return;
    }

    if (
        timeToMinutes(time) % 30 != 0
    )
    {
        printf(
            "\nAppointments use 30-minute slots.\n"
        );

        return;
    }

    if (
        !isSlotAvailable(
            doctorId,
            date,
            time
        )
    )
    {
        printf(
            "\nThis slot is already booked.\n"
        );

        printf(
            "Use Smart Appointment Finder to locate another slot.\n"
        );

        return;
    }

    appointment =
        createAppointment(
            patientId,
            doctorId,
            date,
            time
        );

    if (appointment == NULL)
    {
        printf(
            "\nUnable to create appointment.\n"
        );

        return;
    }

    printf(
        "\nAppointment booked successfully.\n"
    );

    printf(
        "Appointment ID : %d\n",
        appointment->id
    );

    printf(
        "Patient        : %s\n",
        patient->name
    );

    printf(
        "Doctor         : %s\n",
        doctor->name
    );

    printf(
        "Date           : %s\n",
        date
    );

    printf(
        "Time           : %s\n",
        time
    );
}


/* =========================
   VIEW APPOINTMENTS
   ========================= */

void viewAppointments(void)
{
    Appointment *current =
        appointmentHead;

    printf("\n");

    printf(
        "================================================================================================\n"
    );

    printf(
        "                                      APPOINTMENTS\n"
    );

    printf(
        "================================================================================================\n"
    );

    if (current == NULL)
    {
        printf(
            "No appointments available.\n"
        );

        return;
    }

    printf(
        "%-6s %-20s %-20s %-12s %-8s %-18s\n",
        "ID",
        "Patient",
        "Doctor",
        "Date",
        "Time",
        "Status"
    );

    printf(
        "------------------------------------------------------------------------------------------------\n"
    );

    while (current != NULL)
    {
        Patient *patient =
            findPatientById(
                current->patientId
            );

        Doctor *doctor =
            findDoctorById(
                current->doctorId
            );

        printf(
            "%-6d %-20s %-20s %-12s %-8s %-18s\n",
            current->id,
            patient != NULL
                ? patient->name
                : "Unknown",
            doctor != NULL
                ? doctor->name
                : "Unknown",
            current->date,
            current->time,
            current->status
        );

        current =
            current->next;
    }
}


/* =========================
   PATIENT CHECK-IN
   ========================= */

void patientCheckIn(void)
{
    int id;

    Appointment *appointment;

    printf(
        "\nAppointment ID: "
    );

    scanf(
        "%d",
        &id
    );

    appointment =
        findAppointmentById(id);

    if (appointment == NULL)
    {
        printf(
            "\nAppointment not found.\n"
        );

        return;
    }

    if (
        strcmp(
            appointment->status,
            "BOOKED"
        ) != 0
    )
    {
        printf(
            "\nAppointment cannot be checked in.\n"
        );

        printf(
            "Current Status: %s\n",
            appointment->status
        );

        return;
    }

    strcpy(
        appointment->status,
        "CHECKED_IN"
    );

    enqueueWaiting(id);

    saveAppointments();

    printf(
        "\nPatient checked in successfully.\n"
    );

    printf(
        "Added to FIFO waiting queue.\n"
    );
}


/* =========================
   COMPLETE CONSULTATION
   ========================= */

void completeConsultation(void)
{
    int id;

    char completedTime[TIME_LEN];

    Appointment *appointment;

    printf(
        "\nAppointment ID: "
    );

    scanf(
        "%d",
        &id
    );

    appointment =
        findAppointmentById(id);

    if (appointment == NULL)
    {
        printf(
            "\nAppointment not found.\n"
        );

        return;
    }

    if (
        strcmp(
            appointment->status,
            "IN_CONSULTATION"
        ) != 0
    )
    {
        printf(
            "\nThis appointment is not currently in consultation.\n"
        );

        printf(
            "Current Status: %s\n",
            appointment->status
        );

        return;
    }

    printf(
        "Actual completion time (HH:MM): "
    );

    scanf(
        "%5s",
        completedTime
    );

    strcpy(
        appointment->status,
        "COMPLETED"
    );

    saveAppointments();

    printf(
        "\nConsultation completed.\n"
    );

    handleEarlyCompletion(
        appointment->doctorId,
        appointment->date,
        completedTime
    );
}


/* =========================
   CANCEL APPOINTMENT
   ========================= */

void cancelAppointment(void)
{
    int id;

    Appointment *appointment;

    printf(
        "\nAppointment ID: "
    );

    scanf(
        "%d",
        &id
    );

    appointment =
        findAppointmentById(id);

    if (appointment == NULL)
    {
        printf(
            "\nAppointment not found.\n"
        );

        return;
    }

    if (
        strcmp(
            appointment->status,
            "COMPLETED"
        ) == 0
    )
    {
        printf(
            "\nCompleted appointment cannot be cancelled.\n"
        );

        return;
    }

    if (
        strcmp(
            appointment->status,
            "CANCELLED"
        ) == 0
    )
    {
        printf(
            "\nAppointment already cancelled.\n"
        );

        return;
    }

    strcpy(
        appointment->status,
        "CANCELLED"
    );

    saveAppointments();

    printf(
        "\nAppointment cancelled successfully.\n"
    );

    printf(
        "Slot %s on %s is now available.\n",
        appointment->time,
        appointment->date
    );
}