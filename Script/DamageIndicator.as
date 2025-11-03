UCLASS(Abstract)
class UDamageIndicator : UUserWidget
{
    UPROPERTY(BindWidget)
    protected UTextBlock Text;

    UFUNCTION()
    void SetText(float Damage)
    {
        Text.SetText(FText::FromString(f"{Damage=}"));
    }
};