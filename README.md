# ifcuriousthenlearn  

my blog about learning and technology  
https://nagordon.github.io/ifcuriousthenlearn/  

github page source code  
https://github.com/nagordon/ifcuriousthenlearn  

This folder contains the source used to generate a static site using Nikola.

Installation and documentation at https://getnikola.com/

Configuration file for the site is ``conf.py``.

I generally use conda on windows with python, so all commands here are in the anaconda prompt

To create a new post rst formatted post. for more details, see https://getnikola.com/handbook.html#creating-a-blog-post

    nikola new_post
    # or open editor
    nikola new_post -e    
    # or to specify the post format  
    nikola new_post -f rest
    nikola new_post -f ipynb
    nikola new_post -f markdown

To get help with the `new_post` command  

    nikola help new_post

To build the site once locally to see if it works

    nikola build
    # or build automatically
    nikola build -a

To run a local webserver and open a browser, or view at http://127.0.0.1:8000/

    nikola serve -b


or to do both build and serve automatically
    
    nikola auto --browser

To check all available commands

    nikola help

# drafts

change metadata from  
```.. status: draft```  
to  
```.. status: published```



# install nikola with conda on windows  
```python 
pip install -U "Nikola[extras]"  
```


# deploy to github  

```
nikola check --clean-files  
nikola github_deploy  
```

## image compression

To add images to post, compress them first

`GIMP -> Export As -> 30% Quality and uncheck Save Exif info`

or  

`nomacs -> Save As -> Bad Quality`

## author contact

`Neal`

`3792276+nagordon@users.noreply.github.com`

## Helpful Links 

### formatting tips  
https://getnikola.com/creating-a-site-not-a-blog-with-nikola.html  

### Rst formatting

https://getnikola.com/quickref.html

https://github.com/ralsina/rst-cheatsheet/blob/master/rst-cheatsheet.rst  
https://www.sphinx-doc.org/en/master/usage/restructuredtext/basics.html#rst-primer  
https://www.getnikola.com/quickref.html#comments  

https://www.writethedocs.org/guide/writing/reStructuredText/  
https://www.sphinx-doc.org/en/master/usage/restructuredtext/basics.html  
https://docutils.sourceforge.io/docs/ref/rst/restructuredtext.html  

https://sphinx-tutorial.readthedocs.io/step-1/  
https://rest-tutorial.readthedocs.io/en/latest/Basic_reStructuredText.html  

### nikola  

https://getnikola.com/handbook.html  


