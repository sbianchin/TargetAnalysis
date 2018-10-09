{
gROOT->SetStyle("Plain");
gROOT->LoadMacro("ProcEvent.C");
gSystem->Load("libTree"); 
gSystem->Load("libGpad");

gROOT->ProcessLine(".include ClassDefinitions/");
gROOT->ProcessLine(".include Functions/");
gROOT->ProcessLine(".include Parameters/");

gROOT->ProcessLine(".x LoadLibrariesACLiC.C");
}
