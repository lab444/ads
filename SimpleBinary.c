
#include<stdio.h>
#include<stdlib.h> 

struct Node{
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node* buildtree(int data){

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
   
    return newNode;
}

struct Node* insert(struct Node *root , int data){

    if(root == NULL){
        return buildtree(data);
    }

    if(data < root->data){
        root->left = insert(root->left ,data);
    }
    else if(data > root->data){
        root->right = insert(root->right ,data);
    }
    return root;
}


struct Node* inodersucc(struct Node* root){
    
    while(root->left != NULL){
        root = root->left;
    }
    return root;
}
struct Node* deleteNode(struct Node* root, int k)
{
    if (root == NULL){
        return root;
    }

    if (root->data > k) {
        root->left = deleteNode(root->left, k);
    }
    else if (root->data < k) {
        root->right = deleteNode(root->right, k);
    }
 else{
    if(root->left == NULL && root->right == NULL){
        return NULL;
    }
    if (root->left == NULL) {
       return root->right;
    }
    else if (root->right == NULL) {
        return root->left;
    }
    else{
        struct Node* inordersuccnode = inodersucc(root->right);
        root->data = inordersuccnode->data;
        root->right = deleteNode(root->right,inordersuccnode->data);
    }
 }
 return root;
}

void preorder(struct Node *root){
    if(root == NULL){
        return;
    }
    printf("%d " , root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(struct Node *root){
    if(root == NULL){
        return;
    }
    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}

void postorder(struct Node *root){
    if(root == NULL){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%d ",root->data);
}

int flag = 0;

void search(struct Node *root,int key){
 
    if(root == NULL){
        return;
    }
    if(root->data == key){
        flag = 1;
       printf("Found");
       return;
    }
    search(root->left,key);
    search(root->right,key);
}

int main(){

    struct Node* root = NULL;

    int entrycode ;
    int data;
    int key;
    int ele;


    printf("1 ==> create_Node ,  2 ==> insert_Node  , 3 ==> Delete_node\n");
    printf("4 ==> Preorder_travesal   , 5 ==> Inorder_Travsal   , 6 ==> Postorder\n");
    printf("7 ==>>  search_Node \n");
    
    printf("continue or not(1/0) : ");
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
                root = buildtree(data);
                break;
            case 2:
                printf("\nenter data : ");
                scanf("%d",&data);
                insert(root,data);
                break;
            case 3:
                printf("\nenter element : ");
                scanf("%d",&ele);
                deleteNode(root,ele);
                break;
            case 4:
                printf("\nPreorder Travesal : ");
                preorder(root);
                printf("\n");
                break;
            case 5:
                printf("\nInorder Travesal : ");
                inorder(root);
                printf("\n");
                break;
            case 6:
                printf("\nPostorder Travesal : ");
                postorder(root);
                printf("\n");
                break;
            case 7:
                flag = 0;
                printf("\nsearch -  enter Key : ");
                scanf("%d",&key);
                search(root,key);
                if(flag == 0){
                    printf("\nNot found");
                }
                printf("\n");
                break;
            default :
                printf("\nenter valid Inputs");
                break;
        }
        printf("\ncontinue or not(1/0) : ");
        scanf("%d",&entrycode);
    }while(entrycode != 0);
}
