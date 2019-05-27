#ifndef __BST_HPP__
#define __BST_HPP__


#include <iostream>
#include <cstdlib>
#include <string>
#include <queue>

using namespace std;

// Base class template as a binary search tree:
template <class T>
class BST
{
/// protected member variables:
private:
    struct Node
    {
        T data;
        Node* LC;
        Node* RC;

        Node(T data);
    };

    Node* mRoot; // Pointer to the root of the tree.
    int mSize; // How many Nodes in this binary search tree.

/// public member functions:
public:
    // Constructors:
    BST();
    BST(const BST& copySource);
    ~BST();

    /**
        Add a node of which an integer value is val. Traditional BST.
        If the integer has already exist, then return 1 and do nothing.
        Hence, this insertion can guarantee that no same nodes in the
        BST.
    **/
    virtual int add(T data);

    /**
        Print all data in pre-order.
    **/
    void preOrder() const;

    /**
        Print all data in post-order.
    **/
    void postOrder() const;

    /**
        Print all data in post-order.
    **/
    void inOrder() const;

    /**
        Print all data in BFS order.
    **/
    void BFS() const;

    /**
        Return the size of the whole tree:
    **/
    inline void all() {cout << "Size: " << mSize << endl;};

    /**
        Return if the data exist or not.
        Return 0 if not exist, 1 if do:
    **/
    int lookUp(T data) const;

    /**
        Delete a node from the tree:
    **/
    void deleteNode(T data);

    virtual void print() {};


/// protected member functions:
protected:
    /**
        Forbidden "=" operation by overloading the operator as
        protected.
    **/
    BST& operator= (const BST& source){}

    /**
        Called by: copy constructor
        Helping building a tree by deep copy.
        Arguments:
            copiedRoot - pointer pointing to the root of the tree being copied.
            root - pointer pointing to the root of the tree copying.
    **/
    void _BST(const Node* copiedRoot, Node*& root);

    /**
        Called by destructor to do destruction.
    **/
    void _destructor(Node*& root);

    /**
        Called by: int add(T data)
        Helping add one node onto the tree.
    **/
    virtual int add(Node*& root, T data);

    /**
        Called by: void preOrder()
        Helping printing the tree in preOrder.
    **/
    void preOrder(const Node* root) const;

    /**
        Called by: void preOrder()
        Helping printing the tree in preOrder.
    **/
    void postOrder(const Node* root) const;

    /**
        Called by: void preOrder()
        Helping printing the tree in preOrder.
    **/
    void inOrder(const Node* root) const;

    /**
        Return pointer to the node found:
    **/
    const Node* findNode(T data) const;

    /**
        Called by: Node* findNode(T data)
        Helping find out the node desired to be found:
    **/
    const Node* _findNode(Node* root, T data) const;

    /**
        Find the sibling Node of node n.
        This based on PreOrderTraverse principle.
        Return the value of sibling Node found or return -1 if not found.
    **/
    const Node* findSib(T data) const;

    /**
        Find the sibling Node of node n.
        This based on PreOrderTraverse principle.
        Return the value of sibling Node found or return -1 if not found.
    **/
    const Node* findSib(Node* root, T data) const;

    /**
        Return if the data exist or not.
        Return 0 if not exist, 1 if do:
    **/
    int lookUp(Node* root, T data) const;

    /**
        Return pointer to the parent of the node specified:
    **/
    const Node* findPar(T data) const;

    /**
        Return pointer to the parent of specified node:
    **/
    const Node* findPar(Node* root, T data) const;

     /**
        Return pointer to the minimum node of the tree:
    **/
    const Node* findMinNode(Node* root) const;

    /**
        Delete a node from the tree:
    **/
    void deleteNode(Node*& root, T data);

    /**
        Return a copy of the object:
    **/
    virtual BST<T> clone() const {};

    /**
        Balance the tree:
    **/
    virtual void balance(){};
};


template <class T>
BST<T>::Node::Node(T data): data(data), LC(NULL), RC(NULL) {}

// Constructor of class BST:
template <class T>
BST<T>::BST(): mRoot(NULL), mSize(0) {}

// Copy constructor of class BST:
template <class T>
BST<T>::BST(const BST& copySource)
{
    _BST(copySource.mRoot, mRoot);
    mSize = copySource.mSize;
}

template <class T>
void BST<T>::_BST(const Node* copiedRoot, Node*& root)
{
    if(copiedRoot == NULL)
    {
        root = NULL;
        return;
    }

    root = new Node(copiedRoot->data);

    _BST(copiedRoot->LC, root->LC);
    _BST(copiedRoot->RC, root->RC);

    return;
}

// Destructor of class BST:
template <class T>
BST<T>::~BST()
{
    _destructor(mRoot);
}

template <class T>
void BST<T>::_destructor(Node*& root)
{
    if(root == NULL)
    {
        return;
    }

    _destructor(root->LC);
    _destructor(root->RC);

    delete root;

    return;
}

// Insert one element:
template <class T>
int BST<T>::add(T data)
{
    return add(mRoot, data);
}

template <class T>
int BST<T>::add(Node*& root, T data)
{
    // Add node if null:
    if(root == NULL)
    {
        root = new Node(data);
        ++mSize;
        return 0;
    }

    // Return 1 if node already exist:
    if(root->data == data)
    {
        return 1;
    }

    // Recursively search both children:
    if(root->data > data)
    {
        return add(root->LC, data);
    }
    else
    {
        return add(root->RC, data);
    }
}

