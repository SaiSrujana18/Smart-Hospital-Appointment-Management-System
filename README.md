# Smart Hospital Appointment Management System

A **Data Structures and Algorithms in C case study** that demonstrates how linked lists, queues, priority queues, searching, and scheduling algorithms can be applied to a real-world hospital appointment management problem.

The system manages patients, doctors, appointments, patient check-ins, waiting queues, priority cases, and appointment scheduling through a command-line application written in C.

---

## Project Objective

Traditional appointment systems allocate fixed time slots to patients. However, hospital consultations do not always take exactly the scheduled amount of time.

This project demonstrates a smarter appointment management approach that combines:

- Patient and doctor management
- Appointment scheduling
- 30-minute consultation slots
- FIFO waiting queues
- Priority-based patient handling
- Patient check-in
- Consultation tracking
- Smart appointment search
- Dynamic slot utilisation

The main objective is to demonstrate practical applications of **Data Structures and Algorithms in C** through a hospital appointment management case study.

---

# Features

## 1. Patient Management

The system allows hospital staff to:

- Register patients
- View registered patients
- Search patients using ID
- Search patients using name

Patient records are stored using a **Singly Linked List**.

---

## 2. Doctor Management

Hospital staff can:

- Add doctors
- Store doctor specialisation
- Define working hours
- View available doctors

Doctor records are also maintained using a **Singly Linked List**.

Example:

```text
ID     Doctor              Specialisation       From      Until
1      Dr. Sharma          Cardiology            09:00     17:00
2      Dr. Mehta           General Medicine      10:00     18:00
```

---

## 3. Appointment Booking

Patients can book appointments with registered doctors.

Each appointment contains:

- Appointment ID
- Patient
- Doctor
- Date
- Time
- Appointment status

The system uses **30-minute appointment slots**.

Example:

```text
09:00
09:30
10:00
10:30
11:00
...
```

Before confirming an appointment, the system checks whether the selected slot is already occupied.

---

## 4. Smart Appointment Finder

Instead of manually checking every doctor and time slot, the **Smart Appointment Finder** searches for the earliest available appointment.

The user provides:

```text
Patient
Specialisation
Date
```

The scheduler then:

```text
Search matching doctors
        ↓
Check working hours
        ↓
Generate 30-minute slots
        ↓
Check existing appointments
        ↓
Compare available slots
        ↓
Return earliest available appointment
```

This demonstrates **searching and scheduling algorithms**.

---

## 5. Patient Check-In

When a patient arrives at the hospital, the appointment can be checked in.

The appointment status changes from:

```text
BOOKED
```

to:

```text
CHECKED_IN
```

The patient is then inserted into the live waiting queue.

---

# FIFO Waiting Queue

Checked-in patients are managed using a **First-In-First-Out Queue**.

Example:

```text
FRONT

Patient A
   ↓
Patient B
   ↓
Patient C

REAR
```

If Patient A arrived first, Patient A is normally called first.

Queue operations used:

```text
Enqueue
Dequeue
Traversal
```

### Enqueue

A checked-in patient is inserted at the rear.

```text
A -> B -> C -> NULL
          ↑
         REAR
```

### Dequeue

The patient at the front is called for consultation.

```text
Before:

A -> B -> C

After calling A:

B -> C
↑
FRONT
```

Both enqueue and dequeue are implemented efficiently using front and rear pointers.

---

# Priority Queue

Hospitals cannot always follow a pure FIFO system because some patients require urgent treatment.

The system therefore contains a **Priority Queue**.

Priority levels are:

```text
1 → Emergency
2 → Urgent
3 → Senior Citizen
4 → Normal
```

Example:

```text
Emergency
    ↓
Urgent
    ↓
Senior Citizen
    ↓
Normal
```

A higher-priority patient is processed before lower-priority patients.

Patients with the same priority retain their arrival order.

For example:

```text
Emergency A
Emergency B
Urgent C
Senior D
Normal E
```

