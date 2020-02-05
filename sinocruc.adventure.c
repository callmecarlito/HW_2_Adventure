#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define NUM_ROOMS 7
#define MIN_CONNECT 3
#define MAX_CONNECT 6

typedef struct Room{
    char* room_name;
    char* room_type;
    int connections; 
    struct Room* connected_rooms[MAX_CONNECT];
    char* room_path;
} Room;

void FindNewestRooms(char* path_of_rooms_dir);
void GetRoomData(Room* rooms, char* path_of_rooms_dir);
void ConnectRooms(Room* rooms);
void CreateGameRooms(Room* rooms, char* path_of_rooms_dir);

Room rooms[NUM_ROOMS];
char path_of_rooms_dir[128];

int main(){
    FindNewestRooms(path_of_rooms_dir);
    GetRoomData(rooms, path_of_rooms_dir);
    
    return 0;
}
/***********************************************************
 * FindNewestRooms() -
 ***********************************************************/
void FindNewestRooms(char* path_of_rooms_dir){
    int dir_time = -5;
    char* target_dir = "sinocruc.rooms"; //target directories will contain this
    DIR* current_dir; //ptr to directory being explored
    struct dirent* dir_entry; //ptr to an entry in current_dir
    struct stat entry_info; //used for accessing info for an entry

    current_dir = opendir("."); //open directory program is being executed from
    if(current_dir == NULL){ //check if there was a failure opening the directory
        perror("Unable to find newest directory - Error opening directory");
        exit(1);
    }
     while( (dir_entry = readdir(current_dir)) != NULL){ //iterates through each entry in the directory
        if( (strstr(dir_entry->d_name, target_dir)) != NULL){ //strstr looks for the target_dir within d_name
            if( (stat(dir_entry->d_name, &entry_info)) == -1){ //returns info from dir_entry->d_name into the buffer entry_info
                perror("stat");
                exit(1);
            } 
            if((int)entry_info.st_mtime > dir_time){ //compare the last modified time of an entry
                dir_time = (int)entry_info.st_mtime; //if newer, update dir_time
                memset(path_of_rooms_dir, '\0', sizeof(&path_of_rooms_dir)); //clear path variable
                strcpy(path_of_rooms_dir, dir_entry->d_name); //store path of the newest dir in path variable
            }
        }
    }
    closedir(current_dir);
}
/***********************************************************
 * GetRoomData() - 
 ***********************************************************/
void GetRoomData(Room* rooms, char* path_of_rooms_dir){
    int room_number = 0;
    DIR* current_dir; //
    struct dirent* dir_entry; //
    FILE* file_in_dir;

    current_dir = opendir(path_of_rooms_dir); //open newest rooms directory
    if(current_dir == NULL){ //check if there was a failure opening the directory
        perror("Unable to get room data - Error opening directory");
        exit(1);
    }
    printf("%s\n", path_of_rooms_dir);
    while( (dir_entry = readdir(current_dir)) != NULL){
        printf("%s\n", dir_entry->d_name);
    }
    closedir(current_dir);

}
/***********************************************************
 * ConnectRooms() -
 ***********************************************************/
void ConnectRooms(Room* rooms){

}
/***********************************************************
 * CreateGameROoms() 
 ***********************************************************/
void CreateGameRooms(Room* rooms, char* path_of_rooms_dir){
    FindNewestRooms(path_of_rooms_dir);
    GetRoomData(rooms, path_of_rooms_dir);
    ConnectRooms(rooms);
}
/***********************************************************
 * 
 ***********************************************************/