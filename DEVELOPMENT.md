# Week One

### Setting up the project
The project was created with the OpenFrameworks project generator, and the seasocks was cloned from the
git repository. Since seasocks is a CMake project and OpenFrameworks is not, there isn't a great way to link
to the seasocks repository as a library. To get around this, seasocks should be cloned directly into the project
source in order to work. To avoid committing seasocks to the repository, all files in seasocks are in .gitignore
except for a select few that were modified.    

After cloning this repository, seasocks should be cloned to ```\blackjack\src``` into a folder named ```seasocks```. After this,
all seasocks files that are present in this repository should replace the ones that were just cloned.    

Easy WS Client is used to open the web socket connection from the C client. Since this library is only a .hpp and .cpp file, it
is committed directly to ```\blackjack\src\easywsclient```.

Note: the files in ```\blackjack\src\server``` are not compiled in visual studio, and they should be excluded from the build otherwise
Visual Studio will throw errors. To do this, right click on each file in the folder, select properties, and select 'exclude from build'.    

### Setting up the server
This week I wrote most of the server-side code for the websocket server. This can be found in ```\blackjack\src\server```. Here's a high
level overview of how the communication works:  
There are two types of clients. A ```Web Client``` and ```C Client```. Each player in the game will be a ```Web Client```, and through
a web interface they will be able to make game decisions (like hit or stay). There can be multiple Web Clients. There is one ```C Client``. This
client displays a graphic of the current game state, and the players can see their moves updated in real time on the ```C Client```.    

The ```GameConnection``` class serves as a wrapper for the connection objects and the ```GameConnectionManager``` processes all of the commands for the server. the ```ws_test``` file is the entry point to the server and it essentially just calls the game connection manager.    

#### Server Commands
This week, I implemented to following commands for the server:  
- ```SETNAME:<PlayerName>``` Sets the screen name of the player.
- ```ADDUSER:<PlayerName>``` Sent to the C Client to indicate that a new player joined.
- ```UPDATENAME:<PlayerName>``` Sent to the C Client to indicate that a player changed their name.
- ```SETTYPE:<Type>``` Sets the client type. <Type> Should be 0 (Web) or 1 (C).
- ```<CardNumber>:<PlayerName>``` Sends the <CardNumber> (0 to 51) to the <PlayerName>. This can only be called by C Client.
- ```HIT:``` Sent by the web client to indicate they want to recieve a card. This can only be called by Web Client.
- ```STAY:``` Sent by the web client to indicate they want to stay. This can only be called by Web Client.
