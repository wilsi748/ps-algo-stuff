/*
    Author: William Sid (wilsi748)

    Problem solved: Yet Satisfiability Again!
*/

#include <bits/stdc++.h>

using namespace std;

struct Literal
{
    int var;
    bool negation;
    Literal() : var(0), negation(false) {}
    Literal(int v, bool n) : var(v), negation(n) {}
    bool operator<(const Literal &other) const
    {
        if (var != other.var)
        {
            return var < other.var;
        }
        return negation < other.negation;
    }
    bool operator==(const Literal &other) const
    {
        return (var == other.var) && (negation == other.negation);
    }
    bool operator!=(const Literal &other) const
    {
        return (var != other.var);
    }
};

using Clause = vector<Literal>;

void removeClause(vector<Clause> &clauses, const Clause &clauseToRemove)
{
    clauses.erase(remove_if(clauses.begin(), clauses.end(),
                            [&clauseToRemove](const Clause &clause)
                            {
                                if (clause.size() != clauseToRemove.size())
                                {
                                    return false;
                                }
                                for (int i = 0; i < clause.size(); ++i)
                                {
                                    if (clause[i].var != clauseToRemove[i].var ||
                                        clause[i].negation != clauseToRemove[i].negation)
                                    {
                                        return false;
                                    }
                                }
                                return true;
                            }),
                  clauses.end());
}

void removeLiteral(vector<Literal> &clause, Literal lit)
{
    clause.erase(remove_if(clause.begin(), clause.end(),
                           [lit](Literal x)
                           { return x.var == lit.var && x.negation == lit.negation; }),
                 clause.end());
}

void removePure(vector<Clause> &clauses, Literal literalToRemove)
{
    clauses.erase(remove_if(clauses.begin(), clauses.end(),
                            [literalToRemove](Clause &clause)
                            {
                                for (Literal &literal : clause)
                                {
                                    if (literal.var == literalToRemove.var)
                                    {
                                        return true;
                                    }
                                }
                                return false;
                            }),
                  clauses.end());
}

