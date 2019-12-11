# Week One (11/14 - 11/19)

### Setting up the project
The project was created with the OpenFrameworks project generator, and the seasocks was cloned from the
git repository. Since seasocks is a CMake project and OpenFrameworks is not, there isn't a great way to link
to the seasocks repository as a library. To get around this, seasocks should be cloned directly into the project
source in order to work. To avoid committing seasocks to the repository, all files in seasocks are in .gitignore
except for a select few that were modified.    

After cloning this repository, seasocks should be cloned to ```\blackjack\src``` into a folder named ```seasocks```. After this,
all seasocks files that are present in this repository should replace the ones that were just cloned.    

Note: All the files except ```ConnectionConstants.h``` in ```\blackjack\src\server``` are not compiled in visual studio, and they should be excluded from the build otherwise
Visual Studio will throw errors. To do this, right click on each file in the folder, select properties, and select 'exclude from build'.    

### Setting up the server
This week I wrote most of the server-side code for the websocket server. This can be found in ```\blackjack\src\server```. Here's a high
level overview of how the communication works:  
There are two types of clients. A ```Web Client``` and ```C Client```. Each player in the game will be a ```Web Client```, and through
a web interface they will be able to make game decisions (like hit or stay). There can be multiple Web Clients. There is one ```C Client```. This
client displays a graphic of the current game state, and the players can see their moves updated in real time on the ```C Client```.    

The ```GameConnection``` class serves as a wrapper for the connection objects and the ```GameConnectionManager``` processes all of the commands for the server. the ```ws_test``` file is the entry point to the server and it essentially just calls the game connection manager.    

#### Server Commands
This week, I implemented to following commands for the server:  
- ```SETNAME:<PlayerName>``` Sets the screen name of the player.
- ```ADDUSER:<PlayerName>``` Sent to the C Client to indicate that a new player joined.
- ```UPDATENAME:<PlayerName>``` Sent to the C Client to indicate that a player changed their name.
- ```SETTYPE:<Type>``` Sets the client type. ```<Type>``` Should be 0 (Web) or 1 (C).
- ```<CardNumber>:<PlayerName>``` Sends the ```<CardNumber>``` (0 to 51) to the ```<PlayerName>```. This can only be called by C Client.
- ```HIT:``` Sent by the web client to indicate they want to recieve a card. This can only be called by Web Client.
- ```STAY:``` Sent by the web client to indicate they want to stay. This can only be called by Web Client.

# Week Two (11/20 - 11/26)
### Connecting C Client to Web Socket
This week I tried using many different libraries to connect to the web socket server from the c++ client,
and none of them could be integrated well with the project. I tried using easywsclient, boostbeast, ofxlibwebsockets,
websocketpp, and various other libraries, but I couldn't get them to compile when added to the project.    

After spending about 15 hours trying to get these libraries to work, I decided that I would just send messages through the Windows OS between the client and server since they're running on the same machine. This could be achieved through using the ```WM_COPYDATA```
message provided by windows OS. I also ran into problems while implementing this and I decided to try using a websocket library for the C Client one more time. I tried using the [ofxLibwebsockets](https://github.com/robotconscience/ofxLibwebsockets) library again since it's an addon for openframework, so it should've been easy to integrate. I found that 
if I generated a new project with this addon (as opposed to using the update button in the project generator), and if I used Visual
Studio 2017, I could get this library to compile. So, I ended up generating a new project with this addon, and I moved all of the project files into this new folder. This ended up working well, so I can now connect the C Client to the websocket server.    


# Week Three (11/27 - 12/3)
### C Client Connection
I created a simple message handler for the C client so that messages could easily be sent between the server and client. 
I also created a ```WsMessage``` class to convieniently store metadata about messages from the server.    

### Game Logic
I created most of the logic for the actual blackjack game. This involved creating the following classes:
- ```GameManager``` Manages the blackjack game, the websocket connection, and the players.
- ```BlackjackGame``` Runs through a blackjack game, handling all the game logic.
- ```Deck``` Represents the draw pile.
- ```Card``` Represents a single card in the draw pile.
- ```Strategy``` An interface that declares what methods different types of players must implement.
- ```Player``` Implements ```Strategy``` and represents a player who is using the web client.
- ```Dealer``` Implements ```Strategy``` and represents a bot dealer.
  
I also created various utility classes and headers to hold constants. The general flow of a game, as managed
by ```BlackjackGame``` is as follows:    
The C client connects to the server and then the webclients join the game by sending their name to the server. The
players will be added to a match along with a dealer. Then they're dealt cards, then asked if they
want to hit or stand. After everyone makes a decision, anyone with a score greater than the dealer wins, and if there's
a tie, they both win. I started to add betting to the game, but I decided to wait to add that until later -- I want to get a running version of the game with graphics before I add this feature. I connected this game logic to my connection listener on the client side so that the web clients can actually send commands to the c client.

### Server Commands
I added a few more commands to the server:
- ```TIMELEFT:<Time>:<PlayerName>``` Sent by C Client to notify a web client that it is their turn and they have a certain amount of time left.
- ```TURNEND:<PlayerName>``` Send by C Client to notify a web client that their turn is over.
- ```WINNER:<PlayerName>``` Send by C Client to notify all web clients that someone has one.

### Web Client
I updated the HTML and Javascript of the web client a little bit. Now the users have a button to hit or stay, a
dialogue showing how much time is left in their turn, a dialogue showing what cards they have, and a dialogue showing
who won the round.

### Testing
I added catch2 testing to the project this week. I wrote about 45 assertions to test various clases and helper methods.

### Graphics
I just started implementing the graphics. I found free images to use for the background of the game and for each card. Most of my work next week will
be finishing up the graphics.

# Week Four (12/4 - 12/11)
### Graphics
I mapped each card to a file path and got each card to be drawn as the user is dealt cards. I also added a lobby screen where it shows the names of players as the join the
game. When the user presses space on this screen, the game starts. During the game if the user presses space at all, they will be returned to the starts screen. I updated the
grphics to show the score of each player throughout the round.

### Threading
One issue that I had was being able to forcibly stopping the game thread so that I could return to the lobby. I couldn't just modify the boolean tha the loop uses because that
would cause a race condition. After a lot of playing around, I found that I could use an atomic boolean to allow safe variable access between threads. This allowed me to stop
the game loop from the main thread.

### Refactoring
This week I spent some time refactoring my code and cleaning it up by adding comments where needed, removing unused methods and variabled, etc.