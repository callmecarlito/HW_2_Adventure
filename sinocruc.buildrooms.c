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
//bool IsGraphFull();
//void AddRandomConnection();
//Room GetRandomRoom();
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
    //while (IsGraphFull() == false){
    //    AddRandomConnection();
    //}
    //DeleteRooms(rooms);
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
        //assign room types
        if(i == 0){
            rooms[i].room_type = "START_ROOM";
            //strcpy(rooms[i].room_type, "START_ROOM");
        }
        else if(i == 1){
            rooms[i].room_type = "END_ROOM";
            //strcpy(rooms[i].room_type, "END_ROOM");
        }
        else{
            rooms[i].room_type = "MID_ROOM";
            //strcpy(rooms[i].room_type, "MID_ROOM");
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
 * DeleteRooms() - Clean up memory allocated for each room
 ***********************************************************/ 
void DeleteRooms(Room *rooms){
    
}
/***********************************************************
 * PrintRoomsInfo() - 
 ***********************************************************/ 
void PrintRoomsInfo(Room* rooms){
    int i;
    for(i = 0; i < NUM_ROOMS; i++){
        printf("Room %d: %s\n", i+1, rooms[i].room_name);
        printf("  Type: %s\n", rooms[i].room_type );
    }
}
