#include <stdio.h>
#include <stdbool.h>

#define NUM_ROOMS 7
#define MIN_CONNECT 3
#define MAX_CONNECT 6

typedef struct{
    char* room_name;
    char* room_type;
    int connections; 
    Room connected_rooms[MAX_CONNECT]
} Room;

char* rm_names[10] = {"thisroom", "LMNOP", "ThAtroom", "Empty", "KB824", 
                   "infinity", "remember", "SPAced", "dunGEON", "onlyRoom"};
char* rm_types[3] = {"START_ROOM", "END_ROOM", "MID_ROOM"};

Room* InitializeRooms();
void DeleteRooms(Room *arrOfRooms); 
//bool IsGraphFull();
//void AddRandomConnection();
//Room GetRandomRoom();
//bool CanAddConnectionFrom(Room B);
//bool ConnectionAlreadyExists(Room A, Room B);
//void ConnectRoom(Room A, Room B);
//bool IsSameRoom(Room A, Room B);

//reference for creating an array of pointers to structs:
//https://stackoverflow.com/questions/15397728/c-pointer-to-array-of-pointers-to-structures-allocation-deallocation-issues
//array for pointers to Room structs

int main(){
    //declare pointer to array and initialize and allocate memory for array
    Room *(*rooms)[] = InitializeRooms();
    //while (IsGraphFull() == false){
    //    AddRandomConnection();
    //}
    DeleteRooms(*rooms);
    return 0;
}
/***********************************************************
 * InitializeRooms() - initializes the array containing 
 * pointers to room structs and returns the pointer to that
 * array
 ***********************************************************/ 
Room* InitializeRooms(){
    int i;
    //declare array of pointers to structs
    Room *arrOfRooms[NUM_ROOMS];
    //allocate and assign pointers to structs
    for(i = 0; i < NUM_ROOMS; i++){
        arrOfRooms[i] = malloc(sizeof(Room));
    }
    //return pointer to array
    return &arrOfRooms;
}
/***********************************************************
 * DeleteRooms() - Clean up memory allocated for each room
 ***********************************************************/ 
void DeleteRooms(Room *arrOfRooms){
    int i;
    for(i = 0; i < NUM_ROOMS; i++){
        free(arrOfRooms[i]);
    }
}
