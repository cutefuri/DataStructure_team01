#include <stdio.h>
#include <json-c/json.h>

#define STUDENT_FILE "json/student.json"

int student_inf_managerment(){
    FILE *fp = fopen(STUDENT_FILE, "wt");

    if (fp == NULL)
        return -1;

    fprintf(fp,"[]");
    fclose(fp);

    return 0;
}

int add_student(char *name, size_t age, char *phone, char *parent_phone, char *class_time){
    json_object *obj, *student, *root;

    obj = json_object_new_object();
    root = json_object_from_file(STUDENT_FILE);
    if(!root){
        printf("Failed to parse JSON data. \n");
        return -1;
    }

    student = json_object_new_object();
    json_object_object_add(student, "name", json_object_new_string(name));
    json_object_object_add(student, "age", json_object_new_int(age));
    json_object_object_add(student, "parent_phone_num", json_object_new_string(parent_phone));
    json_object_object_add(student, "class_time", json_object_new_string(class_time));

    json_object_object_add(obj, phone, student);

    json_object_array_add(root, obj);

    json_object_to_file(STUDENT_FILE, root);

    return 1;
}

int del_student(const char *phone){
    json_object *root, *obj;

    root = json_object_from_file(STUDENT_FILE);
    if(!root){
        printf("Failed to parse JSON data. \n");
        return -1;
    }

    obj = json_object_object_get(root, phone);

    if(obj ==NULL){
        printf("The information you entered does not exist. \n");
        return -1;
    }

    json_object_object_del(obj, phone);

    json_object_to_file(STUDENT_FILE, root);

    return 1;
}

int del_student1(const char *phone){
    FILE *file = fopen(STUDENT_FILE, "r");
    if (!file) {
        printf("Failed to open JSON file.\n");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *jsonData = (char *)malloc(fileSize + 1);
    fread(jsonData, 1, fileSize, file);
    fclose(file);

    struct json_object *root = json_tokener_parse(jsonData);
    free(jsonData);
    if (!root) {
        printf("Failed to parse JSON data.\n");
        return -1;
    }

    json_object_object_del(root, phone);

    file = fopen(STUDENT_FILE, "w");
    if (!file) {
        printf("Failed to open JSON file for writing.\n");
        return -1;
    }
    fprintf(file, "%s", json_object_to_json_string(root));
    fclose(file);

    json_object_put(root);

    printf("Object with key '%s' deleted successfully.\n", phone);

    return 0;
}

int main(int arge, char *argv[]){
    int choice;
    while(1){
        printf("\n1. add student information \n");
        printf("2. delete student information \n");
        printf("3. modify student information \n");
        printf("4. exit \n\n");
        printf("choose funtion \n >>");
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:
            student_inf_managerment();
            break;
        case 1:
            add_student("test1", 21, "010-1234-1234", "010-1111-1111", "class_A");
            add_student("test2", 23, "010-0000-0000", "010-2222-2222","clss_B");
            break;
        case 2:
            del_student("010-1234-1234");
            break;
        case 3:
            break;
        case 4:
            return 0;
        default:
            printf("Error: try again. \n");
            return 0;
        }
    }
    return 0;
}