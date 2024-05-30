// 연락처 프로그램  
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>

#define MAX_NAME_SIZE 100
#define MAX_PHONENUMBER_SIZE 100



// 데이터 형식
typedef struct {
    char name[MAX_NAME_SIZE];   //키필드
    char phone_number[MAX_PHONENUMBER_SIZE];
} element;

// 노드의 구조
typedef struct TreeNode {
    element key;
    struct TreeNode *left, *right;
} TreeNode;

// 만약 e1 < e2 이면 -1 반환
// 만약 e1 == e2 이면 0 반환
// 만약 e1 > e2 이면 1 반환
int compare(element e1, element e2)
{
    return strcmp(e1.name, e2.name);
}

// 이진 탐색 트리 출력 함수
void display(TreeNode *p)
{


    if (p != NULL) {
        printf("(");
        display(p->left);
        printf("%s:%s", p->key.name, p->key.phone_number);
        display(p->right);
        printf(")");
    }
}

// 이진 탐색 트리 탐색 함수
TreeNode *search(TreeNode *root, element key)
{
    TreeNode *p = root;
    while (p != NULL) {
        if (compare(key, p->key) == 0)
            return p;
        else if (compare(key, p->key) < 0)
            p = p->left;
        else if (compare(key, p->key) > 0)
            p = p->right;
    }
    return p;   //탐색에 실패했을 경우 NULL 반환
}

TreeNode *new_node(element item)
{
    TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

TreeNode *insert_node(TreeNode *node, element key)
{
    // 트리가 공백이면 새로운 노드를 반환한다.
    if (node == NULL) return new_node(key);

    // 그렇지 않으면 순환적으로 트리를 내려간다.
    if (compare(key, node->key) < 0)
        node->left = insert_node(node->left, key);
    else if (compare(key, node->key) > 0)
        node->right = insert_node(node->right, key);
    // 동일 이름이면 전화번호를 덮어 씌운다
    else if (compare(key, node->key) == 0)
        strcpy(node->key.phone_number , key.phone_number); 
    //루트 포인터 반환 

    return node;
}
/*
TreeNode *min_value_node(TreeNode *node)
{
    TreeNode *current = node;
    // 맨 왼쪽 단말 노드를 찾으러 내려감
    while (current->left != NULL)
        current = current->left;
    return current;
}
*/

TreeNode *max_value_node(TreeNode *node)
{
    TreeNode *current = node;
    
    while (current->right != NULL)
        current = current->right;
    return current;
}


//이진 탐색 트리와 키가 주어지면 키가 저장된 노드를 삭제하고 새로운 루트 노드를 반환한다
TreeNode *delete_node(TreeNode *root, element key)
{
    if (root == NULL) return root;  // 최상위 노드가 NULL이면 아무 행동도 취할 필요가 없음
    //만약 키가 루트보다 작으면 왼쪽 서브트리에 있는 것임
    if (compare(key, root->key) < 0)
        root->left = delete_node(root->left, key);
    // 만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
    else if (compare(key, root->key) > 0)
        root->right = delete_node(root->right, key);
    // 키가 루트와 같으면 이 노드를 삭제하면 됨
    else {
        // 첫 번째나 두 번째 경우
        if (root->left == NULL) {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }
        // 세 번째 경우
        TreeNode *temp = max_value_node(root->right);

        // 중위 순회시 후계 노드를 복사한다.
        root->key = temp->key;
        // 중위 순회시 후계 노드를 삭제한다.
        root->right = delete_node(root->right, temp->key);
    }
    return root;
}

void help()
{
    printf("삽입(i), 탐색(s), 출력(p), 삭제(d), 종료(q): ");
}

int size(TreeNode *root)
{
    int cnt = 0;
    if (root != NULL)
    {
        cnt = 1 + size(root->left) + size(root->right);
    }
    return cnt;
}
// 이진 탐색 트리를 사용하는 전화번호부 프로그램
int main(void)
{
    char command;
    element e;
    TreeNode *root = NULL;
    TreeNode *tmp;



    do {
        help();
        command = getchar();
        getchar();
        
        switch (command) {
            case 'i':
                printf("이름: ");
                fgets(e.name, MAX_NAME_SIZE, stdin);
                e.name[strlen(e.name) - 1] = '\0';  // \n 개행문자 제거
                printf("전화번호: ");
                fgets(e.phone_number, MAX_PHONENUMBER_SIZE, stdin);
                e.phone_number[strlen(e.phone_number) - 1] = '\0';// \n 개행문자 제거
                root = insert_node(root, e);
                break;
            case 's':
                printf("이름: ");
                fgets(e.name, MAX_NAME_SIZE, stdin);
                e.name[strlen(e.name) - 1] = '\0';// \n 개행문자 제거
                tmp = search(root, e);
                if (tmp != NULL)
                    printf("%s의 전화번호:%s\n", e.name, tmp->key.phone_number);
                break;
            case 'p':
                printf("\n전체 노드 개수 : %d\n", size(root));
                display(root);
                printf("\n");
                break;
            case 'd':
                printf("이름: ");
                fgets(e.name, MAX_NAME_SIZE, stdin);
                e.name[strlen(e.name) - 1] = '\0';// \n 개행문자 제거
                root = delete_node(root, e);
                break;
        }
    } while (command != 'q');
    return 0; 
}
