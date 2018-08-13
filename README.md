# Studio_Project_1
This is to list all the functions in the project 

##### init()
Initializes the game variables, load data, allocate memory, etc. Code that should run before the game starts should be here.

##### getInput()
Detects input from input sources, e.g. keyboard. This is where you detect if the user has given any input to the game, and set your flags accordingly.

##### update(double dt)
This is the meat of your code, the game logic should be done here. i.e. reaction to input, enemy movement, enemy spawning, win game condition, lose game condition, state of game, etc.
Sounds can be played here.

##### render()
Renders the current state of game onto screen. Go to a specific coordinate on the screen, set colours, write output, etc.

##### shutdown()
Code for cleaning up of game, writing of files, close files, free up memory, etc.

### Console functions in the framework

##### void gotoXY(SHORT x, SHORT y);
##### void gotoXY(COORD c);
Go to a specific location on the screen and writes to the std output from there. Origin is top left.

##### void colour(WORD attrib);
Sets a specific colour to be used in the next call to std::cout.

##### void cls( HANDLE hConsole = 0);
Clears the screen with the last colour attribute set.

#### Console object
You will only need to create one console object, and use this one true object in your code for all the console output. 

##### Console(COORD consoleSize, LPCSTR lpConsoleTitle = 0);
##### Console(SHORT consoleWidth, SHORT consoleHeight, LPCSTR lpConsoleTitle = 0);
Inits the console size, and give it a title, pass in a C-Style string

##### COORD getConsoleSize();  
Gets the console size, in a COORD struct.

##### void setConsoleTitle(LPCSTR lpConsoleTitle);
Sets the console title

##### void setConsoleFont(SHORT width, SHORT height, LPCWSTR lpcwFontName); 
Sets the console font. You can set the width and height of the raster fonts. If you are using a TrueType font, you can use the height as the font size. 

##### void clearBuffer(WORD attribute = 0x0F);
Clears the data buffer, hence "clearing the screen", preparing for new data.

##### void writeToBuffer(COORD c, LPCSTR str, WORD attribute = 0x0F);
##### void writeToBuffer(COORD c, std::string& s, WORD attribute = 0x0F);
##### void writeToBuffer(COORD c, char ch, WORD attribute = 0x0F);
##### void writeToBuffer(SHORT x, SHORT y, LPCSTR str, WORD attribute = 0x0F);
##### void writeToBuffer(SHORT x, SHORT y, std::string& s, WORD attribute = 0x0F);
##### void writeToBuffer(SHORT x, SHORT y, char ch, WORD attribute = 0x0F);  
The origin of the screen is on the top left.
These 6 functions writes to the buffer at that coordinate, you can use C-Style strings, C++ string class or a char. The attribute is a optional parameter. The last 3 functions are overloaded versions of the first 3 functions.


##### void flushBufferToConsole();
Call this at the end of the render() function so that the contents of the buffer will be displayed onto the screen.
