#pragma once

#include "CoreMinimal.h"

namespace AAPMFindHelpers
{
	template<typename TBaseType, typename TLookingType>
	TArray<const TLookingType*> FindValueProperties(const TBaseType* Value)
	{
		TArray<const TLookingType*> results;
	
	
		for (const auto it : TPropertyValueRange<FStructProperty>(TBaseType::StaticStruct(), Value))
		{
			if (it.Key->Struct->IsChildOf(TLookingType::StaticStruct()))
			{
				const TLookingType* typeDataPtr = static_cast<const TLookingType*>(it.Value);
				results.Add(typeDataPtr);
			}
		}

		return results;
	}

}
