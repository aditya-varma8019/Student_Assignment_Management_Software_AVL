#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct Student_record
{
    int student_id;
    char name[50];
    int group_partner_id;
    int group_id;
    int assignment_id;
    char assignment_name[50];
    char deadline[20];
    char status_of_assignment[20]; //(submitted/not-submitted/evaluated
    float offline_evaluation_marks;
    float viva_marks;
} Student_record;

typedef struct Assignment
{
    int assignment_id;
    char topic_name[50];
    char status[20]; //(declared/due-date-over/evaluated)
} Assignment;

typedef struct Assignment_record
{
    int group_id;
    char status[20]; //(declared/submitted/not-submitted/evaluated)
    float viva_marks;
    float offline_marks;
} Assignment_record;

typedef struct AVLNodeStudent
{
    Student_record data;
    int height;
    struct AVLNodeStudent *left;
    struct AVLNodeStudent *right;
} Students;

typedef struct AVLNodeAssignment
{
    Assignment data;
    int height;
    struct AVLNodeGroup *groupHead; // this points to the node of the tree
    struct AVLNodeAssignment *left;
    struct AVLNodeAssignment *right;
} Assignments;

typedef struct AVLNodeGroup
{
    Assignment_record data;
    int height;
    struct AVLNodeGroup *left;
    struct AVLNodeGroup *right;
} Groups;

Students *studentDataBase = NULL;
Assignments *assignmentDataBase = NULL;

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(Students *root)
{
    int retval;
    if (root == NULL)
    {
        retval = -1;
    }
    else if (root->left == NULL && root->right == NULL)
    {
        retval = 0;
    }
    else
    {
        retval = 1 + max(height(root->left), height(root->right));
    }
    return retval;
}

