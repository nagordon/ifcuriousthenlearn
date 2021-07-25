<!--
.. title: Windows package management with Chocolatey
.. slug: testing-markdown
.. date: 2016-05-06 00:00:00 UTC-08:00
.. tags: Windows, software
.. category: 
.. link: 
.. description: Easy software installation and updates in Windows.
.. type: text
-->


For most of us, using software is an everyday activity. Many of us use lots of different packages of software, especially those that does not come pre-installed, like notepad++, chrome or firefox, ebook managers, your favorite video player, etc. Installing that software every time you get a new computer or keeping all those packages up-to-date can be a challenge. Being a Windows user for most of my life, I've accepted the tedious, risky business of finding, installing and not getting viruses from Windows software. Not until I started using Linux did I realize that it can be easier and safer. Linux uses package management, that changes from distribution, but the popular Debian based Linux uses ```apt-get``` to install software from the command line. Installing software can be as easy as ```apt-get install firefox```, and updating all software on the computing can be done with ```apt-get update```. Really easy right?

Well, I still use Windows a lot, and installating and managing software on Windows can be be much easier using [chocolatey](https://github.com/chocolatey/choco/wiki). Chocolatey is a Windows command line tool to manage software, including searching, installing, updataing and removing.

Installation is a cinch. Copy and paste this code into a windows command line access by searching for ```cmd``` in the windows start. If possible, run as administrator (cmd, right-click, run as administrator)
```
@powershell -NoProfile -ExecutionPolicy Bypass -Command "iex ((new-object net.webclient).DownloadString('https://chocolatey.org/install.ps1'))" && SET PATH=%PATH%;%ALLUSERSPROFILE%\chocolatey\bin
```

I typically just search the chocolatey website for the package I want to install and type that into the command line. The example I want to share is my favorite ebook manager, calibre. One of the reasons I enjoy chocolatey with calibre is because calibre is updated a lot, and to keep up with them, you have to go download the calibre exe, and follow the prompts for the installation. Or a simple command will do it all! The ```-y``` is a flag to indicate ```yes``` to eliminate the need to confirm the installation.
```
choco install calibre -y
```

Updating calibre is as easy as this
```
choco update calibre -y
```

Multiple packages can be installed by leaving a space between the names
```
choco install notepadplusplus googlechrome atom 7zip
```

And to update all the packages that were install with chocolatey, this command will take care of it all
```
choco upgrade all -y
```

I think chocolatey is a really neat, useful package that has saved me a lot of time, and I hope it helps alleviate some of your windows woes.
