#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define NUM_ROOMS 7
#define MIN_CONNECT 3
#define MAX_CONNECT 6

typedef struct{
    char* room_name;
    char* room_type;
    int connections; 
    struct Room* connected_rooms[MAX_CONNECT];
} Room;

char* rm_names[10] = {"thisroom", "LMNOP", "ThAtroom", "Empty", "KB824", 
                   "infinity", "remember", "SPAced", "dunGEON", "onlyRoom"};

void CreateRooms(Room* rooms);
void DeleteRooms(Room* rooms); 
void PrintRoomsInfo(Room* rooms);
void PrintRoom(Room* room);
bool IsGraphFull(Room* rooms);
Room* GetRandomRoom(Room* rooms);

//void AddRandomConnection();

//bool CanAddConnectionFrom(Room B);
//bool ConnectionAlreadyExists(Room A, Room B);
//void ConnectRoom(Room A, Room B);
//bool IsSameRoom(Room A, Room B);

/* reference for creating an array of pointers to structs:
 * https://stackoverflow.com/questions/15397728/c-pointer-to-array-of-pointers-to-structures-allocation-deallocation-issues
 * array for pointers to Room structs
 * 
 * REMOVE REMOVE REMOVE ?????????
 *
 */

//declare an array of rooms
Room rooms[NUM_ROOMS];

int main(){
    srand(time(NULL));
    CreateRooms(rooms);
    PrintRoomsInfo(rooms);
    Room* ptr = GetRandomRoom(rooms);
    PrintRoom(ptr);
    return 0;
}
/***********************************************************
 * CreateRooms() - initializes the array containing 
 * pointers to room structs and returns the pointer to that
 * array
 ***********************************************************/ 
void CreateRooms(Room *rooms){
    int i = 0, name_index, j;
    while(i < NUM_ROOMS){
        //initialize the number of connections to 0
        rooms[i].connections = 0;
        //assign room types
        if(i == 0){
            rooms[i].room_type = "START_ROOM";
        }
        else if(i == 1){
            rooms[i].room_type = "END_ROOM";
        }
        else{
            rooms[i].room_type = "MID_ROOM";
        }
        //randomly select name from the list of names
        name_index = rand() % 10;
        //check name is not already in use
        for(j = 0; j < i; j++){
            //if name is in use
            if(strcmp(rooms[j].room_name, rm_names[name_index]) == 0){
                break;
            }
        }
        //if j == i, means we have checked the entire list
        if(j == i){
            //assign name to the next room and increment i
            rooms[i++].room_name = rm_names[name_index];
        }
    }
}
/***********************************************************
 * PrintRoomsInfo() - iterates through the array of rooms
 * and prints the room name, type, number of connections, 
 * and rooms connected 
 ***********************************************************/ 
void PrintRoomsInfo(Room* rooms){
    int i;
    for(i = 0; i < NUM_ROOMS; i++){
        printf("Room %d: %s\n", i+1, rooms[i].room_name);
        printf("  Type: %s\n", rooms[i].room_type);
        printf("  Number Of Connections: %d\n", rooms[i].connections);
    }
}
/***********************************************************
 * PrintRoom() - prints the info for the room passed to it
 ***********************************************************/ 
void PrintRoom(Room* room){
    printf("Room: %s\n", room->room_name);
    printf("  Type: %s\n", room->room_type);
    printf("  Number Of Connections: %d\n", room->connections);
}
/***********************************************************
 * IsGraphFull() - returns true if all rooms have 3 to 6 
 * outbound connections.
 ***********************************************************/ 
bool IsGraphFull(Room* rooms){
    int i;
    for (i = 0; i < NUM_ROOMS; i++){
        //if number of room connects are NOT >= 3 or <= 6
        if(!(rooms[i].connections >= 3 && rooms[i].connections <= 6)){
            return false;
        }
    }
    return true;
}
/***********************************************************
 * GetRandomRoom() - returns a random room, but does not
 * validate if connection can be added
 ***********************************************************/
Room* GetRandomRoom(Room* rooms){
    int room_number = rand() % NUM_ROOMS;
    //return address to randomly picked room
    return &rooms[room_number];
}