/*
BST class modified for Project 5
Adapted from prior CSCI 235 semesters
*/

#ifndef BINARY_SEARCH_TREE_
#define BINARY_SEARCH_TREE_

#include "BinaryNode.hpp"
#include <iostream>

template <class T>
class BinarySearchTree
{
public:
  /*Constructors*/
  BinarySearchTree();                                     //default constructor
  BinarySearchTree(const T &root_item);                   //parameterized constructor
  BinarySearchTree(const BinarySearchTree &another_tree); //copy constructor

  /** @return root_ptr_ **/
  std::shared_ptr<BinaryNode<T>> getRoot() const;

  /** @return true if the BinarySearchTree is emtpy, false otherwise **/
  bool isEmpty() const;

  /** @return the height of the BST structure as the number of nodes on the longest path from root to leaf**/
  int getHeight() const;

  /** @return the number of Nodes in the BST structure**/
  int getNumberOfNodes() const;

  /** @param a new entry to be added to the BST
      @post new entry is added to the BST retaining the
              BST property, s.t. at any node, all Items in
              its left subtree are < the item at that node
              and all items in its right subtree are > 
              Note: > and < would need to be overloaded for self made data types
    **/
  void add(const T &new_entry);

  /** @param entry to be removed from the BST
      @post entry is removed from the BST and retaining its
              BST property, s.t. at any node, all Nodes in
              its left subtree are < the item at that node
              and all items in its right subtree are >**/
  bool remove(const T &entry);


  /** @param entry to be found in the BST
      @return true if entry is found in the BST, false otherwise**/
  bool contains(const T &entry) const;

 


  /**
   * @param: sets the root pointer to the parameter
   */
  void setRoot(std::shared_ptr<BinaryNode<T>> new_root_ptr);

protected:
  std::shared_ptr<BinaryNode<T>> root_ptr_;

  /** called by copy constructor
      @param old_tee_root_ptr a pointer to the root of the tree to be copied
      @post recursively copies every node in the tree pointed to by the parameter pointer
      @return a pointer to the root of the copied subtree
     **/
  std::shared_ptr<BinaryNode<T>> copyTree(const std::shared_ptr<BinaryNode<T>> old_tee_root_ptr) const;


  /** called by getHeight
     @param subtree_ptr a pointer to the root of the current subtree
     @return the height of the BST structure
     as the number of nodes on the longest path
     from root to leaf**/
  int getHeightHelper(std::shared_ptr<BinaryNode<T>> subtree_ptr) const;

  /** called by getNumberOfNodes
     @param subtree_ptr a pointer to the root of the current subtree
     @return the number of nodes in the tree**/
  int getNumberOfNodesHelper(std::shared_ptr<BinaryNode<T>> subtree_ptr) const;

  /** called by add(new_entry)
      @param subtree_ptr a pointer to the subtree in which to place the new node
      @param new_node_ptr a pointer to the new node to be added to the tree
      @post recursively places the new node as a leaf retaining the BST property
      @return a pointer to the root of the subtree in which node was placed
     **/
  std::shared_ptr<BinaryNode<T>> placeNode(std::shared_ptr<BinaryNode<T>> subtree_ptr, std::shared_ptr<BinaryNode<T>> new_node_ptr);


  /** called by remove
      @param subtree_ptr a pointer to the subtree in which to look for the value to be removed
      @param target the item to be removed
      @param success a flag to indicate that item was successfully removed
      @return a pointer to the subtree in which target is found
     **/
  std::shared_ptr<BinaryNode<T>> removeValue(std::shared_ptr<BinaryNode<T>> subtree_ptr, const T target, bool &success);

  /** called by removeValue
      @param node_ptr a pointer to the node to be removed
      @post removed the node pointed to by parameter retaining the BST property
      @return a pointer to the subtree after node has been removed
     **/
  std::shared_ptr<BinaryNode<T>> removeNode(std::shared_ptr<BinaryNode<T>> node_ptr);


  /** called by removeNode
      @param node_ptr a pointer to the node to be removed
      @param inorder_successor a reference to the  inorder successor (the smallest value in the left subtree) of the node to be deleted
      @post removes the node containing the inorder successor
      @return a pointer to the subtree after inorder successor node has been deleted
     **/
  std::shared_ptr<BinaryNode<T>> removeLeftmostNode(std::shared_ptr<BinaryNode<T>> node_ptr, T &inorder_successor);

  /** called by contains
      @param subtree_ptr a pointer to the subtree to be searched
      @param target a reference to the item to be found
      @return a pointer to the node containing the target, nullptr if not found
     **/
  std::shared_ptr<BinaryNode<T>> findNode(std::shared_ptr<BinaryNode<T>> subtree_ptr, const T &target) const;

 


};
#include "BinarySearchTree.cpp"
#endif