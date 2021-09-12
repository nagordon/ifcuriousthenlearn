<!--
.. title: Automating Website Downloads with wget
.. slug: wget-downloads
.. date: 2015-08-19 00:00:00 UTC-08:00
.. tags: linux, webscraping, automation
.. category: computing
.. description: If you like a website, download and keep it forever. Or, if there are a bunch of files, say pictures or pdfs you want on a website, don't click to download all of them. Scrap it!
-->

Have you ever been browsing the internet and found a really cool website that has a bunch of files that you want, say pdfs or mp3s? In Windows it can be a pain to scrape through the site and download all the files. You may be able to write a slick python script to acomplish this, but why reinvent the wheel? Native in Linux is the program wget, which can also be used in windows, [GNU wget](http://www.gnu.org/software/wget/).

To get started, on a Linux computer, open your terminal and type

```bash
man wget
```

This shows the manual for wget for when you get stuck. But for now, we don't need it, so type `q` to quit. OK, time for the rubber to hit the road. Enter

```bash
wget www.ifcuriousthenlearn.com
```

This downloads the html file that is at that url. Easy huh? Lets try something a little more complicated, lets say download a pdf

```bash
wget http://www.aopa.org/airports/CLE/kneeboard.pdf
```
And this downloads the pdf from the url. Wow, can it really be this easy? YES, yes it can. It just takes a while to find cool tools like this.

Here is a more advanced example. This wget command searches recursivley and downloads the entire website given.  

```bash
wget --recursive http://www.brown.edu/Departments/Engineering/Courses/En221/
```
The problem with this is that it will follow any links as it recurses through the site, and we don't want that. So, by adding another flag, called ```--domains```, we limit the command to the domain of the main site.

```bash
wget --domains www.brown.edu --recursive http://www.brown.edu/Departments/Engineering/Courses/En221/
```

What if we just want to download certain file types? Here, use the ```--accept``` flag with the file extension
```bash
wget --accept .pdf --domains www.brown.edu --recursive http://www.brown.edu/Departments/Engineering/Courses/En221/
```

There we have it. Have fun download the internet, saving time and exploring other awesome packages in Linux. I hope you found this useful. Please leave any comments below.

Stay Curious!
