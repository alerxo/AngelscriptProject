// Made by Alexander Robinson. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "DefaultAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class ANGELSCRIPTPROJECT_API UDefaultAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UDefaultAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData HealthMax;
	ATTRIBUTE_ACCESSORS(UDefaultAttributeSet, HealthMax);

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UDefaultAttributeSet, Damage);
	
	UPROPERTY(BlueprintReadOnly, Category = "Strength")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UDefaultAttributeSet, Strength);

	virtual void PreAttributeChange(const FGameplayAttribute&, float&) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData&) override;
};
