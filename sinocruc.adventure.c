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

char path_of_rooms_dir[128];

int main(){
    FindNewestRooms(path_of_rooms_dir);
    return 0;
}
/***********************************************************
 * FindNewestRooms() -
 ***********************************************************/
void FindNewestRooms(char* path_of_rooms_dir){
    int dir_time = -5;
    char* target_dir = "sinocruc.rooms"; //target directories will contain this
    
    DIR* current_dir; //
    struct dirent* dir_entry; //
    struct stat entry_info; //

    current_dir = opendir("."); //open directory program is being executed from
    if(current_dir == NULL){ //check if there was a failure opening the directory
        perror("Unable to open directory");
        exit(1);
    }
    else{
        while( (dir_entry = readdir(current_dir)) != NULL){
            if( (strstr(dir_entry->d_name, target_dir)) != NULL){
                stat(dir_entry->d_name, &entry_info);
                if((int)entry_info.st_mtime > dir_time){
                    dir_time = (int)entry_info.st_mtime;
                    memset(path_of_rooms_dir, '\0', sizeof(&path_of_rooms_dir));
                    strcpy(path_of_rooms_dir, dir_entry->d_name);
                }
            }
        }
    }
    printf("newest directory: %s\n", path_of_rooms_dir);
    closedir(current_dir);
}
/***********************************************************
 * GetRoomData() - 
 ***********************************************************/
void GetRoomData(Room* rooms, char* path_of_rooms_dir){

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