Emergency A remains before Emergency B because A entered the queue first.

This demonstrates a **stable priority queue**.

---

# Consultation Management

When the next checked-in patient is called:

```text
CHECKED_IN
     ↓
IN_CONSULTATION
```

After treatment:

```text
IN_CONSULTATION
        ↓
COMPLETED
```

The system therefore tracks the appointment lifecycle.

```text
BOOKED
   ↓
CHECKED_IN
   ↓
IN_CONSULTATION
   ↓
COMPLETED
```

Appointments may also become:

```text
CANCELLED
```

---

# Smart Slot Optimisation

One of the key ideas demonstrated by this case study is the ability to recognise unused appointment capacity.

Consider a doctor's schedule:

```text
4:00 PM   Patient A
4:30 PM   Patient B
5:00 PM   FREE
5:30 PM   Patient C
```

Consultations are allocated 30-minute slots, but the actual consultation duration may vary.

Suppose a consultation finishes earlier than expected.

```text
Expected completion → 4:30 PM

Actual completion   → 4:20 PM
```

The doctor becomes available earlier.

The scheduler evaluates whether the available capacity can be used rather than unnecessarily making a new patient wait for a later appointment.

The logic considers:

1. Whether an eligible patient is already waiting
2. Whether the relevant upcoming slot is occupied
3. Whether another patient would be displaced
4. Whether an earlier opportunity can safely be offered

Conceptually:

```text
Consultation finishes early
            ↓
Check Waiting Queue
            ↓
    Patient waiting?
       /          \
     YES           NO
      |             |
Give waiting     Check upcoming
patient priority     schedule
                    |
                    v
              Capacity available?
                 /       \
               YES        NO
                |          |
             Offer      Continue
          earlier slot   schedule
```

The purpose is to improve **doctor utilisation and reduce unnecessary patient waiting time** while respecting existing patients.

---

# Appointment Cancellation

Appointments can be cancelled.

When an appointment is cancelled:

```text
BOOKED
   ↓
CANCELLED
```

The corresponding appointment slot becomes available again for future booking.

---

# Data Structures Used

## Singly Linked List

Used for:

- Patient records
- Doctor records
- Appointment records

Example:

```text
HEAD
 |
 v
+----------+     +----------+     +----------+
| Patient1 | --> | Patient2 | --> | Patient3 | --> NULL
+----------+     +----------+     +----------+
```

Linked lists allow records to be created dynamically without defining a fixed maximum number of patients, doctors, or appointments.

---

## FIFO Queue

Used for:

```text
Live Patient Waiting Queue
```

Implementation:

```text
FRONT                              REAR
  |                                  |
  v                                  v
Patient A -> Patient B -> Patient C -> NULL
```

Patients are normally processed according to arrival order.

---

## Priority Queue

Used for urgent hospital cases.

```text
Emergency -> Urgent -> Senior -> Normal
```

The queue is maintained according to patient priority.

---

## Linear Search

Used for operations such as:

- Finding patient by ID
- Finding doctor by ID
- Finding appointment by ID
- Searching patient names
- Finding matching doctor specialisations

Example:

```text
HEAD
 |
 v
P1 -> P2 -> P3 -> P4 -> NULL
           ^
           |
         FOUND
```

---

## Dynamic Memory Allocation

Records are dynamically created using:

```c
malloc()
```

Example:

```c
Patient *newPatient =
    (Patient *)malloc(sizeof(Patient));
```

This allows the system to create data structures dynamically while the application is running.

---

# DSA Concepts Demonstrated

The project demonstrates:

- Structures in C
- Pointers
- Dynamic Memory Allocation
- Singly Linked Lists
- Linked List Insertion
- Linked List Traversal
- Linear Searching
- FIFO Queue
- Enqueue
- Dequeue
- Priority Queue
- Stable Priority Ordering
- Time Slot Searching
- Scheduling Algorithms

---

# Project Structure

