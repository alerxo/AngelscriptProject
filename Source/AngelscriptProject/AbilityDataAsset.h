// Made by Alexander Robinson. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/DataAsset.h"
#include "AbilityDataAsset.generated.h"

UENUM(BlueprintType)
enum class EAbilityInput : uint8
{
	None = 0 UMETA(Hidden),
	Jump = 1,
	Primary = 2,
	Secondary = 3,
	Button1 = 4,
	Button2 = 5,
	Button3 = 6,
	Button4 = 7,
	Button5 = 8,
};

USTRUCT()
struct FAbilitySetItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Ability")
	TSubclassOf<UGameplayAbility> GameplayAbility;
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	EAbilityInput Input { EAbilityInput::None };
};

UCLASS()
class ANGELSCRIPTPROJECT_API UAbilityDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Ability")
	TArray<FAbilitySetItem> Items;
	TArray<FGameplayAbilitySpecHandle> GrantAbilities(UAbilitySystemComponent* AbilitySystemComponent) const;
};
