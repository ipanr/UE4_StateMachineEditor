#include "BPFL_InteractWithDirectories.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/CString.h"
#include <string>

static private FString AddStringAndLineTerminatorWithIndent(FString stringToAdd, int indent = 0);
static private FString StartClassInJSON(FString className, int indent);

bool UBPFL_InteractWithDirectories::SaveArrayText(FString saveDirectory, FString fileName, TArray<FString> savedText, bool allowOverWritting = false){
    saveDirectory += "\\";
    saveDirectory += fileName;
    int indent = 1;

    if(!allowOverWritting)
    {
        if(FPlatformFileManager::Get().GetPlatformFile().FileExists(*saveDirectory))
        {
            return false;
        }
    }

    FString finalString = "";
    //Begin JSON
    finalString += StartClassInJSON("", 0);

    for(FString& stringFromList: savedText)
    {
        //A switch from string is not possible in C++
        if (stringFromList == "START_STATE"){
                finalString += AddStringAndLineTerminatorWithIndent("{", indent);
                indent ++;
        } else if (stringFromList == "END_STATE"){
                finalString += AddStringAndLineTerminatorWithIndent("]", indent);                    
                indent = 1;
                finalString += AddStringAndLineTerminatorWithIndent("},", indent);
        } else if (stringFromList == "START_ACCESIBLE_STATE"){
                indent ++;
                finalString += AddStringAndLineTerminatorWithIndent("{", indent);
                indent ++;
        } else if (stringFromList == "END_ACCESIBLE_STATE"){
                indent --;
                finalString += AddStringAndLineTerminatorWithIndent("},", indent);
                indent --;
        } else if (stringFromList == "START_DETECTIONS"){
                indent ++;
        } else if (stringFromList == "END_DETECTIONS"){
                indent --;
                finalString += AddStringAndLineTerminatorWithIndent("]", indent);
        } else {
                finalString += AddStringAndLineTerminatorWithIndent(stringFromList, indent);
        }
    }

    finalString += AddStringAndLineTerminatorWithIndent("]");
    //End JSON

    return FFileHelper::SaveStringToFile(finalString, *saveDirectory);
}

FString AddStringAndLineTerminatorWithIndent(FString stringToAdd, int indent){
    FString localString = "";
    int indenIteration = 0;

    while (indenIteration < indent){
        localString += "\t";
        indenIteration++;
    }

    localString += stringToAdd;
    localString += LINE_TERMINATOR;

    return localString;
}

FString StartClassInJSON(FString className, int indent){
    FString localString = "";
    int indenIteration = 0;

    while (indenIteration < indent){
        localString += "\t";
        indenIteration++;
    }

    if(className != ""){
        localString += "\"";
        localString += className;
        localString += "\": ";
    }

    localString += "[";
    localString += LINE_TERMINATOR;

    return localString;
}