```text
Smart-Hospital-Appointment-Management-System/
│
├── README.md
├── hospital.h
├── main.c
├── patient.c
├── doctor.c
├── appointment.c
├── queue.c
└── scheduler.c
```

---

# File Description

### `hospital.h`

Contains:

- Data structure definitions
- Shared constants
- Function declarations
- Global linked-list and queue pointer declarations

---

### `main.c`

Contains:

- Main program
- Main menu
- Patient management submenu
- Doctor management submenu
- Waiting queue submenu
- Priority queue submenu
- Appointment management submenu
- Global data structure definitions

---

### `patient.c`

Handles:

- Patient registration
- Patient linked list
- Viewing patients
- Patient searching

---

### `doctor.c`

Handles:

- Doctor registration
- Doctor linked list
- Doctor working hours
- Doctor specialisations
- Viewing doctors

---

### `appointment.c`

Handles:

- Appointment booking
- Appointment linked list
- Slot availability
- Patient check-in
- Appointment status
- Consultation completion
- Appointment cancellation

---

### `queue.c`

Implements:

- FIFO waiting queue
- Enqueue
- Dequeue
- Calling next patient
- Priority queue
- Priority insertion
- Priority patient processing

---

### `scheduler.c`

Implements:

- Time conversion
- 30-minute slot generation
- Doctor specialisation search
- Available slot search
- Earliest appointment selection
- Smart scheduling logic
- Early-completion slot optimisation

---

# Main Menu

```text
==================================================
     SMART HOSPITAL APPOINTMENT MANAGEMENT
==================================================

1. Patient Management
2. Doctor Management
3. Book Appointment
4. View Appointments
5. Smart Appointment Finder
6. Patient Check-In
7. Manage Waiting Queue
8. Manage Priority Queue
9. Complete / Cancel Appointment
0. Exit

==================================================
```

---

# Appointment Status Flow

```text
                    +----------+
                    |  BOOKED  |
                    +----+-----+
                         |
                      Check-In
                         |
                         v
                  +-------------+
                  | CHECKED_IN  |
                  +------+------+
                         |
                    Call Patient
                         |
                         v
               +-------------------+
               | IN_CONSULTATION   |
               +---------+---------+
                         |
                     Complete
                         |
                         v
                  +-------------+
                  | COMPLETED   |
                  +-------------+
```

An appointment may also be cancelled before completion:

```text
BOOKED → CANCELLED
```

---

# Algorithm Overview

## Patient Registration

```text
Create Patient Node
        ↓
Assign Patient ID
        ↓
Enter Patient Details
        ↓
Is Linked List Empty?
      /          \
    YES           NO
     |             |
HEAD = Node     Traverse to End
                   |
                   v
               Insert Node
```

---

## Appointment Scheduling

```text
Patient Request
      ↓
Select Doctor
      ↓
Enter Date and Time
      ↓
Validate Doctor
      ↓
Check Working Hours
      ↓
Check 30-Minute Slot
      ↓
Is Slot Available?
    /           \
  YES            NO
   |               |
Book           Reject /
Appointment   Smart Finder
```

---

## Smart Appointment Search

```text
Required Specialisation
          ↓
Traverse Doctors
          ↓
Matching Doctor?
          ↓
Generate Slots
          ↓
Check Existing Appointments
          ↓
Find Earliest Free Slot
          ↓
Compare Matching Doctors
          ↓
Recommend Best Slot
```

---

# Time Complexity

| Operation | Time Complexity |
|---|---|
| Register Patient | O(n) |
| View Patients | O(n) |
| Search Patient | O(n) |
| Add Doctor | O(n) |
| View Doctors | O(n) |
| Find Doctor | O(n) |
| Add Appointment | O(n) |
| Find Appointment | O(n) |
| Check Slot Availability | O(n) |
| Waiting Queue Enqueue | O(1) |
| Waiting Queue Dequeue | O(1) |
| View Waiting Queue | O(n) |
| Priority Queue Insertion | O(n) |
| Process Priority Patient | O(1) |
| Smart Appointment Search | Depends on doctors, slots and appointments |

