## this are my notes as a walkthrough of the tutorial found here
# http://prof.beuth-hochschule.de/groemping/software/design-of-experiments/project-industrial-doe-in-r/

# opens RCommander with the DOE plugin
require(RcmdrPlugin.DoE)

myDir = "E:/github/technotes/R/DOE/Neal_DOE_Tutorial"

setwd(myDir)

# the workspace can be saved as a *.rda or *.Rdata file
# the workspace does not store figures, plots, or code history

"
General procedure for setting up DoE

* Design -> Create Deasign -> Screening Design
* Set Name, number of runs, factors, and factor details
* Select Button View data set and review the experiment
* Export the experiment to be completed with Design -> Export -> Export Experiment. 
  This will export a rda, html, and csv file. 
* add a column to the csv file with the response variable and standard deviation
* Design -> Re-import experiment from csv and rda
* 

"

# 1 - Create Experiment
## In Rcommander, Design -> Create Design -> Screening Design

## In Base Settings
## runs = 12
## [x] 12 run design in Taguchi order
## factors = 8

## In Factor Details
Screen.example <- pb(nruns= 12 ,n12.taguchi= TRUE ,nfactors= 12 -1, 
                     ncenter= 0 , replications= 1 ,repeat.only= FALSE ,randomize= TRUE ,seed= 
                     20187 , factor.names=list( AirVolume=c(198,672),Valve=c(1,2),Barrel=c("4ft",
                     "6ft"),Angle=c(45,60),Pressure=c(20,40),WadType=c("paper","cloth"),
                     Voltage=c(9,27),BallType=c("white","pink") ) )
## creator element of design.info will be different, when using the command line command!

# show current experiment
print( Screen.example )

# Summarize experiment
summary( Screen.example , brief = FALSE)



# if the experiment has already been created
#load("E:/github/technotes/R/DOE/Neal_DOE_Tutorial/Screen.example.rda")



# 2 - Export experiment to be run
## Design -> Export -> Export experiment

# exports a csv that can be filled in with the response variables

export.design(Screen.example, type="html",
              path=myDir, file="Screen.example", 
              replace=TRUE, OutDec=".")




# 3 For this example, 4 shots are made and the mean and stdev are recorded as response variables
## Design -> Import -> Re-import experiment from csv and rda files

Screen.example <- add.response(Screen.example, myDir, replace=FALSE, InDec=".")

# show updated experiment with response variables
print( Screen.example )

# Summarize experiment
summary( Screen.example , brief = FALSE)




# 4 - Analyze Results
## Design -> Analyze Design -> Effects plot...

## Create a half-normal plot
DanielPlot(Screen.example, code=TRUE, autolab=TRUE, alpha=0.1, half=TRUE, 
           response="mean")
# observe that Pressure, Airvolume, Angle, WadType have the largest effect, respectivley 


## Create a Linear Model, remove dummy regressors e1,e2,e3
LinearModel.1 <- lm(mean ~ AirVolume + Valve + Barrel + Angle + Pressure + 
                      WadType + Voltage + BallType, data=Screen.example)
                    summary(LinearModel.1)
# observe that Pressue, Airvolume, Angle, Wadtype have the largest absolute value t value
                    
                    
## Main effects plot
MEPlot(Screen.example, abbrev=4, select=c(1,2,3,4,5,6,7,8), response="mean")
# observe that Pressue, Airvolume, Angle, Wadtype have the largests slopes

## Another Effects plot
## Models -> Graphs -> Effects Plots
library(effects, pos=25)
plot(allEffects(LinearModel.2, partial.residuals=TRUE), span=0.5)

