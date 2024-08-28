// StandardOpeningTrie.h

#ifndef StandardOpeningTrie_h
#define StandardOpeningTrie_h

#include <memory>
#include <vector>
#include <utility>
#include <string>
#include <unordered_map>

#include "UserEnteredMove.h"
#include "FullMove.h"


class StandardOpeningTrie {

private:
    struct StandardOpeningTrieNode {
        std::unordered_map<std::string, std::unique_ptr<StandardOpeningTrieNode>> children;
        std::vector<std::string> openings;
    };

    std::unique_ptr<StandardOpeningTrieNode> root;

    void collectNextMoves(StandardOpeningTrieNode const *standardOpeningTrieNode, std::vector<std::pair<std::string, std::string>> &results) const;

public:
    StandardOpeningTrie();
    void insert(std::vector<UserEnteredMove> const &userEnteredMoves, std::string const &openingName);
    std::vector<std::pair<std::string, std::string>> getMatchingOpenings(std::vector<FullMove> const &completedMoves) const;

    // TODO: Ideally read in from text file
    static const StandardOpeningTrie Hardcoded;
};


#endif /* StandardOpeningTrie_h */
