// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GAAttributesBase.h"
#include "../GAAttributeBase.h"
#include "GAAttributesTest.generated.h"

/**
 * 
 */
UCLASS()
class GAMEATTRIBUTES_API UGAAttributesTest : public UGAAttributesBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Attributes")
		FGAAttributeBase Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Attributes")
		FGAAttributeBase Energy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Attributes")
		FGAAttributeBase Stamina;
};
