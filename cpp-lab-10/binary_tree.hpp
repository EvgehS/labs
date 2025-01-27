template<typename T_key, typename T_data>
class MyBinaryTree {
private:
    class Node;
    
    Node* root;
    
public:
    MyBinaryTree();

    ~MyBinaryTree();
    
    
    void push(const T_key& key, const T_data& value);

    friend std::ostream& operator<<(std::ostream& out, const MyBinaryTree<T_key, T_data>& tree) {
        
        out << "MyBinaryTree " << "{ " << (*(tree.root)) << "}"; 
        return out;
    }
};

template<typename T_key, typename T_data>
class MyBinaryTree<T_key, T_data>::Node
{
    private:
        T_key key;
        T_data data;
        Node* left = nullptr;
        Node* right = nullptr;
        
        Node(const T_key& key, const T_data& value)
            : key(key), data(value) {}

        ~Node()
        {
            if(left)
            {
                delete left;
                left = nullptr;
            }
            if(right) 
            {
                delete right;
                right = nullptr;
            }
        }
        friend std::ostream& operator<<(std::ostream& out, const Node& node)
        {
            
            out << "{key: " << node.key << "; value: " << node.data << "; left: " << (node.left ? std::to_string((node.left)->key):"NULL") << "; right: " << (node.right ? std::to_string((node.right)->key):"NULL") << ";}" << " ";
            if(node.right) out << *node.right;
            if(node.left) out << *node.left;
            return out;
        }

        friend class MyBinaryTree;
};

template<typename T_key, typename T_data>
MyBinaryTree<T_key, T_data>::MyBinaryTree()
    : root(nullptr) {}

template<typename T_key, typename T_data>
MyBinaryTree<T_key, T_data>::~MyBinaryTree()
{
    delete root;
}

template<typename T_key, typename T_data>
void MyBinaryTree<T_key, T_data>::push(const T_key& key, const T_data& value)
{
    Node** node = &root;

    while(*node)
    {
        
        if(key < (*node)->key)
        {
            node = &((*node)->left);
        }
        else if(key > (*node) -> key)
        {
            node = &((*node) -> right);
        }
        else
        {
            break;
        }

    }

    if(*node) (*node)->data = value;
    else *node = new Node(key, value);
}
