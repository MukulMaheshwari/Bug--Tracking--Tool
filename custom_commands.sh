#!/bin/bash

function help(){
gcc /home/anshul/Bug-Tracking-Tool/commandInfo.c -o commandInfo
./commandInfo
}

function tester(){
gcc /home/anshul/Bug-Tracking-Tool/Tester.c -o tester
./tester $1
}

function pm(){
gcc /home/anshul/Bug-Tracking-Tool/ProjectManager.c -o pm
./pm $1   
}

function developer(){
gcc /home/anshul/Bug-Tracking-Tool/Developer.c -o developer
./developer $1   
}

function bgt(){
    if [ "$1" == "tester" ]
    then 
        if [ "$2" == "view" ]
        then
            tester view
        elif [ "$2" == "create" ]
        then
            tester create
        fi
    elif [ "$1" == "pm" ]
    then 
        if [ "$2" == "view" ]
        then
            pm view
        elif [ "$2" == "assign" ]
        then
            pm assign
        fi
    elif [ "$1" == "developer" ]
    then 
        if [ "$2" == "view" ]
        then
            developer view
        elif [ "$2" == "update" ]
        then
            developer update
        fi
    elif [ "$1" == "help" ]
    then 
        help
    fi
}
