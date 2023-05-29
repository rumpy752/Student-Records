
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct 
{
    char studentID[10];
    char studentName[10];
    
    char studentEmail[20];
    char courseID[10];
    char grade[10];
}Student;

bool write_data(char *filename, Student *data, int total);
Student *read_data(char *filename, int *total);
bool updateRecord(char *filename, Student *data, int total);
bool createRecord(char *filename, Student *data, int total);

int j=0;
char stdID[10] = " ", stdname[10] = " ", stdemail[20] = " ", stdCourse[10] = " ", stdGPA[10];

int main()
{
     Student *school;
     Student *file_data;
     school = malloc(sizeof(Student) * 5);
     int choice =1;
     int total = 0;
    
    while (choice > 0 && choice < 6)
    {
        printf("Menu Driven Program By Jaime\n\n");
        printf("M A I N   M E N U\n\n");
        printf("1. Create the Binary File\n");
        printf("2. Display the contents of the file\n");
        printf("3. Seek a specific record\n");
        printf("4. Update the contents of a record\n");
        printf("5. Delete a record for the specific name\n");
        printf("6. Exit\n\n");
        printf("Please enter your choice: \n\n");
        scanf("%d", &choice);

        if (choice > 6 || choice < 1)
         { printf("The option you have selected in invalid... please try again: \n");
        scanf("%d", &choice);} 

        switch(choice)
        {
            case 1: 
                if (createRecord("school.bin", school, 5)) {
                printf("Write data OK.\n");
                j++;
                } else {
                    printf("Error writing to file.\n");
                    return 1;
                }
                break;
            case 2:
                file_data = read_data("school.bin", &total);
                    if (file_data == NULL) {
                        printf("Error reading from file.\n");
                        return 1;
                     }
                     printf("\n Data read OK.\n\n");
                     printf("File contents: \n\n");
                     for (int i=0; i<j; i++)
                    {
                        printf("Student %d\n", i + 1);
                        printf("ID: %s\n", school[i].studentID);
                        printf("Name: %s\n", school[i].studentName);
                        printf("Email: %s\n", school[i].studentEmail);
                        printf("Course ID: %s\n", school[i].courseID);
                        printf("Grade: %s\n", school[i].grade);
                        printf("\n\n");
                        } 
                break;
            case 3: ;
                char search[] = "";
                int studentNum, s, index, b, pos, size = j;
                printf("Want to find a record? I can help you!\n");
                printf("Enter the student NUMBER of the record you want to search for (i.e. 1, 2, 3): \n");
                scanf("%d", &studentNum);
                while(studentNum < 0 ||  studentNum > j)
                {
                    printf("Invalid student number! Please enter position between 1 to %d: \n", j);
                    scanf("%d", &studentNum);
                }

            
                file_data = read_data("school.bin", &total);
                if (file_data == NULL) {
                    printf("Error reading from file.\n");
                    return 1;
                }

                b = studentNum - 1;

                printf("\n Data read OK.\n\n");
                printf("Here is the record you requested.. \n\n");
                printf("Student %d\n", b + 1);
                printf("ID: %s\n", school[b].studentID);
                printf("Name: %s\n", school[b].studentName);
                printf("Email: %s\n", school[b].studentEmail);
                printf("Course ID: %s\n", school[b].courseID);
                printf("Grade: %s\n", school[b].grade);
                printf("\n\n");
                break;
            case 4:
                if (updateRecord("school.bin", school, 5)) {
                printf("Write data OK.\n");
                } else {
                    printf("Error writing to file.\n");
                    return 1;
                }
                break;
            case 5: ;
                printf("Enter the student NUMBER to be deleted: \n");
                scanf("%d", &pos);
                printf("Size of the school array is: %d\n", size);
                while(pos < 0 || pos > size)
                {
                    printf("Invalid student number! Please enter position between 1 to %d: \n", size);
                    scanf("%d", &pos);
                }
                for(j=pos-1; j<size-1; j++)
                {
                    school[j] = school[j + 1];
                }
                size--;
                printf("..Record successfully deleted.. \n");
                printf("Size of the school array is: %d\n", size);
                break;
            case 6:
                exit(1);
                break;
        }
    }
    free(school);  
    return 0;
}

