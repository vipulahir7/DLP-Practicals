#include<bits/stdc++.h>
using namespace std;

void PR4_1(string content){
    int n = content.size();
    string num = "";
    for(int i=0; i<n; i++){
        if(content[i] >= '0' && content[i] <= '9'){
            num += content[i];
        }
        else if(num.size()){
            cout<<stoi(num)<<endl;
            num = "";
        }
    }
    if(num.size()){
        cout<<stoi(content)<<endl;
        num = "";
    }
}

void PR4_2(string content){
    int n = content.size();
    string str = content;
    for(int i=0; i<n; i++){
        str[i] = tolower(str[i]);
    }

    if(n < 8){
        cout<<content<<endl;
        return;
    }
    string temp = "$";
    for(int i=0; i<7; i++){
        temp += str[i];
    }
    for(int i=7; i<content.size(); i++){
        temp = temp.substr(1,7);
        temp += str[i];

        if(temp == "charusat"){
            str.replace(str.begin() + i - 7, str.begin() + i + 1, "university");
            content.replace(content.begin() + i - 7, content.begin() + i + 1, "university");
        }
    }
    cout<<content<<endl;
}


void PR4_3(string content) {
    int charCount = 0, wordCount = 0, lineCount = 0, spaceCount = 0;
    bool inWord = false;

    for (char ch : content) {
        charCount++;
        if (ch == '\n') {
            lineCount++;
        }
        if (isspace(ch)) {
            spaceCount++;
            inWord = false;
        } else if (!inWord) {
            wordCount++;
            inWord = true;
        }
    }
    
    cout << "Number of characters: " << charCount << endl;
    cout << "Number of words: " << wordCount << endl;
    cout << "Number of lines: " << lineCount << endl;
    cout << "Number of spaces: " << spaceCount << endl;
}

void PR4_4(string content){
    if (content.length() < 9 || content.length() > 15) {
        cout<<"Not Valid"<<endl;
        return;
    }
    
    bool hasLower = false, hasUpper = false, hasDigit = false, hasSymbol = false;
    string symbols = "*;#$@";
    
    for (char ch : content) {
        if(ch == '\n'){
            break;
        }
        if (islower(ch)) hasLower = true;
        else if (isupper(ch)) hasUpper = true;
        else if (isdigit(ch)) hasDigit = true;
        else if (symbols.find(ch) != string::npos) hasSymbol = true;
    }
    
    if(hasLower && hasUpper && hasDigit && hasSymbol){
        cout<<"Valid"<<endl;
    }
    else{
        cout<<"Not Valid"<<endl;
    }
}


int main(){

    ifstream file("PR4.txt");
    string line, content;

    while(getline(file, line)){
        content += line + "\n";
    }
    file.close();

  //uncomment the function you want to run

    // PR4_1(content);
    // PR4_2(content);
    // PR4_3(content);
    // PR4_4(content);

}
