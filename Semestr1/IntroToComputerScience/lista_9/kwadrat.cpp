#include <iostream>
#include <vector>

using namespace std;

// funkcja zwracająca kwadrat magiczny o rozmiarze nxn
vector<vector<int>> find_magic_square(int n) {
  // lista przechowująca kwadrat magiczny
  vector<vector<int>> magic_square;
  // wypełnij kwadrat zerami
  for (int i = 0; i < n; i++) {
    vector<int> row;
    for (int j = 0; j < n; j++) {
      row.push_back(0);
    }
    magic_square.push_back(row);
  }
  // ustaw wartość początkową na 1
  int i = 0;
  int j = n / 2;
  magic_square[i][j] = 1;
  // ustaw pozostałe wartości
  for (int num = 2; num <= n * n; num++) {
    // sprawdź, czy możesz wstawić liczbę
    // w miejscu (i-1, j+1)
    int new_i = (i - 1 + n) % n;
    int new_j = (j + 1) % n;
    if (magic_square[new_i][new_j] == 0) {
      i = new_i;
      j = new_j;
    } else {
      i = (i + 1) % n;
    }
    magic_square[i][j] = num;
  }
  return magic_square;
}

int main() {
  int n;
  cout << "Podaj rozmiar kwadratu magicznego: ";
  cin >> n;
  vector<vector<int>> magic_square = find_magic_square(n);
  // wyświetl kwadrat magiczny
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << magic_square[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}
