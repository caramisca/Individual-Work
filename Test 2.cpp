#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void drawHangman(int attempt, int winner) {
    setcolor(WHITE);
    line(100, 100, 100, 300);
    line(50, 300, 150, 300);
    line(100, 100, 200, 100);
    line(200, 100, 200, 150);
    line(200, 150, 200, 170);

    if (attempt >= 1) {
        circle(200, 190, 20);
    }

    if (attempt >= 2) {
        line(200, 210, 200, 260);
    }

    if (attempt >= 3) {
        line(200, 230, 180, 220);
    }

    if (attempt >= 4) {
        line(200, 230, 220, 220);
    }

    if (attempt >= 5) {
        line(200, 260, 180, 280);
    }

    if (attempt >= 6) {
        line(200, 260, 220, 280);
        setcolor(RED);
        circle(194, 185, 2); 
        circle(206, 185, 2); 
        arc(200, 205, 40, 140, 13);
    }
    
    if (winner >= 1) {
        setcolor(YELLOW);
        circle(194, 185, 2); 
        circle(206, 185, 2); 
        arc(200, 190, 200, 340, 13); 
    }
}

void removeChar(char* str, char c) {
    int n = strlen(str);
    int j=0;
    for (int i = 0; i < n; i++)
    {
    	 if (str[i] != c)
            str[j++] = str[i];   
	}
        
        str[j] = '\0';
}

void drawProgress(char hangmanOutput[100]){
	setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
    int x = 200;
    int y = 350;

    for (int i = 0; hangmanOutput[i] != '\0'; ++i) {
        char letter = hangmanOutput[i];
        char buffer[2] = { letter, '\0' };
        outtextxy(x, y, buffer);
        x += 30;
    }	
}

void drawAvailableLetters( char availableLetters[], char alphabetFromUser) {
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(300, 100, "Available Letters:");
    int x = 300;
    int y = 150;
    int j = 1;	
 
    for (int i = 0; i<strlen(availableLetters); i++) {
        char letter = availableLetters[i];
        if (letter != alphabetFromUser) {
            char buffer[2] = { letter, '\0' };
            outtextxy(x, y, buffer);
            if (j % 5 == 0)
                y += 30, x = 270;
            j++;
            x += 30;
        } 
		
    }
}

int playGame(const char* hangmanWord) {
    char availableLetters[] = "abcdefghijklmnopqrstuvwxyz";
    int attempt = 0;
    int length = strlen(hangmanWord);
    char tempWord[100];
    int wrongTry = 6;
    int matchFound = 0;
    int position = 0;
    int winner = 0;
    char hangmanOutput[100];
    for (int i = 0; i < length; i++) {
        hangmanOutput[i] = '_';
    }
    hangmanOutput[length] = '\0';

    system("cls");
    printf("\n\n Welcome to the HANGMAN GAME!");
    printf("\n\n You will get %d chances to guess the right word", wrongTry);
    _getch();
    system("cls");

    while (wrongTry > 0) {
    	   cleardevice();
        system("cls");
        drawHangman(attempt, winner);
        drawProgress(hangmanOutput);
        drawAvailableLetters(availableLetters, '\0');  
        int matchFound = 0;

        printf("\n\n The word has %d letters \n\n", length);
        printf(" Enter any letter from a to z using small case!!");
        printf("\n\n Number of errors: %d", attempt);
        printf("\n\n Current Progress: %s", hangmanOutput);
        printf("\n\n Enter HERE ==> ");
        char alphabetFromUser;
        scanf(" %c", &alphabetFromUser);
        
        for (int i = 0; i < strlen(availableLetters); i++){
        	if (availableLetters[i] == alphabetFromUser)
				removeChar(availableLetters, alphabetFromUser);	
		}
		

    	cleardevice();
        drawHangman(attempt, winner);
        drawProgress(hangmanOutput);
        drawAvailableLetters(availableLetters, '\0'); 

        if (!isalpha(alphabetFromUser)) {
            printf("\033[0;31m");       	        	
            printf("\n Invalid input. Please enter a letter.\n");
            printf("\033[0m");
			_getch();
            continue;
        }

        for (int counter = 0; counter < length; counter++) {
            if (alphabetFromUser == hangmanWord[counter]) {
                matchFound = 1;
                position = counter;
            }
        }
        
        if (matchFound == 0) {
        	attempt++;
            drawHangman(attempt, winner);
            printf("\033[0;31m");
            printf("\n You have %d tries left ", --wrongTry);
            printf("\033[0m");
            drawAvailableLetters(availableLetters, alphabetFromUser);
 
        } else {
            for (int counter = 0; counter < length; counter++) {
                if (alphabetFromUser == hangmanWord[counter]) {
                    position = counter;
                    matchFound = 1;
                }

                if (matchFound == 1) {
                    for (int i = 0; i < length; i++) {
                        if (i == position) {
                            hangmanOutput[i] = alphabetFromUser;
                        } else if (hangmanOutput[i] >= 'a' && hangmanOutput[i] <= 'z') {
                            continue;
                        } else {
                            hangmanOutput[i] = '_';
                        }
                    }
                    drawProgress(hangmanOutput);
                    //removeChar(availableLetters, alphabetFromUser);
                    drawAvailableLetters(availableLetters, alphabetFromUser);
                    tempWord[position] = alphabetFromUser;
                    tempWord[length] = '\0';
                    winner = strcmp(tempWord, hangmanWord);

                    if (winner == 0) {
                        system("cls");
                        winner++;
                        drawHangman(attempt, winner);
                        printf("\n Congratulations! ");
                        printf("\n\n The Word was");
                        printf("\033[0;32m %s", hangmanWord);
                        printf("\n\n You SAVED the man!");
                        printf("\033[0m");
                        _getch();
                        return 0;
                    }
                }
            }
        }
        printf("\n\n");
        for (int i = 0; i < length; i++) {
            printf(" ");
            printf("%c", hangmanOutput[i]);
        }
        printf("\n\n");
        system("pause");
    }

    system("cls");
    drawHangman(attempt, winner);
    printf("\n\n The Word was");
    printf("\033[0;31m %s", hangmanWord);
    printf("\n\n The man is DEAD");  
    printf("\033[0m");
    _getch();

    return 1;
}

