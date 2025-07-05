/* Name: Khalid Young
Date: 07.04.2025
This is the implementation for the SkillTree class, a derived member of the BinarySearchTree, with constructors, member functions, etc. */

#include "SkillTree.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

/**
Default constructor
Default-initializes all private members
*/
Skill::Skill(){
    this->id_ = 0;
    this->name_ = " ";
    this->description_ = " ";
}

/**
@param: The unique identifier for the Skill (an integer)
@param: The name of the Skill (a string)
@param: The description of the Skill (a string)
*/
Skill::Skill(const int& id, const std::string& name, const std::string& description){ 
    this->id_ = id;
    this->name_ = name;
    this->description_ = description;
}

/**
@param: A const reference to a Skill
@return: true if the id_ of the Skill is equal to that of the argument, false
otherwise
*/
bool Skill::operator==(const Skill& skill) const{
    return this->id_ == skill.id_;
}

/**
@param: A const reference to a Skill
@return: true if the id_ of the Skill is less than that of the argument, false
otherwise
*/
bool Skill::operator<(const Skill& skill) const{
    return this->id_ < skill.id_;
}

/**
@param: A const reference to a Skill
@return: true if the id_ of the Skill is greater than that of the argument, false
otherwise
*/
bool Skill::operator>(const Skill& skill) const{
    return this->id_ > skill.id_;
}

/**
Default constructor.
Default-initializes all private members.
*/
SkillTree::SkillTree() {}

/**
Parameterized constructor.
@param: The name of a csv file (A string)
@post: The SkillTree is populated with Skills from the csv file. The file
format is as follows:
id, name, description
Ignore the first line
*/
SkillTree::SkillTree(const std::string& filename): BinarySearchTree<Skill>(){
    std::ifstream file(filename);
    if(!file.is_open()){
        throw std::runtime_error("Could not open this file: " + filename);
    }
    std::string line;
    bool first_ = true;

    while(std::getline(file, line)) {
        if(first_){
            first_ = false;
            continue;
        }
        std::stringstream ss(line);
        std::string ids_, name, description;
        if (std::getline(ss, ids_, ',') && std::getline(ss, name, ',') && std::getline(ss, description)){
            int id = std::stoi(ids_);
            Skill skill(id, name, description);
            this->add(skill);
        }
    }
    file.close();
}

/**
@param: The id of the Skill to be found (an integer)
@return: A pointer to the node containing the Skill with the given id, or
nullptr if the Skill is not found
*/
std::shared_ptr<BinaryNode<Skill>> SkillTree::findSkill(const int& id){
    Skill dummy(id, "", "");
    return findNode(getRoot(), dummy);
}

/**
@param: A Skill to be added
@post: Thee skill is added to the tree (in BST order) only if it was not
already in the tree
@return: true if the Skill is successfully added to the SkillTree, false
otherwise
*/
bool SkillTree::addSkill(const Skill& skill){
    if(findSkill(skill.id_) == nullptr){
        add(skill);
        return 1;
    }
    return 0;
}

/**
@param: The name of a Skill
@return: true if the Skill is successfully removed from the SkillTree, false
otherwise
*/
bool SkillTree::removeSkill(const std::string& skill){
    std::vector<Skill> skills_;
    inorderTraversal(getRoot(), skills_);
    for(int i = 0; i < skills_.size(); i++){
        if(skills_[i].name_ == skill){
            return remove(skills_[i]);
        }
    }
    return 0;
}

/**
@post: Clears the tree
*/
void SkillTree::clear() {
    setRoot(nullptr);
}

/**
@param: The id of the Skill (an integer)
Note: For a Skill to be leveled up, its parent Skill must also be leveled up,
thus the Skill points are the number of Skills that must be leveled up before
and including the Skill with the given id.
@return: an integer: the number of skill points needed to level up the Skill
with the given id, starting from the root (i.e. the number of nodes from root
to the given Skill).
Include the Skill with the given id in the count. For example, if the tree
contains the following Skills (represented by their ids):
5
/ \
1 8
and the function parameter queries for id 8, the function should return 2.
If the Skill with the given id is not found, return -1
*/
int SkillTree::calculateSkillPoints(const int& id){
    if(findSkill(id) == nullptr){
        return -1;
    }
    auto curr_ = getRoot();
    int reach_ = 1;
    while(curr_ != nullptr){
        int curr_id_ = curr_->getItem().id_;
        if(id == curr_id_){
            return reach_;
        }
        else if(id < curr_id_){
            curr_ = curr_->getLeftChildPtr();
        }
        else{
            curr_ = curr_->getRightChildPtr();
        }
        reach_++;
    }
    return reach_;
}

/**
@post: Balances the tree
Hint: Recall the definition of a balanced tree:
A tree is balanced if for any node, its left and right subtrees differ in height
by no more than 1.
Hint: You may sort the elements and built the tree recursively using a divide
and conquer approach
*/
void SkillTree::balance() {
    std::vector<Skill> nodes_;
    inorderTraversal(getRoot(), nodes_);
    clear();
    root_ptr_ = buildTree(nodes_, 0, nodes_.size() - 1);
}

/**
@post: Prints the tree in preorder:
[id_] [name_]\n
[description_]\n
*/
void SkillTree::preorderDisplay() const{
    preorderDisplayHelper(getRoot());
}

void SkillTree::preorderDisplayHelper(std::shared_ptr<BinaryNode<Skill>> node) const{
    if(node == nullptr){ return; }
    const Skill& skill = node->getItem();
    std::cout << skill.id_ << " " << skill.name_ << "\n";
    std::cout << skill.description_ << "\n";

    preorderDisplayHelper(node->getLeftChildPtr());
    preorderDisplayHelper(node->getRightChildPtr());
}

/**
@param: Root node
@param: Vector for you to store your nodes while traversal
@post: nodes contain skills from the tree in order recursively
*/
void SkillTree::inorderTraversal(std::shared_ptr<BinaryNode<Skill>> root, std::vector<Skill>& nodes){
    if(root != nullptr){
        inorderTraversal(root->getLeftChildPtr(), nodes);
        nodes.push_back(root->getItem());
        inorderTraversal(root->getRightChildPtr(), nodes);
    }
}

/**
@param: Skills from the tree stored as nodes in a vector
@param: Integer representing the start id
@param: Integer representing the final id
*/
std::shared_ptr<BinaryNode<Skill>> SkillTree::buildTree(const std::vector<Skill>& nodes, int start, int finish){
    if(start > finish) {return nullptr;}
    int center_ = start + (finish - start) / 2;

    auto node = std::make_shared<BinaryNode<Skill>> (nodes[center_]);
    node->setLeftChildPtr(buildTree(nodes, start, center_ - 1));
    node->setRightChildPtr(buildTree(nodes, center_ + 1, finish));
    return node;
}