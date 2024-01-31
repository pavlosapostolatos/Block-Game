// This is an empty cpp file you just created for the test,  of course, link to Unreal Engine

#include "AITestsCommon.h"
#include "Boxes/BlockBoxRed.h"
#include "BlockGameInstance.h"
// Unreal Automation Spec, I won't go into the naming convention area. You probably should refer to another page and test it out yourself. After all, I believe best way to learn is to practice.
BEGIN_DEFINE_SPEC(BlockGameInstanceTest, "BlockGame.BlockGameInstanceTest",
                  EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
	// Global variables that are shared by all tests go here
	UWorld* World = nullptr;
END_DEFINE_SPEC(BlockGameInstanceTest)

// Tests in this function will be executed. Generally, you only need this function to run test. Class is not needed.
void BlockGameInstanceTest::Define()
{
	// Code to run before each tests
	BeforeEach([this]()
	{
		// Normally I will initialize variables here
		// Note: Try not to do any test in this scope as `BeforeEach` is not meant to test any expectation,
		// do read the unreal link I provided for more information

		/** Function from Unreal Automation header file
		*   Basically, it opens up a map for your test to run in it
		*/
	});

	// Code to run after each tests
	AfterEach([this]()
	{
		// Normally I would do any clean up here

		// Note: Again, try not to do any test in this scope as `AfterEach` is not meant to test any expectation,
		// do read the unreal link I provided for more information
	});

	// Describe doesn't really do anything, literally just 'describe' the string in the output log
	Describe("Test TSet<FBlockData>", [this]()
	{
		// /* In Unreal Document, `It` is literally means it. In this case, `It` means "Fire Function".
		// *  So in the log, this will show : Fire Function.Should shoot one bullet out.
		// *  My practice is to describe the `It` in full sentence. Something like "ShootBullet should only fire one bullet out."
		// */ It really depends on how you want to do it that will make thing easier to you and your team. At least in my opinion, there isn't any wrong or correct way to do it. 
		It("Simple Add Remove", [this]()
		{
			// Make the test pass by returning true, or fail by returning false.
			UBlockGameInstance* instance = NewObject<UBlockGameInstance>(GetTransientPackage(),
			                                                             UBlockGameInstance::StaticClass());
			const FTransform transform(FVector(1.0, 1.0, 1.0));
			const ABlockBox* actor = FAITestHelpers::GetWorld()->SpawnActor<ABlockBox>(
				ABlockBoxRed::StaticClass(), transform);
			const FRotator Rotator;
			const FBlockData BlockData(actor->GetClass(), FVector(1.0, 1.0, 1.0), Rotator);
			instance->AddBox(BlockData);
			TestEqual("element added", instance->SavedBlocks().Num(), 1);
			instance->DeleteBox(BlockData);
			TestEqual("element deleted", instance->SavedBlocks().Num(), 0);
			return true;
		});

		// Another test that related to the Fire Function can be put here. I will just leave it blank here
		It("Add duplicate", [this]()
		{
			// Make the test pass by returning true, or fail by returning false.
			UBlockGameInstance* instance = NewObject<UBlockGameInstance>(GetTransientPackage(),
			                                                             UBlockGameInstance::StaticClass());
			const FTransform transform(FVector(1.0, 1.0, 1.0));
			const ABlockBox* actor = FAITestHelpers::GetWorld()->SpawnActor<ABlockBox>(
				ABlockBoxRed::StaticClass(), transform);
			const FRotator Rotator;
			const FBlockData BlockData(actor->GetClass(), FVector(1.0, 1.0, 1.0), Rotator);
			instance->AddBox(BlockData);
			TestEqual("element added", instance->SavedBlocks().Num(), 1);
			instance->AddBox(BlockData);
			TestEqual("element not added", instance->SavedBlocks().Num(), 1);
			return true;
		});
	});
}
