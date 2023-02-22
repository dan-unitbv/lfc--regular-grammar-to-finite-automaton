#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
class FiniteAutomaton {
private:
    std::unordered_set<char> states;
    std::unordered_set<char> alphabet;
    std::vector<std::pair<std::pair<char, char>, char>> transitions;
    char initial_state;
    std::unordered_set<char> final_states;
public:

    FiniteAutomaton() = default;

    ~FiniteAutomaton() = default;

    FiniteAutomaton(const std::vector<char>& states, const std::vector<char>& alphabet, const std::vector<std::pair<std::pair<char, char>, char>>& transitions, char& initial_state, const std::vector<char>& final_states) :
        states{ states.begin(), states.end() },
        alphabet{ alphabet.begin(), alphabet.end() },
        transitions{ transitions.begin(), transitions.end() },
        initial_state{ initial_state },
        final_states{ final_states.begin(), final_states.end() } {
    }

    const std::unordered_set<char>& getStates() const {
        return states;
    }

    void setStates(const std::unordered_set<char>& states) {
        FiniteAutomaton::states = states;
    }

    const std::unordered_set<char>& getAlphabet() const {
        return alphabet;
    }

    void setAlphabet(const std::unordered_set<char>& alphabet) {
        FiniteAutomaton::alphabet = alphabet;
    }

    const std::vector<std::pair<std::pair<char, char>, char>>& getTransitions() const {
        return transitions;
    }

    void setTransitions(const std::vector<std::pair<std::pair<char, char>, char>>& transitions) {
        FiniteAutomaton::transitions = transitions;
    }

    char getInitialState() const {
        return initial_state;
    }

    void setInitialState(char initial_state) {
        FiniteAutomaton::initial_state = initial_state;
    }

    const std::unordered_set<char>& getFinalStates() const {
        return final_states;
    }

    void setFinalStates(const std::unordered_set<char>& final_states) {
        FiniteAutomaton::final_states = final_states;
    }

    bool VerifyAutomaton();
    bool CheckWord(std::string word);
    bool IsDeterministic();
    void PrintAutomaton();
};