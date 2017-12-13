/* 
 * File:   main.cpp
 * Author: Drake Gerger
 * Created on December 11th, 2017, 8:00 PM
 * Purpose: Project 2
 */

//System Libraries
#include <iostream> //Input/Output Stream Library
#include <ctime>
#include <cstdlib>

using namespace std;    //Standard Name-space under which System Libraries reside

//User Libraries

//Global Constants - Not variables only Math/Science/Conversion constants

//Function Prototypes
void prob1();
void prob2();
void menu();
void menu2();
void prob3();
void prob4();
void prob5();
void prob6();
void Shuffle(bool CardsDealt[]);
void PrintCard(int Card);
void PrintHand(int Hand[], const int CardCount);
int GetNextCard(bool CardsDealt[]);
int ScoreHand(int Hand[], const int CardCount);
void PrintScoresAndHands(int HouseHand[], 
const int HouseCardCount, int PlayerHand[], const int PlayerCardCount);


//Execution Begins Here!
int main(int argc, char** argv) {
    //Declare Variables
    int choice;
    //Loop the Menu
    do{
        //Input Data/Variables
        menu();
        cout<<"> ";
        cin>>choice;
        //Process or map the inputs to the outputs
        switch(choice){
            case 1:prob1();break;
            case 2:prob2();break;
            default:{
                cout<<"Thank You for Playing!"<<endl;
            }
        }
    }while(choice>0&&choice<3);
    //Exit the program
    return 0;
}

void prob1(){
//Declare Variables
    
    int choice;
    //Loop the Menu and Problems
    do{
        //Input Data/Variables
        menu2();
        cout<<"> ";
        cin>>choice;
        //Process or map the inputs to the outputs
        switch(choice){
            case 1:prob3();break;
            case 2:prob4();break;
            case 3:prob5();break;
            case 4:prob6();break;
            default:{
                cout<<"Exiting to Main Menu!"<<endl;
            }
        }
    }while(choice>0&&choice<4);
    
}

void prob2(){
//Declare Variables
   
   	time_t cTime;
	time(&cTime);
	srand(cTime);
    
    int choice;
	bool CardsDealt[52];
	int HouseCardCount = 0;
	int HouseHand[12];
	int PlayerCardCount = 0;
	int PlayerHand[12];
    
	// Loop once for each hand
	while (true) {
		// randomize the cards; set them all to undealt
		Shuffle(CardsDealt);
		// Deal the hands. Get two cards for each
		PlayerHand[0]		= GetNextCard(CardsDealt);
		HouseHand[0]		= GetNextCard(CardsDealt);
		PlayerHand[1]		= GetNextCard(CardsDealt);
		HouseHand[1]		= GetNextCard(CardsDealt);
		HouseCardCount		= 2;
		PlayerCardCount	    	= 2;

		// Signal a new hand.
		cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
		cout << "$$$               Dealing New Hand...                $$$" << endl;
		cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
        cout << endl;

		char PlayerChoice;
		bool PlayerHits	= true;
		int PlayerScore	= ScoreHand(PlayerHand, PlayerCardCount);
		// Get Player's hits. Calculate the score and redisplay after each hit.
		do {
			// Print the dealt cards, but only the House's second card.
			cout << "House's Hand:" << endl;
			cout << "?? ";
			PrintCard(HouseHand[1]);
			cout << endl;
			cout << "Player's Hand: Score -> " << ScoreHand(PlayerHand, PlayerCardCount) << endl;
			PrintHand(PlayerHand, PlayerCardCount);
                        cout << endl;

			// Ask the Player whether he wants a hit or to stay
			cout << "Would you like to Hit(H) or Stay(S): ";
                        cin >> PlayerChoice;
                        cout <<"---------------------------------------"<<endl;

			if (PlayerChoice == 'H') {
				PlayerHand[PlayerCardCount] = GetNextCard(CardsDealt);
				++PlayerCardCount;
			} else if (PlayerChoice == 'S') {
				PlayerHits = false;
			
			} else {
			    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				cout << "*** PLEASE ENTER Hit(H) OR Stay(S)! ***" << endl;
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			}
			cout << endl;
			// Get the Player's current score to update and check for bust.
			PlayerScore	= ScoreHand(PlayerHand, PlayerCardCount);
		} while (PlayerHits && PlayerScore < 22);

		// Once the player is done taking hits, check whether he busted
		if (PlayerScore > 21) {
			// The Player busted. The House wins.
			cout << "$$$ The HOUSE WINS! $$$" << endl;
                        cout << endl;
			PrintScoresAndHands(HouseHand, HouseCardCount, PlayerHand, PlayerCardCount);
		} else {
			// If the player didn't bust, then the house takes hits below 17
			int HouseScore	= ScoreHand(HouseHand, HouseCardCount);
			while (HouseScore < 17) {
				HouseHand[HouseCardCount] = GetNextCard(CardsDealt);
				++HouseCardCount;
				HouseScore	= ScoreHand(HouseHand, HouseCardCount);
			}
			bool HouseBusts	= (HouseScore > 21);
			if (HouseBusts) {
				// The House busted. Player wins
				cout << "$$$ The PLAYER WINS! $$$" << endl;
                                cout << endl;
				PrintScoresAndHands(HouseHand, HouseCardCount, PlayerHand, PlayerCardCount);
			} else {
				// Compare scores and determine the winner
				if (PlayerScore == HouseScore) {
					// Tie. This is called a "push."
					cout << "$$$ Push! $$$" << endl;
					PrintScoresAndHands(HouseHand, HouseCardCount, PlayerHand, PlayerCardCount);
				} else if (PlayerScore > HouseScore) {
					// The Player wins
					cout << "$$$ The PLAYER WINS! $$$" << endl;
					PrintScoresAndHands(HouseHand, HouseCardCount, PlayerHand, PlayerCardCount);
				} else {
					// The House wins
					cout << "$$$ The HOUSE WINS! $$$" << endl;
					PrintScoresAndHands(HouseHand, HouseCardCount, PlayerHand, PlayerCardCount);
				}
			}
		}
	}
}

