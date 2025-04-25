#include <gtest/gtest.h>
#include <cstdint>
#include <limits>
#include "trie.hpp"

TEST(TrieTest, SearchTest)
{
    Trie trie;

    trie.insert("kot");
    trie.insert("kotek");
    trie.insert("kotek123");

    EXPECT_TRUE(trie.search("kot"));
    EXPECT_TRUE(trie.search("kotek"));
    EXPECT_TRUE(trie.search("kotek123"));
    EXPECT_FALSE(trie.search("pies"));
}

TEST(TrieTest, FindSimilarTest)
{
    Trie trie;

    trie.insert("kot");
    trie.insert("kotek");
    trie.insert("kotek123");
    trie.insert("pies");
    trie.insert("piesa");

    std::vector<std::string> results;

    trie.find_similar("ko", results);
    EXPECT_EQ(results.size(), 3);
    EXPECT_EQ(results[0], "kot");
    EXPECT_EQ(results[1], "kotek");
    EXPECT_EQ(results[2], "kotek123");

    results.clear();

    trie.find_similar("pi", results);
    EXPECT_EQ(results.size(), 2);
    EXPECT_EQ(results[0], "pies");
    EXPECT_EQ(results[1], "piesa");

    results.clear();

    trie.find_similar("", results);
    EXPECT_EQ(results.size(), 5);
    EXPECT_TRUE(std::ranges::find(results, "kot")      != results.end());
    EXPECT_TRUE(std::ranges::find(results, "kotek")    != results.end());
    EXPECT_TRUE(std::ranges::find(results, "kotek123") != results.end());
    EXPECT_TRUE(std::ranges::find(results, "pies")     != results.end());
    EXPECT_TRUE(std::ranges::find(results, "piesa")    != results.end());
}

TEST(TrieTest, NoMatchingPrefix)
{
    Trie trie;

    trie.insert("kot");
    trie.insert("kotek");

    std::vector<std::string> results;

    trie.find_similar("pies", results);
    EXPECT_EQ(results.size(), 0);
}

TEST(TrieTest, EmptyTrie)
{
    Trie trie;

    EXPECT_FALSE(trie.search("kot"));

    std::vector<std::string> results;
    trie.find_similar("kot", results);
    EXPECT_EQ(results.size(), 0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}