

# crossword
Crossword puzzle generator from fixed word list (class exercise)

Usage is: `xws GRID_FILE_NAME DICT_FILE_NAME`

Example: 

    $   ./xws 3.grid dict.txt 
    ...
    $  Printing wordList (12 items):
    Orientation   StartRow   EndRow   StartCol  EndCol   Length   Word:
    horizontal     0         6         6         6         7             |ABANDON|
    horizontal     0         6         0         0         7             |ABATING|
    vertical       6         6         0         6         7             |GATEMAN|
    vertical       0         0         0         6         7             |ALFALFA|
    horizontal     4         6         4         4         3             |JEM|
    horizontal     0         2         4         4         3             |LAG|
    horizontal     4         6         2         2         3             |APT|
    horizontal     0         2         2         2         3             |FEE|
    vertical       4         4         4         6         3             |JUD|
    vertical       4         4         0         2         3             |IRA|
    vertical       2         2         4         6         3             |GOA|
    vertical       2         2         0         2         3             |ANE|
    
    
    Printing puzzle
    A L F A L F A 
                  
    B   E   A   B 
                  
    A N E   G O A 
                  
    T           N 
                  
    I R A   J U D 
                  
    N   P   E   O 
                  
    G A T E M A N 
                  
    18971

