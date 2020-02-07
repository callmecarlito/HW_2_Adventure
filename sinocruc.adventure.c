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
#define MAX_STEPS 250

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

void DisplayPrompt(Room* current_room);
Room* InitializeStartRoom(Room* rooms);
void StartAdventure(Room* rooms);

Room rooms[NUM_ROOMS]; //array of room structs containing data from room files
char path_of_rooms_dir[128]; //used to store the path of the most recently modified rooms directory

int main(){
    CreateGameRooms(rooms, path_of_rooms_dir);
    //PrintRoomsInfo(rooms);
    StartAdventure(rooms);
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

    int room_number = 0; //index for room number in rooms array

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

        int connection_number = 0; //index for connecting room for array of list_of_connecting_rooms
        char str[32]; //buffer for line read by fgets
        memset(str, '\0', sizeof(str)); //clears memory space for buffer

        while( (fgets(str, sizeof(str), file_in_dir)) != NULL){ //reads 1 line at a time from the file
            
            int length = strlen(str);
            //removes newline character captured by fgets and changes it to a null terminator
            if(length > 0 && str[length - 1] == '\n'){
                str[length - 1] = '\0';
            }
            char* parsed_text;
            parsed_text = strtok(str, " "); //using strtok to parse the line of text read into str
            while(parsed_text != NULL){
                //when parsed text contains "NAME:" the next value will contain the value to be added to the struct
                if(strcmp(parsed_text, "NAME:") == 0){
                   parsed_text = strtok(NULL, " ");  //call strtok to get the value for name
                   rooms[room_number].room_name = malloc(sizeof(char)*16); //allocate memory for the string
                   memset(rooms[room_number].room_name, '\0', sizeof(*rooms[room_number].room_name)); //clear allocated memory
                   strcpy(rooms[room_number].room_name, parsed_text); //copy name to room_name of struct
                }
                //when parsed text contains "CONNECTION" the value for the name of the connecting room is coming up
                if(strcmp(parsed_text, "CONNECTION") == 0){
                    parsed_text = strtok(NULL, " ");
                    parsed_text = strtok(NULL, " "); //strtok called twice to skip over the middle term and obtain the actual value of the room name
                    rooms[room_number].list_of_connecting_rooms[connection_number] = malloc(sizeof(char)*16); //allocate memory for the string
                    memset(rooms[room_number].list_of_connecting_rooms[connection_number], '\0', sizeof(*rooms[room_number].list_of_connecting_rooms[connection_number]));
                    strcpy(rooms[room_number].list_of_connecting_rooms[connection_number], parsed_text); //copy name into the array of pointers
                    connection_number++; //increment the number of connections - value will later be added to the struct
                }
                //when parsed text contains "TYPE:" the next value will contain the value to be added to the struct
                if(strcmp(parsed_text, "TYPE:") == 0){
                    parsed_text = strtok(NULL, " "); //call strtok to get the next part of the string
                    rooms[room_number].room_type = malloc(sizeof(char)*16); //allocate memory for the string
                    memset(rooms[room_number].room_type, '\0', sizeof(*rooms[room_number].room_type));
                    strcpy(rooms[room_number].room_type, parsed_text); //copy parsed string into the room_type variable
                }
                parsed_text = strtok(NULL, " ");
            }
        }
        rooms[room_number].connections = connection_number; //adds the total number of rooms to the struct
        fclose(file_in_dir); //close current file as reading from the file is complete
        room_number++; //increment room_number to store data in the next element containing the next room struct
    }
    closedir(current_dir); //close directory once all files have been read from
}
/***********************************************************
 * ConnectRooms() - using the names found in the array 
 * list_of_connecting_rooms. we'll build conections using 
 * pointers and add those pointers to an additional array
 ***********************************************************/
void ConnectRooms(Room* rooms){
    int i, j, k;

    for(i = 0; i < NUM_ROOMS; i++){ //for each room
        for(j = 0; j < rooms[i].connections; j++){ //iterate through each name in list_of_connections
            for(k = 0; k < NUM_ROOMS; k++){
                if(strcmp(rooms[i].list_of_connecting_rooms[j], rooms[k].room_name) == 0){
                    //printf("%s : %s\n", rooms[i].connected_rooms[j], rooms[k].room_name);
                    rooms[i].connected_rooms[j] = &rooms[k];
                }
            }
        }
    }
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
        printf("Room %d: %s\n", i+1, rooms[i].room_name);
        printf("Connections: %d\n", rooms[i].connections);
        //prints connecting rooms via array of strings created by GetRoomData()
        //for(j = 0; j < rooms[i].connections; j++){
        //    printf("    [%d] %s\n", j+1, rooms[i].list_of_connecting_rooms[j]);
        //}
        //prints connecting rooms via array of pointers to room structs created by ConnectRooms()
        for(j = 0; j < rooms[i].connections; j++){
            printf("    [%d] %s\n", j+1, rooms[i].connected_rooms[j]->room_name);
        }
        printf("Type: %s\n", rooms[i].room_type);
        printf("\n");
    }
}
/***********************************************************
 * FreeAllocMem() - frees the memory allocated from 
 * GetRoomData()
 ***********************************************************/
void FreeAllocMem(Room* rooms){
    int i, j;

    for(i = 0; i < NUM_ROOMS; i++){
        free(rooms[i].room_name);
        for(j = 0; j < rooms[i].connections; j++){
            free(rooms[i].list_of_connecting_rooms[j]);
        }
        free(rooms[i].room_type);
    }
}
/***********************************************************
 * StartAdventure() - begins and controls the game play
 ***********************************************************/
void StartAdventure(Room* rooms){
    int num_steps = 0;
    Room* rooms_visited[250]; //array of pointers to rooms used to record the user's path
    Room* current_room = InitializeStartRoom(rooms);

    DisplayPrompt(current_room);
    //GetUserInput()
    //ValidateUserInput()
    //MoveToRoom()
    //IsEndRoom()
    //PrintPath()
}
/***********************************************************
 * DisplayPrompt() - displays prompt to the user stating 
 * the current location, possible rooms to explore next, 
 * and prompts user for input
 ***********************************************************/
void DisplayPrompt(Room* current_room){
    int i;
    printf("CURRENT LOCATION: %s\n", current_room->room_name);
    printf("POSSIBLE CONNECTIONS: ");
    for(i = 0; i < current_room->connections; i++){
        if(i == (current_room->connections - 1)){
            printf("%s.\n", current_room->connected_rooms[i]->room_name);
        }
        else{
            printf("%s, ", current_room->connected_rooms[i]->room_name);
        }
    }
    printf("WHERE TO? >");    
}
/***********************************************************
 * InitializeStartRoom() -  returns a pointer to the
 * START_ROOM
 ***********************************************************/
Room* InitializeStartRoom(Room* rooms){
    int i;
    for(i = 0; i < NUM_ROOMS; i++){
        if(strcmp(rooms[i].room_type, "START_ROOM") ==0){
            return &rooms[i];
        }
    }
    return NULL;
}