#include "FiniteAutomaton.h"

bool FiniteAutomaton::VerifyAutomaton()
{
    if (states.size() == 0 || alphabet.size() == 0)
        return false;

    if (states.find(initial_state) == states.end())
    {
        return false;
    }

    for (auto final_state : final_states)
    {
        if (states.find(final_state) == states.end())
            return false;
    }

    for (auto i = 0; i < transitions.size(); i++)
    {
        if (states.find(transitions[i].first.first) == states.end())
            return false;

        if (alphabet.find(transitions[i].first.second) == alphabet.end())
            return false;

        if (states.find(transitions[i].second) == states.end())
            return false;
    }
    return true;
}

bool FiniteAutomaton::CheckWord(std::string word)
{
    for (int i = 0; i < word.size(); i++)
        if (alphabet.find(word[i]) == alphabet.end())
            return false;
    char current_letter;
    std::unordered_set<char> current_states;
    std::unordered_set<char> result_states;
    current_states.insert(initial_state);
    while (word.size())
    {
        current_letter = word[0];
        word.erase(0, 1);
        bool jam = true;
        for (auto transition : transitions)
        {
            if (current_states.find(transition.first.first) != current_states.end() && current_letter == transition.first.second)
            {
                jam = false;
                result_states.insert(transition.second);
            }
        }
        
        if (jam == true)
            return false;
        else
        {
            current_states.clear();
            current_states = result_states;
            result_states.clear();
        }
    }
    for (auto final_state : final_states)
    {
        if (current_states.find(final_state) != current_states.end())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool FiniteAutomaton::IsDeterministic()
{
    for (int i = 0; i < transitions.size() - 1; i++)
    {
        for (int j = i + 1; j < transitions.size(); j++)
        {
            if (transitions[i].first.first == transitions[j].first.first && transitions[i].first.second == transitions[j].first.second)
                return false;
        }
    }
    return true;
}

void FiniteAutomaton::PrintAutomaton()
{
    std::cout << "states: ";
    for (auto state : states)
    {
        std::cout << state << " ";
    }
    std::cout << std::endl;

    std::cout << "alphabet: ";
    for (auto symbol : alphabet)
    {
        std::cout << symbol << " ";
    }
    std::cout << std::endl;

    std::cout << "transitions: ";
    for (auto transition : transitions)
    {
        std::cout << "{" << transition.first.first << "," << transition.first.second << "}=>" << transition.second << " ";
    }
    std::cout << std::endl;

    std::cout << "initial_state: ";
    std::cout << initial_state;
    std::cout << std::endl;

    std::cout << "final states: ";
    for (auto state : final_states)
    {
        std::cout << state << " ";
    }
    std::cout << std::endl;
}