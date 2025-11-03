// Made by Alexander Robinson. All rights reserved.


#include "EnemyCharacter.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UDefaultAttributeSet>(TEXT("CharacterAttributeSet"));
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitializeAbilitySystem();
}

void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyCharacter::InitializeAbilitySystem()
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

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		UDefaultAttributeSet::GetHealthAttribute()).AddUObject(
			this, &ThisClass::OnHealthChanged);
}

void AEnemyCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	NotifyHealthAttributeChanged(Data.OldValue, Data.NewValue);
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}