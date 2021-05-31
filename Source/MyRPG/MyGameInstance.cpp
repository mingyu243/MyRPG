#include "MyGameInstance.h"

#include "Kismet/KismetMathLibrary.h"

void UMyGameInstance::SetUserName(FString NewUserName)
{
	UserName = NewUserName;
}

FString UMyGameInstance::GetUserName()
{
	if (UserName.IsEmpty())
	{
		int32 RandomNumber = UKismetMathLibrary::RandomIntegerInRange(0, 9999);
		UserName = FString::Printf(TEXT("Guest_%d"), RandomNumber);
	}

	return UserName;
}
