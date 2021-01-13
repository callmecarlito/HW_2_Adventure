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
   
## Specifications
### Rooms Program `sinocruc.buildrooms.c`
1. Creates a subdirectory named: sinocruc.rooms.[PROCESS ID]
   - The program will append its PID to the end of the directory name before creating it
2. Generates 7 different room files (one room per file) within the newly created directory and must contain the following:
   - Room Name 
     - each room should be randomly assigned a name and should be different each time the program is run 
     - cannot exceed 8 characters in length
     - list of available room names must be hard coded into the program
   - Room Type
     - possible types include: START_ROOM, END_ROOM, and MID_ROOM
     - assignment of room type should be randomly assigned each time the program is run
     - there should only be one START_ROOM and END_ROOM
   - Outbound Connections
     - each room should contain a minimum of 3 and maximum of 6 outbound connections to other rooms
     - outbound connections should also be assigned randomly each time the program is run
     - each outbound connection should have a matching connection in the opposite direction - if room A connects to B, then B must connect back to A
     - a room cannot have an outbound connection to itself 
     - a room cannot have more than 1 outbound connection to the same room
     - room file format:
     ```
        ROOM NAME: <room name>
        CONNECTION 1: <room name>
        CONNECTION 2: <room name>
        ...
        ROOM TYPE: <room type>
     ```
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
