
#include<stdio.h>
#include<stdlib.h>

// creating structure  to store treenode info
struct Node{
    int data;
    struct Node *left;
    struct Node *right;
};

// function to create Node
struct Node* buildtree(int data){

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

//function for insert node at left position
struct Node* insertLeft(struct Node* root,int data){
    if(root == NULL){
        return NULL;
    }
    root->left = buildtree(data);
    return root->left;
}

//function for insert node at right position
struct Node* insertRight(struct Node* root,int data){
    if(root == NULL){
        return NULL;
    }
    root->right = buildtree(data);
    return root->right;
}

// function for search
struct Node* search(struct Node* root, int data) {
  if (root == NULL) {
    return NULL;
  }

  if (data == root->data) {
    return root;
  }

  struct Node* foundNode = search(root->left, data);
  if (foundNode != NULL) {
    return foundNode;
  }

  return search(root->right, data);
}

// function for insertion
void insertBT(struct Node* root,int data , int parentnode ,int position){


    struct Node* currroot = search(root,parentnode);
    if(currroot == NULL){
        printf("Node not exit");
        return;
    }

    if(position == 1){
        insertLeft(currroot,data);
    }
    else if(position == 2){
        insertRight(currroot,data);
    }
}

// function for level order travasal
void levelorder(struct Node* root){

    if(root == NULL){
        return;
    }

    struct Node** queue = (struct Node**)malloc(sizeof(struct Node)*100);
    int front = -1;
    int rare = -1;

    queue[++rare] = root;
    queue[++rare] = NULL;
    front = 0;

    while(front <= rare){

        struct Node* curr = queue[front++];

        if(curr == NULL){
            printf("\n");
            if(front == rare+1){
                break;
            }else{
                queue[++rare] = NULL;
            }
        }else{
            printf("%d ",curr->data);
            if(curr->left!=NULL){
                queue[++rare] = curr->left;
            }
            if(curr->right!=NULL){
                queue[++rare] = curr->right;
            }
        }
    }
}

// function for height of Tree
int height(struct Node* root){

    if(root == NULL){
        return 0;
    }

    int lheight = height(root->left);
    int rheight = height(root->right);

    if(lheight > rheight){
        return lheight+1;
    }else{
        return rheight+1;
    }
}


//function for detecting mirror image
int isMirror_image(struct Node* leftnode , struct Node* rightnode){

    if(leftnode == NULL && rightnode == NULL){
        return 1;
    }
    if(leftnode == NULL || rightnode == NULL){
        return 0;
    }
    return leftnode->data == rightnode->data && isMirror_image(leftnode->left,rightnode->right) && isMirror_image(leftnode->right,rightnode->left);
}

//function for create mirror image
struct Node* mirror(struct Node* root){
    if(root == NULL){
        return NULL;
    }

    struct Node* newnode = buildtree(root->data);

    newnode->right = mirror(root->left);
    newnode->left = mirror(root->right);

    return newnode;
}

// function for leafnode print
void leafnode(struct Node* root){
    if(root == NULL){
        return;
    }
    if(root->left == NULL && root->right == NULL){
        printf("%d  ",root->data);
    }
    leafnode(root->left);
    leafnode(root->right);
}

// function for bst or not
int isBST(struct Node* root, struct Node* left, struct Node* right)
{

  if (root == NULL)
    return 1;

  if (left != NULL && root->data <= left->data)
    return 0;

  if (right != NULL && root->data >= right->data)
    return 0;

  return isBST(root->left, left, root) && isBST(root->right, root, right);
}

// driver function
int main(){

    struct Node* root = NULL;

    int entrycode ;
    int data;
    int key;
    int ele;
    int parentnode;
    int position;
    int flag;
    int bst;

    struct Node* mirrorimage;

    printf("1 ==> create_Node ,  2 ==> insert_Node , 3 ==> LevelOrder_travesal , 4 ==>> Height\n");
    printf("5 ==> Mirror_image_detection ,  6 ==> LeafNode , 7 ==>  Create_mirror_image, 8 ==>> Check for BST\n");
    printf("Leftposition ==>> 1        rightposition ==>> 2\n\n");


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
                root = buildtree(data);
                break;
            case 2:
                printf("\nenter data : ");
                scanf("%d",&data);
                printf("\nenter parentnode : ");
                scanf("%d",&parentnode);
                printf("\nenter position : ");
                scanf("%d",&position);
                insertBT(root,data,parentnode,position);
                break;
            case 3:
                printf("\nLevel Order travasal : \n");
                levelorder(root);
                break;
            case 4:
                printf("\n\nHeight of Tree : %d",height(root));
                printf("\n");
                break;
            case 5:
                if(isMirror_image(root->left,root->right) == 1){
                     printf("\nTree have mirror image\n");
                }else{
                    printf("\nTree have not mirror image\n");
                }
                break;
            case 6:
                printf("\nLeaf Nodes are :  ");
                leafnode(root);
                break;
            case 7:
                mirrorimage = mirror(root);
                printf("\nmirror image is done\n");
                levelorder(mirrorimage);
                break;
            case 8:
                bst = isBST(root,NULL,NULL);
                if(bst == 1){
                    printf("\nBinary Tree is BST\n");
                }else{
                    printf("\nBinary Tree is Not BST\n");
                }
                break;
            default :
                printf("\nenter valid Inputs");
                break;
        }
        printf("\ncontinue or not(1/0) : ");
        scanf("%d",&entrycode);
    }while(entrycode != 0);
}
