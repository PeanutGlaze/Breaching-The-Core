# Breaching The Core
 A text adventure in which you explore a mysterious drive

 -- Changelog --

 v.0.3:
 New features:
 + The file-reader can now jump to other flags without having to make a decision
 + The file-reader can now handle decisions with (up to) four cardinal directions
 + Added a bit more text to make working more structured

 - Removed the function to compare strings (strncmp() exists)

 v.0.2:
 + The code is now able to detect flags in txt-files, making it so choices are not hard-coded, thus making the program more flexible
 + The code detects file-paths and flags to jump to specific points in other files
 + The file with the main method has been reduced to just a few lines, because the txt-files don't need to be called manually anymore
 + Added a method to compare inputs better

 v.0.1:
 Added the framework for the game:
 + Program can traverse and read out files
 + Program can read and compare user input
