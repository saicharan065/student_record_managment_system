#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUD_FILE "students.txt"
#define CRE_FILE  "credentials.txt"

char currentUser[50];
char currentRole[20];

int login() {
    char u[50], p[50], r[20];
    char inUser[50], inPass[50];
    printf("USERNAME: ");
    scanf("%s", inUser);
    printf("PASSWORD: ");
    scanf("%s", inPass);
    FILE *fp = fopen(CRE_FILE, "r");
    if (!fp) {
        printf("Credential file missing!\n");
        return 0;
    }
    while (fscanf(fp, "%s %s %s", u, p, r) == 3) {
        if (strcmp(inUser, u) == 0 && strcmp(inPass, p) == 0) {
            strcpy(currentUser, u);
            strcpy(currentRole, r);
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void addStudent() {
    int roll;
    char name[50];
    float mark;
    char type[20];  

    printf("Roll: ");
    scanf("%d", &roll);
    printf("Name: ");
    scanf(" %[^\n]", name);
    printf("Mark: ");
    scanf("%f", &mark);
    printf("Type (hosteler/dayscholar): ");
    scanf("%s", type);

    FILE *fp = fopen(STUD_FILE, "a");
    fprintf(fp, "%d %s %.2f %s\n", roll, name, mark, type);
    fclose(fp);
    printf("Student added!\n");
}

void displayStudents() {
    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp) {
        printf("No student file!\n");
        return;
    }
    int roll;
    char name[50];
    float mark;
    char type[20];

    printf("Roll\tName\t\tMark\tType\n");
    printf("----\t----\t\t----\t----\n");
    while (fscanf(fp, "%d %s %f %s", &roll, name, &mark, type) == 4) {
        printf("%d\t%s\t\t%.2f\t%s\n", roll, name, mark, type);
    }
    fclose(fp);
}

void searchStudent() {
    int find, roll;
    char name[50];
    float mark;
    char type[20];

    printf("Enter roll to search: ");
    scanf("%d", &find);
    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp) {
        printf("No student file!\n");
        return;
    }
    int found = 0;
    while (fscanf(fp, "%d %s %f %s", &roll, name, &mark, type) == 4) {
        if (roll == find) {
            printf("Found: %d %s %.2f %s\n", roll, name, mark, type);
            found = 1;
            break;
        }
    }   
    if (!found) {
        printf("Student not found!\n");
    }
    fclose(fp);
}

void deleteStudent() {
    int delRoll;
    printf("Enter roll to delete: ");
    scanf("%d", &delRoll);
    FILE *fp = fopen(STUD_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");
    int roll;
    char name[50];
    float mark;
    char type[20];
    int found = 0;
    while (fscanf(fp, "%d %s %f %s", &roll, name, &mark, type) == 4) {
        if (roll != delRoll) {
            fprintf(temp, "%d %s %.2f %s\n", roll, name, mark, type);
        } else {
            found = 1;
        }
    }
    fclose(fp);
    fclose(temp);
    remove(STUD_FILE);
    rename("temp.txt", STUD_FILE);
    if (found) printf("Student deleted!\n");
    else printf("Roll not found!\n");
}

void updateStudent() {
    int updateRoll;
    printf("Enter roll to update: ");
    scanf("%d", &updateRoll);

    FILE *fp = fopen(STUD_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    int roll;
    char name[50];
    float mark;
    char type[20];
    int found = 0;

    while (fscanf(fp, "%d %s %f %s", &roll, name, &mark, type) == 4) {
        if (roll == updateRoll) {
            found = 1;
            char newName[50];
            float newMark;
            char newType[20];

            printf("New Name: ");
            scanf(" %[^\n]", newName);
            printf("New Mark: ");
            scanf("%f", &newMark);
            printf("New Type (hosteler/dayscholar): ");
            scanf("%s", newType);

            fprintf(temp, "%d %s %.2f %s\n", roll, newName, newMark, newType);
        } else {
            fprintf(temp, "%d %s %.2f %s\n", roll, name, mark, type);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(STUD_FILE);
    rename("temp.txt", STUD_FILE);

    if (found) printf("Student updated!\n");
    else printf("Roll not found!\n");
}

void securityMenu() {
    int c;
    while (1) {
        printf("\n=== SECURITY MENU ===\n");
        printf("1. Search Student\n");
        printf("2. Logout\n");
        printf("Choice: ");
        scanf("%d", &c);
        if (c == 1) {
            searchStudent();
        } else if (c == 2) {
            return;
        } else {
            printf("Invalid choice!\n");
        }
    }
}

void adminMenu() {
    int c;
    while (1) {
        printf("\n=== ADMIN MENU ===\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Logout\n");
        printf("Choice: ");
        scanf("%d",&c);
        if(c==1) addStudent();
        else if(c==2) displayStudents();
        else if(c==3) searchStudent();
        else if(c==4) updateStudent();
        else if(c==5) deleteStudent();
        else if(c==6) return;
        else printf("Invalid choice!\n");
    }
}

void staffMenu() {
    int c;
    while (1) {
        printf("\n=== STAFF MENU ===\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Logout\n");
        printf("Choice: ");
        scanf("%d",&c);
        if(c==1) addStudent();
        else if(c==2) displayStudents();
        else if(c==3) searchStudent();
        else if(c==4) updateStudent();
        else if(c==5) return;
        else printf("Invalid choice!\n");
    }
}

void guestMenu() {
    int c;
    while (1) {
        printf("\n=== GUEST MENU ===\n");
        printf("1. Display Students\n");
        printf("2. Search Student\n");
        printf("3. Logout\n");
        printf("Choice: ");
        scanf("%d",&c);
        if(c==1) displayStudents();
        else if(c==2) searchStudent();
        else if(c==3) return;
        else printf("Invalid choice!\n");
    }
}

int main() {
    printf("=== STUDENT MANAGEMENT SYSTEM ===\n");
    
    if (!login()) {
        printf("Invalid login!\n");
        return 0;
    }
    
    printf("\nWelcome, %s! Logged in as: %s\n", currentUser, currentRole);
    if (strcmp(currentRole, "security") == 0) {
        printf("\nEntering SECURITY MODE...\n");
        securityMenu();
    } else if (strcmp(currentRole, "admin") == 0) {
        adminMenu();
    } else if (strcmp(currentRole, "staff") == 0) {
        staffMenu();
    } else {
        guestMenu();
    }

    printf("\nLogged out successfully. Goodbye!\n");
    return 0;
}
