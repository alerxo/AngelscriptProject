// Made by Alexander Robinson. All rights reserved.


#include "DefaultAttributeSet.h"
#include "GameplayEffectExtension.h"

void UDefaultAttributeSet::PreAttributeChange(const FGameplayAttribute& GameplayAttribute, float& X)
{
	Super::PreAttributeChange(GameplayAttribute, X);
}

void UDefaultAttributeSet::PostGameplayEffectExecute(
	const FGameplayEffectModCallbackData& GameplayEffectModCallbackData)
{
	Super::PostGameplayEffectExecute(GameplayEffectModCallbackData);

	if (GameplayEffectModCallbackData.EvaluatedData.Attribute == GetDamageAttribute())
	{
		const float InflictedDamage = GetDamage();
		SetDamage(0.0f);

		if (InflictedDamage > 0.0f)
		{
			const float UpdatedHealth = FMath::Clamp(GetHealth() - InflictedDamage, 0.0f, GetHealthMax());
			SetHealth(UpdatedHealth);
		}
	}
}