<!--
.. title: Intro to the Windows Command Line
.. slug: intro-to-the-windows-command-line
.. date: 2015-8-28 00:00:00 UTC-08:00
.. tags: windows, batch, commandline  
.. category: computing
.. description: Getting started with the windows command line to be able to do more with Windows.  
-->

## Introduction

Side Note - I've searched online to find info on many things related to technology. A typical search will yield a lot of blogs and tutorials, and way down the list there is documentation from the company/team that created the product. All this is OK, but i've found if you really want to learn something, the best way is a good old-fashioned book (pdf or print). The ideas are whole and complete, and the quality is much higher than a typical blog post (..yea, I know, this is a blog, and no it is not as good as a book).
And now for the big surprise. Most of my content is from books. I did not invent this stuff. And I think it is important to give credit where credit is due. For more information, check out an  A+ certification book (I got mine from goodwill for 3 bucks, isnb-9780071745154).


Ok, on to the post. This tutorial only applies to the windows command line, not powershell. To start out, I am not a huge Windows fan. It is expensive, and I am often disappointed in the stability. But, most of us use it at work and home, so we should be using to the best of our ability. So this should help extend your skills at doing basic stuff. There are a few things that I will show you that I prefer to use a mouse and keyboard with, but there are a few things I would rather use the command line with (eg, moving files, mouse, finding the ip address of the computer, keyboard). Also, I am using Windows 7.

Lets get started. To get to a command prompt, we can **hold shift and right-click** and select **open command window here**. This is nice because we do not have to change the directory to the our directory we want to work from. You can also just type ```cmd``` in the start menu.

If you ever run a command and it is taking forever to finish, we can terminate the command with **ctrl+c** while in the command prompt.

if you need general help on any command, use
```
help

```


Now, lets get our keyboard hands "dirty".

## File Information
The first command is **dir**. This shows the content of the directory (dir) you are in.

```bat
> dir

 Volume in drive C has no label.
 Volume Serial Number is 5033-5C23

 Directory of C:\Users\ngordon\Desktop\test

08/28/2015  07:44 AM    <DIR>          .
08/28/2015  07:44 AM    <DIR>          ..
08/28/2015  07:44 AM    <DIR>          another-test
08/28/2015  07:44 AM                 0 file1.txt
08/28/2015  07:44 AM             8,746 file2.xlsx
08/28/2015  07:44 AM                72 tmp.txt
               3 File(s)          8,818 bytes
               3 Dir(s)  38,038,937,600 bytes free

```

This is an easy way to see all the files and folders in our current directory. If you want to preserve this information, we can redirect the output to a file *tmp.txt* with
```bat
dir > tmp.txt
```

To get help on the command dir, use
```
dir /?
```

If you just want to see the filenames in 5 columns, we can use a *switch* with the syntax */W*, which looks like this
```
> dir /W
 Volume in drive C has no label.
 Volume Serial Number is 5033-5C23

 Directory of C:\Users\ngordon\Desktop\test

[.]            [..]           [another-test] file1.txt      file2.xlsx      tmp            tmp.txt        
               4 File(s)          9,187 bytes
               3 Dir(s)  38,019,055,616 bytes free
```

### Wildcards
If there are alot of files, using wildcards can reduce the clutter. Also note the ```::``` are commets.

```
:: finds all files
dir *.*

:: finds all files with the extension xlsx
dir *.xlsx

:: finds all files that start with a
dir a*.*

:: finds an exact file
dir file1.txt

```


### Tree
Another cool visual is with the **tree** command. Just using the tree command only shows the folders in the current directory, which shows up fine in the command window, but is not ascii text.
```
> tree
Folder PATH listing
Volume serial number is 5033-5C23
C:.
\---another-test
```

If you want to see ALL the files on your current disk, use the backslash. This may take a while to run on your system drive (C), so remember **ctrl+c** to cancel
```
tree \
```

I prefer being able to copy and paste those results into documents. Lets try and figure out how to change the command to give me ascii characters.
```
> tree /?
C: /?
Graphically displays the folder structure of a drive or path.

TREE [drive:][path] [/F] [/A]

   /F   Display the names of the files in each folder.
   /A   Use ASCII instead of extended characters.
```

Ah ha. We need to add switches to do that. If you want to see the folders and files in the current directory, try
```
> tree /F

Folder PATH listing
Volume serial number is 5033-5C23
C:.
│   file1.txt
│   file2.xlsx
│   tmp.txt
│
└───another-test
        file3.txt

```



Lastly, to create an ascii format list of all files and folders and dump it to a text file, try
```
tree /F /A > tree.txt
```

### attrib

We can also use **attrib** to get file information in the current directory. The *A* stands for archive.
```
> attrib

A            C:\Users\ngordon\Desktop\test\file1.txt
A            C:\Users\ngordon\Desktop\test\file2.xlsx
A            C:\Users\ngordon\Desktop\test\tmp
A            C:\Users\ngordon\Desktop\test\tmp.txt
```

