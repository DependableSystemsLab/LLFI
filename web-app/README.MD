Dependencies:
Nodejs.
webpack   

Steps to set up the development environment:   
1: Download this project from Git   
2: Download NodeJs   
3: Install libraries: Go to the web-app directory and run "npm install"   
4: Install Webpack: In the same directory as step 3, run "sudo npm install -g webpack"   
5: Configurate the LLFI root path for the server:   
The default bevaiour of the program use environment variable $llfibuild as the path of the llfi build directory  
You can set the environment variable llfibuild in your system to point it to the LLFI build directory in your local machine.   

Start the server:   
Go to the /web-app/server folder and run "node server.js"  

Start the front-end dev tool:   
Go to the web-app directory and run "webpack" or "webpack -w"   
