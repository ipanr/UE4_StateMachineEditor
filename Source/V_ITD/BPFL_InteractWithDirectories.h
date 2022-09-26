#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFL_InteractWithDirectories.generated.h"

UCLASS()
class V_ITD_API UBPFL_InteractWithDirectories : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "File in directory interactions", meta = (keywords = "save"))
	static bool SaveArrayText(FString saveDirectory, FString fileName, TArray<FString> savedText, bool allowOverWritting);
	
};