## Navigating

If you want to navigate your system, the cd command is the ticket, to go towards the root of the drive, use **cd**
```
cd ..

:: or to go directly to the root

cd \

:: or for multiple traverses

cd ..\..


```

and to go into another folder use
```
cd test

:: or for multiple folders

cd Desktop\test\another-test
```

This can become tedious, so I'd recommend using **tab** when typing out names. It not only reduces the amount of typing you have to do but also reduced typos.


Lets say you want to search your usb drive. To switch to a different drive other than the default **C:**, just type

```
E:
```

Another modern and handy way to navigate is typing ```cd ``` and dragging and dropping a folder into the command prompt and hitting enter. This can save some time on those deep folder structures.




## Managing Folders and Files

OK, lets make some stuff. To create and destroy a new directory, use **md** and **rd**
```
:: create directory
md newfolder


:: destory an empty directory
rd newfolder

:: BE CAREFUL - recursively destroy directory, and all files and subfolders
rd newfolder /S

```

To copy a single file or groups of files, use **copy**
```
copy file1.txt file10.txt

:: or to copy to a different folder

copy file1.txt another-test\file1.txt

:: or copy all txt files to the subdirectory another-test

copy *.txt another-test
```

To copy an entire directory, we can use **xcopy**

```
:: copy directory another-test and skips empty subdirectories to another-test2
xcopy another-test another-test2

:: to include empty subdirectories, use switch
xcopy another-test another-test3 /E
```


We can rename files or folders with **ren**
```
ren file1.txt text1.txt

:: or more complicated names with spaces
ren text1.txt "text 1.txt"

::change directory name
ren another-test another-test5

```

To delete a file or files, use **del**
```
del tmp.txt

:: deletes all text files in the current directory
del *.txt
```

## Creating New files

It appears that Microsoft deprecated *edit*, the command line editor. For those of you familiar with [vim](http://www.openvim.com/) or [nano](http://www.nano-editor.org/), this are available on windows, so check them out. But for now, we can use the echo command, to create text files and append them

We can use **echo** to print text to the command window
```
echo hi there
```

Or we can redirect the text to a file

```
echo this is my first command line text file > file8.txt
echo this is the second line >> file8.txt
echo this is the third line >> file8.txt
```

for more complicated stuff, we can always open the file with the default text editor notepad.
```
notepad file8.txt
```

## Automating commands with a batch file

A batch file (*.bat) is a simple windows script that can automate simple tasks.

```bat
echo echo hi there > hello.bat
```

Now we can run the batch file by simply typing the name and executing it
```
hello.bat
```

To pause to execution of a bat file, add **pause** to the end. This is nice if you have an error in the file and want to see what the error is, otherwise it will just close the window
```
:: waits for keyboard input from user
pause
```

## Advanced command line

To see all the settings Windows loads by default, use
```
> set
ALLUSERSPROFILE=C:\ProgramData
CommonProgramFiles=C:\Program Files\Common Files
CommonProgramFiles(x86)=C:\Program Files (x86)\Common Files
CommonProgramW6432=C:\Program Files\Common Files
HOME=C:\Users\ngordon
HOMEDRIVE=C:
HOMEPATH=\
Path=C:\Program Files\Common Files\Microsoft Shared\Windows Live
```

A common task is adding a program, exe or other, to the default list windows looks for when running. If we want to be able to run a program without executing the command from that directory, we have to add it to the path variable

Lets switch to the root of our c drive and create a folder called batch, and create a batch file that says *hi there*, and add it to the path so we can be greeted anywhere we are

```
:: go to the root of the c drive
cd \

:: make a new directory
md batch

:: go into the directory
cd batch

:: create a new batch file that says hi there
echo echo hi there > hello.bat

:: add this new folder to the system path
path=%PATH%;c:\batch

:: move out of the directory and check and make sure the system path works. This moves us to our home directory
cd %HOME%
```

Now lets test and make sure the system knows where to look for my custom batch scripts.
```
> hello
hi there
```

Excellent. We have covered the basics.

## Networking Information
I have found myself using the command line alot when learning about networking. Here are some commands to help you get started with networking info.

```
:: robust command for networking options, such as seeing things on the network
net view

:: test the communication of another ip address
ping www.ifcuriousthenlearn.com

:: show network settings
ipconfig

:: tool to find networking information
nslookup www.ifcuriousthenlearn.com

:: traces the path a packet takes to get to the destination
tracert www.ifcuriousthenlearn.com
```

## Summary
We have covered the basics to operate a windows command line. For a lot of work, it is faster than clicking a mouse around, but it takes some practice. There are also some great fundamental tools available found at the command line nearest you. Understanding what is going on in a computer is much easier when you can operate the command lines, as it is an integral part of any operating system. I hope you found this useful, and please comment with any suggestions.

Stay Curious!  
