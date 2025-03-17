/** \file main.cpp
 *  \brief Shape Generator
 *  \details In this program we prompt the user to enter an option they want from a menu and then we generate the desired shape for the user. If they want random shapes, then we generate an x amount of random shapes.
 *  \author Marios Kyriacou
 *  \version 0.1
 *  \date 2025-2025
 *  \copyright GNU Public License.
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

// Global Constants
#define MAX_SHAPES 10

// Function prototypes
void drawHorizontalLine(int, char) ;
void drawVerticalLine(int, char);
void drawSquare(int, char, bool);
void drawSquareFilled(int, char);
void drawRectangle(int, int, char, bool);
void drawRectangleFilled(int, int, char);
bool dataValidation(int, int);
void drawShapes(int);
void initializeArrays(int[], int[], char[], int);
void drawArrays(int[], int[], char[], int);

/**
 * We show the menu to the user, get the option that the user wants and then prompt them to enter the desired data
 * @return Returns 0
 */
int main() {
    srand(time(NULL));
    // Variable declarations
    int choice, arrSize, shapeTy[MAX_SHAPES], shapeLen[MAX_SHAPES];
    char character, shapeCh[MAX_SHAPES];
    bool isValid, isActive = true;
    
    // Continuously loop until the user selects to terminate the program
    do {
        // User Option Menu
        cout << "1) Draw a horizontal line" << endl;
        cout << "2) Draw a vertical line" << endl;
        cout << "3) Draw a square" << endl;
        cout << "4) Draw a rectangle" << endl;
        cout << "5) Draw random shapes" << endl;
        cout << "6) Random Shapes (w/ 2 functions)" << endl;
        cout << "7) Quit" << endl;
        
        // Prompt user to enter a choice
        cout << "Enter your option: ";
        cin >> choice;
        
        // Data validation from user. If it isn't valid prompt them to enter a choice until it is valid
        while(choice > 7 || choice < 1) {
            cout << "I need a choice between 1 and 6. If you want to quit enter 6: ";
            cin >> choice;
        }
        
        assert(choice <= 7 && choice >= 1);
        
        // Switch function to choose the correct choice
        switch(choice) {
            // If the choice is 1 through 3, get the size and the character and validate the size so it's positive
            // if it isn't, request a positive number until one is entered.
            case 1:
            case 2:
            case 3:
                // Temporary variable declarations
                int size;
                
                // Prompt user to enter the size and the character
                cout << "Enter the size and the character you want the shape to be: ";
                cin >> size >> character;
                
                // Validate the size
                isValid = dataValidation(size, 1);
                
                // If it is not valid request a new number, otherwise run the correct function
                while(!isValid) {
                    cout << "Please enter a size that is positive! ";
                    cin >> size;
                    
                    // Validate size again
                    isValid = dataValidation(size, 1);
                }
                
                // Run the corresponding function
                if(isValid) {
                    if(choice == 1) drawHorizontalLine(size, character);
                    if(choice == 2) drawVerticalLine(size, character);
                    if(choice == 3) drawSquare(size, character, false);
                }
                
                break;
            case 4:
                int width, height;
                
                cout << "Enter the width, height and the character you want the shape to be: ";
                cin >> width >> height >> character;
                
                isValid = dataValidation(width, height);
                
                // If it is not valid request a new number, otherwise run the correct function
                while(!isValid) {
                    cout << "Please enter a width and height that is positive! ";
                    cin >> width >> height;
                    
                    // Validate size again
                    isValid = dataValidation(width, height);
                }
                
                // Run the corresponding function
                if(isValid) {
                    drawRectangle(width, height, character, false);
                }
                
                break;
            // Draw a random amount (between 1 and MAX_SHAPES) of random shapes
            case 5:
                drawShapes(rand() % MAX_SHAPES + 1);
                
                break;
            // Call the initializeArray() function and pass the arrSize function
            case 6:
                // Random number from 1-10
                arrSize = rand() % 10 + 1;
                
                initializeArrays(shapeTy, shapeLen, shapeCh, arrSize);
                
                break;
            // If they want to exit it breaks automatically and shows "Have a good day!"
            case 7:
            default:
                isActive = false;
                break;
        }
    } while(isActive);
    
    cout << "Have a good day!" << endl;
    
    return 0;
}

/**
  * Loop from 0 to the desired length and output the character in one straight line. Once it ends add a new line
  * @param length The length variable is the desired length of the line that the user wants to output
  * @param ch The ch variable is the desired character that they want the shape to have
 */
void drawHorizontalLine(const int length, const char ch) {
    assert(length > 0);
    
    for(int i = 0; i < length; i++) {
        cout << ch;
    }
    
    cout << endl;
}