//------------------------------------------------------------------------------
//Function Calling
void menu(){
    //Input Data/Variables
    cout<<"______________________________________________________________"<<endl;
    cout<<"Choose from Menu by Typing Number Next to Where You Want to Go"<<endl;
    cout<<"1. How the Card Game BlackJack Works"<<endl;
    cout<<"2. Play the Game of BlackJack"<<endl;
    cout<<"0. Stop Playing the Program"<<endl;
    
}

void menu2(){
    //Input Data/Variables
    cout<<"______________________________________________________________"<<endl;
    cout<<"Choose from Menu by Typing Number Next to Where You Want to Go"<<endl;
    cout<<"1. Object of Blackjack"<<endl;
    cout<<"2. Rules of Blackjack"<<endl;
    cout<<"3. The Ranks of the Cards"<<endl;
    cout<<"4. Exit to Play Game"<<endl;
}
void prob3(){
    cout<<"The Object of Blackjack is:"<<endl;
    cout<<"To get 21 points on the player's first two cards without a dealer blackjack."<<endl;
    cout<<"Finally, reach a final score higher than the dealer without exceeding 21."<<endl;
    cout<<endl;
    
}
void prob4(){
        
        cout<<"Rules of Blackjack:"<<endl;
        cout<<"Players should then add up their cards and make a decision."<<endl;
        cout<<"“Hit” or “Stay” based on how much your cards add up too."<<endl;
        cout<<"Who ever has 21 or the close to 21 wins."<<endl;
        cout<<"There can also be a tie in which case no one wins or loses."<<endl;

}
void prob5(){
        
        const int SIZE = 9;
        int numbers[SIZE] = {2, 3, 4, 5, 6, 7, 8, 9, 10}; 
        
        cout<<"The Ranks of the Cards:"<<endl;
        cout << "All Number Cards are Valued According to their Number:"<<endl;
        for (int index = 0; index < SIZE; index++)
        cout << numbers[index] << " ";
        cout << endl;
        
    cout << "Face Cards are Valued at:"<<endl;    
        
        const int SIZES = 4;
        int number[SIZES] = {10, 10, 10, 11}; 
    
    cout << "Joker (J), Queen (Q), King (K), Ace (A) or 1"<<endl;
    for (int index = 0; index < SIZES; index++)
    {
        cout << number[index] << "         ";
    }
    cout<<endl;
}

void prob6(){

}

void Shuffle(bool CardsDealt[]) {
	for (int Index = 0; Index < 52; ++Index) {
		CardsDealt[Index] = false;
	}
}

void PrintCard(int Card) {
	using namespace std;
	// Print Rank
	const int Rank = (Card % 13);
	if (Rank == 0) {
		cout << 'A';
	} else if (Rank < 9) {
		cout << (Rank + 1);
	} else if (Rank == 9) {
		cout << 'T';
	} else if (Rank == 10) {
		cout << 'J';
	} else if (Rank == 11) {
		cout << 'Q';
	} else {
		cout << 'K';
	}
	// Print Suit
	const int Suit = (Card/13);
	if (Suit == 0) {
		cout << 'C';
	} else if (Suit == 1) {
		cout << 'D';
	} else if (Suit == 2) {
		cout << 'H';
	} else {
		cout << 'S';
	}
}

void PrintHand(int Hand[], const int CardCount) {
	using namespace std;
	for (int CardIndex = 0; CardIndex < CardCount; ++CardIndex) {
		const int NextCard = Hand[CardIndex];
		PrintCard(NextCard);
		cout << " ";
	}
	cout << endl;
}

int GetNextCard(bool CardsDealt[]) {
	bool CardDealt	= true;
	int NewCard	= -1;
	do {
		NewCard = (rand() % 52);
		if (!CardsDealt[NewCard]) {
			CardDealt = false;
		}
	} while (CardDealt);
	return NewCard;
}

int ScoreHand(int Hand[], const int CardCount) {
	int AceCount	= 0;
	int Score		= 0;
	for (int CardIndex = 0; CardIndex < CardCount; ++CardIndex) {
		const int NextCard = Hand[CardIndex];
		const int Rank = (NextCard % 13);
		if (Rank == 0) {
			++AceCount;
			++Score;
		} else if (Rank < 9) {
			Score = Score + (Rank + 1);
		} else {
			Score = Score + 10;
		}
	}
	while (AceCount > 0 && Score < 12) {
		--AceCount;
		Score = Score + 10;
	}
	return Score;
}

void PrintScoresAndHands(int HouseHand[], const int HouseCardCount, int PlayerHand[], const int PlayerCardCount) {
	using namespace std;
	cout << "House's Hand: Score -> " << ScoreHand(HouseHand, HouseCardCount) << endl;
	PrintHand(HouseHand, HouseCardCount);
	cout << "Player's Hand: Score -> " << ScoreHand(PlayerHand, PlayerCardCount) << endl;
	PrintHand(PlayerHand, PlayerCardCount);
	cout << endl;
}



