// Made by Alexander Robinson. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilityDataAsset.h"
#include "AbilitySystemInterface.h"
#include "DefaultAttributeSet.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "PlayerCharacter.generated.h"

USTRUCT()
struct FAbilityInputToInputBinding
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction { nullptr };
	UPROPERTY(EditDefaultsOnly)
	EAbilityInput AbilityInput { EAbilityInput::None };
};

USTRUCT()
struct FAbilityInputBindings
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TArray<FAbilityInputToInputBinding> InputBindings;
};

UCLASS()
class ANGELSCRIPTPROJECT_API APlayerCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return  AbilitySystemComponent; }

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

	UPROPERTY(EditDefaultsOnly, Category="Input")
	FAbilityInputBindings AbilityInputBindings;

private:
	void InitializeAbilitySystem();
	void AbilityInputBindingPressedHandler(EAbilityInput);
	void AbilityInputBindingReleasedHandler(EAbilityInput);
};