/**
  * Loop from 0 to the desired height and output a character in each line. Once it ends add a new line
  * @param height The height variable is the desired length of the line that the user wants to output
  * @param ch The ch variable is the desired character that they want the shape to have
 */
void drawVerticalLine(const int height, const char ch) {
    assert(height > 0);
    
    for(int i = 0; i < height; i++) {
        cout << ch << endl;
    }
    
    cout << endl;
}

/**
  * Create a square with the desired size. The boolean filled is so it checks if it wants it filled or not. The boolean will be <code>false</code> if it wasn't called by the user, hence the shape will not be filled. If the function gets called from the random shape generator then it gets the default state of not-filled.
  * @param size The size variable is both the width and height of the square
  * @param ch The ch variable is the desired character that they want the shape to have
  * @param filled Checks if the function has been called from the random number generator or from the user
 */
void drawSquare(const int size, const char ch, const bool filled){
    assert(size > 0);
    
    char tempAns;
    
    if(!filled) {
        // Prompt user to ask them if they want the square filled or empty
        cout << "Would you like a filled square (y/n)? ";
        cin >> tempAns;
        
        // Data validation for yes and no
        while(tempAns != 'y' && tempAns != 'n') {
            cout << tempAns;
            cout << "Please enter y or n: ";
            cin >> tempAns;
        }
    }
    
    // If the answer is y then draw a filled square otherwise draw an empty square
    if(tempAns == 'y') drawSquareFilled(size, ch);
    else {
        // Loop through the size. If it's the first row, draw the whole row. Any other row, draw a character add a space of
        // size - 1 (setw starts from 1, so we remove 1 from size) and add another character
        for(int i = 0; i < size; i++) {
            if(i == 0 || i == size - 1) {
                for(int j = 0; j < size; j++) {
                    cout << ch;
                }
                cout << endl;
            } else {
                cout << ch << setw(size - 1) << ch;
                cout << endl;
            }
        }
        
        cout << endl;
    }
}

/**
  * Draw a filled square on the users screen
  * @param size The size variable is both the width and height of the square
  * @param ch The ch variable is the desired character that they want the shape to have
 */
void drawSquareFilled(const int size, const char ch){
    assert(size > 0);
    
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            cout << ch;
        }
        cout << endl;
    }
    
    cout << endl;
}

/**
  * Display the desired rectangle dimensions (i = height, j = length). At the end add a new line. The boolean will be <code>false</code> if it wasn't called by the user, hence the shape will not be filled. If the function gets called from the random shape generator then it gets the default state of not-filled.
  * @param height The height variable is the height of the rectangle
  * @param length The length variable is the length of the rectangle
  * @param ch The ch variable is the desired character that they want the shape to have
  * @param filled The filled variable is in order for us to know if the function was called by a user or not
 */
void drawRectangle(const int height, const int length, const char ch, const bool filled){
    assert(height > 0 && length > 0);
    
    // Temporary Variables
    char tempAns;
    
    if(!filled) {
        // Prompt user to ask them if they want the square filled or empty
        cout << "Would you like a filled square (y/n)? ";
        cin >> tempAns;
        
        // Data validation for yes and no
        while(tempAns != 'y' && tempAns != 'n') {
            cout << tempAns;
            cout << "Please enter y or n: ";
            cin >> tempAns;
        }
    }
    
    // Loop through the size. If it's the first row, draw the whole row. Any other row, draw a character add a space of
    // length - 1 (setw starts from 1, so we remove 1 from size) and add another character
    if(tempAns == 'y') drawRectangleFilled(height, length, ch);
    else {
        for(int i = 0; i < height; i++) {
            if(i == 0 || i == height - 1) {
                for(int j = 0; j < length; j++) {
                    cout << ch;
                }
            } else {
                cout << ch << setw(length - 1) << ch;
            }
            
            cout << endl;
        }
    }
    
    cout << endl;
}

/**
  * Draw a filled rectangle with the desired height and length
  * @param height The height variable is the height of the rectangle
  * @param length The length variable is the length of the rectangle
  * @param ch The ch variable is the desired character that they want the shape to have
 */
void drawRectangleFilled(const int height, const int length, const char ch){
    assert(height > 0 && length > 0);
    
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < length; j++) {
            cout << ch;
        }
        
        cout << endl;
    }
}

/**
  * This function validates the data entered by the user in order to check if the numbers they have entered are more than 0 (because shapes require a positive value)
  * @param num1 The num1 variable is either the height or the length of the shape
  * @param num2 The num2 variable is either the height or the length of the shape
  * @return It will return <code>true</code> if both the numbers are >0 and <code>false</code> if either number is <0
 */
