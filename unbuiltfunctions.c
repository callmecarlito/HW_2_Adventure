/***********************************************************
 * AddRandomConnection() - adds a random, valid outbound 
 * connection from a Room to another Room
 ***********************************************************/
void AddRandomConnection(){
    Room A;
    Room B;

    while(true){
        A = GetRandomRoom();
        if(CanAddConnectionFrom(A) == true){
            break;
        }
    }
    do{
        B = GetRandomRoom();
    }while(CanAddConnectionFrom(B) == false || 
           IsSameRoom(A, B) == true || 
           ConnectionAlreadyExists(A, B) == true);

    ConnectRoom(A, B);
    ConnectRoom(B, A);
}

/***********************************************************
 * CanAddConnectionFrom() - returns true if a connection can
 * be added from Room B (< 6 outbound connections)
 ***********************************************************/
bool CanAddConnectionFrom(Room B){

}
/***********************************************************
 * ConnectionAlreadyExists() - returns true if connection 
 * from Room A and Room B already exists
 ***********************************************************/
bool ConnectionAlreadyExists(Room A, Room B){
    
}
/***********************************************************
 * ConnectRoom() - connects Room A to Room B
 ***********************************************************/
void ConnectRoom(Room A, Room B){

}
/***********************************************************
 * IsSameRoom() - returns true if Room A and Room B are
 * the same room
 ***********************************************************/
bool IsSameRoom(Room A, Room B){

}