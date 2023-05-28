#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<string> questions = {
        "Do you know about stock market?",
        "Are you familiar with trading platforms?",
        "Have you invested in stock market earlier?",
        "Do you know concepts of stocks, bonds, equity?",
        "Do you know options trading?",
        "Do you know future trading?",

        "What is the profit percent of the your invested amount?",
        
        "Are you comfortable analyzing company fundamentals, such as earnings reports and valuation ratios?",
        "Do you understand the concept of diversification and the importance of having a well-balanced portfolio?",
        "Have you ever employed strategies like dollar-cost averaging or value investing in your investment approach?"};

    map<string, int> threshold;
    threshold["Beginner"] = 0;
    threshold["Intermediate"] = 37;
    threshold["Expert"] = 70;

    cout << "\n\n\tWelcome To The Stock Market EXPERT SYSTEM\n"
         << endl;
    cout << "\tNote : Please answer the following questions \n\n"
         << endl;

    int score = 0;
    for (string &question : questions)
    {
        if (question == questions[6])
        {
            cout << question << endl;
            int profit;
            cout << "Enter your profit perecentage:" << endl;
            cin >> profit;
            if (profit >= 70)
                score += 10;
            else if (profit >= 20)
                score += 6;
            else
                score += 1;
            continue;
        }

        cout << question << " "
             << " (Y/N)";
        cout << ">  ";
        char ans;
        cin >> ans;
        while (tolower(ans) != 'y' && tolower(ans) != 'n')
        {
            cout << "Enter a valid input:" << endl;
            cout << question << " "
                 << " (Y/N) ";
            cout << ">  ";
            cin >> ans;
        }

        if (tolower(ans) == 'y')
        {
            cout << "On a scale of 1-10 how would you rate yourself?";
            cout << ">  ";
            int val;
            cin >> val;
            while (val < 1 || val > 10)
            {
                cout << "Enter a valid input:" << endl;
                cout << ">  ";
                cin >> val;
            }
            score += val;
        }
    }

    if (score >= threshold["Expert"])
    {
        cout << "According to our system you seem to be an expert at trading!" << endl;
        cout << "We think that you don't need any tips." << endl;
    }
    else if (score >= threshold["Intermediate"])
    {
        cout << "Based on your answers you seem to be intermediate" << endl;
        cout << "You are advised to learn more things about trading and " << endl;
        cout << "You can visit www.zerodha.com for any information you need" << endl;
    }
    else if (score >= threshold["Beginner"])
    {
        cout << "Based on your answers you seem to be a beginner in trading." << endl;
        cout << "You are advised to learn about basics of stock market." << endl;
        cout << "You can start by investing small amount of money as you wish and get familiar with trading platforms" << endl;
        cout << "You can visit www.zerodha.com for any information you need" << endl;
    }

    return 0;
}
