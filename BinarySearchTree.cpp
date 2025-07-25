/*
BST class modified for Project 5
Adapted from prior CSCI 235 semesters
*/

#include "BinarySearchTree.hpp"
#include <vector>


/*CONSTRUCTRS*/

template <class T>
BinarySearchTree<T>::BinarySearchTree() : root_ptr_(nullptr)
{
} // end default constructor

template <class T>
BinarySearchTree<T>::BinarySearchTree(const T &root_item)
    : root_ptr_(std::make_shared<BinaryNode<T>>(root_item, nullptr, nullptr))
{
} // end constructor

template <class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree &another_tree)
{
  root_ptr_ = copyTree(another_tree.root_ptr_); // Call helper method
} // end copy constructor



/*PUBLIC METHODS*/

 /** @return root_ptr_ **/
template <class T>
std::shared_ptr<BinaryNode<T>> BinarySearchTree<T>::getRoot() const
{
  return root_ptr_;
}

/** @return true if the BinarySearchTree is emtpy, false otherwise **/
template <class T>
bool BinarySearchTree<T>::isEmpty() const
{
  return root_ptr_ == nullptr;
} // end isEmpty


/** @return the height of the BST structure as the number of nodes on the longest path from root to leaf**/
template <class T>
int BinarySearchTree<T>::getHeight() const
{
  return this->getHeightHelper(root_ptr_); // Call helper method
} // end getHeight


/** @return the number of Nodes in the BST structure**/
template <class T>
int BinarySearchTree<T>::getNumberOfNodes() const
{
  return this->getNumberOfNodesHelper(root_ptr_); // Call helper method
} // end getNumberOfNodes


/** @param a new entry to be added to the BST
    @post new entry is added to the BST retaining the
              BST property, s.t. at any node, all Items in
              its left subtree are < the item at that node
              and all items in its right subtree are > 
              Note: > and < would need to be overloaded for self made data types
    **/
template <class T>
void BinarySearchTree<T>::add(const T &new_entry)
{
  std::shared_ptr<BinaryNode<T>> new_node_ptr = std::make_shared<BinaryNode<T>>(new_entry);
  root_ptr_ = placeNode(root_ptr_, new_node_ptr);
} // end add


  /** @param entry to be removed from the BST
      @post entry is removed from the BST and retaining its
              BST property, s.t. at any node, all Nodes in
              its left subtree are < the item at that node
              and all items in its right subtree are >**/
template <class T>
bool BinarySearchTree<T>::remove(const T &entry)
{
  bool is_successful = false;
  // call may change is_successful
  root_ptr_ = removeValue(root_ptr_, entry, is_successful);
  return is_successful;
} // end remove


  /** @param entry to be found in the BST
      @return true if entry is found in the BST, false otherwise**/
template <class T>
bool BinarySearchTree<T>::contains(const T &entry) const
{
  return (findNode(root_ptr_, entry) != nullptr);
} // end contains


/**
 * @param: sets the root pointer to the parameter
 */
template <class T>
void BinarySearchTree<T>::setRoot(std::shared_ptr<BinaryNode<T>> new_root_ptr)
{
  root_ptr_ = new_root_ptr;
}





/*PRIVATE METHODS*/




 /** called by copy constructor
      @param old_tee_root_ptr a pointer to the root of the tree to be copied
      @post recursively copies every node in the tree pointed to by the parameter pointer
      @return a pointer to the root of the copied subtree
     **/
template <class T>
std::shared_ptr<BinaryNode<T>> BinarySearchTree<T>::copyTree(const std::shared_ptr<BinaryNode<T>> old_tee_root_ptr) const
{
  std::shared_ptr<BinaryNode<T>> new_tree_ptr;

  // Copy tree nodes during a preorder traversal
  if (old_tee_root_ptr != nullptr)
  {
    // Copy node
    new_tree_ptr = std::make_shared<BinaryNode<T>>(old_tee_root_ptr->getItem(), nullptr, nullptr);
    new_tree_ptr->setLeftChildPtr(copyTree(old_tee_root_ptr->getLeftChildPtr()));
    new_tree_ptr->setRightChildPtr(copyTree(old_tee_root_ptr->getRightChildPtr()));
  } // end if

  return new_tree_ptr;
} // end copyTree


  /** called by getHeight
     @param subtree_ptr a pointer to the root of the current subtree
     @return the height of the BST structure
     as the number of nodes on the longest path
     from root to leaf**/
template <class T>
int BinarySearchTree<T>::getHeightHelper(std::shared_ptr<BinaryNode<T>> subtree_ptr) const
{
  if (subtree_ptr == nullptr)
    return 0;
  else
    return 1 + std::max(getHeightHelper(subtree_ptr->getLeftChildPtr()), getHeightHelper(subtree_ptr->getRightChildPtr()));
} // end getHeightHelper


/** called by getNumberOfNodes
     @param subtree_ptr a pointer to the root of the current subtree
     @return the number of nodes in the tree**/
template <class T>
int BinarySearchTree<T>::getNumberOfNodesHelper(std::shared_ptr<BinaryNode<T>> subtree_ptr) const
{
  if (subtree_ptr == nullptr)
    return 0;
  else
    return 1 + getNumberOfNodesHelper(subtree_ptr->getLeftChildPtr()) + getNumberOfNodesHelper(subtree_ptr->getRightChildPtr());
} // end getNumberOfNodesHelper


