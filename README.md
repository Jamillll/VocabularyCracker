# Vocabulary Cracker
A key logger that tracks how often you use words, letting you sort it and filter out common words to see what your vocabulary is like. This project is split into two main parts, the first of which is "VCCore". This will be a background process that, similarly to a key logger, will track and register key presses and use that data to track what words you use. From there VCCore will record that data and store it. This is where the second part of Vocabulary Cracker comes in, that being VCApp. This is a seperate program that will retrieve the data and display it. On top of that VCApp allows you to configure VCCore in how it functions. 

## Base level features
Base level features are features that Vocabulary Cracker needs to contain to meet its first milestone. These features alone won't make it ready for a version 1 release but they are a large step. Of course, having these features by no means make this project complete, we still need to impliment the CRUD options and ideally all of the advanced features but having these base level features are a large step in the process.

### VCCore:
- Read individual key presses while running
- Get list of dictionary words from file
- Process individual key presses and interpret them as words
- Compare interpreted words to list of dictionary words
- Store what and how many words in an output file

### VCApp:
- Read what and how many words from backend’s output file
- Display a list of used words and their used amount in a table
- Sort table based on either word count or amount used

## CRUD Operations
The plan for implementing CRUD operations in this program is to, atleast before getting to advanced features, allow users to read from our word list, add custom words to it (used if people want to track use of “XD” for example), update words in the list and delete words from the list. Once the CRUD operations have been implimented, Vocabulary Cracker will be ready for its first release. These operations will have no effect on VCCore

### VCApp:
- TODO

## Advanced features
Advanced features are features that I will add after the base release of Vocabulary Cracker is completed.

### VCCore:
- TODO

### VCApp:
- TODO