Students *newStudentNode(Student_record data)
{
    Students *node = (Students *)malloc(sizeof(Students));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

Students *rightRotate(Students *y)
{
    Students *x = y->left;
    Students *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Students *leftRotate(Students *x)
{
    Students *y = x->right;
    Students *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int getBalance(Students *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return height(node->left) - height(node->right);
}

int heightA(Assignments *root)
{
    int retval;
    if (root == NULL)
    {
        retval = -1;
    }
    else if (root->left == NULL && root->right == NULL)
    {
        retval = 0;
    }
    else
    {
        retval = 1 + max(heightA(root->left), heightA(root->right));
    }
    return retval;
}

Assignments *newAssignmentNode(Assignment data)
{
    Assignments *node = (Assignments *)malloc(sizeof(Assignments));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    node->groupHead = NULL;
    return node;
}

Assignments *rightRotateA(Assignments *y)
{
    Assignments *x = y->left;
    Assignments *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(heightA(y->left), heightA(y->right)) + 1;
    x->height = max(heightA(x->left), heightA(x->right)) + 1;
    return x;
}

Assignments *leftRotateA(Assignments *x)
{
    Assignments *y = x->right;
    Assignments *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(heightA(x->left), heightA(x->right)) + 1;
    y->height = max(heightA(y->left), heightA(y->right)) + 1;
    return y;
}

int getBalanceA(Assignments *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return heightA(node->left) - heightA(node->right);
}

int heightG(Groups *root)
{
    int retval;
    if (root == NULL)
    {
        retval = -1;
    }
    else if (root->left == NULL && root->right == NULL)
    {
        retval = 0;
    }
    else
    {
        retval = 1 + max(heightG(root->left), heightG(root->right));
    }
    return retval;
}

int getBalanceG(Groups *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return heightG(node->left) - heightG(node->right);
}

Groups *rightRotateG(Groups *y)
{
    Groups *x = y->left;
    Groups *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(heightG(y->left), heightG(y->right)) + 1;
    x->height = max(heightG(x->left), heightG(x->right)) + 1;
    return x;
}

Groups *leftRotateG(Groups *x)
{
    Groups *y = x->right;
    Groups *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(heightG(x->left), heightG(x->right)) + 1;
    y->height = max(heightG(y->left), heightG(y->right)) + 1;
    return y;
}

Groups *newGroupNode(Assignment_record data)
{
    Groups *newGroup = (Groups *)malloc(sizeof(Groups));
    newGroup->data = data;
    newGroup->left = NULL;
    newGroup->right = NULL;
}

// Assignments* newAssignmentNode(Assignment data)
// {
//     Assignments* newAssignment=(Assignments*)malloc(sizeof(Assignments));
//     newAssignment->data=data;
//     newAssignment->groupHead=NULL;
//     newAssignment->left=NULL;
//     newAssignment->right=NULL;
//     return newAssignment;
// }

Students *insertStudentRecord(Students *node, Student_record data)
{
    Students *newNode = newStudentNode(data);

    if (node == NULL)
    {
        node = newNode;
    }
    if (data.student_id < node->data.student_id)
    {
        node->left = insertStudentRecord(node->left, data);
    }
    else if (data.student_id > node->data.student_id)
    {
        node->right = insertStudentRecord(node->right, data);
    }
    else
    {
        // student with the same id already exists
        // return node;
    }
    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);
    if (balance > 1 && data.student_id < node->left->data.student_id)
    {
        node = rightRotate(node);
    }
    else if (balance < -1 && data.student_id > node->right->data.student_id)
    {
        node = leftRotate(node);
    }
    else if (balance > 1 && data.student_id > node->left->data.student_id)
    {
        node->left = leftRotate(node->left);
        node = rightRotate(node);
    }
    else if (balance < -1 && data.student_id < node->right->data.student_id)
    {
        node->right = rightRotate(node->right);
        node = leftRotate(node);
    }
    return node;
}

Groups *changeGroups(Groups *root, Assignment_record data)
{
    if (root == NULL)
    {
        root = newGroupNode(data);
        return root;
    }
    if (data.group_id < root->data.group_id)
    {
        root->left = changeGroups(root->left, data);
    }
    else if (data.group_id > root->data.group_id)
    {
        root->right = changeGroups(root->right, data);
    }
    else
    {
        strcpy(root->data.status, data.status);
        root->data.viva_marks = data.viva_marks;
        root->data.offline_marks = data.offline_marks;
        return root;
    }

    root->height = 1 + max(heightG(root->left), heightG(root->right));
    int balance = getBalanceG(root);

    // perform AVL rotations if necessary
    if (balance > 1 && data.group_id < root->left->data.group_id)
    {
        root = rightRotateG(root);
    }
    else if (balance < -1 && data.group_id > root->right->data.group_id)
    {
        root = leftRotateG(root);
    }
    else if (balance > 1 && data.group_id > root->left->data.group_id)
    {
        root->left = leftRotateG(root->left);
        root = rightRotateG(root);
    }
    else if (balance < -1 && data.group_id < (root)->right->data.group_id)
    {
        root->right = rightRotateG(root->right);
        root = leftRotateG(root);
    }
    return root;
}

Assignments *changeAssignmentRecord(Assignments *root, Assignment data, Student_record student)
{
    // perform regular AVL tree insertion
    Assignments *newNode = newAssignmentNode(data);
    if (root == NULL)
    {
        Assignment_record *newGroup = (Assignment_record *)malloc(sizeof(Assignment_record));
        newGroup->group_id = student.group_id;
        newGroup->offline_marks = student.offline_evaluation_marks;
        newGroup->viva_marks = student.viva_marks;
        strcpy(newGroup->status, student.status_of_assignment);
        newNode->groupHead = changeGroups(newNode->groupHead, *newGroup);
        FILE *fp = fopen("assignments.txt", "a+");
        if (fp == NULL)
        {
            printf("\nFile not found for updating!!!");
        }
        else
        {
            int numNodes=1;
            fprintf(fp, "\n%d %s %s %d ", newNode->data.assignment_id, newNode->data.topic_name, newNode->data.status,numNodes);
            fprintf(fp,"\n%d %s %f %f",newGroup->group_id,newGroup->status,newGroup->offline_marks,newGroup->viva_marks);
        }
        fclose(fp);
        return root = newNode;
    }
    if (data.assignment_id < root->data.assignment_id)
    {
        root->left = changeAssignmentRecord(root->left, data, student);
    }
    else if (data.assignment_id > root->data.assignment_id)
    {
        root->right = changeAssignmentRecord(root->right, data, student);
    }
    else
    {
        // the assignment record already exists, update the status
        strcpy(root->data.status, data.status);
        // here insertion of groups takes place
        Groups *curr = root->groupHead;
        Assignment_record *temp = (Assignment_record *)malloc(sizeof(Assignment_record));
        temp->group_id = student.group_id;
        temp->offline_marks = student.offline_evaluation_marks;
        temp->viva_marks = student.viva_marks;
        strcpy(temp->status, student.status_of_assignment);
        root->groupHead = changeGroups(curr, *temp);
    }

    // update the height and balance factor of the node
    root->height = 1 + max(heightA(root->left), heightA(root->right));
    int balance = getBalanceA(root);

    // perform AVL rotations if necessary
    if (balance > 1 && data.assignment_id < root->left->data.assignment_id)
    {
        root = rightRotateA(root);
    }
    else if (balance < -1 && data.assignment_id > root->right->data.assignment_id)
    {
        root = leftRotateA(root);
    }
    else if (balance > 1 && data.assignment_id > root->left->data.assignment_id)
    {
        root->left = leftRotateA(root->left);
        root = rightRotateA(root);
    }
    else if (balance < -1 && data.assignment_id < (root)->right->data.assignment_id)
    {
        root->right = rightRotateA(root->right);
        root = leftRotateA(root);
    }
    return root;
}

Assignment_record *inputOfGroup()
{
    Assignment_record *newGroup = (Assignment_record *)malloc(sizeof(Assignment_record));
    printf("\nEnter group id: ");
    scanf("%d", &newGroup->group_id);
    printf("\nEnter viva marks: ");
    scanf("%f", &newGroup->viva_marks);
    printf("\nEnter offline marks: ");
    scanf("%f", &newGroup->offline_marks);
    return newGroup;
}

Assignments *insertAssignmentRecord(Assignments *root, Assignment data)
{
    Assignments *newAssignment = newAssignmentNode(data);
    if (root == NULL)
    {
        root = newAssignment;
        return root;
    }
    if (data.assignment_id < root->data.assignment_id)
    {
        root->left = insertAssignmentRecord(root->left, data);
    }
    else if (data.assignment_id > root->data.assignment_id)
    {
        root->right = insertAssignmentRecord(root->right, data);
    }
    else
    {
        // the assignment record already exists, update the status
        strcpy(root->data.status, data.status);
        // here insertion of groups takes place
        // Groups* curr=root->groupHead;
        //  Assignment_record* temp=(Assignment_record*)malloc(sizeof(Assignment_record));
        //  temp->
        root->groupHead = NULL;
    }

    root->height = 1 + max(heightA(root->left), heightA(root->right));
    int balance = getBalanceA(root);

    // perform AVL rotations if necessary
    if (balance > 1 && data.assignment_id < root->left->data.assignment_id)
    {
        root = rightRotateA(root);
    }
    else if (balance < -1 && data.assignment_id > root->right->data.assignment_id)
    {
        root = leftRotateA(root);
    }
    else if (balance > 1 && data.assignment_id > root->left->data.assignment_id)
    {
        root->left = leftRotateA(root->left);
        root = rightRotateA(root);
    }
    else if (balance < -1 && data.assignment_id < (root)->right->data.assignment_id)
    {
        root->right = rightRotateA(root->right);
        root = leftRotateA(root);
    }
    return root;
}

// Students *changeStudentDataBase(Students *root, Student_record data)
// {
//     Students *newStudent = (Students *)malloc(sizeof(Students));
// }
//------------------------
Students *search_student_using_student_id(Students *root, int student_id)
{
    if (root == NULL || root->data.student_id == student_id)
    {
        return root;
    }
    if (root->data.student_id > student_id)
    {
        return search_student_using_student_id(root->left, student_id);
    }
    return search_student_using_student_id(root->right, student_id);
}

Assignments *search_assignments_using_assignment_id(Assignments *root, int a_id)
{
    if (root == NULL || root->data.assignment_id == a_id)
        return root;
    if (root->data.assignment_id > a_id)
        return search_assignments_using_assignment_id(root->left, a_id);
    return search_assignments_using_assignment_id(root->right, a_id);
}

Groups *search_groups_using_group_id(Groups *root, int g_id)
{
    if (root == NULL || root->data.group_id == g_id)
        return root;
    if (root->data.group_id > g_id)
        return search_groups_using_group_id(root->left, g_id);
    return search_groups_using_group_id(root->right, g_id);
}

void submit_assignment(int a_id, int g_id)
{
    Assignments *node = search_assignments_using_assignment_id(assignmentDataBase, a_id);
    // strcpy(node->data.status,"submitted");
    Groups *currGroup = search_groups_using_group_id(node->groupHead, g_id);
    if(currGroup==NULL) printf("Group not found for this assignment!!!");
    else if(strcmp(currGroup->data.status,"not-submitted")==0)
    {
        printf("Successfully Submitted the Assignment!!!");
        strcpy(currGroup->data.status, "submitted");
    }
    else 
    {
        printf("The assignment of the given group is already submitted!!!");
    }
    // can enter here marks of offline and viva
}
//-----------------------------

void traverse_groups_inorder(Groups *root)
{
    if (root != NULL)
    {
        traverse_groups_inorder(root->left);
        strcpy(root->data.status, "submitted");
        traverse_groups_inorder(root->right);
    }
}

void assignment_submit(int a_id)
{
    Assignments *node = search_assignments_using_assignment_id(assignmentDataBase, a_id);
    if(node==NULL)
    {
        printf("Assignment not found!!!");
    }
    else
    {
        strcpy(node->data.status,"evaluated");
        Groups *curr = node->groupHead;
        if(curr==NULL)
        {
            printf("There are no groups present for this assignment!!!");
        }
        else
        {
            traverse_groups_inorder(curr);
            printf("Successfully Updated!!!");
        }
    }
}

//--------------------

void assignments_declared_but_not_evaluated(Assignments *root)
{
    if (root != NULL)
    {
        assignments_declared_but_not_evaluated(root->left);
        if (strcmp(root->data.status, "declared") == 0)
        {
            printf("\nThe assignment of assignment id: %d is not evaluated", root->data.assignment_id);
        }
        assignments_declared_but_not_evaluated(root->right);
    }
}
//--------------------------------

void students_traversal_inorder(Students *root, int curr_d, int curr_m, int curr_y)
{
    if (root != NULL)
    {
        students_traversal_inorder(root->left, curr_d, curr_m, curr_y);
        int dd, dm, dy;
        int temp = 0;
        for (int i = 0; i < 10; i++)
        {
            if (root->data.deadline[i] != '/')
            {
                temp = temp * 10 + (root->data.deadline[i] - '0');
            }
            else
            {
                if (i == 2)
                {
                    dd = temp;
                }
                if (i == 5)
                {
                    dm = temp;
                }
                temp = 0;
            }
        }
        dy = temp;
        if (curr_y > dy && strcmp(root->data.status_of_assignment,"not-submitted")==0)
        {
            printf("Group ID: %d, Assignment Name/ID: %s\n", root->data.group_id, root->data.assignment_name);
        }
        else if (curr_m > dm && curr_y == dy && strcmp(root->data.status_of_assignment,"not-submitted")==0)
        {
            printf("Group ID: %d, Assignment Name/ID: %s\n", root->data.group_id, root->data.assignment_name);
        }
        else if (curr_d > dd && curr_m == dm && curr_y == dy && strcmp(root->data.status_of_assignment,"not-submitted")==0)
        {
            printf("Group ID: %d, Assignment Name/ID: %s\n", root->data.group_id, root->data.assignment_name);
        }
        students_traversal_inorder(root->right, curr_d, curr_m, curr_y);
    }
}

void groups_not_submitted_assignments(char *curr_date)
{
    int curr_d = 0, curr_y = 0, curr_m = 0;
    int temp = 0;
    for (int i = 0; i < 10; i++)
    {
        if (curr_date[i] != '/')
        {
            temp = temp * 10 + (curr_date[i] - '0');
        }
        else
        {
            if (i == 2)
            {
                curr_d = temp;
            }
            else if (i == 5)
            {
                curr_m = temp;
            }
            temp = 0;
        }
    }
    curr_y = temp;
    printf("\nList of student groups who have not submitted the assignments even if the due-date is over:\n");
    students_traversal_inorder(studentDataBase, curr_d, curr_m, curr_y);
}
//-------------------------

void groups_traversal(Groups *root)
{
    if (root == NULL)
        return;

    groups_traversal(root->left);

    if (strcmp(root->data.status, "submitted") == 0 && root->data.viva_marks != -1.0 && root->data.offline_marks != -1.0)
    {
        printf("\nEvaluation of students of Group id: %d is not yet taken", root->data.group_id);
    }
    if (strcmp(root->data.status, "submitted") == 0 && root->data.viva_marks == -1.0 && root->data.offline_marks != -1.0)
    {
        printf("\nViva of students group id :%d is yet to be taken", root->data.group_id);
    }
    if (strcmp(root->data.status, "submitted") == 0 && root->data.viva_marks != -1.0 && root->data.offline_marks == -1.0)
    {
        printf("\nOffline evaluation of students group id :%d is yet to be taken", root->data.group_id);
    }
}

void printPendingAssignments(Assignments *root)
{
    if (root == NULL)
    {
        return;
    }

    printPendingAssignments(root->left);

    Groups *curr = root->groupHead;
    groups_traversal(curr);
    printPendingAssignments(root->right);
}

//---------------------------

int compareGroupRecords(const void *a, const void *b)
{
    Assignment_record *groupA = *(Assignment_record **)a;
    Assignment_record *groupB = *(Assignment_record **)b;

    float totalMarksA = groupA->viva_marks + groupA->offline_marks;
    float totalMarksB = groupB->viva_marks + groupB->offline_marks;

    if (totalMarksA > totalMarksB)
    {
        return -1;
    }
    //else if (totalMarksA < totalMarksB)
    // {
    //     return 1;
    // }
    else
    {
        return 1;
    }
}

int getGroupCount(Groups *node)
{
    int retVal;
    if (node == NULL)
    {
        retVal= 0;
    }
    else
    retVal= 1 + getGroupCount(node->left) + getGroupCount(node->right);
    return retVal;
}

void fillGroupRecords(Assignment_record **groupRecords, Groups *node)
{
    static int index = 0;

    if (node == NULL)
    {
        return;
    }

    fillGroupRecords(groupRecords, node->right);

    groupRecords[index++] = &(node->data);

    fillGroupRecords(groupRecords, node->left);
}

void printStudentGroupsDetails(int assignmentId)
{
    Assignments *assignmentNode = search_assignments_using_assignment_id(assignmentDataBase, assignmentId);

    if (assignmentNode == NULL)
    {
        printf("Assignment not found in the database.\n");
        return;
    }

    int count = getGroupCount(assignmentNode->groupHead);
    Assignment_record **groupRecords = (Assignment_record **)malloc(sizeof(Assignment_record *) * count);
    fillGroupRecords(groupRecords, assignmentNode->groupHead);

    qsort(groupRecords, count, sizeof(Assignment_record *), compareGroupRecords);

    for (int i = 0; i < count; i++)
    {
        printf("Group ID: %d\n", groupRecords[i]->group_id);
        printf("Status: %s\n", groupRecords[i]->status);
        printf("Viva marks: %.2f\n", groupRecords[i]->viva_marks);
        printf("Offline marks: %.2f\n", groupRecords[i]->offline_marks);
        printf("\n");
    }

    free(groupRecords);
}
//------------------------------------

// void group_with_highest_marks(Groups *root, int *maxMarks)
// {
//     if (root != NULL)
//     {
//         group_with_highest_marks(root->left, maxMarks);
//         int marks = root->data.offline_marks + root->data.viva_marks;
//         if (marks > *maxMarks)
//         {
//             *maxMarks = marks;
//         }
//         group_with_highest_marks(root->right, maxMarks);
//     }
// }

// void print_student_groups(Groups *root, int marks, int a_id)
// {
//     if (root != NULL)
//     {
//         print_student_groups(root->left, marks, a_id);
//         if (root->data.offline_marks + root->data.viva_marks == marks)
//         {
//             printf("\nThe student group of group id: %d has highest marks of: %d for the assignment of assignment id: %d", root->data.group_id, marks, a_id);
//         }
//         print_student_groups(root->right, marks, a_id);
//     }
// }

// void students_groups_with_highest_marks(Assignments *root)
// {
//     if (root != NULL)
//     {
//         students_groups_with_highest_marks(root->left);
//         int *marks;
//         *marks = 0;
//         Groups *curr = root->groupHead;
//         group_with_highest_marks(curr, marks);
//         print_student_groups(curr, *marks, root->data.assignment_id);
//         students_groups_with_highest_marks(root->right);
//     }
// }

void group_with_highest_marks(Groups *root, float *maxMarks, int *groupId)
{
    if (root != NULL)
    {
        group_with_highest_marks(root->left, maxMarks, groupId);
        float marks = root->data.offline_marks + root->data.viva_marks;
        if (marks > *maxMarks)
        {
            *maxMarks = marks;
            *groupId = root->data.group_id;
        }
        group_with_highest_marks(root->right, maxMarks, groupId);
    }
}

void print_student_groups(Groups *root, float marks, int a_id)
{
    if (root != NULL)
    {
        print_student_groups(root->left, marks, a_id);
        float groupMarks = root->data.offline_marks + root->data.viva_marks;
        if ((groupMarks == marks))
        {
            printf("\nThe student group of group id: %d has highest marks of: %.2f for the assignment of assignment id: %d", root->data.group_id, marks, a_id);
        }
        print_student_groups(root->right, marks, a_id);
    }
}

void students_groups_with_highest_marks(Assignments *root)
{
    if (root != NULL)
    {
        students_groups_with_highest_marks(root->left);
        float maxMarks = 0;
        int groupId = 0;
        Groups *curr = root->groupHead;
        group_with_highest_marks(curr, &maxMarks, &groupId);
        print_student_groups(curr, maxMarks, root->data.assignment_id);
        students_groups_with_highest_marks(root->right);
    }
}


//-------------------------------

void search_assignments(Assignments *root, int mn, int mx)
{
    if (root != NULL)
    {
        search_assignments(root->left, mn, mx);
        if (root->data.assignment_id > mn && root->data.assignment_id < mx)
        {
            printf("\nAssignment id is: %d status of the assignment is: %s topic of the assignment is: %s", root->data.assignment_id, root->data.status, root->data.topic_name);
        }
        search_assignments(root->right, mn, mx);
    }
}

void range_search(int a1_id, int a2_id)
{
    int mx = a1_id, mn = a2_id;
    if (mn > mx)
    {
        int temp = mx;
        mx = mn;
        mn = temp;
    }
    search_assignments(assignmentDataBase, mn, mx);
}

//------------------------------

void inorderTraversal(Students *root)
{
    if (root == NULL)
    {
        return;
    }
    inorderTraversal(root->left);
    printf("Student ID: %d\n", root->data.student_id);
    printf("Name: %s\n", root->data.name);
    printf("Group Partner ID: %d\n", root->data.group_partner_id);
    printf("Group ID: %d\n", root->data.group_id);
    printf("Assignment ID: %d\n", root->data.assignment_id);
    printf("Assignment Name: %s\n", root->data.assignment_name);
    printf("Deadline: %s\n", root->data.deadline);
    printf("Status of Assignment: %s\n", root->data.status_of_assignment);
    printf("Offline Evaluation Marks: %.2f\n", root->data.offline_evaluation_marks);
    printf("Viva Marks: %.2f\n", root->data.viva_marks);
    printf("\n");
    inorderTraversal(root->right);
}

void groupsInorderTraversal(Groups *root)
{
    if (root == NULL)
        return;

    groupsInorderTraversal(root->left);

    printf("\tGroup ID: %d\n", root->data.group_id);
    printf("\tStatus: %s\n", root->data.status);
    printf("\tViva Marks: %.2f\n", root->data.viva_marks);
    printf("\tOffline Evaluation Marks: %.2f\n", root->data.offline_marks);

    groupsInorderTraversal(root->right);
}

void inorderTraversalAssignment(Assignments *node)
{
    if (node == NULL)
    {
        return;
    }

    inorderTraversalAssignment(node->left);

    printf("Assignment ID: %d\n", node->data.assignment_id);
    printf("Topic: %s\n", node->data.topic_name);
    printf("Status: %s\n", node->data.status);

    Groups *current = node->groupHead;
    groupsInorderTraversal(current);

    inorderTraversalAssignment(node->right);
}

void ques1()
{
    Student_record *new_student = (Student_record *)malloc(sizeof(Student_record));
    printf("Enter student ID: ");
    scanf("%d", &new_student->student_id);
    printf("Enter student name: ");
    scanf("%s", new_student->name);
    printf("Enter group partner id: ");
    scanf("%d", &new_student->group_partner_id);
    printf("Enter group ID: ");
    scanf("%d", &new_student->group_id);
    printf("Enter assignment id: ");
    scanf("%d", &new_student->assignment_id);
    printf("Enter assignment name: ");
    scanf("%s", new_student->assignment_name);
    printf("Enter deadline: ");
    scanf("%s", new_student->deadline);
    printf("Enter status of assignment (submitted/not submitted/evaluated): ");
    scanf("%s", new_student->status_of_assignment);
    printf("Enter offline evaluation marks: ");
    scanf("%f", &new_student->offline_evaluation_marks);
    printf("Enter viva marks: ");
    scanf("%f", &new_student->viva_marks);
    FILE *fp = fopen("students.txt", "a+");
    if (fp == NULL)
    {
        printf("\nFile not found for updating!!!");
    }
    else
    {
        fprintf(fp, "\n%d %s %d %d %s %d %s %s %f %f", new_student->student_id, new_student->name, new_student->group_partner_id, new_student->group_id, new_student->assignment_name, new_student->assignment_id, new_student->deadline, new_student->status_of_assignment, new_student->offline_evaluation_marks, new_student->viva_marks);
    }
    fclose(fp);
    printf("\n.......Updated in text file also...");
    studentDataBase = insertStudentRecord(studentDataBase, *new_student);
    Assignment *newAssignment = (Assignment *)malloc(sizeof(Assignment));
    newAssignment->assignment_id = new_student->assignment_id;
    strcpy(newAssignment->topic_name, new_student->assignment_name);
    strcpy(newAssignment->status, new_student->status_of_assignment);
    assignmentDataBase = changeAssignmentRecord(assignmentDataBase, *newAssignment, *new_student);
}

Groups *insert_group_in_groupHead(Groups *node, Groups *curr)
{
    if (node == NULL)
    {
        node = curr;
        return node;
    }
    if (curr->data.group_id < node->data.group_id)
    {
        node->left = insert_group_in_groupHead(node->left, curr);
    }
    else if (curr->data.group_id > node->data.group_id)
    {
        node->right = insert_group_in_groupHead(node->right, curr);
    }
    else
    {
        // student with the same id already exists
        return node;
    }
    node->height = 1 + max(heightG(node->left), heightG(node->right));
    int balance = getBalanceG(node);
    if (balance > 1 && curr->data.group_id < node->left->data.group_id)
    {
        node = rightRotateG(node);
    }
    else if (balance < -1 && curr->data.group_id > node->right->data.group_id)
    {
        node = leftRotateG(node);
    }
    else if (balance > 1 && curr->data.group_id > node->left->data.group_id)
    {
        node->left = leftRotateG(node->left);
        node = rightRotateG(node);
    }
    else if (balance < -1 && curr->data.group_id < node->right->data.group_id)
    {
        node->right = rightRotateG(node->right);
        node = leftRotateG(node);
    }
    return node;
}

// void ques2()
// {
//     Assignment *new_assignment = (Assignment *)malloc(sizeof(Assignment));
//     printf("Enter assignment id :");
//     scanf("%d", &new_assignment->assignment_id);
//     printf("Enter topic name :");
//     scanf("%s", new_assignment->topic_name);
//     printf("Enter the status of the assignment(declared/due-date-over/evaluated)");
//     scanf("%s", new_assignment->status);
//     Assignments* curr=search_assignments_using_assignment_id(assignmentDataBase,new_assignment->assignment_id);
//     assignmentDataBase = insertAssignmentRecord(assignmentDataBase, *new_assignment);
//     if(curr==NULL)
//     {
//         int numGroups;
//         printf("Enter the number of student groups to be assigned to this assignment: ");
//         scanf("%d",&numGroups);
//         FILE *fp2=fopen("assignments.txt","w");
//         fprintf(fp2,"\n%d %s %s %d",new_assignment->assignment_id,new_assignment->topic_name,new_assignment->status,numGroups);
//         for(int i=0;i<numGroups;i++)
//         {
//             // Student_record *new_student = (Student_record *)malloc(sizeof(Student_record));
//             // printf("Enter student ID: ");
//             // scanf("%d", &new_student->student_id);
//             // printf("Enter student name: ");
//             // scanf("%s", new_student->name);
//             // printf("Enter group partner id: ");
//             // scanf("%d", &new_student->group_partner_id);
//             // printf("Enter group ID: ");
//             // scanf("%d", &new_student->group_id);
//             // // printf("Enter assignment id: ");
//             // // scanf("%d", &new_student->assignment_id);
//             // new_student->assignment_id=new_assignment->assignment_id;
//             // // printf("Enter assignment name: ");
//             // // scanf("%s", new_student->assignment_name);
//             // strcpy(new_student->assignment_name,new_assignment->topic_name);
//             // printf("Enter deadline: ");
//             // scanf("%s", new_student->deadline);
//             // printf("Enter status of assignment (submitted/not submitted/evaluated): ");
//             // scanf("%s", new_student->status_of_assignment);
//             // printf("Enter offline evaluation marks: ");
//             // scanf("%f", &new_student->offline_evaluation_marks);
//             // printf("Enter viva marks: ");
//             // scanf("%f", &new_student->viva_marks);
//             Assignments *tm = (Assignments *)malloc(sizeof(Assignments));
//             Students *tmp = (Students *)malloc(sizeof(Students));
//             tmp->left = tmp->right = NULL;
//             tm->left = tm->right = NULL;
//             printf("Enter student ID: ");
//             scanf("%d", &tmp->data.student_id);
//             printf("Enter student name: ");
//             scanf("%s", tmp->data.name);
//             printf("Enter group partner id: ");
//             scanf("%d", &tmp->data.group_partner_id);
//             printf("Enter group ID: ");
//             scanf("%d", &tmp->data.group_id);
//             tmp->data.assignment_id=new_assignment->assignment_id;
//             strcpy(tmp->data.assignment_name,new_assignment->topic_name);
//             printf("Enter deadline: ");
//             scanf("%s", tmp->data.deadline);
//             printf("Enter status of assignment (submitted/not submitted/evaluated): ");
//             scanf("%s", tmp->data.status_of_assignment);
//             printf("Enter offline evaluation marks: ");
//             scanf("%f", &tmp->data.offline_evaluation_marks);
//             printf("Enter viva marks: ");
//             scanf("%f", &tmp->data.viva_marks);
//             printf("--------------------------------------------\n");
//             studentDataBase = insert_student_in_student_dataBase(tmp, sr_root);
//             temp->submission_root = InsertTree_inside_ar(tm, temp->submission_root);
//             FILE *fp = fopen("students.txt", "a+");
//             if (fp == NULL)
//             {
//                 printf("\nFile not found for updating!!!");
//             }
//             else
//             {
//                 fprintf(fp, "\n%d %s %d %d %s %d %s %s %f %f", new_student->student_id, new_student->name, new_student->group_partner_id, new_student->group_id, new_student->assignment_name, new_student->assignment_id, new_student->deadline, new_student->status_of_assignment, new_student->offline_evaluation_marks, new_student->viva_marks);
//             }
//             fclose(fp);

//         }
//     }
// }

Students *insert_student_in_student_dataBase(Students *node, Students *curr)
{
    if (node == NULL)
    {
        node = curr;
        //return node;
    }
    else if (curr->data.student_id < node->data.student_id)
    {
        node->left = insert_student_in_student_dataBase(node->left, curr);
    }
    else if (curr->data.student_id > node->data.student_id)
    {
        node->right = insert_student_in_student_dataBase(node->right, curr);
    }
    else
    {
        // student with the same id already exists
        //return node;
    }
    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);
    if (balance > 1 && curr->data.student_id < node->left->data.student_id)
    {
        node = rightRotate(node);
    }
    else if (balance < -1 && curr->data.student_id > node->right->data.student_id)
    {
        node = leftRotate(node);
    }
    else if (balance > 1 && curr->data.student_id > node->left->data.student_id)
    {
        node->left = leftRotate(node->left);
        node = rightRotate(node);
    }
    else if (balance < -1 && curr->data.student_id < node->right->data.student_id)
    {
        node->right = rightRotate(node->right);
        node = leftRotate(node);
    }
    return node;
}

void ques2()
{
    Assignment *new_assignment = (Assignment *)malloc(sizeof(Assignment));
    printf("Enter assignment id :");
    scanf("%d", &new_assignment->assignment_id);
    printf("Enter topic name :");
    scanf("%s", new_assignment->topic_name);
    printf("Enter the status of the assignment(declared/due-date-over/evaluated)");
    scanf("%s", new_assignment->status);
    Assignments* curr=search_assignments_using_assignment_id(assignmentDataBase,new_assignment->assignment_id);
    if(curr==NULL)
    assignmentDataBase = insertAssignmentRecord(assignmentDataBase, *new_assignment);
    Assignments* assignment=(Assignments*)malloc(sizeof(Assignments));
    assignment->data=*new_assignment;
    assignment->left=assignment->right=NULL;
    assignment->groupHead=NULL;
    int numGroups;
    printf("Enter number of groups in the given assignment: ");
    scanf("%d",&numGroups);
    FILE *fp2=fopen("assignments.txt","a+");
    fprintf(fp2,"\n%d %s %s %d",new_assignment->assignment_id,new_assignment->topic_name,new_assignment->status,numGroups);
    fclose(fp2);
    for(int i=0;i<numGroups;i++)
    {
        Student_record *new_student = (Student_record *)malloc(sizeof(Student_record));
            printf("Enter student ID: ");
            scanf("%d", &new_student->student_id);
            printf("Enter student name: ");
            scanf("%s", new_student->name);
            printf("Enter group partner id: ");
            scanf("%d", &new_student->group_partner_id);
            printf("Enter group ID: ");
            scanf("%d", &new_student->group_id);
            // printf("Enter assignment id: ");
            // scanf("%d", &new_student->assignment_id);
            new_student->assignment_id=new_assignment->assignment_id;
            // printf("Enter assignment name: ");
            // scanf("%s", new_student->assignment_name);
            strcpy(new_student->assignment_name,new_assignment->topic_name);
            printf("Enter deadline: ");
            scanf("%s", new_student->deadline);
            printf("Enter status of assignment (submitted/not submitted/evaluated): ");
            scanf("%s", new_student->status_of_assignment);
            printf("Enter offline evaluation marks: ");
            scanf("%f", &new_student->offline_evaluation_marks);
            printf("Enter viva marks: ");
            scanf("%f", &new_student->viva_marks);
            Students* curr=search_student_using_student_id(studentDataBase,new_student->student_id);
            Students* student=(Students*)malloc(sizeof(Students));
            student->data=*new_student;
            student->left=student->right=NULL;
            student->height=1;
            if(curr==NULL)
            {
                studentDataBase=insert_student_in_student_dataBase(studentDataBase,student);

            }
            Groups* group=NULL;
            FILE *fp = fopen("students.txt", "a+");
            if (fp == NULL)
            {
                printf("\nFile not found for updating!!!");
            }
            else
            {
                fprintf(fp, "\n%d %s %d %d %s %d %s %s %f %f", new_student->student_id, new_student->name, new_student->group_partner_id, new_student->group_id, new_student->assignment_name, new_student->assignment_id, new_student->deadline, new_student->status_of_assignment, new_student->offline_evaluation_marks, new_student->viva_marks);
            }
            fclose(fp);
    }
    
}

Assignments *insert_assignment_in_assignment_dataBase(Assignments *node, Assignments *curr)
{
    if (node == NULL)
    {
        node = curr;
        return node;
    }
    else if (curr->data.assignment_id < node->data.assignment_id)
    {
        node->left = insert_assignment_in_assignment_dataBase(node->left, curr);
    }
    else if (curr->data.assignment_id > node->data.assignment_id)
    {
        node->right = insert_assignment_in_assignment_dataBase(node->right, curr);
    }
    else
    {
        return node;
    }
    node->height = 1 + max(heightA(node->left), heightA(node->right));
    int balance = getBalanceA(node);
    if (balance > 1 && curr->data.assignment_id < node->left->data.assignment_id)
    {
        node = rightRotateA(node);
    }
    else if (balance < -1 && curr->data.assignment_id > node->right->data.assignment_id)
    {
        node = leftRotateA(node);
    }
    else if (balance > 1 && curr->data.assignment_id > node->left->data.assignment_id)
    {
        node->left = leftRotateA(node->left);
        node = rightRotateA(node);
    }
    else if (balance < -1 && curr->data.assignment_id < node->right->data.assignment_id)
    {
        node->right = rightRotateA(node->right);
        node = leftRotateA(node);
    }
    return node;
}



void function()
{

    FILE *fp1, *fp2;
    char line[200];
    fp1 = fopen("students.txt", "r");
    if (fp1 == NULL)
    {
        printf("Error opening students file.");
        exit(1);
    }

    while (fgets(line, sizeof(line), fp1) != NULL)
    {
        Student_record *student = (Student_record *)malloc(sizeof(Student_record));
        sscanf(line, "%d %s %d %d %s %d %s %s %f %f",
               &student->student_id, student->name, &student->group_partner_id,
               &student->group_id, student->assignment_name, &student->assignment_id, student->deadline,
               student->status_of_assignment, &student->offline_evaluation_marks, &student->viva_marks);
        Students *curr = (Students *)malloc(sizeof(Students));
        curr->data = *student;
        curr->height = 1;
        curr->left = curr->right = NULL;
        studentDataBase = insert_student_in_student_dataBase(studentDataBase, curr);
    }
    fclose(fp1);
    inorderTraversal(studentDataBase);

    fp2 = fopen("assignments.txt", "r");
    if (fp2 == NULL)
    {
        printf("Error opening assignments file.");
    }

    while (fgets(line, sizeof(line), fp2) != NULL)
    {
        Assignment *assignment = (Assignment *)malloc(sizeof(Assignment));
        int numGroups;
        sscanf(line, "%d %s %s %d", &assignment->assignment_id, assignment->topic_name, assignment->status, &numGroups);
        Assignments *curr = (Assignments *)malloc(sizeof(Assignments));
        curr->data = *assignment;
        curr->groupHead = NULL;
        curr->height = 1;
        curr->left = NULL;
        curr->right = NULL;
        for (int k = 0; k < numGroups; k++)
        {
            Assignment_record *group = (Assignment_record *)malloc(sizeof(Assignment_record));
            fgets(line, sizeof(line), fp2);
            sscanf(line, "%d %s %f %f", &group->group_id, group->status, &group->offline_marks, &group->viva_marks);
            Groups *currg = (Groups*)malloc(sizeof(Groups));
            currg->data = *group;
            currg->height = 1;
            currg->left = currg->right = NULL;
            curr->groupHead = insert_group_in_groupHead(curr->groupHead, currg);
        }
        assignmentDataBase = insert_assignment_in_assignment_dataBase(assignmentDataBase, curr);
    }
    fclose(fp2);
    //inorderTraversalAssignment(assignmentDataBase);

    int choice;
    do
    {
        int a_id, g_id;
        char date[10];
        int a1_id,a2_id;
        printf("\n1. Insert student record\n2. Insert assignment record\n3. Submit assignment\n4. Evaluate assignment\n5. Print declared assignments\n6. Print missing submissions \n7. Print pending evaluations\n8. Print assignment results\n9. Print top performers\n10. Range Search\n11. Print student list\n12. Print Assignment List\n0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            ques1();
            break;
        case 2:
            ques2();
            break;
        case 3:

            printf("Enter the assignment id and group id: ");
            scanf("%d %d", &a_id, &g_id);
            submit_assignment(a_id, g_id);
            break;
        case 4:

            printf("Enter the assignment id: ");
            scanf("%d", &a_id);
            assignment_submit(a_id);
            break;
        case 5:
            assignments_declared_but_not_evaluated(assignmentDataBase);
            break;
        case 6:
            printf("Enter today's date: ");
            scanf("%s", date);
            groups_not_submitted_assignments(date);
            break;
        case 7:
            // printf("Enter the assignment id: ");
            // scanf("%d", &a_id);
            printPendingAssignments(assignmentDataBase);
            break;
        case 8:
            printf("Enter the assignment id: ");
            scanf("%d", &a_id);
            printStudentGroupsDetails(a_id);
            break;
        case 9:
            students_groups_with_highest_marks(assignmentDataBase);
            break;
        case 10:
            printf("\nEnter the two assignment ids: ");
            scanf("%d %d",&a1_id,&a2_id);
            range_search(a1_id,a2_id);
            break;    
        case 11:
            inorderTraversal(studentDataBase);
            break;
        case 12:
            inorderTraversalAssignment(assignmentDataBase);
            break;
        case 0:
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
            break;
        }
    } while (choice != 0);
}

int main()
{
    int option, i = 0;
    char name[50];
    char password[50];
    printf("Login as :\n1. Student \n2. Teacher\nEnter your choice :");
    scanf("%d", &option);
    printf("\nYou have choosen %d\n", option);
    switch (option)
    {
    case 1:
        printf("---------------------Student's Portal ---------------------------------\n");
        printf("Enter your name :");
        scanf("%s", name);
        while (name[i])
        {
            name[i] = tolower(name[i]);
            i++;
        }
        printf("\nEnter your password (all in lowercase):");
        scanf("%s", password);
        if (strcmp(password, name) == 0)
        {
            printf("Login Successful!!\n");
            function();
        }
        else
        {
            printf("Incorrect password!!\n");
            break;
        }

        break;
    case 2:
        printf("---------------------Teacher's Portal ---------------------------------\n");
        printf("Enter your name :");
        scanf("%s", name);
        while (name[i])
        {
            name[i] = tolower(name[i]);
            i++;
        }
        printf("\nEnter your password (all in lowercase):");
        scanf("%s", password);
        if (strcmp(password, name) == 0)
        {
            printf("\nLogin Successful!!");
        }
        else
        {
            printf("\nIncorrect password!!");
            break;
        }
        function();

    default:
        printf("\nEntered choice is invalid!!");
        break;
    }

    return 0;
}
