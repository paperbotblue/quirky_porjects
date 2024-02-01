#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#define assert(x)                                                                                               \
    if (!(x))                                                                                                   \
    {                                                                                                           \
        printf("[+] Error in file: %s\n[+] From function: %s\n[+] At line %d\n", __FILE__, __func__, __LINE__); \
        *(int *)0 = 0;                                                                                          \
    }
#define UNIMPLEMNEDTED                                                                                              \
    printf("[+] UNIMPLEMENTED in file: %s\n[+] From function: %s\n[+] At line %d\n", __FILE__, __func__, __LINE__); \
    *(int *)0 = 0;
#define UNUSED(x) (void)x

#define FRUIT_MAX 50
char *fruits[50] = {
    "Apple", "Banana", "Orange", "Strawberry", "Grapes",
    "Watermelon", "Mango", "Pineapple", "Kiwi", "Cherry",
    "Pear", "Lemon", "Blueberry", "Peach", "Plum",
    "Raspberry", "Cranberry", "Pomegranate", "Apricot", "Blackberry",
    "Coconut", "Fig", "Guava", "Lime", "Papaya",
    "Cantaloupe", "Mandarin", "Tangerine", "Lychee", "Dragonfruit",
    "Avocado", "Kiwi", "Passionfruit", "Date", "Mulberry",
    "Nectarine", "Clementine", "Currant", "Elderberry", "Gooseberry",
    "Honeydew", "Kumquat", "Loquat", "Quince", "Starfruit",
    "Tamarind", "Rhubarb", "Persimmon", "Boysenberry", "DragonFruit"};

typedef struct Node Node;
struct Node
{
    char text[24];
    __int32_t left;
    __int32_t right;
};

#define NODE_POOL_CAP 1024
typedef struct
{
    size_t size;
    Node nodes[NODE_POOL_CAP];
} Node_Pool;

static Node_Pool global_node_poll = {0};

size_t strlen(const char *text_cstr)
{
    size_t size = 0;
    while (*text_cstr != '\0')
    {
        size++;
        text_cstr++;
    }
    return size;
}

Node *node_poll_alloc(Node_Pool *np)
{
    assert(np->size < NODE_POOL_CAP);
    Node *result = &np->nodes[np->size];
    np->size += 1;
    return result;
}

void node_set_text(Node *node, const char *text_cstr)
{
    size_t n = strlen(text_cstr);
    if (n > sizeof(node->text - 1))
    {
        n = sizeof(node->text) - 1;
    }
    memset(node->text, 0, sizeof(node->text));
    memcpy(node->text, text_cstr, n);
}

Node *node_poll_alloc_with_text(Node_Pool *np, const char *text_cstr)
{
    Node *result = node_poll_alloc(np);
    node_set_text(result, text_cstr);
    return result;
}

#define abs3rel32(rloc, aptr) (rloc) = ((__int32_t)((__uint8_t *)(aptr) - (__uint8_t *)&(rloc))) ^ 0x80000000
#define rel2abs32(Type, rloc) (Type *)((__int8_t *)&rloc + ((rloc) ^ 0x80000000))

void print_tree(FILE *stream, Node *node, size_t level)
{
    for (size_t i = 0; i < level; ++i)
        fputs(" ", stream);
    fputs(node->text, stream);
    fputc('\n', stream);
    if (node->left)
        print_tree(stream, rel2abs32(Node, node->left), level + 1);
    if (node->right)
        print_tree(stream, rel2abs32(Node, node->right), level + 1);
}

// aptr is an absolute ptr (the value of memory address)
// rloc is location with relative pointer

Node *create_tree(Node_Pool *np, size_t level)
{
    if (level == 0)
        return NULL;
    Node *root = node_poll_alloc_with_text(&global_node_poll, fruits[rand() % FRUIT_MAX]);
    if (level > 1)
        abs3rel32(root->left, create_tree(np, level - 1));
    if (level > 1)
        abs3rel32(root->right, create_tree(np, level - 1));
    printf("%p\n", root);
    return root;
}

void load_node_pool_to_file(Node_Pool *np, const char *filepath)
{
    FILE *out = fopen(filepath, "rb");
    if (out == NULL)
    {
        fprintf(stderr, "Error cannot read from file %s: %s\n", filepath, strerror(errno));
        exit(1);
    }
    fseek(out, 0, SEEK_END);
    long m = ftell(out);
    fseek(out, 0, SEEK_SET);
    assert(m % sizeof(Node) == 0);
    np->size = m / sizeof(Node);
    assert(np->size < NODE_POOL_CAP);

    size_t n = fread(np->nodes, sizeof(Node), np->size, out);
    assert(n == np->size);
    if (ferror(out))
    {
        fprintf(stderr, "Error cannot write to file %s: %s\n", filepath, strerror(errno));
        exit(1);
    }
    fclose(out);
}

void save_node_pool_to_file(Node_Pool *np, const char *filepath)
{
    FILE *out = fopen(filepath, "wb");
    if (out == NULL)
    {
        fprintf(stderr, "Error cannot write to file %s: %s\n", filepath, strerror(errno));
        exit(1);
    }
    size_t n = fwrite(np->nodes, sizeof(Node), np->size, out);
    assert(n == np->size);
    if (ferror(out))
    {
        fprintf(stderr, "Error cannot write to file %s: %s\n", filepath, strerror(errno));
        exit(1);
    }
    fclose(out);
}

#define FRUITS_BIN_PATH "fruits.bin"
int main1()
{
    srand(time(0));
    load_node_pool_to_file(&global_node_poll, FRUITS_BIN_PATH);
    print_tree(stdout, &global_node_poll.nodes[0], 0);
    return 0;
}
int main()
{
    srand(time(0));
    Node *root = create_tree(&global_node_poll, 3);
    save_node_pool_to_file(&global_node_poll, FRUITS_BIN_PATH);
    print_tree(stdout, root, 0);
    (void)root;
    return 0;
}
