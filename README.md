# Coding Practices and Project Summary

New contributors: please read this document before you start coding!

This project uses ROOT version 6, C++11, the Boost C++ library (version 1.64), CMake, and subversion.

This file contains guidelines to help keep the code contained 
in the `offline_new/MacrosTrunk` directory readable and maintainable. It is intended to be a 
succinct summary of the basic coding conventions used in this project to help you 
start coding quickly. 

Due to the large amount of code created before this document
was written, not all of the guidelines presented below are followed throughout the project. However, new code is 
expected to follow the guidelines whenever possible. Refactoring of old code to follow the guidelines 
is encouraged and appreciated. 

This is a work in progress and future students and contributors are welcome 
to make additions and modifications to this document 
(after discussing with everyone else of course). 

## Quick start
First, checkout the code from subversion:
```bash
svn checkout svn://helium.physics.sc.edu/jparc/offline_new /path/to/local/copy/offline_new
```
Then, set your environment variables. Edit your `.bashrc` or `.bash_profile` and add these lines:

```bash
export path_raw=/path/to/raw/data/
export path_root=/path/to/root/trees/
export path_merged=/path/to/merged/trees/
export path_histo=/path/to/histograms/
```

You must have installed ROOT version 6, a C++11 compiler, and the Boost C++ library to run the code.

To run the code, simply start ROOT in the `MacrosTrunk` directory. The code should compile automatically
on ROOT start up. This may take a few minutes at first, but subsequent ROOT sessions should start much quicker as only 
modified files need to be recompiled. To run any of the ROOT macros available in the `MacrosTrunk` directory, simply
type the name of the macro (without the .C extension) and the required parameters. For example:

```bash
$ cd /path/to/MacrosTrunk/
$ root
```
ROOT should start up and compile the code. At the ROOT prompt, you can run a macro by typing, for example:

```
root > AnalyzeEvent(3994, 9)
```
If the macro you want to run was not loaded on startup, you must load it first with `.L MacroName.C`:

```
root > .L SFT_Analysis.C
root > SFT_Analysis
```

For more details about the project structure and code, see the `README.md` files located in the `ClassDefinitions`,
and `Functions` directories.
Also be sure to check out the ROOT and Boost documentation online.

