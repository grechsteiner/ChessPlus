// StandardOpeningTrie.h

#ifndef StandardOpeningTrie_h
#define StandardOpeningTrie_h

#include <memory>
#include <vector>
#include <utility>
#include <string>
#include <unordered_map>

#include "Move.h"
#include "CompletedMove.h"


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
    void insert(std::vector<Move> const &moves, std::string const &openingName);
    std::vector<std::pair<std::string, std::string>> getMatchingOpenings(std::vector<CompletedMove> const &completedMoves) const;

    // TODO: Ideally read in from text file
    static const StandardOpeningTrie Hardcoded;
};


#endif /* StandardOpeningTrie_h */