bool write_data(char *filename, Student *data, int total)
{
    FILE *file;
    file = fopen(filename, "wb");
    if (file == NULL) return false;
    if (fwrite(&total, sizeof(int), 1, file) != 1)
        return false;
    if (fwrite(data, sizeof(Student), total, file) != total)
        return false;
    if (fclose(file) == EOF)
        return false;

    return true;
}

Student *read_data(char *filename, int *total)
{
    FILE *file;
    
    file = fopen(filename, "rb");
    
    if (file == NULL) return NULL;
    
    if (fread(total, sizeof(int), 1, file) != 1) {
        return NULL;
    }
    
    Student *data = malloc(sizeof(Student) * *total);
    
    if (fread(data, sizeof(Student), *total, file) != *total) {
         free(data); 
         return NULL;
    }
    
    if (fclose(file) == EOF) {
        free(data); 
        return NULL;
    }

    return data;

}

bool createRecord(char *filename, Student *data, int total)
{
    FILE *file;
    file = fopen(filename, "wb");
    if (file == NULL) return false;
    printf("Enter student data pressing enter between: (Student ID, name, email, course ID, GPA)\n");
    scanf("%s %s %s %s %s", stdID, stdname, stdemail, stdCourse, stdGPA);
    strcpy(data[j].studentID, stdID);
    strcpy(data[j].studentName, stdname);
    strcpy(data[j].studentEmail, stdemail);
    strcpy(data[j].courseID, stdCourse);
    strcpy(data[j].grade, stdGPA);
    if (write_data("school.bin", data, 5)) {
        return true;
        } else {
            printf("Error writing to file.\n");
            return false;
        }
        j++;

        return true;
}

bool updateRecord(char *filename, Student *data, int total)
{
    FILE *file;
    file = fopen(filename, "wb");
    if (file == NULL) return false;
    int index, studentNum, update, f;
    char recordUpdated[256];
    printf("Let's update a record!\n"); 
    printf("Which record do you want to update? (Enter student NUMBER (i.e. 1, 2, 3) to locate record): \n");
    scanf("%d", &studentNum);
    while(studentNum < 0 ||  studentNum >j)
    {
        printf("Invalid student number! Please enter position between 1 to %d: \n", j);
        scanf("%d", &studentNum);
    }
    f = studentNum - 1;
    strcpy(recordUpdated,data[f].studentID); 
    for (int k=0; k<j; k++)
    {
        if(strcmp(data[k].studentID, recordUpdated) == 0) 
        {
             index = k;
             break;
        }
    }
        
    printf("Got it! So what changes are we making today? \n\n");
    printf("1. Student ID\n");
    printf("2. Student name\n");
    printf("3. Student email\n");
    printf("4. Course ID\n");
    printf("5. Student grade\n");
    scanf("%d", &update);
    switch(update)
    {
        case 1:
            printf("Enter new student ID: \n");
            scanf("%s", stdID);
            strcpy(data[index].studentID, stdID);
            printf("...Update successful... \n");
            break;
        case 2:
            printf("Enter new student name: \n");
            scanf("%s", stdname);
            strcpy(data[index].studentName, stdname);
            printf("...Update successful... \n");
            break;
        case 3:
            printf("Enter new student email: \n");
            scanf("%s", stdemail);
            strcpy(data[index].studentEmail, stdemail);
            printf("...Update successful... \n");
            break;
        case 4:
            printf("Enter new course ID: \n");
            scanf("%s", stdCourse);
            strcpy(data[index].courseID, stdCourse);
            printf("...Update successful... \n");
            break;
        case 5:
            printf("Enter new student grade: \n");
            scanf("%s", stdGPA);
            strcpy(data[index].grade, stdGPA);
            printf("...Update successful... \n");
            break;
        case 6:
            exit(1);
            break;
    }
    if (fwrite(&total, sizeof(int), 1, file) != 1)
        return false;

    if (fwrite(data, sizeof(Student), total, file) != total)
        return false;
   
    if (fclose(file) == EOF)
        return false;

    return true;
}