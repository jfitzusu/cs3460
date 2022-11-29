#include "WordTree.hpp"
#include "fmt/format.h"
#include "rlutil.h"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

std::shared_ptr<WordTree> readDictionary(std::string filename)
{
    auto wordTree = std::make_shared<WordTree>();
    std::ifstream inFile = std::ifstream(filename, std::ios::in);

    while (!inFile.eof())
    {
        std::string word;
        std::getline(inFile, word);
        // Need to consume the carriage return character for some systems, if it exists
        if (!word.empty() && word[word.size() - 1] == '\r')
        {
            word.erase(word.end() - 1);
        }
        // Keep only if everything is an alphabetic character -- Have to send isalpha an unsigned char or
        // it will throw exception on negative values; e.g., characters with accent marks.
        if (std::all_of(word.begin(), word.end(), [](unsigned char c)
                        { return std::isalpha(c); }))
        {
            std::transform(word.begin(), word.end(), word.begin(), [](char c)
                           { return static_cast<char>(std::tolower(c)); });
            wordTree->add(word);
        }
    }

    return wordTree;
}

template <typename Out>
void split(const std::string& s, char delim, Out result)
{
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim))
    {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string& s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

int main()
{

    auto wordTree = readDictionary("dictionary.txt");

    rlutil::saveDefaultColor();

    rlutil::cls();

    std::string inputString = "";
    std::string partial = "";
    std::string predictString = "";
    int x = 1;
    int y = 1;
    rlutil::locate(x, y);
    for (bool done = false; !done;)
    {
        if (kbhit())
        {

            char input = static_cast<char>(rlutil::getkey());
            switch (input)
            {
                case rlutil::KEY_BACKSPACE:
                    if (inputString.length() > 0)
                    {
                        inputString = inputString.substr(0, inputString.length() - 1);
                    }
                    break;
                case rlutil::KEY_ESCAPE:
                    done = true;
                    break;
                default:
                    inputString += input;
            }

            // Display at new position
            x = inputString.length() % rlutil::tcols() + 1;
            y = static_cast<int>(inputString.length() / rlutil::tcols()) + 1;

            auto splitString = split(inputString, ' ');
            std::string testPartial = "";
            if (splitString.size() > 0)
            {
                testPartial = splitString.back();
            }
            if (std::all_of(testPartial.begin(), testPartial.end(), [](unsigned char c)
                            { return std::isalpha(c); }))
            {
                std::transform(testPartial.begin(), testPartial.end(), testPartial.begin(), [](char c)
                               { return static_cast<char>(std::tolower(c)); });
                partial = testPartial;
            }
            else
            {
                partial = "";
            }
            auto results = wordTree->predict(partial, rlutil::trows() - y - 3);
            predictString = fmt::format("{:<{}}", " ", rlutil::tcols());
            predictString += fmt::format("{:<{}}", "--- prediction ---", rlutil::tcols());
            for (auto result : results)
            {
                predictString += fmt::format("{:<{}}", result, rlutil::tcols());
            }

            for (std::uint32_t i = 0; i < rlutil::trows() - results.size() - 3 - y; i++)
            {
                predictString += fmt::format("{:<{}}", " ", rlutil::tcols());
            }

            rlutil::hidecursor();
            rlutil::locate(1, 1);
            std::cout << fmt::format("{:<{}}", inputString, y * rlutil::tcols()) << predictString;
            rlutil::locate(x, y);
            rlutil::showcursor();
            std::cout.flush();
        }
    }

    rlutil::showcursor();
    rlutil::resetColor();

    return 0;
}
