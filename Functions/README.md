# Functions
Directory path: `offline_new/MacrosTrunk/Functions`

This directory contains helper functions that are used by the ROOT macros.
It is recommended that you define one function per file, but you can also
group together related functions in one file if needed. You may also define
functions in the macros file itself if that function is only used in that
particular macro.

The directory is included by ROOT on startup
by the script `rootlogon.C` found in the main `offline_new/MacrosTrunk` directory.

To automatically load your function on ROOT startup so that it can be used
interactively and in ROOT macros,
add the appropriate line to the `LoadLibrariesACLiC.C` file. 

For example,
if you've defined a function named `myFunction` in `myFunction.cpp`, then add the following line to 
`LoadLibrariesACLiC.C` _before_ the lines to load any functions or macros that require the function in your file.
(i.e. order matters here.)

```
gROOT->ProcessLine(".L Functions/myFunction.cpp+");
```

Alternatively, simply run the line

```
.L myFunction.cpp+
```
at the root prompt.