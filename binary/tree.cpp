#include "../helper-header.h"

struct Node
{
    int element;
    Node *left;
    Node *right;

    Node(int value)
    {
        element = value;
        left = nullptr;
        right = nullptr; //kad kai sukuriam, kad tie pointeriai nerodytu i garbage value
    }
};


class Tree
{
private:
    std::vector<int> traverse_vector;
public:
    Node *root = nullptr;
    void insert(int element);
    void remove(int element); //delete yra operator cpp tai kitoks name
    Node* search(int element); //returnina pointer tai visai nice
    //void delete_subtree(Node* node);
   // Node* search(Node* node, int element); //recursive search
    void in_order_traverse(Node* node);
    void pre_order_traverse(Node* node);
    void post_order_traverse();
    void print_vector();
   // ~Tree();
};

void Tree::insert(int element)
{
    if(root == nullptr)
    {
        root = new Node(element);
        std::cout << "Root element " << element << " added successfully." << std::endl;
        return;
    }

    Node* parent = nullptr;
    Node* current = root;

    while(current != nullptr)
    {
        parent = current;
        if(current->element == element)
        {
            std::cout << "Element is already in the tree" << std::endl;
            return;
        }
        else if(current->element > element)
            current = current->left;
        else
            current = current->right;
    }

    Node *newNode = new Node(element);

    if(element > parent->element)
        parent->right = newNode;
    else
        parent->left = newNode;
    
    std::cout << "Element " << element << " added successfully." << std::endl;
}

void Tree::remove(int element)
{
    if(search(element) == nullptr)
    {
        std::cout << "Element doesn't exist in the tree" << std::endl;
        return;
    }

    Node* parent = nullptr;
    Node* current = root;

    while(current != nullptr && current->element != element)
    {
        parent = current;
        if(current->element > element)
            current = current->left;
        else
            current = current->right;
    }

    //case 1
    if(current->left == nullptr && current->right == nullptr)
    {
        if(parent == nullptr && current == root)
        {
            delete current; 
            root = nullptr;
            std::cout << "Element " << element << " removed successfully." << std::endl;
            return;
        }
        if(parent->right == current)
        {
            parent->right = nullptr;
        }
        else if(parent->left == current)
        {
            parent->left = nullptr;
        }
        delete current;
        std::cout << "Element " << element << " removed successfully." << std::endl;
        return;
    }

    //case 2:
    if((current->left == nullptr && current->right != nullptr) || //check for if the node only has ONE child
    (current->left != nullptr && current->right == nullptr))
    {
        Node *child = (current->left != nullptr) ? current->left : current->right;

        if(current == root)
            root = child;
        else if(parent->left == current)
            parent->left = child;
        else
            parent->right = child;
        
        delete current;
        std::cout << "Element " << element << " removed successfully." << std::endl;
        return;
    }

    //case 3: two children, i chose to go down to find max value in min
    Node *temp = current->left;
    Node *temp_parent = current;

    while(temp->right != nullptr)
    {
        temp_parent = temp;
        temp = temp->right;
    }

    current->element = temp->element; //assign max value of left subtree
    //reconnect

    if(temp_parent == current) //if the temp has smaller children reassign them to temp_parent left sub tree
    {
        temp_parent->left = temp->left;
    }
    else
        temp_parent->right = temp->left;
    delete temp;
    std::cout << "Element " << element << " removed successfully." << std::endl;
    return;
}

Node* Tree::search(int element)
{
    Node* temp = root;
    while(temp != nullptr)
    {
        if(temp->element == element)
        {
            std::cout << "Found element " << element << std::endl; 
            return temp;
        }
        else if(temp->element < element)
            temp = temp->right;
        else
            temp = temp->left;
    }
    std::cout << "Element not found" << std::endl;
    return nullptr;
}

/* //recursively search
Node* Tree::search(Node* node, int element)
{
    if(node == nullptr)
        return nullptr;
    else if(node->element == element)
        return node;
    else if(node->element > element)
        return search(node->right, element);
    else
        return search(node->left, element);
}
*/

void Tree::in_order_traverse(Node* node)
//inorder Traversal: 10 20 30 100 150 200 300
{
if(node == nullptr)
{
    return;
}
}

void Tree::post_order_traverse()
{
//todo
}
void Tree::pre_order_traverse(Node* node)
{
    if(node == nullptr)
    {
        return;
    }
    
    traverse_vector.push_back(node->element);
    
    pre_order_traverse(node->left);
    pre_order_traverse(node->right);
}
/*
void delete_subtree(Node* node)
{

}
Tree::~Tree()
{
    delete_subtree(root);
}
*/
void Tree::print_vector()
{
    if(traverse_vector.size() == 0)
    {
        std::cout << "Tree is empty!" << std::endl;
        return;
    }
    std::cout << "Tree traversal: ";
    for(int i = 0; i < traverse_vector.size(); i++)
    {
        std::cout << traverse_vector[i];
        if(i != traverse_vector.size() - 1)
        {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
    traverse_vector.clear();
}

void menu()
{
    Tree tree;
    
    print_line();
    std::cout << "Hello, welcome to the binary search tree program, choose your option:\n";
    
    tree.insert(100);
    tree.insert(20);
    tree.insert(200);
    tree.insert(10);
    tree.insert(30);
    tree.insert(150);
    tree.insert(300);
    
    while(true)
    {
        std::cout << "\t'1' Insert a new value in the tree,\n\t'2' Search for an element in the tree,\n\t'3' Traverse the tree,"
        << "\n\t'4' Delete an element from the tree,\n\t'5' Delete a subtree\n\t'6' Exit the program\nEnter your option: ";
        int menu_option = get_int(1,6);
        int element;
        print_line();
        if(menu_option == 1)
        {
            std::cout << "Enter an integer you want to insert into the tree: ";
            element = get_int(INT_MIN, INT_MAX);
            tree.insert(element);
        }
        else if (menu_option == 2)
        {
            std::cout << "Enter an integer you want to search in the tree: ";
            element = get_int(INT_MIN, INT_MAX);
            tree.search(element);
        }
        else if (menu_option == 3)
        {
            std::cout << "Enter how you want to traverse the tree:\n\t'1' in-order\n\t'2' pre-order\n\t'3' post-order\n" <<
            "Enter your option: ";
            int traverse_option = get_int(1,3);
            switch (traverse_option)
            {
            case 1:
                tree.in_order_traverse();
                std::cout << std::endl;
                break;
            case 2:
                tree.pre_order_traverse(tree.root);
                std::cout << std::endl;
                break;
            case 3:
                tree.post_order_traverse();
                std::cout << std::endl;
                break;
            default:
                break;
            }
            tree.print_vector();
        }
        else if(menu_option == 4)
        {
            std::cout << "Enter which element you want to delete from the tree: ";
            element = get_int(INT_MIN, INT_MAX);
            tree.remove(element);
        }
        else if(menu_option == 5)
        {
            //todo delete subtree root
            std::cout << "Enter which subtree you want to delete (the element entered will also be deleted: ";
        }
        else
        {
            //todo delete subtree(root)
            std::cout << "Exiting the program...\n";
            return 0;
        }
        
    }
}

int main()
{ 
    menu();
    return 0;
}