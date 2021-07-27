<!--
.. title: The Fastest Way To Linux on Windows using Vagrant
.. slug: vagrant-linux
.. date: 2015-08-18 00:00:00 UTC-08:00
.. tags: linux
.. category: computing
.. description: An guide for intermediate Windows users looking to start using Linux.
-->

## Introduction and Motivation
This article is written for Windows users that would like to extend their skill-set to Linux and assumes you are comfortable with the command line. Go brush up before reading this if you are unsure what a command line is:)

I wish I would have spent more time as a kid learning Linux than all the time I wasted on Windows. That is my biggest regret when it comes to technology. Once I started to see all the amazing software available on Linux (for free), I realized the potential . The road to practical application wasn't easy, but it was fun. Now, with a few years under my belt, I am able to save time utilizing the tools that already exist, or having the capability to create my own without having to buy licenses for them!

This post is designed for the intermediate Windows users that are ready to start using Linux for whatever reason you have. I think the easiest way (but not the most useful) to use Linux is to install [Mint](http://www.linuxmint.com/edition.php?id=190), install on a usb drive larger than 4 GB with [win32diskimager](http://sourceforge.net/projects/win32diskimager/), [unebootin](http://unetbootin.github.io/), or [pendrivelinux](http://www.pendrivelinux.com/universal-usb-installer-easy-as-1-2-3/). Now, just boot from the USB and you are ready for action. But, this is not a practical working solution, especially at work or at home if you need other windows applications. The ideal situation is if we can use Linux and Windows along side one another. **Enter [VirtualBox](https://www.virtualbox.org/wiki/Downloads)**. Virtualbox is a program that allows you to *virtualize* other operating systems on your current one, is open-source, and works great. You can collect a few ISO files of your favorite Linux operating systems (check out [distrowatch](http://distrowatch.com/)), and install them on VirtualBox and use the operating system (OS) graphical user interface (GUI). This method has its time and place, like if you prefer using a GUI for everything, then there is no need to read further. But, I encourage you to learn command line operation, as it is faster and easier to operate many programs from a command line as it is to mouse-click through them. Or when you start developing your own software tools, it will become clear why command line operation is nice. Anyways, there is yet an easier way to use Linux. **Enter [Vagrant](https://www.vagrantup.com/)**. Vagrant is a command line tool that allows you to manage your Virtualbox operating systems from a command line and easily share files from Windows and Linux. The general workflow is:

1. Install Vagrant and dependencies
2. Download a base image called a box to be used and reused as you create new virtual Linux environments
3. Make a folder to store your virtual Linux settings in Windows
4. Initialize Vagrant in that folder
5. Install software and use Linux in Windows from the command line


>Why Vagrant?
There are other programs that can perform a similar task as what we are trying to accomplish  here, such as [Docker](https://www.docker.com/). Docker is an amazing tool that runs containers, rather than virtual environments. But, my goal here is to get from Windows to Linux in the fastest time possible, and I have found that Docker in Windows is a bit finicky and Vagrant is so far rock-solid.

## Getting Started

### 1. Installation

OK, time to get our hands dirty. There are a few programs we need to install before we get to vagrant, so lets do that first.

#### Git Install (~10 MB)
git is a source control program that is awesome to use, but has a steep learning curve. All we need from this install is mysysgit, which is a windows bash terminal, which is like the windows command line for Linux. Download and install [git](https://git-scm.com/downloads) and select the defaults. At the end of the install, select ```[x] git bash here``` to give us an option to start a bash command prompt with a right-click of the mouse in our folder

#### VirtualBox Install (~110 MB)

Download [VirtualBox](https://www.virtualbox.org/wiki/Downloads) and install with the default settings.


#### Vagrant Install (~160 MB)

Install [Vagrant from the Windows exe](https://dl.bintray.com/mitchellh/vagrant/vagrant_1.7.4.msi). Once that is complete, it will ask you to reboot your machine.

#### Using gitbash and windows command line
Now we are almost ready to try everything out!
if you right-click on your desktop, you should have an option to ```Git Bash Here.```. Select that an you should be greeted with MINGW32 (aka gitbash) command prompt. Welcome to your first *bash-like* command prompt. You can perform all the vagrant opertions in windows using gitbash, but we can also use windows command line for everything, but not ssh connections. We must use [putty](http://www.chiark.greenend.org.uk/~sgtatham/putty/) or some other windows ssh tool.

If you really want to use the windows command line, here are some tips.
Lets close that and try out the windows command line. My favorite way to launch the windows command line is to hold shift and right-click on the desktop and select ```open command window here```. Now we have windows command line. We can also access this by searching in Start, but then you have to use the ```cd``` command to change yuor directory to your vagrant_test.  Another option is to type ```cd```, copy the folder path to the clipboard, ie *C:\Users\ngordon\Desktop\vagrant_test* and right-click in a command prompt and paste and enter. This will take you to your folder.
And lastly, after that nice explanation, don't use windows command line, use powershell, which is an enhanced command line for windows that has many of the same features as bash. launch from the command line with ```powershell```

I would recommend doing everything in gitbash because it is good practice for a real Linux bash terminal and we can use ssh all in the same window.

### 2. Download Base Image (~1 GB)

To make future deployments fast lets grab a base image of Linux Ubuntu 14.04. Go to your windows desktop and launch a windows command line as described previously, or, I prefer using gitbash. Note, comments in gitbash are #, so do not type those

Lets add Ubuntu Server 14.04 LTS 62-bit image to our local vagrant images. Or browse the [catalog](https://atlas.hashicorp.com/boxes/search) for your preferred image
```bash
vagrant box add ubuntu/trusty64
# or hashicorp/precise64 for a 12.04 LTS 64 machine
# or chef/ubuntu-14.04  for a base 14.04 LTS 64 ubuntu machine
```

### 3. Set up a work folder

This will take some time to download, but once complete. The rest of the operations are a matter of seconds.

```bash
# make a new folder called vagrant_test
mkdir vagrant_test

# change directory to vagrant test
cd vagrant_test

# print working directory to check the file path
pwd
```

### 4. Initialize a new Vagrant project
Now we have everything we need to start. After running the following commands, a config text file *Vagrantfile* will be created with a hidden file *.vagrant*

```bash
# initializes this vagrant session with the image we downloaded
vagrant init ubuntu/trusty64

# starts the virtual machine
vagrant up
```

Once the box is set up, make sure you have git install to access the MINGGW32 bash terminal in windows. From the *git bash* found when you right-click in an empty space in your *vagrant_test* folder, type

### 5. Access your brand new Linux machine on Windows!

```bash
# using ssh to access the shell of your machine
vagrant ssh

# and when finished exit ssh
exit
```
and that will enter an ssh shell into the vagrant box. Finally, we have a true linux bash command line or shell!! Horray. The hardest part is over, celebrate and get ready to actually hace some fun

### 6. Using File Sync
One of the most confusing and challenging parts of Linux is networking. Vagrant does an awesome job of transferring files to and from your vagrant session, ie, The VM syncs easily with the host machine. To test the sync feature, in your current bash shell,

```
# create a directory called test
mkdir /vagrant/test

# create a file called test.txt and add a string to it
echo "testing the files sync in a vagrant VM" >> /vagrant/test/test.txt
```

### 7. Reloading, Stopping, and Starting

```bash
# To reload a VM and reload any new changes in the Vagrantfile config run
vagrant reload

# When complete and want to exit, run
vagrant halt

# When you are ready to start working again and starting fresh
vagrant up

```

### 8. Running scripts and Installing programs
#### Issues with writing bash scripts in windows
As you start editing install scripts and the Vagrantfile, I have found that using windows text editors messes up the character encoding, so use gitbash and vim, like ```vim install.sh``` to launch the in shell editor. If you do edit files in windows, you may need to convert them. I have found dos2unix to work well. To install and convert a shell script in place, use

```bash
sudo apt-get install dos2unix
dos2unix script.sh
```
#### Installing python
There are many ways to install python, but I really appreciate how well conda works. It has all the packages I want, and they just work. To get conda either install the full package [anaconda](http://continuum.io/downloads#all) or, I prefer [miniconda](http://conda.pydata.org/miniconda.html) because my internet is slow. Also, I attempted to create a silent install script but was not successful, so if anyone knows how to perform a silent install of miniconda on a vagrant machine, please let me know!
```bash
git clone https://github.com/nagordon/vagrant-miniconda.git
cd vagrant-miniconda
vagrant up
vagrant ssh
```

copy and paste these commands line by line into the vagrant shell to manually install miniconda

```bash
# downloads miniconda
wget http://repo.continuum.io/miniconda/Miniconda-latest-Linux-x86_64.sh

# makes the miniconda installation executable
chmod +x Miniconda-latest-Linux-x86_64.sh

# installs miniconda manually. Make sure you select yes for adding the path. Also spacebar to skip the documentation at the beginning
bash Miniconda-latest-Linux-x86_64.sh

# remove the downloaded fil
rm Miniconda-latest-Linux-x86_64.sh

```

now close the ssh connection and restart to access conda
```bash
exit
vagrant ssh
```

Run the install script to get all the packages you want

```bash
conda install pip -y
conda install numpy -y
conda install ipython -y
conda install matplotlib -y
conda install pandas -y
conda install numpy -y
conda install ipython-notebook -y
```


### 9. ENJOY

Now that we have everything running smoothly, go out an explore all the amazing software out there on Linux and enjoy.

## Summary

In my experience, this is the fastest and easiest way to get from Windows to a real Linux environment. Now, practicing Linux operation from the command line should be easier and fast without having to mess around with the operting system interface. I hope you enjoy your foray into Linux as much as I have. Please let me know if you have any questions, comments, or suggestions. Thanks! Stay Curious!
