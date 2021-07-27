<!--
.. title: Team Fortress 2 Server Install for Dummies
.. slug: tf2-server-setup
.. date: 2015-03-14 00:00:00 UTC-08:00
.. tags: linux, gaming
.. category: computing
.. description: How to set up a Team Fortress 2 steam server-setup
-->

For those of us who remember playing games on dos, steam[http://store.steampowered.com/]
is a nice program for purchasing, managing, and playing video games. I grew up playing LAN games because dial-up just wasn't fast enough for online gaming, and it is way more fun to play games in the same room with your friends rather than random people online.

Things have changed since those days. Internet speeds and just fine for online gaming, but I still prefer LAN games because, again, it is way more fun to game with your friends in the same room. So, I enjoy hosting LAN games, and I found setting up a local server a fun technical challenge, and If you are interested in doing the same, this should help you do it.

The cool things with steam servers is you don't even need an account. You can create an anonymous server that is not affiliated with you.

##**Step 1** - Get a free operating system
Get a Debain based Linux computer. I am using an older samsung laptop (6 GB, i5 processor) running [mint-cinnamon](http://www.linuxmint.com/edition.php?id=172)

##**Step 2** - Install dependent software
Get to your linux terminal and install the required software by running this command
```sudo apt-get install gdb mailutils postfix lib32gcc1```

##**Step 3** - Create server user account
Create a user for the server admin, assign a password, and login to tf2server account
```bash
adduser tf2server
passwd tf2server
su tf2server
```

##**Step 4** - Install steam server software
There are multiple ways of doing this. One is to follow the [steam installation](https://wiki.teamfortress.com/wiki/Linux_dedicated_server) or another [tutorial](http://stevenbenner.com/2010/11/how-to-set-up-a-team-fortress-2-dedicated-server-on-ubuntu/) or [another tutorial](http://danielgibbs.co.uk/lgsm/tf2server/), which is what I recommend and used.  

This will download the script, make it executable, and execute the installation
```bash
wget http://danielgibbs.co.uk/dl/tf2server
chmod +x tf2server
./tf2server install
```

##**Step 5** - Start the server
Go to the tf2server home directory ```cd ~``` which will take you to ```/home/tf2server/``` and use these commands to manage your server  
```bash
./tf2server start
./tf2server stop
./tf2server restart
./tf2server details
```

Type ```./tf2server start``` to start the server

##**Step 6** - Connect via LAN

if you run ```./tf2server details``` you will see a bunch of output  
```
Team Fortress 2 Server Details
================================================================================================================================================
Server name:    tf2 server 1
Server IP:      192.168.1.196:27015
RCON password:  tf2server
Status:         ONLINE

Command-line Parameters
================================================================================================================================================
./srcds_run -game tf -strictportbind -ip 192.168.1.196 -port 27015 +clientport 27005 +tv_port 27020 -tickrate  +map pl_goldrush +servercfgfile tf2-server.cfg -maxplayers 16
```

what we want here is the local ip and port ```Server IP: 192.168.1.196:27015```

Now we can connect locally by launching Team Fortress 2, hit ```~``` to drop down the console and type ```connect 192.168.1.196:27015``` and that should connect you to the server locally

##**Step 7** - Set up a Public Server
If you want to make this a public server, we need to do a few more things. First, I needed to remove the ```-strictportbind``` portion on the command-line properties in the file located in ```/tf2server/tf2server``` file so that an unused port is chosen, so when you restart the tf2server, it may choose a different port to allow for online access.

After that, I access my default router IP via a web browser with ```192.168.1.1``` and set up a port forward on the server IP and port

Now, restart the tf2server with ```./tf2server restart``` and go to the console ```./tf2server console``` and look at some of the output. Note, this script uses tmux, which allows us to log out of the server and keep the server running. Here, you can run all the comamnds to manage the server

You should see somewhere in the top the public ip address of the server computer
```
Connection to Steam servers successful.
   Public IP is 12.34.56.78.
```

and

```bash
Network: IP 192.168.1.196, mode MP, dedicated Yes, ports 27015 SV / 27005 CL
```

##**Step 8** - Connect to your public server
Now we have all the information we need to create public server, the public IP and the SV port it selected. Finally launch Steam and do
>Severs -> Favorites -> Add a Server -> enter ```12.34.56.78:27015```

Now you have a public server!

if you want to play without people, add some bots. Go to your console via ```./tf2server console``` and add some bots```tf_bot_add 4``` change the level to ```changelevel pl_goldrush```

I have found many maps don't work well with bots. The maps I have listed below seemed to work well.

## Server Customization
To customize your server there are a few files you should edit. Make sure you make a backup of each in case it gets messed up

The configuration file updates the server every time a new map loads. Here is mine.
/home/tf2server/serverfiles/tf/cfg/tf2-server.cfg
```
mp_disable_respawn_times 0
tf_bot_quota 13
tf_bot_quota_mode "fill"
tf_bot_difficulty 1
mp_timelimit 15
mp_maxrounds 5
mp_winlimit
sv_cheats 0
tf_bot_melee_only 0
```

/home/tf2server/serverfiles/tf/cfg/mapcycle_default.txt
The mapcycle file tells the server which map to go to next. if you use ```changelevel pl_barnblitz```, it will begin the cycle there
```
pl_badwater
pl_goldrush
pl_upward
pl_barnblitz
pl_hoodoo_final
koth_viaduct
koth_nucleus
koth_harvest_final
koth_lakeside_final
koth_badlands
koth_king
plr_pipeline
plr_hightower
pl_thundermountain
pl_frontier_final
```
If you want to use your xbox controller, from the client computer access the console via ```~``` and run ```exec 260controller```

Enjoy!

Here are some links that I found helpful   
https://wiki.teamfortress.com/wiki/Linux_dedicated_server  
http://danielgibbs.co.uk/lgsm/tf2server/  
http://stevenbenner.com/2010/11/how-to-set-up-a-team-fortress-2-dedicated-server-on-ubuntu/  
https://developer.valvesoftware.com/wiki/List_of_TF2_console_commands_and_variables  
https://developer.valvesoftware.com/wiki/Console_Command_List  
http://steamcommunity.com/sharedfiles/filedetails/?id=250332112  
https://wiki.teamfortress.com/wiki/Linux_dedicated_server  
https://wiki.teamfortress.com/wiki/Bots  
