#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* root;

struct Node* CreateTree(struct Node* root, int data) {
    if (root == NULL) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Ошибка выделения памяти");
            exit(0);
        }
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if (data == root->data) {
        // Элемент уже существует, не добавляем дубликат
        printf("Элемент %d уже существует в дереве, добавление отменено\n", data);
        return root;
    }

    if (data < root->data) {
        root->left = CreateTree(root->left, data);
    }
    else {
        root->right = CreateTree(root->right, data);
    }

    return root;
}

void print_tree(struct Node* r, int l) {
    if (r == NULL) {
        return;
    }

    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++) {
        printf("   ");
    }

    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}

struct Node* SearchTree(struct Node* r, int data) {
    if (r == NULL || r->data == data) {
        return r;
    }

    if (data < r->data) {
        return SearchTree(r->left, data);
    }
    else {
        return SearchTree(r->right, data);
    }
}

int Countvh(struct Node* r, int data) {
    if (r == NULL) {
        return 0;
    }

    int count = (r->data == data) ? 1 : 0;

    count += Countvh(r->left, data);
    count += Countvh(r->right, data);

    return count;
}


int findDepth(struct Node* r, int data, int depth) {
    if (r == NULL) {
        return -1;
    }

    if (r->data == data) {
        return depth;
    }

    if (data < r->data) {
        return findDepth(r->left, data, depth + 1);
    }
    else {
        return findDepth(r->right, data, depth + 1);
    }
}

int main() {
    setlocale(LC_ALL, "");
    int D, start = 1;
    int search_value;

    root = NULL;
    printf("-1 - окончание построения дерева\n");
    while (start) {
        printf("Введите число: ");
        scanf("%d", &D);
        if (D == -1) {
            printf("Построение дерева окончено\n\n");
            start = 0;
        }
        else {
            root = CreateTree(root, D);
        }
    }

    printf("\nДерево:\n");
    print_tree(root, 0);

    printf("\nПоиск элемента\n");
    printf("Введите число для поиска: ");
    scanf("%d", &search_value);

    struct Node* result = SearchTree(root, search_value);
    if (result != NULL) {
        printf("Значение %d найдено в дереве.\n", result->data);


        int depth = findDepth(root, search_value, 0);
        if (depth != -1) {
            printf("Глубина элемента: %d\n", depth);
        }
    }
    else {
        printf("Значение %d не найдено в дереве.\n", search_value);
    }

    printf("\nПодсчёт вхождений\n");
    printf("Введите число для подсчёта вхождений: ");
    scanf("%d", &search_value);

    int occ = Countvh(root, search_value);
    printf("Количество вхождений значения %d в дереве: %d\n", search_value, occ);

    return 0;
}