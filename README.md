# CSE115-Group-3
# Hangman Game in C Language

## Project Description
This is a simple console-based game called "Hangman Game" developed for our CSE115 course's group project. Players guess letters one at a time to reveal a hidden word before running out of tries. The game features score tracking, multiple rounds, and a high scores leaderboard system.

## How to Play
1. Enter your name when prompted
2. The game will select a random word from the dictionary
3. Guess one letter at a time
4. You have 6 tries to guess the word correctly
5. Correct guesses reveal letters in the word
6. Wrong guesses decrease your remaining tries and draw the hangman
7. Win by guessing all letters before tries run out
8. Earn points based on remaining tries (10 points per try left)
9. Play multiple rounds to increase your score
10. View the high scores leaderboard at the end

## Project Structure
```
CSE115-Group-3/
│
├── main.c                  # Main game controller and entry point
├── README.md              # This file - project documentation
├── requirements.txt       # Build and compilation requirements
│
├── support/               # Supporting game components
│   ├── game.h            # Game function declarations
│   ├── game.c            # Core game logic implementation
│   ├── player.h          # Player function declarations
│   └── player.c          # Player management implementation
│
├── data/                  # Word database and scores
│   ├── words.txt         # Dictionary of 180+ words
│   └── scores.txt        # High scores (auto-generated during gameplay)
│
└── others/                # Additional project documentation
```

## Features
- Random word selection from 180+ word dictionary
- 6 tries per round with visual hangman display
- Input validation (only accepts alphabetic characters)
- Duplicate guess detection
- Score tracking across multiple rounds
- Persistent high scores saved to file
- Top 10 leaderboard display
- Play multiple rounds without restarting
- Clean console-based user interface

## Group Members (names are ordered alphabetically)
- **Ashfaqul Alam**
- **Intisar Binthay Fauzul**
- **Rafiha Saleha**
- **Syed Sadat Hasan**

## Running the Game

### On Linux/Mac:
```bash
./hangman
```

### On Windows:
```bash
hangman.exe
```

## File Descriptions

### Core Files

**main.c**
- Entry point of the program
- Handles game initialization and main loop
- Manages player input for name and replay choice
- Loads word dictionary from file
- Controls game flow between rounds
- Displays final scores and leaderboard

**support/game.h & game.c**
- Contains core game logic functions
- Word selection from dictionary
- Letter guess validation and processing
- Game progress tracking
- Win/loss condition checking
- Hangman ASCII art display
- Main gameplay loop

**support/player.h & player.c**
- Player name input handling
- Score saving to file
- High scores reading and display
- Word dictionary loading from file
- Memory management for word list

### Data Files

**data/words.txt**
- Contains 180+ words for the game
- Mix of programming terms and common words
- One word per line
- All lowercase

**data/scores.txt**
- Automatically created when first score is saved
- Stores player names and scores
- Format: `PlayerName:Score`
- Persistent across game sessions

## Game Rules
- You have **6 tries** to guess the word
- Each wrong guess costs 1 try and draws more of the hangman
- Duplicate guesses are detected but don't cost tries
- Only letters (A-Z) are accepted as input
- Case-insensitive (both 'A' and 'a' work the same)
- Win the round by guessing all letters before tries run out

## Scoring System
Points are awarded based on remaining tries when you win:
- 6 tries left = 60 points
- 5 tries left = 50 points
- 4 tries left = 40 points
- 3 tries left = 30 points
- 2 tries left = 20 points
- 1 try left = 10 points
- 0 tries left (loss) = 0 points

Score accumulates across multiple rounds in the same session.

## Technical Details

### Programming Concepts Used
- Functions and modular programming
- Arrays and strings
- File I/O operations
- Dynamic memory allocation (malloc/free)
- Pointers and pass-by-reference
- Loops (while, for)
- Conditional statements (if-else)
- Input validation
- Random number generation
- Sorting algorithms (bubble sort for leaderboard)

### Libraries Used
- `stdio.h` - Standard input/output operations
- `stdlib.h` - Memory allocation and random numbers
- `string.h` - String manipulation functions
- `ctype.h` - Character type checking
- `time.h` - Random seed generation

## Development Timeline

### Week 1-3 (Sep 21 - Oct 11)
- Group formation and project selection
- Learned C basics: data types, operators, control structures
- Planned game logic and structure

### Week 4-5 (Oct 12 - Oct 25)
- Created GitHub repository
- Set up project folder structure
- Learned about loops and functions
- Designed modular architecture

### Week 6-7 (Oct 26 - Nov 5)
- Learned about variable scope
- Group meeting to finalize function names
- Created header files (game.h, player.h)
- Started implementing core functions

### Week 8-10 (Nov 6 - Present)
- Implemented all game functions
- Added file I/O for words and scores
- Testing and debugging
- Completed documentation

## Known Limitations
- Maximum 50 words can be loaded from file
- Maximum 100 scores can be stored
- Player names limited to 50 characters
- Console-based interface only
- No GUI

## Future Improvements
- Add difficulty levels (word length categories)
- Implement hint system
- Add word categories (tech, animals, etc.)
- Create GUI version
- Add sound effects
- Multi-player support

## Troubleshooting

**Problem: "Could not load words file"**
- Solution: Make sure `data/words.txt` exists in the correct location
- The game will use default words if file is missing

**Problem: "Could not save score"**
- Solution: Make sure `data/` folder exists and is writable
- Check file permissions

**Problem: Compilation errors**
- Solution: Make sure all files are in correct folders
- Check that you're compiling all three .c files together

## Credits
Developed by Group 3 for CSE115 Programming Fundamentals course.

Special thanks to our course instructor for guidance throughout the project development.

Disclaimer: AI has been used to assist with documentation (https://chatgpt.com/).

## License
This project is created for educational purposes as part of a university course assignment.

---

**Last Updated**: December 2025  
**Version**: 1.0  
**Course**: CSE115 - Programming Fundamentals