// Pre order print:
template <class T>
void BST<T>::preOrder() const
{
    preOrder(mRoot);
}

// PreOrder print helper:
template <class T>
void BST<T>::preOrder(const Node* root) const
{
    if(root == NULL){
        return;
    }

    cout << "Node: " << root->data << endl;

    preOrder(root->LC);
    preOrder(root->RC);

    return;
}

// Post order print:
template <class T>
void BST<T>::postOrder() const
{
    postOrder(mRoot);
}

template <class T>
void BST<T>::postOrder(const Node* root) const
{
    if(root == NULL){
        return;
    }

    postOrder(root->LC);
    postOrder(root->RC);

    cout << "Node: " << root->data << endl;

    return;
}

// In order print:
template <class T>
void BST<T>::inOrder() const
{
    inOrder(mRoot);
}

template <class T>
void BST<T>::inOrder(const Node* root) const
{
    if(root == NULL){
        return;
    }

    inOrder(root->LC);
    cout << "Node: " << root->data << endl;
    inOrder(root->RC);

    return;
}

// BFS print:
template <class T>
void BST<T>::BFS() const
{

    queue<Node*> q;

    if(mRoot==NULL){
        return;
    }

    q.push(mRoot);

    while(!q.empty()){
        Node* tmp = q.front();
        cout << "Node: " << tmp->data << endl;
        q.pop();

        if(tmp->LC!=NULL){
            q.push(tmp->LC);
        }
        if(tmp->RC!=NULL){
            q.push(tmp->RC);
        }
    }
}

// Return pointer to the node to be found:
template <class T>
const typename BST<T>::Node* BST<T>::findNode(T data) const
{
    return _findNode(mRoot, data);
}

template <class T>
const typename BST<T>::Node* BST<T>::_findNode(Node* root, T data) const
{
    //
    if(root == NULL || root->data == data)
    {
        return root;
    }
    else
    {
        const Node *tmp = _findNode(root->LC, data); //Returns a pointer that from target Node's parent.
        if(tmp==NULL)
        {
            return _findNode(root->RC, data); //Returns a pointer that from target Node's parent.
        }
        return tmp;
    }
}

// Return
template <class T>
const typename BST<T>::Node* BST<T>::findSib(T data) const
{
    return findSib(mRoot, data);
}

template <class T>
const typename BST<T>::Node* BST<T>::findSib(Node* root, T data) const
{
    // No sibling, return null:
    if(root == NULL){
        return NULL;
    }

    const Node *tmp = NULL;

    if(root->LC != NULL){
        if(root->LC->data == data){
            return root->RC;  // If root->RC is NULL, just return NULL!
        }
        tmp = findSib(root->LC,data);
    }
    if(tmp == NULL && root->RC != NULL){
        if(root->RC->data == data){
            return root->LC;  // If root->LC is NULL, just return NULL!
        }
        tmp = findSib(root->RC,data);
    }
    return tmp;
}

// Return 1 if the node exists, else return 0:
template <class T>
int BST<T>::lookUp(T data) const
{
    return lookUp(mRoot, data);
}

template <class T>
int BST<T>::lookUp(Node* root, T data) const
{
    // No such node:
    if(root == NULL)
    {
        return 0;
    }

    // Node exists:
    if(root->data == data)
    {
        return 1;
    }

    return lookUp(root->LC, data) || lookUp(root->RC, data);
}

// Return the parent of the specified node:
template <class T>
const typename BST<T>::Node* BST<T>::findPar(T data) const
{
    return findPar(mRoot, data);
}

template <class T>
const typename BST<T>::Node* BST<T>::findPar(Node* root, T data) const
{
    if(root == NULL)
    {
        return NULL;
    }

    const Node *tmp = NULL;
    if(root->LC != NULL)
    {
        if(root->LC->data == data)
        {
            return root;
        }
        tmp = findPar(root->LC,data);
    }
    if(tmp == NULL && root->RC != NULL)
    {
        if(root->RC->data == data)
        {
            return root;
        }
        tmp = findPar(root->RC,data);
    }
    return(tmp);
}

// Return pointer to the minimum node in the tree:
template <class T>
const typename BST<T>::Node* BST<T>::findMinNode(Node* root) const
{
    if(root == NULL)
    {
        return NULL;
    }

    const Node* next = findMinNode(root->LC);

    if(next == NULL)
    {
        return root;
    }
    else
    {
        return next;
    }
}

// To delete a node from the tree:
template <class T>
void BST<T>::deleteNode(T data)
{
    deleteNode(mRoot, data);
}

template <class T>
void BST<T>::deleteNode(Node*& root, T data)
{
    if(root==NULL){
        return;
    }
    else if(data < root->data){
        deleteNode(root->LC,data);
    }
    else if(data > root->data){
        deleteNode(root->RC,data);
    }
    else{ // Find the node to be delete.
        if(root->LC == NULL && root->RC == NULL){
            delete root;
            --mSize;
            root = NULL;
            return;
        }
        else if(root->LC == NULL){
            Node* tmp = root;
            root = root->RC;
            delete tmp;
            --mSize;
            return;
        }
        else if(root->RC == NULL){
            Node* tmp = root;
            root = root->LC;
            delete tmp;
            --mSize;
            return;
        }
        else{
            const Node* tmpMin = findMinNode(root->RC);
            root->data = tmpMin->data;
            deleteNode(root->RC,tmpMin->data);
            return;
        }
    }
}


#endif // __BST_H__
