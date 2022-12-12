#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
/*
 * Test input:
 * oojow     klkds lkl7sd,dfewij  ,,, dn8732r328 JHUuhdwkdlh      .
 * */
using namespace std;

bool isEmpty(string &);

bool isPMark(char &);

int main() {
    int option;
    cout << "Choose how to read the text: '1' from the keyboard or '2' from the file:";
    cin >> option;
    string text;
    if (option == 1) {
        cout << "Enter text:" << endl;
        getline(cin, text);
        getline(cin, text);
    } else {
        cout << "Enter path:" << endl;
        string path;
        cin >> path;
        ifstream file(path);
        while (!file.is_open()) {
            cout << "Wrong path or such file does not exist, try again" << endl;
            cin >> path;
            file.open(path);
        }
        getline(file, text);
    }

    string t, res;
    vector<string> words;
    stringstream(text) >> t;
    while (!isEmpty(text)) {
        text.replace(text.find(t), t.size(), "");
        transform(t.begin(), t.end(), t.begin(), [](unsigned char c) { return std::tolower(c); });
        res += t + " ";
        stringstream(text) >> t;
    }
    res.erase(res.end() - 1);
    for (int i = 0; i < res.size(); ++i) {
        if (isPMark(res[i])) {
            if (res[i] == '.' && i == res.size() - 3 && res[i + 1] == '.' && res[i + 2] == '.') {
                break;
            } else if (res[i] == '.' && i < res.size() - 3 && res[i + 1] == '.' && res[i + 2] == '.' &&
                       res[i + 3] != '.') {
                i += 2;
                continue;
            }
            while (i + 1 != res.size() && res[i + 1] == res[i]) res.erase(res.begin() + i + 1);
        }
    }
    for (int i = 0; i < res.size(); ++i) {
        if (res[i] == ' ' && isPMark(res[i + 1])) {
            res.erase(res.begin() + i);
            i--;
        }
        if (isPMark(res[i]) && i + 1 != res.size() && res[i + 1] != ' ' && !isPMark(res[i + 1]))
            res = res.substr(0, i + 1) + " " + res.substr(i + 1, res.size() - i);
    }
    text = res;
    cout << "Corrected line:" << endl << text << endl << endl;

    string textCopy = text;
    stringstream(textCopy) >> t;
    while (!isEmpty(textCopy)) {
        textCopy.replace(textCopy.find(t), t.size(), "");
        transform(t.begin(), t.end(), t.begin(), [](unsigned char c) { return std::tolower(c); });
        if (!isPMark(t[0])) words.push_back(isPMark(t[t.size() - 1]) ? t.substr(0, t.size() - 1) : t);
        stringstream(textCopy) >> t;
    }
    sort(words.begin(), words.end());
    cout << "Lexicographically sorted words:" << endl;
    for (string &str : words) cout << str << " ";

    cout << endl << endl << "All words of the original sequence displayed vertically:" << endl;
    int maxLength = 0;
    for (string &str : words) if (str.size() > maxLength) maxLength = str.size();
    for (string &str : words) while (str.size() != maxLength) str += ' ';
    for (int i = 0; i < maxLength; ++i) {
        for (string &str : words) cout << str[i] << ' ';
        cout << endl;
    }

    cout << endl << endl << "Current line:" << endl << text << endl << "Enter substring to find:" << endl;
    string substring;
    cin >> substring;
    bool isFound = 0;
    for (int i = 0; i < text.size() - substring.size() + 1; ++i) {
        if (text.substr(i, substring.size()) == substring) {
            cout << "First occurrence indexes [" << i << "; " << i + substring.size() << "]" << endl;
            isFound = 1;
            break;
        }
    }
    if (!isFound) cout << "Substring not found" << endl;

    int *prefTable = new int[substring.size()];
    for (int j = 0; j < substring.size(); ++j) prefTable[j] = 0;
    for (int j = 2; j <= substring.size(); ++j) {
        string subSubstr = substring.substr(0, j);
        int maxPrefLength = 0;
        for (int k = 1; k < subSubstr.size(); ++k) {
            string prefix = subSubstr.substr(0, k), suffix = subSubstr.substr(subSubstr.size() - k, k);
            if (prefix == suffix && k > maxPrefLength) maxPrefLength = k;
        }
        prefTable[j - 1] = maxPrefLength;
    }
    int i = 0;
    for (int j = 0; j < substring.size() && i < text.size(); ++j) {
        if (substring[j] != text[i + j]) {
            if (j == 0) {
                i++;
                j--;
                continue;
            } else {
                i += j - prefTable[j - 1];
                j = prefTable[j - 1] - 1;
            }
        }
    }
    if (i != text.size()) cout << "First occurrence indexes with KMP alg [" << i << "; " << i + substring.size() << "]" << endl;
}

bool isEmpty(string &str) {
    for (char &ch: str) if (ch != ' ') return false;
    return true;
}

bool isPMark(char &ch) {
    if ((ch >= 48 && ch <= 57) || (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || ch == 32) return false;
    return true;
}