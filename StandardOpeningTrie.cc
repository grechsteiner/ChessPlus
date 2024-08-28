// StandardOpeningTrie.cc

#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <unordered_map>

#include "StandardOpeningTrie.h"
#include "UserEnteredMove.h"
#include "FullMove.h"

using std::string;
using std::vector;
using std::pair;
using std::unique_ptr;


// Static
const StandardOpeningTrie StandardOpeningTrie::Hardcoded = [] {
    StandardOpeningTrie trie;

    trie.insert({UserEnteredMove("e2", "e4"), UserEnteredMove("e7", "e5"), UserEnteredMove("g1", "f3"), UserEnteredMove("b8", "c6"), UserEnteredMove("f1", "b5")}, "Ruy López");
    trie.insert({UserEnteredMove("e2", "e4"), UserEnteredMove("e7", "e6")}, "French Defense");
    trie.insert({UserEnteredMove("e2", "e4"), UserEnteredMove("e7", "e5"), UserEnteredMove("g1", "f3"), UserEnteredMove("b8", "c6"), UserEnteredMove("f1", "c4")}, "Italian Game");
    trie.insert({UserEnteredMove("d2", "d4"), UserEnteredMove("d6", "d5"), UserEnteredMove("c2", "c4")}, "Queen's Gambit");
    trie.insert({UserEnteredMove("d2", "d4"), UserEnteredMove("g8", "f6"), UserEnteredMove("c2", "c4"), UserEnteredMove("g7", "g6")}, "King's Indian Defense");

    return trie;
}();

StandardOpeningTrie::StandardOpeningTrie() : root(std::make_unique<StandardOpeningTrieNode>()) {}

void StandardOpeningTrie::collectNextMoves(StandardOpeningTrieNode const *standardOpeningTrieNode, std::vector<std::pair<std::string, std::string>> &results) const {
    for (auto const &pair : standardOpeningTrieNode->children) {
        for (const std::string &opening : pair.second->openings) {
            results.push_back({opening, pair.first});
        }
    }
}

void StandardOpeningTrie::insert(const vector<UserEnteredMove>& userEnteredMoves, const string& openingName) {
    StandardOpeningTrieNode* standardOpeningTrieNode = root.get();
    for (const auto& userEnteredMove : userEnteredMoves) {
        if (standardOpeningTrieNode->children.find(userEnteredMove.toString()) == standardOpeningTrieNode->children.end()) {
            standardOpeningTrieNode->children[userEnteredMove.toString()] = std::make_unique<StandardOpeningTrieNode>();
        }
        standardOpeningTrieNode = standardOpeningTrieNode->children[userEnteredMove.toString()].get();
        standardOpeningTrieNode->openings.push_back(openingName);
    }
}

vector<pair<string, string>> StandardOpeningTrie::getMatchingOpenings(const vector<FullMove>& completedMoves) const {
    vector<pair<string, string>> results;
    const StandardOpeningTrieNode* standardOpeningTrieNode = root.get();
    if (!standardOpeningTrieNode) return results; // Ensure root is not null

    for (const auto& completedMove : completedMoves) {
        if (standardOpeningTrieNode->children.find(completedMove.toString()) == standardOpeningTrieNode->children.end()) {
            return results;
        }
        standardOpeningTrieNode = standardOpeningTrieNode->children.at(completedMove.toString()).get();
    }
    collectNextMoves(standardOpeningTrieNode, results);
    return results;
}