Literal parse_literal(const string &s)
{
    Literal lit;
    try
    {
        if (s[0] == '~')
        {
            lit.negation = true;
            lit.var = stoi(s.substr(2));
        }
        else
        {

            lit.negation = false;
            lit.var = stoi(s.substr(1));
        }
    }
    catch (const invalid_argument &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
    return lit;
}

void printClauses(const vector<Clause> &clauses)
{
    for (int i = 0; i < clauses.size(); i++)
    {
        const Clause &clause = clauses[i];
        cout << "Clause " << i + 1 << ": ";
        for (int j = 0; j < clause.size(); j++)
        {
            const Literal &literal = clause[j];
            cout << (literal.negation ? "~" : "") << "x" << literal.var << " ";
        }
        cout << endl;
    }
}

void unit_propagation(vector<Clause> &clauses)
{
    Literal lit;
    vector<Literal> unit_clause;
    bool lol = false;
    for (auto &clause : clauses)
    {
        if (clause.size() == 1)
        {
            lit = clause[0];
            unit_clause = clause;
            lol = true;
            break;
        }
    }
    if(lol) return;
    vector<Clause> clauses_to_remove;
    for (auto& clause : clauses) {
        if(unit_clause == clause) continue;
        for(auto& literal : clause) {
            if(lit.var == literal.var) {
                if(literal.negation) {
                    clauses_to_remove.push_back(clause);
                } else {
                    removeLiteral(clause, literal);
                }
            }
        }
    }
    for(auto& clause : clauses_to_remove) {
        removeClause(clauses, clause);
    }

}

void pure_elimination(vector<Clause> &clauses, int n)
{
    vector<Literal> pure_literals;
    vector<int> visited(n + 1, -1);
    for (auto &clause : clauses)
    {
        for (auto &lit : clause)
        {
            if (visited[lit.var] == -1)
            {
                visited[lit.var] = lit.negation ? 0 : 1;
            }
            else if ((lit.negation && visited[lit.var] == 1) || (!lit.negation && visited[lit.var] == 0))
            {
                visited[lit.var] = -2;
            }
        }
    }
    for (int i = 0; i < visited.size(); ++i)
    {
        if (visited[i] == 0)
        {
            pure_literals.push_back(Literal(i, true));
        }
        else if (visited[i] == 1)
        {
            pure_literals.push_back(Literal(i, false));
        }
    }
    for (auto &pure_lit : pure_literals)
    {
        removePure(clauses, pure_lit);
    }
}

vector<int> update_literal_freq(vector<int> literal_freq, vector<Clause> &clauses)
{
    vector<int> new_literal_freq(literal_freq.size(), 0);
    for (auto &clause : clauses)
    {
        for (auto &literal : clause)
        {
            new_literal_freq[literal.var]++;
        }
    }
    return new_literal_freq;
}

bool dpll(vector<Clause> &clauses, int n, vector<int> literal_freq)
{
    //printClauses(clauses);
    //cout << "---------------" << endl;

    // Unit propagation
    unit_propagation(clauses);

    //printClauses(clauses);
    //cout << "---------------" << endl;

    // Pure literal elimination
    pure_elimination(clauses, n);

    //printClauses(clauses);
    //cout << "---------------" << endl;
    // Check cnf
    if (clauses.size() == 0)
    {
        return true;
    }

    // Check clauses
    for (Clause c : clauses)
    {
        if (c.size() == 0)
        {
            return false;
        }
    }

    // Choose most frequent literal.
    literal_freq = update_literal_freq(literal_freq, clauses);
    int freq_literal = 0;
    for (int i = 0; i < literal_freq.size(); i++)
    {
        if (literal_freq[i] > freq_literal)
            freq_literal = i;
    }

    Literal branchFalse = Literal(clauses[0][0].var, true);
    Literal branchTrue = Literal(clauses[0][0].var, false);

    vector<Clause> new_clauses = clauses;
    vector<Clause> to_remove;
    for (auto &clause : new_clauses)
    {
        for (auto &literal : clause)
        {
            if (literal.var == branchFalse.var && !literal.negation)
            {
                to_remove.push_back(clause);
                break;
            }
            else if (literal == branchFalse)
            {
                removeLiteral(clause, branchFalse);
            }
        }
    }

    for (auto &clause : to_remove)
    {
        removeClause(new_clauses, clause);
    }
    //printClauses(new_clauses);
    //cout << "---------------" << endl;

    vector<Clause> to_remove2;
    for (auto &clause : clauses)
    {
        for (auto &literal : clause)
        {
            if (literal.var == branchTrue.var && literal.negation)
            {
                to_remove2.push_back(clause);
                break;
            }
            else if (literal.var == branchTrue.var)
            {
                removeLiteral(clause, branchTrue);
            }
        }
    }

    for (auto &clause : to_remove2)
    {
        removeClause(clauses, clause);
    }
    //printClauses(clauses);
    //cout << "---------------" << endl;

    return dpll(clauses, n, literal_freq) || dpll(new_clauses, n, literal_freq);
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        cin.ignore();
        vector<Clause> clauses;
        vector<int> literal_freq(n + 1, 0);
        for (int i = 0; i < m; i++)
        {
            string line;
            getline(cin, line);
            istringstream iss(line);
            string literal;
            Clause c;
            while (iss >> literal)
            {
                if (literal == "v")
                    continue;
                Literal lit = parse_literal(literal);
                literal_freq[lit.var]++;
                c.push_back(lit);
            }
            clauses.push_back(c);
        }
        bool satisfiable = dpll(clauses, n + 1, literal_freq);
        cout << (satisfiable ? "satisfiable" : "unsatisfiable") << endl;
    }
    return 0;
}
