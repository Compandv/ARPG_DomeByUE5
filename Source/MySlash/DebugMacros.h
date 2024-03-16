#pragma once
#include "DrawDebugHelpers.h"

#define DRAW_SPHERE(location) if(GetWorld()) DrawDebugSphere(GetWorld(), location, 25.f, 12, FColor::Red, false, 30.f)
#define DRAW_SPHERE_COLOR(location, Color) if(GetWorld()) DrawDebugSphere(GetWorld(), location, 8.f, 12, Color, false, 5.f)

#define DRAW_SPHERE_SINGLEFRAME(location) if(GetWorld()) DrawDebugSphere(GetWorld(), location, 25.f, 12, FColor::Red, false, -1.f)
#define DRAW_LINE(startLocation, endLocation) if(GetWorld()) DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Red, true, -1.f, 0, 1.f)
#define DRAW_LINE_SINGLEFRAME(startLocation, endLocation) if(GetWorld()) DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Red, false, -1.f, 0, 1.f)

#define DRAW_POINT(location) if (GetWorld()) DrawDebugPoint(GetWorld(), location, 15.f, FColor::Red, true)
#define DRAW_POINT_SINGLEFRAME(location) if (GetWorld()) DrawDebugPoint(GetWorld(), location, 15.f, FColor::Red, false, -1.f)
#define DRAW_VECTOR(startLocation, endLocation)if(GetWorld()) \
{\
	DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Red, true, -1.f, 0, 1.f);\
	DrawDebugPoint(GetWorld(), endLocation, 15.f, FColor::Red, true);\
}

#define DRAW_VECTOR_SINGLEFRAME(startLocation, endLocation)if(GetWorld()) \
{\
	DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Red, false, -1.f, 0, 1.f);\
	DrawDebugPoint(GetWorld(), endLocation, 15.f, FColor::Red, false, -1.f);\
}