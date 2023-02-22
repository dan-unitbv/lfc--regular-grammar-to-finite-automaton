#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include "Production.h"
#include "Grammar.h"
#include "FiniteAutomaton.h"

auto RegularGrammarToFiniteAutomaton(Grammar g)
{
    auto states = std::vector<char>{ g.getNonterminals().begin(), g.getNonterminals().end() };
    auto alphabet = std::vector<char>{ g.getTerminals().begin(), g.getTerminals().end() };
    auto transitions = std::vector<std::pair<std::pair<char, char>, char>>{};
    auto final_states = std::vector<char>{};
    char initial_state = g.getStartSymbol();
    char new_final_state = 'A';
    for (auto production : g.getProductions())
    {
        if (production.getV().length() == 1)
        {
            if (production.getV()[0] == '$')
                final_states.push_back(production.getU()[0]);

            while (g.getNonterminals().find(new_final_state) != g.getNonterminals().end())
                new_final_state++;

            transitions.emplace_back(std::make_pair(production.getU()[0], production.getV()[0]), new_final_state);
            final_states.push_back(new_final_state);
            states.push_back(new_final_state);
        }
        if (production.getV().length() == 2)
        {
            transitions.emplace_back(std::make_pair(production.getU()[0], production.getV()[0]), production.getV()[1]);
        }
    }
    return FiniteAutomaton{ states, alphabet, transitions, initial_state, final_states };
}

void ReadWord(std::string& word)
{
    std::cout << "Enter a word: \n";
    std::cin >> word;
}

int main()
{
    Grammar g;
    FiniteAutomaton a;
    g.ReadGrammar();
    std::cout << "Press 'a' to print the grammar." << std::endl;
    std::cout << "Press 'b' to generate the finite automaton and print it." << std::endl;
    std::cout << "Press 'c' to check if the finite automaton is correct." << std::endl;
    std::cout << "Press 'd' to check if the finite automaton is deterministic." << std::endl;
    std::cout << "Press 'e' to read a word and check if it is accepted by the finite automaton." << std::endl;
    std::cout << "Press 'f' to exit." << std::endl;
    if (g.VerifyGrammar() == true && g.IsRegular() == true)
    {
        std::string option;
        bool menu = true;
        while (menu == true)
        {
            std::cin >> option;
            if(option.length() == 1)
                switch (option[0])
                {
                case 'a':
                {
                    g.PrintGrammar();
                    std::cout << std::endl;
                    break;
                }
                case 'b':
                {
                    a = RegularGrammarToFiniteAutomaton(g);
                    a.PrintAutomaton();
                    std::cout << std::endl;
                    break;
                }
                case 'c':
                {
                    if (a.VerifyAutomaton() == 1)
                        std::cout << "The finite automaton is correct." << std::endl;
                    else
                        std::cout << "The finite automaton is incorrect." << std::endl;
                    std::cout << std::endl;
                    break;
                }
                case 'd':
                {
                    if (a.IsDeterministic() == 1)
                        std::cout << "The finite automaton is deterministic." << std::endl;
                    else
                        std::cout << "The finite automaton is nondeterministic." << std::endl;
                    std::cout << std::endl;
                    break;
                }
                case 'e':
                {
                    std::string word;
                    ReadWord(word);
                    if (a.CheckWord(word) == true)
                        std::cout << "The word is accepted.";
                    else
                        std::cout << "The word is not accepted.";
                    std::cout << std::endl;
                    std::cout << std::endl;
                    break;
                }
                case 'f':
                {
                    menu = false;
                    break;
                }
                default:
                {
                    if (option[0] < 'a' || option[0] > 'f')
                    {
                        std::cout << "Not an option, try again:" << std::endl;
                        std::cout << std::endl;
                    }
                }
                }
            else
            {
                std::cout << "Not an option, try again:" << std::endl;
                std::cout << std::endl;
            }
         }
    }
    else
        std::cout << "The grammar is wrong or not regular.";
    return 0;
}

