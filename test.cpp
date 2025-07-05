#include "SkillTree.hpp"
#include <iostream>
#include <cassert>

int main() {
    try {
        std::cout << "Testing SkillTree from CSV:\n";

        SkillTree tree("skills.csv");

        // Test preorderDisplay
        std::cout << "\nPreorder display (from file):\n";
        tree.preorderDisplay();

        // 3. Test findSkill
        assert(tree.findSkill(1) != nullptr);  // Shield
        assert(tree.findSkill(3) != nullptr);  // Heal
        assert(tree.findSkill(99) == nullptr); // Not present

        // Test calculateSkillPoints
        std::cout << "\nSkill points to level up 'Lightning Bolt' (id 4): " << tree.calculateSkillPoints(4) << "\n";

        // Test removeSkill
        assert(tree.removeSkill("Blood Bat"));  // Should remove id 5
        assert(tree.findSkill(5) == nullptr);   // Confirm removal

        // Test addSkill (re-adding removed skill)
        assert(tree.addSkill(Skill(5, "Blood Bat", "Re-added")));
        assert(tree.findSkill(5) != nullptr);   // Should now exist again

        // Test balance
        std::cout << "\nBalancing tree...\n";
        tree.balance();
        std::cout << "Preorder after balancing:\n";
        tree.preorderDisplay();

        // Test clear
        tree.clear();
        std::cout << "\nAfter clearing:\n";
        assert(tree.findSkill(1) == nullptr);
        assert(tree.findSkill(3) == nullptr);
        std::cout << "(Tree successfully cleared)\n";

        std::cout << "\n All CSV-based tests passed!\n";
    } catch (const std::exception& e) {
        std::cerr << " Exception occurred: " << e.what() << "\n";
        return 1;
    }

    return 0;
}