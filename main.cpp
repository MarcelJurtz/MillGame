#include <iostream>
#include <string>
using namespace std;

// TODOs:
// - Buchstaben können für Positionsangaben verwendet werden -> Programm crasht

const string PLAYER_1 = "W";
const string PLAYER_2 = "S";

string currentPlayer = PLAYER_1;
int stonesPlayer1 = 9;
int stonesPlayer2 = 9;

// Gültige Schiebezüge pro Spielfeldposition
const int validMoves[24][4] = {
    { 1, 9, -1, -1 },   // 0
    { 0, 2, 4, -1 },    // 1
    { 1, 14, -1, -1},   // 2
    { 4, 10, -1, -1 },  // 3
    { 1, 3, 5, 7 },     // 4
    { 4, 13, -1, -1 },  // 5
    { 11, 7, -1, -1 },  // 6
    { 4, 6, 8, -1 },    // 7
    { 7, 12, -1, -1 },  // 8
    { 0, 10, 21, -1 },  // 9
    { 3, 9, 15, 11},    // 10
    { 6, 15, 10, -1 },  // 11
    { 8, 13, 17, -1 },  // 12
    { 5, 12, 20, 14 },  // 13
    { 2, 23, 13, -1 },  // 14
    { 11, 16, -1, -1 }, // 15
    { 15, 17, 19, -1},  // 16
    { 12, 16, -1, -1},  // 17
    { 10, 19, -1, -1},  // 18
    { 16, 18, 20, 22},  // 19
    { 13, 19, -1, -1},  // 20
    { 9, 22, -1, -1},   // 21
    { 21, 19, 23, -1},  // 22
    { 13, 22, -1, -1 }  // 23
};

string state[24] = {
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
    "0",
};

string boardIndices[24] = {"00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23"};

void printGameBoard() 
{
    string indices[13][13] = {
        {boardIndices[0], "----", "-", "----", "-", "----", boardIndices[1], "----", "-", "----", "-", "----", boardIndices[2]},
        {"|", "    ", " ", "    ", " ", "     ", "|", "    ", " ", "    ", " ", "      ", "|"},
        {"|", "    ", boardIndices[3], "----", "-", "----", boardIndices[4], "----", "-", "----", boardIndices[5], "    ", "|"},
        {"|", "    ", "|", "    ", " ", "     ", "|", "    ", " ", "      ", "|", "    ", "|"},
        {"|", "    ", "|", "    ", boardIndices[6], "----", boardIndices[7], "----", boardIndices[8], "    ", "|", "    ", "|"},
        {"|", "    ", "|", "    ", "|", "    ", " ", "       ", "|", "    ", "|", "    ", "|"},
        {boardIndices[9], "---", boardIndices[10], "---", boardIndices[11], "      ", " ", "   ", boardIndices[12], "---", boardIndices[13], "---", boardIndices[14]},
        {"|", "    ", "|", "    ", "|", "    ", " ", "       ", "|", "    ", "|", "    ", "|"},
        {"|", "    ", "|", "    ", boardIndices[15], "----", boardIndices[16], "----", boardIndices[17], "    ", "|", "    ", "|"},
        {"|", "    ", "|", "    ", " ", "     ", "|", "    ", " ", "      ", "|", "    ", "|"},
        {"|", "    ", boardIndices[18], "----", "-", "----", boardIndices[19], "----", "-", "----", boardIndices[20], "    ", "|"},
        {"|", "    ", " ", "    ", " ", "     ", "|", "    ", " ", "    ", " ", "      ", "|"},
        {boardIndices[21], "----", "-", "----", "-", "----", boardIndices[22], "----", "-", "----", "-", "----", boardIndices[23]}};

    string currentState[13][13] = {
        {state[0], "----", "-", "----", "-", "----", state[1], "----", "-", "----", "-", "----", state[2]},
        {"|", "    ", " ", "    ", " ", "    ", "|", "    ", " ", "    ", " ", "    ", "|"},
        {"|", "    ", state[3], "----", "-", "----", state[4], "----", "-", "----", state[5], "    ", "|"},
        {"|", "    ", "|", "    ", " ", "    ", "|", "    ", " ", "    ", "|", "    ", "|"},
        {"|", "    ", "|", "    ", state[6], "----", state[7], "----", state[8], "    ", "|", "    ", "|"},
        {"|", "    ", "|", "    ", "|", "    ", " ", "    ", "|", "    ", "|", "    ", "|"},
        {state[9], "----", state[10], "----", state[11], "    ", " ", "    ", state[12], "----", state[13], "----", state[14]},
        {"|", "    ", "|", "    ", "|", "    ", " ", "    ", "|", "    ", "|", "    ", "|"},
        {"|", "    ", "|", "    ", state[15], "----", state[16], "----", state[17], "    ", "|", "    ", "|"},
        {"|", "    ", "|", "    ", " ", "    ", "|", "    ", " ", "    ", "|", "    ", "|"},
        {"|", "    ", state[18], "----", "-", "----", state[19], "----", "-", "----", state[20], "    ", "|"},
        {"|", "    ", " ", "    ", " ", "    ", "|", "    ", " ", "    ", " ", "    ", "|"},
        {state[21], "----", "-", "----", "-", "----", state[22], "----", "-", "----", "-", "----", state[23]}};

    // Ausgeben beider Felder
    for (int j = 0; j < 13; j++) 
    {
        for (int i = 0; i < 13; i++)
        {
            cout << currentState[j][i];
        }
        cout << "    -    ";
        for (int k = 0; k < 13; k++)
        {
            cout << indices[j][k];
        }
        cout << endl;
    }
}

