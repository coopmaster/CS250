/* Modify this file! */

#ifndef _BINARY_SEARCH_TREE_HPP
#define _BINARY_SEARCH_TREE_HPP

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template <typename TK, typename TD>
//! A template node class, to be used in the BinarySearchTree class.
class Node      // done
{
public:
    //! Initializes left and right pointers to nullptr.
    Node()
    {
        ptrLeft = nullptr;
        ptrRight = nullptr;
    }

    //! Destroys left and right children, if they are not pointing to nullptr.
    ~Node()
    {
        // destroy children
        if ( ptrLeft != nullptr ) { delete ptrLeft; }
        if ( ptrRight != nullptr ) { delete ptrRight; }
    }

    //! Pointer to the left child of the node, which is lesser in value
    Node<TK, TD>* ptrLeft;

    //! Pointer to the right chlid of the node, which is greater in value
    Node<TK, TD>* ptrRight;

    //! The data stored by the node
    TD data;

    //! The key of this node
    TK key;
};

template <typename TK, typename TD>
//! A template binary search tree class
class BinarySearchTree
{
public:
    //! Initializes the node count to 0, and the root pointer to nullptr.
    BinarySearchTree()	// done
    {
        m_ptrRoot = nullptr;
        m_nodeCount = 0;
    }

    //! Destroys the root node
    ~BinarySearchTree()		// done
    {
        if ( m_ptrRoot != nullptr ) { delete m_ptrRoot; }
    }

    //! Creates a new node for the tree and assigns the data of that node to the parameter passed in.
    /**
        If the tree is empty, the new data goes at the root node.
        Otherwise, we will have to recurse through the tree in order to
        find the correct position for our new data.

        @param newKey const TK&, the key to index this new item under
        @param newData const TD&, the new data to be added to the tree
        @return <void>
    */
    void Insert( const TK& newKey, const TD& newData )
    {

        RecursiveInsert(newKey,newData,m_ptrRoot);
        /*
        if(m_nodeCount == 0){
            m_ptrRoot = new Node<TK, TD>();
            m_ptrRoot->data = newData;
            m_ptrRoot->key = newKey;
            m_nodeCount++;
        }else{
            Node<TK, TD> * currNode = m_ptrRoot;
            while(currNode != nullptr){
                if(currNode->key < newKey){
                    if(currNode->ptrRight == nullptr){
                        Node<TK, TD> * newNode = new Node<TK, TD>();
                        newNode->key = newKey;
                        newNode->data = newData;
                        currNode->ptrRight = newNode;
                        m_nodeCount++;
                        return;
                    }else{
                        currNode = currNode->ptrRight;
                    }
                }else{
                    if(currNode->ptrLeft == nullptr){
                        Node<TK, TD> * newNode = new Node<TK, TD>();
                        newNode->key = newKey;
                        newNode->data = newData;
                        currNode->ptrLeft = newNode;
                        m_nodeCount++;
                        return;
                    }else{
                        currNode = currNode->ptrLeft;
                    }
                }
            }
            Node<TK, TD> * newNode = new Node<TK, TD>();
            newNode->key = newKey;
            newNode->data = newData;
            currNode = newNode;
            m_nodeCount++;
        }*/
    }

