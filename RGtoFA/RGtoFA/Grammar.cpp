#include "Grammar.h"

bool Grammar::VerifyGrammar()
{
    if (nonterminals.size() == 0 || terminals.size() == 0 || productions.size() == 0)
        return false;

    if (nonterminals.find(start_symbol) == nonterminals.end())
        return false;

    for (auto nonterminal : nonterminals)
    {
        if (terminals.find(nonterminal) != terminals.end())
            return false;
    }

    for (auto terminal : terminals)
    {
        if (nonterminals.find(terminal) != nonterminals.end())
            return false;
    }

    bool minOneNonterminal = false;

    for (auto production : productions)
    {
        for (int i = 0; i < production.getU().length(); i++)
        {
            if (nonterminals.find(production.getU()[i]) == nonterminals.end())
            {
                if (terminals.find(production.getU()[i]) == terminals.end())
                    return false;
            }
            else
                minOneNonterminal = true;
        }

        if (production.getV().length() == 0 || production.getU().length() == 0)
            return false;

        for (int i = 0; i < production.getV().length(); i++)
        {
            if (nonterminals.find(production.getV()[i]) == nonterminals.end())
            {
                if (terminals.find(production.getV()[i]) == terminals.end())
                    return false;
            }
        }
    }
    if (minOneNonterminal == false)
        return false;

    return true;
}

bool Grammar::IsRegular()
{
    bool startProduction = false;

    for (auto production : productions)
    {
        if (production.getU().length() > 1)
        {
            return false;
        }
        if (nonterminals.find(production.getU()[0]) == nonterminals.end())
        {
            return false;
        }

        if (production.getU()[0] == start_symbol)
            startProduction = true;

        if (production.getV().length() > 2)
        {
            return false;
        }
        if (terminals.find(production.getV()[0]) == terminals.end())
        {
            return false;
        }
        if (production.getV().length() == 2 && nonterminals.find(production.getV()[1]) == nonterminals.end())
        {
            return false;
        }
    }

    if (startProduction == false)
        return false;

    return true;
}

void Grammar::ReadGrammar()
{
    std::ifstream fin("grammar.txt");

    int nr_nonterminals, nr_terminals, nr_productions;

    char nonterminal;
    fin >> nr_nonterminals;

    for (int i = 0; i < nr_nonterminals; i++)
    {
        fin >> nonterminal;
        nonterminals.insert(nonterminal);
    }

    char terminal;
    fin >> nr_terminals;

    for (int i = 0; i < nr_terminals; i++)
    {
        fin >> terminal;
        terminals.insert(terminal);
    }

    fin >> start_symbol;

    std::string u;
    std::string v;
    fin >> nr_productions;

    for (int i = 0; i < nr_productions; i++)
    {
        Production production;
        fin >> production;
        productions.push_back(production);
    }

    fin.close();
}

void Grammar::PrintGrammar()
{
    std::cout << "nonterminals: ";
    for (auto nonterminal : nonterminals)
    {
        std::cout << nonterminal << " ";
    }
    std::cout << std::endl;

    std::cout << "terminals: ";
    for (auto terminal : terminals)
    {
        std::cout << terminal << " ";
    }
    std::cout << std::endl;

    std::cout << "start symbol: ";
    std::cout << start_symbol;
    std::cout << std::endl;

    std::cout << "productions: ";
    for (auto production : productions)
    {
        std::cout << production << " ";
    }
    std::cout << std::endl;
}