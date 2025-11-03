class AFireBall_Angel : AActor
{
    UPROPERTY()
    UNiagaraSystem ImpactNiagaraSystem;

    FGameplayEffectSpecHandle Handle;

    float ScaleAlpha = 0;
    const float ScaleSpeed = 1;
    const float ImpactRadius = 250;

    UFUNCTION(BlueprintOverride)
    void BeginPlay()
    {
        SetActorScale3D(FVector(0, 0, 0));
    }

    UFUNCTION(BlueprintOverride)
    void Tick(float DeltaSeconds)
    {
        if(ScaleAlpha >= 1)
        {
            return;
        }

        FVector Scale = Math::Lerp(GetActorScale3D(), FVector(0.5, 0.5, 0.5), ScaleAlpha);
        SetActorScale3D(Scale);

        ScaleAlpha += (DeltaSeconds * ScaleSpeed);
        ScaleAlpha = Math::Clamp(ScaleAlpha, 0, 1);
    }

    UFUNCTION(BlueprintOverride)
    void Hit(UPrimitiveComponent MyComp, AActor Other, UPrimitiveComponent OtherComp, bool bSelfMoved,
             FVector HitLocation, FVector HitNormal, FVector NormalImpulse, FHitResult Hit)
    {
        UAbilitySystemComponent AbilitySystemComponent = UAbilitySystemComponent::Get(Owner);

        if(IsValid(AbilitySystemComponent))
        {
            TArray<EObjectTypeQuery> Types;
            TSubclassOf<UClass> Filter;
            TArray<AActor> Ignore;
            TArray<AActor> OutActors;

            System::SphereOverlapActors(
                HitLocation, 
                ImpactRadius, 
                Types,
                Filter,
                Ignore,
                OutActors);

            for(auto Actor : OutActors)
            {
                UAbilitySystemComponent OtherAbilitySystemComponent = UAbilitySystemComponent::Get(Actor);
                
                if(!IsValid(OtherAbilitySystemComponent))
                {
                    continue;
                }

                AbilitySystemComponent.ApplyGameplayEffectSpecToTarget(Handle, OtherAbilitySystemComponent);
            }
        }

        Niagara::SpawnSystemAtLocation(ImpactNiagaraSystem, ActorLocation, ActorRotation);

        DestroyActor();
    }

    UFUNCTION()
    void SetHandle(FGameplayEffectSpecHandle GameplayEffectSpecHandle)
    {
        Handle = GameplayEffectSpecHandle;
    }
}