#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define NUM_ROOMS 7
#define MIN_CONNECT 3
#define MAX_CONNECT 6

typedef struct Room{
    char* room_name;
    char* room_type;
    int connections; 
    struct Room* connected_rooms[MAX_CONNECT];
} Room;

//list for name of rooms to be randomly selected from
char* rm_names[10] = {"thisroom", "LMNOP", "ThAtroom", "Empty", "KB824", 
                   "infinity", "remember", "SPAced", "dunGEON", "onlyRoom"};

void InitializeRooms(Room* rooms);
void PrintRoomsInfo(Room* rooms);
void PrintRoom(Room* room);
bool IsGraphFull(Room* rooms);
Room* GetRandomRoom(Room* rooms);
bool CanAddConnectionFrom(Room* B);
bool ConnectionAlreadyExists(Room* A, Room* B);
void ConnectRoom(Room* A, Room* B);
bool IsSameRoom(Room* A, Room* B);
void AddRandomConnection(Room* rooms);
void CreateRooms(Room* rooms);

//declare an array of rooms
Room rooms[NUM_ROOMS];

int main(){
    srand(time(NULL));
    CreateRooms(rooms);
    PrintRoomsInfo(rooms);
    return 0;
}
/***********************************************************
 * InitializeRooms() - randomly assigns room names and room
 * types
 ***********************************************************/ 
void InitializeRooms(Room *rooms){
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
            //increment i and assign name to the next room
            rooms[i++].room_name = rm_names[name_index];
        }
    }
}
/***********************************************************
 * PrintRoomsInfo() - iterates through the array of rooms
 * and prints the room name, type, number of connections, 
 * and rooms connected.  
 ***********************************************************/ 
void PrintRoomsInfo(Room* rooms){
    int i, j;
    for(i = 0; i < NUM_ROOMS; i++){
        printf("Room %d: %s", i+1, rooms[i].room_name);
        printf(" --- Type: %s", rooms[i].room_type);
        printf(" --- Number Of Connections: %d\n", rooms[i].connections);
        for(j = 0; j < rooms[i].connections; j++){
            printf("    [%d] %s\n", j+1, rooms[i].connected_rooms[j]->room_name);
        }
        printf("\n");
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
/***********************************************************
 * CanAddConnectionFrom() - returns true if a connection can
 * be added from Room B (< 6 outbound connections)
 ***********************************************************/
bool CanAddConnectionFrom(Room* B){
    if(B->connections < MAX_CONNECT){
        return true;
    }
    else{
        return false;
    }
}
/***********************************************************
 * ConnectionAlreadyExists() - returns true if connection 
 * from Room A and Room B already exists
 ***********************************************************/
bool ConnectionAlreadyExists(Room* A, Room* B){
    int i;
    for(i = 0; i < A->connections; i++){
        //compares the pointers to the of room B
        if(A->connected_rooms[i] == B){
            return true;
        }
    }
    return false;
}
/***********************************************************
 * ConnectRoom() - connects Room A to Room B
 ***********************************************************/
void ConnectRoom(Room* A, Room* B){
    //adds pointer for room B to the array for rooms connected to A
    A->connected_rooms[A->connections++] = B;
}
/***********************************************************
 * IsSameRoom() - returns true if Room A and Room B are
 * the same room
 ***********************************************************/
bool IsSameRoom(Room* A, Room* B){
    //compares to pointers of room A and B to see if they are the same
    if(A == B){
        return true;
    }
    else{
        return false;
    }
}
/***********************************************************
 * AddRandomConnection() - adds a random, valid outbound 
 * connection from a Room to another Room
 ***********************************************************/
void AddRandomConnection(Room* rooms){
    Room* A;
    Room* B;

    while(true){
        A = GetRandomRoom(rooms);
        if(CanAddConnectionFrom(A) == true){
            break;
        }
    }
    do{
        B = GetRandomRoom(rooms);
    }while(CanAddConnectionFrom(B) == false || 
           IsSameRoom(A, B) == true || 
           ConnectionAlreadyExists(A, B) == true);

    ConnectRoom(A, B);
    ConnectRoom(B, A);
}
/***********************************************************
 * CreateRooms() - assigns names and room types to room then
 * creates the connections between the rooms
 ***********************************************************/
void CreateRooms(Room* rooms){
    InitializeRooms(rooms);
    while(!IsGraphFull(rooms)){
        AddRandomConnection(rooms);
    }
}