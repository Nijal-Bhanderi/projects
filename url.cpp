#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <regex>
#include <limits>
using namespace std;

void Print_menu() {
    cout << "____ URL Shortener ____" << endl;
    cout << "1. Shorten URL" << endl;
    cout << "2. Retrieve Original URL" << endl;
    cout << "3. Displaying All URLs" << endl;
    cout << "4. Exit" << endl;
}

bool isValidURL(const string& url) {
    const regex pattern(R"(https?://([\w\-]+\.)+[\w\-]+(/[\w\- ./?%&=]*)?)");
    return regex_match(url, pattern);
}

void Shorten_URL(unordered_map<string, string> &URL, unordered_map<string, int> &count, string lourl, int &counter) {
    for (auto &pair : URL) {
        if (pair.second == lourl) {
            cout << "URL already shortened: " << pair.first << endl;
            return;
        }
    }

    string choice;
    cout << "Do you want to provide a custom alias? (y/n): ";
    getline(cin, choice);

    string shortURL;
    if (choice == "y" || choice == "Y") {
        cout << "Enter your custom alias (no spaces): ";
        string alias;
        getline(cin, alias);
        shortURL = "short.ly/" + alias;

        if (URL.find(shortURL) != URL.end()) {
            cout << "This alias already exists. Please try again with a different alias." << endl;
            return;
        }
    } else {
        shortURL = "short.ly/" + to_string(counter++);
    }

    URL[shortURL] = lourl;
    count[shortURL] = 0;
    cout << "Short URL: " << shortURL << endl;
}

void Original_URL(unordered_map<string, string> &URL, unordered_map<string, int> &count, string sourl) {
    if (URL.find(sourl) != URL.end()) {
        cout << "The original URL is: " << URL[sourl] << endl;
        count[sourl]++;
        cout << "Click Count: " << count[sourl] << endl;
    } else {
        cout << "Short URL is not found!" << endl;
        cout << "Please try again!!!" << endl << endl;
    }
}

void display(unordered_map<string, string> &URL, unordered_map<string, int> &count) {
    if (URL.empty()) {
        cout << "No URLs available!" << endl;
    } else {
        for (auto &ele : URL) {
            cout << ele.first << " -> " << ele.second << " | Clicks: " << count[ele.first] << endl;
        }
    }
}

void URL_file(unordered_map<string, string> &URL, unordered_map<string, int> &count) {
    ifstream file("urls.txt");
    string surl, lurl;
    int c;
    while (file >> surl >> lurl >> c) {
        URL[surl] = lurl;
        count[surl] = c;
    }
    file.close();
}

void save_file(unordered_map<string, string> &URL, unordered_map<string, int> &count) {
    ofstream file("urls.txt");
    for (auto &pair : URL) {
        file << pair.first << " " << pair.second << " " << count[pair.first] << endl;
    }
    file.close();
}

int main() {
    unordered_map<string, string> URL;
    unordered_map<string, int> count;
    int n = 0;
    int id = 1000;
    string longURL;
    string shortURL;

    URL_file(URL, count);

    while (n != 4) {
        Print_menu();
        cout << "Enter your choice: ";
        if (!(cin >> n)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Invalid input! Please enter a number.\n" << endl;
        continue;
}
cin.ignore();
        if (n == 1) {
            cout << "Enter the Long URL to convert it into Short URL: ";
            getline(cin, longURL);
            if (!isValidURL(longURL)) {
                cout << endl<< "Invalid URL format! Please enter a proper URL starting with http:// or https://\n" << endl;
            } else {
                Shorten_URL(URL, count, longURL, id);
                cout << endl;
            }
        } 
        else if (n == 2) {
            cout << "Enter the short URL: ";
            getline(cin, shortURL);
            Original_URL(URL, count, shortURL);
            cout << endl;
        } 
        else if (n == 3) {
            display(URL, count);
            cout << endl;
        } 
        else if (n == 4) {
            save_file(URL, count);
            cout << "Exiting the program" << endl << endl;
        } 
        else {
            cout << "OOPS WRONG CHOICE TRY AGAIN!!" << endl << endl;
        }
    }

    return 0;
}
