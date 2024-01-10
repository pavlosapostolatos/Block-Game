#include "AITestsCommon.h"
#include "BlockBoxRed.h"
#include "BlockGameInstance.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(BlockGameInstanceTest, "Private.BlockGameInstanceTest",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool BlockGameInstanceTest::RunTest(const FString& Parameters)
{
	// Make the test pass by returning true, or fail by returning false.
	UBlockGameInstance* instance = NewObject<UBlockGameInstance>(GetTransientPackage(),
	                                                             UBlockGameInstance::StaticClass());
	const FTransform transform(FVector(1.0, 1.0, 1.0));
	const ABlockBox* actor = FAITestHelpers::GetWorld()->SpawnActor<ABlockBox>(ABlockBoxRed::StaticClass(), transform);
	const FRotator Rotator;
	const FBlockData BlockData(actor->GetClass(), FVector(1.0, 1.0, 1.0), Rotator);
	instance->AddBox(BlockData);
	TestEqual("element added", instance->SavedBlocks().Num(), 1);
	instance->DeleteBox(BlockData);
	TestEqual("element deleted", instance->SavedBlocks().Num(), 0);
	return true;
}
