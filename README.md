# Blackjack
### Download Dependencies
This project is intended to run on Windows 10 with Visual Studio 2017. This project may not work on differnet
operating systems and will only run in Visual Studio 2017.    

First download Visual Studio 2017 Community Edition and follow the installation instructions. Then clone this
repository into any folder on your computer.
    
Next download [OpenFrameworks](https://openframeworks.cc/download/) and choose the Visual Studio 2017 version.
After installing this, locate the addons folder located inside the openframeworks folder, and install 
[ofxlibwebsockets](https://github.com/robotconscience/ofxLibwebsockets) in this folder. Follow the installation
instructions on that github page.
    
After that's installed, use the openframeworks project generator to setup this project. For the project name box,
just type in the name of the root folder that this repository was cloned to, and for project path, put the
path that the root folder is in. If you setup ofxlibwebsockets correctly, you should be able to select it as an
addon. Now just press the update button.
    
You will also need [Seasocks](https://github.com/mattgodbolt/seasocks/wiki/Seasocks-quick-tutorial) to run the 
project. Just clone the seasocks repository into ```blackjack/src/seasocks```, and follow the cmake instructions
on the seasocks github.

#### Running the project
To compile the project you will need to exclude all files in ```blackjack/src/server``` from being included in
the build except for ```ConnectionConstants.h```. This can be done by right clicking each file, selecting properties,
and choosing 'yes' for 'exclude file from build'. The project architecture will also need to be set to x64 in order to run.
  
Before you run the project you must start the websocket server. You can do this by navigating to the ```seasocks```
folder in a terminal and then run ```build/src/test/ws_test```. If seasocks was configured correctly, the server
should be running on localhost:9090.
    
Now you should be able to run the project in Visual Studio.