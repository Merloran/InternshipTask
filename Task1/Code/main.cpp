#include <iostream>
#include "trie.hpp"

int main()
{
    void(setlocale(LC_ALL, "pl_PL")); // Sanity check
    Trie trie;

    std::string line;
    std::vector<std::string> results;
    std::cout << "==========================================================\n"
                 "         *** Witaj w Szukajka.pl - Rok 1997 ***           \n"
                 "        Twój osobisty silnik podpowiedzi zapytañ!         \n"
                 "==========================================================\n"
                 "  Dostêpne komendy:                                       \n"
                 "                                                          \n"
                 "  > add: <zapytanie>                                      \n"
                 "     Dodaje nowe zapytanie do bazy wyszukiwarki.          \n"
                 "     Przyk³ad: add: Kiedy jest nowy rok w Chinach?        \n"
                 "                                                          \n"
                 "  > ask: <prefix zapytania>                               \n"
                 "     Wyszukuje zapytania zaczynaj¹ce siê od danego        \n"
                 "     prefixu i wypisuje najbardziej pasuj¹ce.             \n"
                 "     Przyk³ad: ask: Kiedy jest nowy rok                   \n"
                 "                                                          \n"
                 "  > exit.                                                 \n"
                 "     Koñczy dzia³anie programu.                           \n"
                 "==========================================================\n";

    std::cout << ">";
    while (std::getline(std::cin, line))
    {
        if (line.starts_with("add: "))
        {
            std::string query = line.substr(5);
            trie.insert(query);
        }
        else if (line.starts_with("ask: "))
        {
            std::string prefix = line.substr(5);
            trie.find_similar(prefix, results);
            if (results.empty())
            {
                std::cout << "Brak wyników :(\n";
            } else {
                for (const std::string &similar : results)
                {
                    std::cout << "result: " << similar << "\n";
                }
            }
        }
        else if (line.starts_with("exit."))
        {
            break;
        }
        else
        {
            std::cout << "Nieznana komenda\n";
        }
        std::cout << ">";
    }

    return 0;
}
