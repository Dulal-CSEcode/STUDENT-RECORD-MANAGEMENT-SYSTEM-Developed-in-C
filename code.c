#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

// Define the student structure to store student information.
struct student
{
    char ID[15];              // Student ID
    char name[20];            // Student name
    char add[20];             // Address of the student
    char parname[20];         // Parent's name
    int Class;                // Class of the student
    long unsigned int phone_no; // Phone number of the student
};

struct student stu;           // Declare a global student variable

/// Function to set the foreground color for printing in a console window.
void SetColor(int ForgC)
{
     WORD wColor;  // WORD is a 16-bit unsigned integer type.
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);  // Handle for standard output device.
     CONSOLE_SCREEN_BUFFER_INFO csbi;  // Struct to hold screen buffer info.

     // Get the current screen buffer info to retrieve the background color.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
        // Set the new foreground color without changing the background.
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);  // Apply the new color.
     }
     return;
}

/// Function to clear the console and set it to the specified foreground and background colors.
void ClearConsoleToColors(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);  // Combine colors.
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);  // Get handle to console.
     COORD coord = {0, 0};  // Start coordinates to clear from.
     DWORD count;  // Variable to store the number of characters written.
     CONSOLE_SCREEN_BUFFER_INFO csbi;  // Struct to hold buffer info.

     // Set the background and foreground color for the console.
     SetConsoleTextAttribute(hStdOut, wColor);
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          // Fill the console with spaces (clears it).
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
          // Set the color for each character.
          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
          SetConsoleCursorPosition(hStdOut, coord);  // Reset cursor position to top left.
     }
     return;
}

/// Function to set both foreground and background colors.
void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);  // Combine colors.
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);  // Apply the color.
     return;
}

/// This function allows positioning the cursor at (x, y) in the console window.
COORD coord = {0,0}; // Initialize coordinates to top-left (0, 0).
void gotoxy(int x, int y){
    coord.X = x; coord.Y = y; // Set new X and Y coordinates.
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);  // Move cursor.
}

/// Function to draw the border of the console window as a rectangle.
void drawRectangle()
{
    int i, j;
    gotoxy(0,0);  // Position cursor to top left corner.
    printf("%c",201);  // Print the top-left corner of the rectangle.
    for(i = 1; i < 78; i++)  // Draw the top border.
    {
        gotoxy(i, 0);
        printf("%c",205);  // Horizontal border character.
    }
    gotoxy(78,0);  // Position for top-right corner.
    printf("%c",187);  // Print the top-right corner.

    for(i = 1; i < 25; i++)  // Draw the vertical right border.
    {
        gotoxy(78, i);
        if(i == 6)  // At row 6, draw a special character.
        {
            printf("%c",185);
        }
        else
        {
            printf("%c",186);  // Vertical border character.
        }
    }

    gotoxy(78, 25);  // Position for bottom-right corner.
    printf("%c",188);  // Print bottom-right corner.
    
    // Drawing the bottom border.
    for(i = 77; i > 0; i--)
    {
        gotoxy(i,25);
        if(i == 35)
        {
            printf("%c",202);  // Special character at position 35.
        }
        else
        {
            printf("%c",205);  // Horizontal border character.
        }
    }
    
    gotoxy(0,25);  // Position for bottom-left corner.
    printf("%c",200);  // Print bottom-left corner.

    // Drawing the left border.
    for(i = 24; i > 0; i--)
    {
        gotoxy(0,i);
        if(i == 6)  // Special character at row 6.
        {
            printf("%c",204);
        }
        else
        {
            printf("%c",186);  // Vertical border character.
        }
    }

    // Draw the horizontal separator in the middle of the window.
    for(i = 1; i < 78; i++)
    {
        gotoxy(i,6);
        if(i == 35)  // Special character at position 35.
        {
            printf("%c",203);
        }
        else
        {
            printf("%c",205);  // Horizontal border character.
        }
    }

    // Drawing the vertical separator between columns.
    for(i = 7; i < 25; i++)
    {
        gotoxy(35,i);
        printf("%c",186);  // Vertical border character.
    }
}

/// Function to clear the content inside the rectangle (except the border).
void clearWindow(){
    int i,j;
    for(i = 37; i < 78; i++){  // From column 37 to 78 (inside the border).
        for(j = 7; j < 25; j++){  // From row 7 to 25 (inside the border).
            gotoxy(i,j); printf(" ");  // Replace content with space (clears it).
        }
    }
    return;
}

/// Function to display a window with a heading.
void window()
{
    drawRectangle();  // Draw the border of the window.
    gotoxy(28,2);  // Position cursor for title.
    SetColor(35);  // Set color for title.
    printf("STUDENT RECORD SYSTEM");  // Print the title.
    gotoxy(24,3);  // Position for sub-title.
    printf("GREEN UNIVERSITY OF BANGLADESH");  // Print sub-title.
    gotoxy(31,4);  // Position for establishment date.
    printf("Estd.: 2003 B.S.");  // Print establishment date.
    gotoxy(25,24);  // Position for bottom message.
    SetColor(17);  // Reset color.
}

/// Function to get a password from the user input, masking the characters with '*'.
void get_password(char* pass)
{
    char temp_passP[25];  // Temporary buffer to store the password.
    int i=0;  // Index for the password array.
    while(1)  // Infinite loop to get password input.
    {
        temp_passP[i]=getch();  // Get character input without echoing it on the screen.
        if(temp_passP[i]==13)  // Check if 'Enter' key is pressed.
        {
            break;
        }
        else if(temp_passP[i]==8)  // Check if 'Backspace' is pressed.
        {
            if(i!=0) {
                printf("\b \b");  // Remove the last character.
                i--;
            } else {
                printf("\a");  // Beep if no characters to delete.
            }
        }
        else
        {
            printf("*");  // Print '*' for every typed character.
            *(pass+i) = temp_passP[i];  // Add character to the password.
            i++;
        }
        *(pass+i)='\0';  // Null-terminate the password string.
     }
}
