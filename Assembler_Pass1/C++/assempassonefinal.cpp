#include <iostream>
#include <bits/stdc++.h>
using namespace std;

map<string, map<string, int>> dir;
map<string, int> rel, reg;

class Code;

string lowercase(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = tolower(s[i]);
    }
    return s;
}

string uppercase(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = toupper(s[i]);
    }
    return s;
}

class Syntax
{
    string label, opcode, op1, op2;
    friend class Code;

public:
    Syntax()
    {
        label = opcode = op1 = op2 = "_";
    }
};

class Pass1
{
    int lc;
    string lcount,icopcode, icop1, icop2;
    friend class Code;

public:
    Pass1()
    {
        lc = 0;
        icopcode = icop1 = icop2 = lcount = "";
    }
};

class Symbol
{
    int addr;
    string sym;
    friend class Code;

public:
    Symbol()
    {
        sym = "";
        addr = 0;
    }
};

class Literal
{
    int addr;
    string lit;
    friend class Code;

public:
    Literal()
    {
        lit = "";
        addr = 0;
    }
};

class Code
{
    vector<Syntax> code;
    vector<Pass1> ans;
    vector<Symbol> stab;
    vector<Literal> ltab;
    vector<int> ltorg;
    vector<int> check;
    int lcount=0;
    vector<pair<pair<string, string>, pair<string, int>>> v;

public:
    Code()
    {
        code.clear();
        ans.clear();
        stab.clear();
        ltab.clear();
        ltorg.clear();
        check.clear();
        v.clear();
        ltorg.push_back(0);
    }
    void input2()
    {
        fstream f;
        f.open("text2.txt", ios::in);
        string s;
        while (getline(f, s))
        {
            string str = "";
            Syntax t;
            vector<string> a;
            bool flag = false;
            for (int i = 0; i < s.length(); i++)
            {
                if (s[i] == ' ')
                {
                    str = lowercase(str);
                    if (dir[str].size() == 0 && flag == false)
                    {
                        t.label = str;
                    }
                    else if (dir[str].size() != 0)
                    {
                        t.opcode = str;
                        flag = true;
                    }
                    else if (reg[str] != 0 || rel[str] != 0)
                    {
                        t.op1 = str;
                    }
                    str = "";
                }
                else
                {
                    str += s[i];
                }
            }
            str = lowercase(str);
            if (dir[str].size() != 0)
            {
                t.opcode = str;
            }
            else
            {
                t.op2 = str;
            }
            code.push_back(t);
        }
        f.close();
    }
    void display()
    {
        cout << left << setw(57) << setfill('-') << '+' << right << '+' << endl;
        cout << left << setw(14) << setfill(' ') << "| Label";
        cout << left << setw(14) << setfill(' ') << "| Opcode";
        cout << left << setw(14) << setfill(' ') << "| Operand1";
        cout << left << setw(14) << setfill(' ') << "| Operand2";
        cout << " |" << endl;
        cout << left << setw(57) << setfill('-') << '+' << right << '+' << endl;

        for (int i = 0; i < code.size(); i++)
        {
            cout << "| ";
            cout << left << setw(12) << setfill(' ') << uppercase(code[i].label);
            cout << "| ";
            cout << left << setw(12) << setfill(' ') << uppercase(code[i].opcode);
            cout << "| ";
            cout << left << setw(12) << setfill(' ') << uppercase(code[i].op1);
            cout << "| ";
            cout << left << setw(12) << setfill(' ') << uppercase(code[i].op2);
            cout << " |";
            cout << endl;
        }
        cout << left << setw(57) << setfill('-') << '+' << right << '+' << endl;
    }
    void createIC()
    {
        int lct = 0;
        for (int i = 0; i < code.size(); i++)
        {
            Pass1 p;
            auto it = dir[code[i].opcode].begin();
            string s = it->first;
            uppercase(s);
            p.icopcode = "(" + s + "," + to_string(it->second) + ")";
            if (code[i].op1 != "_")
            {
                auto it = reg.find(code[i].op1);
                if (it == reg.end())
                {
                    p.icop1 = "(" + to_string(rel[code[i].op1]) + ')';
                }
                else
                {
                    p.icop1 = "(" + to_string(reg[code[i].op1]) + ')';
                }
            }
            if (code[i].opcode == "start")
            {
                lct = stoi(code[i].op2);
                p.lc = 0;
                p.icop2 = "(C," + code[i].op2 + ')';
            }
            else if (it->first == "AD")
            {
                // equ,ltorg and origin to be written here
                string lhs, rhs, sign = "~";
                int idx2, val;
                bool pushed = false;
                if (code[i].op2 != "_")
                {
                    string ptr = code[i].op2;
                    auto it1 = find(ptr.begin(), ptr.end(), '+');
                    auto it2 = find(ptr.begin(), ptr.end(), '-');
                    if (it1 != ptr.end() || it2 != ptr.end())
                    {
                        string sep = "";
                        for (int i = 0; i < ptr.length(); i++)
                        {
                            if (ptr[i] == '+' || ptr[i] == '-')
                            {
                                sign = ptr[i];
                                lhs = sep;
                                sep = "";
                            }
                            else
                            {
                                sep += ptr[i];
                            }
                        }
                        rhs = sep;
                    }

                    if (sign != "~")
                    {
                        idx2 = findsymbol(lhs);
                        val = stoi(rhs);
                        p.icop2 = "(S," + to_string(idx2 + 1) + ')' + sign + rhs;
                    }
                    else
                    {
                        idx2 = findsymbol(code[i].op2);
                        p.icop2 = "(S," + to_string(idx2 + 1) + ')';
                    }
                }

                if (code[i].opcode == "equ")
                {
                    int idx1 = findsymbol(code[i].label);
                    if (idx2 == -1)
                    {
                        check.push_back(i);
                        pair<pair<string, string>, pair<string, int>> p;
                        p.first.first = code[i].label;
                        p.first.second = sign;
                        p.second.first = (sign == "~") ? code[i].op2 : lhs;
                        p.second.second = (sign == "~") ? 0 : val;
                        v.push_back(p);
                    }
                    if (sign == "+")
                    {
                        stab[idx1].addr = stab[idx2].addr + val;
                    }
                    else if (sign == "-")
                    {
                        stab[idx1].addr = stab[idx2].addr - val;
                    }
                    else
                    {
                        stab[idx1].addr = stab[idx2].addr;
                    }
                }
                else if (code[i].opcode == "origin")
                {
                    if (sign == "+")
                    {
                        lct = stab[idx2].addr + val;
                    }
                    else if (sign == "-")
                    {
                        lct = stab[idx2].addr - val;
                    }
                    else
                    {
                        lct = stab[idx2].addr;
                    }
                }
                // ltorg is written here
                else if (code[i].opcode == "ltorg" || code[i].opcode == "end")
                {
                    if (code[i].opcode == "end")
                    {
                        p.lc = 0;
                        ans.push_back(p);
                        pushed = true;
                    }
                    if (ltab.size() > 0)
                    {
                        ltorg.push_back(ltab.size() - 1);
                        for (int i = ltorg.size() - 2; i >= 0 && i < ltorg.size(); i++)
                        {
                            if (ltab[ltorg[i]].addr == 0)
                            {
                                p.lc = lct;
                                p.lcount=to_string(lct);
                                string lite = ltab[ltorg[i]].lit;
                                lite = lite.substr(2, 1);
                                p.icop1 = "(C," + lite + ")";
                                p.icopcode = "(DL,1)";
                                ltab[ltorg[i]].addr = lct;
                                ans.push_back(p);
                                pushed = true;
                                lct += 1;
                            }
                        }
                    }
                }
                if (pushed == true)
                {
                    continue;
                }
                p.lc = 0;
            }
            else if (code[i].opcode == "ds")
            {
                p.lc = lct;
                p.lcount=to_string(lct);
                p.icop2 = "(C," + code[i].op2 + ')';
                Symbol st;
                int idx = findsymbol(code[i].label);
                if (idx == -1)
                {
                    st.sym = code[i].label;
                    st.addr = lct;
                    stab.push_back(st);
                }
                else
                {
                    stab[idx].sym = code[i].label;
                    stab[idx].addr = lct;
                }

                lct += stoi(code[i].op2);
            }
            else
            {
                p.lc = lct;
                p.lcount=to_string(lct);
                if (code[i].opcode == "dc")
                {
                    string temp = code[i].op2;
                    temp = temp.substr(1, temp.length()-2);
                    p.icop2 = "(C," + temp + ')';
                    int idx = findsymbol(code[i].label);
                    stab[idx].sym = code[i].label;
                    stab[idx].addr = lct;
                }
                else if (code[i].label != "_")
                {
                    int idx = findsymbol(code[i].label);
                    if (idx == -1)
                    {
                        Symbol ptr;
                        ptr.sym = code[i].label;
                        ptr.addr = lct;
                        stab.push_back(ptr);
                    }
                    else
                    {
                        stab[idx].addr = lct;
                    }
                }
                if (code[i].op2 != "_" && code[i].opcode != "dc" && code[i].op2[0] != '=')
                {

                    int idx = findsymbol(code[i].op2);
                    if (idx == -1)
                    {
                        Symbol ptr;
                        ptr.sym = code[i].op2;
                        ptr.addr = 0;
                        stab.push_back(ptr);
                        idx = findsymbol(code[i].op2);
                        p.icop2 = "(S," + to_string(idx + 1) + ')';
                    }
                    else
                    {
                        p.icop2 = "(S," + to_string(idx + 1) + ')';
                    }
                }
                if (code[i].op2 != "_" && code[i].opcode != "dc" && code[i].op2[0] == '=')
                {
                    Literal ltr;
                    ltr.lit = code[i].op2;
                    ltr.addr = 0;
                    ltab.push_back(ltr);
                    // string lite = code[i].op2;
                    // lite = lite.substr(2, 1);
                    lcount+=1;
                    p.icop2 = "(L," + to_string(lcount) + ")";
                }
                lct += 1;
            }
            ans.push_back(p);
        }
    }
    int findsymbol(string str)
    {
        for (int i = 0; i < stab.size(); i++)
        {
            if (stab[i].sym == str)
            {
                return i;
            }
        }
        return -1;
    }
    int findliteral(string str)
    {
        for (int i = 0; i < ltab.size(); i++)
        {
            if (ltab[i].lit == str)
            {
                return i;
            }
        }
        return -1;
    }
    void displayIC()
    {
        fstream ic;
        ic.open("ic.txt", ios::out);
        cout << left << setw(57) << setfill('-') << '+' << right << '+' << endl;
        cout << left << setw(14) << setfill(' ') << "| LC";
        cout << left << setw(14) << setfill(' ') << "| Opcode";
        cout << left << setw(14) << setfill(' ') << "| Operand1";
        cout << left << setw(14) << setfill(' ') << "| Operand2";
        cout << " |" << endl;
        cout << left << setw(57) << setfill('-') << '+' << right << '+' << endl;

        ic << left << setw(57) << setfill('-') << '+' << right << '+' << endl;
        ic << left << setw(14) << setfill(' ') << "| LC";
        ic << left << setw(14) << setfill(' ') << "| Opcode";
        ic << left << setw(14) << setfill(' ') << "| Operand1";
        ic << left << setw(14) << setfill(' ') << "| Operand2";
        ic << " |" << endl;
        ic << left << setw(57) << setfill('-') << '+' << right << '+' << endl;

        for (int i = 0; i < ans.size(); i++)
        {
            cout << "| ";
            cout << left << setw(12) << setfill(' ') << ans[i].lcount;
            cout << "| ";
            cout << left << setw(12) << setfill(' ') << ans[i].icopcode;
            cout << "| ";
            cout << left << setw(12) << setfill(' ') << ans[i].icop1;
            cout << "| ";
            cout << left << setw(12) << setfill(' ') << ans[i].icop2;
            cout << " |";
            cout << endl;

            ic << "| ";
            ic << left << setw(12) << setfill(' ') << ans[i].lcount;
            ic << "| ";
            ic << left << setw(12) << setfill(' ') << ans[i].icopcode;
            ic << "| ";
            ic << left << setw(12) << setfill(' ') << ans[i].icop1;
            ic << "| ";
            ic << left << setw(12) << setfill(' ') << ans[i].icop2;
            ic << " |";
            ic << endl;
        }
        cout << left << setw(57) << setfill('-') << '+' << right << '+' << endl;
        ic << left << setw(57) << setfill('-') << '+' << right << '+' << endl;
        ic.close();
    }
    void displayStab()
    {
        fstream stabfile;
        stabfile.open("symbol.txt", ios::out);
        cout << left << setw(43) << setfill('-') << '+' << right << '+' << endl;
        cout << left << setw(14) << setfill(' ') << "| Sr. No.";
        cout << left << setw(14) << setfill(' ') << "| Symbol";
        cout << left << setw(14) << setfill(' ') << "| Address";
        cout << " |" << endl;
        cout << left << setw(43) << setfill('-') << '+' << right << '+' << endl;

        stabfile << left << setw(43) << setfill('-') << '+' << right << '+' << endl;
        stabfile << left << setw(14) << setfill(' ') << "| Sr. No.";
        stabfile << left << setw(14) << setfill(' ') << "| Symbol";
        stabfile << left << setw(14) << setfill(' ') << "| Address";
        stabfile << " |" << endl;
        stabfile << left << setw(43) << setfill('-') << '+' << right << '+' << endl;

        for (int i = 0; i < stab.size(); i++)
        {
            cout << "| ";
            cout << left << setw(12) << setfill(' ') << i + 1;
            cout << "| ";
            cout << left << setw(12) << setfill(' ') << uppercase(stab[i].sym);
            cout << "| ";
            cout << left << setw(12) << setfill(' ') << stab[i].addr;
            cout << " |" << endl;

            stabfile << "| ";
            stabfile << left << setw(12) << setfill(' ') << i + 1;
            stabfile << "| ";
            stabfile << left << setw(12) << setfill(' ') << uppercase(stab[i].sym);
            stabfile << "| ";
            stabfile << left << setw(12) << setfill(' ') << stab[i].addr;
            stabfile << " |" << endl;
        }
        cout << left << setw(43) << setfill('-') << '+' << right << '+' << endl;
        stabfile << left << setw(43) << setfill('-') << '+' << right << '+' << endl;
        stabfile.close();
    }
    void displayLtab()
    {
        fstream stabfile;
        stabfile.open("literal.txt", ios::out);

        cout << left << setw(43) << setfill('-') << '+' << right << '+' << endl;
        cout << left << setw(14) << setfill(' ') << "| Sr. No.";
        cout << left << setw(14) << setfill(' ') << "| Literal";
        cout << left << setw(14) << setfill(' ') << "| Address";
        cout << " |" << endl;
        cout << left << setw(43) << setfill('-') << '+' << right << '+' << endl;

        stabfile << left << setw(43) << setfill('-') << '+' << right << '+' << endl;
        stabfile << left << setw(14) << setfill(' ') << "| Sr. No.";
        stabfile << left << setw(14) << setfill(' ') << "| Literal";
        stabfile << left << setw(14) << setfill(' ') << "| Address";
        stabfile << " |" << endl;
        stabfile << left << setw(43) << setfill('-') << '+' << right << '+' << endl;

        for (int i = 0; i < ltab.size(); i++)
        {
            cout << "| ";
            cout << left << setw(12) << setfill(' ') << i + 1;
            cout << "| ";
            cout << left << setw(12) << setfill(' ') << ltab[i].lit;
            cout << "| ";
            cout << left << setw(12) << setfill(' ') << ltab[i].addr;
            cout << " |" << endl;

            stabfile << "| ";
            stabfile << left << setw(12) << setfill(' ') << i + 1;
            stabfile << "| ";
            stabfile << left << setw(12) << setfill(' ') << ltab[i].lit;
            stabfile << "| ";
            stabfile << left << setw(12) << setfill(' ') << ltab[i].addr;
            stabfile << " |" << endl;

        }
        cout << left << setw(43) << setfill('-') << '+' << right << '+' << endl;
        stabfile << left << setw(43) << setfill('-') << '+' << right << '+' << endl;
    }
    void forwardreference()
    {
        for (int i = 0; i < v.size(); i++)
        {
            int idx1, idx2;
            idx1 = findsymbol(v[i].first.first);
            idx2 = findsymbol(v[i].second.first);
            if (v[i].first.second == "~")
            {
                stab[idx1].addr = stab[idx2].addr;
                ans[check[i]].icop2 = "(S," + to_string(idx2 + 1) + ')';
            }
            else if (v[i].first.second == "+")
            {
                stab[idx1].addr = stab[idx2].addr + v[i].second.second;
                ans[check[i]].icop2 = "(S," + to_string(idx2 + 1) + ')' + v[i].first.second + to_string(v[i].second.second);
            }
            else
            {
                stab[idx1].addr = stab[idx2].addr - v[i].second.second;
                ans[check[i]].icop2 = "(S," + to_string(idx2 + 1) + ')' + v[i].first.second + to_string(v[i].second.second);
            }
        }
    }
};

