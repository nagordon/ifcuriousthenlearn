This folder contains the source used to generate a static site using Nikola.

Installation and documentation at https://getnikola.com/

Configuration file for the site is ``conf.py``.

To build the site::

    nikola build

To see it::

    nikola serve -b

To check all available commands::

    nikola help



    

pip install -U "Nikola[extras]"

nikola init --demo mysite

nikola build

nikola new_post

nikola serve -b

nikola new_post -f markdown

nikola new_post -f ipynb

nikola github_deploy