    //! Deletes the Node that contains the given data, if it exists in the tree.
    /**
        Search the tree for a Node that contains the data. This Node will be removed.

        You must handle children of the node based on how many it has.

        See the Sherrod attachment for the detailed code, page 310 - 312.

        @param data const TK&, the data to be removed from the tree.
        @return <void>
    */
    void Delete( const TK& key )
    {
        if(m_ptrRoot->key == key){
            return;
        }
        Node<TK, TD> * currNode = FindNode(key);
        Node<TK, TD> * parentNode = FindParentOfNode(key);
        if(currNode->ptrLeft == nullptr && currNode->ptrRight == nullptr){
            //has no children, just remove the node
            if(parentNode->ptrLeft->key == key){
                parentNode->ptrLeft = nullptr;
            }else{
                parentNode->ptrRight = nullptr;
            }
        }else if(currNode->ptrLeft != nullptr && currNode->ptrRight != nullptr){
            //has both children, figure out who goes on top
            Node<TK, TD> * maxNode = FindNode(key);
            while(maxNode->ptrRight != nullptr){
                maxNode = maxNode->ptrRight;
            }
            if(parentNode->ptrLeft != nullptr && parentNode->ptrLeft->key == key){
                parentNode->ptrLeft->key = maxNode->key;
            }else if(parentNode->ptrRight != nullptr && parentNode->ptrRight->key == key){
                parentNode->ptrRight->key = maxNode->key;
            }else{
                cout << "um... what?" << endl;
            }
        }else{
            //only has one child, make that child take parent's place
            Node<TK, TD> * pofp = FindParentOfNode(parentNode->key);
            if(pofp->ptrLeft != nullptr && pofp->ptrLeft->key == key){
                pofp->ptrLeft = currNode;
            }else if(pofp->ptrRight != nullptr && pofp->ptrRight->key == key){
                pofp->ptrRight = currNode;
            }else{
                cout << "um... what? (2)" << endl;
            }
        }
        m_nodeCount--;
    }

    //! Searches the tree for the key provided and returns true if found, false if not.
    /**
        @return <bool> whether or not the key is found in the tree.
    */
    bool Contains( const TK& key )
    {
        Node<TK, TD> * currNode = m_ptrRoot;
        while(currNode != nullptr){
            if(currNode->key == key){
                return true;
            }else if(key < currNode->key){
                currNode = currNode->ptrLeft;
            }else{
                currNode = currNode->ptrRight;
            }
        }
		return false;
    }

    //! Displays the keys of the nodes in the tree, in in-order format.
    /**
        This function creates a stringstream and calls the recursive
        GetInOrder function. It will return the keys of the nodes in the tree
        in string format.

        @return <string> The keys of the nodes in the tree, in in-order format, as a string.
    */
    string GetInOrder()     // done
    {
        stringstream stream;
        GetInOrder( m_ptrRoot, stream );
        return stream.str();
    }

    //! Displays the keys of the nodes in the tree, in pre-order format.
    /**
        This function creates a stringstream and calls the recursive
        GetPreOrder function. It will return the keys of the nodes in the tree
        in string format.

        @return <string> The keys of the nodes in the tree, in pre-order format, as a string.
    */
    string GetPreOrder()     // done
    {
        stringstream stream;
        GetPreOrder( m_ptrRoot, stream );
        return stream.str();
    }

    //! Displays the keys of the nodes in the tree, in post-order format.
    /**
        This function creates a stringstream and calls the recursive
        GetPostOrder function. It will return the keys of the nodes in the tree
        in string format.

        @return <string> The keys of the nodes in the tree, in post-order format, as a string.
    */
    string GetPostOrder()     // done
    {
        stringstream stream;
        GetPostOrder( m_ptrRoot, stream );
        return stream.str();
    }

    //! Returns the largest value in the tree
    /**
        Keep in mind that, for any given node, anything to
        the RIGHT is greater than that node.

        @return <TK*> Largest key in the tree, or nullptr if tree is empty
    */
    TK* GetMax()     // done
    {
        return GetMax( m_ptrRoot );
    }

    //! Returns the amount of nodes in the tree.
    /**
        @return <int> the amount of nodes in the tree
    */
    int GetCount()     // done
    {
        return m_nodeCount;
    }

    //! Returns the height of the entire tree; must be max height.
    /**
        @return <int> height of the tree
    */
    int GetHeight()     // done
    {
        if ( m_ptrRoot == nullptr )
        {
            return 0;
        }

        return GetHeight( m_ptrRoot );
    }