bool dataValidation(const int num1, const int num2) {
    assert(num1 > 0 && num2 > 0);
    
    if(num1 > 0 && num2 > 0) return true;
    
    return false;
}

/**
  * Generate random numbers and get a random shape with a random width (and height), with a random character, numShapes number of times. For each shapeType call the correct function using a switch statement.
  * @param numShapes The numShapes variable is the amount of random shapes that gets generated in the main function
 */
void drawShapes(const int numShapes) {
    assert(numShapes > 0 && numShapes <= 10);
    
    // ShapeType: Generate a number from 0 to 5 and add 1 (so range will become 1-6)
    // ShapeLength && ShapeHeight: Have an offset of 5 and generate a random number between 0-15. Range will become 5-20
    // ShapeCharacter: Have an offset of 33 and generate a random number between 0 and 93
    
    for(int i = 0; i < numShapes; i++) {
        int shapeType = rand() % 6 + 1, shapeLength = 5 + ( rand() % 16 ), shapeHeight = 5 + ( rand() % 16 ), shapeCharacter = 33 + ( rand() % 94 );
        
        switch(shapeType) {
            case 1:
                drawHorizontalLine(shapeLength, shapeCharacter);
                
                break;
            case 2:
                drawVerticalLine(shapeLength, shapeCharacter);
                
                break;
            case 3:
                drawSquareFilled(shapeLength, shapeCharacter);
                
                break;
            case 4:
                drawSquare(shapeLength, shapeCharacter, true);
                
                break;
            case 5:
                drawRectangle(shapeHeight, shapeLength, shapeCharacter, true);
                
                break;
            default:
                drawRectangleFilled(shapeHeight, shapeLength, shapeCharacter);
                
                break;
        }
    }
}

/**
 * This function will initialize the arrays with random values
 * @param shapeTy The shapeTy generates a random value from 1-6, arrSize number of times, to indicate which shape type to print
 * @param shapeLen The shapeLen variable generates a random value from 1-20, arrSize number of times, to see the length of the shape
 * @param shapeCh The shapeCh variable generates a random value (ASCII) from 33-126, arrSize number of times, in order to show it as the character of the shape
 * @param arrSize The arrSize variable is a random value between 1-10 that will be the amount of values that will be generated for the arrays
*/
void initializeArrays(int shapeTy[], int shapeLen[], char shapeCh[], const int arrSize) {
    assert(arrSize >= 1 && arrSize <= 10);
    
    for(int i = 0; i < arrSize; i++) {
        shapeTy[i] = rand() % 6 + 1;
        assert(shapeTy[i] >= 1 && shapeTy[i] <= 6);
        
        shapeLen[i] = rand() % 20 + 1;
        assert(shapeLen[i] >= 1 && shapeLen[i] <= 20);
        
        shapeCh[i] = (char)(33 + (rand() % 94));
        assert(shapeCh[i] >= 33 && shapeCh[i] <= 126);
    }
    
    drawArrays(shapeTy, shapeLen, shapeCh, arrSize);
}

/**
 * In this function, we will draw the values that have been added to the variables in the <code>initializeArrays()</code> function
 * @param shapeTy The shapeTy variable has random values from 1-6, arrSize number of times, to indicate which shape type to print
 * @param shapeLen The shapeLen variable has random values from 1-20, arrSize number of times, to see the length of the shape
 * @param shapeCh The shapeCh variable has random values (ASCII) from 33-126, arrSize number of times, in order to show it as the character of the shape
 * @param arrSize The arrSize variable is a random value between 1-10 that will be the amount of values that will be generated for the arrays
*/
void drawArrays(int shapeTy[], int shapeLen[], char shapeCh[], const int arrSize) {
    for(int i = 0; i < arrSize; i++) {
        switch(shapeTy[i]) {
            case 1:
                drawHorizontalLine(shapeLen[i], shapeCh[i]);
                
                break;
            case 2:
                drawVerticalLine(shapeLen[i], shapeCh[i]);
                
                break;
            case 3:
                drawSquareFilled(shapeLen[i], shapeCh[i]);
                
                break;
            case 4:
                drawSquare(shapeLen[i], shapeCh[i], true);
                
                break;
            case 5:
                drawRectangle(shapeLen[i] / 2, shapeLen[i], shapeCh[i], true);
                
                break;
            default:
                drawRectangleFilled(shapeLen[i] / 2, shapeLen[i], shapeCh[i]);
                
                break;
        }
    }
}