bool isMill(int index1, int index2, int index3)
{
    return state[index1] == state[index2] && state[index2] == state[index3];
}

bool stoneIsInMill(int index)
{
    switch (index)
    {
        case 0:            
            return isMill(0, 1, 2) || isMill(0, 9, 21);
        case 1:            
            return isMill(0, 1, 2) || isMill(1,4,7);
        case 2:
            return isMill(0, 1, 2) || isMill(2, 14, 23);            
        case 3:
            return isMill(3,4,5) || isMill(3,10,18);            
        case 4:
            return isMill(3,4,5) || isMill(1,4,7);
        case 5:
            return isMill(3,4,5) || isMill(5,13,20);            
        case 6:       
            return isMill(6,7,8) || isMill(6,11,15);
        case 7:
            return isMill(6,7,8) || isMill(1,4,7);
        case 8:
            return isMill(6,7,8) || isMill(8,12,17);            
        case 9:
            return isMill(9,10,11) || isMill(0,9,21);
        case 10:
            return isMill(9,10,11) || isMill(3,10,18);            
        case 11:
            return isMill(9,10,11) || isMill(6,11,15);            
        case 12:
            return isMill(12,13,14) || isMill(8,12,17);            
        case 13:
            return isMill(12,13,14) || isMill(5,13,20);            
        case 14:
            return isMill(12,13,14) || isMill(2,14,23);
        case 15:    
            return isMill(15,16,17) || isMill(6,11,15);
        case 16:
            return isMill(15,16,17) || isMill(16,19,22);
        case 17:
            return isMill(15,16,17) || isMill(8,12,17);
        case 18:
            return isMill(18,19,20) || isMill(3,10,18);
        case 19:
            return isMill(18,19,20) || isMill(16,19,22);
        case 20:
            return isMill(18,19,20) || isMill(5,13,20);
        case 21:
            return isMill(21,22,23) || isMill(0,9,21);
        case 22:
            return isMill(21,22,23) || isMill(16,19,22);            
        case 23:
            return isMill(21,22,23) || isMill(2,14,24);            
        default:            
            cout << "Error, bad input, quitting\n";
            break;
    }
}

void removeOpponentStone() {
    while(true)
    {
        cout << "Welcher Stein soll entfernt werden? ";
        int position;
        cin >> position;

        string opponent = currentPlayer == PLAYER_1 ? PLAYER_2 : PLAYER_1;
        if(position > 0 && position < 24 && state[position] == opponent && !stoneIsInMill(position))
        {
            // TODO Nur entfernen, wenn Stein nicht selbst in einer Mühle liegt
            state[position] = "0";
            printGameBoard();
            break;
        }
    }
}

void checkMill(int index)
{
    if(stoneIsInMill(index))
    {
        removeOpponentStone();
    }   
}

