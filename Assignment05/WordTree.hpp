#pragma once
#include <array>
#include <memory>
#include <string>
#include <vector>

class TreeNode
{
  public:
    TreeNode();
    bool m_endOfWord;
    std::array<std::shared_ptr<TreeNode>, 26> m_children;
};

class WordTree
{
  public:
    WordTree();

    void add(std::string word);
    bool find(std::string word);
    std::vector<std::string> predict(std::string partial, std::uint8_t howMany);
    std::size_t size();

  private:
    std::size_t m_size;
    std::shared_ptr<TreeNode> m_head;
};