    //! Returns the data based on a key passed in, or nullptr if not present.
    /**
        Search the binary tree for the node that has the given key
        (can use the FindNode function), and returns the data associated
        with that node. If no node is found, return nullptr instead.

        @param key <TK&>    the key of the node we're searching for
        @return <TD*>       data of the node that has the key given
    */
    TD* GetData( const TK& key )	// done
    {
        Node<TK, TD>* node = FindNode( key );

        if ( node == nullptr )
        {
            return nullptr;
        }

        return &(node->data);
    }

private:
    //! Returns the Node* that contains the key, or nullptr if data is not in the tree.
    /**
        Similar to the Contains function, you will have to traverse the tree to find
        the key. If you find the Node that contains this data, you will return
        the Node*.

        @param data <const TK&>, the key that we are searching for.
        @return <Node<T>*> the Node* that contains the key. Otherwise, nullptr if data is not found.
    */
    Node<TK, TD>* FindNode( const TK& key )
    {
        Node<TK, TD>* currNode = m_ptrRoot;
        if(m_nodeCount == 0){
            return nullptr;
        }else{
            //if it isn't root node, compare keys and step down
            while(currNode != nullptr){
                if(currNode->key == key){
                    return currNode;
                }else if(currNode->key < key){
                    currNode = currNode->ptrRight;
                }else{
                    currNode = currNode->ptrLeft;
                }
            }
        }
        return nullptr;
    }

    //! Returns the PARENT Node* of the Node* that contains the key, or nullptr if data is not in the tree.
    /**
        Similar to the FindNode function, you will instead return the PARENT NODE
        of the node that contains the key, rather than the node itself.

        @param data <const TK&>,    the key we are searching for; but going to return the parent of this node.
        @return <Node<TK, TD>*>     the Node* that contains the data. Otherwise, nullptr if key is not found.
    */
    Node<TK, TD>* FindParentOfNode( const TK& key )
    {
        Node<TK, TD>* currNode = m_ptrRoot;
        if(currNode->key != key){
            while(currNode != nullptr){
                if(currNode->ptrLeft != nullptr && currNode->ptrLeft->key == key){
                    return currNode;
                }else if(currNode->ptrRight != nullptr && currNode->ptrRight->key == key){
                    return currNode;
                }else if(currNode->key < key){
                    currNode = currNode->ptrRight;
                }else{
                    currNode = currNode->ptrLeft;
                }
            }
        }
        return nullptr;
    }

    // RECURSIVE FUNCTIONS: These will recurse through
    // the tree to do the specified operation and
    // return the result back to the interface function,
    // to return back to the caller.

    //! Recurses through the tree and finds the proper location for the new data.
    /**
        TERMINATING CASE: If ptrCurrent is a nullptr, then we have traversed
        to a space that is available for our new node. Create our new node here
        and set up the data.

        RECURSIVE CASE: If ptrCurrent is already taken, we must figure out whether
        to recurse LEFT or RIGHT, based on the value of newData compared to the
        prtCurrent's data.

        @param newKey const TK&,            the key to index this new item under
        @param newData const TD&,           the new data to be added to the tree
        @param ptrCurrent Node<TK, TD>*,    the pointer to the current root of a subtree;
            will traverse left or right if newKey is less-than or greater-than, respectively.
        @return <void>
    */
    void RecursiveInsert( const TK& newKey, const TD& newData, Node<TK, TD>* ptrCurrent )
    {

        if(ptrCurrent == nullptr){
            //set new data here

            //this should only happen if root node is null
            if(m_nodeCount == 0){
                m_ptrRoot = new Node<TK, TD>();
                m_ptrRoot->key = newKey;
                m_ptrRoot->data = newData;
            }else{
                //shouldn't happen
                cout << endl << "null pointer inserted into recursive insert." << endl;
                return;
            }
            m_nodeCount++;
        }else if(ptrCurrent->key < newKey){
            if(ptrCurrent->ptrRight == nullptr){
                //assign here
                ptrCurrent->ptrRight = new Node<TK, TD>();
                ptrCurrent->ptrRight->key = newKey;
                ptrCurrent->ptrRight->data = newData;
                m_nodeCount++;
            }else{
                RecursiveInsert(newKey,newData,ptrCurrent->ptrRight);
            }
        }else if(ptrCurrent->key > newKey){
            if(ptrCurrent->ptrLeft == nullptr){
                //assign here
                ptrCurrent->ptrLeft = new Node<TK, TD>();
                ptrCurrent->ptrLeft->key = newKey;
                ptrCurrent->ptrLeft->data = newData;
                m_nodeCount++;
            }else{
                RecursiveInsert(newKey,newData,ptrCurrent->ptrLeft);
            }
        }else{
            cout << endl << "um... what? (3)" << endl;
        }
    }

