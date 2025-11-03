// Made by Alexander Robinson. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilityDataAsset.h"
#include "AbilitySystemInterface.h"
#include "DefaultAttributeSet.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class ANGELSCRIPTPROJECT_API AEnemyCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return  AbilitySystemComponent; }
	
	void OnHealthChanged(const FOnAttributeChangeData&);
	UFUNCTION(BlueprintImplementableEvent, Category="Attribute")
	void NotifyHealthAttributeChanged(float OldValue, float NewValue);

protected:
	UPROPERTY(VisibleAnywhere, Category="Ability")
	UAbilitySystemComponent* AbilitySystemComponent { nullptr };
	UPROPERTY(VisibleAnywhere, Category="Ability")
	UDefaultAttributeSet* AttributeSet { nullptr };
	UPROPERTY(EditDefaultsOnly, Category="Ability")
	UAbilityDataAsset* InitialAbilities { nullptr };
	UPROPERTY(EditDefaultsOnly, Category="Ability")
	TSubclassOf<UGameplayEffect> InitialGameplayEffect;

	UPROPERTY(Transient)
	TArray<FGameplayAbilitySpecHandle> InitialAbilitySpecHandles;

private:
	void InitializeAbilitySystem();
};