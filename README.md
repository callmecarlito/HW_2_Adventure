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
1. Reads the room data generated above into the program
2. Should use the most recently generated set of files
   - use the `stat()` function call to find the directory with the most recent `st_mtime` value from the returned `stat` struct
3. Provides gameplay interface which tells the player their current location, possible outbound connections, and a prompt
   ```
      CURRENT LOCATION: XYZZY
      POSSIBLE CONNECTIONS: PLOVER, Dungeon, twisty.
      WHERE TO? > 
   ```
   - the user can then enter the name of the next room they choose and then re-prompted 
   ```
      CURRENT LOCATION: XYZZY
      POSSIBLE CONNECTIONS: PLOVER, Dungeon, twisty.
      WHERE TO? >twisty

      CURRENT LOCATION: twisty
      POSSIBLE CONNECTIONS: PLOVER, XYZZY, Dungeon, PLUGH.
      WHERE TO? >
   ```
   - if the user enters an invalid room name, an error message should be produced and then prompt the user again
4. The program should keep track of the number of steps taken by the user to reach the end room as well as the path taken
   - invalid room selections should not be counted nor tracked in the history
5. Once the user reaches the end room:
   - they receive a congratulatory message 
   - output the path taken (not including the start room)
   - output the number of steps taken
   - then exit (make sure to set exit status code to 0)
6. Time Keeping
   - the program must also be able to return the current time of day
     - must utilize a second thread and mutex(es)
       - use the classic pthread library to accomplish this simple multithreading
         - remember to use `-lpthread` compile option switch
   - when the player enters `time` at the game prompt, the second thread must write the current time to a file called `currentTime.txt` located
     in the same directory as the program
     - use `strftime()` for the formatting
   - the main thread will then read this time value from the file and print it out to the user
     - the mutex will be used to control the execution between the two threads
   - any additional calls for time by the user should simply overwrite the data in the `currentTime.txt` file

## Compiling and Running
Make sure all files are contained within the same directory. To compile the program, navigate to the program directory from your terminal.
Once you are there type "make all" followed by enter key. Once complete, two executable files should appear: `sinocruc.buildrooms.out` and 
`sinocruc.adventure.out`. First begin by running the buildrooms program, if successful, a new subdirectory should be created containing the 
files for each room. Next, run the adventure program which will begin the game.

A "make clean" option has also been added, should you like you can utilize that to remove the executable
files from the directory. 

If you have any additional questions, please feel free to contact me.

Thanks!

written by: Carl S. (sinocruc@oregonstate.edu)
