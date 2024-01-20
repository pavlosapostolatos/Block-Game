#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyHealthWidget.h"
#include "HeartWidget.h"
#include "ToolbarWidget.h"
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
	
	void ConstructAll();
};