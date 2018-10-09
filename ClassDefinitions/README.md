# Class Definitions

Directory path: `offline_new/MacrosTrunk/ClassDefinitions/`

This directory contains classes and structures that are commonly used throughout
the code. It is automatically included on ROOT startup if you start in the `offline_new/MacrosTrunk` directory
by the `rootlogon.C` file. If it is not included, then run

```
.include path/to/ClassDefinitions/
``` 
at the ROOT prompt.

The implementation files are compiled by the `LoadLibrariesACLiC.C` script on start up.
To add your own class, follow the existing examples. In particular, you must
 1. Extend the TObject class.
 2. Include the line ClassDef(ClassName, 1) at the end of the `.hpp` file.
 3. Include the line ClassImp(ClassName) at the start of the `.cpp` file.
 4. Add the line `gROOT->ProcessLine(.L "MyClass.cpp+");` in `LoadLibrariesACLiC.C`.