---

# Compilation

The project requires a C compiler such as GCC.

Compile all source files together:

```bash
gcc main.c patient.c doctor.c appointment.c queue.c scheduler.c -o hospital.exe
```

---

# Running the Program

### Windows

```bash
.\hospital.exe
```

### Linux / macOS

Compile using:

```bash
gcc main.c patient.c doctor.c appointment.c queue.c scheduler.c -o hospital
```

Run:

```bash
./hospital
```

---

# Example Workflow

A typical workflow is:

```text
1. Register Patient
        ↓
2. Add Doctor
        ↓
3. Book Appointment
        ↓
4. Patient Arrives
        ↓
5. Patient Check-In
        ↓
6. Added to Waiting Queue
        ↓
7. Call Next Patient
        ↓
8. Consultation Starts
        ↓
9. Complete Consultation
        ↓
10. Smart Scheduler Checks Available Capacity
```

For urgent cases:

```text
Patient
   ↓
Assign Priority
   ↓
Priority Queue
   ↓
Emergency / Urgent / Senior / Normal
   ↓
Process Highest Priority Patient
```

---

# Case Study Problem Statement

Hospitals handle multiple patients, doctors, appointments, waiting patients, and urgent cases every day.

A simple fixed appointment list does not adequately demonstrate situations such as:

- Multiple patient records
- Different doctor schedules
- Appointment conflicts
- Patient arrival order
- Emergency patients
- Appointment cancellations
- Consultations finishing earlier than expected
- Finding the earliest available appointment

This project models these problems using fundamental Data Structures and Algorithms.

---

# Proposed Solution

The Smart Hospital Appointment Management System combines multiple data structures:

```text
Patients
   ↓
Linked List

Doctors
   ↓
Linked List

Appointments
   ↓
Linked List

Checked-In Patients
   ↓
FIFO Queue

Urgent Patients
   ↓
Priority Queue

Appointment Search
   ↓
Scheduling Algorithm
```

This demonstrates how different data structures can work together within one practical application.

---

# Advantages

- Dynamic patient and doctor records
- Prevents duplicate appointment slots
- Organises checked-in patients
- Supports urgent cases
- Searches available doctor schedules
- Reuses cancelled slots
- Demonstrates dynamic scheduling concepts
- Uses multiple DSA concepts in one real-world case study
- Modular C source-code structure

---

# Current Scope

This project is a **command-line DSA case-study implementation**.

It focuses on the underlying data structures and scheduling logic rather than providing a graphical hospital-management dashboard.

The current version stores data in memory while the program is running.

Possible future extensions include:

- File-based persistent storage
- Database integration
- Graphical user interface
- Web/mobile appointment booking
- Doctor login
- Patient login
- Notifications
- Department management
- Appointment history
- Real-time hospital integration

---

# Learning Outcomes

Through this project, the following concepts can be understood practically:

1. How linked lists can manage dynamically changing records
2. How queues model real-world waiting lines
3. How priority queues handle urgent cases
4. How linear searching locates records
5. How dynamic memory allocation works in C
6. How multiple data structures interact in one application
7. How scheduling algorithms can improve appointment allocation
8. How DSA concepts can be applied to real-world management problems

---

# Conclusion

The **Smart Hospital Appointment Management System** demonstrates the application of Data Structures and Algorithms to a practical hospital scheduling problem.

Instead of functioning only as a basic appointment booking program, the system combines **linked lists, FIFO queues, priority queues, searching, dynamic memory allocation, and smart scheduling**.

The project shows how appropriate data structures can organise hospital records, manage waiting patients, prioritise urgent cases, prevent appointment conflicts, and improve the utilisation of available appointment slots.

---

## Technology Used

- **Language:** C
- **Compiler:** GCC
- **Data Structures:** Singly Linked List, Queue, Priority Queue
- **Concepts:** Searching, Dynamic Memory Allocation, Scheduling
- **Development Environment:** Visual Studio Code