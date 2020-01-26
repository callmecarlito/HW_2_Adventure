#include <stdio.h>
typedef enum {false, true} bool;

struct Room{
    char* roomName;
};

/***********************************************************
 * IsGraphFull() - returns true if all rooms have 3 to 6 
 * outbound connections.
 ***********************************************************/ 
bool IsGrapgFull(){

}
/***********************************************************
 * AddRandomConnection() - adds a random, valid outbound 
 * connection from a Room to another Room
 ***********************************************************/
void AddRandomConnection(){

}
/***********************************************************
 * GetRandomRoom() - returns a random room, but does not
 * validate if connection can be added
 ***********************************************************/
struct Room GetRandomRoom(){

}
/***********************************************************
 * CanAddConnectionFrom() - returns true if a connection can
 * be added from Room B (< 6 outbound connections)
 ***********************************************************/
bool CanAddConnectionFrom(struct Room B){

}
/***********************************************************
 * ConnectionAlreadyExists() - returns true if connection 
 * from Room A and Room B already exists
 ***********************************************************/
bool ConnectionAlreadyExists(struct Room A, struct Room B){
    
}
/***********************************************************
 * ConnectRoom() - connects Room A to Room B
 ***********************************************************/
void ConnectRoom(struct Room A, struct Room B){

}
/***********************************************************
 * IsSameRoom() - returns true if Room A and Room B are
 * the same room
 ***********************************************************/
bool IsSameRoom(struct Room A, struct Room B){

}