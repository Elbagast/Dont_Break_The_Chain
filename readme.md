Don't Break the Chain
======================

A simple tool based on the motivational technique used by Jerry Seinfeld:
http://lifehacker.com/281626/jerry-seinfelds-productivity-secret

This isn't a huge wall calender, but rather something that will easily allow the same sort of thing
for say, lots of small tasks or types of things I should be doing in the day. This is deliberately
simple to use because it isn't aiming to be a tool for tracking workload - that's another project.

Will it work out? Well the Github squares seem to be working on me and that was basically a test run
of this sort of thing...

Possible additonal features:
- Smarter chain management
    - Editing existing chain details?
    - Rearranging the list?
    - Store chains as active and inactive?
- Presentation and size
    - Alternative visualisations?
    - Longest/current streak?

Todo:
- Icon(s)
- About
- Licence(s)
- Figure out which Qt dlls it needs

Done:
- Selectable chain colours
- Make entirely Qt library based
- Saving and loading chains
    - Now in a single 'chains.xml' file
    - In the directory the .exe is in
- Make New_Chain_Dialog determine acceptable inputs in a better way
    - Displays seperate errors on an empty title and colours that are invalid
        - OK button is disabled if there is an error

Compiling Notes
----------------
- Qt 5.4 library
