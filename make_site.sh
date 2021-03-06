'''
# find python interpreter
import sys
print(sys.executable)

# python server
cd output
python -m http.server

'''# run with git bash on windows

### use
# bash make_site.sh

# local build
# pelican content -s pelicanconf.py

# preview site and rebuild when changes occur
pelican --autoreload --listen
http://localhost:8000/


pelican content -s publishconf.py

#git add site && git commit -m "site subtree commit"
#git add --all && git commit -m "added site source code"
#git subtree push --prefix site origin gh-pages
#rm site

# #-p    ##-p is a push
ghp-import output -m "updated doc webpage on gh-pages branch"

rm -rf output
rm *pyc

# add all master branch files
git add --all
git commit -m "auto add changes to master branch and updated gh-pages"
git push --all origin