    //! Recurses through the tree in IN-ORDER order, writing to the stream.
    /**
        In order will display the items in the tree in ascending order.
        From an algorithmic point of view, for whatever node it is on, it will:
            - Display the left node item
            - Display the current node item
            - Display the right node item

        To write out to the stream, simply use:
        stream << ptrCurrent->key << " ";

        Note that it is expected that you will have a leading space " "
        at the end of the generated string.
    */
    void GetInOrder( Node<TK, TD>* ptrCurrent, stringstream& stream )
    {
        if(ptrCurrent->ptrLeft != nullptr){
            GetInOrder(ptrCurrent->ptrLeft,stream);
        }

        stream << ptrCurrent->key << " ";

        if(ptrCurrent->ptrRight != nullptr){
            GetInOrder(ptrCurrent->ptrRight,stream);
        }

    }

    //! Recurses through the tree in PRE-ORDER order, writing to the stream.
    /**
        In order will display the items in the tree pre-order.
        From an algorithmic point of view, for whatever node it is on, it will:
            - Display the current node item
            - Display the left node item
            - Display the right node item

        Note that it is expected that you will have a leading space " "
        at the end of the generated string.
    */
    void GetPreOrder( Node<TK, TD>* ptrCurrent, stringstream& stream )
    {
        stream << ptrCurrent->key << " ";

        if(ptrCurrent->ptrLeft != nullptr){
            GetPreOrder(ptrCurrent->ptrLeft,stream);
        }

        if(ptrCurrent->ptrRight != nullptr){
            GetPreOrder(ptrCurrent->ptrRight,stream);
        }
    }

    //! Recurses through the tree in POST-ORDER order, writing to the stream.
    /**
        In order will display the items in the tree post-order.
        From an algorithmic point of view, for whatever node it is on, it will:
            - Display the left node item
            - Display the right node item
            - Display the current node item

        Note that it is expected that you will have a leading space " "
        at the end of the generated string.
    */
    void GetPostOrder( Node<TK, TD>* ptrCurrent, stringstream& stream )
    {
        if(ptrCurrent->ptrLeft != nullptr){
            GetPostOrder(ptrCurrent->ptrLeft,stream);
        }

        if(ptrCurrent->ptrRight != nullptr){
            GetPostOrder(ptrCurrent->ptrRight,stream);
        }

        stream << ptrCurrent->key << " ";
    }

    //! Recurses through the tree, going to the right-child-nodes until the max key is found.
    /**
    Items are inserted into a binary search tree in a sorted order.
    This means that larger items always get inserted to the right,
    with the maximum value being the right-most value.
    */
    TK* GetMax( Node<TK, TD>* ptrCurrent )
    {
        if(ptrCurrent->ptrRight != nullptr){
            return GetMax(ptrCurrent->ptrRight);
        }
        return &ptrCurrent->key;
    }

    /**
    Get the height of left sub tree, say leftHeight
    Get the height of right sub tree, say rightHeight
    Take the Max(leftHeight, rightHeight) and add 1 for the root and return
    Call recur­sively.
    */
    int GetHeight( Node<TK, TD>* ptrCurrent )
    {
        int leftHeight = 0;
        int rightHeight = 0;
        if(ptrCurrent != nullptr){
            rightHeight++;
            leftHeight++;
        }
        if(ptrCurrent->ptrRight != nullptr){
            rightHeight += GetHeight(ptrCurrent->ptrRight);
        }
        if(ptrCurrent->ptrLeft != nullptr){
            leftHeight += GetHeight(ptrCurrent->ptrLeft);
        }
		return max(leftHeight,rightHeight);
    }

private:
    //! A pointer to the root node of the tree; TK = data type of the key, TD = data type of the data.
    Node<TK, TD>* m_ptrRoot;

    //! The amount of nodes in the tree
    int m_nodeCount;

friend class Tester;
};

#endif
