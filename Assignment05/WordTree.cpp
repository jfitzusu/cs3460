#include "WordTree.hpp"

#include <algorithm>
#include <deque>
#include <iostream>
#include <memory>

TreeNode::TreeNode()
{
    m_endOfWord = false;
    m_children = std::array<std::shared_ptr<TreeNode>, 26>();
}

WordTree::WordTree()
{
    m_head = std::make_shared<TreeNode>();
    m_size = 0;
}

void WordTree::add(std::string toAdd)
{
    std::shared_ptr<TreeNode> current = m_head;

    std::transform(toAdd.begin(), toAdd.end(), toAdd.begin(), [](char c)
                   { return static_cast<char>(std::tolower(c)); });

    for (char letter : toAdd)
    {
        int index = static_cast<int>(letter - 'a');
        if (current->m_children[index] == nullptr)
        {
            current->m_children[index] = std::make_shared<TreeNode>();
        }
        current = current->m_children[index];
    }

    if (current->m_endOfWord || current == m_head)
    {
        return;
    }

    current->m_endOfWord = true;
    m_size += 1;
}

bool WordTree::find(std::string word)
{
    if (!std::all_of(word.begin(), word.end(), [](unsigned char c)
                     { return std::isalpha(c); }))
    {
        return false;
    }
    std::shared_ptr<TreeNode> current = m_head;
    std::transform(word.begin(), word.end(), word.begin(), [](char c)
                   { return static_cast<char>(std::tolower(c)); });

    for (char letter : word)
    {

        int index = static_cast<int>(letter - 'a');
        if (current->m_children[index] == nullptr)
        {
            return false;
        }
        current = current->m_children[index];
    }

    return current->m_endOfWord;
}

std::vector<std::string> WordTree::predict(std::string partial, std::uint8_t howMany)
{
    std::shared_ptr<TreeNode> current = m_head;
    std::transform(partial.begin(), partial.end(), partial.begin(), [](char c)
                   { return static_cast<char>(std::tolower(c)); });

    std::vector<std::string> results;
    if (partial == "")
    {
        return results;
    }
    for (char letter : partial)
    {
        int index = static_cast<int>(letter - 'a');
        if (current->m_children[index] == nullptr)
        {
            return results;
        }
        current = current->m_children[index];
    }

    std::deque<std::shared_ptr<TreeNode>> nodeQueue;
    std::deque<std::string> stringQueue;
    std::string currentString;
    std::shared_ptr<TreeNode> lookAt;

    nodeQueue.push_back(current);
    stringQueue.push_back(partial);

    while (results.size() < howMany && nodeQueue.size() > 0)
    {
        lookAt = nodeQueue.back();
        nodeQueue.pop_back();
        currentString = stringQueue.back();
        stringQueue.pop_back();

        if (lookAt->m_endOfWord && currentString != partial)
        {
            results.push_back(currentString);
        }

        for (std::uint32_t i = 0; i < lookAt->m_children.size(); i++)
        {
            if (lookAt->m_children[i] != nullptr)
            {
                nodeQueue.push_back(lookAt->m_children[i]);
                stringQueue.push_back(currentString + static_cast<char>(97 + i));
            }
        }
    }

    return results;
}

std::size_t WordTree::size()
{
    return m_size;
}