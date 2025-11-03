// Made by Alexander Robinson. All rights reserved.


#include "PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UDefaultAttributeSet>(TEXT("DefaultAttributeSet"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitializeAbilitySystem();
	SetupPlayerInputComponent(InputComponent);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		for (const auto& [InputAction, AbilityInput] : AbilityInputBindings.InputBindings)
		{
			EnhancedInputComponent->BindAction(
				InputAction,
				ETriggerEvent::Triggered,
				this,
				&ThisClass::AbilityInputBindingPressedHandler,
				AbilityInput);

			EnhancedInputComponent->BindAction(
				InputAction,
				ETriggerEvent::Completed,
				this,
				&ThisClass::AbilityInputBindingReleasedHandler,
				AbilityInput);
		}
	}
}

void APlayerCharacter::InitializeAbilitySystem()
{
	if (!IsValid(AbilitySystemComponent) || !IsValid(AttributeSet))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to initialize AbilitySystem"));
		return;
	}

	if (IsValid(InitialAbilities))
	{
		InitialAbilitySpecHandles.Append(InitialAbilities->GrantAbilities(AbilitySystemComponent));
	}

	if (IsValid(InitialGameplayEffect))
	{
		AbilitySystemComponent->ApplyGameplayEffectToSelf(
			InitialGameplayEffect->GetDefaultObject<UGameplayEffect>(),
			0.0f,
			AbilitySystemComponent->MakeEffectContext());
	}
}

void APlayerCharacter::AbilityInputBindingPressedHandler(EAbilityInput AbilityInput)
{
	AbilitySystemComponent->AbilityLocalInputPressed(static_cast<uint32>(AbilityInput));
}

void APlayerCharacter::AbilityInputBindingReleasedHandler(EAbilityInput AbilityInput)
{
	AbilitySystemComponent->AbilityLocalInputPressed(static_cast<uint32>(AbilityInput));
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}