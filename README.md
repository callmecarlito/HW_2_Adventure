# Text Adventure Game
This game is comprised of two different programs. The first, generates the rooms and the game environment layout. The second, runs the actual 
adventure game. The user will begin one of the rooms and must navigate to find the end room.  

## Files
1. sinocruc.buildrooms.c
   - generates a subdirectory containing a series of files representing the rooms for the game. Each file will contain a description of the 
     room including the rooms connected to it
   - each time this program is executed a new subdirectory is created with a different series of files
2. sinocruc.adventure.c
   - provides the interface for playing the game using the most recently generated subdirectory containing the room files
3. Makefile
   
## Requirements
### Rooms Program `sinocruc.buildrooms.c`
 - creates a subdirectory named: sinocruc.rooms.[PROCESS ID OF ROOMS PROGRAM]   
### The Game `sinocruc.adventure.c`

## compiling and running
Make sure all files are contained within the same directory. To compile the program, navigate to the program directory from your terminal.
Once you are there type "make all" followed by enter key. Once complete, two executable files should appear: `sinocruc.buildrooms.out` and 
`sinocruc.adventure.out`. First begin by running the buildrooms program, if successful, a new subdirectory should be created containing the 
files for each room. Next, run the adventure program which will begin the game.

A "make clean" option has also been added, should you like you can utilize that to remove the executable
files from the directory. 

If you have any additional questions, please feel free to contact me.

Thanks!

written by: Carl S. (sinocruc@oregonstate.edu)
