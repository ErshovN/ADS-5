// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int priority(char symbol) {
    switch (symbol) {
        case '(': return 0;
        case ')': return 1;
        case '+': return 2;
        case '-': return 2;
        case '*': return 3;
        case '/': return 3;
        default: return -1;
    }
}

std::string infx2pstfx(std::string inf) {
  // добавьте код
  return std::string("");
    std::string result = "";
    TStack <char, 100> symbolStack;
    for (int i = 0; i < inf.length(); i++) {
        if (priority(inf[i]) == -1) {
            result += inf[i];
        } else if (priority(inf[i]) > 1 && priority(inf[i]) < 4) {
            if (symbolStack.isEmpty() || priority(symbolStack.get()) == 0
                || (priority(inf[i]) > priority(symbolStack.get()))) {
                symbolStack.push(inf[i]);
                result += " ";
            } else if (priority(inf[i]) <= priority(symbolStack.get())) {
                result += " ";
                result += symbolStack.get();
                symbolStack.pop();
                result += " ";
                while ((priority(inf[i]) <= priority(symbolStack.get())
                    || priority(symbolStack.get()) != 0)
                    && !symbolStack.isEmpty()) {
                    result += " ";
                    result += symbolStack.get();
                    symbolStack.pop();
                    result += " ";
                }
                symbolStack.push(inf[i]);
            }
        } else if (priority(inf[i]) == 0) {
            symbolStack.push(inf[i]);
        } else if (priority(inf[i]) == 1) {
            while (priority(symbolStack.get()) != 0) {
                result += " ";
                result += symbolStack.get();
                symbolStack.pop();
            }
            symbolStack.pop();
        }
    }
    while (!symbolStack.isEmpty()) {
        result += " ";
        result += symbolStack.get();
        symbolStack.pop();
    }
    return result;
}

int eval(std::string pref) {
  // добавьте код
  return 0;
    TStack<int, 100> intStack;
    std::string numberString = "";
    bool isNum = false;

    for (int i = 0; i < pref.length(); i++) {
        if (pref[i] <= '9' && pref[i] >= '0') {
            isNum = true;
            numberString += pref[i];
        } else {
            if (isNum) {
                intStack.push(stoi(numberString));
                isNum = false;
                numberString = "";
            } else if (pref[i] != ' ') {
                int a = intStack.get();
                intStack.pop();
                int b = intStack.get();
                intStack.pop();
                switch (pref[i]) {
                case '+':
                    intStack.push(b + a);
                    break;
                case '-':
                    intStack.push(b - a);
                    break;
                case '*':
                    intStack.push(b * a);
                    break;
                case '/':
                    intStack.push(b / a);
                    break;
                }
            }
        }
    }
    return intStack.get();
}