void SingleplayerGame(int attempt) {
    const char* difficultyWords[][5] = {
        {"apple", "banana", "orange", "grape", "pear"},
        {"elephant", "giraffe", "rhinoceros", "hippopotamus", "crocodile"},
        {"programming", "algorithm", "variable", "function", "array"},
        {"university", "education", "knowledge", "learning", "student"},
        {"mountain", "river", "forest", "ocean", "desert"}
    };

    int difficulty;
    while (1) {
        printf("Choose difficulty level (1-5):\n");

        if (scanf("%d", &difficulty) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');  
            continue;  
        }

        if (difficulty < 1 || difficulty > 5) {
            printf("Invalid difficulty level. Please enter a number between 1 and 5.\n");
            continue;  
        }
        break;  
	}
	
    const char* hangmanWord = difficultyWords[difficulty - 1][rand() % 5];
    playGame(hangmanWord);
}

int isAlphaString(const char* str) {
    while (*str) {
        if (!isalpha(*str)) {
            return 0; 
        }
        str++;
    }
    return 1; 
}

void MultiplayerGame(int attempt) {
    char hangmanWord[100];
    system("cls");
    printf("\n\n Enter any word in small case and hit >>ENTER<<");
    printf("\n\n Enter HERE ==>  ");
    scanf("%s", hangmanWord);
    if (!isAlphaString(hangmanWord)) {
        printf("\033[0;31mInvalid input! Please enter a word with only alphabetical characters.\n\033[0m");
        _getch();
        return;
    }
    playGame(hangmanWord);
}

int main() {
	unsigned seed = (unsigned int)(GetCurrentProcessId());
	srand(seed);
    while (1) {
        system("cls");
        int choice;
        printf("\033[0;33m                              HANGMAN GAME                             \033[0m\n");
        printf("What mode would you like to play?(1 for singleplayer/2 for multiplayer)\n");
        choice = _getch();
        switch (choice) {
	        case 49: {
	            int gd = DETECT, gm;
	            initgraph(&gd, &gm, " ");
	            int attempt = 0;
	            SingleplayerGame(attempt);
	            closegraph();
	            break;
	        }
	        case 50: {
	            int gd = DETECT, gm;
	            initgraph(&gd, &gm, " ");
	            int attempt = 0;
	            MultiplayerGame(0);
	            closegraph();
	            break;
	        }
	        case 27: {
	            closegraph();
	            return 0;
	            break;
	        }
	        default: {
	            system("cls");
	            printf("\n\033[0;31m Wrong Input\033[0m");
	            _getch();
	            break;
	        }
        }
    }
}