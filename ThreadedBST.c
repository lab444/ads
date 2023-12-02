#include<stdio.h>
#include<stdlib.h>


struct Node{
    int data;
    int lbit;
    int rbit;
    struct Node *left ,*right;
};


struct Node* create(int data){

    struct Node* newnode =(struct Node*)malloc(sizeof(struct Node));
    newnode->data = data;
    newnode->lbit = newnode->rbit =0;
    newnode->left = newnode->right = NULL;

    return newnode;
}


struct Node* insert(struct Node* root,int data){

    struct Node* newnode=create(data);

    if(root == NULL){

        struct Node* head = create(999);
        head->right = head;
        root = newnode;
        root->left = root->right = head;
        head->left = root;
        head->lbit = head->rbit = 1;

        return head;
    }
    else{

        if(newnode->data < root->data){
            if(root->lbit != 1){
                newnode->left = root->left;
                newnode->right = root;
                root->left = newnode;
                root->lbit =1;
            }
            else{
              root->left = insert(root->left,data);
            }
        }
        else if(newnode->data > root->data){
            if(root->rbit != 1){
                newnode->left = root;
                newnode->right = root->right;
                root->right = newnode;
                root->rbit = 1;
            }
            else{
              root->right = insert(root->right,data);
            }
        }
    }
    return root;
}


struct Node* inordersucc(struct Node* root){

    if(root->rbit == 0){
        return root->right;
    }
    root = root->right;
    while(root->lbit !=0){
        root = root->left;
    }
    return root;
}


void inorder(struct Node* root){

    if(root == NULL){
        return;
    }

    struct Node* temp = root->left;

    while(temp->lbit!=0){
        temp = temp->left;
    }

    while(temp!=root){

        printf("%d ",temp->data);

        temp = inordersucc(temp);
    }
}


void preorder(struct Node* head){

    struct Node* temp = head->left;

    while(temp!=head){

        printf("%d ",temp->data);

        if(temp->lbit == 1){
            temp = temp->left;
        }
        else if(temp->rbit == 1){
            temp = temp->right;
        }
        else if(temp->rbit == 0){
            while(temp->rbit == 0){
                temp = temp->right;
            }
            temp = temp->right;
        }
    }
}


struct Node* search(struct Node* head ,struct Node* root,int data){

    struct Node* temp = root;

    struct Node* par = root;

    while(temp!=head){

    if(temp->data == data){
        return par;
    }
    else if(temp->data > data){
        par = temp;
        temp = temp->left;
    }
    else if(temp->data < data){
        par = temp;
        temp = temp->right;
    }
    }
    return NULL;
}


struct Node* delete(struct Node* head, struct Node* root, int data) {
    if (root == NULL) {
        return NULL;
    }

    struct Node* parent = search(head, root, data);

    if (parent == NULL) {

        return root;
    }


    struct Node* del = (parent->data < data) ? parent->right : parent->left;

    if (del->lbit == 0 && del->rbit == 0) {

        if (parent->left == del) {
            parent->lbit = 0;
            parent->left = del->left;
        } else {
            parent->rbit = 0;
            parent->right = del->right;
        }
        free(del);

    }
    else if (del->lbit == 0 || del->rbit == 0) {

        struct Node* child = (del->lbit == 0) ? del->right : del->left;

        if (parent->left == del) {
            parent->left = child;
        } else {
            parent->right = child;
        }


        struct Node* successor = inordersucc(del);


        if (successor->left == del) {
            successor->left = child;
        }


        if (successor->right == del) {
            successor->right = child;
        }


        free(del);
    } else {

        struct Node* inorders = inordersucc(del);
        int inordersucc_data = inorders->data;


        root = delete(head, root, inordersucc_data);


        del->data = inordersucc_data;
    }

    return root;
}




void main(){

     struct Node* root = NULL;


    int entrycode;
    int data;
    int deldata;

    printf("1 ==>  insertnode in threded BST\n");
    printf("2 ==>  deletenode in threded BST\n");
    printf("3 ==>  preorder travasal in threded BST\n");

    printf("\ncontinue or not(1/0) : ");
    scanf("%d",&entrycode);

        do{
            if(entrycode == 0){
                exit(0);
            }

            printf("\nenter option : ");
            int option;
            scanf("%d",&option);


        switch(option){
            case 1:
                printf("\nenter data : ");
                scanf("%d",&data);
                root = insert(root,data);
                break;
            case 2:
                printf("\nenter data for delete : ");
                scanf("%d",&deldata);
                delete(root,root->left,deldata);
                break;
            case 3:
                printf("\npreorder Travasal :  ");
                preorder(root);
                break;
        }
        printf("\ncontinue or not(1/0) : ");
        scanf("%d",&entrycode);
    }while(entrycode != 0);

    // int arr[11] = {56,43,24,46,30,45,48,78,96,85,100};

    //  for(int i =0;i<11;i++){
    //   root =  insert(root,arr[i]);
    // }

    // inorder(root);

    // delete(root,root->left,100);
    // printf("\n");

    // inorder(root);
}
