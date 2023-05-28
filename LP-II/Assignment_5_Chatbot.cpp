/*
    Subject : ChatBot Application
*/

#include <bits/stdc++.h>
#include <regex>
using namespace std;

vector<pair<regex, string>> rules = {
    {regex("hi|hello|hey", regex_constants::icase), "Hello! Welcome to our food ordering service. How can I assist you with your order?"},
    {regex(".*menu.*", regex_constants::icase), "Sure! Here is our menu:\n1. Pizza\n2. Burger\n3. Pasta\n4. Salad"},
    {regex(".*order.*", regex_constants::icase), "Great! Please let me know your order."},
    {regex(".*pizza.*", regex_constants::icase), "Excellent choice! Our pizza is delicious."},
    {regex(".*burger.*", regex_constants::icase), "Our burgers are juicy and mouthwatering."},
    {regex(".*pasta.*", regex_constants::icase), "Our pasta is cooked to perfection."},
    {regex(".*salad.*", regex_constants::icase), "Our salads are fresh and healthy."},
    {regex(".*thank you.*", regex_constants::icase), "You're welcome! Enjoy your meal!"},
    {regex("exit", regex_constants::icase), "Thank you for using our food ordering service. Goodbye!"},
};

string generateResponse(string &userInput)
{
    for (pair<regex, string> &rule : rules)
    {
        if (regex_search(userInput, rule.first))
        {
            return rule.second;
        }
    }
    return "I'm sorry, I don't understand.";
}

int main()
{
    string userInput;
    cout << "Chatbot: Hello! Welcome to our food ordering service. " << endl;
    while (true)
    {
        cout << "User: ";
        getline(cin, userInput);

        string response = generateResponse(userInput);
        cout << "Chatbot: " << response << endl;

        if (regex_search(userInput, regex("exit", regex_constants::icase)))
            break;
    }
    return 0;
}
