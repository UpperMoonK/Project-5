/* Name: Khalid Young
Date: 07.04.2025
This is the documentation for the SkillTree class, a derived member of the BinarySearchTree, with constructors, member functions, etc. */

#ifndef SKILLTREE_HPP_
#define SKILLTREE_HPP_
#include "BinarySearchTree.hpp"
#include "BinaryNode.hpp"

struct Skill{
    int id_;
    std::string name_;
    std::string description_;
    Skill();
    Skill(const int& id, const std::string& name, const std::string& description);
    bool operator==(const Skill& skill) const;
    bool operator<(const Skill& skill) const;
    bool operator>(const Skill& skill) const;
};

class SkillTree: public BinarySearchTree<Skill>{
public: 
    SkillTree();
    SkillTree(const std::string& filename);
    std::shared_ptr<BinaryNode<Skill>>findSkill(const int& id);
    bool addSkill(const Skill& skill);
    bool removeSkill(const std::string& skill);
    void clear();
    int calculateSkillPoints(const int& id);
    void balance();
    void preorderDisplay() const;
    void preorderDisplayHelper(std::shared_ptr<BinaryNode<Skill>> node) const;
    void inorderTraversal(std::shared_ptr<BinaryNode<Skill>> root, std::vector<Skill>& nodes);
    std::shared_ptr<BinaryNode<Skill>> buildTree(const std::vector<Skill>& nodes, int start, int finish);
};
#endif