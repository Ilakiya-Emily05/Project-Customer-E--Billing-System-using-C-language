#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Done by Jessicaa V
typedef struct {
    char name[100];
    char address[200];
    char phone[15];
    float paid_amount;
    float due_amount;
    char payment_date[11]; 
} Customer;

void input(Customer *c);
void writefile(const Customer *c);
void search(const char *filename, const char *search_key);
void output(const Customer *c);
void updatefile(const char *filename, const Customer *new_data, const char *search_key);
//Done by Ilakiya Emily
int main() {
    Customer c;
    char filename[] = "C:\\Users\\Gaia\\Desktop\\Internship\\Data\\customer_data.txt";
    char search_key[100];
    int choice;

    while (1) {
        printf("\n1. Add New Customer\n2. Search Customer\n3. Update Customer\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 
        switch (choice) {
            case 1:
                input(&c);
                writefile(&c);
                break;
            case 2:
                printf("Enter name or phone number to search: ");
                fgets(search_key, sizeof(search_key), stdin);
                search_key[strcspn(search_key, "\n")] = '\0'; 
                search(filename, search_key);
                break;
            case 3:
                printf("Enter name or phone number to update: ");
                fgets(search_key, sizeof(search_key), stdin);
                search_key[strcspn(search_key, "\n")] = '\0'; 
                printf("Enter updated details:\n");
                input(&c);
                updatefile(filename, &c, search_key);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
//Done by Gopika Kumar
void input(Customer *c) {
    printf("Enter Customer Name: ");
    fgets(c->name, sizeof(c->name), stdin);
    c->name[strcspn(c->name, "\n")] = 0; 

    printf("Enter Address: ");
    fgets(c->address, sizeof(c->address), stdin);
    c->address[strcspn(c->address, "\n")] = 0; 

    printf("Enter Phone Number: ");
    fgets(c->phone, sizeof(c->phone), stdin);
    c->phone[strcspn(c->phone, "\n")] = 0; 

    printf("Enter Paid Amount: ");
    scanf("%f", &c->paid_amount);

    printf("Enter Due Amount: ");
    scanf("%f", &c->due_amount);
    getchar(); 

    printf("Enter Payment Date (dd/mm/yyyy): ");
    fgets(c->payment_date, sizeof(c->payment_date), stdin);
    c->payment_date[strcspn(c->payment_date, "\n")] = 0; 
}
//Done by Ilakiya Emily
void writefile(const Customer *c) {
    FILE *file = fopen("C:\\Users\\Gaia\\Desktop\\Internship\\Data\\customer_data.txt", "a");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    fprintf(file, "%s\n%s\n%s\n%.2f\n%.2f\n%s\n\n",
            c->name, c->address, c->phone,
            c->paid_amount, c->due_amount,
            c->payment_date);

    if (ferror(file)) {
        perror("Error writing to file");
    } else {
        printf("Customer data saved successfully.\n");
    }

    fclose(file);
}
//Done by Ilakiya Emily
void search(const char *filename, const char *search_key) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    Customer c;
    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, search_key) != NULL) {
            found = 1;
            do {
                fgets(c.name, sizeof(c.name), file);
                fgets(c.address, sizeof(c.address), file);
                fgets(c.phone, sizeof(c.phone), file);
                fscanf(file, "%f %f", &c.paid_amount, &c.due_amount);
                fgetc(file); 
                fgets(c.payment_date, sizeof(c.payment_date), file);
                c.payment_date[strcspn(c.payment_date, "\n")] = 0; 

                output(&c);

                fgets(line, sizeof(line), file);

            } while (fgets(line, sizeof(line), file) && line[0] != '\n');
            break;
        }
    }

    if (!found) {
        printf("Customer not found.\n");
    }

    fclose(file);
}
//Done by Ilakiya Emily
void output(const Customer *c) {
    printf("\nCustomer Details:\n");
    printf("Name: %s\n", c->name);
    printf("Address: %s\n", c->address);
    printf("Phone: %s\n", c->phone);
    printf("Amount Paid: %.2f\n", c->paid_amount);
    printf("Due Amount: %.2f\n", c->due_amount);
    printf("Payment Date: %s\n", c->payment_date);
}

void updatefile(const char *filename, const Customer *new_data, const char *search_key) {
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        perror("Error opening file for updating");
        return;
    }

    FILE *temp = fopen("C:\\Users\\Gaia\\Desktop\\Internship\\Data\\temp.txt", "w");
    if (temp == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    Customer c;
    char line[256];
    int found = 0;
//Done by Ilakiya Emily
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, search_key) != NULL) {
            found = 1;
            do {
                fgets(c.name, sizeof(c.name), file);
                fgets(c.address, sizeof(c.address), file);
                fgets(c.phone, sizeof(c.phone), file);
                fscanf(file, "%f %f", &c.paid_amount, &c.due_amount);
                fgetc(file); 
                fgets(c.payment_date, sizeof(c.payment_date), file);
                c.payment_date[strcspn(c.payment_date, "\n")] = 0;

                fprintf(temp, "%s\n%s\n%s\n%.2f\n%.2f\n%s\n\n",
                        new_data->name, new_data->address, new_data->phone,
                        new_data->paid_amount, new_data->due_amount,
                        new_data->payment_date);

                fgets(line, sizeof(line), file);

            } while (fgets(line, sizeof(line), file) && line[0] != '\n');
        } else {
            fprintf(temp, "%s", line);
        }
    }

    if (!found) {
        printf("Customer not found.\n");
    }

    fclose(file);
    fclose(temp);
    if (remove(filename) != 0) {
        perror("Error removing original file");
    } else if (rename("C:\\Users\\Gaia\\Desktop\\Internship\\Data\\temp.txt", filename) != 0) {
        perror("Error renaming temporary file");
    }
}

