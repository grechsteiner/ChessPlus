// StandardOpeningTrie.cc

#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <unordered_map>

#include "StandardOpeningTrie.h"
#include "UserMove.h"
#include "BoardMove.h"
#include "UserSquare.h"

using std::string;
using std::vector;
using std::pair;
using std::unique_ptr;


// Static
const StandardOpeningTrie StandardOpeningTrie::Hardcoded = [] {
    StandardOpeningTrie trie;

    trie.insert({UserMove(UserSquare("e2"), UserSquare("e4")), UserMove(UserSquare("e7"), UserSquare("e5")), UserMove(UserSquare("g1"), UserSquare("f3")), UserMove(UserSquare("b8"), UserSquare("c6")), UserMove(UserSquare("f1"), UserSquare("b5"))}, "Ruy López");
    trie.insert({UserMove(UserSquare("e2"), UserSquare("e4")), UserMove(UserSquare("e7"), UserSquare("e6"))}, "French Defense");
    trie.insert({UserMove(UserSquare("e2"), UserSquare("e4")), UserMove(UserSquare("e7"), UserSquare("e5")), UserMove(UserSquare("g1"), UserSquare("f3")), UserMove(UserSquare("b8"), UserSquare("c6")), UserMove(UserSquare("f1"), UserSquare("c4"))}, "Italian Game");
    trie.insert({UserMove(UserSquare("d2"), UserSquare("d4")), UserMove(UserSquare("d6"), UserSquare("d5")), UserMove(UserSquare("c2"), UserSquare("c4"))}, "Queen's Gambit");
    trie.insert({UserMove(UserSquare("d2"), UserSquare("d4")), UserMove(UserSquare("g8"), UserSquare("f6")), UserMove(UserSquare("c2"), UserSquare("c4")), UserMove(UserSquare("g7"), UserSquare("g6"))}, "King's Indian Defense");

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

void StandardOpeningTrie::insert(const vector<UserMove>& userEnteredMoves, const string& openingName) {
    StandardOpeningTrieNode* standardOpeningTrieNode = root.get();
    for (const auto& userEnteredMove : userEnteredMoves) {
        if (standardOpeningTrieNode->children.find(userEnteredMove.toString()) == standardOpeningTrieNode->children.end()) {
            standardOpeningTrieNode->children[userEnteredMove.toString()] = std::make_unique<StandardOpeningTrieNode>();
        }
        standardOpeningTrieNode = standardOpeningTrieNode->children[userEnteredMove.toString()].get();
        standardOpeningTrieNode->openings.push_back(openingName);
    }
}

vector<pair<string, string>> StandardOpeningTrie::getMatchingOpenings(const vector<BoardMove>& completedMoves) const {
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
