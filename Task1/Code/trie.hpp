#pragma once
#include <array>
#include <cassert>
#include <string>
#include <unordered_map>
#include <vector>

// Based on https://www.geeksforgeeks.org/trie-insert-and-search/

struct TrieNode
{
    std::unordered_map<char, size_t> childrenIds;
    bool isLeaf;

    TrieNode()
    : isLeaf(false)
    {}
};

class Trie
{
    static constexpr size_t INITIAL_VECTOR_SIZE = 512;
    std::vector<TrieNode> nodes;
    size_t rootId;

public:
    Trie()
    {
        nodes.reserve(INITIAL_VECTOR_SIZE);
        nodes.emplace_back();
        rootId = 0;
    }

    void insert(const std::string &key)
    {
        assert(nodes.empty() == false && "Tree is not initialized!");

        TrieNode *current = &nodes[rootId];

        for (const char c : key)
        {
            if (current->childrenIds.contains(c) == false)
            {
                current->childrenIds[c] = nodes.size();
                nodes.emplace_back();
            }

            current = &nodes[current->childrenIds[c]];
        }

        current->isLeaf = true;
    }

    [[nodiscard]]
    bool search(const std::string &key) const
    {
        assert(nodes.empty() == false && "Tree is not initialized!");

        const TrieNode *current = &nodes[rootId];

        for (const char c : key)
        {
            auto iterator = current->childrenIds.find(c);
            if (iterator == current->childrenIds.end())
            {
                return false;
            }

            current = &nodes[iterator->second];
        }

        return current->isLeaf;
    }

    void find_similar(const std::string &prefix, std::vector<std::string> &results) const
    {
        assert(nodes.empty() == false && "Tree is not initialized!");

        const TrieNode *current = &nodes[rootId];

        for (const char c : prefix)
        {
            auto iterator = current->childrenIds.find(c);
            if (iterator == current->childrenIds.end())
            {
                return;
            }

            current = &nodes[iterator->second];
        }
        std::string copy = prefix;
        collect_suffixes(current, copy, results);
    }

private:
    void collect_suffixes(const TrieNode *node, std::string &current, std::vector<std::string> &results) const
    {
        if (node->isLeaf)
        {
            results.push_back(current);
        }

        for (auto [c, id] : node->childrenIds)
        {
            current.push_back(c);
            collect_suffixes(&nodes[id], current, results);
            current.pop_back();
        }
    }
};