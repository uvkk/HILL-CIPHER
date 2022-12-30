#include<iostream>
using namespace std;

void getKey(double key[2][2]) {
    cout<<"Enter the Key Matrix"<<endl;
    for(int i=0; i<2; i++) {
        for(int j=0; j<2; j++) {
            cin>>key[i][j];
        }
    }
}

void getMessage(string& text) {
    cout<<"Enter the Plain Text: ";
    getline(cin>>ws, text);
}

int to_num(char c) {
    if(c >= 'A' && c <= 'Z') return c - 'A';
}

void multiply(double p[2], double k[2][2], double c[2]) {
    c[0] = int((p[0]*k[0][0] + p[1]*k[1][0])) % 26;
    c[1] = int((p[0]*k[0][1] + p[1]*k[1][1])) % 26;
}

char to_char(int x) {
    while(x < 0) x += 26;
    if(x >= 0 && x <= 25) return char('A' + x);

}

string encryptHill(string text, double key[2][2]) {
    string encrypted;

    for(int i=0; i<text.length(); i+=2) {
        double p[2];
        p[0] = to_num(text[i]);
        p[1] = to_num(text[i+1]);

        double c[2];
        multiply(p, key, c);
        encrypted.push_back(to_char(c[0]));
        encrypted.push_back(to_char(c[1]));
    }

    return encrypted;
}

int inv(int a) {
    for (int i=1; i<26; i++) {
        if (((a % 26) * i) % 26 == 1) {
            return i;
        }
    }
}

string decryptHill(string cipher, double key[2][2]) {
    string decrypted;
    double inverse_key[2][2];

    int det = ((key[0][0] * key[1][1]) - (key[0][1] * key[1][0]));
    double m = inv(det);

    inverse_key[0][0] = m * key[1][1];
    inverse_key[0][1] = m * key[0][1] * (-1);
    inverse_key[1][0] = m * key[1][0] * (-1);
    inverse_key[1][1] = m * key[0][0];


    for(int i=0; i<cipher.length(); i+=2) {
        double c[2];
        c[0] = to_num(cipher[i]);
        c[1] = to_num(cipher[i+1]);

        double p[2];
        multiply(c, inverse_key, p);
        decrypted.push_back(to_char(p[0]));
        decrypted.push_back(to_char(p[1]));
    }

    return decrypted;
}

int main() {
    double key[2][2];
    string text;

    getKey(key);
    getMessage(text);
    if(text.length() & 1) text.push_back('X');

    string encrypted = encryptHill(text, key);
    cout<<"Cipher Text: "<<encrypted<<endl;

    string decrypted = decryptHill(encrypted, key);
    cout<<"Decrypted Message: "<<decrypted<<endl;

    return 0;
}