void createReg(map<string, int> &m)
{
    m["areg"] = 1;
    m["breg"] = 2;
    m["creg"] = 3;
    m["dreg"] = 4;
}

void createRel(map<string, int> &m)
{
    m["lt"] = 1;
    m["le"] = 2;
    m["eq"] = 3;
    m["gt"] = 4;
    m["ge"] = 5;
    m["any"] = 6;
}

void createDir(map<string, map<string, int>> &m)
{
    m["stop"].insert(make_pair("IS", 0));
    m["add"].insert(make_pair("IS", 1));
    m["sub"].insert(make_pair("IS", 2));
    m["mult"].insert(make_pair("IS", 3));
    m["mover"].insert(make_pair("IS", 4));
    m["movem"].insert(make_pair("IS", 5));
    m["comp"].insert(make_pair("IS", 6));
    m["bc"].insert(make_pair("IS", 7));
    m["div"].insert(make_pair("IS", 8));
    m["read"].insert(make_pair("IS", 9));
    m["print"].insert(make_pair("IS", 10));
    m["start"].insert(make_pair("AD", 1));
    m["end"].insert(make_pair("AD", 2));
    m["origin"].insert(make_pair("AD", 3));
    m["equ"].insert(make_pair("AD", 4));
    m["ltorg"].insert(make_pair("AD", 5));
    m["dc"].insert(make_pair("DL", 1));
    m["ds"].insert(make_pair("DL", 2));
}

int main()
{
    createDir(dir);
    createRel(rel);
    createReg(reg);
    Code obj;
    obj.input2();
    obj.display();
    cout << endl;
    obj.createIC();
    obj.forwardreference();
    obj.displayIC();
    cout << endl;
    obj.displayStab();
    cout << endl;
    obj.displayLtab();
    cout << endl;
    cout << endl;
    return 0;
}