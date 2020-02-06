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
    int connections;
    char* list_of_connecting_rooms[MAX_CONNECT]; 
    struct Room* connected_rooms[MAX_CONNECT];
    char* room_type;
} Room;

void FindNewestRooms(char* path_of_rooms_dir);
void GetRoomData(Room* rooms, char* path_of_rooms_dir);
void ConnectRooms(Room* rooms);
void CreateGameRooms(Room* rooms, char* path_of_rooms_dir);
void PrintRoomsInfo(Room* rooms);
void FreeAllocMem(Room* rooms);

Room rooms[NUM_ROOMS];
char path_of_rooms_dir[128];

int main(){
    FindNewestRooms(path_of_rooms_dir);
    GetRoomData(rooms, path_of_rooms_dir);
    PrintRoomsInfo(rooms);
    FreeAllocMem(rooms);
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
    DIR* current_dir; //
    struct dirent* dir_entry; //
    FILE* file_in_dir;

    current_dir = opendir(path_of_rooms_dir); //open newest rooms directory
    if(current_dir == NULL){ //check if there was a failure opening the directory
        perror("Unable to get room data - Error opening directory: ");
        exit(1);
    }
    //changed working directory in order to get fopen() to function properly 
    //without needing the entire file path of the files
    int change_dir = chdir(path_of_rooms_dir);
    if(change_dir != 0){
        perror("Unable to change working directory: ");
        exit(1);
    }

    int room_number = 0;

    while( (dir_entry = readdir(current_dir)) != NULL){ //iterates through the entries in current_dir
        //skips over "." and ".."
        if (strcmp(dir_entry->d_name,".") == 0 || 
            strcmp(dir_entry->d_name, "..") == 0){
                continue;
        }
        //from the new working directory call fopen to open the file
        file_in_dir = fopen(dir_entry->d_name, "r");
        if(file_in_dir == NULL){
            perror("Error opening room file: ");
            exit(1);
        }
        int connection_number = 0;
        char str[32];
        memset(str, '\0', sizeof(str));
        while( (fgets(str, sizeof(str), file_in_dir)) != NULL){
            char* parsed_text;
            parsed_text = strtok(str, " ");
            while(parsed_text != NULL){
                if(strcmp(parsed_text, "NAME:") == 0){
                   parsed_text = strtok(NULL, " "); 
                   rooms[room_number].room_name = malloc(sizeof(char)*16);
                   memset(rooms[room_number].room_name, '\0', sizeof(rooms[room_number].room_name));
                   strcpy(rooms[room_number].room_name, parsed_text);
                }
                if(strcmp(parsed_text, "CONNECTION") == 0){
                    parsed_text = strtok(NULL, " ");
                    parsed_text = strtok(NULL, " ");
                    //printf("[CONNECTION] %s\n", parsed_text);
                    //rooms[room_number].connected_rooms[connection_number]->room_name = malloc(sizeof(char)*16);
                    //memset(rooms[room_number].connected_rooms[connection_number]->room_name, '\0', sizeof(rooms[room_number].connected_rooms[connection_number]->room_name));
                    //strcpy(rooms[room_number].connected_rooms[connection_number]->room_name, parsed_text);
                    rooms[room_number].list_of_connecting_rooms[connection_number] = malloc(sizeof(char)*16);
                    memset(rooms[room_number].list_of_connecting_rooms[connection_number], '\0', sizeof(rooms[room_number].list_of_connecting_rooms[connection_number]));
                    strcpy(rooms[room_number].list_of_connecting_rooms[connection_number], parsed_text);
                    connection_number++;
                }
                if(strcmp(parsed_text, "TYPE:") == 0){
                    parsed_text = strtok(NULL, " ");
                    //printf("[TYPE] %s\n", parsed_text);
                }
                parsed_text = strtok(NULL, " ");
            }
        }
        rooms[room_number].connections = connection_number; 
        fclose(file_in_dir);
        room_number++;
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
 * PrintRoomsInfo() - iterates through the array of rooms
 * and prints the room name, type, number of connections, 
 * and rooms connected.  
 ***********************************************************/ 
void PrintRoomsInfo(Room* rooms){
    int i, j;

    for(i = 0; i < NUM_ROOMS; i++){
        printf("Room %d: %s", i+1, rooms[i].room_name);
        printf("Connections: %d\n", rooms[i].connections);
        for(j = 0; j < rooms[i].connections; j++){
            printf("    [%d] %s", j+1, rooms[i].list_of_connecting_rooms[j]);
        }
    }
}
/***********************************************************
 * 
 ***********************************************************/
void FreeAllocMem(Room* rooms){
    int i, j;

    for(i = 0; i < NUM_ROOMS; i++){
        free(rooms[i].room_name);
        for(j = 0; j < rooms[i].connections; j++){
            free(rooms[i].list_of_connecting_rooms[j]);
        }
    }
}
/***********************************************************
 * 
 ***********************************************************/