#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "cards.h"

using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  //Read each file
  
  IntBST bstAlice;
  IntBST bstBob;
  int minA = 1000;
  int maxB = -1000;

  while (getline (cardFile1, line) && (line.length() > 0)){

    int suit;
    int card;

    stringstream ss(line);
    string suitStr = "";
    getline(ss, suitStr, ' ');
    
    string cardStr = "";
    getline(ss, cardStr, ' ');
    
    if (suitStr == "c")
      suit = 100;
    else if (suitStr == "d")
      suit = 200;
    else if (suitStr == "s")
      suit = 300;
    else if (suitStr == "h")
      suit == 400;
    
    if (cardStr == "a")
      card = suit + 1;
    else if (cardStr == "j")
      card = suit + 11;
    else if (cardStr == "q")
      card = suit + 12;
    else if (cardStr == "k")
      card = suit + 13;
    else
      card = suit + stoi(cardStr);

    bstAlice.insert(card);
    if (card < minA)
      minA = card;
  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    
    int suit;
    int card;

    stringstream ss(line);
    string suitStr = "";
    getline(ss, suitStr, ' ');
    
    string cardStr = "";
    getline(ss, cardStr, ' ');
    
    if (suitStr == "c")
      suit = 100;
    else if (suitStr == "d")
      suit = 200;
    else if (suitStr == "s")
      suit = 300;
    else if (suitStr == "h")
      suit == 400;
    
    if (cardStr == "a")
      card = suit + 1;
    else if (cardStr == "j")
      card = suit + 11;
    else if (cardStr == "q")
      card = suit + 12;
    else if (cardStr == "k")
      card = suit + 13;
    else
      card = suit + stoi(cardStr);

    bstBob.insert(card);
    if (card > maxB)
        maxB = card;
  }
  cardFile2.close();
  
  while (bstAlice.playB(bstBob))
  {
    bstBob.playA(bstAlice);
  }

  while (bstBob.playA(bstAlice))
  {
    bstAlice.playB(bstBob);
  }
  return 0;
}