int main()
{
    cout << "\nSpielfeldkoordinaten mit Array: \n\n";
    cout << "\nSpielfeld\n";

    printGameBoard();

    int position;

    // Setzphase
    while(true)
    {
        bool player1CanMove = currentPlayer == PLAYER_1 && stonesPlayer1 > 0;
        bool player2CanMove = currentPlayer == PLAYER_2 && stonesPlayer2 > 0;

        if(!player1CanMove && !player2CanMove) 
        {
            break;
        }

        // Gültigkeit der Position prüfen
        while(true) {
            // Nr des nächsten Steins des aktuellen Spielers
            int nextStoneNumber = 9 - (currentPlayer == PLAYER_1 ? stonesPlayer1 : stonesPlayer2) + 1;

            cout << "\nSpieler " << currentPlayer << " setzen Sie Ihren " << nextStoneNumber << ". Stein: ";
            cin >> position;

            if(position >= 0 && position <= 23 && state[position] == "0") 
            {
                state[position] = currentPlayer;
                if(currentPlayer == PLAYER_1) 
                {
                    stonesPlayer1--;
                } 
                else 
                {
                    stonesPlayer2--;
                }
                break;
            } 
            else
            {
                cout << "Ungültige Positionsangabe.";
            }
        }

        printGameBoard();

        // Prüfung auf neue Mühle
        checkMill(position);

        // Aktuellen Spieler umschalten für nächsten Spielzug
        currentPlayer = currentPlayer == PLAYER_1 ? PLAYER_2 : PLAYER_1;
    }

    // Schiebephase & Sprungphase
    bool gameover = false;
    while(!gameover)
    {
        // Anzahl Steine aktueller Spieler
        int stones = 0;
        for(int i = 0; i < 24; i++) 
        {
            if(state[i] == currentPlayer) 
            {
                stones++;
            }
        }

        if(stones >= 3) 
        {
            // Schiebephase
            //MS 1 für Weiss und 2 für Schwarz
            int position;
            while(true)
            {
                cout << "Spieler " << currentPlayer << ", wähle einer deiner eigenen Spielsteine für die Schiebephase aus: ";
                cin >> position;

                if(state[position] == currentPlayer) 
                {
                    // Prüfe, ob Nachbarfeld gültig und frei ist
                    int neightborValidMoves = 0;
                    for(int i = 0; i < 4; i++) {
                        int neightborIndex = validMoves[position][i];
                        if(neightborIndex != -1 && state[neightborIndex] == "0") {
                            neightborValidMoves++;
                        }
                    }
                    
                    // Mindestens auf ein Nachbarfeld könnte geschoben werden
                    if(neightborValidMoves > 0) {
                        break;
                    }
                } 

                cout << "Ungültige Positionsangabe";
            }
            
            int targetPosition;
            while(true)
            {
                cout << "\nWohin möchten Sie den Stein verschieben? ";
                cin >> targetPosition;

                if(state[targetPosition] == "0") 
                {
                    // Ist die angegebene Position ein gültiger Nachbar
                    bool isCurrentNeighbor = false;
                    for(int i = 0; i < 4; i++) {
                        int neightborIndex = validMoves[position][i];
                        if(neightborIndex == targetPosition) {
                            isCurrentNeighbor = true;
                        }
                    }

                    if(isCurrentNeighbor)
                    {
                        break;
                    }
                } 
                
                cout << "Ungültige Positionsangabe";
            }
            
            state[position] = "0";
            state[targetPosition] = currentPlayer;

            // Prüfung auf neue Mühle
            checkMill(targetPosition);
        }
        else if(stones == 3) 
        {
            // Sprungphase
            int position;
            int targetPosition;

            while(true) 
            {
                cout << "Spieler " << currentPlayer << ", wähle einer deiner eigenen Spielsteine für die Sprungphase aus";
                cin >> position;

                if(position >= 0 && position < 24 && state[position] == currentPlayer) 
                {
                    break;
                }
            }

            while(true) 
            {
                cout << "\nWohin möchten Sie springen?";
                cin >> targetPosition;

                if(state[targetPosition] == "0") 
                {
                    break;
                }

                cout << "Ungültige Positionsangabe";
            }

            state[position] = "0";
            state[targetPosition] = currentPlayer;

            // Prüfung auf neue Mühle
            checkMill(targetPosition);
        }
        else
        {
            // Fertig
            cout << "Spieler " << (currentPlayer == PLAYER_1 ? PLAYER_2 : PLAYER_1) << " hat gewonnen";
            gameover = true;
        }

        // Aktuellen Spieler umschalten für nächsten Spielzug
        currentPlayer = currentPlayer == PLAYER_1 ? PLAYER_2 : PLAYER_1;
    } 

    // Fertig
    return 0;
}
