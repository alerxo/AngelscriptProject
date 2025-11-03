class ATargetDummy_Angel : AEnemyCharacter
{
    UPROPERTY()
    TSubclassOf<ATargetDummy_Angel> ActorClass;

    UPROPERTY()
    UAnimMontage DamageMontage;
    UPROPERTY()
    UAnimMontage DeathMontage;

    UPROPERTY()
    UMaterial FlashMaterial;
    UPROPERTY()
    UMaterialInstance MannyMaterial1;
    UPROPERTY()
    UMaterialInstance MannyMaterial2;

    float DeathTimer = -1.0;
    const float DeathDuration = 2.0;

    float FlashTimer = -1.0;
    const float FlashDuration = 0.1;

    UFUNCTION(BlueprintOverride)
    void Tick(float DeltaSeconds)
    {
        if(DeathTimer > 0.0)
        {
            DeathTimer -= DeltaSeconds;

            if(DeathTimer < 0)
            {
                SpawnActor(ActorClass, this.ActorLocation, this.ActorRotation);
                DestroyActor();
            }
        }

        if(FlashTimer > 0.0)
        {
            FlashTimer -= DeltaSeconds;

            if(FlashTimer < 0)
            {
                USkeletalMeshComponent SkeletalMesh = USkeletalMeshComponent::Get(this);
                SkeletalMesh.SetMaterial(0, MannyMaterial1);
                SkeletalMesh.SetMaterial(1, MannyMaterial2);
            }
        }
    }

    UFUNCTION(BlueprintOverride)
    void NotifyHealthAttributeChanged(float OldValue, float NewValue)
    {
        if(OldValue == 0)
        {
            return;
        }

        if(NewValue == 0)
        {
            UCapsuleComponent Collider = UCapsuleComponent::Get(this);
            Collider.SetCollisionEnabled(ECollisionEnabled::NoCollision);

            float MontageDuration = PlayAnimMontage(DeathMontage);
            DeathTimer = MontageDuration + DeathDuration;
        }

        else
        {
            PlayAnimMontage(DamageMontage);
        }

        USkeletalMeshComponent SkeletalMesh = USkeletalMeshComponent::Get(this);
        SkeletalMesh.SetMaterial(0, FlashMaterial);
        SkeletalMesh.SetMaterial(1, FlashMaterial);
        FlashTimer = FlashDuration;
    }
}