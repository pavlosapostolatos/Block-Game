#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyHealthWidget.h"
#include "HeartWidget.h"
#include "ToolbarWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MainHud.generated.h"

UCLASS()
class BLOCKGAME_API UMyMainHud : public UUserWidget
{

private:
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Text, meta = (AllowPrivateAccess = "true"))
	UMyHealthWidget* HealthWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Text, meta = (AllowPrivateAccess = "true"))
	UHeartWidget* HeartWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Text, meta = (AllowPrivateAccess = "true"))
	UToolbarWidget* Toolbar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Text, meta = (AllowPrivateAccess = "true"))
	UTextBlock* WaveTextBlock;

	FTimerHandle TimerHandle;

public:
	[[nodiscard]] UMyHealthWidget* GetHealthWidget() const
	{
		return HealthWidget;
	}

	void SetHealthWidget(UMyHealthWidget* Widget)
	{
		this->HealthWidget = Widget;
	}

	[[nodiscard]] UToolbarWidget* GetToolbar() const
	{
		return Toolbar;
	}

	void SetToolbar(UToolbarWidget* Widget)
	{
		this->Toolbar = Widget;
	}

	[[nodiscard]] UHeartWidget* GetHeartWidget() const
	{
		return HeartWidget;
	}

	void SetHeartWidget(UHeartWidget* newHeartWidget)
	{
		this->HeartWidget = newHeartWidget;
	}

	void SetWave(int Wave)
	{
		WaveTextBlock->SetVisibility(ESlateVisibility::Visible);
		WaveTextBlock->SetText(FText::FromString("Wave: " + FString::FromInt(Wave)));
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMyMainHud::SetHiddenText, 3.0f, false);
	}
	
	void SetHiddenText() const
	{
		WaveTextBlock->SetVisibility(ESlateVisibility::Hidden);
	};
	
	void ConstructAll();
};