// Made by Alexander Robinson. All rights reserved.


#include "AbilityDataAsset.h"

#include "AbilitySystemComponent.h"

TArray<FGameplayAbilitySpecHandle> UAbilityDataAsset::GrantAbilities(UAbilitySystemComponent* AbilitySystemComponent) const
{
	check(AbilitySystemComponent);

	TArray<FGameplayAbilitySpecHandle> Handles;
	Handles.Reserve(Items.Num());

	for (const auto [GameplayAbility, Input] : Items)
	{
		Handles.AddUnique(AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(GameplayAbility,0, static_cast<uint32>(Input))
		));
	}

	return Handles;
}