## General guidelines
These should really go without saying, but...

 * Remember that coding is a collaborative process. Be sure to communicate regularly with everyone else.
 Have frequent code reviews, and ask lots of questions.
 
 * Keep it simple stupid (KISS). Prioritize clarity over cleverness. Make sure your code is readable and maintainable.
 
 * Do not optimize pre-maturally. Write code that makes sense and works first, then optimize if you need the code to run
 faster. Try to profile the code to identify the bottlenecks and resolve them instead of changing things haphazardly.
 
 * Don't reinvent the wheel. Look online for library solutions before you try to code an algorithm from
 scratch. Don't repeat what someone else has already done. Code in libraries are generally well tested and fast, and
 likely better than what you'll come up with.
 
 * Refactor often. As the code base grows, it will often become untidy and difficult to read and maintain. 
 Keep a habit of refactoring often and the code will never grow into a monster.
 
 ## Pro-Tips
 * Use the object oriented features of C++ and ROOT. Be sure to follow the 
 [SOLID](https://en.wikipedia.org/wiki/SOLID) principles when coding.
 Write your own classes and use abstraction to make the code easier to understand. Your code should be modular,
 with clearly defined inputs and outputs. For example, analysis, printing, and plotting functions should be completely
 separate from each other.
 All class definition and struct definition files should be placed in the 
 `offline_new/Macros/ClassDefinitions/` directory.
 
 * Use subversion! Commit your changes and update your working copy as often as you can to minimize merge conflicts. 
 Make sure meet up with other coders when there are merge conflicts to resolve them.
 This project is organized with `MacrosBranches`, `MacrosTags`, and `MacrosTrunk` directories, and
 uses the "branch when necessary" approach. See http://svnbook.red-bean.com for more details.
 
 * Many functions in this project are hundreds or thousands of lines long.
 Going forward, please break up your functions into smaller, logical pieces. Remember to follow
 the one function one purpose rule. Helper functions may be placed in
 the `offline_new/Macros/Functions/` directory, or somewhere else in the file. It is expected that most functions 
 will only be tens of lines long, not hundreds or thousands.
 
 * Use comments wisely. Follow the guidelines in the **Comments** sections, and be sure to explain
 the logic and physics of your code if you believe future confusion is likely. In a complex physics project,
 comments are absolutely essential for future coders to maintain and contribute to the code base.
 
 * Always use header files and header guards to separate the interface from the implmentation. 
  Only `#include` header files (never source files). 
  For more information, see the **Headers** sections.
 
 * Be wary of declaring a lot of constants and variables in header files. Often, that makes it difficult for others 
 to determine the use of that variable. Declare and initialize variables in narrowest scope possible. 
 (Currently, I am upset about the idiotic usage of `Batch_Variables.h`). 
 Only commonly used constants that are used throughout
 the project should be in header files _in their own namespace_.

 * Avoid using statements like  `using namespace std;`. This is a complex project, and we would like to avoid name
   clashes. Just type the extra `std::` or type something like `using std::cout; using std::endl;`.
 
 * Do not leave unused code commented out in the source files! After you've solved the problems and fixed the bugs,
   then delete the old stuff. Leaving old code "just in case" often just clutters the code and confuse others who
   work on the code. If you've committed your code, it is saved by subversion anyway, and if you think you must leave in commented code, please add comments explaining why.
   
 * For anything not addressed here, please follow the example of the existing code (please reference a more recent 
  file) and/or follow the Google C++ coding practices found at
   [https://google.github.io/styleguide/cppguide.html]
   
## Indents and spacing
Use four spaces to indent your code. Include a blank line in between functions, and class definitions. 
Opening braces should go on the same line as the function / class name / struct / statement, and closing braces should be
on its own line.

## Naming conventions
 Variables and function parameters should be named using `snake_case`, 
 and be self-descriptive. As this is a complicated physics project, 
 longer variable names are expected. 
 You are encouraged to prefer longer, more descriptive variable names that are
 easy to understand than to save space by using potentially confusing abbreviations.
 If the variable name is still confusing, please add a comment!
   
 Member variables (both private and public) should be prefixed with `m_`. An exception exists for member variables 
 that correspond to root file leaves (for example the public arrays in DetectorData), where the name should match the
 branch name in the root file.
 
 Pointers should be prefixed with `p_`. For example, `Coordinates *p_coords;`.

  ```$xslt
  // Bad; This was declared in a large header file with many other variables.
  // and the corr is ambiguous (correlated? corrected?). It's type and usage
  // is not readily available.
  ADC_High_corr_max = 0;
  
  // Good
  Int_t ADC_High_corrected_max = 0;
  
   ```
 Functions should be named using `camelCase`. This applies to the regular helper functions
 as well as member functions. Source files containing only function declarations should
 similarly be named using camelCase. Function names should use verbs that describe the action
 of the function.

 Classes, structs, enums, and namespaces should be named using `PascalCase`. 
  
 ROOT macros should be named using `PascalCase` and should use verbs, just like for functions.
 ```$xslt
 DisplayEvent(run_num, event_num)  // good macro name
 Event_Display(run_num, event_num) // bad macro name
 ```
 
 Constants should be named using ALLCAPS. 

 File extenions should follow the current scheme. Source files should end with `.cpp`,
 and header files with `.hpp`  (except for the ROOT macros files which end with `.C` and `.h`).
 
## Basic data types
As this is a ROOT project, there are some usages of ROOT data types over C++ types.
(e.g. Int_t instead of int). However, both appear to work the same way, so it is up to you.

## Comments
Comments should be used wherever the author feels that a new coder would benefit from an explanation in plain
English. Your code should be self-descriptive. Do not use comments to point out details that are obvious in the code.

Example of a poor comment:
```$xslt
Int_t gapCounter[12] = {0};  // initialize the gapCounter array to 0
```

Example of a good comment:
```
// Keep track of the score for each TOF1 gap. 
// At the end, the gap with the highest score is the most likely one.
Int_t gapCounter[12] = {0}; 
```

Block comments should go at the top of each file after the include statements
(unless the file is very short and self-explanatory).
At the very least, include your name and date of creation of the file. A short description of the class with 
usage examples and any special notes would also be helpful. It would also be appreciated if you would
leave a contact email in case anyone in the future has questions about your code.
 
For class definitions, include the block comment only in the header file and not the source file.
Files containing a collection of regular function definitions should have a short description of 
why the functions are grouped together and where they are used.

```$xslt
/*
 * Created by Jack Hong on 2018-05-28 (jhong@alumni.ubc.ca)
 * 
 * Usage: for loading and manipulating TREK data from root files. Instantiation
 * of this class initializes the ROOT Tree. Assumes root file is organized like
 * in Run3994MS.root.
 *
 * NB: Changes to root file layout will require changes to this class.
 *
 * Class automatically loaded on ROOT start up by the rootlogon.C script found in the offline_new/Macros directory
 * if you are working in that directory. Otherwise, you will need to load it with ".L DetectorData.C".
 *
 * EXAMPLE:
 *    // Load the data from run 3994 (Run3994MS.root) and set the arrays to data from event 9
 *    DetectorData data(3994, 9);
 *
 *    data.correctTimeWalk();      // apply time walk corrections to event 9 data
 *    data.isTimeWalkCorrected();  // true
 *    data.getEntry(12);           // switch to event 12
 *
 *    data.isTimeWalkCorrected()  // false because event switched
 *    data.getEntry(9)            // switch back to event 9
 *    data.isTimeWalkCorrected()  // false because GetEntry() resets data to root file values.
 */
```

Function comments should go above complex functions and describe their purpose in plain English.
Do not restate the signature as that can be read from the function declaration itself. 
Be sure to explain the high level reasoning and physics behind your code. If the usage
is potentially confusing, please provide an example.

In the header file, write comments about the usage of the function. For example,
any pre-conditions, post-conditions, and exception handling, as well as a short
summary of what the function does and what the parameters are 
if it is not immediately clear. 

In the source file, write comments about the implementation of the function.
This is where you should explain the physics or the particular algorithm used
in your function.
```$xslt
// in determineGap.h
/* 
 * Return the TOF1 gap that the lepton passed through (a number between [1, 12])
 * You must initiali
 */ ...
 Int_t determineGap(DetectorData data);
 
 
 // in determineGap.C
 /*
  * There are twelve gaps in total, arranged like the hours of a clock.
  * Each gap is given a running score, tracked in gap_counter. For each
  * hit in the outer and inner ...
  */
 Int_t determineGap(DetectorData data) {
    ...
 }


```
 
## Header files
All source files should have an accompanying header file, even if the header is short. The goal is to separate the
interface from the implementation. This will also help with compile time by not compiling all of the code when changes
are made. 

Variables should be defined and initialized _where they are used_ when possible, and not
in a separate header file. This is to help keep the type and usage of each variable readily
available to anyone who reads the code.

Only include header files. NEVER source files.

All header files MUST use header guards. Currently most files use guards like this:
   ```
   #ifndef MY_FILE_h
   #define MY_FILE_h
   
   // your code here
   
   #endif  // MY_FILE_h
   ```
  
but this should also be supported:  
```
#pragma once
```

## Namespaces
Avoid using the `using` directive if possible to avoid name clashes. 

For global variables (you should be sure that they MUST be global variables), put them in their own namespace. For example, see 
`CommonParameters.h`.

## Tests
You are encouraged to use test driven development when you code. Details
to come later?? Should we use the boost framework?
=======
# TargetAnalysis
>>>>>>> bcf8ea288d92965db10c53f9ccafcaa3a68dbe9c