/** called by add(new_entry)
      @param subtree_ptr a pointer to the subtree in which to place the new node
      @param new_node_ptr a pointer to the new node to be added to the tree
      @post recursively places the new node as a leaf retaining the BST property
      @return a pointer to the root of the subtree in which node was placed
     **/
template <class T>
std::shared_ptr<BinaryNode<T>> BinarySearchTree<T>::placeNode(std::shared_ptr<BinaryNode<T>> subtree_ptr, std::shared_ptr<BinaryNode<T>> new_node_ptr)
{
  if (subtree_ptr == nullptr)
    return new_node_ptr;
  else
  {
    if (subtree_ptr->getItem() > new_node_ptr->getItem())
      subtree_ptr->setLeftChildPtr(placeNode(subtree_ptr->getLeftChildPtr(), new_node_ptr));
    else
      subtree_ptr->setRightChildPtr(placeNode(subtree_ptr->getRightChildPtr(), new_node_ptr));
    return subtree_ptr;
  }
} // end placeNode


    /** called by contains
      @param subtree_ptr a pointer to the subtree to be searched
      @param target a reference to the item to be found
      @return a pointer to the node containing the target, nullptr if not found
     **/
template <class T>
std::shared_ptr<BinaryNode<T>> BinarySearchTree<T>::findNode(std::shared_ptr<BinaryNode<T>> subtree_ptr, const T &target) const
{
  // Uses a binary search
  if (subtree_ptr == nullptr)
    return subtree_ptr; // Not found
  else if ((subtree_ptr->getItem() == target))
    return subtree_ptr; // Found
  else if (subtree_ptr->getItem() > target)
    // Search left subtree
    return findNode(subtree_ptr->getLeftChildPtr(), target);
  else
    // Search right subtree
    return findNode(subtree_ptr->getRightChildPtr(), target);
} // end findNode


/** called by removeNode
      @param node_ptr a pointer to the node to be removed
      @param inorder_successor a reference to the  inorder successor (the smallest value in the left subtree) of the node to be deleted
      @post removes the node containing the inorder successor
      @return a pointer to the subtree after inorder successor node has been deleted
     **/
template <class T>
std::shared_ptr<BinaryNode<T>> BinarySearchTree<T>::removeLeftmostNode(std::shared_ptr<BinaryNode<T>> node_ptr, T &inorder_successor)
{
  if (node_ptr->getLeftChildPtr() == nullptr)
  {
    inorder_successor = node_ptr->getItem();
    return removeNode(node_ptr);
  }
  else
  {
    node_ptr->setLeftChildPtr(removeLeftmostNode(node_ptr->getLeftChildPtr(), inorder_successor));
    return node_ptr;
  } // end if
} // end removeLeftmostNode



    /** called by removeValue
      @param node_ptr a pointer to the node to be removed
      @post removed the node pointed to by parameter retaining the BST property
      @return a pointer to the subtree after node has been removed
     **/
template <class T>
std::shared_ptr<BinaryNode<T>> BinarySearchTree<T>::removeNode(std::shared_ptr<BinaryNode<T>> node_ptr)
{
  // Case 1) Node is a leaf - it is deleted
  if (node_ptr->isLeaf())
  {
    node_ptr.reset();
    return node_ptr; // delete and return nullptr
  }
  // Case 2) Node has one child - parent adopts child
  else if (node_ptr->getLeftChildPtr() == nullptr) // Has rightChild only
  {
    return node_ptr->getRightChildPtr();
  }
  else if (node_ptr->getRightChildPtr() == nullptr) // Has left child only
  {
    return node_ptr->getLeftChildPtr();
  }
  // Case 3) Node has two children: Find successor node.
  else
  {
    // Traditional way to remove a value in a node with two children
    T new_node_value;
    node_ptr->setRightChildPtr(removeLeftmostNode(node_ptr->getRightChildPtr(), new_node_value));
    node_ptr->setItem(new_node_value);
    return node_ptr;
  } // end if
} // end removeNode


/** called by remove
      @param subtree_ptr a pointer to the subtree in which to look for the value to be removed
      @param target the item to be removed
      @param success a flag to indicate that item was successfully removed
      @return a pointer to the subtree in which target is found
     **/
template <class T>
std::shared_ptr<BinaryNode<T>> BinarySearchTree<T>::removeValue(std::shared_ptr<BinaryNode<T>> subtree_ptr, const T target, bool &success)
{
  if (subtree_ptr == nullptr)
  {
    // Not found here
    success = false;
    return subtree_ptr;
  }
  if ((subtree_ptr->getItem() == target))
  {
    // Item is in the root of some subtree
    subtree_ptr = removeNode(subtree_ptr);
    success = true;
    return subtree_ptr;
  }
  else
  {
    if (subtree_ptr->getItem() > target)
    {
      // Search the left subtree
      subtree_ptr->setLeftChildPtr(removeValue(subtree_ptr->getLeftChildPtr(), target, success));
    }
    else
    {
      // Search the right subtree
      subtree_ptr->setRightChildPtr(removeValue(subtree_ptr->getRightChildPtr(), target, success));
    }
    return subtree_ptr;
  }
} // end removeValue



